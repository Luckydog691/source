#pragma once
#include "stander.h"

using namespace std;

class charter
{
private:
	bool bits[bit_SIZE];
	char message;
public:
	void init();
	void encode();
	void decode();
	bool get_bit(int k);
	void set_bit(int k, bool val);
	void set_message(char k);
	char get_message();
	charter() {};
};
vector<charter> build_charter(string fp);
string charter_to_string(vector<charter> ct);