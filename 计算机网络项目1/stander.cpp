#include "stander.h"

bool check(int x, int y, pair<int, int> size)
{
	int min_r = size.first / bit_SIZE;
	int min_c = size.second;
	int row = size.first, col = size.second * bit_SIZE;
	if (((x >= 0 && x <= min_r) || (x <= 7 * min_r && x >= 6 * min_r)) && y <= 7 * min_c) return 1;
	if (((y >= 0 && y <= min_c) || (y <= 7 * min_c && y >= 6 * min_c)) && x <= 7 * min_r) return 1;
	if (x >= 2 * min_r && x <= 5 * min_r && y >= 2 * min_c && y <= 5 * min_c) return 1;
	return 0;
}