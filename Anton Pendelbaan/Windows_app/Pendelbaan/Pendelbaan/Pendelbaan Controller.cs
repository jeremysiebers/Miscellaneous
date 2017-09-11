using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Pendelbaan
{
    public delegate void ReceivedCharCallback(string text);

    public interface iForm1
    {
        void ReceivedChar(string text);
    }

    public partial class Form1 : Form, iForm1
    {
        
        public Form1()
        {
            InitializeComponent();
            SerialPortInterface Serial = new SerialPortInterface();
            Serial.Open(this);
        }

        public void ReceivedChar(string text)
        {
            if (SerialRead.InvokeRequired)
            {
                ReceivedCharCallback d = new ReceivedCharCallback(ReceivedChar);
                SerialRead.Invoke(d, new object[] { text });
            }
            else
            {
                SerialRead.AppendText(text);
                SerialRead.AppendText(Environment.NewLine);
            }
            
        }
    }
}
