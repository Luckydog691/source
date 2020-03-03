#pragma once
#include "block.h"
/*
ͼ����
��3����׼��λ���3����Ϣ�����
from������pic����������Ϣ��
read�����pic���õ�3����Ϣ��
*/
class pict : public block
{
private:
	block block_info[3];
	block info;
public:
	pict()
	{
		int r = ROW + 2 * ex_size * bit_SIZE, c = COL + 2 * ex_size;
		info.set_block(r, c);
		charter t;
		for (int i = 1; i <= r * c; i++)info.add_char(t);
		Mat info_mat = info.get_mat();
		for(int i = 0; i < bit_SIZE * ex_size; i++)
			for (int j = 0; j < c * bit_SIZE; j++)
			{
				info_mat.at<double>(i, j) = 0;
				info_mat.at<double>(r - i - 1, j) = 0;
			}
				
		for (int i = 0; i < r; i++)
			for (int j = 0; j < ex_size * bit_SIZE; j++)
			{
				info_mat.at<double>(i, j) = 0;
				info_mat.at<double>(i, c * bit_SIZE - j - 1) = 0;
			}
		info.set_mat(info_mat);
		info.decode();
	}
	void encode();
	void decode();
	void set_block_info(int index, block src);
	block get_block_info(int index);
	void show(int x, int y);
};

//charter��תpict��
vector<pict>charter_to_pict(vector<charter> ct);

//charter��תblock��
vector<charter> pict_to_charter(vector<pict> pt);