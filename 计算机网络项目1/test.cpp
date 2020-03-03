#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include "reff.h"
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


int main()
{
	string a;
	//freopen("testdata.in", "r", stdin);
	srand(time(0));
	for (int i = 1; i <= 1000; i++)
	{
		int u = (char)(rand() % 256 - 127);
		a.push_back(u);
	}
	vector<charter>b = build_charter(a);
	vector<pict>c = charter_to_pict(b);
	c[0].encode();
	c[0].show(5, 5);
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
	return 0;
}