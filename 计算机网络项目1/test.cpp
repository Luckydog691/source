#include <opencv2/opencv.hpp>
#include "reff.h"

using namespace std;
using namespace cv;
//mainº¯Êý

/*
int main()
{
	pict test;
	test.encode();
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("123", test.get_mat());
	waitKey();
	return 0;
}*/


void test_691()
{
	string a;
	/*Mat i = imread("image/input3.jpg");
	Mat j;
	get_qrcode(i,j);
	//freopen("testdata.in", "r", stdin);*/
	
	srand(time(0));
	for (int i = 1; i <= 30000; i++)
		a.push_back(rand() % 256 + 1);
	vector<charter>b = build_charter(a);
	vector<pict>c = charter_to_pict(b);
	Mat_to_mov("D:\\test\\sp.avi", "D:\\test\\pic\\pic", c, 6, 6);
	c = Mov_to_mat("D:\\test\\sp.avi", "D:\\test\\depic\\pic", 6);

	/*Save_pic(c[0], "D:\\test\\test1.jpg");
	Save_pic(c[0], "D:\\test\\test2.jpg", 6, 6);
	Mat aa = c[0].get_info_mat();
	aa = Extend_mat(aa, 6, 6);
	imwrite("D:\\test\\test3.jpg", aa);
	aa = Lessen_mat(aa, 6, 6);
	imwrite("D:\\test\\test4.jpg", aa);
	aa = Extend_mat(aa, 6, 6);
	imwrite("D:\\test\\vtest5.jpg",aa);
	resize(aa, aa, Size(80, 80));
	imwrite("D:\\test\\test6.jpg", aa);*/
	

}
int main()
{
	test_691();
	return 0;
}