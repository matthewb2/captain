using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
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
            richTextBox1.KeyDown += RichTextBox1_KeyDown;
            richTextBox1.VScroll += RichTextBox1_VScroll;
        }


        private void UserControl1_Paint(Object sender, EventArgs e)
        {
            DrawLineNumber();
            syntaxHighlight();
        }

        private void RichTextBox1_VScroll(object sender, EventArgs e)
        {
            DrawLineNumber();
        }

        public void RichTextBox1_TextChanged(object sender, EventArgs e)
        {

            DrawLineNumber();
            syntaxHighlight();
        }

        public void syntaxHighlight()
        {

            // getting keywords/functions
            string keywords = @"\b(public|private|partial|static|namespace|class|using|void|foreach|in)\b";
            MatchCollection keywordMatches = Regex.Matches(richTextBox1.Text, keywords);

            // getting types/classes from the text 
            string types = @"\b(Console)\b";
            MatchCollection typeMatches = Regex.Matches(richTextBox1.Text, types);

            // getting comments (inline or multiline)
            string comments = @"(\/\/.+?$|\/\*.+?\*\/)";
            MatchCollection commentMatches = Regex.Matches(richTextBox1.Text, comments, RegexOptions.Multiline);
            //MatchCollection commentMatches = Regex.Matches(richTextBox1.Text, comments);

            // getting strings
            string strings = "\".+?\"";
            MatchCollection stringMatches = Regex.Matches(richTextBox1.Text, strings);

            // saving the original caret position + forecolor
            int originalIndex = richTextBox1.SelectionStart;
            int originalLength = richTextBox1.SelectionLength;
            Color originalColor = Color.Black;

            // MANDATORY - focuses a label before highlighting (avoids blinking)
            label1.Focus();
            
            //this is important
            richTextBox1.Font = new System.Drawing.Font("굴림", 11F);
            // removes any previous highlighting (so modified words won't remain highlighted)
            richTextBox1.SelectionStart = 0;
            richTextBox1.SelectionLength = richTextBox1.Text.Length;
            richTextBox1.SelectionColor = originalColor;

            // scanning...


            foreach (Match m in commentMatches)
            {
                richTextBox1.SelectionStart = m.Index;
                richTextBox1.SelectionLength = m.Length;
                richTextBox1.SelectionColor = Color.Green;
            }

            foreach (Match m in keywordMatches)
            {
                richTextBox1.SelectionStart = m.Index;
                richTextBox1.SelectionLength = m.Length;
                richTextBox1.SelectionColor = Color.Blue;
            }

            foreach (Match m in typeMatches)
            {
                richTextBox1.SelectionStart = m.Index;
                richTextBox1.SelectionLength = m.Length;
                richTextBox1.SelectionColor = Color.DarkCyan;
            }

            foreach (Match m in stringMatches)
            {
                richTextBox1.SelectionStart = m.Index;
                richTextBox1.SelectionLength = m.Length;
                richTextBox1.SelectionColor = Color.Brown;
            }
            
            // restoring the original colors, for further writing
            richTextBox1.SelectionStart = originalIndex;
            richTextBox1.SelectionLength = originalLength;
            richTextBox1.SelectionColor = originalColor;

            // giving back the focus
            richTextBox1.Focus();

        }
        // Handle the KeyDown event to determine the type of character entered into the control.
        private void RichTextBox1_KeyDown(object sender, System.Windows.Forms.KeyEventArgs e)
        {
            
        }

        public void DrawLineNumber()
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
                Font f = new Font("Courier New", 12, GraphicsUnit.Pixel);
                g.DrawString((lineNum + 1).ToString(), f, Brushes.DarkGray, new PointF(0, pt.Y));
                lineNum++;

                if (height < pt.Y)
                    break;
            }
            g.Dispose();
        }

    }
}
