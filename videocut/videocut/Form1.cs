using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Text.RegularExpressions;
using WMPLib;


namespace videocut
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            //string strCmdText;
            //strCmdText = "/C copy /b Image1.jpg + Archive.rar " + textBox1.Text;
            //System.Diagnostics.Process.Start("CMD.exe", strCmdText);

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                System.IO.StreamReader sr = new System.IO.StreamReader(openFileDialog1.FileName);
                textBox1.Text = openFileDialog1.FileName;
               
                double total = Duration(textBox1.Text);
                // MessageBox.Show("okay");

                int minutes = (int)total / 60;

                int seconds = (int)total % 60;

                int hour = (int)minutes / 60;

                if (minutes > 60)
                {
                    minutes = (int)total % 60;
                }

                numericUpDown4.Value = (decimal) hour;

                numericUpDown5.Value = (decimal) minutes;

                numericUpDown6.Value = (decimal) seconds;


                // MessageBox.Show("okay");
                sr.Close();
            }

        }

        public Double Duration(String file)
        {
            WindowsMediaPlayer wmp = new WindowsMediaPlayerClass();
            IWMPMedia mediainfo = wmp.newMedia(file);
            return mediainfo.duration;
        }

        private void button2_Click(object sender, EventArgs e)
        {

            System.Diagnostics.Process.Start("CMD.exe", textBox4.Text);
            

            

        }

        private void button3_Click(object sender, EventArgs e)
        {
            var onlyfilename = Path.GetFileName(openFileDialog1.FileName);

            string pattern = "\\s+";
            string replacement = "_";
            onlyfilename = Regex.Replace(onlyfilename, pattern, replacement);


                int hour = Convert.ToInt32(numericUpDown1.Value);
                int minute = Convert.ToInt32(numericUpDown2.Value);
                int second = Convert.ToInt32(numericUpDown3.Value);

                TimeSpan stime = new TimeSpan(hour, minute, second);

                int hour2 = Convert.ToInt32(numericUpDown4.Value);
                int minute2 = Convert.ToInt32(numericUpDown5.Value);
                int second2 = Convert.ToInt32(numericUpDown6.Value);

                TimeSpan etime = new TimeSpan(hour2, minute2, second2);
            
                textBox4.Text = "/C ffmpeg -i " + "\"" + textBox1.Text + "\"" + " -ss " + stime + " -to " + etime + " -c copy D:\\cut_" + onlyfilename;
            
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void numericUpDown6_ValueChanged(object sender, EventArgs e)
        {

        }
    }
}
