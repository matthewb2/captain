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
    
    public partial class 체리텍스트에디터 : Form
    {

        Regex r;
         

        public 체리텍스트에디터()
        {
            InitializeComponent();
            String inputLanguage =
"// Comment.\n" +
"using System;\n" +
"\n" +
"public class Stuff : Form { \n" +
" public static void Main(String args) {\n" +
" }\n" +
"}\n";

            //r= new Regex();
            String[] lines = inputLanguage.Split('\n');


            foreach (string l in lines)
            {
                ParseLine(l);
            }

        }

        void ParseLine(string line)
        {
            Regex r = new Regex("([ \\t{}():;])");
            String[] tokens = r.Split(line);
            foreach (string token in tokens)
            {
                // Set the tokens default color and font.  
                usercontrol1.richTextBox1.SelectionColor = Color.Black;
                usercontrol1.richTextBox1.SelectionFont = new Font("Courier New", 10, FontStyle.Regular);
                // Check whether the token is a keyword.   
                String[] keywords = { "public", "void", "using", "static", "class" };
                for (int i = 0; i < keywords.Length; i++)
                {
                    if (keywords[i] == token)
                    {
                        // Apply alternative color and font to highlight keyword.  
                        usercontrol1.richTextBox1.SelectionColor = Color.Blue;
                        usercontrol1.richTextBox1.SelectionFont = new Font("Courier New", 10, FontStyle.Bold);
                        break;
                    }
                }
                usercontrol1.richTextBox1.SelectedText = token;
            }
            usercontrol1.richTextBox1.SelectedText = "\n";
        }

        private void 정보ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            About ab = new About();
            ab.Visible = true;
        }
    }
}
