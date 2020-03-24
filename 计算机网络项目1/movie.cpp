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
	Mat frame,to_Insert,new_to_Insert; pict elem;
	long long currentFrame = firstFrame;
	while (!finished && currentFrame < totalFrameNumber)//��ȡ��k*frameDis֡���������frames��
	{
		if (!capture.read(frame))
			finished = true;
		if (currentFrame % frameDis == 0)
		//if (currentFrame % 1 == 0)
		{

			frame.copyTo(to_Insert);
			string position = picname + int_to_str(currentFrame / frameDis) + ".jpg";
			if (get_qrcode(to_Insert, new_to_Insert))
			{
				resize(new_to_Insert, new_to_Insert,Size(ROW, COL * bit_SIZE));
				imwrite(position, new_to_Insert);
				elem.set_info_mat(new_to_Insert);
				elem.decode();
				frames.push_back(elem);
			}
		}
		++currentFrame;
	}
	return frames;
}

//picת��Ƶ������Ϊ������Ƶ�Ĵ洢·��(string)��Mat�飬һ��ͼƬ������֡��
void Mat_to_movie(string filename, string imagename, vector<pict>frames, int framedis, int T,int upplimit)
{
	int uppframe = upplimit * 60 / 1000 - framedis;
	// ����һ��VideoWriter
	int width = T * COL * bit_SIZE + 2 * anchor_size * T * bit_SIZE, height = T * ROW + 2 * anchor_size * T * bit_SIZE;
	//�����������͵��ĸ������ֱ�Ϊ֡�ʺ���Ƶ�ߴ�
	VideoWriter video;
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	video.open(filename, fourcc, 60, Size(height, width), 1);//Ĭ��60֡
	if (!video.isOpened())
	{
		cout << "failed!!!!!\n";
		return;
	}
	Mat background(T * ROW + 2 * anchor_size * T * bit_SIZE, T * COL * bit_SIZE + 2 * anchor_size * T * bit_SIZE, CV_8UC1, Scalar(255));
	imwrite("image/bg.jpg", background);
	background = imread("image/bg.jpg");
	for (int j = 0; j < framedis && uppframe; j++,--uppframe)
		video.write(background);

	for (int i = 0; i < frames.size(); i++)
	{
		frames[i].encode();
		string position = imagename + int_to_str(i) + ".jpg";
		Save_pic(frames[i], position, T, T);
		Mat to_image = imread(position);
		
		for (int j = 0; j < framedis && uppframe; j++,--uppframe)
			video.write(to_image);
	}
	for (int j = 0; j < framedis; j++)
		video.write(background);
	return;
}
