#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
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
	//freopen("testdata.in", "r", stdin);
	srand(time(0));
	for (int i = 1; i <= 30000; i++)
		a.push_back(rand() % 256 + 1);
		//a.push_back(128);
	vector<charter>b = build_charter(a);
	vector<pict>c = charter_to_pict(b);
		
	string mov1 = "D:\\test1.mp4", mov2 = "D:\\test2.AVI";
	Mat_to_mov(mov1, c, 12);


	//vector<pict>d = Mov_to_mat(mov1, 2);
	//Mat_to_mov(mov2, d, 12);
}
int main()
{
	/*
	vector<pict>dp;
	vector<charter>dc;
	for (auto& e : c)
		dp.push_back(e);
	for (auto& e : dc)
		e.decode();
	dc = pict_to_charter(dp);
	double sum = 0, cnt = 0;

	for (int i = 0; i < b.size(); i++)
	{
		for (int j = 0; j < bit_SIZE; j++)
		{
			sum++;
			if (dc[i].get_bit(j) != b[i].get_bit(j)) cnt++;
		}
	}
	cout << "sum:" << sum << endl << "error:" << cnt << endl << "error rate:" << cnt / sum << endl;
	*/
	test_691();
	return 0;
}