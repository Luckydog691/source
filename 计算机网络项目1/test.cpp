#define _CRT_SECURE_NO_WARNINGS
#include <opencv2/opencv.hpp>
#include "reff.h"
#include "file.h"

using namespace std;
using namespace cv;

int main()
{
	
	//���������¶�ȡ�����ļ���Ҳ����ɾ��֮�����̨����
	string astring, bstring;
	//freopen("testdata.in", "r", stdin);
	//while (getline(cin, astring))bstring += astring;
    
	//�ַ���ת��Ƶ��  �������������ַ��� ��Ƶ�����ַ ֡��
	//ExportMovie(bstring, "D:\\jwtest\\movie\\test.avi", 24);
	
	//��Ƶת�ַ�����  ��������Ƶ�����ַ ֡��
	bstring = ImportMovie("D:\\jwtest\\movie\\test.avi", 24);

	//����̨���ת��֮���ַ���
	cout << bstring << endl;

	return 0;
}