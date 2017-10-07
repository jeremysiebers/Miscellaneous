using System;
using System.IO;
using System.IO.Ports;
using System.Text;

namespace Pendelbaan
{
    /// <summary> 
    /// Interfaces with a serial port. There should only be one instance 
    /// of this class for each serial port to be used. 
    /// </summary> 
    class SerialPortInterface
    {
        public iForm1 m_iForm1;
        private SerialPort _serialPort = new SerialPort();
        private int _baudRate = 19200;
        private int _dataBits = 8;
        private Handshake _handshake = Handshake.None;
        private Parity _parity = Parity.None;
        private string _portName = "COM4";
        private StopBits _stopBits = StopBits.One;

        /// <summary> 
        /// Holds data received until we get a terminator. 
        /// </summary> 
        private string tString = string.Empty;
        /// <summary> 
        /// End of transmition byte in this case EOT (ASCII 4). 
        /// </summary> 
        private byte _terminator = 0x4;

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
                
                byte[] buffer = new byte[8];
                Action kickoffRead = null;
                kickoffRead = delegate {
                    _serialPort.BaseStream.BeginRead(buffer, 0, buffer.Length, delegate (IAsyncResult ar) {
                        try
                        {
                            int actualLength = _serialPort.BaseStream.EndRead(ar);
                            byte[] received = new byte[actualLength];
                            Buffer.BlockCopy(buffer, 0, received, 0, actualLength);
                            raiseAppSerialDataEvent(received);
                            Array.Clear(buffer, 0, buffer.Length);
                        }
                        catch (IOException exc)
                        {
                            handleAppSerialError(exc);
                        }
                        kickoffRead();
                    }, null);
                };
                kickoffRead();            
        }
        
        private void raiseAppSerialDataEvent(byte[] received)
        {
            tString += Encoding.ASCII.GetString(received);
            Console.WriteLine(tString);
            m_iForm1.ReceivedChar(tString);
            tString = "";
        }

        private void handleAppSerialError(IOException exc)
        {
            
        }
    }
}
