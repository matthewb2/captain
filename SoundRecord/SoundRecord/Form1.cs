using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using NAudio.Lame;
using NAudio.Wave;

namespace SoundRecord
{
    public partial class Form1 : Form
    {
        static LameMP3FileWriter wri; 
        
        IWaveIn waveIn = new WasapiLoopbackCapture(); 
        public Form1()
        {
            InitializeComponent();
            NAudio.CoreAudioApi.MMDeviceEnumerator enumerator = new NAudio.CoreAudioApi.MMDeviceEnumerator(); 
            var devices = enumerator.EnumerateAudioEndPoints(NAudio.CoreAudioApi.DataFlow.All, NAudio.CoreAudioApi.DeviceState.Active);
            comboBox1.Items.AddRange(devices.ToArray());
            comboBox1.SelectedIndex = 0;


            timer1.Interval = 100;
            timer1.Start();
            label1.Text = "";
           
           
        }

    

        private void Form1_Load(object sender, EventArgs e)
        {
            button1.Enabled = true;
            button2.Enabled = false;

            
         

            
        }

        static void waveIn_RecordingStopped(object sender, StoppedEventArgs e)         {    
            // signal that recording has finished            
            
            // flush output to finish MP3 file correctly            
            wri.Flush();
            
            wri.Dispose();         
        }

        static void waveIn_DataAvailable(object sender, WaveInEventArgs e)         
        {             
            // write recorded data to MP3 writer 
             wri.Write(e.Buffer, 0, e.BytesRecorded);      
        }

        private void button1_Click(object sender, EventArgs e)
        {
            button1.Enabled = false;
            waveIn.DataAvailable += waveIn_DataAvailable;
            DateTime dt = DateTime.Now; // Or whatever
            string s = dt.ToString("yyyy_MMdd_HHmm_ss");

            wri = new LameMP3FileWriter(@"C:\Temp\"+s+".mp3", waveIn.WaveFormat, 32);
            waveIn.StartRecording();
            label1.Text = "녹음 중..";

        }

        private void button2_Click(object sender, EventArgs e)
        {
            button2.Enabled = true;
            waveIn.RecordingStopped += waveIn_RecordingStopped;
            // Dispose of objects  
            waveIn.Dispose();
            label1.Text = "";
            button1.Enabled = true;
        }

        private void timer1_Tick_1(object sender, EventArgs e)
        {
            //MessageBox.Show("test");
            if (comboBox1.SelectedItem != null)
            {
                var device = (NAudio.CoreAudioApi.MMDevice)comboBox1.SelectedItem;
                progressBar1.Value = (int)(Math.Round(device.AudioMeterInformation.MasterPeakValue * 50));
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();

            openFileDialog1.InitialDirectory = "c:\\Temp";
            openFileDialog1.Filter = "audio files (*.wav)|*.mp3|All files (*.*)|*.*" ;
            openFileDialog1.FilterIndex = 2 ;
            openFileDialog1.RestoreDirectory = true ;

            openFileDialog1.ShowDialog();
        }
    }
}
