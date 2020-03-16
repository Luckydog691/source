using System;
using System.IO.Ports;
using System.Threading;

public class PortChat
{
    static StringComparer stringComparer;
    static Thread readThread;
    static SerialPort SP;//�ӿ�ͨ����
    static bool is_open = false;//�Ƿ�����ͨ��
    //��÷���ʱ��
    private static string get_sent_time()
    {
        string a = "[SENT  ", b = DateTime.Now.ToString();
        a = a + b + "] ";
        return a;
    }
    //��ý���ʱ��
    private static string get_rev_time()
    {
        string a = "[RECV  ", b = DateTime.Now.ToString();
        a = a + b + "] ";
        return a;
    }
    private static bool get_portname()//ѡ�񴮿���
    {
        //������д��ڵ�����
        Console.WriteLine("���õĴ������£������봮������ѡ�񴮿�\n");
        string[] portname = SerialPort.GetPortNames();
        for (int i = 0; i < portname.Length; i++)
            Console.WriteLine("{0} {1}\n", i + 1, portname[i]);
        //�����ѡ��Ĵ�������
        SP.PortName = Console.ReadLine();
        for (int i = 0; i < portname.Length; i++)
        {
            if (SP.PortName == portname[i]) { Console.WriteLine("����ѡ��ɹ���\n"); return true; }
        }
        Console.WriteLine("��������Ч��������ѡ��\n");
        return false;
    }
    private static void get_baudrate()//���벨����
    {

        Console.Write("�����벨����:\n");
        string sub = Console.ReadLine();
        int rate;
        if (!int.TryParse(sub, out rate))
            Console.Write("����������Ч,������ΪĬ��ֵ{0}\n", SP.BaudRate);
        else
        {
            Console.Write("�����ʳɹ����ã�\n");
            SP.BaudRate = rate;
        }
    }
    private static void get_stopbit()//����ֹͣλ��
    {

        Console.Write("������ֹͣλ��:\n1 : 1λ\n2 : 2λ\n");
        string sub = Console.ReadLine();
        int rate;
        if (!int.TryParse(sub, out rate))
            Console.Write("����������Ч,ֹͣλ��ΪĬ��1λ\n");
        else
        {
            if (rate < 1 || rate > 2) Console.Write("����������Ч,ֹͣλ��ΪĬ��1λ\n");
            else Console.Write("ֹͣλ���ɹ����ã�\n");
            {
                switch (rate)
                {
                    case 1: { SP.StopBits = StopBits.One; break; }
                    case 2: { SP.StopBits = StopBits.Two; break; }
                }
            }
        }
    }
    private static void ini()//��ʼ��
    {
        stringComparer = StringComparer.OrdinalIgnoreCase;
        readThread = new Thread(Getmessage);
        SP = new SerialPort();//�½�SerialPort��
        Console.WriteLine("������д���ͨ�ŵĻ�������\n\n");
        while (get_portname() == false) ;//ѡ����ȷ�Ĵ�����
        get_baudrate();
        get_stopbit();
        SP.ReadTimeout = 500;
        SP.WriteTimeout = 500;//���ö�д���ʱ��
        SP.Open();
        is_open = true;
        readThread.Start();
    }
    public static void Main()
    {
        Console.WriteLine("��ӭʹ�ô���ͨ��ģ��ϵͳ��\n");
        ini();
        Console.WriteLine("��ʼͨ�ţ�����\"exit\"����\n");
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