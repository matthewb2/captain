using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CherryEdit
{
    
    public partial class Form1 : Form
    {
        

        public Form1()
        {
            InitializeComponent();
            String inputLanguage =
"// Comment. \n" +
"using System;\n" +
"\n" +
"public class Stuff : Form { \n" +
" public static void Main(String args) {\n" +
" }\n" +
"}\n";
            usercontrol1.richTextBox1.Text = inputLanguage;

            usercontrol1.syntaxHighlight();

        }

        private void 정보ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            About ab = new About();
            ab.Visible = true;
        }

        private void 열기ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var fileContent = string.Empty;
            var filePath = string.Empty;

            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.InitialDirectory = "c:\\";
                openFileDialog.Filter = "All files (*.*)|*.*";
                openFileDialog.FilterIndex = 2;
                openFileDialog.RestoreDirectory = true;

                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    //Get the path of specified file
                    filePath = openFileDialog.FileName;

                    //Read the contents of the file into a stream
                    var fileStream = openFileDialog.OpenFile();


                    StreamReader sr = new StreamReader(fileStream);
                    //Read the first line of text
                    string line = sr.ReadLine();
                    usercontrol1.richTextBox1.Text = "";
                    usercontrol1.richTextBox1.Text = System.IO.File.ReadAllText(filePath);
                    usercontrol1.DrawLineNumber();
                    usercontrol1.syntaxHighlight();
                }
            }
        }

        private void 닫기ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }
    }
}
