#include "reff.h"
#include "movie.h"
#include "crc32.h"
//string类直接转换成视频，参数分别为：读入的字符串，视频保存的地址，帧率
void ExportMovie(string inputaddress, string movaddress, int framedis,int upplimit);

void ImportMovie(string movaddress, string outputaddress1, string outputaddress2,int framedis);//读入Movie,导出string

