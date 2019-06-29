//USB Host Shield 2.0 example HIDBootKbd modified by Alex Beverly
#include <Arduino.h>
#include <HID-Project.h>
#include <HID-Settings.h>
#include <hidboot.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
#include <EEPROM.h>

#define ACTIVEPIN 13
#define OEMCODES 0x6B
#define SWITCHPINS 10
#define MAXLAYERS 5

//define modifier indexes
#define LCTRL 0x6A  //moved from 0x00 to avoid USB Host Shield 2.0 error
#define LSHFT 0x01
#define LALT 0x02
#define LGUI 0x03
#define RCTRL 0x66
#define RSHFT 0x67
#define RALT 0x68
#define RGUI 0x69

//define external switch indexes (0x6B + i in for loop)
#define SW0 0x6B
#define SW1 0x6C
#define SW2 0x6D
#define SW3 0x6E
#define SW4 0x6F
#define SW5 0x70
#define SW6 0x71
#define SW7 0x72
#define SW8 0x73
#define SW9 0x74

//define layer switching codes (arbitrary codes by me for handling)
#define LAYER1 200
#define LAYER2 201
#define LAYER3 202
#define LAYER4 203
#define LAYER5 204
//define toggle layers
#define TLAYER1 210
#define TLAYER2 211
#define TLAYER3 212
#define TLAYER4 213
#define TLAYER5 214
//define set default
#define LAYERD 215

uint8_t keyToSend[MAXLAYERS][OEMCODES + SWITCHPINS] = {
  //0
  {KEY_RESERVED, KEY_LEFT_SHIFT, KEY_LEFT_ALT, KEY_LEFT_GUI, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_ENTER, KEY_ESC, KEY_BACKSPACE, KEY_TAB, KEY_SPACE, KEY_MINUS, KEY_EQUAL, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_BACKSLASH, KEY_NON_US_NUM, KEY_SEMICOLON, KEY_QUOTE, KEY_TILDE, KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_CAPS_LOCK, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_PRINT, KEY_SCROLL_LOCK, KEY_PAUSE, KEY_INSERT, KEY_HOME, KEY_PAGE_UP, KEY_DELETE, KEY_END, KEY_PAGE_DOWN, KEY_RIGHT_ARROW, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_UP_ARROW, KEY_NUM_LOCK, KEYPAD_DIVIDE, KEYPAD_MULTIPLY, KEYPAD_SUBTRACT, KEYPAD_ADD, KEYPAD_ENTER, KEYPAD_1, KEYPAD_2, KEYPAD_3, KEYPAD_4, KEYPAD_5, KEYPAD_6, KEYPAD_7, KEYPAD_8, KEYPAD_9, KEYPAD_0, KEYPAD_DOT, KEY_NON_US, KEY_APPLICATION, KEY_RIGHT_CTRL, KEY_RIGHT_SHIFT, KEY_RIGHT_ALT, KEY_RIGHT_GUI, KEY_LEFT_CTRL, KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9},
  //1
  {KEY_RESERVED, KEY_LEFT_SHIFT, KEY_LEFT_ALT, KEY_LEFT_GUI, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_ENTER, KEY_ESC, KEY_BACKSPACE, KEY_TAB, KEY_SPACE, KEY_MINUS, KEY_EQUAL, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_BACKSLASH, KEY_NON_US_NUM, KEY_SEMICOLON, KEY_QUOTE, KEY_TILDE, KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_CAPS_LOCK, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_PRINT, KEY_SCROLL_LOCK, KEY_PAUSE, KEY_INSERT, KEY_HOME, KEY_PAGE_UP, KEY_DELETE, KEY_END, KEY_PAGE_DOWN, KEY_RIGHT_ARROW, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_UP_ARROW, KEY_NUM_LOCK, KEYPAD_DIVIDE, KEYPAD_MULTIPLY, KEYPAD_SUBTRACT, KEYPAD_ADD, KEYPAD_ENTER, KEYPAD_1, KEYPAD_2, KEYPAD_3, KEYPAD_4, KEYPAD_5, KEYPAD_6, KEYPAD_7, KEYPAD_8, KEYPAD_9, KEYPAD_0, KEYPAD_DOT, KEY_NON_US, KEY_APPLICATION, KEY_RIGHT_CTRL, KEY_RIGHT_SHIFT, KEY_RIGHT_ALT, KEY_RIGHT_GUI, KEY_LEFT_CTRL, KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9},
  //2
  {KEY_RESERVED, KEY_LEFT_SHIFT, KEY_LEFT_ALT, KEY_LEFT_GUI, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_ENTER, KEY_ESC, KEY_BACKSPACE, KEY_TAB, KEY_SPACE, KEY_MINUS, KEY_EQUAL, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_BACKSLASH, KEY_NON_US_NUM, KEY_SEMICOLON, KEY_QUOTE, KEY_TILDE, KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_CAPS_LOCK, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_PRINT, KEY_SCROLL_LOCK, KEY_PAUSE, KEY_INSERT, KEY_HOME, KEY_PAGE_UP, KEY_DELETE, KEY_END, KEY_PAGE_DOWN, KEY_RIGHT_ARROW, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_UP_ARROW, KEY_NUM_LOCK, KEYPAD_DIVIDE, KEYPAD_MULTIPLY, KEYPAD_SUBTRACT, KEYPAD_ADD, KEYPAD_ENTER, KEYPAD_1, KEYPAD_2, KEYPAD_3, KEYPAD_4, KEYPAD_5, KEYPAD_6, KEYPAD_7, KEYPAD_8, KEYPAD_9, KEYPAD_0, KEYPAD_DOT, KEY_NON_US, KEY_APPLICATION, KEY_RIGHT_CTRL, KEY_RIGHT_SHIFT, KEY_RIGHT_ALT, KEY_RIGHT_GUI, KEY_LEFT_CTRL, KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9},
  //3
  {KEY_RESERVED, KEY_LEFT_SHIFT, KEY_LEFT_ALT, KEY_LEFT_GUI, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_ENTER, KEY_ESC, KEY_BACKSPACE, KEY_TAB, KEY_SPACE, KEY_MINUS, KEY_EQUAL, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_BACKSLASH, KEY_NON_US_NUM, KEY_SEMICOLON, KEY_QUOTE, KEY_TILDE, KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_CAPS_LOCK, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_PRINT, KEY_SCROLL_LOCK, KEY_PAUSE, KEY_INSERT, KEY_HOME, KEY_PAGE_UP, KEY_DELETE, KEY_END, KEY_PAGE_DOWN, KEY_RIGHT_ARROW, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_UP_ARROW, KEY_NUM_LOCK, KEYPAD_DIVIDE, KEYPAD_MULTIPLY, KEYPAD_SUBTRACT, KEYPAD_ADD, KEYPAD_ENTER, KEYPAD_1, KEYPAD_2, KEYPAD_3, KEYPAD_4, KEYPAD_5, KEYPAD_6, KEYPAD_7, KEYPAD_8, KEYPAD_9, KEYPAD_0, KEYPAD_DOT, KEY_NON_US, KEY_APPLICATION, KEY_RIGHT_CTRL, KEY_RIGHT_SHIFT, KEY_RIGHT_ALT, KEY_RIGHT_GUI, KEY_LEFT_CTRL, KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9},
  //4
  {KEY_RESERVED, KEY_LEFT_SHIFT, KEY_LEFT_ALT, KEY_LEFT_GUI, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_ENTER, KEY_ESC, KEY_BACKSPACE, KEY_TAB, KEY_SPACE, KEY_MINUS, KEY_EQUAL, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_BACKSLASH, KEY_NON_US_NUM, KEY_SEMICOLON, KEY_QUOTE, KEY_TILDE, KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_CAPS_LOCK, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_PRINT, KEY_SCROLL_LOCK, KEY_PAUSE, KEY_INSERT, KEY_HOME, KEY_PAGE_UP, KEY_DELETE, KEY_END, KEY_PAGE_DOWN, KEY_RIGHT_ARROW, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_UP_ARROW, KEY_NUM_LOCK, KEYPAD_DIVIDE, KEYPAD_MULTIPLY, KEYPAD_SUBTRACT, KEYPAD_ADD, KEYPAD_ENTER, KEYPAD_1, KEYPAD_2, KEYPAD_3, KEYPAD_4, KEYPAD_5, KEYPAD_6, KEYPAD_7, KEYPAD_8, KEYPAD_9, KEYPAD_0, KEYPAD_DOT, KEY_NON_US, KEY_APPLICATION, KEY_RIGHT_CTRL, KEY_RIGHT_SHIFT, KEY_RIGHT_ALT, KEY_RIGHT_GUI, KEY_LEFT_CTRL, KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9},
};

void ReadEEPROM()
{
  for (int i = 0; i < EEMPROM.length(); i++) keyToSend[ i / (OEMCODES + SWITCHPINS) ][ i % (OEMCODES + SWITCHPINS) ] = EEPROM.Read(i);
}

void WriteEEPROM()
{
  //TODO: read serial from the PC and assign to keyToSend[][]
  for (int i = 0; i < EEPROM.length(); i++) EEPROM.Write(i, keyToSend[ i / (OEMCODES + SWITCHPINS) ][ i % (OEMCODES + SWITCHPINS) ]);
}