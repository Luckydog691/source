#include"movie.h"
//视频转pic，参数为读入视频的存储路径(string)，帧距
vector<pict> Mov_to_mat(string filename, int frameDis)
{
	VideoCapture capture(filename);
	bool finished = false;
	if (capture.isOpened())
		cout << "opened" << endl;
	else
		cout << "not opened" << endl;
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
//pic转视频，参数为读入视频的存储路径(string)，Mat组，一张图片持续的帧数
void Mat_to_mov(string filename, vector<pict>frames, int framedis)
{
	// 构造一个VideoWriter
	int width = 10, height = 10;
	//第三个参数和第四个参数分别为帧率和视频尺寸
	VideoWriter video;
	video.open(filename, -1, 15.0, Size(height, width));
	if (!video.isOpened())
	{
		return;
	}

	for (int i = 0; i < (int)frames.size(); i++)
	{
		Mat image = frames[i].get_info_mat();
		resize(image, image, Size(height, width));
		// 流操作符，把图片传入视频
		for (int j = 0; j < framedis; j++)
			video << image;
	}
}
