#include "charter.h"

//通过message获得bits
void charter::encode()
{
	int num = message;
	for (int i = 0; i < bit_SIZE; i++)
	{
		bits[i] = num & 1;
		if (num)
			num >>= 1;
	}
}

//通过bits获得message
void charter::decode()
{
	int num = 0;
	for (int i = bit_SIZE - 1; i >= 0; i--)
	{
		num <<= 1;
		num += bits[i];
	}
	message = num;
}

//获得k位上的信息
bool charter::get_bit(int k) { return bits[k]; }

//改变k位上的信息
void charter::set_bit(int k, bool val) { bits[k] = val; }

//改变message
void charter::set_message(char k) { message = k; }

//获得message的信息
char charter::get_message() { return message; }

//从文件字符串传出成charter流
vector<charter> build_charter(string fp)
{
	vector<charter>ret; charter elem;
	ret.clear();
	for (int i = 0; i < (int)fp.size(); i++)
	{
		elem.set_message(fp[i]);
		elem.encode();
		ret.push_back(elem);
	}
	return ret;
}

//charter流转string
string charter_to_string(vector<charter> ct)
{
	string ret;
	for (int i = 0; i < (int)ct.size(); i++)
		ret.push_back(ct[i].get_message());
	return ret;
}

//初始化
void charter::init()
{
	message = 0;
	encode();
}