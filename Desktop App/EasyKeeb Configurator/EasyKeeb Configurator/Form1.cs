using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace EasyKeeb_Configurator
{
    public partial class Form1 : Form
    {
        Dictionary<string, byte> keycodes = new Dictionary<string, byte>();
        Dictionary<string, int> keys = new Dictionary<string, int>();

        Dictionary<string,string>[] keymapStr = new Dictionary<string, string>[]
        {
            new Dictionary<string, string>(),
            new Dictionary<string, string>(),
            new Dictionary<string, string>(),
            new Dictionary<string, string>(),
            new Dictionary<string, string>()
        };

        byte[] keymap = new byte[5 * 117];
        string curBtn = "";
        int curLyr = 0;

        void BuildKeymapUI(Dictionary<string,string> kmap)
        {
            foreach (Button b in pnlKeys.Controls) b.Text = "";
            foreach (KeyValuePair<string, string> p in kmap)
            {
                foreach (Button b in pnlKeys.Controls)
                {
                    if (b.Name == p.Key) b.Text = p.Value;
                }
            }
        }

        void ResetLyr(int layer)
        {
            //Build initial keymap
            using (System.IO.StreamReader reader = new System.IO.StreamReader("DefaultLayout.json"))
            {
                string s = reader.ReadToEnd();
                //clear dictionary
                keymapStr[layer].Clear();

                Dictionary<string, string>[] d = new Dictionary<string, string>[5];
                d = JsonConvert.DeserializeObject<Dictionary<string, string>[]>(s);
                foreach (KeyValuePair<string, string> p in d[layer]) keymapStr[layer][p.Key] = p.Value;
                BuildKeymapUI(keymapStr[layer]);
            }
        }

        void ResetAll()
        {
            //Build initial keymap
            using (System.IO.StreamReader reader = new System.IO.StreamReader("DefaultLayout.json"))
            {
                string s = reader.ReadToEnd();
                //clear dictionaries
                foreach (Dictionary<string, string> d in keymapStr) d.Clear();

                keymapStr = JsonConvert.DeserializeObject<Dictionary<string, string>[]>(s);
                BuildKeymapUI(keymapStr[0]);
            }
        }


        public Form1()
        {
            InitializeComponent();

            //fill keycode dictionary - assigns key strings to their keycodes
            keycodes.Add("(None)", 0);
            keycodes.Add("Left Ctrl", 106);
            keycodes.Add("Left Shift", 1);
            keycodes.Add("Left Alt", 2);
            keycodes.Add("Left Win", 3);
            keycodes.Add("A", 4);
            keycodes.Add("B", 5);
            keycodes.Add("C", 6);
            keycodes.Add("D", 7);
            keycodes.Add("E", 8);
            keycodes.Add("F", 9);
            keycodes.Add("G", 10);
            keycodes.Add("H", 11);
            keycodes.Add("I", 12);
            keycodes.Add("J", 13);
            keycodes.Add("K", 14);
            keycodes.Add("L", 15);
            keycodes.Add("M", 16);
            keycodes.Add("N", 17);
            keycodes.Add("O", 18);
            keycodes.Add("P", 19);
            keycodes.Add("Q", 20);
            keycodes.Add("R", 21);
            keycodes.Add("S", 22);
            keycodes.Add("T", 23);
            keycodes.Add("U", 24);
            keycodes.Add("V", 25);
            keycodes.Add("W", 26);
            keycodes.Add("X", 27);
            keycodes.Add("Y", 28);
            keycodes.Add("Z", 29);
            keycodes.Add("1", 30);
            keycodes.Add("2", 31);
            keycodes.Add("3", 32);
            keycodes.Add("4", 33);
            keycodes.Add("5", 34);
            keycodes.Add("6", 35);
            keycodes.Add("7", 36);
            keycodes.Add("8", 37);
            keycodes.Add("9", 38);
            keycodes.Add("0", 39);
            keycodes.Add("Enter", 40);
            keycodes.Add("Esc", 41);
            keycodes.Add("Backspace", 42);
            keycodes.Add("Tab", 43);
            keycodes.Add("Space", 44);
            keycodes.Add("-", 45);
            keycodes.Add("=", 46);
            keycodes.Add("[", 47);
            keycodes.Add("]", 48);
            keycodes.Add("\\", 49);
            //keycodes.Add("NON_US_NUM", 50);   NON_US_NUM key is not applicable and is only here for reference
            keycodes.Add(";", 51);
            keycodes.Add("'", 52);
            keycodes.Add("~", 53);
            keycodes.Add(",", 54);
            keycodes.Add(".", 55);
            keycodes.Add("/", 56);
            keycodes.Add("Caps Lock", 57);
            keycodes.Add("F1", 58);
            keycodes.Add("F2", 59);
            keycodes.Add("F3", 60);
            keycodes.Add("F4", 61);
            keycodes.Add("F5", 62);
            keycodes.Add("F6", 63);
            keycodes.Add("F7", 64);
            keycodes.Add("F8", 65);
            keycodes.Add("F9", 66);
            keycodes.Add("F10", 67);
            keycodes.Add("F11", 68);
            keycodes.Add("F12", 69);
            keycodes.Add("PrntSc", 70);
            keycodes.Add("Scroll Lock", 71);
            keycodes.Add("Pause Break", 72);
            keycodes.Add("Insert", 73);
            keycodes.Add("Home", 74);
            keycodes.Add("Page Up", 75);
            keycodes.Add("Delete", 76);
            keycodes.Add("End", 77);
            keycodes.Add("Page Down", 78);
            keycodes.Add("→", 79);
            keycodes.Add("←", 80);
            keycodes.Add("↓", 81);
            keycodes.Add("↑", 82);
            keycodes.Add("Num Lock", 83);
            keycodes.Add("Num /", 84);
            keycodes.Add("Num *", 85);
            keycodes.Add("Num -", 86);
            keycodes.Add("Num +", 87);
            keycodes.Add("Num Enter", 88);
            keycodes.Add("Num 1", 89);
            keycodes.Add("Num 2", 90);
            keycodes.Add("Num 3", 91);
            keycodes.Add("Num 4", 92);
            keycodes.Add("Num 5", 93);
            keycodes.Add("Num 6", 94);
            keycodes.Add("Num 7", 95);
            keycodes.Add("Num 8", 96);
            keycodes.Add("Num 9", 97);
            keycodes.Add("Num 0", 98);
            keycodes.Add("Num .", 99);
            //keycodes.Add("NON_US", 100);  //NON_US key is not applicable and is only here for reference
            keycodes.Add("Menu", 101);
            keycodes.Add("Right Ctrl", 102);
            keycodes.Add("Right Shift", 103);
            keycodes.Add("Right Alt", 104);
            keycodes.Add("Right Win", 105);
            keycodes.Add("Layer 1", 200);
            keycodes.Add("Layer 2", 201);
            keycodes.Add("Layer 3", 202);
            keycodes.Add("Layer 4", 203);
            keycodes.Add("Layer 5", 204);
            keycodes.Add("Toggle Layer 1", 210);
            keycodes.Add("Toggle Layer 2", 211);
            keycodes.Add("Toggle Layer 3", 212);
            keycodes.Add("Toggle Layer 4", 213);
            keycodes.Add("Toggle Layer 5", 214);

            //fill keyIndex dictionary - assign button names with indices of final keymap
            keys.Add("btnLCtrl",    106);
            keys.Add("btnLSh",      1);
            keys.Add("btnLAlt",     2);
            keys.Add("btnLGUI",     3);
            keys.Add("btnA",        4);
            keys.Add("btnB",        5);
            keys.Add("btnC",        6);
            keys.Add("btnD",        7);
            keys.Add("btnE",        8);
            keys.Add("btnF",        9);
            keys.Add("btnG",        10);
            keys.Add("btnH",        11);
            keys.Add("btnI",        12);
            keys.Add("btnJ",        13);
            keys.Add("btnK",        14);
            keys.Add("btnL",        15);
            keys.Add("btnM",        16);
            keys.Add("btnN",        17);
            keys.Add("btnO",        18);
            keys.Add("btnP",        19);
            keys.Add("btnQ",        20);
            keys.Add("btnR",        21);
            keys.Add("btnS",        22);
            keys.Add("btnT",        23);
            keys.Add("btnU",        24);
            keys.Add("btnV",        25);
            keys.Add("btnW",        26);
            keys.Add("btnX",        27);
            keys.Add("btnY",        28);
            keys.Add("btnZ",        29);
            keys.Add("btn1",        30);
            keys.Add("btn2",        31);
            keys.Add("btn3",        32);
            keys.Add("btn4",        33);
            keys.Add("btn5",        34);
            keys.Add("btn6",        35);
            keys.Add("btn7",        36);
            keys.Add("btn8",        37);
            keys.Add("btn9",        38);
            keys.Add("btn0",        39);
            keys.Add("btnEnt",      40);
            keys.Add("btnEsc",      41);
            keys.Add("btnBsp",      42);
            keys.Add("btnTab",      43);
            keys.Add("btnSpc",      44);
            keys.Add("btnMin",      45);
            keys.Add("btnEql",      46);
            keys.Add("btnLbr",      47);
            keys.Add("btnRbr",      48);
            keys.Add("btnBsl",      49);
            keys.Add("btnScl",      51);
            keys.Add("btnQuot",     52);
            keys.Add("btnGrv",      53);
            keys.Add("btnCom",      54);
            keys.Add("btnPer",      55);
            keys.Add("btnSlsh",     56);
            keys.Add("btnCap",      57);
            keys.Add("btnF1",       58);
            keys.Add("btnF2",       59);
            keys.Add("btnF3",       60);
            keys.Add("btnF4",       61);
            keys.Add("btnF5",       62);
            keys.Add("btnF6",       63);
            keys.Add("btnF7",       64);
            keys.Add("btnF8",       65);
            keys.Add("btnF9",       66);
            keys.Add("btnF10",      67);
            keys.Add("btnF11",      68);
            keys.Add("btnF12",      69);
            keys.Add("btnPrnt",     70);
            keys.Add("btnScrLk",    71);
            keys.Add("btnPause",    72);
            keys.Add("btnIns",      73);
            keys.Add("btnHm",       74);
            keys.Add("btnPgUp",     75);
            keys.Add("btnDel",      76);
            keys.Add("btnEnd",      77);
            keys.Add("btnPgDn",     78);
            keys.Add("btnRight",    79);
            keys.Add("btnLeft",     80);
            keys.Add("btnDn",       81);
            keys.Add("btnUp",       82);
            keys.Add("btnNumLk",    83);
            keys.Add("btnNumSlsh",  84);
            keys.Add("btnNumStr",   85);
            keys.Add("btnNumMin",   86);
            keys.Add("btnNumPlus",  87);
            keys.Add("btnNumEnt",   88);
            keys.Add("btnNum1",     89);
            keys.Add("btnNum2",     90);
            keys.Add("btnNum3",     91);
            keys.Add("btnNum4",     92);
            keys.Add("btnNum5",     93);
            keys.Add("btnNum6",     94);
            keys.Add("btnNum7",     95);
            keys.Add("btnNum8",     96);
            keys.Add("btnNum9",     97);
            keys.Add("btnNum0",     98);
            keys.Add("btnNumPer",   99);
            keys.Add("btnMenu",     101);
            keys.Add("btnRCtrl",    102);
            keys.Add("btnRSh",      103);
            keys.Add("btnRAlt",     104);
            keys.Add("btnRGUI",     105);
            keys.Add("btnEx0",      107);
            keys.Add("btnEx1",      108);
            keys.Add("btnEx2",      109);
            keys.Add("btnEx3",      110);
            keys.Add("btnEx4",      111);
            keys.Add("btnEx5",      112);
            keys.Add("btnEx6",      113);
            keys.Add("btnEx7",      114);
            keys.Add("btnEx8",      115);
            keys.Add("btnEx9",      116);

            //fill keys dropdown
            cboKey.DropDownStyle = ComboBoxStyle.DropDownList;
            cboKey.Items.Add("(None)");
            foreach(KeyValuePair<string,byte> p in keycodes) cboKey.Items.Add(p.Key);

            //fill layers dropdown
            cboLayer.DropDownStyle = ComboBoxStyle.DropDownList;
            for (int i = 0; i < 5; ++i) cboLayer.Items.Add((i+1).ToString());
            cboLayer.SelectedIndex = 0;

            foreach (Button b in pnlKeys.Controls)
            {
                b.MouseClick += new MouseEventHandler(
                    delegate (object sender, MouseEventArgs e)
                    {
                        Button btn = (Button)sender;
                        curBtn = btn.Name;
                        if (!cboKey.Enabled) cboKey.Enabled = true;
                        cboKey.SelectedIndex = cboKey.FindStringExact(btn.Text);
                        cboKey.Focus();
                    });
            }

            ResetAll();
            btnEsc.Select();
        }

        void ClearLayer(int layer)
        {
            keymapStr[layer].Clear();
            foreach(Button b in pnlKeys.Controls)
            {
                b.Text = "";
                keymapStr[layer].Add(b.Name, b.Text);
            }
        }

        void ClearAll()
        {
            foreach (Dictionary<string, string> d in keymapStr)
            {
                d.Clear();

                foreach (Button b in pnlKeys.Controls)
                {
                    b.Text = "";
                    d.Add(b.Name, b.Text);
                }
            }
        }

        //fill dictionary for current layer
        void GetLayerMap(int layer)
        {
            keymapStr[layer].Clear();
            foreach (Button b in pnlKeys.Controls)
            {
                keymapStr[layer].Add(b.Name, b.Text);
            }
        }

        void Export()
        {
            GetLayerMap(curLyr);
            txtExport.Text = JsonConvert.SerializeObject(keymapStr);
        }

        void ExportFile()
        {
            Export();
            using (SaveFileDialog saveFileDialog = new SaveFileDialog())
            {
                saveFileDialog.Filter = "txt files (*.txt)|*.txt|JSON files (*.json)|*.json|All files (*.*)|*.*";
                saveFileDialog.FilterIndex = 2;
                saveFileDialog.RestoreDirectory = true;

                if (saveFileDialog.ShowDialog() == DialogResult.OK)
                {
                    using (System.IO.StreamWriter writer = new System.IO.StreamWriter(System.IO.File.Create(saveFileDialog.FileName)))
                    {
                        writer.Write(txtExport.Text);
                    }
                }
            }
        }

        void Import()
        {
            //clear dictionaries
            foreach (Dictionary<string,string> d in keymapStr) { d.Clear(); }
            keymapStr = JsonConvert.DeserializeObject<Dictionary<string, string>[]>(txtImport.Text);
            BuildKeymapUI(keymapStr[0]);
            cboKey.Enabled = false;
        }

        void ImportFile()
        {
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.Filter = "txt files (*.txt)|*.txt|JSON files (*.json)|*.json|All files (*.*)|*.*";
                openFileDialog.FilterIndex = 2;
                openFileDialog.RestoreDirectory = true;

                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    var fileStream = openFileDialog.OpenFile();

                    using (System.IO.StreamReader reader = new System.IO.StreamReader(fileStream))
                    {
                        txtImport.Text = reader.ReadToEnd();
                    }
                }
            }
        }

        private void cboKey_SelectionChangeCommitted(object sender, EventArgs e)
        {
            foreach (Button b in pnlKeys.Controls)
            {
                if (b.Name == curBtn) b.Text = cboKey.Text;
            }
        }

        private void txtImport_TextChanged(object sender, EventArgs e)
        {
            btnImport.Enabled = (txtImport.Text.Length > 0);
        }

        private void btnImport_Click(object sender, EventArgs e)
        {
            Import();
        }

        private void btnImportFile_Click(object sender, EventArgs e)
        {
            ImportFile();
            lblImportInstructions.Visible = (txtImport.Text.Length > 0);
        }

        private void btnExport_Click(object sender, EventArgs e)
        {
            Export();
            txtExport.SelectAll();
            txtExport.Focus();
        }

        private void btnExportFile_Click(object sender, EventArgs e)
        {
            ExportFile();
        }

        private void cboLayer_SelectedIndexChanged(object sender, EventArgs e)
        {
            cboKey.Enabled = false;
            cboKey.SelectedIndex = -1;
            GetLayerMap(curLyr);
            curLyr = cboLayer.SelectedIndex;
            BuildKeymapUI(keymapStr[curLyr]);
        }

        private void btnRst_Click(object sender, EventArgs e)
        {
            ResetAll();
        }

        private void btnClr_Click(object sender, EventArgs e)
        {
            ClearAll();
        }

        private void btnRstLyr_Click(object sender, EventArgs e)
        {
            ResetLyr(curLyr);
        }

        private void btnClrLyr_Click(object sender, EventArgs e)
        {
            ClearLayer(curLyr);
        }

        private void btnLoad_Click(object sender, EventArgs e)
        {
            GetLayerMap(curLyr);
            //set every value in keymap[] to 0
            for (int i = 0; i < (5 * 117); i++) keymap[i] = 0;
            //assign values to keymap array
            for (int i = 0; i < 5; i++)
            {
                foreach (KeyValuePair<string, string> p in keymapStr[i])
                {
                    keymap[keys[p.Key] + (i * 117)] = keycodes[p.Value];
                }
            }

            Form2 frm2 = new Form2(keymap);
            frm2.ShowDialog();
        }
    }
}