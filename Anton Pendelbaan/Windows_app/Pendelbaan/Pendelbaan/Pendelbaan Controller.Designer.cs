namespace Pendelbaan
{
    partial class Form1
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.communicatieToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.comPoortToolStripMenuItem = new System.Windows.Forms.ToolStripComboBox();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.maakVerbindingToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.RcRb = new System.Windows.Forms.TextBox();
            this.RcRf = new System.Windows.Forms.TextBox();
            this.RcLf = new System.Windows.Forms.TextBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.RcLb = new System.Windows.Forms.TextBox();
            this.SerialRead = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.RcLmu = new System.Windows.Forms.TextBox();
            this.RcLmd = new System.Windows.Forms.TextBox();
            this.RcRmd = new System.Windows.Forms.TextBox();
            this.RcRmu = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.JunctionLeftBtn = new System.Windows.Forms.Button();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.JunctionRightBtn = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.ManPwm = new System.Windows.Forms.HScrollBar();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.AutoSize = false;
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.communicatieToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(8, 2, 0, 2);
            this.menuStrip1.Size = new System.Drawing.Size(1006, 28);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.AutoSize = false;
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(44, 24);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(181, 26);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // communicatieToolStripMenuItem
            // 
            this.communicatieToolStripMenuItem.AutoSize = false;
            this.communicatieToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.comPoortToolStripMenuItem,
            this.toolStripSeparator1,
            this.maakVerbindingToolStripMenuItem});
            this.communicatieToolStripMenuItem.Name = "communicatieToolStripMenuItem";
            this.communicatieToolStripMenuItem.Size = new System.Drawing.Size(117, 24);
            this.communicatieToolStripMenuItem.Text = "Communicatie";
            // 
            // comPoortToolStripMenuItem
            // 
            this.comPoortToolStripMenuItem.Name = "comPoortToolStripMenuItem";
            this.comPoortToolStripMenuItem.Size = new System.Drawing.Size(152, 28);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(215, 6);
            // 
            // maakVerbindingToolStripMenuItem
            // 
            this.maakVerbindingToolStripMenuItem.Name = "maakVerbindingToolStripMenuItem";
            this.maakVerbindingToolStripMenuItem.Size = new System.Drawing.Size(218, 26);
            this.maakVerbindingToolStripMenuItem.Text = "Maak Verbinding";
            this.maakVerbindingToolStripMenuItem.Click += new System.EventHandler(this.maakVerbindingToolStripMenuItem_Click);
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(1211, 1);
            this.progressBar1.Margin = new System.Windows.Forms.Padding(4);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(133, 28);
            this.progressBar1.TabIndex = 3;
            // 
            // RcRb
            // 
            this.RcRb.Enabled = false;
            this.RcRb.Location = new System.Drawing.Point(1006, 437);
            this.RcRb.Margin = new System.Windows.Forms.Padding(4);
            this.RcRb.Name = "RcRb";
            this.RcRb.Size = new System.Drawing.Size(11, 22);
            this.RcRb.TabIndex = 4;
            // 
            // RcRf
            // 
            this.RcRf.Enabled = false;
            this.RcRf.Location = new System.Drawing.Point(986, 431);
            this.RcRf.Margin = new System.Windows.Forms.Padding(4);
            this.RcRf.Name = "RcRf";
            this.RcRf.Size = new System.Drawing.Size(11, 22);
            this.RcRf.TabIndex = 4;
            // 
            // RcLf
            // 
            this.RcLf.Enabled = false;
            this.RcLf.Location = new System.Drawing.Point(324, 487);
            this.RcLf.Margin = new System.Windows.Forms.Padding(4);
            this.RcLf.Name = "RcLf";
            this.RcLf.Size = new System.Drawing.Size(11, 22);
            this.RcLf.TabIndex = 4;
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox1.ErrorImage = null;
            this.pictureBox1.Image = global::Pendelbaan.Properties.Resources.tandrad_str_str;
            this.pictureBox1.InitialImage = null;
            this.pictureBox1.Location = new System.Drawing.Point(16, 33);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(4);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(977, 600);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 5;
            this.pictureBox1.TabStop = false;
            // 
            // RcLb
            // 
            this.RcLb.Enabled = false;
            this.RcLb.Location = new System.Drawing.Point(304, 486);
            this.RcLb.Margin = new System.Windows.Forms.Padding(4);
            this.RcLb.Name = "RcLb";
            this.RcLb.Size = new System.Drawing.Size(11, 22);
            this.RcLb.TabIndex = 4;
            // 
            // SerialRead
            // 
            this.SerialRead.Location = new System.Drawing.Point(1190, 789);
            this.SerialRead.Margin = new System.Windows.Forms.Padding(4);
            this.SerialRead.Multiline = true;
            this.SerialRead.Name = "SerialRead";
            this.SerialRead.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.SerialRead.Size = new System.Drawing.Size(156, 132);
            this.SerialRead.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(55, 566);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(86, 29);
            this.label1.TabIndex = 6;
            this.label1.Text = "Boven";
            // 
            // label2
            // 
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(192, 244);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(118, 29);
            this.label2.TabIndex = 6;
            this.label2.Text = "Beneden";
            // 
            // label3
            // 
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(1125, 244);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(118, 29);
            this.label3.TabIndex = 6;
            this.label3.Text = "Beneden";
            // 
            // label4
            // 
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(1195, 566);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(86, 29);
            this.label4.TabIndex = 6;
            this.label4.Text = "Boven";
            // 
            // RcLmu
            // 
            this.RcLmu.Enabled = false;
            this.RcLmu.Location = new System.Drawing.Point(20, 476);
            this.RcLmu.Margin = new System.Windows.Forms.Padding(4);
            this.RcLmu.Name = "RcLmu";
            this.RcLmu.Size = new System.Drawing.Size(11, 22);
            this.RcLmu.TabIndex = 4;
            // 
            // RcLmd
            // 
            this.RcLmd.Enabled = false;
            this.RcLmd.Location = new System.Drawing.Point(172, 188);
            this.RcLmd.Margin = new System.Windows.Forms.Padding(4);
            this.RcLmd.Name = "RcLmd";
            this.RcLmd.Size = new System.Drawing.Size(11, 22);
            this.RcLmd.TabIndex = 4;
            // 
            // RcRmd
            // 
            this.RcRmd.Enabled = false;
            this.RcRmd.Location = new System.Drawing.Point(1085, 188);
            this.RcRmd.Margin = new System.Windows.Forms.Padding(4);
            this.RcRmd.Name = "RcRmd";
            this.RcRmd.Size = new System.Drawing.Size(11, 22);
            this.RcRmd.TabIndex = 4;
            // 
            // RcRmu
            // 
            this.RcRmu.Enabled = false;
            this.RcRmu.Location = new System.Drawing.Point(1295, 518);
            this.RcRmu.Margin = new System.Windows.Forms.Padding(4);
            this.RcRmu.Name = "RcRmu";
            this.RcRmu.Size = new System.Drawing.Size(11, 22);
            this.RcRmu.TabIndex = 4;
            // 
            // label6
            // 
            this.label6.Location = new System.Drawing.Point(204, 491);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(88, 17);
            this.label6.TabIndex = 6;
            this.label6.Text = "Reedcontact";
            // 
            // label7
            // 
            this.label7.Location = new System.Drawing.Point(39, 480);
            this.label7.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(88, 17);
            this.label7.TabIndex = 6;
            this.label7.Text = "Reedcontact";
            // 
            // label8
            // 
            this.label8.Location = new System.Drawing.Point(192, 192);
            this.label8.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(88, 17);
            this.label8.TabIndex = 6;
            this.label8.Text = "Reedcontact";
            // 
            // label9
            // 
            this.label9.Location = new System.Drawing.Point(1105, 192);
            this.label9.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(88, 17);
            this.label9.TabIndex = 6;
            this.label9.Text = "Reedcontact";
            // 
            // label10
            // 
            this.label10.Location = new System.Drawing.Point(1026, 441);
            this.label10.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(88, 17);
            this.label10.TabIndex = 6;
            this.label10.Text = "Reedcontact";
            // 
            // label11
            // 
            this.label11.Location = new System.Drawing.Point(886, 431);
            this.label11.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(88, 17);
            this.label11.TabIndex = 6;
            this.label11.Text = "Reedcontact";
            // 
            // label12
            // 
            this.label12.Location = new System.Drawing.Point(1191, 522);
            this.label12.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(88, 17);
            this.label12.TabIndex = 6;
            this.label12.Text = "Reedcontact";
            // 
            // JunctionLeftBtn
            // 
            this.JunctionLeftBtn.Location = new System.Drawing.Point(333, 658);
            this.JunctionLeftBtn.Margin = new System.Windows.Forms.Padding(4);
            this.JunctionLeftBtn.Name = "JunctionLeftBtn";
            this.JunctionLeftBtn.Size = new System.Drawing.Size(100, 28);
            this.JunctionLeftBtn.TabIndex = 7;
            this.JunctionLeftBtn.Text = "Rechtdoor";
            this.JunctionLeftBtn.UseVisualStyleBackColor = true;
            this.JunctionLeftBtn.Click += new System.EventHandler(this.JunctionLeftBtn_Click);
            // 
            // label13
            // 
            this.label13.Location = new System.Drawing.Point(345, 639);
            this.label13.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(86, 17);
            this.label13.TabIndex = 8;
            this.label13.Text = "Wissel Links";
            // 
            // label14
            // 
            this.label14.Location = new System.Drawing.Point(847, 639);
            this.label14.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(97, 17);
            this.label14.TabIndex = 8;
            this.label14.Text = "Wissel Rechts";
            // 
            // JunctionRightBtn
            // 
            this.JunctionRightBtn.Location = new System.Drawing.Point(847, 658);
            this.JunctionRightBtn.Margin = new System.Windows.Forms.Padding(4);
            this.JunctionRightBtn.Name = "JunctionRightBtn";
            this.JunctionRightBtn.Size = new System.Drawing.Size(100, 28);
            this.JunctionRightBtn.TabIndex = 7;
            this.JunctionRightBtn.Text = "Rechtdoor";
            this.JunctionRightBtn.UseVisualStyleBackColor = true;
            this.JunctionRightBtn.Click += new System.EventHandler(this.JunctionRightBtn_Click);
            // 
            // label5
            // 
            this.label5.Location = new System.Drawing.Point(344, 492);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(88, 17);
            this.label5.TabIndex = 8;
            this.label5.Text = "Reedcontact";
            // 
            // ManPwm
            // 
            this.ManPwm.Location = new System.Drawing.Point(507, 658);
            this.ManPwm.Name = "ManPwm";
            this.ManPwm.Size = new System.Drawing.Size(275, 17);
            this.ManPwm.TabIndex = 9;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(1006, 721);
            this.Controls.Add(this.ManPwm);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.JunctionRightBtn);
            this.Controls.Add(this.JunctionLeftBtn);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.RcLmu);
            this.Controls.Add(this.RcRmu);
            this.Controls.Add(this.RcRmd);
            this.Controls.Add(this.RcLmd);
            this.Controls.Add(this.RcLb);
            this.Controls.Add(this.RcLf);
            this.Controls.Add(this.RcRf);
            this.Controls.Add(this.RcRb);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.SerialRead);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.pictureBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Pendelbaan Controller";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem communicatieToolStripMenuItem;
        private System.Windows.Forms.ToolStripComboBox comPoortToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem maakVerbindingToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.TextBox RcRb;
        private System.Windows.Forms.TextBox RcRf;
        private System.Windows.Forms.TextBox RcLf;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.TextBox RcLb;
        private System.Windows.Forms.TextBox SerialRead;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox RcLmu;
        private System.Windows.Forms.TextBox RcLmd;
        private System.Windows.Forms.TextBox RcRmd;
        private System.Windows.Forms.TextBox RcRmu;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Button JunctionLeftBtn;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Button JunctionRightBtn;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.HScrollBar ManPwm;
    }
}

