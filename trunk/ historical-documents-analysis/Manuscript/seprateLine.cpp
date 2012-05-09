#include "SeprateLine.h"

using namespace cv;

SeprateLine::SeprateLine(){

}
// constructor
SeprateLine::SeprateLine(int left,int right){
	_left = left;
	_right = right;
	_length = _right - _left;
	_sumWeight = 0;
}
//copy constructor
SeprateLine::SeprateLine(SeprateLine*& other){
	_left = other->getLeft();
	_right = other->getRight();
	_length = other->getLength();
}
//  ************************************  //
// getters 
int SeprateLine::getLeft(){
	return _left;
}

int SeprateLine::getRight(){
	return _right;
}

int SeprateLine::getLength(){
	return _length;
}

double seprateLine::getSumWeight(){
	return _sumWeight;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Sets the sum weight of the distance between seprate seed and the medial line. </summary>
///
/// <remarks>	Mohamad, 3/22/12. </remarks>
///
/// <param name="SeamMap">	 the seam map. </param>
/// <param name="seprate">	 the seprate Seed. </param>
/// <param name="medial"> 	the medial . </param>
/// <param name="height"> 	The height image. </param>
/// <param name="width">  	The width image. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SeprateLine::setSumWeight(double** SeamMap,int* seprate,int* medial,int height,int width){
	int i=0;
	for (i=_left+1;i<=_right;i++){
		double weight = SeamMap[seprate[i]][i]-SeamMap[medial[i]][i];
		if (weight < 0)
			weight = weight*-1.0;
		_sumWeight = _sumWeight + weight ;
	}
	_sumWeight = _sumWeight/(_right - _left);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Extends the seprating Seed to the sides of the image </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
///
/// <param name="image">	  	The image. </param>
/// <param name="SeamMap">	  	seam map. </param>
/// <param name="seprateSeed">	the seprate seed. </param>
/// <param name="final">	  	the final that will contain the seprate Line. </param>
/// <param name="medial">	  	 medial Line. </param>
/// <param name="height">	  	The height of image. </param>
/// <param name="width">	  	The width of image. </param>
/// <param name="pos">		  	The position if Seprate UP == 1 or Seprate Down == -1. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SeprateLine::findLine(Mat image,double** SeamMap,int* seprateSeed,int * final,int * medial ,int height,int width,int pos){
	int i=0;
//////////////////////////////////////////////
	//copy seprate Seed to final
	for (i=_left;i<=_right;i++){
		image.at<uchar>(seprateSeed[i],i) = 100;
		final[i] = seprateSeed[i];
	}
/////////////////////////////////////////
	int iprev=seprateSeed[_right];
	int max =0;
	int j=0;
	int end=0;
	if (pos == -1)
		end = height -1;
////////////////////////////////////////
// extend the seprate Seed to right by finding the maximum Path to the right
	for (j=_right+1;j<width;j++){
		if (iprev<height-1 && iprev>0){
			max = findMax(SeamMap[iprev][j],SeamMap[(iprev-1)][j],SeamMap[(iprev+1)][j],pos);
			if (max == 1)	iprev = iprev -1;
			if (max == 2)   iprev = iprev +1;
			image.at<uchar>(iprev,j) = 200;
			final[j] = iprev;
		}
		else if (iprev == 0){
			max = findMax(SeamMap[iprev][j],SeamMap[(iprev+1)][j],SeamMap[(iprev+1)][j],pos);
			if (max == 1)	iprev = iprev +1;
			if (max == 2)   iprev = iprev +1;
			image.at<uchar>(iprev,j) = 200;	
			final[j] = iprev;
		}
		else{
			max = findMax(SeamMap[iprev][j],SeamMap[(iprev-1)][j],SeamMap[(iprev-1)][j],pos);
			if (max == 1)	iprev = iprev -1;
			if (max == 2)   iprev = iprev -1;
			image.at<uchar>(iprev,j) = 200;	
			final[j] = iprev;
		}
		if (j==width-1){
			end = iprev;
			image.at<uchar>(iprev,j) = 200;
			final[j] = iprev;
		}
			
	}
/////////////////////////////////////////
// extend the seprate Seed to Left by finding the maximum Path to the Left
	iprev=seprateSeed[_left];
	max = 0;
	for (j=_left-1;j>=0;j--){
		if (iprev<height-1 && iprev>0){
			max = findMax(SeamMap[iprev][j],SeamMap[(iprev-1)][j],SeamMap[(iprev+1)][j],pos);
			if (max == 1)	iprev = iprev -1;
			if (max == 2)   iprev = iprev +1;
			image.at<uchar>(iprev,j) = 200;
			final[j] = iprev;
		}
		else if (iprev == 0){
			max = findMax(SeamMap[iprev][j],SeamMap[(iprev+1)][j],SeamMap[(iprev+1)][j],pos);
			if (max == 1)	iprev = iprev +1;
			if (max == 2)   iprev = iprev +1;
			image.at<uchar>(iprev,j) = 200;
			final[j] = iprev;
		}
		else{
			max = findMax(SeamMap[iprev][j],SeamMap[(iprev-1)][j],SeamMap[(iprev-1)][j], pos);
			if (max == 1)	iprev = iprev - 1;
			if (max == 2)   iprev = iprev - 1;
			image.at<uchar>(iprev,j) = 200;
			final[j] = iprev;
		}
	}
///////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Searches for the first maximum. </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
///
/// <param name="i1"> 	Zero-based index of the 1. </param>
/// <param name="i2"> 	Zero-based index of the 2. </param>
/// <param name="i3"> 	Zero-based index of the 3. </param>
/// <param name="pos">	The position. </param>
///
/// <returns>	The found maximum. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

int SeprateLine::findMax(double i1,double i2,double i3,int pos){
	int i=0,ans = 0;
	double max=-10000;
	double arr[] = {i1,i2,i3};
		for (i=0;i<3;i++){
			if (arr[i]>max){
				max = arr[i];
				ans = i;
			}
		}
	if (i2==i3 && ans!=0){
			if (pos == 1){
				ans = 0;
			}
			else{
				ans = 0; 
			}
		}
	return ans;
}

SeprateLine::~SeprateLine(){
}