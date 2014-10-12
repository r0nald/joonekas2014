namespace SerialTerminal
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.textBoxPort = new System.Windows.Forms.TextBox();
            this.buttonClosePort = new System.Windows.Forms.Button();
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.buttonGetParam = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.textBoxISumLimit = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.textBoxDGAIN = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.textBoxPGAIN = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.buttonSendLine = new System.Windows.Forms.Button();
            this.textBoxIGAIN = new System.Windows.Forms.TextBox();
            this.textBoxADCTresh = new System.Windows.Forms.TextBox();
            this.label31 = new System.Windows.Forms.Label();
            this.textBoxPWMBase = new System.Windows.Forms.TextBox();
            this.label27 = new System.Windows.Forms.Label();
            this.textBoxPWMLimit = new System.Windows.Forms.TextBox();
            this.label28 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.cmbSerialPort = new System.Windows.Forms.ComboBox();
            this.labelStatus = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label10 = new System.Windows.Forms.Label();
            this.textBoxRUNTime = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.textBoxPacketLOSS = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.textBoxPacketERR = new System.Windows.Forms.TextBox();
            this.textBoxLog = new System.Windows.Forms.TextBox();
            this.labelState = new System.Windows.Forms.Label();
            this.label33 = new System.Windows.Forms.Label();
            this.buttonRunStop = new System.Windows.Forms.Button();
            this.textBoxSTATUS = new System.Windows.Forms.TextBox();
            this.label32 = new System.Windows.Forms.Label();
            this.textBoxVBAT = new System.Windows.Forms.TextBox();
            this.label30 = new System.Windows.Forms.Label();
            this.label29 = new System.Windows.Forms.Label();
            this.textBoxUsensors = new System.Windows.Forms.TextBox();
            this.textBoxLsensors = new System.Windows.Forms.TextBox();
            this.textBoxRPWM = new System.Windows.Forms.TextBox();
            this.textBoxLPWM = new System.Windows.Forms.TextBox();
            this.textBoxPIDU = new System.Windows.Forms.TextBox();
            this.textBoxPIDD = new System.Windows.Forms.TextBox();
            this.textBoxPIDI = new System.Windows.Forms.TextBox();
            this.textBoxPIDK = new System.Windows.Forms.TextBox();
            this.label26 = new System.Windows.Forms.Label();
            this.label25 = new System.Windows.Forms.Label();
            this.label24 = new System.Windows.Forms.Label();
            this.label23 = new System.Windows.Forms.Label();
            this.label22 = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.textBoxPIDFB = new System.Windows.Forms.TextBox();
            this.label20 = new System.Windows.Forms.Label();
            this.textBoxADC1 = new System.Windows.Forms.TextBox();
            this.textBoxADC2 = new System.Windows.Forms.TextBox();
            this.textBoxADC3 = new System.Windows.Forms.TextBox();
            this.textBoxADC5 = new System.Windows.Forms.TextBox();
            this.textBoxADC4 = new System.Windows.Forms.TextBox();
            this.textBoxADC6 = new System.Windows.Forms.TextBox();
            this.textBoxADC7 = new System.Windows.Forms.TextBox();
            this.textBoxADC8 = new System.Windows.Forms.TextBox();
            this.textBoxADC9 = new System.Windows.Forms.TextBox();
            this.textBoxADC10 = new System.Windows.Forms.TextBox();
            this.label19 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.buttonClear = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // textBoxPort
            // 
            this.textBoxPort.Location = new System.Drawing.Point(79, 21);
            this.textBoxPort.Name = "textBoxPort";
            this.textBoxPort.Size = new System.Drawing.Size(133, 20);
            this.textBoxPort.TabIndex = 2;
            this.textBoxPort.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxPort_KeyPress);
            // 
            // buttonClosePort
            // 
            this.buttonClosePort.Location = new System.Drawing.Point(165, 46);
            this.buttonClosePort.Name = "buttonClosePort";
            this.buttonClosePort.Size = new System.Drawing.Size(47, 23);
            this.buttonClosePort.TabIndex = 3;
            this.buttonClosePort.Text = "Close";
            this.buttonClosePort.UseVisualStyleBackColor = true;
            this.buttonClosePort.Click += new System.EventHandler(this.buttonClosePort_Click);
            // 
            // serialPort
            // 
            this.serialPort.BaudRate = 115200;
            this.serialPort.Parity = System.IO.Ports.Parity.Space;
            this.serialPort.ErrorReceived += new System.IO.Ports.SerialErrorReceivedEventHandler(this.serialPort_ErrorReceived);
            this.serialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort_DataReceived);
            // 
            // timer
            // 
            this.timer.Enabled = true;
            this.timer.Tick += new System.EventHandler(this.timerStartup_Tick);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.buttonGetParam);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.textBoxISumLimit);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.textBoxDGAIN);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.textBoxPGAIN);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.buttonSendLine);
            this.groupBox1.Controls.Add(this.textBoxIGAIN);
            this.groupBox1.Controls.Add(this.textBoxADCTresh);
            this.groupBox1.Controls.Add(this.label31);
            this.groupBox1.Controls.Add(this.textBoxPWMBase);
            this.groupBox1.Controls.Add(this.label27);
            this.groupBox1.Controls.Add(this.textBoxPWMLimit);
            this.groupBox1.Controls.Add(this.label28);
            this.groupBox1.Location = new System.Drawing.Point(12, 96);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(218, 261);
            this.groupBox1.TabIndex = 27;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Adjustable Parameters";
            // 
            // buttonGetParam
            // 
            this.buttonGetParam.Location = new System.Drawing.Point(109, 229);
            this.buttonGetParam.Name = "buttonGetParam";
            this.buttonGetParam.Size = new System.Drawing.Size(88, 23);
            this.buttonGetParam.TabIndex = 52;
            this.buttonGetParam.Text = "Get Parameters";
            this.buttonGetParam.UseVisualStyleBackColor = true;
            this.buttonGetParam.Click += new System.EventHandler(this.buttonGetParam_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(95, 167);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(61, 13);
            this.label6.TabIndex = 51;
            this.label6.Text = "I SUM Limit";
            // 
            // textBoxISumLimit
            // 
            this.textBoxISumLimit.BackColor = System.Drawing.Color.LightGray;
            this.textBoxISumLimit.Location = new System.Drawing.Point(12, 164);
            this.textBoxISumLimit.Name = "textBoxISumLimit";
            this.textBoxISumLimit.Size = new System.Drawing.Size(77, 20);
            this.textBoxISumLimit.TabIndex = 50;
            this.textBoxISumLimit.Text = "0";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(95, 141);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(44, 13);
            this.label5.TabIndex = 49;
            this.label5.Text = "D GAIN";
            // 
            // textBoxDGAIN
            // 
            this.textBoxDGAIN.BackColor = System.Drawing.Color.LightGray;
            this.textBoxDGAIN.Location = new System.Drawing.Point(12, 138);
            this.textBoxDGAIN.Name = "textBoxDGAIN";
            this.textBoxDGAIN.Size = new System.Drawing.Size(77, 20);
            this.textBoxDGAIN.TabIndex = 48;
            this.textBoxDGAIN.Text = "0";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(95, 89);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(43, 13);
            this.label4.TabIndex = 47;
            this.label4.Text = "P GAIN";
            // 
            // textBoxPGAIN
            // 
            this.textBoxPGAIN.BackColor = System.Drawing.Color.LightGray;
            this.textBoxPGAIN.Location = new System.Drawing.Point(12, 86);
            this.textBoxPGAIN.Name = "textBoxPGAIN";
            this.textBoxPGAIN.Size = new System.Drawing.Size(77, 20);
            this.textBoxPGAIN.TabIndex = 46;
            this.textBoxPGAIN.Text = "0";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(95, 115);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(39, 13);
            this.label3.TabIndex = 45;
            this.label3.Text = "I GAIN";
            // 
            // buttonSendLine
            // 
            this.buttonSendLine.Location = new System.Drawing.Point(12, 229);
            this.buttonSendLine.Name = "buttonSendLine";
            this.buttonSendLine.Size = new System.Drawing.Size(88, 23);
            this.buttonSendLine.TabIndex = 6;
            this.buttonSendLine.Text = "Set Parameters";
            this.buttonSendLine.UseVisualStyleBackColor = true;
            this.buttonSendLine.Click += new System.EventHandler(this.buttonSendLine_Click);
            // 
            // textBoxIGAIN
            // 
            this.textBoxIGAIN.BackColor = System.Drawing.Color.LightGray;
            this.textBoxIGAIN.Location = new System.Drawing.Point(12, 112);
            this.textBoxIGAIN.Name = "textBoxIGAIN";
            this.textBoxIGAIN.Size = new System.Drawing.Size(77, 20);
            this.textBoxIGAIN.TabIndex = 44;
            this.textBoxIGAIN.Text = "0";
            // 
            // textBoxADCTresh
            // 
            this.textBoxADCTresh.BackColor = System.Drawing.Color.LightGray;
            this.textBoxADCTresh.Location = new System.Drawing.Point(12, 19);
            this.textBoxADCTresh.Name = "textBoxADCTresh";
            this.textBoxADCTresh.Size = new System.Drawing.Size(77, 20);
            this.textBoxADCTresh.TabIndex = 42;
            this.textBoxADCTresh.Text = "0";
            // 
            // label31
            // 
            this.label31.AutoSize = true;
            this.label31.Location = new System.Drawing.Point(95, 22);
            this.label31.Name = "label31";
            this.label31.Size = new System.Drawing.Size(73, 13);
            this.label31.TabIndex = 43;
            this.label31.Text = "ADC Treshold";
            // 
            // textBoxPWMBase
            // 
            this.textBoxPWMBase.BackColor = System.Drawing.Color.LightGray;
            this.textBoxPWMBase.Location = new System.Drawing.Point(12, 60);
            this.textBoxPWMBase.Name = "textBoxPWMBase";
            this.textBoxPWMBase.Size = new System.Drawing.Size(77, 20);
            this.textBoxPWMBase.TabIndex = 35;
            this.textBoxPWMBase.Text = "0";
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Location = new System.Drawing.Point(95, 63);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(61, 13);
            this.label27.TabIndex = 36;
            this.label27.Text = "Base PWM";
            // 
            // textBoxPWMLimit
            // 
            this.textBoxPWMLimit.BackColor = System.Drawing.Color.LightGray;
            this.textBoxPWMLimit.Location = new System.Drawing.Point(12, 190);
            this.textBoxPWMLimit.Name = "textBoxPWMLimit";
            this.textBoxPWMLimit.Size = new System.Drawing.Size(77, 20);
            this.textBoxPWMLimit.TabIndex = 34;
            this.textBoxPWMLimit.Text = "0";
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Location = new System.Drawing.Point(95, 193);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(58, 13);
            this.label28.TabIndex = 37;
            this.label28.Text = "PWM Limit";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.cmbSerialPort);
            this.groupBox2.Controls.Add(this.labelStatus);
            this.groupBox2.Controls.Add(this.buttonClosePort);
            this.groupBox2.Controls.Add(this.textBoxPort);
            this.groupBox2.Location = new System.Drawing.Point(12, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(218, 75);
            this.groupBox2.TabIndex = 27;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Serial Port";
            // 
            // cmbSerialPort
            // 
            this.cmbSerialPort.FormattingEnabled = true;
            this.cmbSerialPort.Location = new System.Drawing.Point(6, 20);
            this.cmbSerialPort.Name = "cmbSerialPort";
            this.cmbSerialPort.Size = new System.Drawing.Size(67, 21);
            this.cmbSerialPort.TabIndex = 55;
            this.cmbSerialPort.SelectionChangeCommitted += new System.EventHandler(this.cmbSerialPort_SelectionChangeCommitted);
            this.cmbSerialPort.Click += new System.EventHandler(this.cmbSerialPort_Click);
            // 
            // labelStatus
            // 
            this.labelStatus.AutoSize = true;
            this.labelStatus.Location = new System.Drawing.Point(95, 51);
            this.labelStatus.Name = "labelStatus";
            this.labelStatus.Size = new System.Drawing.Size(60, 13);
            this.labelStatus.TabIndex = 4;
            this.labelStatus.Text = "Port closed";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.label10);
            this.groupBox3.Controls.Add(this.textBoxRUNTime);
            this.groupBox3.Controls.Add(this.label9);
            this.groupBox3.Controls.Add(this.textBoxPacketLOSS);
            this.groupBox3.Controls.Add(this.label8);
            this.groupBox3.Controls.Add(this.textBoxPacketERR);
            this.groupBox3.Controls.Add(this.textBoxLog);
            this.groupBox3.Controls.Add(this.labelState);
            this.groupBox3.Controls.Add(this.label33);
            this.groupBox3.Controls.Add(this.buttonRunStop);
            this.groupBox3.Controls.Add(this.textBoxSTATUS);
            this.groupBox3.Controls.Add(this.label32);
            this.groupBox3.Controls.Add(this.textBoxVBAT);
            this.groupBox3.Controls.Add(this.label30);
            this.groupBox3.Controls.Add(this.label29);
            this.groupBox3.Controls.Add(this.textBoxUsensors);
            this.groupBox3.Controls.Add(this.textBoxLsensors);
            this.groupBox3.Controls.Add(this.textBoxRPWM);
            this.groupBox3.Controls.Add(this.textBoxLPWM);
            this.groupBox3.Controls.Add(this.textBoxPIDU);
            this.groupBox3.Controls.Add(this.textBoxPIDD);
            this.groupBox3.Controls.Add(this.textBoxPIDI);
            this.groupBox3.Controls.Add(this.textBoxPIDK);
            this.groupBox3.Controls.Add(this.label26);
            this.groupBox3.Controls.Add(this.label25);
            this.groupBox3.Controls.Add(this.label24);
            this.groupBox3.Controls.Add(this.label23);
            this.groupBox3.Controls.Add(this.label22);
            this.groupBox3.Controls.Add(this.label21);
            this.groupBox3.Controls.Add(this.textBoxPIDFB);
            this.groupBox3.Controls.Add(this.label20);
            this.groupBox3.Controls.Add(this.textBoxADC1);
            this.groupBox3.Controls.Add(this.textBoxADC2);
            this.groupBox3.Controls.Add(this.textBoxADC3);
            this.groupBox3.Controls.Add(this.textBoxADC5);
            this.groupBox3.Controls.Add(this.textBoxADC4);
            this.groupBox3.Controls.Add(this.textBoxADC6);
            this.groupBox3.Controls.Add(this.textBoxADC7);
            this.groupBox3.Controls.Add(this.textBoxADC8);
            this.groupBox3.Controls.Add(this.textBoxADC9);
            this.groupBox3.Controls.Add(this.textBoxADC10);
            this.groupBox3.Controls.Add(this.label19);
            this.groupBox3.Controls.Add(this.label18);
            this.groupBox3.Controls.Add(this.label17);
            this.groupBox3.Controls.Add(this.label15);
            this.groupBox3.Controls.Add(this.label14);
            this.groupBox3.Controls.Add(this.label13);
            this.groupBox3.Controls.Add(this.label12);
            this.groupBox3.Controls.Add(this.label11);
            this.groupBox3.Controls.Add(this.label2);
            this.groupBox3.Controls.Add(this.label1);
            this.groupBox3.Location = new System.Drawing.Point(236, 12);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(514, 345);
            this.groupBox3.TabIndex = 28;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Debug Data";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(286, 267);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(57, 13);
            this.label10.TabIndex = 54;
            this.label10.Text = "RUN Time";
            // 
            // textBoxRUNTime
            // 
            this.textBoxRUNTime.Location = new System.Drawing.Point(202, 264);
            this.textBoxRUNTime.Name = "textBoxRUNTime";
            this.textBoxRUNTime.Size = new System.Drawing.Size(77, 20);
            this.textBoxRUNTime.TabIndex = 53;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(390, 178);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(66, 13);
            this.label9.TabIndex = 52;
            this.label9.Text = "Packet Loss";
            // 
            // textBoxPacketLOSS
            // 
            this.textBoxPacketLOSS.BackColor = System.Drawing.Color.Lime;
            this.textBoxPacketLOSS.Location = new System.Drawing.Point(461, 175);
            this.textBoxPacketLOSS.Name = "textBoxPacketLOSS";
            this.textBoxPacketLOSS.Size = new System.Drawing.Size(41, 20);
            this.textBoxPacketLOSS.TabIndex = 51;
            this.textBoxPacketLOSS.Text = "0";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(390, 152);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(66, 13);
            this.label8.TabIndex = 50;
            this.label8.Text = "Packet Error";
            // 
            // textBoxPacketERR
            // 
            this.textBoxPacketERR.BackColor = System.Drawing.Color.Lime;
            this.textBoxPacketERR.Location = new System.Drawing.Point(461, 149);
            this.textBoxPacketERR.Name = "textBoxPacketERR";
            this.textBoxPacketERR.Size = new System.Drawing.Size(41, 20);
            this.textBoxPacketERR.TabIndex = 49;
            this.textBoxPacketERR.Text = "0";
            // 
            // textBoxLog
            // 
            this.textBoxLog.Location = new System.Drawing.Point(7, 295);
            this.textBoxLog.Multiline = true;
            this.textBoxLog.Name = "textBoxLog";
            this.textBoxLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBoxLog.Size = new System.Drawing.Size(428, 41);
            this.textBoxLog.TabIndex = 48;
            // 
            // labelState
            // 
            this.labelState.AutoSize = true;
            this.labelState.Location = new System.Drawing.Point(292, 240);
            this.labelState.Name = "labelState";
            this.labelState.Size = new System.Drawing.Size(47, 13);
            this.labelState.TabIndex = 30;
            this.labelState.Text = "Stopped";
            // 
            // label33
            // 
            this.label33.AutoSize = true;
            this.label33.Location = new System.Drawing.Point(371, 204);
            this.label33.Name = "label33";
            this.label33.Size = new System.Drawing.Size(85, 13);
            this.label33.TabIndex = 47;
            this.label33.Text = "CMD / STATUS";
            // 
            // buttonRunStop
            // 
            this.buttonRunStop.Location = new System.Drawing.Point(195, 235);
            this.buttonRunStop.Name = "buttonRunStop";
            this.buttonRunStop.Size = new System.Drawing.Size(91, 23);
            this.buttonRunStop.TabIndex = 29;
            this.buttonRunStop.Text = "RUN / STOP";
            this.buttonRunStop.UseVisualStyleBackColor = true;
            this.buttonRunStop.Click += new System.EventHandler(this.buttonRunStop_Click);
            // 
            // textBoxSTATUS
            // 
            this.textBoxSTATUS.Location = new System.Drawing.Point(461, 201);
            this.textBoxSTATUS.Name = "textBoxSTATUS";
            this.textBoxSTATUS.Size = new System.Drawing.Size(41, 20);
            this.textBoxSTATUS.TabIndex = 46;
            // 
            // label32
            // 
            this.label32.AutoSize = true;
            this.label32.Location = new System.Drawing.Point(416, 100);
            this.label32.Name = "label32";
            this.label32.Size = new System.Drawing.Size(38, 13);
            this.label32.TabIndex = 45;
            this.label32.Text = "V BAT";
            // 
            // textBoxVBAT
            // 
            this.textBoxVBAT.BackColor = System.Drawing.Color.Lime;
            this.textBoxVBAT.Location = new System.Drawing.Point(461, 97);
            this.textBoxVBAT.Name = "textBoxVBAT";
            this.textBoxVBAT.Size = new System.Drawing.Size(41, 20);
            this.textBoxVBAT.TabIndex = 44;
            // 
            // label30
            // 
            this.label30.AutoSize = true;
            this.label30.Location = new System.Drawing.Point(218, 81);
            this.label30.Name = "label30";
            this.label30.Size = new System.Drawing.Size(68, 13);
            this.label30.TabIndex = 41;
            this.label30.Text = "Line Sensors";
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.Location = new System.Drawing.Point(213, 124);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(73, 13);
            this.label29.TabIndex = 40;
            this.label29.Text = "Used Sensors";
            // 
            // textBoxUsensors
            // 
            this.textBoxUsensors.Location = new System.Drawing.Point(209, 140);
            this.textBoxUsensors.Name = "textBoxUsensors";
            this.textBoxUsensors.Size = new System.Drawing.Size(77, 20);
            this.textBoxUsensors.TabIndex = 39;
            // 
            // textBoxLsensors
            // 
            this.textBoxLsensors.Location = new System.Drawing.Point(209, 97);
            this.textBoxLsensors.Name = "textBoxLsensors";
            this.textBoxLsensors.Size = new System.Drawing.Size(77, 20);
            this.textBoxLsensors.TabIndex = 38;
            // 
            // textBoxRPWM
            // 
            this.textBoxRPWM.Location = new System.Drawing.Point(167, 201);
            this.textBoxRPWM.Name = "textBoxRPWM";
            this.textBoxRPWM.Size = new System.Drawing.Size(77, 20);
            this.textBoxRPWM.TabIndex = 33;
            // 
            // textBoxLPWM
            // 
            this.textBoxLPWM.Location = new System.Drawing.Point(247, 201);
            this.textBoxLPWM.Name = "textBoxLPWM";
            this.textBoxLPWM.Size = new System.Drawing.Size(77, 20);
            this.textBoxLPWM.TabIndex = 32;
            // 
            // textBoxPIDU
            // 
            this.textBoxPIDU.Location = new System.Drawing.Point(9, 201);
            this.textBoxPIDU.Name = "textBoxPIDU";
            this.textBoxPIDU.Size = new System.Drawing.Size(77, 20);
            this.textBoxPIDU.TabIndex = 31;
            // 
            // textBoxPIDD
            // 
            this.textBoxPIDD.Location = new System.Drawing.Point(9, 175);
            this.textBoxPIDD.Name = "textBoxPIDD";
            this.textBoxPIDD.Size = new System.Drawing.Size(77, 20);
            this.textBoxPIDD.TabIndex = 30;
            // 
            // textBoxPIDI
            // 
            this.textBoxPIDI.Location = new System.Drawing.Point(9, 149);
            this.textBoxPIDI.Name = "textBoxPIDI";
            this.textBoxPIDI.Size = new System.Drawing.Size(77, 20);
            this.textBoxPIDI.TabIndex = 29;
            // 
            // textBoxPIDK
            // 
            this.textBoxPIDK.Location = new System.Drawing.Point(9, 123);
            this.textBoxPIDK.Name = "textBoxPIDK";
            this.textBoxPIDK.Size = new System.Drawing.Size(77, 20);
            this.textBoxPIDK.TabIndex = 28;
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Location = new System.Drawing.Point(179, 185);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(43, 13);
            this.label26.TabIndex = 27;
            this.label26.Text = "L PWM";
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Location = new System.Drawing.Point(261, 185);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(45, 13);
            this.label25.TabIndex = 26;
            this.label25.Text = "R PWM";
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Location = new System.Drawing.Point(92, 204);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(51, 13);
            this.label24.TabIndex = 25;
            this.label24.Text = "PID OUT";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(92, 178);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(36, 13);
            this.label23.TabIndex = 24;
            this.label23.Text = "PID D";
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(92, 152);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(34, 13);
            this.label22.TabIndex = 23;
            this.label22.Text = "PID I ";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(92, 126);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(35, 13);
            this.label21.TabIndex = 22;
            this.label21.Text = "PID P";
            // 
            // textBoxPIDFB
            // 
            this.textBoxPIDFB.Location = new System.Drawing.Point(9, 97);
            this.textBoxPIDFB.Name = "textBoxPIDFB";
            this.textBoxPIDFB.Size = new System.Drawing.Size(77, 20);
            this.textBoxPIDFB.TabIndex = 21;
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(92, 100);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(46, 13);
            this.label20.TabIndex = 20;
            this.label20.Text = "ERROR";
            // 
            // textBoxADC1
            // 
            this.textBoxADC1.Location = new System.Drawing.Point(463, 42);
            this.textBoxADC1.Name = "textBoxADC1";
            this.textBoxADC1.Size = new System.Drawing.Size(41, 20);
            this.textBoxADC1.TabIndex = 19;
            // 
            // textBoxADC2
            // 
            this.textBoxADC2.Location = new System.Drawing.Point(413, 42);
            this.textBoxADC2.Name = "textBoxADC2";
            this.textBoxADC2.Size = new System.Drawing.Size(41, 20);
            this.textBoxADC2.TabIndex = 18;
            // 
            // textBoxADC3
            // 
            this.textBoxADC3.Location = new System.Drawing.Point(361, 42);
            this.textBoxADC3.Name = "textBoxADC3";
            this.textBoxADC3.Size = new System.Drawing.Size(41, 20);
            this.textBoxADC3.TabIndex = 17;
            // 
            // textBoxADC5
            // 
            this.textBoxADC5.Location = new System.Drawing.Point(259, 42);
            this.textBoxADC5.Name = "textBoxADC5";
            this.textBoxADC5.Size = new System.Drawing.Size(41, 20);
            this.textBoxADC5.TabIndex = 16;
            // 
            // textBoxADC4
            // 
            this.textBoxADC4.Location = new System.Drawing.Point(309, 42);
            this.textBoxADC4.Name = "textBoxADC4";
            this.textBoxADC4.Size = new System.Drawing.Size(41, 20);
            this.textBoxADC4.TabIndex = 15;
            // 
            // textBoxADC6
            // 
            this.textBoxADC6.Location = new System.Drawing.Point(209, 42);
            this.textBoxADC6.Name = "textBoxADC6";
            this.textBoxADC6.Size = new System.Drawing.Size(41, 20);
            this.textBoxADC6.TabIndex = 14;
            // 
            // textBoxADC7
            // 
            this.textBoxADC7.Location = new System.Drawing.Point(159, 42);
            this.textBoxADC7.Name = "textBoxADC7";
            this.textBoxADC7.Size = new System.Drawing.Size(41, 20);
            this.textBoxADC7.TabIndex = 13;
            // 
            // textBoxADC8
            // 
            this.textBoxADC8.Location = new System.Drawing.Point(109, 42);
            this.textBoxADC8.Name = "textBoxADC8";
            this.textBoxADC8.Size = new System.Drawing.Size(41, 20);
            this.textBoxADC8.TabIndex = 12;
            // 
            // textBoxADC9
            // 
            this.textBoxADC9.Location = new System.Drawing.Point(59, 42);
            this.textBoxADC9.Name = "textBoxADC9";
            this.textBoxADC9.Size = new System.Drawing.Size(41, 20);
            this.textBoxADC9.TabIndex = 11;
            // 
            // textBoxADC10
            // 
            this.textBoxADC10.Location = new System.Drawing.Point(9, 42);
            this.textBoxADC10.Name = "textBoxADC10";
            this.textBoxADC10.Size = new System.Drawing.Size(41, 20);
            this.textBoxADC10.TabIndex = 10;
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(410, 26);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(46, 13);
            this.label19.TabIndex = 9;
            this.label19.Text = "ADC R4";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(460, 26);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(46, 13);
            this.label18.TabIndex = 8;
            this.label18.Text = "ADC R5";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(358, 26);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(46, 13);
            this.label17.TabIndex = 7;
            this.label17.Text = "ADC R3";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(306, 26);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(46, 13);
            this.label15.TabIndex = 6;
            this.label15.Text = "ADC R2";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(256, 26);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(46, 13);
            this.label14.TabIndex = 5;
            this.label14.Text = "ADC R1";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(206, 26);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(44, 13);
            this.label13.TabIndex = 4;
            this.label13.Text = "ADC L1";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(156, 26);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(44, 13);
            this.label12.TabIndex = 3;
            this.label12.Text = "ADC L2";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(106, 26);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(44, 13);
            this.label11.TabIndex = 2;
            this.label11.Text = "ADC L3";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(56, 26);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(44, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "ADC L4";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 26);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "ADC L5";
            // 
            // buttonClear
            // 
            this.buttonClear.Location = new System.Drawing.Point(677, 325);
            this.buttonClear.Name = "buttonClear";
            this.buttonClear.Size = new System.Drawing.Size(65, 23);
            this.buttonClear.TabIndex = 55;
            this.buttonClear.Text = "Clear";
            this.buttonClear.UseVisualStyleBackColor = true;
            this.buttonClear.Click += new System.EventHandler(this.buttonClear_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(762, 371);
            this.Controls.Add(this.buttonClear);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.groupBox3);
            this.Name = "MainForm";
            this.Text = "K2RP UI";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TextBox textBoxPort;
        private System.Windows.Forms.Button buttonClosePort;
        private System.IO.Ports.SerialPort serialPort;
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button buttonSendLine;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label labelStatus;
        private System.Windows.Forms.TextBox textBoxADC10;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBoxADC1;
        private System.Windows.Forms.TextBox textBoxADC2;
        private System.Windows.Forms.TextBox textBoxADC3;
        private System.Windows.Forms.TextBox textBoxADC5;
        private System.Windows.Forms.TextBox textBoxADC4;
        private System.Windows.Forms.TextBox textBoxADC6;
        private System.Windows.Forms.TextBox textBoxADC7;
        private System.Windows.Forms.TextBox textBoxADC8;
        private System.Windows.Forms.TextBox textBoxADC9;
        private System.Windows.Forms.TextBox textBoxPIDFB;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.TextBox textBoxRPWM;
        private System.Windows.Forms.TextBox textBoxLPWM;
        private System.Windows.Forms.TextBox textBoxPIDU;
        private System.Windows.Forms.TextBox textBoxPIDD;
        private System.Windows.Forms.TextBox textBoxPIDI;
        private System.Windows.Forms.TextBox textBoxPIDK;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.TextBox textBoxPWMBase;
        private System.Windows.Forms.TextBox textBoxPWMLimit;
        private System.Windows.Forms.TextBox textBoxLsensors;
        private System.Windows.Forms.Label label30;
        private System.Windows.Forms.Label label29;
        private System.Windows.Forms.TextBox textBoxUsensors;
        private System.Windows.Forms.Label label33;
        private System.Windows.Forms.TextBox textBoxSTATUS;
        private System.Windows.Forms.Label label32;
        private System.Windows.Forms.TextBox textBoxVBAT;
        private System.Windows.Forms.Label label31;
        private System.Windows.Forms.TextBox textBoxADCTresh;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox textBoxISumLimit;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBoxDGAIN;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBoxPGAIN;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxIGAIN;
        private System.Windows.Forms.Label labelState;
        private System.Windows.Forms.Button buttonRunStop;
        private System.Windows.Forms.TextBox textBoxLog;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox textBoxPacketLOSS;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textBoxPacketERR;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textBoxRUNTime;
        private System.Windows.Forms.Button buttonClear;
        private System.Windows.Forms.Button buttonGetParam;
        private System.Windows.Forms.ComboBox cmbSerialPort;
    }
}

