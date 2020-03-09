#include "stander.h"
#include "pict.h"
#include "rotate.h"

Mat Extend_mat(Mat input, int x, int y);//��Mat����������x��������������y��
Mat Lessen_mat(Mat input, int x, int y);//��Mat��������Сx������������Сy��
void Save_pic(pict src, string dst);//��pict���͵�ͼƬ�����ڱ���
void Save_pic(pict src, string dst,int x,int y);//��pict���͵�ͼƬ�����ڱ���
bool get_qrcode(Mat input, Mat& output);//��ȡ��ά����Ч��Ϣ
bool IsQrColorRate(cv::Mat& image);
//����ڰױ����ж�
bool IsQrRate(float rate);
bool IsQrColorRateX(cv::Mat& image);
bool Judge(vector<Point>& contour, Mat& img);
void AdjustQrPoint(vector<Point2f>& point);
bool Point2f_compare(Point2f a, Point2f b);

