#include <opencv.hpp>
using namespace cv;

Mat matRotateClockWise90(Mat src)//À≥ ±’Î90
{
	transpose(src, src);
	flip(src, src, 1);
	return src;
}

Mat matRotateClockWise180(Mat src)//À≥ ±’Î180
{

	flip(src, src, 0);
	flip(src, src, 1);
	return src;
}

Mat matRotateClockWise270(Mat src)//À≥ ±’Î270
{

	transpose(src, src);
	flip(src, src, 0);
	return src;
}