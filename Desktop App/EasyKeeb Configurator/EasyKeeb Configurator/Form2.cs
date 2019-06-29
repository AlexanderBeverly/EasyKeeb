using System;
using System.IO.Ports;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EasyKeeb_Configurator
{
    public partial class Form2 : Form
    {
        byte[] keymap = new byte[5 * 117];
        public Form2(byte[] km)
        {
            InitializeComponent();
            keymap = km;
        }

        void LoadToArduino()
        {
            //hide controls
            foreach (Control c in this.Controls)
            {
                c.Visible = false;
            }
            //show wait label
            lblWait.Visible = true;
            //counter for checksum
            int sum = 0;
            foreach (byte b in keymap) sum += b;
            //open port
            serialPort1.Open();
            //write to arduino
            serialPort1.Write(keymap, 0, (5 * 117));
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            cboCOM.Enabled = false;
            btnLoad.Enabled = false;
        }

        private void btnCOM_Click(object sender, EventArgs e)
        {
            cboCOM.Enabled = false;
            btnLoad.Enabled = false;
            cboCOM.Items.Clear();
            //get available serial ports
            string[] ports = SerialPort.GetPortNames();
            foreach (string port in ports)
            {
                cboCOM.Items.Add(port);
            }
            //enable controls if serial ports are available
            if (cboCOM.Items.Count > 0)
            {
                cboCOM.Enabled = true;
                btnLoad.Enabled = true;
                cboCOM.SelectedIndex = 0;
            }

        }

        private void cboCOM_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cboCOM.Text != "") serialPort1.PortName = cboCOM.Text;
        }

        private void btnLoad_Click(object sender, EventArgs e)
        {
            LoadToArduino();
        }
    }
}
