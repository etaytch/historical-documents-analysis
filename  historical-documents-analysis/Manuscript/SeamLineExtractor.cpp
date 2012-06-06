#include <iostream>
#include <algorithm>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "seprateLine.h"
#include "ImageCombiner.h"
#include "DImage.h"
#include "SeamLineExtractor.h"
#include "TextLine.h"
#include "Tools.h"
#include "ImageTools.h"
using namespace cv;
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Extracts lines of a given text image. </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
	// the Main  Loop That extracts a text Lines
	//1. find a medial , 
		//1.1 by finding The Lowest pixel in the last column on the Seam Map Copy 
	    //1.2 find the Lowest Path from the last column to the first column by 
		//1.3 the medial is stored in medial Variable , it's length is the same as the width image 
			 // so every member in the array is a index row value in the image .
	//2. find the seprating Seeds (UP,Down) according to the Medial that we found.
	//3. find the best Seprating Seed :
		//3.1 remain the tallest 30% seeds.
		//3.2 we calculate the distance from the medial from the remain seeds
		//3.3 remain the highest  30% Distance seeds .
		//3.4 take the tallest Seed remain and it will be the Seprating Seed.
		//3.5 we extend the Seprating to the left and the Rigth .
	//4. we removed this area from the Seam map Copy , cause when we try to find another medial it will find for us a different medial.
	//5. save the points into The TextLine vector 
	//6. make this loop as the number of lines in the image .

/// <param name="textLine">	 vector that will contain the data of the lines extracted. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SeamLineExtractor::extract(vector<TextLine*>& textLine){

	int* medialSeam = new int[_image.cols];
	int* upSeprateSeed = new int[_image.cols];
	int* downSeprateSeed = new int[_image.cols];
	int* upSeprateIndex = new int[_image.cols];
	int* downSeprateIndex = new int[_image.cols];

	_seamMap = Mat(_image.rows,_image.cols,CV_32F,Scalar(0));
	buildSeamMap();

	Mat tempSeamMap = _seamMap.clone();
	float max = getRowMax(tempSeamMap, tempSeamMap.cols-1) ;
	for(int index = 0 ; index < _lines ; index++){
		memset(upSeprateSeed,0,_image.cols);
		memset(downSeprateSeed,_image.rows - 1,_image.cols);
		memset(medialSeam,0,_image.cols);
		findMedialSeam(medialSeam, tempSeamMap); // find the medial    1.

		for (int i = _image.cols-1 ; i >= 0 ; i--){
			sepratingSeeds(medialSeam[i], i, upSeprateSeed, -1); // seprating Seed Up   2.
			sepratingSeeds(medialSeam[i], i, downSeprateSeed, 1); // seprating Seed down    2.
		}
		seprateLine* upperSeed = findSepratingSeed(upSeprateSeed, medialSeam);
		upperSeed->extendSeedToSeam(_distanceMap, upSeprateSeed, upSeprateIndex);

		seprateLine* lowerSeed = findSepratingSeed(downSeprateSeed, medialSeam);
		lowerSeed->extendSeedToSeam(_distanceMap, downSeprateSeed, downSeprateIndex);

		textLine.push_back(removeLineAndAddPoints(tempSeamMap, upSeprateIndex, downSeprateIndex, max));
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Removes the line and add points to the Text Line. </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 4/2/12. </remarks>
///
/// <param name="seamMapCopy">	The seam map copy. </param>
/// <param name="finalUp">	  	[in,out] If non-null, the final up. </param>
/// <param name="finalDown">  	[in,out] If non-null, the final down. </param>
/// <param name="setMax">		the max value of the last column . </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

TextLine* SeamLineExtractor::removeLineAndAddPoints(Mat seamMap, int* seprateUpSeem, int* seprateDownSeem,float setMax){
	TextLine* line = new TextLine() ;
	int min = MinArray(seprateUpSeem,_image.cols);
	int max = MaxArray(seprateDownSeem,_image.cols);
	for (int j = 0 ; j < seamMap.cols ; j++){
		line->setPoints(Point(seprateUpSeem[j],j),Point(seprateDownSeem[j],j));  // 5.
	}

	for(int i = seprateUpSeem[seamMap.cols-1] ; i <= seprateDownSeem[seamMap.cols-1] ; i++){  //     4.
			seamMap.at<float>(i,seamMap.cols-1) = setMax; 
	}
	line->setRect(min, max, seamMap.cols, max - min);
	return line;
}

// We assume the Mat is one channel with float values 

float SeamLineExtractor::getRowMax(Mat m, int row){
	float max = m.at<float>(row,0);
	for (int i = 1 ; i < m.cols ; i++){	
		if ( max < m.at<float>(row,i) )
			max = m.at<float>(row,i);
	}
	return max ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>Building the Seam Map //
/// 1.build the Seam map Right To Left according to the Distance Transform .
/// 2.build the Seam map Left To Right according to the Distance Transform .
/// 3.Blend in the two Seam map Right -> Left & Left -> Right . </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
///
////////////////////////////////////////////////////////////////////////////////////////////////////

void SeamLineExtractor::buildSeamMap(){
	Mat seamRtoLimage(_image.rows,_image.cols,CV_32F,Scalar(0));
	Mat seamLtoRimage(_image.rows,_image.cols,CV_32F,Scalar(0));
	for (int i = 0 ; i < _seamMap.rows ; i++){	
		seamLtoRimage.at<float>(i,0) = _distanceMap.at<char>(i,0);
		seamRtoLimage.at<float>(i,_seamMap.cols-1 - i) = _distanceMap.at<char>(i,_seamMap.cols-1 - i);
	}
	for(int j = 1 ; j < _seamMap.cols ; j++){
		buildSeamMapCol(seamLtoRimage,j,-1);
		buildSeamMapCol(seamRtoLimage,_seamMap.cols - 1 - j,1);
	}
	ImageCombiner combine;
	combine.combine(seamRtoLimage,seamLtoRimage,_seamMap);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Seam Map Builder. </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 4/2/12. </remarks>
///
/// <param name="Seam">	   	The seam. </param>
/// <param name="col">	   	the column to be builded. </param>
/// <param name="pos">	   	The position. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SeamLineExtractor::buildSeamMapCol(Mat seam,int col,int pos){
	float min = 0;
	float center , up , down;

	center = seam.at<float>(0,col + pos);
	down = seam.at<float>(1,col + pos);
	min = std::min(center,(float)0.7 * down);
	seam.at<float>(0,col) =  (float)(2.0 * (_distanceMap.at<char>(0,col))  + min);
	for(int i = 1 ; i < seam.rows - 1 ; i++){
		center = seam.at<float>(i, col + pos);
		up = seam.at<float>(i - 1, col + pos);
		down = seam.at<float>(i + 1, col + pos); 
		min = Min(center,(float)0.7 * up,(float)0.7 * down);					
		seam.at<float>(i,col) = (float)(2.0 * (_distanceMap.at<char>(i,col))  + min);
	}
	center = seam.at<float>(seam.rows - 1,col + pos);
	up = seam.at<float>(seam.rows - 2, col + pos);
	min = std::min(center,(float)0.7 * up);
	seam.at<float>(seam.rows - 1,col) =  (float)(2.0 * (_distanceMap.at<char>(seam.rows - 1,col))  + min);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	finds a medial Seam in the Seam Map .
///				medial array is an array of indexes , every element in medial 
///				is the row suitable for a col in image
///				example : say the 10th member has a value 30
///				it means that we are referring to  (30,10) pixel in image </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
///
/// <param name="medial">	  	 the medial. </param>
/// <param name="seamMapCopy">	 the seam map copy. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SeamLineExtractor::findMedialSeam(int* medial,Mat temoSeamMap){
	int nextRow = 0,min = 0;
	nextRow = MinColIndex(temoSeamMap,temoSeamMap.cols - 1);
	medial[_seamMap.cols-1] = nextRow;
	float center, up, down;
	for (int col = _seamMap.cols-1 ; col > 0 ; col--){
		center = temoSeamMap.at<float>(nextRow,col - 1);
		up = (nextRow == 0 ) ? 0 : temoSeamMap.at<float>(nextRow - 1,col - 1);
		down = (nextRow == _seamMap.rows - 1)  ? 0 : temoSeamMap.at<float>(nextRow + 1,col - 1);
		if (nextRow > 0 && nextRow < _seamMap.rows - 1){
			min = MinIndex(center,up,down);
			if (min == 1) 
				nextRow = nextRow - 1;
			if (min == 2) 
				nextRow = nextRow + 1;
			medial[col-1] = nextRow;
		}
		else if (nextRow == 0){
			min = MinIndex(center,down,down);
			if (min != 0) 
				nextRow = nextRow + 1;
			medial[col-1] = nextRow;
		}
		else{
			min = MinIndex(center,up,up);
			if (min != 0) 
				nextRow = nextRow - 1;
			medial[col-1] = nextRow;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	find the Seprating Seeds Up  & Down , and store them in sepratUp </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
///
/// <param name="row">			row </param>
/// <param name="col">			col </param>
/// <param name="seprate">		the seprate Array Seeds. </param>
/// <param name="pos">			to go up or down . </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SeamLineExtractor::sepratingSeeds(int row,int col, int* seprate,int pos){

	if (col == _seamMap.cols - 1) {
		sepratingSeedsBorder(row, col, seprate, pos, -1);
	}
	else if (col == 0 )	{
		sepratingSeedsBorder(row, col, seprate, pos, 1);
	}
	else{
		double avg1 = (_seamMap.at<float>(row,col) + _seamMap.at<float>(row,col-1) + _seamMap.at<float>(row,col+1))/3.0;
		double avg2 = 0.0; 
		int flag = 1;
		for (int i = row + pos ; flag == 1 && i >= 0 && i < _seamMap.rows ;i = i + pos){
			avg2 = (_seamMap.at<float>(i,col) + _seamMap.at<float>(i,col-1)+ _seamMap.at<float>(i,col+1))/3.0;
			if (avg2 - avg1 < 0){
				seprate[col] = i;
				flag = 0;
			}
			else{
				avg1 = avg2;
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	find the Seprating Seeds Up  & Down , and store them in sepratUp </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
///
/// <param name="row">			row </param>
/// <param name="col">			col </param>
/// <param name="seprate">		the seprate Array Seeds. </param>
/// <param name="pos">			to go up or down . </param>
/// <param name="dir">			to go right or left on the border . </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
void SeamLineExtractor::sepratingSeedsBorder(int row,int col,int* seprate,int pos, int dir){
		double avg1 = (_seamMap.at<float>(row,col) + _seamMap.at<float>(row,col + dir))/2.0;
		double avg2 = 0.0; 
		int flag = 1;
		for (int i = row + pos ; flag == 1 && i >= 0 && i < _seamMap.rows ; i = i + pos){
			avg2 = (_seamMap.at<float>(i,col) + _seamMap.at<float>(i,col + dir))/2.0; 
			if (avg2 - avg1 < 0){
				seprate[col] = i;
				flag = 0;
			}
			else{
				avg1 = avg2;
			}
		}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Merge continuos seeds togother in one container. </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 4/2/12. </remarks>
///
/// These arrays hold the index of the row for each column (0..cols)
/// <param name="seperateSeedCols">  	seprate Seeds indexs. </param>
/// <param name="medialCols">	medial seam indexs. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
seprateLine* SeamLineExtractor::findSepratingSeed(int* seperateSeedCols, int* medialCols){

	vector<seprateLine*> seprateSeeds; //will contain seprate Up Seeds

	mergeContinuosSeeds(seperateSeedCols, seprateSeeds);	
	filterShortSeeds(seprateSeeds);

	//    calculate the seeds distance from the medial
	for (unsigned int i = 0 ;i < seprateSeeds.size() ; i++)
		seprateSeeds[i]->setSumWeight(_distanceMap, seperateSeedCols, medialCols);

	filterLightSeeds(seprateSeeds);

	int longestSeamIdx = getLongestSeed(seprateSeeds);

	return seprateSeeds[longestSeamIdx] ;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Merge continuos seeds togother in one container. </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 4/2/12. </remarks>
///
/// <param name="seprateSeedCols">  	seprate Seed indexs. </param>
/// <param name="seprateSeeds">	contains the seprating seeds </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SeamLineExtractor::mergeContinuosSeeds(int* seprateSeedCols, vector<seprateLine*>& seprateSeeds){
	int start = 0 ;
	for (int i = 1 ; i < _seamMap.cols ; i++){
		if (abs(seprateSeedCols[i-1] - seprateSeedCols[i]) > 1 ){
			seprateSeeds.push_back(new seprateLine(start,i-1));
			start = i;
		}
	}
	seprateSeeds.push_back(new seprateLine(start, _seamMap.cols-1));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary> 	Extracts The longest seeds from the vector. </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 4/2/12. </remarks>
///
/// <param name="seperate_seeds">   	contains the seprating seeds. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////
int SeamLineExtractor::getLongestSeed(vector<seprateLine*>& seperate_seeds ){
	int maxi = 0;
	double max = (seperate_seeds[0]->getLength() + seperate_seeds[0]->getSumWeight())/2.0;
	for(unsigned int i = 0 ; i < seperate_seeds.size() ; i++){
		if ((seperate_seeds[i]->getLength() + seperate_seeds[i]->getSumWeight())/2.0  > max){
				max = (seperate_seeds[i]->getLength() + seperate_seeds[i]->getSumWeight())/2.0;
				maxi = i;
			}
	}
	return maxi ;
}



// compare's the length between two seeds 
bool SeedSizeCompare (seprateLine* i,seprateLine* j) { return (i->getLength() > j->getLength()); }

//removes the shortest seeds by a given threshold
void SeamLineExtractor::filterShortSeeds(vector<seprateLine*>& seprateSeeds){
	std::sort(seprateSeeds.begin(),seprateSeeds.end(), SeedSizeCompare);
	int remove_from = (int) (seprateSeeds.size() * _seedFilterThreshold);
	seprateSeeds.erase(seprateSeeds.begin() + remove_from, seprateSeeds.end()) ;
}

//compare's the weight between two seeds
bool SeedWeightCompare (seprateLine* i,seprateLine* j) { return (i->getSumWeight()>j->getSumWeight());}

//removes the lightest seeds by a given thershold
void SeamLineExtractor::filterLightSeeds(vector<seprateLine*>& seprateSeeds){
	std::sort(seprateSeeds.begin(),seprateSeeds.end(), SeedWeightCompare);
	int remove_from = (int)(seprateSeeds.size() * _seedFilterThreshold ) ;
	seprateSeeds.erase(seprateSeeds.begin() + remove_from, seprateSeeds.end()) ;
}
