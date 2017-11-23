using System;
using System.Windows.Forms;
using System.IO.Ports;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Threading;
using System.Drawing;

namespace Pendelbaan
{
    public delegate void ReceivedDataCallback(int Api, int Value);

    public interface iForm1
    {
        void ReceivedData(int Api, int Value);
    }

    /*#--------------------------------------------------------------------------#*/
    /*  Description: Main Class
     *
     *  Input(s)   :
     *
     *  Output(s)  :
     *
     *  Returns    :
     *
     *  Pre.Cond.  :
     *
     *  Post.Cond. :
     *
     *  Notes      :
     */
    /*#--------------------------------------------------------------------------#*/
    public partial class Form1 : Form, iForm1
    {
        public SerialPortExample serialPort;
        static System.Windows.Forms.Timer myTimer = new System.Windows.Forms.Timer();
        public Image tandrad = Pendelbaan.Properties.Resources.tandrad_str_str;
        public int SetPwm;

        #region Variables
        int api_size = 0;
        int watchdog = 0;
        int train_wait_time = 0;
        int junction_wait_time = 0;
        int lights_on_wait_time = 0;
        int stationary_left = 0;
        int stationary_right = 0;
        int max_pwm_right = 0;
        int max_pwm_left = 0;
        int max_jerk_pwm_brake = 0;
        int max_jerk_pwm = 0;
        int input_debounce = 0;
        int rc_rb = 0;
        int rc_rf = 0;
        int rc_lb = 0;
        int rc_lf = 0;
        int btn_start = 0;
        int btn_stop = 0;
        int btn_mid = 0;
        int btn_lb = 0;
        int btn_lf = 0;
        int btn_rb = 0;
        int btn_rf = 0;
        int train1_pos = 0;
        int train2_pos = 0;
        int rc_lmu = 0;
        int rc_lmd = 0;
        int rc_rmu = 0;
        int rc_rmd = 0;
        int max_pwm_rmu_right = 0;
        int max_pwm_rmu_left = 0;
        int max_pwm_rmd_right = 0;
        int max_pwm_rmd_left = 0;
        int max_pwm_lmu_right = 0;
        int max_pwm_lmu_left = 0;
        int max_pwm_lmd_right = 0;
        int max_pwm_lmd_left = 0;
        int delay_rmu_down = 0;
        int delay_rmu_up = 0;
        int delay_rmd_down = 0;
        int delay_rmd_up = 0;
        int delay_lmd_down = 0;
        int delay_lmd_up = 0;
        int delay_lmu_down = 0;
        int delay_lmu_up = 0;
        int train_path_from = 0;
        int train_path_to = 0;
        int main_program = 0;
        int junction_left_str = 1;
        int junction_left_bnd = 0;
        int junction_right_str = 1;
        int junction_right_bnd = 0;
        int actual_pwm_speed = 0;
        int pwm_brake = 0;
        int sw_start = 0;
        int sw_stop = 0;
        int sw_reset = 0;
        int sw_junction_left_str = 0;
        int sw_junction_left_bnd = 0;
        int sw_junction_right_str = 0;
        int sw_junction_right_bnd = 0;
        int sw_pwm_brake_on = 0;
        int sw_pwm_brake_off = 0;
        int sw_actual_pwm_speed = 0;
        int switch_program = 0;
        int junction_left_str_prev = 1;
        int junction_left_bnd_prev = 0;
        int junction_right_str_prev = 1;
        int junction_right_bnd_prev = 0;
        int pwm_direction = 0;
        #endregion Variables

        #region Indicator init
        public Form1()
        {
            InitializeComponent();

            serialPort = new SerialPortExample("COM4", "\r\n", 900000);


            string[] ports = SerialPort.GetPortNames();
            foreach (string port in ports) {
                this.comPoortToolStripMenuItem.Items.Add(port);
            }
            this.comPoortToolStripMenuItem.SelectedItem = this.comPoortToolStripMenuItem.Items[0];


            pictureBox1.Image = Pendelbaan.Properties.Resources.tandrad_str_str;

            ManPwm.Minimum = -255;
            ManPwm.Maximum = 255;
            ManPwm.MouseLeave += ManPwm_Moved;
            SetPwm = ManPwm.Value;


            /* Adds the event and the event handler for the method that will 
            process the timer event to the timer. */
            myTimer.Tick += new EventHandler(TimerEventProcessor);

            // Sets the timer interval to 1 seconds.
            myTimer.Interval = 1000;
            myTimer.Start();
        }

        private void ManPwm_Moved(object sender, EventArgs e)
        {
            if (main_program == 1)
            {
                if(ManPwm.Value > 0 && SetPwm != ManPwm.Value)
                {
                    SetPwm = ManPwm.Value;
                    serialPort.Send("sx81x1G", false);
                    //Thread.Sleep(50);
                    serialPort.Send("sx79x" + ManPwm.Value.ToString() + "G", false);
                }
                else if(ManPwm.Value < 0 && SetPwm != ManPwm.Value)
                {
                    SetPwm = ManPwm.Value;
                    var left = SetPwm * -1;
                    serialPort.Send("sx81x0G", false);
                    //Thread.Sleep(50);
                    serialPort.Send("sx79x" + left.ToString() + "G", false);
                }
                
            }
        }

        /*#--------------------------------------------------------------------------#*/
        /*  Description: Show received character from uController
         *
         *  Input(s)   :
         *
         *  Output(s)  :
         *
         *  Returns    :
         *
         *  Pre.Cond.  :
         *
         *  Post.Cond. :
         *
         *  Notes      :
         */
        /*#--------------------------------------------------------------------------#*/
        public void ReceivedData(int Api, int Value)
        {            
            if (SerialRead.InvokeRequired)
            {
                ReceivedDataCallback d = new ReceivedDataCallback(ReceivedData);
                SerialRead.Invoke(d, new object[] { Api, Value });
            }
            else
            {
                progressBar1.Value += 1;
                if (progressBar1.Value > 99)
                {
                    progressBar1.Value = 0;
                }

                SerialRead.AppendText(Api.ToString() + " " + Value.ToString() + Environment.NewLine);

                switch (Api)
                {
                    case API.API_SIZE: api_size = Value; break;
                    case API.WATCHDOG: watchdog = Value; break;
                    case API.TRAIN_WAIT_TIME: train_wait_time = Value; break;
                    case API.JUNCTION_WAIT_TIME: junction_wait_time = Value; break;
                    case API.LIGHTS_ON_WAIT_TIME: lights_on_wait_time = Value; break;
                    case API.STATIONARY_LEFT: stationary_left = Value; break;
                    case API.STATIONARY_RIGHT: stationary_right = Value; break;
                    case API.MAX_PWM_RIGHT: max_pwm_right = Value; break;
                    case API.MAX_PWM_LEFT: max_pwm_left = Value; break;
                    case API.MAX_JERK_PWM_BRAKE: max_jerk_pwm_brake = Value; break;
                    case API.MAX_JERK_PWM: max_jerk_pwm = Value; break;
                    case API.INPUT_DEBOUNCE: input_debounce = Value; break;

                    case API.RC_RB:
                        rc_rb = Value;
                        if (rc_rb == 1)
                        {
                            RcRb.BackColor = System.Drawing.Color.LimeGreen;
                        }
                        else
                        {
                            RcRb.BackColor = System.Drawing.Color.LightGray;
                        }
                        break;

                    case API.RC_RF:
                        rc_rf = Value;
                        if (rc_rf == 1)
                        {
                            RcRf.BackColor = System.Drawing.Color.LimeGreen;
                        }
                        else
                        {
                            RcRf.BackColor = System.Drawing.Color.LightGray;
                        }
                        break;

                    case API.RC_LB:
                        rc_lb = Value;
                        if (rc_lb == 1)
                        {
                            RcLb.BackColor = System.Drawing.Color.LimeGreen;
                        }
                        else
                        {
                            RcLb.BackColor = System.Drawing.Color.LightGray;
                        }
                        break;

                    case API.RC_LF:
                        rc_lf = Value;
                        if (rc_lf == 1)
                        {
                            RcLf.BackColor = System.Drawing.Color.LimeGreen;
                        }
                        else
                        {
                            RcLf.BackColor = System.Drawing.Color.LightGray;
                        }
                        break;

                    case API.BTN_START: btn_start = Value; break;
                    case API.BTN_STOP: btn_stop = Value; break;
                    case API.BTN_MID: btn_mid = Value; break;
                    case API.BTN_LB: btn_lb = Value; break;
                    case API.BTN_LF: btn_lf = Value; break;
                    case API.BTN_RB: btn_rb = Value; break;
                    case API.BTN_RF: btn_rf = Value; break;
                    case API.TRAIN1_POS: train1_pos = Value; break;
                    case API.TRAIN2_POS: train2_pos = Value; break;

                    case API.RC_LMU:
                        rc_lmu = Value;
                        if (rc_lmu == 1)
                        {
                            RcLmu.BackColor = System.Drawing.Color.LimeGreen;
                        }
                        else
                        {
                            RcLmu.BackColor = System.Drawing.Color.LightGray;
                        }
                        break;
                    case API.RC_LMD:
                        rc_lmd = Value;
                        if (rc_lmd == 1)
                        {
                            RcLmd.BackColor = System.Drawing.Color.LimeGreen;
                        }
                        else
                        {
                            RcLmd.BackColor = System.Drawing.Color.LightGray;
                        }
                        break;
                    case API.RC_RMU:
                        rc_rmu = Value;
                        if (rc_rmu == 1)
                        {
                            RcRmu.BackColor = System.Drawing.Color.LimeGreen;
                        }
                        else
                        {
                            RcRmu.BackColor = System.Drawing.Color.LightGray;
                        }
                        break;
                    case API.RC_RMD:
                        rc_rmd = Value;
                        if (rc_rmd == 1)
                        {
                            RcRmd.BackColor = System.Drawing.Color.LimeGreen;
                        }
                        else
                        {
                            RcRmd.BackColor = System.Drawing.Color.LightGray;
                        }
                        break;

                    case API.MAX_PWM_RMU_RIGHT: max_pwm_rmu_right = Value; break;
                    case API.MAX_PWM_RMU_LEFT: max_pwm_rmu_left = Value; break;
                    case API.MAX_PWM_RMD_RIGHT: max_pwm_rmd_right = Value; break;
                    case API.MAX_PWM_RMD_LEFT: max_pwm_rmd_left = Value; break;
                    case API.MAX_PWM_LMU_RIGHT: max_pwm_lmu_right = Value; break;
                    case API.MAX_PWM_LMU_LEFT: max_pwm_lmu_left = Value; break;
                    case API.MAX_PWM_LMD_RIGHT: max_pwm_lmd_right = Value; break;
                    case API.MAX_PWM_LMD_LEFT: max_pwm_lmd_left = Value; break;
                    case API.DELAY_RMU_DOWN: delay_rmu_down = Value; break;
                    case API.DELAY_RMU_UP: delay_rmu_up = Value; break;
                    case API.DELAY_RMD_DOWN: delay_rmd_down = Value; break;
                    case API.DELAY_RMD_UP: delay_rmd_up = Value; break;
                    case API.DELAY_LMD_DOWN: delay_lmd_down = Value; break;
                    case API.DELAY_LMD_UP: delay_lmd_up = Value; break;
                    case API.DELAY_LMU_DOWN: delay_lmu_down = Value; break;
                    case API.DELAY_LMU_UP: delay_lmu_up = Value; break;
                    case API.TRAIN_PATH_FROM: train_path_from = Value; break;
                    case API.TRAIN_PATH_TO: train_path_to = Value; break;

                    case API.MAIN_PROGRAM:
                        main_program = Value;
                        if (main_program == 1)
                        {
                            JunctionLeftBtn.Enabled = true;
                            JunctionRightBtn.Enabled = true;
                        }
                        else if (main_program == 2 || main_program == 3)
                        {
                            JunctionLeftBtn.Enabled = false;
                            JunctionRightBtn.Enabled = false;
                        }
                        break;

                    case API.JUNCTION_LEFT_STR:
                        junction_left_str = Value;
                        if (junction_left_str == 1)
                        {
                            JunctionLeftBtn.Text = "Rechtdoor";                            
                        }
                        break;
                    case API.JUNCTION_LEFT_BND:
                        junction_left_bnd = Value;
                        if (junction_left_bnd == 1)
                        {
                            JunctionLeftBtn.Text = "Afbuigen";                            
                        }
                        break;
                    case API.JUNCTION_RIGHT_STR:
                        junction_right_str = Value;
                        if (junction_right_str == 1)
                        {
                            JunctionRightBtn.Text = "Rechtdoor";                            
                        }
                        break;
                    case API.JUNCTION_RIGHT_BND:
                        junction_right_bnd = Value;
                        if (junction_right_bnd == 1)
                        {
                            JunctionRightBtn.Text = "Afbuigen";                            
                        }
                        break;

                    case API.ACTUAL_PWM_SPEED: actual_pwm_speed = Value; break;
                    case API.PWM_BRAKE: pwm_brake = Value; break;
                    case API.SW_START: sw_start = Value; break;
                    case API.SW_STOP: sw_stop = Value; break;
                    case API.SW_RESET: sw_reset = Value; break;
                    case API.SW_JUNCTION_LEFT_STR: sw_junction_left_str = Value; break;
                    case API.SW_JUNCTION_LEFT_BND: sw_junction_left_bnd = Value; break;
                    case API.SW_JUNCTION_RIGHT_STR: sw_junction_right_str = Value; break;
                    case API.SW_JUNCTION_RIGHT_BND: sw_junction_right_bnd = Value; break;
                    case API.SW_PWM_BRAKE_ON: sw_pwm_brake_on = Value; break;
                    case API.SW_PWM_BRAKE_OFF: sw_pwm_brake_off = Value; break;
                    case API.SW_ACTUAL_PWM_SPEED: sw_actual_pwm_speed = Value; break;
                    case API.SWITCH_PROGRAM: switch_program = Value; break;

                    case API.JUNCTION_LEFT_STR_PREV:
                        junction_left_str_prev = Value;
                        if (junction_left_str_prev == 1)
                        {
                            junction_left_bnd_prev = 0;
                        }
                        UpdatePicture();
                        break;
                    case API.JUNCTION_LEFT_BND_PREV:
                        junction_left_bnd_prev = Value;
                        if (junction_left_bnd_prev == 1)
                        {
                            junction_left_str_prev = 0;
                        }
                        UpdatePicture();
                        break;
                    case API.JUNCTION_RIGHT_STR_PREV:
                        junction_right_str_prev = Value;
                        if (junction_right_str_prev == 1)
                        {
                            junction_right_bnd_prev = 0;
                        }
                        UpdatePicture();
                        break;
                    case API.JUNCTION_RIGHT_BND_PREV:
                        junction_right_bnd_prev = Value;
                        if (junction_right_bnd_prev == 1)
                        {
                            junction_right_str_prev = 0;
                        }
                        UpdatePicture();
                        break;

                    case API.PWM_DIRECTION: pwm_direction = Value; break;

                    default:
                        break;
                }

                


            }

        }

        private void UpdatePicture()
        {
            if (junction_left_str_prev == 1 && junction_right_str_prev == 1)
            {
                pictureBox1.Image = Pendelbaan.Properties.Resources.tandrad_str_str;
            }
            else if (junction_left_bnd_prev == 1 && junction_right_bnd_prev == 1)
            {
                pictureBox1.Image = Pendelbaan.Properties.Resources.tandrad_bnd_bnd;
            }
            else if (junction_left_str_prev == 1 && junction_right_bnd_prev == 1)
            {
                pictureBox1.Image = Pendelbaan.Properties.Resources.tandrad_str_bnd;
            }
            else if (junction_left_bnd_prev == 1 && junction_right_str_prev == 1)
            {
                pictureBox1.Image = Pendelbaan.Properties.Resources.tandrad_bnd_str;
            }
        }

        /*#--------------------------------------------------------------------------#*/
        /*  Description: Exit tag in pulldown menu
         *
         *  Input(s)   :
         *
         *  Output(s)  :
         *
         *  Returns    :
         *
         *  Pre.Cond.  :
         *
         *  Post.Cond. :
         *
         *  Notes      :
         */
        /*#--------------------------------------------------------------------------#*/
        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //Serial.Close();
            this.Close();
        }


        /*#--------------------------------------------------------------------------#*/
        /*  Description: maakVerbindingToolStripMenuItem_Click
         *
         *  Input(s)   :
         *
         *  Output(s)  :
         *
         *  Returns    :
         *
         *  Pre.Cond.  :
         *
         *  Post.Cond. :
         *
         *  Notes      :
         */
        /*#--------------------------------------------------------------------------#*/

        private void maakVerbindingToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string port = (string)comPoortToolStripMenuItem.SelectedItem;
            
            serialPort.PortName = port;

            if (maakVerbindingToolStripMenuItem.Text == "Maak Verbinding")
            {   
                try
                {
                    serialPort.Open();
                    comPoortToolStripMenuItem.Enabled = false;
                    maakVerbindingToolStripMenuItem.Enabled = false;
                    ReadAllData();
                    Task.Factory.StartNew(HardwareReadout);                    
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Fout bij openen van " + (string)comPoortToolStripMenuItem.SelectedItem);
                }
            }            
        }

        /*#--------------------------------------------------------------------------#*/
        /*  Description: private void HardwareReadout()
         *
         *  Input(s)   :
         *
         *  Output(s)  :
         *
         *  Returns    :
         *
         *  Pre.Cond.  :
         *
         *  Post.Cond. :
         *
         *  Notes      :
         */
        /*#--------------------------------------------------------------------------#*/
        private void HardwareReadout()
        {
            try
            {
                while (true)
                {
                    RawData(serialPort.Read());
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), "Receiver error");
            }
        }

        /*#--------------------------------------------------------------------------#*/
        /*  Description: private void ReadAllData()
         *
         *  Input(s)   :
         *
         *  Output(s)  :
         *
         *  Returns    :
         *
         *  Pre.Cond.  :
         *
         *  Post.Cond. :
         *
         *  Notes      :
         */
        /*#--------------------------------------------------------------------------#*/
        private void ReadAllData()
        {
            for (int i = 16; i < 87; i++)
            {
                RawData(serialPort.Send("gx"+ i.ToString() + "G", true));
                Thread.Sleep(50);
            }
            
        }

        /*#--------------------------------------------------------------------------#*/
        /*  Description: private static void TimerEventProcessor(Object myObject, EventArgs myEventArgs)
         *
         *  Input(s)   :
         *
         *  Output(s)  :
         *
         *  Returns    :
         *
         *  Pre.Cond.  :
         *
         *  Post.Cond. :
         *
         *  Notes      :
         */
        /*#--------------------------------------------------------------------------#*/
        private static void TimerEventProcessor(Object myObject, EventArgs myEventArgs)
        {
            myTimer.Stop();


            myTimer.Enabled = true;

        }

        #endregion Indicator init

        /*#--------------------------------------------------------------------------#*/
        /*  Description: private async Task startread(CancellationToken ct)
         *
         *  Input(s)   :
         *
         *  Output(s)  :
         *
         *  Returns    :
         *
         *  Pre.Cond.  :
         *
         *  Post.Cond. :
         *
         *  Notes      :
         */
        /*#--------------------------------------------------------------------------#*/
        public void RawData(string tString)
        {

            if (tString != string.Empty && tString != null)
            {
                //tString += Encoding.ASCII.GetString(received);
                //Console.WriteLine(tString);
                //Console.WriteLine("-------------------------------------------------------------------------");


                if (tString.IndexOf("M#") == 0)
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
                        ReceivedData(Api, Value);
                    }

                }

                tString = "";
            }

        }

        /*#--------------------------------------------------------------------------#*/
        /*  Description: Buttons
         *
         *  Input(s)   :
         *
         *  Output(s)  :
         *
         *  Returns    :
         *
         *  Pre.Cond.  :
         *
         *  Post.Cond. :
         *
         *  Notes      :
         */
        /*#--------------------------------------------------------------------------#*/
        private void JunctionLeftBtn_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                if (JunctionLeftBtn.Text == "Rechtdoor")
                {
                    serialPort.Send("sx74x1G", false);
                    //serialPort.Send("sx74x0G", false);
                    JunctionLeftBtn.Text = "Afbuigen";
                }
                else
                {
                    serialPort.Send("sx73x1G", false);
                    //serialPort.Send("sx73x0G", false);
                    JunctionLeftBtn.Text = "Rechtdoor";
                }
            }          
        }

        private void JunctionRightBtn_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                if (JunctionRightBtn.Text == "Rechtdoor")
                {
                    serialPort.Send("sx76x1G", false);
                    //serialPort.Send("sx76x0G", false);
                    JunctionRightBtn.Text = "Afbuigen";
                }
                else
                {
                    serialPort.Send("sx75x1G", false);
                    //serialPort.Send("sx75x0G", false);
                    JunctionRightBtn.Text = "Rechtdoor";
                }
            }
        }
    }



    /*#--------------------------------------------------------------------------#*/
    /*  Description: static class API
     *
     *  Input(s)   :
     *
     *  Output(s)  :
     *
     *  Returns    :
     *
     *  Pre.Cond.  :
     *
     *  Post.Cond. :
     *
     *  Notes      :
     */
    /*#--------------------------------------------------------------------------#*/
    static class API
    {
        public const int API_SIZE = 16;
        public const int WATCHDOG = 17;
        public const int TRAIN_WAIT_TIME = 18;
        public const int JUNCTION_WAIT_TIME = 19;
        public const int LIGHTS_ON_WAIT_TIME = 20;
        public const int STATIONARY_LEFT = 21;
        public const int STATIONARY_RIGHT = 22;
        public const int MAX_PWM_RIGHT = 23;
        public const int MAX_PWM_LEFT = 24;
        public const int MAX_JERK_PWM_BRAKE = 25;
        public const int MAX_JERK_PWM = 26;
        public const int INPUT_DEBOUNCE = 27;
        public const int RC_RB = 28;
        public const int RC_RF = 29;
        public const int RC_LB = 30;
        public const int RC_LF = 31;
        public const int BTN_START = 32;
        public const int BTN_STOP = 33;
        public const int BTN_MID = 34;
        public const int BTN_LB = 35;
        public const int BTN_LF = 36;
        public const int BTN_RB = 37;
        public const int BTN_RF = 38;
        public const int TRAIN1_POS = 39;
        public const int TRAIN2_POS = 40;
        public const int RC_LMU = 41;
        public const int RC_LMD = 42;
        public const int RC_RMU = 43;
        public const int RC_RMD = 44;
        public const int MAX_PWM_RMU_RIGHT = 45;
        public const int MAX_PWM_RMU_LEFT = 46;
        public const int MAX_PWM_RMD_RIGHT = 47;
        public const int MAX_PWM_RMD_LEFT = 48;
        public const int MAX_PWM_LMU_RIGHT = 49;
        public const int MAX_PWM_LMU_LEFT = 50;
        public const int MAX_PWM_LMD_RIGHT = 51;
        public const int MAX_PWM_LMD_LEFT = 52;
        public const int DELAY_RMU_DOWN = 53;
        public const int DELAY_RMU_UP = 54;
        public const int DELAY_RMD_DOWN = 55;
        public const int DELAY_RMD_UP = 56;
        public const int DELAY_LMD_DOWN = 57;
        public const int DELAY_LMD_UP = 58;
        public const int DELAY_LMU_DOWN = 59;
        public const int DELAY_LMU_UP = 60;
        public const int TRAIN_PATH_FROM = 61;
        public const int TRAIN_PATH_TO = 62;
        public const int MAIN_PROGRAM = 63;
        public const int JUNCTION_LEFT_STR = 64;
        public const int JUNCTION_LEFT_BND = 65;
        public const int JUNCTION_RIGHT_STR = 66;
        public const int JUNCTION_RIGHT_BND = 67;
        public const int ACTUAL_PWM_SPEED = 68;
        public const int PWM_BRAKE = 69;
        public const int SW_START = 70;
        public const int SW_STOP = 71;
        public const int SW_RESET = 72;
        public const int SW_JUNCTION_LEFT_STR = 73;
        public const int SW_JUNCTION_LEFT_BND = 74;
        public const int SW_JUNCTION_RIGHT_STR = 75;
        public const int SW_JUNCTION_RIGHT_BND = 76;
        public const int SW_PWM_BRAKE_ON = 77;
        public const int SW_PWM_BRAKE_OFF = 78;
        public const int SW_ACTUAL_PWM_SPEED = 79;
        public const int SWITCH_PROGRAM = 80;
        public const int JUNCTION_LEFT_STR_PREV = 82;
        public const int JUNCTION_LEFT_BND_PREV = 83;
        public const int JUNCTION_RIGHT_STR_PREV = 84;
        public const int JUNCTION_RIGHT_BND_PREV = 85;
        public const int PWM_DIRECTION = 86;	
    }
}