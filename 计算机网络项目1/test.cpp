#define _CRT_SECURE_NO_WARNINGS
#include <opencv2/opencv.hpp>
#include "reff.h"
#include <stdlib.h>
#include <ctime>

//mainº¯Êý
int main()
{
	string a;
	//freopen("testdata.in", "r", stdin);
	srand(time(0));
	for (int i = 1; i <= 3000; i++)
	{
		int u = (char)(rand() % 256 - 127);
		a.push_back(u);
	}
	vector<charter>b = build_charter(a);
	vector<pict>c = charter_to_pict(b);
	c[0].encode();
	c[0].show(8,8);
	return 0;
}