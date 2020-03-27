#pragma once
#include "block.h"
/*
图像类
由3个标准定位块和3个信息块组成
from：生成pic（由上述信息）
read：解读pic，得到3个信息块
*/
class pict 
{
private:
	block block_info[3];
	block info;
public:
	pict()
	{
		int r = ROW + 2 * 0 * bit_SIZE, c = COL + 2 * 0;
		info.set_block(r, c);
		charter t;
		for (int i = 1; i <= r * c; i++)info.add_char(t);
		Mat info_mat = info.get_mat();
		for(int i = 0; i < bit_SIZE * 0; i++)
			for (int j = 0; j < c * bit_SIZE; j++)
			{
				info_mat.at<uchar>(i, j) = 0;
				info_mat.at<uchar>(r - i - 1, j) = 0;
			}	
		for (int i = 0; i < r; i++)
			for (int j = 0; j < 0 * bit_SIZE; j++)
			{
				info_mat.at<uchar>(i, j) = 0;
				info_mat.at<uchar>(i, c * bit_SIZE - j - 1) = 0;
			}
		info.set_mat(info_mat);
		info.decode();
		block_info[0].set_block(anchor_size * bit_SIZE,COL - 2 * anchor_size);
		block_info[1].set_block(ROW - 2 * anchor_size * bit_SIZE, COL);
		block_info[2].set_block(anchor_size * bit_SIZE, COL - 2 * anchor_size);
	}
	void encode();
	void decode();
	void set_block_info(int index, block src);
	block get_block_info(int index);
	Mat get_info_mat();
	void set_info_mat(Mat elem);
	void show(int x, int y);
};

//charter流转pict流
vector<pict>charter_to_pict(vector<charter> ct);

//charter流转block流
vector<charter> pict_to_charter(vector<pict> pt);
Mat returninisize(Mat& ini);