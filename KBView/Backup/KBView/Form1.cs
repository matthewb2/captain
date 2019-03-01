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
        string[] filePaths = null;
        string fileName = null;
        string path = null;
        int pos;

           
        string cut_file;

        private Point MouseDownLocation;




        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                MouseDownLocation = e.Location;
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                //MessageBox.Show("okay");
                
                    contextMenuStrip1.Show(pictureBox1, e.X, e.Y);
                    //MessageBox.Show("okay");
                    contextMenuStrip1.ItemClicked += new ToolStripItemClickedEventHandler(
                                                             contextMenuStrip1_ItemClicked);
                

            }


        }

        void contextMenuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            ToolStripItem item = e.ClickedItem;
            // your code here
            //MessageBox.Show("okay");
            if (File.Exists(cut_file))
            {
                fileName = cut_file;
                // MessageBox.Show(fileName);

                //string currFile = pictureBox1.Tag.ToString();
                //MessageBox.Show(path);
                if (pos <= 0)
                {

                    pos = Array.IndexOf(filePaths, fileName);
                    // MessageBox.Show(pos.ToString());

                }
                try
                {
                    pos++;
                    pictureBox1.Image = Image.FromFile(filePaths[pos]);
                    cut_file = filePaths[pos];
                    pictureBox1_zoom(1);
                   // MessageBox.Show(filePaths[pos - 1]);
                    File.Delete(filePaths[pos-1]);

                }
                catch { }

                
            }
                
        }

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                pictureBox1.Left = e.X + pictureBox1.Left - MouseDownLocation.X;
                pictureBox1.Top = e.Y + pictureBox1.Top - MouseDownLocation.Y;
            }
        }

    

        public Form1(string[] argv)
        {
            this.KeyPreview = true;
            InitializeComponent();


            button1.MouseEnter += new EventHandler(button1_MouseEnter);
            button1.MouseLeave += new EventHandler(button1_MouseLeave);

            button2.MouseEnter += new EventHandler(button2_MouseEnter);
            button2.MouseLeave += new EventHandler(button2_MouseLeave);

            button1.FlatAppearance.BorderColor = Color.FromArgb(0, 255, 255, 255); // transparent
            
          
            //MessageBox.Show(argv[0].ToString());
            // pictureBox1.Image = "C:\\test.jpg";
            pictureBox1.Image = Image.FromFile(argv[0].ToString());
            cut_file = argv[0].ToString();

            FileInfo fileInfo = new FileInfo(cut_file);
            path = fileInfo.DirectoryName; // contains "C:\MyDirectory"

            //get all name of files in path

            filePaths = Directory.GetFiles(path, "*.jpg");

            toolStripStatusLabel1.Text = "가로" + pictureBox1.Image.Width.ToString() + " 세로 " + pictureBox1.Image.Height.ToString();
     
            
        }

        public Form1()
        {
            this.KeyPreview = true;
            InitializeComponent();
            button1.MouseEnter += new EventHandler(button1_MouseEnter);
            button1.MouseLeave += new EventHandler(button1_MouseLeave);

            button2.MouseEnter += new EventHandler(button2_MouseEnter);
            button2.MouseLeave += new EventHandler(button2_MouseLeave);

          
          
        }

        private void Form1_Resize(object sender, System.EventArgs e)
        {
            //MessageBox.Show("ddd");

            float c_width, c_height;

            if (cut_file !=null)
             
            {
               
                
                c_width = pictureBox1.Width;
                c_height = pictureBox1.Height;

                if (c_width+120 > this.Width || c_height+80 > this.Height)
                {
                    Size newSize = new Size((int)(this.Width - 120 ), (int)(this.Height - 100 ));
                    Bitmap tmp = new Bitmap(cut_file);
                    Bitmap bmp = new Bitmap(tmp, newSize);
                    CenterPictureBox(pictureBox1, bmp);


                }
                else
                {
                    Bitmap tmp = new Bitmap(cut_file);
                    
                    //tabImageView.Controls.Add(picBoxView);
                    CenterPictureBox(pictureBox1, tmp);
                }
            }

            
        }


        protected override void OnMouseWheel(MouseEventArgs e)
        {
            //MessageBox.Show("ddd");
            //int zoomFactor = 10;
            float zoomLevel;
            if (e.Delta > 0)
            {
                zoomLevel = 1.2f;
            }
            else zoomLevel = 0.8f;

            //pictureBox1.Image = Image.FromFile("C:\\Documents and Settings\\Administrator\\daymin.com\\973691257.jpg");
            
            Image img = pictureBox1.Image;
            
            //MessageBox.Show("ddd");

            Bitmap bitMapImg = new Bitmap(img);
            Bitmap tmp = new Bitmap(cut_file);

            Size newSize = new Size((int)(bitMapImg.Width * zoomLevel), (int)(bitMapImg.Height * zoomLevel));
            Bitmap bmp = new Bitmap(tmp, newSize);

            pictureBox1.Width = newSize.Width;
            pictureBox1.Height = newSize.Height;

            pictureBox1.Image = (Image)bmp;

        }



        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "jpg (*.jpg)|*.jpg|bmp (*.bmp)|*.bmp|png (*.png)|*.png";

            if (ofd.ShowDialog() == DialogResult.OK)
            {
                Bitmap b = new Bitmap(ofd.FileName);
                cut_file = ofd.FileName;
                //imagePanel1.CanvasSize = b.Size;
                pictureBox1.Image = b;

                pictureBox1.Location = new Point((this.Width / 2) - (b.Width / 2),
                                        (this.Height / 2) - (b.Height / 2));
           
            }

            FileInfo fileInfo = new FileInfo(cut_file);
            path = fileInfo.DirectoryName; // contains "C:\MyDirectory"

            //get all name of files in path

            filePaths = Directory.GetFiles(path, "*.jpg");
            
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
            if (cut_file !=null)
            {
                fileName = cut_file;
                // MessageBox.Show(fileName);

                //string currFile = pictureBox1.Tag.ToString();
                //MessageBox.Show(path);
                if (pos <= 0)
                {

                    pos = Array.IndexOf(filePaths, fileName);
                    // MessageBox.Show(pos.ToString());

                }
                try
                {
                    pos++;
                    pictureBox1.Image = Image.FromFile(filePaths[pos]);
                    cut_file = filePaths[pos];
                    pictureBox1_zoom(1);

                }
                catch { MessageBox.Show("fail"); }
            }

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
            try { pos--; pictureBox1.Image = Image.FromFile(filePaths[pos]);
            pictureBox1_zoom(1);
            }
            catch { MessageBox.Show("fail"); }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // register keyboard event on form
            this.KeyDown += new KeyEventHandler(Form1_KeyDown);
        }

        
        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            float zoomLevel;
            zoomLevel = 0.0f;

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

            if (e.KeyCode == Keys.Add)
            {
                zoomLevel = 1.2f;
                //MessageBox.Show("ddd");
                pictureBox1_zoom(zoomLevel);

            }
            if (e.KeyCode == Keys.Subtract)
            {
                zoomLevel = 0.8f;
                pictureBox1_zoom(zoomLevel);

            }

        }


        protected void pictureBox1_zoom(float zoomLevel)
        {
           
            //pictureBox1.Image = Image.FromFile("C:\\Documents and Settings\\Administrator\\daymin.com\\973691257.jpg");

            Image img = pictureBox1.Image;

            //MessageBox.Show("ddd");

            Bitmap bitMapImg = new Bitmap(img);
            Bitmap tmp = new Bitmap(cut_file);

            Size newSize = new Size((int)(bitMapImg.Width * zoomLevel), (int)(bitMapImg.Height * zoomLevel));
            Bitmap bmp = new Bitmap(tmp, newSize);

            pictureBox1.Width = newSize.Width;
            pictureBox1.Height = newSize.Height;

            pictureBox1.Image = (Image)bmp;

            //rpicBoxView.SizeMode = PictureBoxSizeMode.AutoSize;
            //picBoxView.Anchor = AnchorStyles.None;
            //tabImageView.Controls.Add(picBoxView);
            CenterPictureBox(pictureBox1, bmp);


        }

        private void CenterPictureBox(PictureBox picBox, Bitmap picImage)
        {
            picBox.Image = picImage;
            picBox.Size = picImage.Size;
            picBox.Location = new Point((picBox.Parent.ClientSize.Width / 2) - (picImage.Width / 2),
                                        (picBox.Parent.ClientSize.Height / 2) - (picImage.Height / 2));
            picBox.Refresh();
        }



      


        private void tableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            //MessageBox.Show("Form Pressed");
            NextToolStripMenuItem_Click_1(sender, e);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //MessageBox.Show("Form Pressed");
            이전ToolStripMenuItem_Click(sender, e);
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            //MessageBox.Show("Form Pressed");
            NextToolStripMenuItem_Click_1(sender, e);
       
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            //MessageBox.Show("Form Pressed");
            이전ToolStripMenuItem_Click(sender, e);
       
        }

        private void button1_MouseEnter(object sender, EventArgs e)
        {
            button1.UseVisualStyleBackColor = true;
        }

        private void button1_MouseLeave(object sender, EventArgs e)
        {
            button1.UseVisualStyleBackColor = false;
        }

        private void button2_MouseEnter(object sender, EventArgs e)
        {
            button2.UseVisualStyleBackColor = true;
        }

        private void button2_MouseLeave(object sender, EventArgs e)
        {
            button2.UseVisualStyleBackColor = false;
        }

        private void 전체화면ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            float c_width, c_height;

            if (cut_file != null)
            {


                c_width = pictureBox1.Width;
                c_height = pictureBox1.Height;

                
                   Size newSize = new Size((int)(this.Width - 120), (int)(this.Height - 100));
                    Bitmap tmp = new Bitmap(cut_file);
                    Bitmap bmp = new Bitmap(tmp, newSize);
                    CenterPictureBox(pictureBox1, bmp);


            }

        }



    }
}
