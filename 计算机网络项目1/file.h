#include "stander.h"
#include "pict.h"
#include "rotate.h"

Mat Extend_mat(Mat input, int x, int y);//将Mat横坐标扩大x倍，纵坐标扩大y倍
Mat Lessen_mat(Mat input, int x, int y);//将Mat横坐标缩小x倍，纵坐标缩小y倍
void Save_pic(pict src, string dst);//将pict类型的图片保存在本地
void Save_pic(pict src, string dst,int x,int y);//将pict类型的图片保存在本地
bool get_qrcode(Mat input, Mat& output);//截取二维码有效信息
bool IsQrColorRate(cv::Mat& image);
//横向黑白比例判断
bool IsQrRate(float rate);
bool IsQrColorRateX(cv::Mat& image);
bool Judge(vector<Point>& contour, Mat& img);
void AdjustQrPoint(vector<Point2f>& point);
bool Point2f_compare(Point2f a, Point2f b);

