#include "Header.h"

#define DBINTERVAL 50

//GLOBAL VARIABLES
const uint8_t switchPins[SWITCHPINS] = {2, 3, 4, 5, 6, 7, 8, 9, 11, 12}; //define switch pins
int layer = MAXLAYERS - 1;
int pressedLayer[OEMCODES];


void PressKey(int layer, int key)
{
  BootKeyboard.press((KeyboardKeycode)keyToSend[layer][key]);
  pressedLayer[key] = layer;
    /*
    Serial.print(layer);
    Serial.print(" : ");
    Serial.print(key);
    Serial.print(" : ");
    Serial.println(keyToSend[layer][key]);*/
}

void ReleaseKey(int key)
{
  BootKeyboard.release((KeyboardKeycode)keyToSend[pressedLayer[key]][key]);
}

void LayerSwitch(int key, int inputLayer, bool press)
{
  if(press)
  {
    pressedLayer[key] = layer;
    layer = inputLayer;
  }
  else { layer = (inputLayer == layer) ? 10 : layer; }
}

void ToggleLayerSwitch(int key, int inputLayer, bool press)
{
  if(!press) return;
  layer = (inputLayer == layer) ? 10 : inputLayer;
}

void HandleKeyCode(uint8_t key, bool press)
{
  uint8_t val = (press) ? keyToSend[layer][key] : keyToSend[pressedLayer[key]][key];
  switch(val)
  {
    case LAYER0:
    case LAYER1:
    case LAYER2:
    case LAYER3:
    case LAYER4:
    case LAYER5:
    case LAYER6:
    case LAYER7:
    case LAYER8:
    case LAYER9:
    LayerSwitch(key, (val - 200), press);
    break;
    case TLAYER0:
    case TLAYER1:
    case TLAYER2:
    case TLAYER3:
    case TLAYER4:
    case TLAYER5:
    case TLAYER6:
    case TLAYER7:
    case TLAYER8:
    case TLAYER9:
    ToggleLayerSwitch(key, (val - 210), press);
    break;
    case LAYERD:
    layer = (press) ? 10 : layer;
    break;
    default:
    if(press) { PressKey(layer, key); }
    else { ReleaseKey(key); }
  }
}

class KbdRptParser : public KeyboardReportParser
{
  void PrintKey(uint8_t mod, uint8_t key);

protected:
  void OnControlKeysChanged(uint8_t before, uint8_t after);

  void OnKeyDown  (uint8_t mod, uint8_t key);
  void OnKeyUp  (uint8_t mod, uint8_t key);
  void OnKeyPressed(uint8_t key);
};

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)  //press corresponding key when a key is pressed
{
  //KeyboardReportParser().kbdLockingKeys.bLeds = BootKeyboard.getLeds();
  //PressKey(layer, key);
  HandleKeyCode(key, true);
  //(myHID)->SetReport(0,0,2,0,1,0x04);
}

void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)
{
  //ReleaseKey(key);
  HandleKeyCode(key, false);
}

void KbdRptParser::OnControlKeysChanged(uint8_t before, uint8_t after) {  //handles modifier keys (shift, ctrl, alt, gui)

  MODIFIERKEYS beforeMod;
  *((uint8_t*)&beforeMod) = before;

  MODIFIERKEYS afterMod;
  *((uint8_t*)&afterMod) = after;

  if (beforeMod.bmLeftCtrl != afterMod.bmLeftCtrl) { //LCTRL CHANGED
    HandleKeyCode( LCTRL, beforeMod.bmLeftCtrl < afterMod.bmLeftCtrl );
  }

  if (beforeMod.bmLeftShift != afterMod.bmLeftShift) { //LSHIFT CHANGED
    HandleKeyCode( LSHFT, beforeMod.bmLeftShift < afterMod.bmLeftShift );
  }

  if (beforeMod.bmLeftAlt != afterMod.bmLeftAlt) { //LALT CHANGED
    HandleKeyCode( LALT, beforeMod.bmLeftAlt < afterMod.bmLeftAlt );
  }

  if (beforeMod.bmLeftGUI != afterMod.bmLeftGUI) { //LGUI CHANGED
    HandleKeyCode( LGUI, beforeMod.bmLeftGUI < afterMod.bmLeftGUI );
  }

  if (beforeMod.bmRightCtrl != afterMod.bmRightCtrl) { //RCTRL CHANGED
    HandleKeyCode( RCTRL, beforeMod.bmRightCtrl < afterMod.bmRightCtrl );
  }

  if (beforeMod.bmRightShift != afterMod.bmRightShift) { //RSHIFT CHANGED
    HandleKeyCode( RSHFT, beforeMod.bmRightShift < afterMod.bmRightShift );
  }

  if (beforeMod.bmRightAlt != afterMod.bmRightAlt) { //RALT CHANGED
    HandleKeyCode( RALT, beforeMod.bmRightAlt < afterMod.bmRightAlt );
  }

  if (beforeMod.bmRightGUI != afterMod.bmRightGUI) { //RGUI CHANGED
    HandleKeyCode( RGUI, beforeMod.bmRightGUI < afterMod.bmRightGUI );
  }
}

bool active = true;       //if arduino needs to be reprogrammed but keystrokes are getting in the way
//uint8_t lockLeds = 0;     //represents what LEDs should be on
unsigned long timer = 0;
unsigned long debounce[SWITCHPINS];
bool exSwprev[SWITCHPINS];  //keeps track of switch presses
bool exSw[SWITCHPINS];  //keeps track of switch presses
//standard layout:
//uint8_t keyToSend[] = {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_LEFT_ALT, KEY_LEFT_GUI, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_ENTER, KEY_ESC, KEY_BACKSPACE, KEY_TAB, KEY_SPACE, KEY_MINUS, KEY_EQUAL, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_BACKSLASH, 0x00, KEY_SEMICOLON, KEY_QUOTE, KEY_TILDE, KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_CAPS_LOCK, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_PRINT, KEY_SCROLL_LOCK, KEY_PAUSE, KEY_INSERT, KEY_HOME, KEY_PAGE_UP, KEY_DELETE, KEY_END, KEY_PAGE_DOWN, KEY_RIGHT_ARROW, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_UP_ARROW, KEY_NUM_LOCK, KEYPAD_DIVIDE, KEYPAD_MULTIPLY, KEYPAD_SUBTRACT, KEYPAD_ADD, KEYPAD_ENTER, KEYPAD_1, KEYPAD_2, KEYPAD_3, KEYPAD_4, KEYPAD_5, KEYPAD_6, KEYPAD_7, KEYPAD_8, KEYPAD_9, KEYPAD_0, KEYPAD_DOT, 0x00, KEY_APPLICATION, KEY_RIGHT_CTRL, KEY_RIGHT_SHIFT, KEY_RIGHT_ALT, KEY_RIGHT_GUI};
/*
Error with USB Host Shield 2.0 when pressing multiple keys keeps first index pressed until released again.
KEEP THE FIRST INDEX 0x00 TO AVOID THIS ERROR
*/

USB     Usb;
//USBHub     Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);

KbdRptParser Prs;

void setup() {
  Serial.begin( 115200 );
  pinMode(ACTIVEPIN, INPUT_PULLUP);
  for (int i = 0; i < SWITCHPINS; i++)
  {
    exSw[i] = false;
    exSwprev[i] = false;
    debounce[i] = 0;
    pinMode(switchPins[i], INPUT_PULLUP);
  }

  //#if !defined(__MIPSEL__)
  //while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  //#endif
  //Serial.println("Start");

  if (Usb.Init() == -1)
    //Serial.println("OSC did not start.");

    delay( 200 );

  HidKeyboard.SetReportParser(0, &Prs);
  BootKeyboard.begin();
}

void loop() {
  active =  digitalRead(ACTIVEPIN);
  if (!active) //if pin13 is grounded, disable keyboard
  {
    BootKeyboard.end();
    while(true);
  }

  for (int i = 0; i < SWITCHPINS; i++) //iterate through pins
  {
    if ((millis() - debounce[i]) > DBINTERVAL) //ignore in debounce interval
    {
      exSw[i] = !digitalRead(switchPins[i]); //record current state
      debounce[i] = timer; //reset debounce timer
      if (exSw[i] != exSwprev) //if switch state changes
      {
        HandleKeyCode( (SW0 + i), (exSw[i]) ); //press/release
        exSwprev[i] = exSw[i]; //record previous state
      }
    }
  }
  
  Usb.Task();
}
