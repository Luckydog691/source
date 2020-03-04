#include"movie.h"

//视频转pic，参数为读入视频的存储路径(string)，帧距
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
	while (!finished)//读取第k*frameDis帧，将其存入frames中
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

//pic转视频，参数为读入视频的存储路径(string)，Mat组，一张图片持续的帧数
void Mat_to_mov(string filename, vector<pict>frames, int framedis)
{
	// 构造一个VideoWriter
	int width = 800;
	int height = 800;
	//第三个参数和第四个参数分别为帧率和视频尺寸
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
		// 流操作符，把图片传入视频
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
