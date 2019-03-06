using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using NAudio.Wave;

using Microsoft.WindowsAPICodePack.Shell.PropertySystem;
using Microsoft.WindowsAPICodePack.Shell;
using System.Threading;


using System.IO;

namespace NAudioLoop
{

    public partial class Form1 : Form
    {

        static EventWaitHandle _waitHandle = new AutoResetEvent(false);


        private WaveOut waveOut;

        string strFileName;
        string strFilePath;

      

        public static void Mp3ToWav(string mp3File, string outputFile)
        {
            try
            {
                using (Mp3FileReader reader = new Mp3FileReader(mp3File))
                {
                    using (WaveStream pcmStream = WaveFormatConversionStream.CreatePcmStream(reader))
                    {
                        WaveFileWriter.CreateWaveFile(outputFile, pcmStream);
                    }
                }
            }
            catch {
                MessageBox.Show("can not make a output");
            }
        }

        public TimeSpan GetVideoDuration(string filePath)
        {
            ulong t;
            try
            {
                using (var shell = ShellObject.FromParsingName(filePath))
                {
                    IShellProperty prop = shell.Properties.System.Media.Duration;
                    t = (ulong)prop.ValueAsObject;
                    return TimeSpan.FromTicks((long)t);
                }
            }
            catch { }
            return new TimeSpan(0);

        }


        public static void Concatenate(string outputFile, ArrayList sourceFiles)
        {
            byte[] buffer = new byte[1024];
            WaveFileWriter waveFileWriter = null;

            try
            {
                foreach (string sourceFile in sourceFiles)
                {
                    using (WaveFileReader reader = new WaveFileReader(sourceFile))
                    {
                        if (waveFileWriter == null)
                        {
                            // first time in create new Writer
                            waveFileWriter = new WaveFileWriter(outputFile, reader.WaveFormat);
                        }
                        else
                        {
                            if (!reader.WaveFormat.Equals(waveFileWriter.WaveFormat))
                            {
                                throw new InvalidOperationException("Can't concatenate WAV Files that don't share the same format");
                            }
                        }

                        int read;
                        while ((read = reader.Read(buffer, 0, buffer.Length)) > 0)
                        {
                            waveFileWriter.WriteData(buffer, 0, read);
                        }
                    }
                }
            }
            finally
            {
                if (waveFileWriter != null)
                {
                    waveFileWriter.Dispose();
                }
            }

        }


        public Form1()
        {
            InitializeComponent();


        }



        public void MyMethod(ArrayList sf)
        {
            //... (execute any other action)

            Concatenate(@"C:\Output.wav", sf);
            _waitHandle.Set();
        }

        public void MyMethod2()
        {
            //... (execute any other action)

            //Concatenate(@"C:\Output.wav", sf);
            Mp3ToWav(textBox2.Text, @"C:\test.wav");
            _waitHandle.Set();
        }

        


        private void buttonStartStop_Click_1(object sender, EventArgs e)
        {

            ThreadStart tStart = new ThreadStart(() => MyMethod2());

            Thread t = new Thread(tStart);
            t.Start();

            t.Join();
            _waitHandle.WaitOne();


            //Mp3ToWav(textBox2.Text, @"C:\test.wav");
            //MessageBox.Show("audio file is ready");

            string music_src = @"C:\test.wav";
            WaveFileReader reader = new WaveFileReader(music_src);

            TimeSpan ts = reader.TotalTime;


            // label1.Text = String.Format("총 재생시간 {0}:{0}", ts.Minutes, ts.Seconds);

            ArrayList sf = new ArrayList();


            TimeSpan ts2 = GetVideoDuration(textBox1.Text);

            //MessageBox.Show(ts2.TotalSeconds.ToString());

            // label1.Text = String.Format("총 재생시간 {0}:{0}", ts2.Minutes, ts2.Seconds);
            //TimeSpan ts2 = new TimeSpan(0);
                       
            TimeSpan tout = new TimeSpan(0);

            while (ts2.TotalSeconds > tout.TotalSeconds)
            {
                sf.Add(music_src);
                //sf.Add(@"C:\Example.wav");
                tout += ts;
                // MessageBox.Show(tout.TotalSeconds.ToString());
            }


            tStart = new ThreadStart(() => MyMethod(sf));

            t = new Thread(tStart);
            t.Start();

            t.Join();
            _waitHandle.WaitOne();
            if (tout.TotalSeconds > ts2.TotalSeconds)
            {
                string endpoint = ts2.Hours + ":" + ts2.Minutes + ":" + ts2.Seconds;

                string files = "-y -ss 00:00:00 -i C:\\Output.wav -t " + endpoint + " C:\\Output2.wav";
                //MessageBox.Show(files);
                string cmdtext = "/C ffmpeg " + files;
                var process = System.Diagnostics.Process.Start("CMD.exe", cmdtext);
                process.WaitForExit();
                string cmdtext2 = "/C ffmpeg -y -i C:\\Output2.wav -filter:a volume=0.3 C:\\Output3.wav";
                var process2 = System.Diagnostics.Process.Start("CMD.exe", cmdtext2);
                process2.WaitForExit();

            }
            else
            {
                // ffmpeg -i input.wav -filter:a "volume=0.5" output.wav
                string cmdtext2 = "/C ffmpeg -y -i C:\\test.wav -filter:a volume=0.2 C:\\Output3.wav";
                var process2 = System.Diagnostics.Process.Start("CMD.exe", cmdtext2);
                process2.WaitForExit();
            }

          

            // string cmdtext3 = "/C ffmpeg -y -i "+ fullPath + " -i C:\\Output3.wav -filter_complex [0:a][1:a]amix=duration=shortest[a] -map 0:v -map [a] -c:v copy C:\\newavoutput.mp4";
            string cmdtext3 = "/C ffmpeg -y -i " + textBox1.Text.Replace(@"\", @"\\") + " -i C:\\Output3.wav -filter_complex [0:a][1:a]amix=duration=shortest[a] -map 0:v -map [a] -c:v copy " + textBox3.Text.Replace(@"\", @"\\");

            var process3 = System.Diagnostics.Process.Start("CMD.exe", cmdtext3);
            process3.WaitForExit();

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {

                System.IO.FileInfo fInfo = new System.IO.FileInfo(openFileDialog1.FileName);

                strFileName = fInfo.Name;

                strFilePath = fInfo.DirectoryName;

                //MessageBox.Show(strFileName + ", " + strFilePath);

                textBox1.Text = strFilePath + strFileName;
                // textBox2.Text = fInfo.DirectoryName + "\\" + fInfo.Name;


                // sr.Close();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (openFileDialog2.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {

                System.IO.FileInfo fInfo = new System.IO.FileInfo(openFileDialog2.FileName);

                string astrFileName = fInfo.Name;

                string astrFilePath = fInfo.DirectoryName;

                textBox2.Text = astrFilePath + "\\"+astrFileName;

                //textBox2.Text = astrFilePath + "\\" + astrFileName;
                textBox2.Text = textBox2.Text.Replace(@"\\", @"\");

            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            // Displays a SaveFileDialog so the user can save the Image  
            // assigned to Button2.  
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.Filter = "Mpeg4 Video|*.mp4";
            saveFileDialog1.Title = "Save an Mpeg4 File";
            saveFileDialog1.ShowDialog();

            // If the file name is not an empty string open it for saving.  
            if (saveFileDialog1.FileName != "")
            {
                // Saves the Image via a FileStream created by the OpenFile method.  
                System.IO.FileStream fs =
                   (System.IO.FileStream)saveFileDialog1.OpenFile();
                // Saves the Image in the appropriate ImageFormat based upon the  
                // File type selected in the dialog box.  
                // NOTE that the FilterIndex property is one-based.  
                // Get file name.
                string name = saveFileDialog1.FileName;
                textBox3.Text = name;

                fs.Close();
            }
        }
    }
}

