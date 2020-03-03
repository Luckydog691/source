#include <opencv2/opencv.hpp>
#include <opencv.hpp>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
#pragma once
//anchor是横坐标charter个数
const int bit_SIZE = 8, THRESHOLD = 120, anchor_size = 20 , ROW = 800, COL = 100;

bool check(int x, int y, pair<int, int> size);