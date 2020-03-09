#include"movie.h"


//��Ƶתpic������Ϊ������Ƶ�Ĵ洢·��(string)��֡��
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
	while (!finished && currentFrame < totalFrameNumber)//��ȡ��k*frameDis֡���������frames��
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

//picת��Ƶ������Ϊ������Ƶ�Ĵ洢·��(string)��Mat�飬һ��ͼƬ������֡��
void Mat_to_movie(string filename, string imagename, vector<pict>frames, int framedis, int T)
{
	// ����һ��VideoWriter
	int width = T * COL * bit_SIZE, height = T * ROW;
	//�����������͵��ĸ������ֱ�Ϊ֡�ʺ���Ƶ�ߴ�
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
