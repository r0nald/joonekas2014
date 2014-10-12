using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Linq;
using System.IO;
using System.Globalization;


namespace SerialTerminal
{
    public partial class MainForm : Form
    {
        const string _CONFIGURATION_FILENAME = "Serial_Terminal.ini";
        static readonly TimeSpan _PACKET_MAX_TIME = TimeSpan.FromMilliseconds(100);
        static readonly TimeSpan _MAX_QUIET_TIME = TimeSpan.FromMilliseconds(2 * 1000);
        static readonly TimeSpan _MAX_KEYPRESS_WAIT = TimeSpan.FromMilliseconds(2000);

     

        /// <summary>Last time data was received - skip some packets in order to catch the fresh with the new ones..</summary>
        DateTime _lastActionTime = DateTime.Now.Add(_PACKET_MAX_TIME);

        /// <summary>Last keypress time.</summary>
        DateTime _lastKeypressTime = DateTime.Now.Subtract(_MAX_KEYPRESS_WAIT);

        /// <summary>Current line under building.</summary>
        StringBuilder _lineBuilder = new StringBuilder();

        // received packet buffer
        List<byte> _PacketBuffer = new List<byte>();


        static void _dont_throw(Action x)
        {
            try { x(); } catch (Exception /* ex */) { }
        }

        void _append_log(string text)
        {
            if (InvokeRequired)
            {
                BeginInvoke(new Action(() => { textBoxLog.AppendText(text); }));
            }
            else
            {
                textBoxLog.AppendText(text);
            }
        }

        void _close_port(string reason)
        {
            _dont_throw(() =>
            {
                if (serialPort.IsOpen)
                {
                    serialPort.Close();
                }
                if (reason != null)
                {
                    _append_log(reason);
                }
                portStat = false;
            });
        }

        void _open_port(string reason)
        {
            _dont_throw(() =>
            {
                if (serialPort.IsOpen)
                {
                    serialPort.Close();
                }
                _lineBuilder.Clear();
                SerialPortHelper.openSerialPortByDescription(serialPort, PortData);
                if (reason != null)
                {
                    _append_log(reason);
                }
            });
        }

        public MainForm()
        {
            InitializeComponent();

        }


  
        private string PortData;
        private bool portStat;

        private void MainForm_Load(object sender, EventArgs e)
        {

            // 1. Load configuration.
            _dont_throw(() =>
            {
                portStat = false;
                textBoxPort.Text = "115200,DTR,PN,S2,D8";
                var s = "0";
                try
                {
                   s = System.IO.File.ReadAllText(_CONFIGURATION_FILENAME);
                }
                catch
                {
                    _append_log("Config file not found! Select correct port\r\n");
                }  

                    // we have some data stored in config file
                    if (s.Length > 12)
                    {
                        var index = s.IndexOf(',');
                        var comNum = s.Substring(0, index);
                        var set = s.Substring(index + 1);

                        var com = comNum.Substring(0, 3);
                        if (com == "COM")
                        {
                            cmbSerialPort.Text = comNum;    // Fill port number BOX
                            if (set.Length == 0)
                            {
                                set = "115200,DTR,PN,S2,D8";
                            }

                            textBoxPort.Text = set;         // Fill port settings BOX
  
                            PortData = comNum + "," + set;


                            // Nice methods to browse all available ports:
                            string[] ports = System.IO.Ports.SerialPort.GetPortNames();
                           
                            // Check if port exists
                            foreach (string port in ports)
                            {
                                if (comNum == port)
                                {
                                    portStat = true;
                                    _open_port(null);
                                }
                            }

                            if (portStat == false)
                            {
                                _append_log("This COM not exist! Select correct port\r\n");
                            }
                         
                        }
                        else
                        {
                            _append_log("Config file corrupted! Select correct port\r\n");
                        }
                    }
                    else
                    {
                        _append_log("Config file corrupted! Select correct port\r\n");
                    }
                  
                        
            });
        }


        // Parameters class (struct)
        class ParametersSET
        {	
            public float BasePWM;					        // Base PWM setting
            public float SET_P; 						    // P gain setting
            public float SET_I;								// I gain setting
            public float SET_D;								// D gain setting
            public float ISUM_Limit;						// I sum limit
            public float PWM_Limit;							// PWM MAX limit
            public byte CMD;	                            // Command	
            public byte adcTresh;                          // ADC Linesense treshold
        }

        ParametersSET paramSet = new ParametersSET();


        // DBG Data Length
        // !!!!! CHANGE IF Add / Remove DBG Data fields !!!!!
        public const uint DBGDataLen = 52;
        // DBG Data class (struct)
        #pragma warning disable 0649                            // disable warnings
        class DBGData
        {
            public ushort   StartSTR;							// "K2"	
            public byte     adc1;								// Most right linesensor value
            public byte     adc2;
            public byte     adc3;
            public byte     adc4;
            public byte     adc5;								// Center Right linesensor value
            public byte     adc6;								// Center Left linesensor value
            public byte     adc7;
            public byte     adc8;
            public byte     adc9;
            public byte     adc10;								// Most left linesensor value		
            public ushort   lineSensors;
            public ushort   usedSensors;

            public float    pidFeedback;					    // PID error
            public float    pidK; 								// P VAL: error * P
            public float    pidI;								// I VAL: SUM (error * I)
            public float    pidD;								// D VAL: (error - last error) * D
            public float    pidU;								// PID OUT: (P + I + D) limited with MAX PID value
            public float    pwmLeft;							// BASE PWM - PID OUT
            public float    pwmRight;							// BASE PWM + PID OUT
            public UInt32   time;	                            // RunTime

            public byte     CMD_STAT;							// Command Echo & status bits
            public byte     battVoltage;					    // Battery voltage
            public ushort   EndByte;							// 0x0D0A

        }
        // Enable warnings
        #pragma warning restore 0649                            

        // DBGData data;
        DBGData data = new DBGData();

        public UInt32 PacketError = 0;

        public byte SendPacket = 0;

        public string Convert(ushort x)
        {
            char[] bits = new char[10];
            int i;
            for(i = 0; i < 10; i++)  {
                bits[i] = (x & 1) == 1 ? '1' : '0';
                x >>= 1;
            }

            Array.Reverse(bits, 0, i);
            return new string(bits);
        }


        void serialPort_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            int to_read = serialPort.BytesToRead;
            if (to_read > 0)
            {
                  
                byte[] buffer = new byte[to_read];
                int n = serialPort.Read(buffer, 0, to_read);
                var t1 = DateTime.Now;
                TimeSpan dt = t1.Subtract(_lastActionTime);
                _lastActionTime = t1;
  
                if (n > 0)
                {
                    BeginInvoke(new Action(() =>
                    {
                         
                        for (int i = 0; i < n; ++i) {
                            var c = buffer[i];

                            if (_PacketBuffer.Count > 1) {
                                _PacketBuffer.Add(c);
                                if (_PacketBuffer.Count == DBGDataLen)
                                { // process packet 
                                    int index_so_far = 0;
                                    var _PacketBufferBytes = _PacketBuffer.ToArray();

                                    foreach (var field_info in data.GetType().GetFields()) {
                                        if (field_info.FieldType == typeof(byte)) {
                                            field_info.SetValue(data, _PacketBufferBytes[index_so_far]);
                                            index_so_far += 1;
                                        }
                                        else if (field_info.FieldType == typeof(ushort))
                                        {
                                            field_info.SetValue(data, BitConverter.ToUInt16(_PacketBufferBytes, index_so_far) );
                                            index_so_far += 2;
                                        }
                                        else if (field_info.FieldType == typeof(UInt32))
                                        {
                                            field_info.SetValue(data, BitConverter.ToUInt32(_PacketBufferBytes, index_so_far));
                                            index_so_far += 4;
                                        }
                                        else if (field_info.FieldType == typeof(float))
                                        {
                                            field_info.SetValue(data, BitConverter.ToSingle(_PacketBufferBytes, index_so_far));
                                            index_so_far += 4;
                                        }   
                                    }

                                    if (SendPacket != 0)        // We need to send packet to K2RP
                                    {
                                        sendToSerial();         // Send Packet
                                        paramSet.CMD = 0;       // clear cmd bits
                                        SendPacket = 0;         // clear packet send flag
                                    }

                                    _PacketBuffer.Clear();     // Clear buffer

                                    if (data.EndByte == 0x0A0D)
                                    { // we got correct end byte

                                        textBoxADC10.Text = data.adc10.ToString();
                                        textBoxADC9.Text = data.adc9.ToString();
                                        textBoxADC8.Text = data.adc8.ToString();
                                        textBoxADC7.Text = data.adc7.ToString();
                                        textBoxADC6.Text = data.adc6.ToString();
                                        textBoxADC5.Text = data.adc5.ToString();
                                        textBoxADC4.Text = data.adc4.ToString();
                                        textBoxADC3.Text = data.adc3.ToString();
                                        textBoxADC2.Text = data.adc2.ToString();
                                        
                                        if ((data.CMD_STAT & 0x04) != 0) 
                                        { // Read SET parameters
                                            textBoxADCTresh.Text = data.adc1.ToString();
                                            textBoxPWMBase.Text = data.pidU.ToString("0.000");
                                            textBoxPGAIN.Text = data.pidK.ToString("0.000000");
                                            textBoxIGAIN.Text = data.pidI.ToString("0.000000");
                                            textBoxDGAIN.Text = data.pidD.ToString("0.000000");
                                            textBoxISumLimit.Text = data.pwmRight.ToString("0.0000");
                                            textBoxPWMLimit.Text = data.pwmLeft.ToString("0.00");
                                        }
                                        else
                                        { // Read Debug parameters
                                            textBoxADC1.Text = data.adc1.ToString();
                                            textBoxPIDK.Text = data.pidK.ToString("0.000000");
                                            textBoxPIDI.Text = data.pidI.ToString("0.000000");
                                            textBoxPIDD.Text = data.pidD.ToString("0.000000");
                                            textBoxPIDU.Text = data.pidU.ToString("00.0000");
                                            textBoxLPWM.Text = data.pwmLeft.ToString("0.0000");
                                            textBoxRPWM.Text = data.pwmRight.ToString("0.0000");
                                        }

                                        textBoxPIDFB.Text = data.pidFeedback.ToString("0.0000");
                                        textBoxLsensors.Text = Convert(data.lineSensors);
                                        textBoxUsensors.Text = Convert(data.usedSensors);
                                        
                                        float timesec = (float)(data.time * 0.01);
                                        textBoxRUNTime.Text = timesec.ToString("0000.00"); 

                                        if ((data.CMD_STAT & 0x01) != 0)
                                        {
                                            labelState.Text = "Running";
                                        }
                                        else 
                                        {
                                            labelState.Text = "Stopped";
                                        }

                                        float VBAT = (float)(data.battVoltage / 3.6);

                                        if (VBAT < 10.8)
                                        { // about 10.8V
                                            textBoxVBAT.BackColor = Color.Red;
                                        }
                                        else
                                        {
                                            textBoxVBAT.BackColor = Color.Lime;
                                        }
                                        textBoxVBAT.Text = VBAT.ToString("00.00");
                                        textBoxSTATUS.Text = data.CMD_STAT.ToString();
                                       
                                        if (textBoxADCTresh.Text == "0") // Ask parameters if 0
                                        {
                                            if ((data.CMD_STAT & 0x01) != 0) // running
                                            {
                                                paramSet.CMD = 0x03;   // Set get parameters & run bits
                                            }
                                            else // stopped
                                            {
                                                paramSet.CMD = 0x02;   // Set get parameters bit
                                            }

                                            SendPacket = 1;         // Set packet send flag                                 
                                        }
                                    }  
                                    else
                                    {
                                        PacketError++;
                                        textBoxVBAT.BackColor = Color.Red;
                                        textBoxPacketERR.Text = PacketError.ToString();
                                    }                                
                                }
                            }
                            else if (_PacketBuffer.Count > 0)
                            {
                                if (c == 0x32)
                                {
                                    _PacketBuffer.Add(c);
                                }
                                else
                                {
                                    _PacketBuffer.Clear();     // Clear buffer
                                }
                            }
                            // Search packet start
                            else {
                                if (c == 0x4B) {
                                    _PacketBuffer.Add(c);
                                }
                            }   
                        } // End for 
                    }));
                }

                else
                {
                    _append_log("Read failed. Closing serial port.\r\n");
                }
            }
        }

        void serialPort_ErrorReceived(object sender, System.IO.Ports.SerialErrorReceivedEventArgs e)
        {
            _append_log("|__\r\n");
        }

        private void textBoxPort_KeyPress(object sender, KeyPressEventArgs e)
        {
            _lastKeypressTime = DateTime.Now;
        }

        void timerStartup_Tick(object sender, EventArgs e)
        {
            // here - open the serial port.
            // SerialPortHelper.openSerialPortByDescription(serialPort, textBoxPort.Text);
            var t1 = DateTime.Now;
            TimeSpan dt = t1.Subtract(_lastActionTime);
            TimeSpan dkey = t1.Subtract(_lastKeypressTime);
            if (dt > _MAX_QUIET_TIME && dkey>_MAX_QUIET_TIME)
            {
                if ( (!(serialPort.IsOpen)) && (portStat == true) )
                {
                  
                    string[] ports = System.IO.Ports.SerialPort.GetPortNames();
                    portStat = false;
                    // Check if port exists
                    foreach (string port in ports)
                    {
                        if (cmbSerialPort.Text == port)
                        {
                            portStat = true;
                            PortData = cmbSerialPort.Text + "," + textBoxPort.Text;

                            _open_port("Port opened after timeout\r\n");
                        }
                    }

                    if (portStat == false)
                    {
                        _append_log("This COM not exist! Select correct port\r\n");
                    }
                }
                _lastActionTime = t1.Add(_PACKET_MAX_TIME);
            }
            labelStatus.Text = serialPort.IsOpen ? "Opened" : "Closed";
        }

        // Clear Log box button click
        void buttonClear_Click(object sender, EventArgs e)
        {
            textBoxLog.Clear();
        }

        // start stop button
        void buttonRunStop_Click(object sender, EventArgs e)
        {
            if ((data.CMD_STAT & 0x01) != 0)
            {
                paramSet.CMD = 0x00; // STOP
            }
            else
            {
                paramSet.CMD = 0x01; // RUN
            }
            SendPacket = 1;       // Set var to send packet      
        }

        // Get parameters
        void buttonGetParam_Click(object sender, EventArgs e)
        {
            if ((data.CMD_STAT & 0x01) != 0) // running
            {
                paramSet.CMD = 0x03;   // Set get parameters & run bits
            }
            else // stopped
            {
                paramSet.CMD = 0x02;   // Set get parameters bit
            }
            SendPacket = 1;         // Set var to send packet
        }

        // Set parameters
        void buttonSendLine_Click(object sender, EventArgs e)
        {
            if ((data.CMD_STAT & 0x01) != 0) // running
            {
                paramSet.CMD = 0x05;   // Set send parameters  & run bits
            }
            else // stopped
            {
                paramSet.CMD = 0x04;   // Set send parameters bit
            }
            SendPacket = 1;         // Set var to send packet
        }


        // send packet to serial
        void sendToSerial() {

            paramSet.adcTresh = byte.Parse(textBoxADCTresh.Text);
            paramSet.BasePWM = float.Parse(textBoxPWMBase.Text.Replace(",", "."), System.Globalization.CultureInfo.InvariantCulture);
            paramSet.SET_P = float.Parse(textBoxPGAIN.Text.Replace(",", "."), System.Globalization.CultureInfo.InvariantCulture);
            paramSet.SET_I = float.Parse(textBoxIGAIN.Text.Replace(",", "."), System.Globalization.CultureInfo.InvariantCulture);
            paramSet.SET_D = float.Parse(textBoxDGAIN.Text.Replace(",", "."), System.Globalization.CultureInfo.InvariantCulture);
            paramSet.ISUM_Limit = float.Parse(textBoxISumLimit.Text.Replace(",", "."), System.Globalization.CultureInfo.InvariantCulture);
            paramSet.PWM_Limit = float.Parse(textBoxPWMLimit.Text.Replace(",", "."), System.Globalization.CultureInfo.InvariantCulture);


            var bytes = new List<byte>();
            
            bytes.Add(0x4B); // K
            bytes.Add(0x32); // 2
            bytes.AddRange( BitConverter.GetBytes(paramSet.BasePWM) );
            bytes.AddRange(BitConverter.GetBytes(paramSet.SET_P) );
            bytes.AddRange(BitConverter.GetBytes(paramSet.SET_I) );
            bytes.AddRange(BitConverter.GetBytes(paramSet.SET_D) );
            bytes.AddRange(BitConverter.GetBytes(paramSet.ISUM_Limit) );
            bytes.AddRange(BitConverter.GetBytes(paramSet.PWM_Limit) );
            bytes.Add(paramSet.CMD);
            bytes.Add(paramSet.adcTresh);
            bytes.Add(0x0D);
            bytes.Add(0x0A);
            
            if (serialPort.IsOpen)
            {
                serialPort.Write(bytes.ToArray(), 0, bytes.Count);
            }
            else
            {
                MessageBox.Show("Port is closed!", "Error");
            }

        }

        // Close serial port
        void buttonClosePort_Click(object sender, EventArgs e)
        {
            _lastActionTime = DateTime.Now.Add(_PACKET_MAX_TIME);
            _lastKeypressTime = DateTime.Now;
            _close_port("Closing port...\r\n");
        }


        // Close form
        void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            // 1. Remember the serial port for the next time.
            // 2. Close the serial port.

            _dont_throw(() =>
            {
                timer.Enabled = false;
                if (portStat == true)  // store if correct data
                {
                    System.IO.File.WriteAllText(_CONFIGURATION_FILENAME, PortData);
                }
               

            });
        }


        private void cmbSerialPort_SelectionChangeCommitted(object sender, EventArgs e)
        {
            portStat = true;

        }

        private void cmbSerialPort_Click(object sender, EventArgs e)
        {
            // Nice methods to browse all available ports:
            string[] ports = System.IO.Ports.SerialPort.GetPortNames();
            // Clear port list
            cmbSerialPort.Items.Clear();
            // Add all port names to the combo box:
            foreach (string port in ports)
            {
                cmbSerialPort.Items.Add(port);
            }
            if (serialPort.IsOpen)
            {
                _close_port("Closing port...\r\n");
            }
        }

    }
}