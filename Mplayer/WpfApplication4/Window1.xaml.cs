using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using System.IO;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Threading;


namespace WpfApplication4
{
    /// <summary>
    /// Window1.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class Window1 : Window, INotifyPropertyChanged
    {
        
        bool isFullScreen = false;
        bool autoplay = true;
        double height;
        double width;
        private TimeSpan TotalTime;
        DispatcherTimer timerVideoTime;
        int cur_sec;

        string[] filePaths;

        double gVolume = 0.5;

        List<string> playlist = new List<string>();

        string cur_file;
        private int _height;
        private double m_MyWindowHeight = 0;
        public double MyWindowHeight
        {
            get
            {
                return m_MyWindowHeight;
            }
            set
            {
                m_MyWindowHeight = value;
                this.OnPropertyChanged("MyWindowHeight");
            }
        }

        public static Bitmap Crop(Bitmap bmp)
        {
            int w = bmp.Width;
            int h = bmp.Height;

            Func<int, bool> allWhiteRow = row =>
            {
                for (int i = 0; i < w; ++i)
                    if (bmp.GetPixel(i, row).R != 0)
                        return false;
                return true;
            };

            Func<int, bool> allWhiteColumn = col =>
            {
                for (int i = 0; i < h; ++i)
                    if (bmp.GetPixel(col, i).R != 0)
                        return false;
                return true;
            };

            int topmost = 0;
            for (int row = 0; row < h; ++row)
            {
                if (allWhiteRow(row))
                    topmost = row;
                else break;
            }

            int bottommost = 0;
            for (int row = h - 1; row >= 0; --row)
            {
                if (allWhiteRow(row))
                    bottommost = row;
                else break;
            }

            int leftmost = 0, rightmost = 0;
            for (int col = 0; col < w; ++col)
            {
                if (allWhiteColumn(col))
                    leftmost = col;
                else
                    break;
            }

            for (int col = w - 1; col >= 0; --col)
            {
                if (allWhiteColumn(col))
                    rightmost = col;
                else
                    break;
            }

            if (rightmost == 0) rightmost = w; // As reached left
            if (bottommost == 0) bottommost = h; // As reached top.

            // 10, 20 for correction
            int croppedWidth = rightmost - leftmost - 10;
            int croppedHeight = bottommost - topmost - 20;

            if (croppedWidth == 0) // No border on left or right
            {
                leftmost = 0;
                croppedWidth = w;
            }

            if (croppedHeight == 0) // No border on top or bottom
            {
                topmost = 0;
                croppedHeight = h;
            }

            try
            {
                var target = new Bitmap(croppedWidth, croppedHeight);
                using (Graphics g = Graphics.FromImage(target))
                {
                    g.DrawImage(bmp,
                      new RectangleF(0, 0, croppedWidth, croppedHeight),
                      new RectangleF(leftmost, topmost, croppedWidth, croppedHeight),
                      GraphicsUnit.Pixel);
                }
                return target;
            }
            catch (Exception ex)
            {
                throw new Exception(
                  string.Format("Values are topmost={0} btm={1} left={2} right={3} croppedWidth={4} croppedHeight={5}", topmost, bottommost, leftmost, rightmost, croppedWidth, croppedHeight),
                  ex);
            }
        }

        public Window1()
        {

            InitializeComponent();
            MyWindowHeight = 500;
            this.DataContext = this;


            int SliderValue = (int)TimeLine.Value;

            btnPlay.Focusable = False;
            //btnPause.Focusable = False;
            btnStop.Focusable = False;
            btnBrowse.Focusable = False;


            
            
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName)
        {
            if (this.PropertyChanged != null)
                this.PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }


        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);

            // Begin dragging the window
            this.DragMove();
        }

        private void Minimize_Click(object sender, RoutedEventArgs e)
        {
            // MessageBox.Show("how do i handle the other clicks?!");
            WindowState = WindowState.Minimized;
            
        }
        private void Maximize_Click(object sender, RoutedEventArgs e)
        {
            // MessageBox.Show("how do i handle the other clicks?!");
            WindowState = WindowState.Maximized;

        }
     
        private void NextFile_Click(object sender, RoutedEventArgs e)
        {
            // MessageBox.Show("how do i handle the other clicks?!");
            //get from curfile
            mediaPlayer1.Stop();

            int index = playlist.IndexOf(cur_file);

                //  MessageBox.Show(i.ToString());

                    mediaPlayer1.Source = new Uri(filePaths[index + 1]);
                    this.Title = filePaths[index + 1];

                    cur_file = filePaths[index + 1];

                    //gVolume = 0;
                    //MessageBox.Show(gVolume.ToString());
                    //mediaPlayer1.Volume = gVolume;
                    mediaPlayer1.Play();

        }

        private void PrevFile_Click(object sender, RoutedEventArgs e)
        {
            // MessageBox.Show("how do i handle the other clicks?!");
            Application.Current.Shutdown();
        }

        public void MyMethod()
        {
            //... (execute any other action)
            File.Delete(cur_file);

        }

        private void DeleteFile_Click(object sender, RoutedEventArgs e)
        {
            // MessageBox.Show("how do i handle the other clicks?!");
            //Application.Current.Shutdown();
            // delete file thread

            
            ThreadStart tStart = new ThreadStart(() => MyMethod());

            Thread t = new Thread(tStart);
            t.Start();

            t.Join();

            NextFile_Click(sender, e);

        }

        private void CaptureFrame_Click(object sender, RoutedEventArgs e)
        {
            // MessageBox.Show("how do i handle the other clicks?!");
            float factorx = .93f;
            float factory = .87f;
            System.Windows.Size dpi = new System.Windows.Size((int)96*factorx, (int)96 *factory);
            //Size dpi = new Size(mediaPlayer1.Width, mediaPlayer1.Height);

            int btmWidth = mediaPlayer1.NaturalVideoWidth;
            int btmHeight = mediaPlayer1.NaturalVideoHeight;

            RenderTargetBitmap bmp =
                new RenderTargetBitmap(btmWidth, btmHeight,
                dpi.Width, dpi.Height, PixelFormats.Pbgra32);
                    //mediaPlayer1.Play();
            bmp.Render(mediaPlayer1);

            JpegBitmapEncoder encoder = new JpegBitmapEncoder();

            encoder.Frames.Add(BitmapFrame.Create(bmp));

            string filename = Guid.NewGuid().ToString() + ".jpg";
            FileStream fs = new FileStream(filename, FileMode.Create);
            encoder.Save(fs);
            fs.Close();
            string filename2 = Guid.NewGuid().ToString() + "_cropped.jpg";
            using (Stream BitmapStream = System.IO.File.Open(filename, System.IO.FileMode.Open))
            {
                System.Drawing.Image img = System.Drawing.Image.FromStream(BitmapStream);

                Bitmap mBitmap = new Bitmap(img);
                //...do whatever
                Bitmap cropped = Crop(mBitmap);

                cropped.Save(filename2, System.Drawing.Imaging.ImageFormat.Jpeg);

            }


          
            

            Process.Start(filename2);

        }



        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            // MessageBox.Show("how do i handle the other clicks?!");
            Application.Current.Shutdown();
        }

        private void btnPlayLists_Click(object sender, RoutedEventArgs e)
        {
            // MessageBox.Show("how do i handle the other clicks?!");
            Application.Current.Shutdown();
        }

        private void window1_KeyUp(object sender, KeyEventArgs e)
        {

           
            if (e.Key == Key.Left)
            {
                //10초 뒤로 이동
               
                
                // ts2.Text = TimeLine.Value.ToString();
                cur_sec -= 10;

                TimeSpan ts3 = new TimeSpan(0, 0, (int)cur_sec);
                // ts2.Text = TimeLine.Value.ToString();
                ts2.Text = ts3.ToString();

                TimeLine.Value -= 10;

                mediaPlayer1.Position = new TimeSpan(0, 0, 0, cur_sec, 0);  
                
                
            }

            if (e.Key == Key.Right)
            {
                //10초 forward로 이동


                // ts2.Text = TimeLine.Value.ToString();
                cur_sec += 10;

                TimeSpan ts3 = new TimeSpan(0, 0, (int)cur_sec);
                // ts2.Text = TimeLine.Value.ToString();
                ts2.Text = ts3.ToString();

                TimeLine.Value += 10;

                mediaPlayer1.Position = new TimeSpan(0, 0, 0, cur_sec, 0);


            }

            if (e.Key == Key.Enter)
            {
                height = mediaPlayer1.Height = System.Windows.SystemParameters.PrimaryScreenHeight;
                width = System.Windows.SystemParameters.PrimaryScreenWidth;
                
                if (WindowState == WindowState.Maximized)
                {
                    //MessageBox.Show("yesy");
                    MyWindowHeight = 300;


                }
                else WindowState = WindowState.Maximized;
            }

            if (e.Key == Key.Down)
            {
                mediaPlayer1.Volume -= 0.1;
                slider.Value = mediaPlayer1.Volume;
                gVolume = mediaPlayer1.Volume;

            }

            if (e.Key == Key.Up)
            {
                mediaPlayer1.Volume += 0.1;
                slider.Value = mediaPlayer1.Volume;
                
                gVolume = mediaPlayer1.Volume;


            }
             if (e.Key == Key.Space)
             {


                 if (timerVideoTime.IsEnabled)
                 {
                     // Do Something
                     //btnPause_Click(sender, e);
                 }
                 else if (!timerVideoTime.IsEnabled)
                 {
                     // Do Something
                     btnPlay_Click(sender, e);
                 }

             }





        }

        private void btnBrowse_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog ofd = new Microsoft.Win32.OpenFileDialog();

            if (ofd.ShowDialog().Value)
            {

                string fileName = ofd.FileName;

                string fullPath = ofd.FileName;
                string fileName2 = ofd.SafeFileName;
                string path = fullPath.Replace(fileName2, "");
                string[] extensions = { ".mp4", ".avi", ".asp", "wmv" };

                filePaths = Directory.GetFiles(path, "*.*").Where(f => extensions.Contains(new FileInfo(f).Extension.ToLower())).ToArray();

                for (int i=0; i < filePaths.Length; i++) { 
                    playlist.Add(filePaths[i]);
                }

                cur_file = fileName;

                mediaPlayer1.Source = new Uri(fileName);

                title.Text = System.IO.Path.GetFileName(fileName);
                
                

                mediaPlayer1.Play();

               


             

                TimeLine.Value = 0;

                
                // Create a timer that will update the counters and the time slider
                timerVideoTime = new DispatcherTimer();
                timerVideoTime.Interval = TimeSpan.FromSeconds(1);
                timerVideoTime.Tick += timer_Tick;
                timerVideoTime.Start();

                

            }
        }

        private void btnPlay_Click(object sender, RoutedEventArgs e)
        {
            if (mediaPlayer1.HasVideo)
            {

                mediaPlayer1.Play();
                //btnPlay.IsEnabled = false;
                if (btnPlay.Content == FindResource("Play"))
                {
                    btnPlay.Content = FindResource("Stop");
                }
                else
                {
                    btnPlay.Content = FindResource("Play");
                }
                //btnPause.IsEnabled = true;
                btnStop.IsEnabled = true;



            }

            if (!timerVideoTime.IsEnabled)
            {
                timerVideoTime.IsEnabled = true;
            }

        }

        void timer_Tick(object sender, EventArgs e)
        {
            // Increment the value of the ProgressBar a value of one each time.
            
                mediaPlayer1.Volume = gVolume;
                slider.Value = gVolume;
            
            TimeLine.Value +=1;
            cur_sec += 1;
            TimeSpan ts = new TimeSpan(0, 0, cur_sec);
            // ts2.Text = TimeLine.Value.ToString();
            ts2.Text = ts.ToString();

            // Determine if we have completed by comparing the value of the Value property to the Maximum value.
            if (TimeLine.Value == TimeLine.Maximum)
            {
                // Stop the timer.
                mediaPlayer1.Stop();
                // MessageBox.Show("end of file");
                timerVideoTime.Stop();
                timerVideoTime.IsEnabled = false;
                if (autoplay == true) {
                    // MessageBox.Show(filePaths.Length.ToString());
                    
                    for (int i=0; i< filePaths.Length-1; i++)
                    {
                        if (filePaths[i].Contains(cur_file))
                        //  MessageBox.Show(i.ToString());
                        {

                            if (i < filePaths.Length-1)
                            {
                                mediaPlayer1.Source = new Uri(filePaths[i + 1]);

                                this.Title = filePaths[i + 1];

                                cur_file = filePaths[i + 1];

                                //gVolume = 0;
                                //MessageBox.Show(gVolume.ToString());
                                //mediaPlayer1.Volume = gVolume;
                                mediaPlayer1.Play();

                                TimeLine.Value = 0;
                                mediaPlayer1.Volume = 0;

                                // Create a timer that will update the counters and the time slider
                                timerVideoTime = new DispatcherTimer();
                                timerVideoTime.Interval = TimeSpan.FromSeconds(1);
                                timerVideoTime.Tick += timer_Tick;
                                timerVideoTime.Start();

                                cur_sec = 0;
                                ts2.Text = "00:00:00";
                                tst.Text = "00:00:00";
                            }
                            break;
                        }
                       

                    }


                    //  mediaPlayer1.Source = new Uri(fileName);

                    //  this.Title = fileName;



                    //   mediaPlayer1.Play();

                }
            }

           
        }
        /*
        public void btnPause_Click(object sender, RoutedEventArgs e)
        {
            if (mediaPlayer1.HasVideo)
            {

                if (mediaPlayer1.IsLoaded)
                {

                    mediaPlayer1.Pause();

                    timerVideoTime.Stop();

                    btnPlay.IsEnabled = true;
                    btnPause.IsEnabled = false;
                    btnStop.IsEnabled = false;




                    timerVideoTime.IsEnabled = False;

                     

                }

            }
        }
        */
        private void btnStop_Click(object sender, RoutedEventArgs e)
        {
            if (mediaPlayer1.HasVideo)
            {

                mediaPlayer1.Stop();
                btnPlay.IsEnabled = true;
                //btnPause.IsEnabled = false;
                btnStop.IsEnabled = false;


                TimeLine.Value = 0;

                // Create a timer that will update the counters and the time slider
                timerVideoTime = new DispatcherTimer();
                timerVideoTime.Interval = TimeSpan.FromSeconds(1);
                timerVideoTime.Tick += timer_Tick;
                timerVideoTime.Start();

                cur_sec = 0;
                ts2.Text = "00:00:00";

            }
        }

       
        private void MediaPlayer_MediaOpened(object sender, RoutedEventArgs e)
        {

            // TimeLine.Maximum = mediaPlayer1.NaturalDuration.TimeSpan.TotalMilliseconds;
            TimeLine.Maximum = mediaPlayer1.NaturalDuration.TimeSpan.TotalSeconds;
            TotalTime = new TimeSpan(0, 0, (int)mediaPlayer1.NaturalDuration.TimeSpan.TotalSeconds);
            //TimeSpan Total = new TimeSpan(0, 0, mediaPlayer1.NaturalDuration.TimeSpan.TotalSeconds);

            //btnPlay.IsEnabled = true;
            //btnPause.IsEnabled = true;
            btnStop.IsEnabled = true;

            tst.Text = TotalTime.ToString();

            mediaPlayer1.Volume = 0.5;
            slider.Value = mediaPlayer1.Volume*100;


            TimeLine.Value = 0;

            // ts2.Text = TimeLine.Value.ToString();
            ts2.Text = "00:00:00";


        }

        private void mediaPlayer1_MouseWheel(object sender, MouseWheelEventArgs e)
        {
            mediaPlayer1.Volume += (double) e.Delta/1000;
            slider.Value += (double)e.Delta/1000;
            gVolume = mediaPlayer1.Volume;

        }
        



        private void TimeLine_MouseDown(object sender, MouseButtonEventArgs e)
        {
            double MousePosition = e.GetPosition(TimeLine).X;
            TimeLine.Value = SetProgressBarValue(MousePosition);
            //MessageBox.Show("works");
            cur_sec = (int)TimeLine.Value;
            mediaPlayer1.Position = new TimeSpan(0, 0, 0, cur_sec, 0);



        }

        private void progressBar1_MouseDown(object sender, MouseButtonEventArgs e)
        {
            double MousePosition = e.GetPosition(slider).X;
            //slider.Value = SetProgressBarValue(MousePosition);
            //MessageBox.Show("works");
            //cur_sec = (int)TimeLine.Value;
            //mediaPlayer1.Position = new TimeSpan(0, 0, 0, cur_sec, 0);



        }

        private double SetProgressBarValue(double MousePosition)
        {
            double ratio = MousePosition / TimeLine.ActualWidth;
            double ProgressBarValue = ratio * TimeLine.Maximum;
            return ProgressBarValue;
        }









        public bool False { get; set; }

        private void slider_Scroll(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            mediaPlayer1.Volume = (double)e.NewValue;
        }

      
        
    }
}
