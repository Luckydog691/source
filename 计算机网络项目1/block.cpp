#include "block.h"
#include "rotate.h"

void block::set_block(int r, int c)
{
	row = r, col = c;
	charter t;
	for (int i = 1; i <= r * c; i++)add_char(t);
	info_mat = Mat(r, bit_SIZE * c, CV_64FC1, Scalar(255));
	//decode();
}

//将整个src拷贝到以r行c列为左上角的block里(未更新mat)
void block::block_copy(int r, int c, block src)
{
	int src_r = src.get_size().first, src_c = src.get_size().second;
	for (int i = 0; i < src_r; i++)
		for (int j = 0; j < src_c; j++)
			set_char(r + i, c + j, src.get_char(i, j));
}

//构图
void block::encode()
{
	int index = 0, count = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col * bit_SIZE; j++)
		{
			if (char_info[index].get_bit(count))
				info_mat.at<double>(i, j) = 255;
			else
				info_mat.at<double>(i, j) = 0;
			++count;
			if (count >= 8) { count = 0; ++index; }
		}
	}
}

//解图
void block::decode()
{
	int index = 0, count = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col * bit_SIZE; j++)
		{
			double gray = info_mat.at<double>(i, j);
			char_info[index].set_bit(count, gray < THRESHOLD);
			++count;
			if (count >= 8) { count = 0; ++index; }
		}
	}
	for (int i = 0; i < (int)char_info.size(); i++)char_info[i].decode();
}

Mat block::get_mat() { return info_mat; }

void block::set_mat(Mat roi) { info_mat = roi; }

//(i为1-index)获得block中i行j列的元素
bool block::get_info(int i, int j)
{
	int index = i * col + j / bit_SIZE, bt = j % bit_SIZE;

	return char_info[index].get_bit(bt);
}
//(i为1-index)把block中i行j列的元素置为val
void block::set_info(int i, int j, bool val)
{
	int index = i * col + j / bit_SIZE, bt = j % bit_SIZE;

	char_info[index].set_bit(bt, val);
}

//在当前block后新增一个charter类
void block::add_char(charter c) { char_info.push_back(c); }

//清空block
void block::clear()
{
	char_info.clear();
	encode();
}

//获得第r行第c个字符
charter block::get_char(int r, int c)
{
	int C = get_size().second;
	int index = r * C + c;
	return char_info[index];
}
void block::set_char(int r, int c, charter ch)
{
	int C = get_size().second;
	int index = r * C + c;
	char_info[index] = ch;
}
//获得block的大小
pair<int, int> block::get_size() { return make_pair(row, col); }

//charter流转block流
block build_block(vector<charter>char_info_flow, int row, int col, int& index)
{
	//最后一个block可能会出现charter不足的情况,设置终止符（null ascii:0）
	block elem;
	charter terminal;//终止符
	terminal.set_message('\0'); terminal.encode();
	elem.set_block(row, col);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if (index >= char_info_flow.size())elem.set_char(i, j, terminal);
			else elem.set_char(i, j, char_info_flow[index]);
			++index;
		}
	elem.encode();
	return elem;
}
//block流转charter流
vector<charter> block_to_charter(vector<block> blo)
{
	vector<charter>ret;
	for (auto& e : blo)
	{
		e.decode();
		int r = e.get_size().first, c = e.get_size().second;
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				ret.push_back(e.get_char(i, j));
	}
	return ret;
}
//把当前block变成anchor块
void block::anchor()
{
	set_block(bit_SIZE * anchor_size, anchor_size);
	for (int i = 0; i < get_size().first; i++)
	{
		for (int j = 0; j < get_size().second; j++)
		{
			charter t;
			add_char(t);
			for (int k = 0; k < bit_SIZE; k++)
			{
				int index = j * bit_SIZE + k;
				if (!check(i, index, get_size()))
					info_mat.at<double>(i, index) = 0;
				else
					info_mat.at<double>(i, index) = 255;
			}
		}
	}
	decode();
}


block blockRotateClockWise90(block b)//顺时针90
{
	Mat src = b.get_mat();
	src = matRotateClockWise90(src);
	b.set_mat(src);
	b.decode();
	return b;
}

block blockRotateClockWise180(block b)//顺时针180
{
	Mat src = b.get_mat();
	src = matRotateClockWise180(src);
	b.set_mat(src);
	b.decode();
	return b;
}

block blockRotateClockWise270(block b)//顺时针270
{
	Mat src = b.get_mat();
	src = matRotateClockWise270(src);
	b.set_mat(src);
	b.decode();
	return b;
}


//展示当前block的内容
void block::show()
{
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("123", info_mat);
	//waitKey();
}