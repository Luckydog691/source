#include "file.h"

Mat Extend_mat(Mat input, int x, int y)//将Mat横坐标扩大x倍，纵坐标扩大y倍
{
	int r = input.rows, c = input.cols;
	Mat dst(r * x, c * y, CV_8UC1);
	for (int i = 0; i < r * x; i += x)
		for (int j = 0; j < c * y; j += y)
			for (int ii = 0; ii < x; ii++)
				for (int jj = 0; jj < y; jj++)
				{
					dst.at<uchar>(i + ii, j + jj) = input.at<uchar>(i / x, j / y);
				}
	return dst;
}
Mat Lessen_mat(Mat input, int x, int y)//将Mat横坐标缩小x倍，纵坐标缩小y倍
{
	int r = input.rows, c = input.cols;
	Mat dst(r / x, c / y, CV_8UC1);
	for (int i = 0; i < r / x; i++)
		for (int j = 0; j < c / y; j++)
		{
			int sum = 0;
			for (int ii = 0; ii < x; ii++)
				for (int jj = 0; jj < y; jj++)
					sum += input.at<uchar>(i * x + ii, j * y +jj);
			if(sum/(x*y)>=THRESHOLD)dst.at<uchar>(i, j)=255;
			else dst.at<uchar>(i, j) = 0;
		}
	return dst;
}
void Save_pic(pict src, string dst)//将pict类型的图片保存在本地
{
	src.encode();
	imwrite(dst, src.get_info_mat());
}
void Save_pic(pict src, string dst,int x,int y)//将pict类型的图片保存在本地,放大倍数的同时会自动向外扩展边框
{
	src.encode();
    Mat sub; Extend_mat(src.get_info_mat(), x, y).copyTo(sub);

    copyMakeBorder(sub, sub, anchor_size * y *bit_SIZE, anchor_size * y * bit_SIZE, anchor_size * x * bit_SIZE, anchor_size * x * bit_SIZE, BORDER_CONSTANT, 255);
	imwrite(dst, sub);
}
bool IsQrColorRate(cv::Mat& image)
{
    bool x = IsQrColorRateX(image);
    if (!x)
        return false;
    Mat image2 = matRotateClockWise90(image);
    bool y = IsQrColorRateX(image2);
    return y;
}
//横向黑白比例判断
bool IsQrRate(float rate)
{
    //大概比例 不能太严格
    return rate > 0.6 && rate < 1.9;
}
bool IsQrColorRateX(cv::Mat& image)
{
    int nr = image.rows / 2;
    int nc = image.cols * image.channels();

    vector<int> vValueCount;
    vector<uchar> vColor;
    int count = 0;
    uchar lastColor = 0;

    uchar* data = image.ptr<uchar>(nr);
    for (int i = 0; i < nc; i++)
    {
        vColor.push_back(data[i]);
        uchar color = data[i];
        if (color > 0)
            color = 255;

        if (i == 0)
        {
            lastColor = color;
            count++;
        }
        else
        {
            if (lastColor != color)
            {
                vValueCount.push_back(count);
                count = 0;
            }
            count++;
            lastColor = color;
        }
    }

    if (count != 0)
        vValueCount.push_back(count);

    if (vValueCount.size() < 5)
        return false;

    //横向黑白比例1:1:3:1:1
    int index = -1;
    int maxCount = -1;
    for (int i = 0; i < vValueCount.size(); i++)
    {
        if (i == 0)
        {
            index = i;
            maxCount = vValueCount[i];
        }
        else
        {
            if (vValueCount[i] > maxCount)
            {
                index = i;
                maxCount = vValueCount[i];
            }
        }
    }

    //左边 右边 都有两个值，才行
    if (index < 2)
        return false;
    if ((vValueCount.size() - index) < 3)
        return false;

    //黑白比例1:1:3:1:1
    float rate = ((float)maxCount) / 3.00;

    float rate2 = vValueCount[index - 2] / rate;
    if (!IsQrRate(rate2))return false;

    rate2 = vValueCount[index - 1] / rate;
    if (!IsQrRate(rate2))
        return false;

    rate2 = vValueCount[index + 1] / rate;
    if (!IsQrRate(rate2))
        return false;

    rate2 = vValueCount[index + 2] / rate;
    if (!IsQrRate(rate2))
        return false;

    return true;
}
bool Judge(vector<Point>& contour, Mat& img)
{
    //最小大小限定
    RotatedRect rotatedRect = minAreaRect(contour);//旋转矩形
    if (rotatedRect.size.height < 10 || rotatedRect.size.width < 10)return false;
    //将二维码从整个图上抠出来
    Point2f center = rotatedRect.center;//矩形中心点坐标
    Mat rot_mat = getRotationMatrix2D(center, rotatedRect.angle, 1.0);
    Mat rot_image;//旋转之后的图形
    Mat newimg = img.clone();
    warpAffine(newimg, rot_image, rot_mat, img.size());//原图像旋转
    if (center.x - (rotatedRect.size.width / 2) < 0 || center.y - (rotatedRect.size.height / 2) < 0)
        return false;
    Mat cropImg = rot_image(Rect(center.x - (rotatedRect.size.width / 2), center.y - (rotatedRect.size.height / 2), rotatedRect.size.width, rotatedRect.size.height));//提取ROI
    //横向黑白比例1:1:3:1:1
   

    return IsQrColorRate(cropImg);
}

bool get_qrcode(Mat input,Mat& output)
{
    //彩色图转灰度图
    Mat newinput = input.clone();
    cvtColor(newinput, newinput, CV_BGR2GRAY);
    //二值化

    threshold(newinput, newinput, 0, 255, THRESH_BINARY | THRESH_TRIANGLE);
    
    Mat ini; newinput.copyTo(ini);
    GaussianBlur(ini, newinput, Size(Point(5, 5)), 0);
    //高斯模糊
    imwrite("image/gs.jpg", newinput);
    //调用查找轮廓函数
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    
    findContours(newinput, contours, hierarchy, CV_RETR_TREE, CHAIN_APPROX_NONE, Point(0, 0));

    //通过黑色定位角作为父轮廓，有两个子轮廓的特点，筛选出四个定位角
    int parentIdx = -1;
    int ic = 0;
    vector<vector<Point>>pos;//记录二维码顶点的坐标
    
    int cnt = 0;
    for (int i = 0; i < contours.size(); i++)
    {
        if (hierarchy[i][2] != -1 && ic == 0)
        {
            parentIdx = i;
            ic++;
        }
        else if (hierarchy[i][2] != -1)
        {
            ic++;
        }
        else if (hierarchy[i][2] == -1)
        {
            ic = 0;
            parentIdx = -1;
        }
        if(ic >= 2)
        {
            ++cnt; cout << cnt << " ";
            //保存找到的三个黑色定位角
            if (Judge(contours[parentIdx], ini))
            {
                pos.push_back(contours[parentIdx]);
            }
            else ic = 0;
        }
    }    
    cout << pos.size() << endl;
    if ( pos.size() < 4)return 0;
    
    vector<Point2f>qrcenter;//保存二维码中心的坐标
    vector<Point2f>newcenter;//仿射变换坐标
    for (int i = 0; i < 4; i++)
    {
        int sumx = 0, sumy = 0;
        for (int j = 0; j < (int)pos[i].size(); j++)
        {
            sumx += pos[i][j].x;
            sumy += pos[i][j].y;
        }
        sumx /= (int)pos[i].size();
        sumy /= (int)pos[i].size();
        qrcenter.push_back(Point2f(sumx, sumy));
    }
    newcenter = qrcenter;
    AdjustQrPoint(qrcenter);

    int newx = qrcenter[1].x - qrcenter[0].x;
    newcenter[0] = qrcenter[0];
    newcenter[1].x = newcenter[0].x + newx, newcenter[1].y = newcenter[0].y;
    newcenter[2].x = newcenter[0].x, newcenter[2].y = newcenter[0].y + newx;
    newcenter[3].x = newcenter[0].x + newx, newcenter[3].y = newcenter[0].y + newx;
    
    auto M = getPerspectiveTransform(qrcenter, newcenter);
    Mat drawingRotation;
    warpPerspective(ini, drawingRotation, M, ini.size());
    double dist = newx;
    double k = (double)anchor_size / (double)COL;
    double new_COL = dist/(1-((double)7/8)*k);
    double new_anchor_size = new_COL * k;
    double edge_dis = new_anchor_size * ((double)7 / 16);
    int x1 = qrcenter[0].x - edge_dis, y1 = qrcenter[0].y - edge_dis, x2 = qrcenter[0].x - edge_dis + new_COL, y2 = qrcenter[0].y - edge_dis + new_COL;
    Mat newoutput = drawingRotation( Range(y1, y2), Range(x1, x2) );
    newoutput.copyTo(output);
    
    return 1;
}
bool Point2f_compare(Point2f a, Point2f b)
{
    return (a.x + a.y) < (b.x + b.y);
}
void AdjustQrPoint(vector<Point2f> &point)//调整四个顶点相对位置，目前只保证是正向拍摄
{
    sort(point.begin(), point.end(), Point2f_compare);
    while (point.size() > 4)point.erase(point.begin() + 2);
    if (point[0].x > point[1].x&& point[0].x > point[2].x)swap(point[0], point[1]);
    else if (point[2].x > point[1].x&& point[2].x > point[0].x)swap(point[2], point[1]);
    if (point[0].y > point[1].y&& point[0].y > point[2].y)swap(point[0], point[2]);
}
//为字符串进行随机化编解码
string str_transform(string& a)
{
    string b = a;
    for (int i = 0; i < (int)b.size(); i++)
        b[i] ^= SPSTR[i % SPSTR_LEN];
    
    return b;
}