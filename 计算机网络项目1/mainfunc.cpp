#include "mainfunc.h"
//读入string,导出Movie
void ExportMovie(string inputstr, string movaddress, int framedis)
{
	while (inputstr.size() % CHAR_PER_PICT > 0)inputstr.push_back(END_CHAR);
	inputstr = str_transform(inputstr);
	
	vector<charter>charterflow = build_charter(inputstr);
	vector<pict>pictflow = charter_to_pict(charterflow);
	Mat_to_movie(movaddress, "image/pic", pictflow, framedis, 8);
}
string ImportMovie(string movaddress, int framedis)//读入Movie,导出string
{
	string ans;
	vector<pict> pictflow= Mov_to_mat(movaddress, "image/outpic", framedis);
	vector<charter>charterflow = pict_to_charter(pictflow);
	ans = charter_to_string(charterflow);
	ans = str_transform(ans);
	while (ans.back() == END_CHAR)ans.pop_back();
	return ans;
}