#ifndef _SEAMLINEEXTRACTOR_H 
#define _SEAMLINEEXTRACTOR_H 

#include "cv.h"
#include "highgui.h"
#include "SeparateLine.h"
#include "TextLine.h"
#include "TextLineExtractor.h"
using namespace cv;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	SeamLineExtractor extends TextLineExtractor , extracts lines of a text image. </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class SeamLineExtractor : public TextLineExtractor{

private:
	int  distanceTransform(int row,int col,int height,int width,Mat imageData);
	void SeamFromRightToLeft(int height,int width,double** Seam,Mat distance);
	void SeamFromLeftToRight(int height,int width,double** Seam,Mat distance);
	void seamMapBlending(int height,int width,double** SeamMap,double** SeamLToR,double** SeamRToL);
	double findMinDouble(double i1,double i2,double i3);
	bool isInBound(int row, int col,int height,int width);
	bool isContour(int row,int col,int height,int width,Mat image);
	void findMedialSeam(int height,int width,double** SeamMap,Mat imageData,int* medial,double** SeamMapCopy);
	int  findMinMedial(int height,int width,double** SeamMapCopy);
	int  findMin(double i1,double i2,double i3);
	void sepratingSeamDown(int height,int width,int i1,int j1,double** SeamMap,Mat image,int* seprateDown);
	void sepratingSeamUp(int height,int width,int i1,int j1,double** SeamMap,Mat image,int* seprateUp);
	void findSepratingSeam(int height,int width,int* seprateUp,int* seprateDown,double** SeamMap,int* medial,Mat image
					   ,int* finalUp,int* finalDown);
	int finish(int height,int width,double** SeamMapCopy);
	int estimateLinesNum(Mat binary);
	void LinearConvolution(double X[],double Y[], double Z[], int lenx, int leny);
	int lmax(double histogram[],int filt,int m);
public:
	SeamLineExtractor(void) {;}
	~SeamLineExtractor(void) {;}
	void extract(vector<TextLine*>& textLine);
};

#endif