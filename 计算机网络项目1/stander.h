#include <opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <cmath>
#include <opencv.hpp>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
#pragma once
//anchor是横坐标charter个数
const int bit_SIZE = 8, THRESHOLD = 120, anchor_size = 2, ROW = 80, COL = 10;
const int SPSTR[17] = { -43,12,97,-53,75,99,-1,-91,45,-63,100,82,-2,53,-9,0,42};
const int SPSTR_LEN = 17;
const int ANCHOR_COUNT = 4;
const char END_CHAR = '\0';
const int CHAR_PER_PICT = ROW * COL - anchor_size * anchor_size * bit_SIZE * ANCHOR_COUNT;
bool check(int x, int y, pair<int, int> size);

string int_to_str(int k);