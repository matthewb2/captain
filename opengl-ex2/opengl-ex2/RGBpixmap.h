
#include <GL/glut.h>


#define checkImageWidth 512
#define checkImageHeight 512



using namespace std;

typedef unsigned short ushort;
typedef unsigned long ulong;
typedef unsigned char uchar;


class mRGB
{
public:
	uchar r, g, b, a;
	mRGB() { r = g = b = 0, a = 255; }
};

class RGBpixmap
{
public:
	int nRows, nCols;
	mRGB* pixel;
	void readBMPFile(char* frame);
	void makeCheckerBoard();
	void makeCheckImage();
	void setTexture(GLuint textureName);
};
