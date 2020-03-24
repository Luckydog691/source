#define _CRT_SECURE_NO_WARNINGS
#include <opencv2/opencv.hpp>
#include "reff.h"
#include "file.h"
using namespace std;
using namespace cv;
//下面是输入输出地址
string moviedefaultadd = "D:\\jwtest\\movie\\";
string inputdefaultadd = "D:\\jwtest\\input\\";
string outputdefaultadd = "D:\\jwtest\\output\\";
//下面是五个测试点的默认参数
const int framebit = 6;//每张图片保留多少帧
const int timelimit[5] = { 2000,4000,4000,8000,8000 };//五个测试点的最大视频时间
//选择地址
string selectadd(string a)
{
	cout << "输入<=2字节即为默认地址"<< endl;
	string b;
	cin >> b;
	if (b.size() <= 2)
	{
		cout << "已选择默认地址" << a << endl;
		return a;
	}
	else
	{
		cout << "已选择新地址" << b << endl;
		return b;
	}
}
void mainencode()
{
	cout << "请输入视频输出地址,默认地址为" << moviedefaultadd << ",文件名为e1-e5.avi" << endl;
	moviedefaultadd = selectadd(moviedefaultadd);
	cout << "请输入二进制文件读入地址,默认地址为" << inputdefaultadd << ",文件名为e1-e5.bin" << endl;
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
	cout << "请输入视频输入地址,默认地址为" << moviedefaultadd << ",文件名为e1-e5.avi" << endl;
	moviedefaultadd = selectadd(moviedefaultadd);
	cout << "请输入二进制文件输出地址,默认地址为" << outputdefaultadd << ",文件名为1-5.bin,v1-v5.bin" << endl;
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
	//可以用如下读取本地文件，也可以删除之后控制台读入
    //默认视频是60帧
	//字符串转视频：  参数：欲编码字符串地址 视频保存地址 帧率 视频长度(ms)
	//视频转字符串：  参数：视频保存地址 帧率
	mainencode();
	maindecode();
	return 0;
}