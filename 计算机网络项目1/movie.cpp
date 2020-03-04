#include"movie.h"

//��Ƶתpic������Ϊ������Ƶ�Ĵ洢·��(string)��֡��
vector<pict> Mov_to_mat(string filename, int frameDis)
{
	VideoCapture capture(filename);

	bool finished = 1;
	vector<pict> frames;
	long long totalFrameNumber = capture.get(CAP_PROP_FRAME_COUNT);
	long long firstFrame = 1, lastFrame = totalFrameNumber;
	if (lastFrame > totalFrameNumber)	
		finished = true;
	double frameRate = capture.get(CAP_PROP_FPS);
	double space = 1000 / frameRate;
	capture.set(CAP_PROP_POS_FRAMES, firstFrame);
	Mat frame; pict elem;
	long long currentFrame = firstFrame;
	while (!finished)//��ȡ��k*frameDis֡���������frames��
	{
		if (!capture.read(frame))
		{
			cout << "failed to access!" << endl;
			finished = true;
		}
		if (currentFrame % frameDis == 0)
		{
			Mat to_Insert = Mat(frame);
			elem.set_info_mat(to_Insert);
			frames.push_back(elem);
			++currentFrame;
			if (currentFrame >= totalFrameNumber)
				finished = true;
		}
	}
	return frames;
}

Mat  REsize(int row, int col, Mat src)
{
	double fx = row / src.rows, fy = col / src.cols;
	Mat ret(Size(row, col), CV_64FC1, Scalar(0));
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int indexi = i / fx, indexj = j / fy;
			ret.at<double>(i, j) = src.at<double>(indexi, indexj);
		}
	}
	return ret;
}

//picת��Ƶ������Ϊ������Ƶ�Ĵ洢·��(string)��Mat�飬һ��ͼƬ������֡��
void Mat_to_mov(string filename, vector<pict>frames, int framedis)
{
	// ����һ��VideoWriter
	int width = 800;
	int height = 800;
	//�����������͵��ĸ������ֱ�Ϊ֡�ʺ���Ƶ�ߴ�
	VideoWriter video;
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	video.open(filename, fourcc, 30, Size(height, width), 0);
	if (!video.isOpened())
	{
		cout << "failed!!!!!\n";
		return;
	} 
	/*
	for (int i = 0; i < frames.size(); i++)
	{
		frames[i].encode();
		Mat image = frames[i].get_info_mat();
		Mat to_image = REsize(height, width, image);
		/*
		namedWindow("input", WINDOW_AUTOSIZE);
		imshow("123", to_image);
		waitKey();/
		// ������������ͼƬ������Ƶ
		for (int j = 0; j < framedis; j++)
			video.write(to_image);
	}
	*/
	Mat to_image(800, 800, CV_64FC1);
	to_image = imread("D:\\tes.jpg",  0);
	//to_image = REsize(height, width, to_image);
	for(int i = 0; i < 100; i++)
		video.write(to_image);
}
