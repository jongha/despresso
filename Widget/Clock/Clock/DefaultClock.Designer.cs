namespace Clock
{
    partial class DefaultClock
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
            if(disposing && (components != null))
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DefaultClock));
            this.niMainMenu = new System.Windows.Forms.NotifyIcon(this.components);
            this.cmsAllMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.tsmiAbout = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiSeparator = new System.Windows.Forms.ToolStripSeparator();
            this.tsmiExit = new System.Windows.Forms.ToolStripMenuItem();
            this.tmrRotate = new System.Windows.Forms.Timer(this.components);
            this.cmsAllMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // niMainMenu
            // 
            this.niMainMenu.ContextMenuStrip = this.cmsAllMenu;
            this.niMainMenu.Icon = ((System.Drawing.Icon)(resources.GetObject("niMainMenu.Icon")));
            this.niMainMenu.Text = "Time flies!";
            this.niMainMenu.Visible = true;
            // 
            // cmsAllMenu
            // 
            this.cmsAllMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsmiAbout,
            this.tsmiSeparator,
            this.tsmiExit});
            this.cmsAllMenu.Name = "cmsAllMenu";
            this.cmsAllMenu.Size = new System.Drawing.Size(108, 54);
            // 
            // tsmiAbout
            // 
            this.tsmiAbout.Name = "tsmiAbout";
            this.tsmiAbout.Size = new System.Drawing.Size(107, 22);
            this.tsmiAbout.Text = "About";
            this.tsmiAbout.Click += new System.EventHandler(this.tsmiAbout_Click);
            // 
            // tsmiSeparator
            // 
            this.tsmiSeparator.Name = "tsmiSeparator";
            this.tsmiSeparator.Size = new System.Drawing.Size(104, 6);
            // 
            // tsmiExit
            // 
            this.tsmiExit.Name = "tsmiExit";
            this.tsmiExit.Size = new System.Drawing.Size(107, 22);
            this.tsmiExit.Text = "Exit";
            this.tsmiExit.Click += new System.EventHandler(this.tsmiExit_Click);
            // 
            // tmrRotate
            // 
            this.tmrRotate.Enabled = true;
            this.tmrRotate.Interval = 1000;
            this.tmrRotate.Tick += new System.EventHandler(this.tmrRotate_Tick);
            // 
            // frmIrregular
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(160, 160);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "frmIrregular";
            this.ShowInTaskbar = false;
            this.Text = "Time flies";
            this.TransparencyKey = System.Drawing.SystemColors.Control;
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.frmIrregular_MouseMove);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.frmIrregular_MouseDown);
            this.Load += new System.EventHandler(this.frmIrregular_Load);
            this.cmsAllMenu.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.NotifyIcon niMainMenu;
        private System.Windows.Forms.ContextMenuStrip cmsAllMenu;
        private System.Windows.Forms.ToolStripMenuItem tsmiAbout;
        private System.Windows.Forms.ToolStripMenuItem tsmiExit;
        private System.Windows.Forms.ToolStripSeparator tsmiSeparator;
        private System.Windows.Forms.Timer tmrRotate;
    }
}