using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Reflection;
using System.IO;
using System.Drawing.Drawing2D;

namespace Clock
{
    public partial class DefaultClock : Form
    {
        private Point ptMouseOffset;

        /// <summary>
        ///  Constructor
        /// </summary>
        public DefaultClock()
        {
            InitializeComponent();
            EnableDoubleBuffering();
        }

        /// <summary>
        ///  Enable double-buffering
        /// </summary>
        public void EnableDoubleBuffering()
        {
            // Set the value of the double-buffering style bits to true.
            this.SetStyle(ControlStyles.DoubleBuffer | ControlStyles.UserPaint |
                            ControlStyles.AllPaintingInWmPaint, true);
            this.UpdateStyles();
        }

        /// <summary>
        /// Initialization here
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void frmIrregular_Load(object sender, EventArgs e)
        {
            try
            {
                // read the embeded resource
                Assembly asmImage = Assembly.GetExecutingAssembly();
                Stream streamImage = asmImage.GetManifestResourceStream("Clock.Resources.Clock.Default.bmp");
                Bitmap bmpBackground = new Bitmap(streamImage);
                SetFormBackgroundImage(bmpBackground);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Resource wasn't found!");
            }
        }
        
        /// <summary>
        ///  Set the form background
        /// </summary>
        /// <param name="bmpImage"></param>
        private void SetFormBackgroundImage(Bitmap bmpImage)
        {
            Color clrPixel = bmpImage.GetPixel(0, 0);
            bmpImage.MakeTransparent(clrPixel);
            this.BackgroundImage = bmpImage;
            // Set the form size from image size
            this.Size = bmpImage.Size;
        }

        private void frmIrregular_MouseDown(object sender, MouseEventArgs e)
        {
            ptMouseOffset = new Point(-e.X, -e.Y);
        }

        private void frmIrregular_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                Point ptCurrMousePos = Control.MousePosition;

                ptCurrMousePos.Offset(ptMouseOffset.X, ptMouseOffset.Y);
                this.Location = ptCurrMousePos;
            }
        }

        private void tsmiExit_Click(object sender, EventArgs e)
        {
            niMainMenu.Visible = false;
            Application.Exit();
        }

        private void tsmiAbout_Click(object sender, EventArgs e)
        {
            MessageBox.Show("You can contact me at gan.gary@gmail.com", "C# Clock");
        }

        /// <summary>
        /// Override the paint event
        /// </summary>
        /// <param name="e"></param>
        protected override void OnPaint(System.Windows.Forms.PaintEventArgs e)
        {
            // Set the origin to center of the form
            e.Graphics.TranslateTransform(80.0F, 80.0F);

            // Save translated graphics state; So origin will remain at center of form when restore
            GraphicsState transState = e.Graphics.Save();

            // Capture a copy of current time for consistent
            DateTime dtNow = DateTime.Now;

            // rotation starts from new center of the form
            e.Graphics.RotateTransform(dtNow.Second * 6.0F - 90.0F);
            // Anti-alias only affect the next shape
            e.Graphics.SmoothingMode = SmoothingMode.AntiAlias;
            // draw the second hand at new center of the form
            e.Graphics.FillRectangle(new SolidBrush(Color.Silver), -1, -1, 55, 2);

            //// Restore graphics state to translated state and fill second hand
            e.Graphics.Restore(transState);

            // minus 90 degree because start at x-axis
            e.Graphics.RotateTransform(dtNow.Minute * 6.0F - 90.0F);
            // Anti-alias only affect the next shape
            e.Graphics.SmoothingMode = SmoothingMode.AntiAlias;
            e.Graphics.FillRectangle(new SolidBrush(Color.Silver), -1, -1, 45, 3);

            //// Restore graphics state to translated state and fill minute hand
            //gHands.Restore(transState);
            // Reset transformation matrix to identity and fill rectangle.
            e.Graphics.ResetTransform();
            // Set the origin to center of the form
            e.Graphics.TranslateTransform(80.0F, 80.0F);

            // minus 90 degree because start at x-axis; Minute affects hour hand too
            e.Graphics.RotateTransform(dtNow.Hour * 30.0F - 90.0F + dtNow.Minute * 0.5F);
            // Anti-alias only affect the next shape
            e.Graphics.SmoothingMode = SmoothingMode.AntiAlias;
            e.Graphics.FillRectangle(new SolidBrush(Color.Silver), -1, -1, 35, 4);
        }

        /// <summary>
        /// Force the form to repaint for every tick
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tmrRotate_Tick(object sender, EventArgs e)
        {
            // Force to redraw
            //this.Invalidate();
            this.Refresh();
        }
    }
}