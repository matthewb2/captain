using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.Diagnostics;
using System.IO;
using System.Net;
using System.Threading;



namespace CSDownload
{
    public partial class Form1 : Form
    {
        // The thread inside which the download happens
        private Thread thrDownload;
        // The stream of data retrieved from the web server
        private Stream strResponse;
        // The stream of data that we write to the harddrive
        private Stream strLocal;
        // The request to the web server for file information
        private HttpWebRequest webRequest;
        // The response from the web server containing information about the file
        private HttpWebResponse webResponse;
        // The progress of the download in percentage
        private static int PercentProgress;
        // The delegate which we will call from the thread to update the form
        private delegate void UpdateProgessCallback(Int64 BytesRead, Int64 TotalBytes);
        string path;

        public Form1()
        {
            InitializeComponent();
        }

        

        private void UpdateProgress(Int64 BytesRead, Int64 TotalBytes)
        {
            // Calculate the download progress in percentages
            PercentProgress = Convert.ToInt32((BytesRead * 100) / TotalBytes);
            // Make progress on the progress bar
            prgDownload.Value = PercentProgress;
            // Display the current progress on the form
            lblDownload.Text = "Downloaded " + BytesRead + " out of " + TotalBytes + " (" + PercentProgress + "%)";
        }

        private void Download()
        {
            using (WebClient wcDownload = new WebClient())
            {
                try
                {
                    // Create a request to the file we are downloading
                    webRequest = (HttpWebRequest)WebRequest.Create(txtUrl.Text);
                    // Set default authentication for retrieving the file
                    webRequest.Credentials = CredentialCache.DefaultCredentials;
                    // Retrieve the response from the server
                    webResponse = (HttpWebResponse)webRequest.GetResponse();
                    // Ask the server for the file size and store it
                    Int64 fileSize = webResponse.ContentLength;

                    // txtPath.Text = "C:\\temp\\";
                    Uri uri = new Uri(txtUrl.Text);
                    string filename = System.IO.Path.GetFileName(uri.LocalPath);
                    // Open the URL for download
                    strResponse = wcDownload.OpenRead(txtUrl.Text);
                    // Create a new file stream where we will be saving the data (local drive)
                    // strLocal = new FileStream("C:\\temp\\"+ filename, FileMode.Create, FileAccess.Write, FileShare.None);
                    strLocal = new FileStream(path + filename, FileMode.Create, FileAccess.Write, FileShare.None);

                    // It will store the current number of bytes we retrieved from the server
                    int bytesSize = 0;
                    // A buffer for storing and writing the data retrieved from the server
                    byte[] downBuffer = new byte[2048];

                    // Loop through the buffer until the buffer is empty
                    while ((bytesSize = strResponse.Read(downBuffer, 0, downBuffer.Length)) > 0)
                    {
                        // Write the data from the buffer to the local hard drive
                        strLocal.Write(downBuffer, 0, bytesSize);
                        // Invoke the method that updates the form's label and progress bar
                        this.Invoke(new UpdateProgessCallback(this.UpdateProgress), new object[] { strLocal.Length, fileSize });
                    }
                }
                finally
                {
                    // When the above code has ended, close the streams
                    strResponse.Close();
                    strLocal.Close();
                }
            }
        }

      

        private void btnDownload_Click_1(object sender, EventArgs e)
        {
            // Let the user know we are connecting to the server
            lblDownload.Text = "Download Starting";
            // Create a new thread that calls the Download() method
            thrDownload = new Thread(Download);
            // Start the thread, and thus call Download()
            thrDownload.Start();
        }

        private void btnStop_Click_1(object sender, EventArgs e)
        {
            // Close the web response and the streams
            webResponse.Close();
            strResponse.Close();
            strLocal.Close();
            // Abort the thread that's downloading
            thrDownload.Abort();
            // Set the progress bar back to 0 and the label
            prgDownload.Value = 0;
            lblDownload.Text = "Download Stopped";
        }

        private void btnLocation_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog folderDlg = new FolderBrowserDialog();

            folderDlg.ShowNewFolderButton = true;

            // Show the FolderBrowserDialog.

            DialogResult result = folderDlg.ShowDialog();

            if (result == DialogResult.OK)

            {

                path = folderDlg.SelectedPath;

                txtPath.Text = path;

                //  Environment.SpecialFolder root = folderDlg.RootFolder;

            }
        }
    }



}
