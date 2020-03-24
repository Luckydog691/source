#include "mainfunc.h"
//读入string,导出Movie
void ExportMovie(string inputaddress, string movaddress, int framedis,int upplimit)
{
	string inputstr = Readfile(inputaddress);//读入字符串
	while (inputstr.size() % (CHAR_PER_PICT - 1) > 0)inputstr.push_back(END_CHAR);//加入休止符
	inputstr = change_string(inputstr, CHAR_PER_PICT - 1);//加入CRC
	inputstr = str_transform(inputstr);//对字符串进行哈希加密
	
	vector<charter>charterflow = build_charter(inputstr);//string转charter
	vector<pict>pictflow = charter_to_pict(charterflow);//charter转pict
	Mat_to_movie(movaddress, "image/pic", pictflow, framedis, 8, upplimit);//pict转视频，最后参数是放大倍数
}
void ImportMovie(string movaddress, string outputaddress1, string outputaddress2, int framedis)//读入Movie,导出string
{
	string ans;
	vector<pict> pictflow= Mov_to_mat(movaddress, "image/outpic", framedis);//视频转pict
	vector<charter>charterflow = pict_to_charter(pictflow);//pict转charter
	ans = charter_to_string(charterflow);
	ans = str_transform(ans);//恢复到原来的str
	while (ans.back() == END_CHAR)ans.pop_back();
	Writefile(ans, outputaddress1, outputaddress2);
	return;
}