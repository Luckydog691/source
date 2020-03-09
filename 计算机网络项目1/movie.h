#pragma once
#include "reff.h"
#include "file.h"
using namespace cv;
using namespace std;

vector<pict> Mov_to_mat(string filename, string picname, int frameDis);

void Mat_to_mov(string filename, string imagename, vector<pict>frames, int framedis, int T);