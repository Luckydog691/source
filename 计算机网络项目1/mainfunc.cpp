#include "mainfunc.h"
void ExportMovie(string inputstr, string movaddress, int framedis)
{
	vector<charter>charterflow = build_charter(inputstr);
	vector<pict>pictflow = charter_to_pict(charterflow);
	Mat_to_movie(movaddress, "D:\\jwtest\\image\\pic", pictflow, 6, 6);

}
string Mat_to_string()//¶ÁÈëMat,µ¼³östring
{
	string ans;
	return ans;
}