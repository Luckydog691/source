#include"movie.h"
//��Ƶתpic������Ϊ������Ƶ�Ĵ洢·��(string)��֡��
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
//picת��Ƶ������Ϊ������Ƶ�Ĵ洢·��(string)��Mat�飬һ��ͼƬ������֡��
void Mat_to_mov(string filename, vector<pict>frames, int framedis)
{
	// ����һ��VideoWriter
	int width = 10, height = 10;
	//�����������͵��ĸ������ֱ�Ϊ֡�ʺ���Ƶ�ߴ�
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
		// ������������ͼƬ������Ƶ
		for (int j = 0; j < framedis; j++)
			video << image;
	}
}
