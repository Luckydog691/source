#define _CRT_SECURE_NO_WARNINGS
#include <opencv2/opencv.hpp>
#include "reff.h"
#include "file.h"
using namespace std;
using namespace cv;
//���������������ַ
string moviedefaultadd = "D:\\jwtest\\movie\\";
string inputdefaultadd = "D:\\jwtest\\input\\";
string outputdefaultadd = "D:\\jwtest\\output\\";
//������������Ե��Ĭ�ϲ���
const int framebit = 6;//ÿ��ͼƬ��������֡
const int timelimit[5] = { 2000,4000,4000,8000,8000 };//������Ե�������Ƶʱ��
//ѡ���ַ
string selectadd(string a)
{
	cout << "����<=2�ֽڼ�ΪĬ�ϵ�ַ"<< endl;
	string b;
	cin >> b;
	if (b.size() <= 2)
	{
		cout << "��ѡ��Ĭ�ϵ�ַ" << a << endl;
		return a;
	}
	else
	{
		cout << "��ѡ���µ�ַ" << b << endl;
		return b;
	}
}
void mainencode()
{
	cout << "��������Ƶ�����ַ,Ĭ�ϵ�ַΪ" << moviedefaultadd << ",�ļ���Ϊe1-e5.avi" << endl;
	moviedefaultadd = selectadd(moviedefaultadd);
	cout << "������������ļ������ַ,Ĭ�ϵ�ַΪ" << inputdefaultadd << ",�ļ���Ϊe1-e5.bin" << endl;
	inputdefaultadd = selectadd(inputdefaultadd);
	for (int i = 1; i <= 5; i++)
	{
		string num; num.push_back(i + '0');
		string a = moviedefaultadd + "e" + num + ".avi";
		string b = inputdefaultadd + "e" + num + ".bin";
		ExportMovie(b, a, framebit, timelimit[i - 1]);
	}
}
void maindecode()
{
	cout << "��������Ƶ�����ַ,Ĭ�ϵ�ַΪ" << moviedefaultadd << ",�ļ���Ϊe1-e5.avi" << endl;
	moviedefaultadd = selectadd(moviedefaultadd);
	cout << "������������ļ������ַ,Ĭ�ϵ�ַΪ" << outputdefaultadd << ",�ļ���Ϊ1-5.bin,v1-v5.bin" << endl;
	outputdefaultadd = selectadd(outputdefaultadd);
	for (int i = 1; i <= 5; i++)
	{
		string num; num.push_back(i + '0');
		string a = moviedefaultadd + "e" + num + ".avi";
		string b = outputdefaultadd + num + ".bin";
		string c = outputdefaultadd + "v" + num + ".bin";
		ImportMovie(a, b, c, framebit);
	}

}

int main()
{
	//���������¶�ȡ�����ļ���Ҳ����ɾ��֮�����̨����
    //Ĭ����Ƶ��60֡
	//�ַ���ת��Ƶ��  �������������ַ�����ַ ��Ƶ�����ַ ֡�� ��Ƶ����(ms)
	//��Ƶת�ַ�����  ��������Ƶ�����ַ ֡��
	mainencode();
	maindecode();
	return 0;
}