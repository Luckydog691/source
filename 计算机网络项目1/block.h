#pragma once
#include "stander.h"
#include "charter.h"
using namespace std;
using namespace cv;
/*
block�࣬��ʾС��ͼ����Ϣ����8*8bit
encode������bit��Ϣ��info�������ͼ����Ϣ��info_mat��
decode�������ͼ����Ϣ��info_mat�������bit��Ϣ��info��
build�����ַ�����Ϣ��charter��ת����ͼ��飨block��
*/
class block : public charter
{
protected:
	int row, col;
	vector<charter> char_info;
	Mat info_mat;
public:
	void set_block(int r, int c);
	void block_copy(int r, int c, block src);
	void clear();
	void encode();
	void decode();
	Mat get_mat();
	void set_mat(Mat roi);
	void set_info(int i, int j, bool val);
	bool get_info(int i, int j);
	void add_char(charter c);
	void show();
	void anchor();
	pair<int, int> get_size();
	charter get_char(int r, int c);
	void set_char(int r, int c, charter ch);
};
block blockRotateClockWise90(block b);
block blockRotateClockWise180(block b);
block blockRotateClockWise270(block b);
block build_block(vector<charter>char_info_flow, int row, int col, int& index);
vector<charter> block_to_charter(vector<block> blo);
