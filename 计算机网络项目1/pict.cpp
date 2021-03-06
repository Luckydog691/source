#include "pict.h"
#include "rotate.h"
#include "block.h"

//生成block（四个定位点）
Mat returninisize(Mat& ini)
{
	Mat sub(ROW, COL * bit_SIZE, CV_8UC1);
	for (int x = 0; x < ROW; x++)
	{
		for (int y = 0; y < COL * bit_SIZE; y++)
		{
			double sum = (double)ini.at<uchar>(x * 8 + 4, y * 8 + 4)
				+ ini.at<uchar>(x * 8 + 4, y * 8 + 3)
				+ ini.at<uchar>(x * 8 + 3, y * 8 + 4)
				+ ini.at<uchar>(x * 8 + 3, y * 8 + 3);
			if (sum / 4 >= 128)
				sub.at<uchar>(x, y) = 255;
			else sub.at<uchar>(x, y) = 0;
		}
	}
	return sub;
}
void pict::encode()
{
	block anc1;
	anc1.anchor();
	
	info.block_copy(0, 0, anc1);
	anc1 = blockRotateClockWise270(anc1);
	info.block_copy(ROW - anchor_size * bit_SIZE, 0, anc1);
	anc1 = blockRotateClockWise180(anc1);
	info.block_copy(0 , COL - anchor_size, anc1);
	anc1 = blockRotateClockWise90(anc1);
	info.block_copy(ROW - anchor_size * bit_SIZE, COL - anchor_size, anc1);

	info.block_copy(0, anchor_size, block_info[0]);
	info.block_copy(anchor_size * bit_SIZE, 0, block_info[1]);
	info.block_copy(ROW - anchor_size * bit_SIZE, anchor_size, block_info[2]);
	
	info.encode();
}

//生成分块block
void pict::decode()
{
	Mat roi, src = info.get_mat();
	
	roi = Mat(anchor_size * bit_SIZE, (COL - 2 * anchor_size) * bit_SIZE, CV_8UC1);

	src(Rect(anchor_size * bit_SIZE, 0, (COL - 2 * anchor_size) * bit_SIZE, anchor_size * bit_SIZE)).copyTo(roi);
	block_info[0].set_mat(roi);

	src(Rect(anchor_size * bit_SIZE,ROW - anchor_size * bit_SIZE , (COL - 2 * anchor_size) * bit_SIZE, anchor_size * bit_SIZE)).copyTo(roi);
	block_info[2].set_mat(roi);

	roi = Mat((ROW - 2 * anchor_size * bit_SIZE), COL * bit_SIZE, CV_8UC1);
	src(Rect( 0, anchor_size * bit_SIZE, COL * bit_SIZE,(ROW - 2 * anchor_size * bit_SIZE))).copyTo(roi);
	block_info[1].set_mat(roi);

	
	block_info[0].decode();
	block_info[1].decode();
	block_info[2].decode();
}

//设置第index块block_info的信息
void pict::set_block_info(int index, block src)
{
	block_info[index] = src;
}

//获得第index块block_info的信息
block pict::get_block_info(int index)
{
	return block_info[index];
}

//charter流转pict流
vector<pict>charter_to_pict(vector<charter> ct)
{
	int index = 0;
	vector<pict>ret; pict elem;
	while (index < ct.size())
	{
		elem.set_block_info(0, build_block(ct, anchor_size * bit_SIZE, COL - 2 * anchor_size, index));
		elem.set_block_info(1, build_block(ct, ROW - 2 * anchor_size * bit_SIZE, COL, index));
		elem.set_block_info(2, build_block(ct, anchor_size * bit_SIZE, COL - 2 * anchor_size, index));
		elem.encode();//这里是原来的form
		ret.push_back(elem);
	}  
	return ret;
}

//pict流转charter流
vector<charter> pict_to_charter(vector<pict> pt)
{
	vector<charter>ret;
	for (int i = 0; i < (int)pt.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			block elem = pt[i].get_block_info(j);
			int r = elem.get_size().first, c = elem.get_size().second;
			for (int ii = 0; ii < r; ii++)
				for (int jj = 0; jj < c; jj++)
					ret.push_back(elem.get_char(ii, jj));
		}
	}
	return ret;
}
void pict::set_info_mat(Mat elem)
{
	info.set_mat(elem);
}
Mat pict::get_info_mat()
{
	return info.get_mat();
}
//行扩大x倍宽扩大y倍输出
void pict::show(int x, int y)
{
	int r = info.get_mat().rows, c = info.get_mat().cols;
	Mat sub(r * x, c * y, CV_8UC1);
	for (int i = 0; i < r * x; i += x)
		for (int j = 0; j < c * y; j += y)
			for (int ii = 0; ii < x; ii++)
				for (int jj = 0; jj < y; jj++)
				{	
					sub.at<uchar>(i + ii, j + jj) = info.get_mat().at<uchar>(i / x, j / y);
				}
	imshow("test23", sub);
	waitKey();
}