#ifndef  _IMAGETOOLS_H_ 
#define _IMAGETOOLS_H_

#include <opencv\cv.h>
using namespace cv ;

int MinRowIndex(Mat m, int row){
	int  midx = 0 ;
	Mat_<uchar> mat = m ;
	for (int i = 1 ; i < mat.cols ; i++)
		if ( mat(row, midx) > mat(row, i)) 
			midx = i ;
	return midx ;
}

int MinColIndex(Mat m, int col){
	int  midx = 0 ;
	Mat_<uchar> mat = m ;
	for (int i = 1; i < mat.rows; i++)
		if ( mat(midx, col) > mat(i, col))
			midx = i ;
	return midx ;
}

int MaxRowIndex(Mat m, int row){
	int  midx = 0 ;
	Mat_<uchar> mat = m ;
	for (int i = 1 ; i < mat.cols ; i++)
		if ( mat(row, midx) < mat(row, i)) 
			midx = i ;
	return midx ;
}

int MaxColIndex(Mat m, int col){
	int  maxi = 0 ;
	Mat_<uchar> mat = m ;
	for (int i = 1; i < mat.rows; i++)
		if ( mat(maxi, col) < mat(i, col))
			maxi = i ;
	return maxi ;
}

#endif 