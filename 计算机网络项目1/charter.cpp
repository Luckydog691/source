#include "charter.h"

//ͨ��message���bits
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

//ͨ��bits���message
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

//���kλ�ϵ���Ϣ
bool charter::get_bit(int k) { return bits[k]; }

//�ı�kλ�ϵ���Ϣ
void charter::set_bit(int k, bool val) { bits[k] = val; }

//�ı�message
void charter::set_message(char k) { message = k; }

//���message����Ϣ
char charter::get_message() { return message; }

//���ļ��ַ���������charter��
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

//charter��תstring
string charter_to_string(vector<charter> ct)
{
	string ret;
	for (int i = 0; i < (int)ct.size(); i++)
		ret.push_back(ct[i].get_message());
	return ret;
}

//��ʼ��
void charter::init()
{
	message = 0;
	encode();
}