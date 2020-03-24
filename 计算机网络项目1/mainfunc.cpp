#include "mainfunc.h"
//����string,����Movie
void ExportMovie(string inputaddress, string movaddress, int framedis,int upplimit)
{
	string inputstr = Readfile(inputaddress);//�����ַ���
	while (inputstr.size() % (CHAR_PER_PICT - 1) > 0)inputstr.push_back(END_CHAR);//������ֹ��
	inputstr = change_string(inputstr, CHAR_PER_PICT - 1);//����CRC
	inputstr = str_transform(inputstr);//���ַ������й�ϣ����
	
	vector<charter>charterflow = build_charter(inputstr);//stringתcharter
	vector<pict>pictflow = charter_to_pict(charterflow);//charterתpict
	Mat_to_movie(movaddress, "image/pic", pictflow, framedis, 8, upplimit);//pictת��Ƶ���������ǷŴ���
}
void ImportMovie(string movaddress, string outputaddress1, string outputaddress2, int framedis)//����Movie,����string
{
	string ans;
	vector<pict> pictflow= Mov_to_mat(movaddress, "image/outpic", framedis);//��Ƶתpict
	vector<charter>charterflow = pict_to_charter(pictflow);//pictתcharter
	ans = charter_to_string(charterflow);
	ans = str_transform(ans);//�ָ���ԭ����str
	while (ans.back() == END_CHAR)ans.pop_back();
	Writefile(ans, outputaddress1, outputaddress2);
	return;
}