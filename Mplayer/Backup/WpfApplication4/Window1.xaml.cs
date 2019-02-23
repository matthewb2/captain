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

namespace WpfApplication4
{
    /// <summary>
    /// Window1.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class Window1 : Window
    {
        public Window1()
        {
            InitializeComponent();
        }

        private void btnBrowse_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog ofd = new Microsoft.Win32.OpenFileDialog();

            if (ofd.ShowDialog().Value)
            {

                string fileName = ofd.FileName;

                mediaPlayer1.Source = new Uri(fileName);

                mediaPlayer1.Play();

            }
        }

        private void btnPlay_Click(object sender, RoutedEventArgs e)
        {
            if (mediaPlayer1.HasVideo)
            {

                mediaPlayer1.Play();

            }
        }

        private void btnPause_Click(object sender, RoutedEventArgs e)
        {
            if (mediaPlayer1.HasVideo)
            {

                if (mediaPlayer1.IsLoaded)
                {

                    mediaPlayer1.Pause();

                }

            }
        }

        private void btnStop_Click(object sender, RoutedEventArgs e)
        {
            if (mediaPlayer1.HasVideo)
            {

                mediaPlayer1.Stop();

            }
        }
    }
}
