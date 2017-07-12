using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace ScreenRecord
{

    public partial class Form2 : Form
    {

        private Point _lastLeftClickPos, _lastRightClickPos;
        private bool _isVertical;
        private readonly Color _darkTan = Color.FromArgb(176, 125, 68);
        private const int _STRING_PADDING = 10;
        private const string _SIE_STRING_FORMAT = "{0}x{1}";
        // private readonly Bitmap _texture = Resources.SeamlessWood;
        private BufferedGraphics _bufGraphics;
        

        protected override void OnMouseMove(MouseEventArgs e)
        {
            base.OnMouseMove(e);

            if (e.Button == MouseButtons.Left)
            {
                this.Left += e.Location.X - _lastLeftClickPos.X;
                this.Top += e.Location.Y - _lastLeftClickPos.Y;
            }

            this.Invalidate(false);
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            base.OnMouseDown(e);

            if (e.Button == MouseButtons.Left)
            {
                this.Cursor = Cursors.SizeAll;
                _lastLeftClickPos = e.Location;
            }
            else if (e.Button == MouseButtons.Right)
            {
                _lastRightClickPos = e.Location;
            }
        }

        protected override void OnMouseUp(MouseEventArgs e)
        {
            base.OnMouseUp(e);

            if (e.Button == MouseButtons.Left)
            {
                this.Cursor = Cursors.Cross;
            }
        }

        protected override void OnKeyDown(KeyEventArgs e)
        {
            base.OnKeyDown(e);

            if (e.KeyCode == Keys.Escape)
            {
                Application.Exit();
            }
        }

        





        public Form2()
        {

            this.TransparencyKey = Color.Turquoise;
            this.BackColor = Color.Turquoise;
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.ControlBox = false;
            this.Text = String.Empty;
            this.TopMost = true;



            InitializeComponent();

        }
      

        private void Form2_Load(object sender, EventArgs e)
        {
       
        }

        private void SetWindowPos(IntPtr handle, object hWND_TOPMOST, int v1, int v2, int v3, int v4, object tOPMOST_FLAGS)
        {
            throw new NotImplementedException();
        }

        //  int TogMove; int MValX; int MValY;

        //  private void Form2_MouseDown(object sender, MouseEventArgs e) { TogMove = 1; MValX = e.X; MValY = e.Y; }

        //  private void Form2_MouseMove(object sender, MouseEventArgs e) { if (TogMove == 1) { this.SetDesktopLocation(MousePosition.X - MValX, MousePosition.Y - MValY); } }
    }

}

