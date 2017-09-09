using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.Win32;

namespace ExecMenu
{
    public partial class Form1 : Form
    {
        string openfilename;

  

        public Form1(string s)
        {
            InitializeComponent();
            // if (s != null && i > 0)
                //MessageBox.Show(s);
                openfilename = s;
                MessageBox.Show(openfilename);

            textBox1.LostFocus += new EventHandler(textBox1_LostFocus);
            
        }

        public Form1()
        {
            InitializeComponent();
            
            textBox1.LostFocus += new EventHandler(textBox1_LostFocus);
        }


        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text !=null)
            {
                RegistryKey key, subkey;
                key = Registry.ClassesRoot.CreateSubKey("*\\shell\\" + textBox1.Text);

                key.SetValue("", textBox1.Text);

                subkey = key.CreateSubKey("command");

                if (textBox2.Text != null)
                {
                    subkey.SetValue("", textBox2.Text);

                    MessageBox.Show("성공");
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
              Registry.ClassesRoot.DeleteSubKeyTree("*\\shell\\" + textBox1.Text);
             // DeleteValue(("command");

        }

        private void textBox1_LostFocus(object sender, System.EventArgs e)
        {
            // Reset the colors and selection of the TextBox after focus is lost.
            textBox2.Text = "C:\\"+ textBox1.Text + ".exe %1";
        }


    }
}
