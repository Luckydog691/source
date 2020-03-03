#include "pict.h"
#include "rotate.h"
#include "block.h"

//����block��Ŀǰֻд��������λ�㣩

void pict::encode()
{
	block anc1;
	anc1.anchor();
	
	info.block_copy(0 + ex_size * bit_SIZE, 0 + ex_size, anc1);
	anc1 = blockRotateClockWise270(anc1);
	info.block_copy(ROW - anchor_size * bit_SIZE + ex_size * bit_SIZE, 0 + ex_size, anc1);
	anc1 = blockRotateClockWise180(anc1);
	info.block_copy(0 + ex_size * bit_SIZE, COL - anchor_size + ex_size, anc1);
	
	info.block_copy(0 + ex_size * bit_SIZE, anchor_size + ex_size, block_info[0]);
	info.block_copy(anchor_size * bit_SIZE + ex_size * bit_SIZE, 0 + ex_size, block_info[1]);
	info.block_copy(ROW - anchor_size * bit_SIZE + ex_size * bit_SIZE, anchor_size + ex_size, block_info[2]);
	

	info.encode();
	
	info.show();
}

//���ɷֿ�block
void pict::decode()
{
	Mat roi, src = info.get_mat();
	roi = Mat(anchor_size * bit_SIZE, (COL - 2 * anchor_size) * bit_SIZE, CV_64FC1);
	src.copyTo(roi(Rect(ex_size * bit_SIZE, (anchor_size + ex_size) * bit_SIZE, anchor_size * bit_SIZE, (COL - 2 * anchor_size) * bit_SIZE)));
	block_info[0].set_mat(roi);
	src.copyTo(roi(Rect((ROW - anchor_size * bit_SIZE + ex_size) * bit_SIZE, (anchor_size + ex_size) * bit_SIZE, anchor_size * bit_SIZE, (COL - 2 * anchor_size) * bit_SIZE)));
	block_info[2].set_mat(roi);

	roi = Mat((ROW - 2 * anchor_size * bit_SIZE) * bit_SIZE, COL * bit_SIZE, CV_64FC1);
	src.copyTo(roi(Rect((ex_size + anchor_size * bit_SIZE) * bit_SIZE, 0, (ROW - 2 * anchor_size * bit_SIZE + ex_size) * bit_SIZE, COL * bit_SIZE)));
	block_info[1].set_mat(roi);
}

//���õ�index��block_info����Ϣ
void pict::set_block_info(int index, block src)
{
	block_info[index] = src;
}

//��õ�index��block_info����Ϣ
block pict::get_block_info(int index)
{
	return block_info[index];
}

//charter��תpict��
vector<pict>charter_to_pict(vector<charter> ct)
{
	int index = 0;
	vector<pict>ret; pict elem;
	while (index < ct.size())
	{
		elem.set_block_info(0, build_block(ct, anchor_size * bit_SIZE, COL - 2 * anchor_size, index));
		elem.set_block_info(1, build_block(ct, ROW - 2 * anchor_size * bit_SIZE, COL, index));
		elem.set_block_info(2, build_block(ct, anchor_size * bit_SIZE, COL - 2 * anchor_size, index));
		elem.encode();//������ԭ����form
		ret.push_back(elem);
	}
	return ret;
}

//pict��תcharter��
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

//������x��������y�����
void pict::show(int x, int y)
{
	int r = info.get_mat().rows, c = info.get_mat().cols;
	Mat sub(r * x, c * y, CV_64FC1);
	for (int i = 0; i < r * x; i += x)
		for (int j = 0; j < c * y; j += y)
			for (int ii = 0; ii < x; ii++)
				for (int jj = 0; jj < y; jj++)
				{
					if (i + ii >= sub.rows || j + jj >= sub.cols || i / x >= info.get_mat().rows || j / y >= info.get_mat().cols)
						getchar();
					sub.at<double>(i + ii, j + jj) = info.get_mat().at<double>(i / x, j / y);

				}
	imshow("test23", sub);
	waitKey();
}