#define _CRT_SECURE_NO_WARNINGS
#include <opencv2/opencv.hpp>
#include "reff.h"
#include "file.h"

using namespace std;
using namespace cv;

int main()
{
	string astring, bstring;
	freopen("testdata.in", "r", stdin);
	while (getline(cin, astring))bstring += astring;
	ExportMovie(bstring, "D:\\jwtest\\movie\\test.avi", 6);
	return 0;
}