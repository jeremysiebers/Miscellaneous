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
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.SerialRead = new System.Windows.Forms.TextBox();
            this.RcRb = new System.Windows.Forms.TextBox();
            this.RcRf = new System.Windows.Forms.TextBox();
            this.RcLf = new System.Windows.Forms.TextBox();
            this.RcLb = new System.Windows.Forms.TextBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
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
            // statusStrip1
            // 
            this.statusStrip1.Location = new System.Drawing.Point(0, 707);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(1008, 22);
            this.statusStrip1.TabIndex = 2;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(908, 1);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(100, 23);
            this.progressBar1.TabIndex = 3;
            // 
            // SerialRead
            // 
            this.SerialRead.Location = new System.Drawing.Point(755, 588);
            this.SerialRead.Multiline = true;
            this.SerialRead.Name = "SerialRead";
            this.SerialRead.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.SerialRead.Size = new System.Drawing.Size(241, 93);
            this.SerialRead.TabIndex = 0;
            // 
            // RcRb
            // 
            this.RcRb.Location = new System.Drawing.Point(711, 137);
            this.RcRb.Name = "RcRb";
            this.RcRb.Size = new System.Drawing.Size(20, 20);
            this.RcRb.TabIndex = 4;
            // 
            // RcRf
            // 
            this.RcRf.Location = new System.Drawing.Point(711, 267);
            this.RcRf.Name = "RcRf";
            this.RcRf.Size = new System.Drawing.Size(20, 20);
            this.RcRf.TabIndex = 4;
            // 
            // RcLf
            // 
            this.RcLf.Location = new System.Drawing.Point(158, 267);
            this.RcLf.Name = "RcLf";
            this.RcLf.Size = new System.Drawing.Size(20, 20);
            this.RcLf.TabIndex = 4;
            // 
            // RcLb
            // 
            this.RcLb.Location = new System.Drawing.Point(158, 137);
            this.RcLb.Name = "RcLb";
            this.RcLb.Size = new System.Drawing.Size(20, 20);
            this.RcLb.TabIndex = 4;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(12, 27);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(984, 465);
            this.pictureBox1.TabIndex = 5;
            this.pictureBox1.TabStop = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1008, 729);
            this.Controls.Add(this.RcLb);
            this.Controls.Add(this.RcLf);
            this.Controls.Add(this.RcRf);
            this.Controls.Add(this.RcRb);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.SerialRead);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.pictureBox1);
            this.MainMenuStrip = this.menuStrip1;
            this.MaximizeBox = false;
            this.Name = "Form1";
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
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.TextBox SerialRead;
        private System.Windows.Forms.TextBox RcRb;
        private System.Windows.Forms.TextBox RcRf;
        private System.Windows.Forms.TextBox RcLf;
        private System.Windows.Forms.TextBox RcLb;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}

