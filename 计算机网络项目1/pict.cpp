#include "pict.h"


//根据block里面的信息更新mat
void pict::show(int x,int y)//行扩大x倍宽扩大y倍输出
{
	//info.show();
	int r = info.get_mat().rows, c = info.get_mat().cols;
	Mat sub(r * x, c * y, CV_64FC1);
	for(int i = 0;i < r * x;i += x)
		for (int j = 0; j < c * y; j += y)
			for(int ii = 0;ii < x;ii++)
				for (int jj = 0; jj < y; jj++)
				{
					if (i + ii >= sub.rows || j + jj >= sub.cols || i / x >= info.get_mat().rows || j / y >= info.get_mat().cols)
						getchar();
					sub.at<double>(i + ii, j + jj) = info.get_mat().at<double>(i / x, j / y);

				}
	imshow("test23", sub);
	waitKey();
	
}
void pict::encode()
{
	block anc1;
	anc1.anchor();
	//拷贝三个定位点
	info.block_copy(0, 0, anc1);
	info.block_copy(ROW - anchor_size * bit_SIZE, 0, anc1);
	info.block_copy(0, COL - anchor_size, anc1);
	
	//拷贝三个信息点
	info.block_copy(0, anchor_size, block_info[0]);
	info.block_copy(anchor_size * bit_SIZE, 0, block_info[1]);
	info.block_copy(ROW - anchor_size * bit_SIZE, anchor_size, block_info[2]);	
	info.encode();
}

//根据mat信息更新block
void pict::decode()
{
	Mat roi, src = info.get_mat();
	roi = Mat(anchor_size, COL - 2 * anchor_size, CV_64FC1);
	src.copyTo(roi(Rect(0, anchor_size, anchor_size * bit_SIZE, COL - 2 * anchor_size)));
	block_info[0].set_mat(roi);
	src.copyTo(roi(Rect(ROW - anchor_size * bit_SIZE, anchor_size, anchor_size * bit_SIZE, COL - 2 * anchor_size)));
	block_info[2].set_mat(roi);

	roi = Mat(ROW - 2 * anchor_size * bit_SIZE, COL, CV_64FC1);
	src.copyTo(roi(Rect(anchor_size * bit_SIZE, 0, ROW - 2 * anchor_size * bit_SIZE, COL)));
	block_info[1].set_mat(roi);
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
		elem.set_block_info(0, build_block(ct, anchor_size * 8, COL - 2 * anchor_size,index));
		elem.set_block_info(1, build_block(ct, ROW - 2 * anchor_size * 8, COL ,index));	
		elem.set_block_info(2, build_block(ct, anchor_size * 8, COL - 2 * anchor_size, index));
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
			int r = elem.get_size().first,c = elem.get_size().second;
			for (int ii = 0; ii < r; ii++)
				for (int jj = 0; jj < c; jj++)
					ret.push_back(elem.get_char(ii, jj));
		}
	}
	return ret;
}
