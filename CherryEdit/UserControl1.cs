using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CherryEdit
{
    public partial class UserControl1 : UserControl
    {
        public UserControl1()
        {
            InitializeComponent();
            this.Paint += UserControl1_Paint;
            richTextBox1.TextChanged += RichTextBox1_TextChanged;
            richTextBox1.VScroll += RichTextBox1_VScroll;
        }


        private void UserControl1_Paint(Object sender, EventArgs e)
        {

            //MessageBox.Show("You are in the UserControl.Load event.");
            DrawLineNumber();
        }

        private void RichTextBox1_VScroll(object sender, EventArgs e)
        {
            
        }

        private void RichTextBox1_TextChanged(object sender, EventArgs e)
        {
            DrawLineNumber();
        }
        void DrawLineNumber()
        {
            int lineNum = 0;
            int height = richTextBox1.Size.Height;
            Graphics g = this.CreateGraphics();
            g.Clear(Color.White);

            int charIndex = richTextBox1.GetCharIndexFromPosition(new Point(0, 0));
            lineNum = richTextBox1.GetLineFromCharIndex(charIndex);

            while (true)
            {
                charIndex = richTextBox1.GetFirstCharIndexFromLine(lineNum);
                if (charIndex == -1)
                    break;
                Point pt = richTextBox1.GetPositionFromCharIndex(charIndex);
                Font f = new Font("굴림",13, GraphicsUnit.Pixel);
                g.DrawString((lineNum + 1).ToString(), f, Brushes.Blue, new PointF(0, pt.Y));
                lineNum++;

                if (height < pt.Y)
                    break;
            }
            g.Dispose();
        }

    }
}
