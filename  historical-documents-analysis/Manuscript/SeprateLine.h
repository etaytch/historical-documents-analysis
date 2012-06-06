
#ifndef SEPRATElINE_H_
#define SEPRATElINE_H_
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "manuscript_global.h" 

using namespace cv;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Hols the boundries of seprating Seed from the left to the right . </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class MANUSCRIPT_EXPORT seprateLine {
private:
	int _left;
	int _right;
	int _length;
	double _sumWeight;
	char MaxIndex(char i1,char i2,char i3);	

public:
	seprateLine();
	seprateLine(int left, int right);//row, column
	seprateLine(seprateLine*& other);
	int getLeft();
	int getRight();
	int getLength();
	void setSumWeight(Mat Distance,int* seprate,int* medial);
	double getSumWeight();
	void extendSeedToSeam(Mat distance,int* seprateSeed,int* seprateSeem);
	int extendSeedToSeamCol(Mat distance,int row,int col,int* seprateSeem);
	virtual ~seprateLine();
};

#endif

