using System;
using System.IO.Ports;
using System.Threading;

public class PortChat
{
    static StringComparer stringComparer;
    static Thread readThread;
    static SerialPort SP;//接口通信类
    static bool is_open = false;//是否正在通信
    //获得发送时间
    private static string get_sent_time()
    {
        string a = "[SENT  ", b = DateTime.Now.ToString();
        a = a + b + "] ";
        return a;
    }
    //获得接收时间
    private static string get_rev_time()
    {
        string a = "[RECV  ", b = DateTime.Now.ToString();
        a = a + b + "] ";
        return a;
    }
    private static bool get_portname()//选择串口名
    {
        //获得所有串口的名字
        Console.WriteLine("可用的串口如下，请输入串口名称选择串口\n");
        string[] portname = SerialPort.GetPortNames();
        for (int i = 0; i < portname.Length; i++)
            Console.WriteLine("{0} {1}\n", i + 1, portname[i]);
        //输入待选择的串口名字
        SP.PortName = Console.ReadLine();
        for (int i = 0; i < portname.Length; i++)
        {
            if (SP.PortName == portname[i]) { Console.WriteLine("串口选择成功！\n"); return true; }
        }
        Console.WriteLine("串口名无效！请重新选择\n");
        return false;
    }
    private static void get_baudrate()//输入波特率
    {

        Console.Write("请输入波特率:\n");
        string sub = Console.ReadLine();
        int rate;
        if (!int.TryParse(sub, out rate))
            Console.Write("输入数字无效,波特率为默认值{0}\n", SP.BaudRate);
        else
        {
            Console.Write("波特率成功设置！\n");
            SP.BaudRate = rate;
        }
    }
    private static void get_stopbit()//输入停止位数
    {

        Console.Write("请输入停止位数:\n1 : 1位\n2 : 2位\n");
        string sub = Console.ReadLine();
        int rate;
        if (!int.TryParse(sub, out rate))
            Console.Write("输入数字无效,停止位数为默认1位\n");
        else
        {
            if (rate < 1 || rate > 2) Console.Write("输入数字无效,停止位数为默认1位\n");
            else Console.Write("停止位数成功设置！\n");
            {
                switch (rate)
                {
                    case 1: { SP.StopBits = StopBits.One; break; }
                    case 2: { SP.StopBits = StopBits.Two; break; }
                }
            }
        }
    }
    private static void ini()//初始化
    {
        stringComparer = StringComparer.OrdinalIgnoreCase;
        readThread = new Thread(Getmessage);
        SP = new SerialPort();//新建SerialPort类
        Console.WriteLine("下面进行串口通信的基础设置\n\n");
        while (get_portname() == false) ;//选择正确的串口名
        get_baudrate();
        get_stopbit();
        SP.ReadTimeout = 500;
        SP.WriteTimeout = 500;//设置读写最大时间
        SP.Open();
        is_open = true;
        readThread.Start();
    }
    public static void Main()
    {
        Console.WriteLine("欢迎使用串口通信模拟系统！\n");
        ini();
        Console.WriteLine("开始通信，键入\"exit\"结束\n");
        while (is_open)
        {
            string now = Console.ReadLine();
            if (now == "exit")
            { is_open = false; break; }
            if (now == "testlen")
            {
                string uu = "";
                for (int i = 0; i <= 1000; i++) uu = uu + "a";
                SP.WriteLine(get_sent_time() + uu); continue;
            }
            Console.WriteLine(get_sent_time() + now);
            SP.WriteLine(get_sent_time() + now);
        }
        readThread.Join();
        SP.Close();
    }
    private static void Getmessage()
    {
        while (is_open)
            try
            {
                Console.WriteLine(get_rev_time() + SP.ReadLine());
            }
            catch (TimeoutException) { }
    }
}