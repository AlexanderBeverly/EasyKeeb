namespace EasyKeeb_Configurator
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.lblWait = new System.Windows.Forms.Label();
            this.cboCOM = new System.Windows.Forms.ComboBox();
            this.btnCOM = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.btnLoad = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // lblWait
            // 
            this.lblWait.AutoSize = true;
            this.lblWait.Location = new System.Drawing.Point(63, 18);
            this.lblWait.Name = "lblWait";
            this.lblWait.Size = new System.Drawing.Size(166, 13);
            this.lblWait.TabIndex = 0;
            this.lblWait.Text = "Loading to Device. Please Wait...";
            this.lblWait.Visible = false;
            // 
            // cboCOM
            // 
            this.cboCOM.Enabled = false;
            this.cboCOM.FormattingEnabled = true;
            this.cboCOM.Location = new System.Drawing.Point(12, 44);
            this.cboCOM.Name = "cboCOM";
            this.cboCOM.Size = new System.Drawing.Size(69, 21);
            this.cboCOM.TabIndex = 1;
            this.cboCOM.SelectedIndexChanged += new System.EventHandler(this.cboCOM_SelectedIndexChanged);
            // 
            // btnCOM
            // 
            this.btnCOM.Location = new System.Drawing.Point(87, 44);
            this.btnCOM.Name = "btnCOM";
            this.btnCOM.Size = new System.Drawing.Size(158, 21);
            this.btnCOM.TabIndex = 2;
            this.btnCOM.Text = "Scan COM Ports";
            this.btnCOM.UseVisualStyleBackColor = true;
            this.btnCOM.Click += new System.EventHandler(this.btnCOM_Click);
            // 
            // serialPort1
            // 
            this.serialPort1.BaudRate = 115200;
            // 
            // btnLoad
            // 
            this.btnLoad.Enabled = false;
            this.btnLoad.Location = new System.Drawing.Point(54, 71);
            this.btnLoad.Name = "btnLoad";
            this.btnLoad.Size = new System.Drawing.Size(129, 76);
            this.btnLoad.TabIndex = 3;
            this.btnLoad.Text = "Load to Device";
            this.btnLoad.UseVisualStyleBackColor = true;
            this.btnLoad.Click += new System.EventHandler(this.btnLoad_Click);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(257, 172);
            this.Controls.Add(this.btnLoad);
            this.Controls.Add(this.btnCOM);
            this.Controls.Add(this.cboCOM);
            this.Controls.Add(this.lblWait);
            this.Name = "Form2";
            this.Text = "Loading Keymap...";
            this.Load += new System.EventHandler(this.Form2_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblWait;
        private System.Windows.Forms.ComboBox cboCOM;
        private System.Windows.Forms.Button btnCOM;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Button btnLoad;
    }
}