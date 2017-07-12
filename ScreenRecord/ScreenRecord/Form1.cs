using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

using AForge.Video.FFMPEG;
using AForge.Video;
using System.Diagnostics;

using CSCore;
using CSCore.SoundIn;
using CSCore.Codecs.WAV;

namespace ScreenRecord
{
    public partial class Form1 : Form
    {
        private bool _isRecording;
        private List<string> _screenNames;
        private Rectangle _screenSize;
        private UInt32 _frameCount;
        private int fps;
        private VideoFileWriter _writer;
        private int _width;
        private int _height;
        private ScreenCaptureStream _streamVideo;
        private Stopwatch _stopWatch;
        private Rectangle _screenArea = new Rectangle(0, 0, 600, 500);

        
        private WasapiCapture capture = null;
        private WaveWriter w = null;

        static string fullName;

        

        Form2 form2 = new Form2();

        private void StartRec(string path)
        {
            // form2.Opacity = 0;
            form2.Hide();

            if (_isRecording == false)
            {

                this.SetScreenArea();

                this.SetVisible(true);

                this._frameCount = 0;
                this.fps = 10;
                this.tb_SaveFolder.Text = path;
                fullName = string.Format(@"{0}\{1}", path, DateTime.Now.ToString("MM_dd_HH_mm_ss"));
                //string fullName2 = string.Format(@"{0}\{1}_{2}.wav", path, Environment.UserName.ToUpper(), DateTime.Now.ToString("d_MMM_yyyy_HH_mm_ssff"));
                // Save File option
                _writer.Open(
                    fullName + ".avi",
                    this._width,
                    this._height,
                    fps,
                    (VideoCodec)cb_VideoCodec.SelectedValue,
                    (int)(BitRate)this.cb_BitRate.SelectedValue);

                // Start main work
                this.StartRecord();
                this._isRecording = true;
                if (checkBox1.Checked == true)
                {
                    //start audio
                    
                    //wri = new LameMP3FileWriter(@"C:\Temp\test_output.mp3", waveIn.WaveFormat, 32);
                    // wri = new LameMP3FileWriter(fullName + ".wav", waveIn.WaveFormat, 32);
                    
                    capture = new CSCore.SoundIn.WasapiLoopbackCapture();
                    capture.Initialize();
                    w = new WaveWriter(fullName + ".wav", capture.WaveFormat);
                    //setup an eventhandler to receive the recorded data
                    capture.DataAvailable += (s, capData) =>
                    {
                        //save the recorded audio
                        w.Write(capData.Data, capData.Offset, capData.ByteCount);
                    };
                    //start recording
                    capture.Start();
                }

            }
        }

        public Form1()
        {
            
            form2.Show();
            InitializeComponent();

            // string fullName; 

           

            this._isRecording = false;
            this._screenSize = Screen.PrimaryScreen.Bounds;
            this._frameCount = 0;
            this._width = SystemInformation.VirtualScreen.Width;
            this._height = SystemInformation.VirtualScreen.Height;


            this._stopWatch = new Stopwatch();
            this._screenArea = Rectangle.Empty;

            this.bt_Save.Enabled = false;
            this._writer = new VideoFileWriter();

            _screenNames = new List<string>();
            _screenNames.Add( @"Select ALL" );
            foreach ( var screen in Screen.AllScreens )
            {
                _screenNames.Add(screen.DeviceName);
            }
            this.cb_screenSelector.DropDownStyle = ComboBoxStyle.DropDownList;
            this.cb_screenSelector.DataSource = _screenNames;

            // Codec ComboBox
            this.cb_VideoCodec.DataSource = Enum.GetValues( typeof( VideoCodec ) );
            this.cb_VideoCodec.DropDownStyle = ComboBoxStyle.DropDownList;

            // BitRate 2000kbit/s 2000000 1000000
            this.cb_BitRate.DataSource = Enum.GetValues( typeof( BitRate ) );
            this.cb_BitRate.DropDownStyle = ComboBoxStyle.DropDownList;
            this.cb_BitRate.SelectedIndex = 5;  //비트레이트 초기값
        }

        private void bt_start_Click( object sender, EventArgs e )
        {
            

            try
            {
                if ( this.tb_SaveFolder.Text.Length < 1 )
                {
                    FolderBrowserDialog fbd = new FolderBrowserDialog();
                    if ( fbd.ShowDialog() == DialogResult.OK )
                    {
                        this.StartRec( fbd.SelectedPath );
                    }
                }
                else
                {
                    this.StartRec( this.tb_SaveFolder.Text );
                }
            }
            catch ( Exception exc )
            {
                MessageBox.Show( exc.Message );
            }
        }

      

        private void SetScreenArea()
        {
            // get entire desktop area size
            string screenName = this.cb_screenSelector.SelectedValue.ToString();
            if ( string.Compare( screenName, @"Select ALL", StringComparison.OrdinalIgnoreCase) == 0 )
            {
                foreach ( Screen screen in Screen.AllScreens )
                {
                    //this._screenArea = Rectangle.Union( _screenArea, screen.Bounds );
                    if (form2.Width % 2 == 1) form2.Width = form2.Width + 1;
                    this._screenArea.Width = form2.Width-20;
                    this._width = form2.Width-20;
                    if (form2.Height % 2 == 1) form2.Height = form2.Height + 1;
                    this._screenArea.Height = form2.Height-30;
                    this._height = form2.Height-30;

                    this._screenArea.Offset(form2.Left+10, form2.Top+30);

                }
            }
            else
            {
                this._screenArea = Screen.AllScreens.First( scr => scr.DeviceName.Equals( screenName ) ).Bounds;
                
            }
        }

        private void StartRecord() //Object stateInfo
        {
            // create screen capture video source
            this._streamVideo = new ScreenCaptureStream( this._screenArea );

            // set NewFrame event handler
            this._streamVideo.NewFrame += new NewFrameEventHandler( this.video_NewFrame );

            // start the video source
            this._streamVideo.Start();

            // _stopWatch
            this._stopWatch.Start();
        }

        private void video_NewFrame( object sender, NewFrameEventArgs eventArgs )
        {
            if ( this._isRecording )
            {
                this._frameCount += Convert.ToUInt32(fps);
                this._writer.WriteVideoFrame( eventArgs.Frame );

                this.lb_1.Invoke( new Action( () =>
                {
                    lb_1.Text = string.Format( @"Frames: {0}", _frameCount );
                } ) );

                this.lb_stopWatch.Invoke(new Action(() =>
              {
              this.lb_stopWatch.Text = string.Format("{0:00}:{1:00}:{2:00}", _stopWatch.Elapsed.Hours, _stopWatch.Elapsed.Minutes, (int)_stopWatch.Elapsed.Seconds);
                    

                }) );
            }
            else
            {
                _stopWatch.Reset(); // Terninate Thread
                
                _streamVideo.SignalToStop();
                
                _writer.Close(); // End Recoding

                if (checkBox1.Checked == true)
                {
                    //stop recording
                    capture.Stop();
                    w.Dispose();
                    w = null;
                    capture.Dispose();
                    capture = null;


                    string files = "-i " + fullName + ".avi -i " + fullName + ".wav -c:v copy -c:a aac -strict experimental " + fullName + ".mp4";
                    string cmdtext = "/C ffmpeg " + files;
                    var process = System.Diagnostics.Process.Start("CMD.exe", cmdtext);
                    process.WaitForExit();
                    try
                    {
                        System.IO.File.Delete(fullName + ".avi");
                        System.IO.File.Delete(fullName + ".wav");
                    }
                    catch { MessageBox.Show("fail"); }


                }
            }
        }

        private void bt_Save_Click( object sender, EventArgs e )
        {
            this.SetVisible( false );

            this._isRecording = false;

            //MessageBox.Show(@"File saved!");
            //form2.TransparencyKey = Color.Turquoise;
            //form2.BackColor = Color.Turquoise;
            // form2.Opacity = 80;
            form2.TopMost = true;
            form2.Show();
        }

        private void SetVisible( bool visible )
        {
            this.bt_start.Enabled = !visible;
            this.bt_Save.Enabled = visible;
            this._isRecording = visible;
        }

        private void Form1_FormClosing( object sender, FormClosingEventArgs e )
        {
            this._isRecording = false;
        }

               

    }

    public enum BitRate
    {
        _500kbit = 50000,
        _1000kbit = 1000000,
        _2000kbit = 2000000,
        _3000kbit = 3000000,
        _4000kbit = 4000000,
        _5000kbit = 5000000,
    }
}
