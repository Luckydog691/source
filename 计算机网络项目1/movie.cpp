#include"movie.h"


//视频转pic，参数为读入视频的存储路径(string)，帧距
vector<pict> Mov_to_mat(string filename, string picname, int frameDis)
{
	VideoCapture capture(filename);
	bool finished = 0;
	vector<pict> frames;

	long long totalFrameNumber = capture.get(CAP_PROP_FRAME_COUNT);
	long long firstFrame = 0;
	if (!totalFrameNumber) finished = 1;
	double frameRate = capture.get(CAP_PROP_FPS);
	capture.set(CAP_PROP_POS_FRAMES, firstFrame);
	Mat frame; pict elem;
	long long currentFrame = firstFrame;
	while (!finished && currentFrame < totalFrameNumber)//读取第k*frameDis帧，将其存入frames中
	{
		if (!capture.read(frame))
		{
			cout << "failed to access!" << endl;
			finished = true;
		}
		if (currentFrame % frameDis == 0)
		{
			Mat to_Insert = Mat(frame);
			string position = picname + int_to_str(currentFrame / frameDis) + ".jpg";
			imwrite(position, to_Insert);
			elem.set_info_mat(to_Insert);
			elem.decode();
			frames.push_back(elem);
		}
		++currentFrame;
	}
	return frames;
}

//pic转视频，参数为读入视频的存储路径(string)，Mat组，一张图片持续的帧数
void Mat_to_movie(string filename, string imagename, vector<pict>frames, int framedis, int T)
{
	// 构造一个VideoWriter
	int width = T * COL * bit_SIZE, height = T * ROW;
	//第三个参数和第四个参数分别为帧率和视频尺寸
	VideoWriter video;
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	video.open(filename, fourcc, 30, Size(height, width), 1);
	if (!video.isOpened())
	{
		cout << "failed!!!!!\n";
		return;
	}

	for (int i = 0; i < frames.size(); i++)
	{
		frames[i].encode();
		string position = imagename + int_to_str(i) + ".jpg";
		Save_pic(frames[i], position, T, T);
		Mat to_image = imread(position);
		for (int j = 0; j < framedis; j++)
			video.write(to_image);
	}
}
