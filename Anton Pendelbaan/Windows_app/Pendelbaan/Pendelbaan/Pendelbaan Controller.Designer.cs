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
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.communicatieToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1008, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(92, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // communicatieToolStripMenuItem
            // 
            this.communicatieToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.comPoortToolStripMenuItem,
            this.toolStripSeparator1,
            this.maakVerbindingToolStripMenuItem});
            this.communicatieToolStripMenuItem.Name = "communicatieToolStripMenuItem";
            this.communicatieToolStripMenuItem.Size = new System.Drawing.Size(98, 20);
            this.communicatieToolStripMenuItem.Text = "Communicatie";
            // 
            // comPoortToolStripMenuItem
            // 
            this.comPoortToolStripMenuItem.Name = "comPoortToolStripMenuItem";
            this.comPoortToolStripMenuItem.Size = new System.Drawing.Size(152, 23);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(209, 6);
            // 
            // maakVerbindingToolStripMenuItem
            // 
            this.maakVerbindingToolStripMenuItem.Name = "maakVerbindingToolStripMenuItem";
            this.maakVerbindingToolStripMenuItem.Size = new System.Drawing.Size(212, 22);
            this.maakVerbindingToolStripMenuItem.Text = "Maak Verbinding";
            this.maakVerbindingToolStripMenuItem.Click += new System.EventHandler(this.maakVerbindingToolStripMenuItem_Click);
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(908, 1);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(100, 23);
            this.progressBar1.TabIndex = 3;
            // 
            // RcRb
            // 
            this.RcRb.Enabled = false;
            this.RcRb.Location = new System.Drawing.Point(749, 355);
            this.RcRb.Name = "RcRb";
            this.RcRb.Size = new System.Drawing.Size(9, 20);
            this.RcRb.TabIndex = 4;
            // 
            // RcRf
            // 
            this.RcRf.Enabled = false;
            this.RcRf.Location = new System.Drawing.Point(734, 350);
            this.RcRf.Name = "RcRf";
            this.RcRf.Size = new System.Drawing.Size(9, 20);
            this.RcRf.TabIndex = 4;
            // 
            // RcLf
            // 
            this.RcLf.Enabled = false;
            this.RcLf.Location = new System.Drawing.Point(243, 396);
            this.RcLf.Name = "RcLf";
            this.RcLf.Size = new System.Drawing.Size(9, 20);
            this.RcLf.TabIndex = 4;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::Pendelbaan.Properties.Resources.tandrad;
            this.pictureBox1.InitialImage = null;
            this.pictureBox1.Location = new System.Drawing.Point(12, 27);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(984, 638);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 5;
            this.pictureBox1.TabStop = false;
            // 
            // RcLb
            // 
            this.RcLb.Enabled = false;
            this.RcLb.Location = new System.Drawing.Point(228, 395);
            this.RcLb.Name = "RcLb";
            this.RcLb.Size = new System.Drawing.Size(9, 20);
            this.RcLb.TabIndex = 4;
            // 
            // SerialRead
            // 
            this.SerialRead.Location = new System.Drawing.Point(878, 609);
            this.SerialRead.Multiline = true;
            this.SerialRead.Name = "SerialRead";
            this.SerialRead.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.SerialRead.Size = new System.Drawing.Size(118, 108);
            this.SerialRead.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(41, 460);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(46, 15);
            this.label1.TabIndex = 6;
            this.label1.Text = "Boven";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(144, 198);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(64, 15);
            this.label2.TabIndex = 6;
            this.label2.Text = "Beneden";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(844, 198);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(64, 15);
            this.label3.TabIndex = 6;
            this.label3.Text = "Beneden";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(922, 460);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(46, 15);
            this.label4.TabIndex = 6;
            this.label4.Text = "Boven";
            // 
            // RcLmu
            // 
            this.RcLmu.Enabled = false;
            this.RcLmu.Location = new System.Drawing.Point(15, 387);
            this.RcLmu.Name = "RcLmu";
            this.RcLmu.Size = new System.Drawing.Size(9, 20);
            this.RcLmu.TabIndex = 4;
            // 
            // RcLmd
            // 
            this.RcLmd.Enabled = false;
            this.RcLmd.Location = new System.Drawing.Point(129, 153);
            this.RcLmd.Name = "RcLmd";
            this.RcLmd.Size = new System.Drawing.Size(9, 20);
            this.RcLmd.TabIndex = 4;
            // 
            // RcRmd
            // 
            this.RcRmd.Enabled = false;
            this.RcRmd.Location = new System.Drawing.Point(814, 153);
            this.RcRmd.Name = "RcRmd";
            this.RcRmd.Size = new System.Drawing.Size(9, 20);
            this.RcRmd.TabIndex = 4;
            // 
            // RcRmu
            // 
            this.RcRmu.Enabled = false;
            this.RcRmu.Location = new System.Drawing.Point(977, 421);
            this.RcRmu.Name = "RcRmu";
            this.RcRmu.Size = new System.Drawing.Size(9, 20);
            this.RcRmu.TabIndex = 4;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(153, 399);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(69, 13);
            this.label6.TabIndex = 6;
            this.label6.Text = "Reedcontact";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(29, 390);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(69, 13);
            this.label7.TabIndex = 6;
            this.label7.Text = "Reedcontact";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(144, 156);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(69, 13);
            this.label8.TabIndex = 6;
            this.label8.Text = "Reedcontact";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(829, 156);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(69, 13);
            this.label9.TabIndex = 6;
            this.label9.Text = "Reedcontact";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(764, 358);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(69, 13);
            this.label10.TabIndex = 6;
            this.label10.Text = "Reedcontact";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(659, 350);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(69, 13);
            this.label11.TabIndex = 6;
            this.label11.Text = "Reedcontact";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(899, 424);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(69, 13);
            this.label12.TabIndex = 6;
            this.label12.Text = "Reedcontact";
            // 
            // JunctionLeftBtn
            // 
            this.JunctionLeftBtn.Location = new System.Drawing.Point(231, 535);
            this.JunctionLeftBtn.Name = "JunctionLeftBtn";
            this.JunctionLeftBtn.Size = new System.Drawing.Size(75, 23);
            this.JunctionLeftBtn.TabIndex = 7;
            this.JunctionLeftBtn.Text = "Rechtdoor";
            this.JunctionLeftBtn.UseVisualStyleBackColor = true;
            this.JunctionLeftBtn.Click += new System.EventHandler(this.JunctionLeftBtn_Click);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(240, 519);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(66, 13);
            this.label13.TabIndex = 8;
            this.label13.Text = "Wissel Links";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(653, 519);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(75, 13);
            this.label14.TabIndex = 8;
            this.label14.Text = "Wissel Rechts";
            // 
            // JunctionRightBtn
            // 
            this.JunctionRightBtn.Location = new System.Drawing.Point(653, 535);
            this.JunctionRightBtn.Name = "JunctionRightBtn";
            this.JunctionRightBtn.Size = new System.Drawing.Size(75, 23);
            this.JunctionRightBtn.TabIndex = 7;
            this.JunctionRightBtn.Text = "Rechtdoor";
            this.JunctionRightBtn.UseVisualStyleBackColor = true;
            this.JunctionRightBtn.Click += new System.EventHandler(this.JunctionRightBtn_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(258, 400);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(69, 13);
            this.label5.TabIndex = 8;
            this.label5.Text = "Reedcontact";
            // 
            // ManPwm
            // 
            this.ManPwm.Location = new System.Drawing.Point(380, 535);
            this.ManPwm.Name = "ManPwm";
            this.ManPwm.Size = new System.Drawing.Size(206, 17);
            this.ManPwm.TabIndex = 9;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(1008, 729);
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
            this.MainMenuStrip = this.menuStrip1;
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(1024, 768);
            this.MinimumSize = new System.Drawing.Size(1024, 768);
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

