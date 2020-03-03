#include "reff.h"
#include "pict.h"
using namespace cv;
using namespace std;

vector<pict> Mov_to_mat(string filename, int frameDis);

void Mat_to_mov(string filename, vector<pict>frames, int framedis);
