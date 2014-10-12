using System;
using System.Collections.Generic;
using System.Text;

namespace SerialTerminal
{
    public static class SerialPortHelper
    {
        /// <summary>
        /// Set serial port name, set options and open it.
        /// 
        /// Description consists of comma-separated port name and options, comma-separated. Options are:
        /// - speed, numeric.
        /// - Parity, one of \c PE (even), \c PM (mark), \c PN (no), \c PO (odd), or \c PS (space).
        /// - Stop bits, one of \c S1, \c S1.5 or \c S2.
        /// - Data bits, one of \c D5, \c D6, \c D7 or \c D8.
        /// - \c DTR to enable DTR
        /// - \c RTS to enable RTS
        /// 
        /// Example of serial port description: "COM1,9600,PN,S1,D8".
        /// </summary>
        /// <param name="sp">Serial port.</param>
        /// <param name="description">Serial port name and options, comma-separated.</param>
        public static void openSerialPortByDescription(
            System.IO.Ports.SerialPort sp,
            string description)
        {
            string[] opts = description.Split(new char[] { ',' });
            sp.PortName = opts[0];
            for (int i = 1; i < opts.Length; ++i)
            {
                string o = opts[i];
                if (o.Length > 0) {
                    char k = o[0];
                    if (k >= '0' && k <= '9')
                    {
                        // Must be baud rate.
                        sp.BaudRate = int.Parse(o);
                    }
                    else if (o=="DTR")
                    {
                        sp.DtrEnable = true;
                    }
                    else if (o=="RTS")
                    {
                        sp.RtsEnable = true;
                    }
                    else if (k == 'P')
                    {
                        switch (o[1])
                        {
                            case 'E':
                                sp.Parity = System.IO.Ports.Parity.Even;
                                break;
                            case 'M':
                                sp.Parity = System.IO.Ports.Parity.Mark;
                                break;
                            case 'N':
                                sp.Parity = System.IO.Ports.Parity.None;
                                break;
                            case 'O':
                                sp.Parity = System.IO.Ports.Parity.Odd;
                                break;
                            case 'S':
                                sp.Parity = System.IO.Ports.Parity.Space;
                                break;
                        }
                    }
                    else if (k == 'S')
                    {
                        if (o == "S0")
                        {
                            sp.StopBits = System.IO.Ports.StopBits.None;
                        }
                        else if (o == "S1")
                        {
                            sp.StopBits = System.IO.Ports.StopBits.One;
                        }
                        else if (o == "S1.5")
                        {
                            sp.StopBits = System.IO.Ports.StopBits.OnePointFive;
                        }
                        else if (o == "S2")
                        {
                            sp.StopBits = System.IO.Ports.StopBits.Two;
                        }
                    }
                    else if (k == 'D')
                    {
                        // - Data bits, one of \c D5, \c D6, \c D7 or \c D8.
                        sp.DataBits = int.Parse(o.Substring(1));
                    }
                }
            }
            sp.Open();
        }
    }
}
