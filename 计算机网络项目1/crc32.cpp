
#include "crc32.h"
using namespace std;
char hash_test(string a)
{
    int bin = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] % 2)++bin;
    }
    cout << endl;
    return (char)bin;
}
int8_t getCRC(unsigned char* q, int len)
{
    uint8_t crc = 0;

    while (len-- > 0)
        crc = ccitt_table[(crc >> 8 ^ *q++) & 0xff] ^ (crc << 8);
    return ~crc;
}

//格式转化（不用管）
int8_t GetCRC(string str)
{
    int len = str.size();
    unsigned char* buf = new unsigned char[len];
    stringstream sstr;
    sstr.clear();
    sstr << str;
    sstr >> buf;
    return getCRC(buf, len);
}
//给一个字符串，每k位后面加一个crc32校验码
string change_string(string str, int k)
{
    int cnt = 0;
    string tem, ret;
    tem.clear(), ret.clear();
    for (auto& e : str)
    {
        ret.push_back(e);
        tem.push_back(e);
        cnt++;
        if (cnt == k)
        {
            cnt = 0;
            ret.push_back(hash_test(tem));
            tem.clear();
        }
    }
    return ret;
}


//转成01串表示是否符合crc16标准
string to_01(string str, int k)
{
    int cnt = 0;
    string ret, tem;
    ret.clear(), tem.clear();  
    for (auto& e : str)
    {
        if (cnt == k)
        {
            cnt = 0;
            char crc = hash_test(tem);
            tem.clear();
            for (int i = 1; i <= k; i++)ret.push_back(-1);
        }
        else
        {
            tem.push_back(e);
            cnt++;
        }
    }
    return ret;
}

string Readfile(string file)//读取hex文件,并将其转换成正常的string
{ 
    FILE* fp = NULL;
    fp = fopen(file.c_str(), "rb");
    char ch; string ans;
    while (!feof(fp))
    {
        ch = fgetc(fp);
        ans.push_back(ch);
        if (ans.size() >= MAX_CHAR)break;
    }
    fclose(fp);
    return ans;
}
void Writefile(string str, string fileaddress1,string fileaddress2)//将字符串转换成十六进制并转换()
{
    FILE *fp1, *fp2;
    fp1 = fopen(fileaddress1.c_str(), "wb");
    fp2 = fopen(fileaddress2.c_str(), "wb");
    int k = CHAR_PER_PICT - 1;
    int cnt = 0;
    string q = to_01(str, k); int tot = 0;
    int sub = 0;
    cout << str.size() << endl;
    for (int i = 0; i < str.size(); i++)
    {    
        if (cnt == k)
        {
            cnt = 0;continue;
        }
        else
        {
            fputc(str[i], fp1); 
            fputc(q[tot++], fp2);
            ++sub;
        }
        cnt++;
    }  
    cout << "成功解码"<< sub <<"B！"<< endl;
    fclose(fp1); 
    fclose(fp2);
}
