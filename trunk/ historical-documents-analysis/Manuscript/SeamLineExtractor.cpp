#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "SeparateLine.h"
#include "OtsulBinarizer.h"
#include "DImage.h"
#include "SeamLineExtractor.h"
#include "TextLine.h"
using namespace cv;
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Extracts lines of a given text image. </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
///
/// <param name="textLine">	 vector that will contain the data of the lines extracted. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SeamLineExtractor::extract(vector<TextLine*>& textLine){
	int i=0,j=0;
	DImage* gray = _image.rgb2gray(); // convert to gray scale
	OtsulBinarizer binarizer ;
	DImage* binary = gray->binarize(binarizer);
	Mat image = binary->getMat();

	int height = image.rows; // variable image is the binary image
	int width = image.cols;
	Mat_<char> imgDistance = image.clone(); // signed Distance Transform
	image.create(
	int* medial = new int[width];
	int* seprateUp = new int[width];
	int* seprateDown = new int[width];
	int* finalUp = new int[width];
	int* finalDown = new int[width];
	double** SeamLtoR;
	double** SeamRtoL;
	double** SeamMap;
	double** SeamMapCopy;
	SeamLtoR = new double*[height];
	SeamRtoL = new double*[height];
	SeamMap = new double*[height];
	SeamMapCopy = new double*[height];
	for (i=0;i<height;i++){
		SeamLtoR[i] = new double[width];
		SeamRtoL[i] = new double[width];
		SeamMap[i] = new double[width];
		SeamMapCopy[i] = new double[width];
	}
	for (i = 0; i < height; i++){
		for (j = 0; j < width; j++){
			SeamLtoR[i][j] = 0;
			SeamRtoL[i][j] = 0;
			SeamMap[i][j] = 0;
			SeamMapCopy[i][j] = 0;
		}
	}
	// The Distance Transform calculates the cityblock distacne drom the nearest zero
	//in our distance Transform we didn't remove components "like dots or small objects" 
	//that can damage the image proccess .
/************************************************************************************/
	for (i=0;i<height;i++){
		for(j=0;j<width;j++){
			if (image.at<uchar>(i,j) != 0){
				imgDistance.at<char>(i,j) =  distanceTransform(i,j,height,width,image);
			}
		}
	}   // Distance Map  , the variable Mat that has the distance Map is "imgDistance"
	for (i=0;i<height;i++){
		for(j=0;j<width;j++){
			if (image.at<uchar>(i,j)==0 && !isContour(i,j,height,width,image)){
				imgDistance.at<char>(i,j) = -1*distanceTransform(i,j,height,width,image);
			}
		}
	}

/**********************************************************************************/

///////////////////////////////////////////////////////////////////////////
	//Building the Seam Map //
	//1.build the Seam map Right To Left according to the Distance Transform .
	//2.build the Seam map Left To Right according to the Distance Transform .
	//3.Blend in the two Seam map Right -> Left & Left -> Right .
	SeamFromRightToLeft(height,width,SeamRtoL,imgDistance);
	SeamFromLeftToRight(height,width,SeamLtoR,imgDistance);
	seamMapBlending(height,width,SeamMap,SeamLtoR,SeamRtoL);
///////////////////////////////////////////////////////////////////////////	
	// Seam Map Copy is just a help variable that we used .
	for (i=0;i<height;i++){
		for(j=0;j<width;j++){
			SeamMapCopy[i][j] = SeamMap[i][j];
		}
	}
//////////////////////////////////////////////////////////////////////////

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

//	int linesNum=estimateLinesNum(image); // number of lines in the document
	int linesNum ;
	printf("Enter Number Of Lines :\n");
	cin >> linesNum;
	int index = 0;
	for(index=0;index<linesNum&&((finish(height,width,SeamMapCopy))==0);index++){
		for (i=0;i<width;i++){
				seprateUp[i]=0;
				seprateDown[i]=height-1;
				medial[i]=0;
			}
		findMedialSeam(height,width,SeamMap,imgDistance,medial,SeamMapCopy); // find the medial    1.
		for (i=width-1;i>=0;i--){
			sepratingSeamUp(height,width,medial[i],i,SeamMap,imgDistance,seprateUp); // seprating Seed Up   2.
			sepratingSeamDown(height,width,medial[i],i,SeamMap,imgDistance,seprateDown); // seprating Seed down    2.
		}

		findSepratingSeam(height,width,seprateUp,seprateDown,SeamMap,medial,image,finalUp,finalDown); //finds the seprating Seams (Up,Down)  3.
		
		TextLine* line = new TextLine() ;
		int min = 10000;
		int max = -10000;
		for (j=0;j<width;j++){
			min = 10000;
			max = -100000;
			line->setPoints(Point(finalUp[j],j),Point(finalDown[j],j));  // 5.
			for(i=finalUp[j];i<=finalDown[j];i++){ //     4.
					SeamMapCopy[i][j] = 100000;
					if (finalUp[j] < min){
						min = finalUp[j];
					}
					if (finalDown[j] >max){
						max = finalDown[j];
					}
			}
		}
		line->setRect(min,max,max-min,width);
		textLine.push_back(line);
	}
////////////////////////////////////////////////////////////////////////////////////


	delete SeamLtoR;
	delete SeamRtoL;
	delete SeamMap;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	checks if all the last column of the Seam Map is 100000 </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
///
/// <param name="height">	  	The height. </param>
/// <param name="width">	  	The width. </param>
/// <param name="SeamMapCopy">	 the seam map copy. </param>
///
/// <returns>	return 1 if all last column is 100000 else return 0. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

int SeamLineExtractor::finish(int height,int width,double** SeamMapCopy){
	int i=0;
	int j=0;
	int ans = 1;
	for (i=0;i<height;i++){
			if (SeamMapCopy[i][width-1] != 100000){
				ans = 0;
			}
	}
	return ans;
}
/*
	
checks if the image(row,col) is on the contour

*/

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	checks if the row col is on the contour. </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
///
/// <param name="row">   	The row. </param>
/// <param name="col">   	The col. </param>
/// <param name="height">	The height. </param>
/// <param name="width"> 	The width. </param>
/// <param name="image"> 	The image. </param>
///
/// <returns>	true if contour, false if not. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

bool SeamLineExtractor::isContour(int row,int col,int height,int width,Mat image){
	int i=0,j=0;
	for (i=row-1;i<row+2;i++){
		for(j=col-1;j<col+2;j++){
			if (isInBound(i,j,height,width)){
				if (image.at<char>(i,j) > 0)
					return true;
			}
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	calculates the shortest distance of a given pixel to its closest zero. </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
///
/// <param name="i">	 	row. </param>
/// <param name="j">	 	col. </param>
/// <param name="height">	The height. </param>
/// <param name="width"> 	The width. </param>
/// <param name="image"> 	The image. </param>
///
/// <returns>	. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

int SeamLineExtractor::distanceTransform(int i,int j,int height,int width,Mat image) {
	bool found = false;
	int dist = 0;
	int originRow = i;
	int originCol = j;
	int tRow = originRow;
	int tCol = originCol;

	while (!found) {
		dist++;
		for (int i = 0; i <= dist; i++) {
			tRow = (originRow + i);
			tCol = (originCol + dist - i);
			if (isInBound(tRow, tCol, height,width) && image.at<uchar>(tRow,tCol) == 0) {

				found = true;
				break;
			}
			tRow = (originRow - i);
			tCol = (originCol + dist - i);
			if (isInBound(tRow, tCol, height,width) && image.at<uchar>(tRow,tCol) == 0) {
				found = true;
				break;
			}
			tRow = (originRow + i);
			tCol = (originCol - dist + i);
			if (isInBound(tRow, tCol, height,width) && image.at<uchar>(tRow,tCol) == 0) {
				found = true;
				break;
			}
			tRow = (originRow - i);
			tCol = (originCol - dist + i);
			if (isInBound(tRow, tCol, height,width) && image.at<uchar>(tRow,tCol) == 0) {
				found = true;
				break;
			}
		}
	}
	return dist; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	checks if row & col is in image dimentions </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
///
/// <param name="row">   	The row. </param>
/// <param name="col">   	The col. </param>
/// <param name="height">	The height. </param>
/// <param name="width"> 	The width. </param>
///
/// <returns>	true if in bound, false if not. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

bool SeamLineExtractor::isInBound(int row, int col,int height,int width) {

	if ((row >= 0 && row < height && col >= 0 && col < width)) {
		return true;
	} else {
		return false;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	build Seam Map Left -> Right , copys the last column of the distance map 
/// 			, and then starts building
///				the Seam map .</summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
///
/// <param name="height">  	The height. </param>
/// <param name="width">   	The width. </param>
/// <param name="Seam">	   	 the seam. </param>
/// <param name="distance">	The distance Map. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SeamLineExtractor::SeamFromLeftToRight(int height,int width,double** Seam,Mat distance){
	int i=0,j=0;
	double min = 0.0;
	for (i=0;i<height;i++){	
		Seam[i][0] = double(distance.at<char>(i,0));
	}

	for(j=1;j<width;j++){
		for(i=0;i<height;i++){
				  if (i==0){
					  min = findMinDouble(Seam[i][j-1],Seam[i][j-1],Seam[i+1][j-1]*0.7);					
				  }
				  else if (i == height-1){
					  min = findMinDouble(Seam[i][j-1],Seam[i][j-1],Seam[i-1][j-1]*0.7);						
				  }
				  else{
					  min = findMinDouble(Seam[i-1][j-1]*0.7,Seam[i][j-1],Seam[i+1][j-1]*0.7);					
				  }
				  Seam[i][j] = 2.0*double(distance.at<char>(i,j)) + min;
		}	
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	build Seam Map Right -> Left , copys the last column of the distance map 
/// 			, and then starts building
///				the Seam map .</summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
///
/// <param name="height">  	The height. </param>
/// <param name="width">   	The width. </param>
/// <param name="Seam">	   	 the seam. </param>
/// <param name="distance">	The distance Map. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SeamLineExtractor::SeamFromRightToLeft(int height,int width,double** Seam,Mat distance){
	int i=0,j=0;
	double min = 0.0;
	for (i=0;i<height;i++){
		Seam[i][width-1] =	double(distance.at<char>(i,width-1));
	}
	for(j=width-2;j>=0;j--){
		for(i=0;i<height;i++){
				  if (i==0){
					  min = findMinDouble(Seam[i][j+1],Seam[i][j+1],Seam[i+1][j+1]*0.7);					
				  }
				  else if (i == height-1){
					  min = findMinDouble(Seam[i][j+1],Seam[i][j+1],Seam[i-1][j+1]*0.7);						
				  }
				  else{
					  min = findMinDouble(Seam[i-1][j+1]*0.7,Seam[i][j+1],Seam[i+1][j+1]*0.7);					
				  }
				  Seam[i][j] = 2.0*double(distance.at<char>(i,j))  + min;
		}	
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Searches for the first minimum double. </summary>
///
/// <remarks>	Mohamad, 3/22/12. </remarks>
///
/// <param name="i1">	Zero-based index of the 1. </param>
/// <param name="i2">	Zero-based index of the 2. </param>
/// <param name="i3">	Zero-based index of the 3. </param>
///
/// <returns>	The found minimum double. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

double SeamLineExtractor::findMinDouble(double i1,double i2,double i3){
	double arr[] = {i1,i2,i3};
	int i=0;
	double min = 10000.0;
	for (i=0;i<3;i++){
		if (arr[i]<min){
			min = arr[i];
		}
	}
	return min;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	build the Seam Map according to the Seam Map  Left -> Right and Seam Map  
/// 			Right -> Left by interpolation algorithm. </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12, </remarks>
///
/// <param name="height">  	The height. </param>
/// <param name="width">   	The width. </param>
/// <param name="SeamMap"> 	the seam map. </param>
/// <param name="SeamLToR">	 the seam l to r. </param>
/// <param name="SeamRToL">	 the seam r to l. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SeamLineExtractor::seamMapBlending(int height,int width,double** SeamMap,double** SeamLToR,double** SeamRToL){
	int i=0,j=0;
	int min = 0;
	double fa=0.0;
	double fb=0.0;
	double cols = width;
	double clr=0.0;
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			fa =(cols - j)/cols;
			fb = j/cols;
			clr = SeamRToL[i][j]*fb + SeamLToR[i][j]*fa;
			SeamMap[i][j] = clr;
		}
	}
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
/// <param name="height">	  	The height. </param>
/// <param name="width">	  	The width. </param>
/// <param name="SeamMap">	  	 the seam map. </param>
/// <param name="image">	  	The image. </param>
/// <param name="medial">	  	 the medial. </param>
/// <param name="SeamMapCopy">	 the seam map copy. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SeamLineExtractor::findMedialSeam(int height,int width,double** SeamMap,Mat image,int* medial,double** SeamMapCopy){
	int i=0,j=0,min=0;
	i = findMinMedial(height,width,SeamMapCopy);
	medial[width-1] = i;
	for (j=width-1;j>0;j--){
			if (i > 0 && i < height-1){
				int min = findMin(SeamMapCopy[i][j-1],SeamMapCopy[(i-1)][j-1],SeamMapCopy[(i+1)][j-1]);
				if (min == 1)
					i = i-1;
				if (min == 2)
					i = i+1;
					medial[j-1] = i;
					image.at<char>(i,j) = 127;
			}
			else if (i==0){
				int min = findMin(SeamMapCopy[i][j-1],SeamMapCopy[(i+1)][j-1],SeamMapCopy[(i+1)][j-1]);
				if (min == 1)
					i = i+1;
				if (min == 2)
					i = i+1;
					medial[j-1] = i;
					image.at<char>(i,j) = 127;
			}
			else{
				int min = findMin(SeamMapCopy[i][j+1],SeamMapCopy[(i-1)][j+1],SeamMapCopy[(i-1)][j+1]);
				if (min == 1)
					i = i-1;
				if (min == 2)
					i = i-1;
					medial[j-1] = i;
					image.at<char>(i,j) = 127;
			}
		}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Searches for the first minimum. </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
///
/// <param name="i1">	Zero-based index of the 1. </param>
/// <param name="i2">	Zero-based index of the 2. </param>
/// <param name="i3">	Zero-based index of the 3. </param>
///
/// <returns>	The found minimum. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

int SeamLineExtractor::findMin(double i1,double i2,double i3){
	double arr[] = {i1,i2,i3};
	int i=0;
	double min = 10000;
	int ans=0;
	for (i=0;i<3;i++){
		if (arr[i]<min){
			min = arr[i];
			ans = i;
		}
	}
	return ans;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Searches for the first minimum medial. </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
///
/// <param name="height">	  	The height. </param>
/// <param name="width">	  	The width. </param>
/// <param name="SeamMapCopy">	[in,out] If non-null, the seam map copy. </param>
///
/// <returns>	The found minimum medial. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

int SeamLineExtractor::findMinMedial(int height,int width,double** SeamMapCopy){
	int i=0;
	int ans=0;
	double min = 100000; 
	for (i=0;i<height;i++){
		if (SeamMapCopy[i][width-1]<min){
			ans = i;
			min = SeamMapCopy[i][width-1];
		}
	}
	return ans;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	find the Seprating Seeds Up , and store them in sepratUp </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
///
/// <param name="height">   	The height. </param>
/// <param name="width">		The width. </param>
/// <param name="i1">			row </param>
/// <param name="j1">			col </param>
/// <param name="SeamMap">  	the seam map. </param>
/// <param name="image">		The image. </param>
/// <param name="seprateUp">	the seprate up. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SeamLineExtractor::sepratingSeamUp(int height,int width,int i1,int j1,double** SeamMap,Mat image,int* seprateUp){
	int i=0,j=0;
	if (j1==width-1){
		double avg1 = (SeamMap[i1][j1] + SeamMap[i1][j1-1])/2;
		double avg2 = 10000; 
		int flag = 1;
		for (i=i1-1;flag == 1 && i>=0;i--){
			avg2 = (SeamMap[i][j1] + SeamMap[i][j1-1])/2; 
			if (avg2-avg1<=-1){
				seprateUp[j1] = i;
				flag =0;
			}
			else{
				avg1 = avg2;
			}
		}
	}
	else if (j1==0){
		double avg1 = (SeamMap[i1][j1] + SeamMap[i1][j1+1])/2;
		double avg2 = 10000; 
		int flag = 1;
		for (i=i1-1;flag == 1 && i>=0;i--){
			avg2 = (SeamMap[i][j1] + SeamMap[i][j1+1])/2; 
			if (avg2-avg1<=-1){
				seprateUp[j1] = i;
				flag =0;
			}
			else{
				avg1 = avg2;
			}
		}
	}
	else{
		double avg1 = (SeamMap[i1][j1] + SeamMap[i1][j1-1] + SeamMap[i1][j1+1])/3.0;
		double avg2 = 0.0; 
		double flag = 1;
		for (i=i1-1;flag == 1 && i>=0;i--){
			avg2 = (SeamMap[i][j1] + SeamMap[i][j1-1] + SeamMap[i][j1+1])/3.0;
			if (avg2-avg1<=-1){
				seprateUp[j1] = i;
				flag =0;
			}
			else{
				avg1 = avg2;
			}
		}
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	find the Seprating Seeds Down , and store them in sepratDown </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
///
/// <param name="height">   	The height. </param>
/// <param name="width">		The width. </param>
/// <param name="i1">			row </param>
/// <param name="j1">			col </param>
/// <param name="SeamMap">  	the seam map. </param>
/// <param name="image">		The image. </param>
/// <param name="seprateUp">	the seprate up. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SeamLineExtractor::sepratingSeamDown(int height,int width,int i1,int j1,double** SeamMap,Mat image,int* seprateDown){
	int i=0,j=0;
	if (j1==width-1){
		double avg1 = (SeamMap[i1][j1] + SeamMap[i1][j1-1])/2;
		double avg2 = 10000; 
		int flag = 1;
		for (i=i1+1;flag == 1 && i<height;i++){
			avg2 = (SeamMap[i][j1] + SeamMap[i][j1-1])/2; 
			if (avg2-avg1<0){
				seprateDown[j1] = i;
				flag =0;
			}
			else{
				avg1 = avg2;
			}
		}
	}
	else if (j1==0){
		double avg1 = (SeamMap[i1][j1] + SeamMap[i1][j1+1])/2;
		double avg2 = 10000; 
		int flag = 1;
		for (i=i1+1;flag == 1 && i<height;i++){
			avg2 = (SeamMap[i][j1] + SeamMap[i][j1+1])/2; 
			if (avg2-avg1<0){
				seprateDown[j1] = i;
				flag =0;
			}
			else{
				avg1 = avg2;
			}
		}
	}
	else{
		double avg1 = (SeamMap[i1][j1] + SeamMap[i1][j1-1] + SeamMap[i1][j1+1])/3.0;
		double avg2 = 10000; 
		int flag = 1;
		for (i=i1+1;flag == 1 && i<height;i++){
			avg2 = (SeamMap[i][j1] + SeamMap[i][j1-1] + SeamMap[i][j1+1])/3.0;
			if (avg2-avg1<0){
				seprateDown[j1] = i;
				flag =0;
			}
			else{
				avg1 = avg2;
			}
		}
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	finds the Seprating Seam Up & Down , according to 
/// 			the medial Seam and Seprating Seeds . </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna3/22/12. </remarks>
///
/// <param name="height">	  	The height. </param>
/// <param name="width">	  	The width. </param>
/// <param name="seprateUp">  	[in,out] If non-null, the seprate up. </param>
/// <param name="seprateDown">	[in,out] If non-null, the seprate down. </param>
/// <param name="SeamMap">	  	[in,out] If non-null, the seam map. </param>
/// <param name="medial">	  	[in,out] If non-null, the medial. </param>
/// <param name="image">	  	The image. </param>
/// <param name="finalUp">	  	[in,out] If non-null, the final up. </param>
/// <param name="finalDown">  	[in,out] If non-null, the final down. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void SeamLineExtractor::findSepratingSeam(int height,int width,int* seprateUp,int* seprateDown,double** SeamMap,int* medial,Mat image
					   ,int* finalUp,int* finalDown){
		int i=0;
		int j=0;
		vector<SeparateLine*>* seprate_Up = new vector<SeparateLine*>();//will contain seprate Up Seeds
		vector<SeparateLine*>* seprate_Down = new vector<SeparateLine*>();//will contain seprate Down Seeds
		int beginiUp=seprateUp[0];
		int beginiDown=seprateDown[0];
		int beginjUp=0;
		int beginjDown =0;
		int count =0;
///////////////////////////////////////////////////////////////////// 
/*
	put the countinus Seed in one Seed and push it to the vector .
	Down & UP
*/
		for (i=1;i<width;i++){
			if (abs(beginiUp - seprateUp[i])>1 && i<width - 1){
				seprate_Up->push_back(new SeparateLine(beginjUp,i-1));
				beginjUp = i;
			}
			if (abs(beginiDown - seprateDown[i])>1 && i<width - 1){
				seprate_Down->push_back(new SeparateLine(beginjDown,i-1));
				beginjDown = i;
			}
			if (i==width-1){
				seprate_Up->push_back(new SeparateLine(beginjUp,i));
				seprate_Down->push_back(new SeparateLine(beginjDown,i));
			}
			beginiUp = seprateUp[i];
			beginiDown = seprateDown[i];
		}
////////////////////////////////////////////////////////////////////
/*
	calculate the seeds distance from the medial

*/
		for (i = 0 ;i < seprate_Up->size()|i<seprate_Down->size();i++){
			if(i<seprate_Up->size()){
				seprate_Up->at(i)->setSumWeight(SeamMap,seprateUp,medial,height,width);
			}
			if(i<seprate_Down->size()){
				seprate_Down->at(i)->setSumWeight(SeamMap,seprateDown,medial,height,width);
			}
		}

////////////////////////////////////////////////////////////////////
		int limitUp = seprate_Up->size()*0.3;//30% Thershold on Up & Down
		int limitDown = seprate_Down->size()*0.3;
		int maxUp =-1;
		int maxDown=-1;
		int UpIndex=0;
		int DownIndex=0;
		int Upsize = seprate_Up->size();
		int Downsize = seprate_Down->size();
///////////////////////////////////////////////////////////////////////
/*
  remain the 30% tallest Seeds in seprate_Up & seprate_Down
*/
		for (i=0;i<limitUp|i<limitDown;i++){
			for (j=0;j<seprate_Up->size()|j<seprate_Down->size();j++){
				if (i<limitUp&&j<seprate_Up->size()){
					if (maxUp<seprate_Up->at(j)->getLength()){
						maxUp = seprate_Up->at(j)->getLength();
						UpIndex = j;
					}
				}
				if (i<limitDown&&j<seprate_Down->size()){	
					if (maxDown<seprate_Down->at(j)->getLength()){
						maxDown = seprate_Down->at(j)->getLength();
						DownIndex = j;
					}
				}
			}
			if (i<limitUp){
				seprate_Up->push_back(seprate_Up->at(UpIndex));
			}
			if (i<limitDown){
				seprate_Down->push_back(seprate_Down->at(DownIndex));
			}
		}
//////////////////////////////////////////////////////////////////////
		(limitUp==0) ? UpIndex = 0 : UpIndex = seprate_Up->size()-limitUp;
		(limitDown == 0) ? DownIndex = 0 : DownIndex = seprate_Down->size()-limitDown;
		limitUp = (seprate_Up->size() - UpIndex)*0.3;// Threshold for the 30 % hightest distance from the medial
		limitDown = (seprate_Down->size() - DownIndex)*0.3;
		int UpIndex1 = 0;
		int DownIndex1 = 0;
		maxUp = -1;
		maxDown = -1;
		int maximum = 100000;
///////////////////////////////////////////////////////////////////////
/*
	remain the highest 30% seeds the remains from the tallest 30%
	UP & Down
*/
		for (i=0;i<limitUp;i++){
			for (j=UpIndex;j<seprate_Up->size();j++){
				if (maxUp<seprate_Up->at(j)->getSumWeight()&&maximum>seprate_Up->at(j)->getSumWeight()){
						maxUp = seprate_Up->at(j)->getSumWeight();
						UpIndex1 = j;
				}
			}
			seprate_Up->push_back(seprate_Up->at(UpIndex1));
			maximum = maxUp;
			maxUp = -1;
		}
		 maximum = 100000;
		for (i=0;i<limitDown;i++){
			for (j=DownIndex;j<seprate_Down->size();j++){
					if (maxDown < seprate_Down->at(j)->getSumWeight()&&maximum> seprate_Down->at(j)->getSumWeight()){
						maxDown = seprate_Down->at(j)->getSumWeight();
						DownIndex1 = j;
					}
			}
				seprate_Down->push_back(seprate_Down->at(DownIndex1));
				maximum = maxDown;
				maxDown = -1;
		}
///////////////////////////////////////////////////////////////////////
/*
	take the tallest Seed from the Seeds that Remained
	Up & Down
*/

		(limitUp==0) ? UpIndex = 0 : UpIndex = seprate_Up->size()-limitUp;
		(limitDown == 0) ? DownIndex =0 : DownIndex = seprate_Down->size()-limitDown;
		int indexUpFinal = 0;
		maxUp=-1;
		for(i=UpIndex;i<seprate_Up->size();i++){
			if (seprate_Up->at(i)->getLength()>maxUp){
				maxUp = seprate_Up->at(i)->getLength();
				indexUpFinal = i;
			}
		}
		int indexDownFinal = 0;
		maxDown=-1;
		for(i=DownIndex;i<seprate_Down->size();i++){
			if (seprate_Down->at(i)->getLength()>maxDown){
				maxDown = seprate_Down->at(i)->getLength();
				indexDownFinal = i;
			}
		}
/////////////////////////////////////////////////////////////////////
		//extend the Seprate Seed Down To the Left And the Right
		seprate_Down->at(indexDownFinal)->findLine(image,SeamMap,seprateDown,finalDown,medial,height,width,-1);
		//extend the Seprate Seed Up To the Left And the Right
		seprate_Up->at(indexUpFinal)->findLine(image,SeamMap,seprateUp,finalUp,medial,height,width,1);
		delete seprate_Up;
		delete seprate_Down;

}
