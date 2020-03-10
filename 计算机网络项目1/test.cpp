#define _CRT_SECURE_NO_WARNINGS
#include <opencv2/opencv.hpp>
#include "reff.h"
#include "file.h"

using namespace std;
using namespace cv;

int main()
{
	
	//可以用如下读取本地文件，也可以删除之后控制台读入
	string astring, bstring;
	//freopen("testdata.in", "r", stdin);
	//while (getline(cin, astring))bstring += astring;
    
	//字符串转视频：  参数：欲编码字符串 视频保存地址 帧率
	//ExportMovie(bstring, "D:\\jwtest\\movie\\test.avi", 24);
	
	//视频转字符串：  参数：视频保存地址 帧率
	bstring = ImportMovie("D:\\jwtest\\movie\\test.avi", 24);

	//控制台输出转码之后字符串
	cout << bstring << endl;

	return 0;
}