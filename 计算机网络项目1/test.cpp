#include <opencv2/opencv.hpp>
#include "reff.h"
#include "file.h"

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
	Mat i = imread("image/input3.jpg");
	Mat j;
	get_qrcode(i,j);
	//freopen("testdata.in", "r", stdin);
	/*
	srand(time(0));
	for (int i = 1; i <= 30000; i++)
		a.push_back(rand() % 256 + 1);
	vector<charter>b = build_charter(a);
	vector<pict>c = charter_to_pict(b);
	Save_pic(c[0], "image/test1.jpg");
	Save_pic(c[0], "image/test2.jpg", 6, 6);
	Mat aa = c[0].get_info_mat();
	aa = Extend_mat(aa, 6, 6);
	imwrite("image/test3.jpg", aa);
	aa = Lessen_mat(aa, 6, 6);
	imwrite("image/test4.jpg", aa);
	aa = Extend_mat(aa, 6, 6);
	imwrite("image/test5.jpg",aa);
	resize(aa, aa, Size(80, 80));
	imwrite("image/test6.jpg", aa);
	*/

}
int main()
{

	test_691();
	return 0;
}