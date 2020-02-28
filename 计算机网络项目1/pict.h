#pragma once
#include "block.h"
/*
图像类
由3个标准定位块和6个信息块组成
from：生成pic（由上述信息）
read：解读pic，得到6个信息块
*/
class pict
{
private:
	block block_info[3];
	block info;
public:
	pict()
	{
		info.set_block(ROW, COL);
		block_info[0].set_block(anchor_size * 8, COL - 2 * anchor_size);//上方信息块
		block_info[1].set_block(ROW - 2 * anchor_size * 8, COL);//中部信息块
		block_info[2].set_block(anchor_size * 8, COL - 2 * anchor_size);//下方信息块
	}
	void encode();
	void decode();
	void show(int x, int y);
	block get_block_info(int index);
	void set_block_info(int index, block src);
};

//charter流转pict流
vector<pict>charter_to_pict(vector<charter> ct);

//pict流转charter流
vector<charter> pict_to_charter(vector<pict> pt);

//
FILE* mat_to_mov(vector<Mat>, int k);
vector<Mat> mov_to_mat(FILE* mov, int k);
