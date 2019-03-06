using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Microsoft.Win32;


namespace Regeditor
{
    public partial class Form1 : Form
    {


       

        public Form1()
        {
            InitializeComponent();
              this.Text = "시작프로그램 등록 및 삭제";

            textBox3.TextChanged += TextChanged;


        }

        private void TextChanged(object sender, EventArgs e)
        {
            textBox2.Text = textBox3.Text;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
            RegistryKey reg;

            // reg = Registry.ClassesRoot.CreateSubKey(@"*\shell\WSCloudClient\").CreateSubKey("command");
            // 예 2;
            if (textBox1.Text !="")
            {
                try
                {
                    // Registry.SetValue(keyName, textBox1.Text, textBox2.Text);
                    Registry.SetValue("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", textBox1.Text, textBox2.Text);

                    MessageBox.Show("키 등록 성공");

                }
                catch
                {
                    MessageBox.Show("키 등록 실패");
                }
            }
            else MessageBox.Show("프로그램을 선택해주십시오");            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string keyName = @"Software\Microsoft\Windows\CurrentVersion\Run";
            using (RegistryKey key = Registry.CurrentUser.OpenSubKey(keyName, true))
            {
                if (key == null)
                {
                    // Key doesn't exist. Do whatever you want to handle
                    // this case
                    MessageBox.Show("value field is empty");
                }
                else
                {
                    try
                    {
                        key.DeleteValue(textBox1.Text);
                        MessageBox.Show("The value was deleted");
                    }
                    catch
                    {
                        MessageBox.Show("deleting was failed");
                    }

                }
            }
            

            
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                
                System.IO.FileInfo fInfo = new System.IO.FileInfo(openFileDialog1.FileName);

                string strFileName = fInfo.Name;

                string strFilePath = fInfo.DirectoryName;

                //MessageBox.Show(strFileName + ", " + strFilePath);

                textBox1.Text = fInfo.Name;
                // textBox2.Text = fInfo.DirectoryName + "\\" +fInfo.Name;
                textBox3.Text = openFileDialog1.FileName;
                textBox2.Text = textBox3.Text;
                // sr.Close();
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
