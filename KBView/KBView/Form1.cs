using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace KBView
{
    public partial class Form1 : Form
    {
        string[] filePaths;
        string fileName;
        string path;
        int pos;
        Image imgOriginal;

        public Form1(string[] argv)
        {
            InitializeComponent();
           // MessageBox.Show(argv[0].ToString());
            // pictureBox1.Image = "C:\\test.jpg";
        }

        

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "jpg (*.jpg)|*.jpg|bmp (*.bmp)|*.bmp|png (*.png)|*.png";

            if (ofd.ShowDialog() == DialogResult.OK && ofd.FileName.Length > 0)
            {
                pictureBox1.SizeMode = PictureBoxSizeMode.Zoom;
                pictureBox1.Image = Image.FromFile(ofd.FileName);
                imgOriginal = pictureBox1.Image;
                // directoryPath = Path.GetDirectoryName(filePath);
                string fullPath = ofd.FileName;
                
                fileName = ofd.SafeFileName;
                path = fullPath.Replace(fileName, "");

                filePaths = Directory.GetFiles(path, "*.jpg");
                string toDisplay = string.Join(Environment.NewLine, filePaths);
                //MessageBox.Show(toDisplay);
                //MessageBox.Show("dot net","improrant");
            }

            toolStripStatusLabel1.Text = "가로" + pictureBox1.Image.Width.ToString() + " 세로 " + pictureBox1.Image.Height.ToString();
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = "jpg (*.jpg)|*.jpg|bmp (*.bmp)|*.bmp|png (*.png)|*.png";

            if (sfd.ShowDialog() == DialogResult.OK && sfd.FileName.Length > 0)
            {
                pictureBox1.Image.Save(sfd.FileName);
            }
        }

        
        private void NextToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            //MessageBox.Show(path+fileName);

            //string currFile = pictureBox1.Tag.ToString();
            //MessageBox.Show(path + currFile);
            if (pos <= 0)
            {
                pos = Array.IndexOf(filePaths, path + fileName);
                // MessageBox.Show(pos.ToString());
            }
            try { pos++;  pictureBox1.Image = Image.FromFile(filePaths[pos]); }
                catch { MessageBox.Show("fail"); }
            
        }

        private void 이전ToolStripMenuItem_Click(object sender, EventArgs e)
        {


            //string currFile = pictureBox1.Tag.ToString();
            //MessageBox.Show(path + currFile);
            if (pos <= 0)
            {
                pos = Array.IndexOf(filePaths, path + fileName);
                // MessageBox.Show(pos.ToString());
            }
            try { pos--; pictureBox1.Image = Image.FromFile(filePaths[pos]); }
            catch { MessageBox.Show("fail"); }
        }

        private void Form1_Load(object sender, EventArgs e)
        {   
            // register keyboard event on form
            this.KeyDown += new KeyEventHandler(Form1_KeyDown);
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Space)
            {
                //MessageBox.Show("Form Pressed");
                NextToolStripMenuItem_Click_1(sender, e);
            }
            if (e.KeyCode == Keys.Back)
            {
                //MessageBox.Show("Form Pressed");
                이전ToolStripMenuItem_Click(sender, e);
            }
        }

        private void NextToolStripMenuItem_Click_1()
        {
            throw new NotImplementedException();
        }

        private void statusStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

      



        
    }
}
