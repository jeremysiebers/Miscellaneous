using System;
using System.IO;
using System.IO.Ports;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Windows.Forms;
using System.Threading.Tasks;

namespace Pendelbaan
{
    /// <summary> 
    /// Interfaces with a serial port. There should only be one instance 
    /// of this class for each serial port to be used. 
    /// </summary> 
    public class SerialPortInterface
    {
        public iForm1 m_iForm1;
        private SerialPort _serialPort = new SerialPort();
        private int _baudRate = 19200;
        private int _dataBits = 8;
        private Handshake _handshake = Handshake.None;
        private Parity _parity = Parity.None;
        private string _portName = "COM1";
        private StopBits _stopBits = StopBits.One;

        private bool ClosePort = false;

        /// <summary> 
        /// Holds data received until we get a terminator. 
        /// </summary> 
        private string tString = string.Empty;
        /// <summary> 
        /// End of transmition byte in this case EOT (ASCII 4). 
        /// </summary> 
        //private byte _terminator = 0x4;

        public int BaudRate { get { return _baudRate; } set { _baudRate = value; } }
        public int DataBits { get { return _dataBits; } set { _dataBits = value; } }
        public Handshake Handshake { get { return _handshake; } set { _handshake = value; } }
        public Parity Parity { get { return _parity; } set { _parity = value; } }
        public string PortName { get { return _portName; } set { _portName = value; } }

        public void Open(iForm1 iForm1Ctrl)
        {
            m_iForm1 = iForm1Ctrl;
            _serialPort.BaudRate = _baudRate;
            _serialPort.DataBits = _dataBits;
            _serialPort.Handshake = _handshake;
            _serialPort.Parity = _parity;
            _serialPort.PortName = _portName;
            _serialPort.StopBits = _stopBits;

            _serialPort.Open();

            /*
            byte[] buffer = new byte[20];
            Action kickoffRead = null;            
                kickoffRead = delegate { _serialPort.BaseStream.BeginRead(buffer, 0, buffer.Length, delegate (IAsyncResult ar)
                    {
                        try
                        {
                            if (_serialPort.IsOpen == true)
                            {
                                int actualLength = _serialPort.BaseStream.EndRead(ar);
                                byte[] received = new byte[actualLength];
                                Buffer.BlockCopy(buffer, 0, received, 0, actualLength);
                                raiseAppSerialDataEvent(received);
                                Array.Clear(buffer, 0, buffer.Length);
                            }
                        }
                        catch (IOException exc)
                        {
                            handleAppSerialError(exc);
                        }
                        if (_serialPort.IsOpen == true)
                        {
                            kickoffRead();
                        }
                    }, null);
                };
            if (_serialPort.IsOpen == true)
            {
                kickoffRead();
            }   */

            var cancelToken = new CancellationTokenSource();
            Task.Factory.StartNew(() => ReadSerialBytesAsync(cancelToken.Token)) ;
        }

        private async Task ReadSerialBytesAsync(CancellationToken ct)
        {
            while ((!ct.IsCancellationRequested) && (_serialPort.IsOpen))
            {
                try
                {
                    _serialPort.BaseStream.ReadTimeout = 0;
                    var bytesToRead = 1024;
                    var receiveBuffer = new byte[bytesToRead];
                    var numBytesRead = await _serialPort.BaseStream.ReadAsync(receiveBuffer, 0, bytesToRead, ct);

                    var bytesReceived = new byte[numBytesRead];
                    Array.Copy(receiveBuffer, bytesReceived, numBytesRead);

                    // Here is where I audit the received data.
                    // the NewSerialData event handler displays the 
                    // data received (as hex bytes) and writes it to disk.
                    raiseAppSerialDataEvent(bytesReceived);                    
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error in ReadSerialBytesAsync: " + ex.ToString());
                    throw;
                }
            }
        }

        public void Close()
        {            
            _serialPort.Close();
            //_serialPort.BaseStream.Dispose();
        }
        
        private void raiseAppSerialDataEvent(byte[] received)
        {
            tString += Encoding.ASCII.GetString(received);
            Console.WriteLine(tString);
            Console.WriteLine("-------------------------------------------------------------------------");


            if (tString.IndexOf("M#") > 0)
            {                
                int j = 0;
                int Api = 0;
                int Value = 0;
                string[] numbers = Regex.Split(tString, @"\D+");
                foreach (string value in numbers)
                {
                    if (!string.IsNullOrEmpty(value))
                    {
                        int i = int.Parse(value);
                        //Console.WriteLine("Number: {0}", i);
                        if (j == 0)
                        {
                            Api = i;
                            j = 1;
                        }
                        else if (j == 1)
                        {
                            Value = i;
                            j = 2;
                        }
                    }
                }

                if (Api != 0)
                {
                    m_iForm1.ReceivedData(Api, Value);
                }

            }

            tString = "";
        }

        private void handleAppSerialError(IOException exc)
        {
            
        }
    }
}
