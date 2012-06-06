

#include "seprateLine.h"

using namespace cv;

seprateLine::seprateLine(){

}
// constructor
seprateLine::seprateLine(int left,int right){
	_left = left;
	_right = right;
	_length = _right - _left;
	_sumWeight = 0;
}
//copy constructor
seprateLine::seprateLine(seprateLine*& other){
	_left = other->getLeft();
	_right = other->getRight();
	_length = other->getLength();
}
 //  ************************************  //
// getters 
int seprateLine::getLeft(){
	return _left;
}

int seprateLine::getRight(){
	return _right;
}

int seprateLine::getLength(){
	return _length;
}

double seprateLine::getSumWeight(){
	return _sumWeight;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Sets the sum weight of the distance between seprate seed and the medial line. </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna, 3/22/12. </remarks>
///
/// <param name="distacne">	 distance map. </param>
/// <param name="seprate">	 the seprate Seed. </param>
/// <param name="medial"> 	the medial . </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void seprateLine::setSumWeight(Mat Distance,int* seprate,int* medial){
	for (int i = _left; i <= _right; i++){
		int weight = Distance.at<char>(seprate[i],i) - Distance.at<char>(medial[i],i);
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
/// <param name="distacne">	  	distacne map. </param>
/// <param name="seprateSeed">	the seprate seed. </param>
/// <param name="seprate Seem">	  	seprate Seem. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void seprateLine::extendSeedToSeam(Mat distance,int* seprateSeed,int* seprateSeem){

	//copy seprate Seed to final
	for (int i =_left ; i <= _right ; i++){
		seprateSeem[i] = seprateSeed[i];
	}

	int row = seprateSeed[_right];

// extend the seprate Seed to right by finding the maximum Path to the right
	for (int col =_right + 1; col < distance.cols ; col++){
		row = extendSeedToSeamCol(distance,row,col,seprateSeem);
	}
// extend the seprate Seed to Left by finding the maximum Path to the Left
	row = seprateSeed[_left];
	for (int col =_left-1 ;col >=0 ; col--){
		row = extendSeedToSeamCol(distance,row,col,seprateSeem);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	finds the next row in the seprate Seam for a given column . </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
///
/// <param name="distance"> 	distance map </param>
/// <param name="row"> 	the previous row. </param>
/// <param name="col"> 	column. </param>
/// <param name="seprateSeem"> 	seprate Seem. </param>
///
/// <returns>	return the next row . </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
int seprateLine::extendSeedToSeamCol(Mat distance,int row,int col,int* seprateSeem){
		char max = 0;
		if (row < distance.rows-1 && row>0){
			max = MaxIndex(distance.at<char>(row,col),distance.at<char>(row - 1,col),distance.at<char>(row + 1,col));
			if (max == 1)	row = row -1;
			if (max == 2)   row = row +1;
			seprateSeem[col] = row;
		}
		else if (row == 0){
			max = MaxIndex(distance.at<char>(row,col),distance.at<char>(row + 1,col),distance.at<char>(row + 1,col));
			if (max != 0)	row = row +1;
			seprateSeem[col] = row;
		}
		else{
			max = MaxIndex(distance.at<char>(row,col),distance.at<char>(row - 1,col),distance.at<char>(row - 1,col));
			if (max != 0)	row = row - 1;
			seprateSeem[col] = row;
		}
		return row;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Searches for the first maximum index . </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
///
/// <param name="i1"> 	Zero-based index of the 1. </param>
/// <param name="i2"> 	Zero-based index of the 2. </param>
/// <param name="i3"> 	Zero-based index of the 3. </param>
///
/// <returns>	The first maximum index. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

char seprateLine::MaxIndex(char i1,char i2,char i3){
	int i=0;
	char ans = 0;
	char arr[] = {i1,i2,i3};
	char max = arr[0];
		for (i = 1; i < 3; i++){
			if (arr[i] > max){
				max = arr[i];
				ans = i;
			}
		}
	if (i2==i3 && ans!=0){
		ans=0;	
	}
	return ans;
}

seprateLine::~seprateLine(){
	
}