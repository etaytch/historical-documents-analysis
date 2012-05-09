
#ifndef SEPRATElINE_H_
#define SEPRATElINE_H_
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Hols the boundries of seprating Seed from the left to the right . </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class SeprateLine {
private:
	int _left;
	int _right;
	int _length;
	double _sumWeight;
	int findMax(double i1,double i2,double i3,int pos);	

public:
	SeprateLine();
	SeprateLine(int left, int right);//row, column
	SeprateLine(SeprateLine*& other);
	
	int getLeft();
	int getRight();
	int getLength();
	void setSumWeight(double** imageData,int* seprate,int* medial,int height,int width);
	double getSumWeight();
	void findLine(Mat image,double** SeamMap,int* seprateSeed,int * final,int * medial ,int height,int width,int pos);
	virtual ~SeprateLine();
};

#endif

