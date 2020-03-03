#include <opencv.hpp>
using namespace cv;

Mat matRotateClockWise90(Mat src)//˳ʱ��90
{
	transpose(src, src);
	flip(src, src, 1);
	return src;
}

Mat matRotateClockWise180(Mat src)//˳ʱ��180
{

	flip(src, src, 0);
	flip(src, src, 1);
	return src;
}

Mat matRotateClockWise270(Mat src)//˳ʱ��270
{

	transpose(src, src);
	flip(src, src, 0);
	return src;
}