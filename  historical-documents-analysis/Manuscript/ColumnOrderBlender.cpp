#include "ColumnOrderBlender.h"

ColumnOrderBlender::ColumnOrderBlender(void){;}


ColumnOrderBlender::~ColumnOrderBlender(void){;}

void ColumnOrderBlender::combine(cv::Mat a, cv::Mat b, cv::Mat r){
	r = a.clone();
	for (int i=0; i < a.rows; i++){
		for(int j=0; j < a.cols; j++){
			float w = (float)j/float(a.cols) ;
			r.at<float>(i,j) = a.at<float>(i,j)*w + b.at<float>(i,j)*(1-w);
		}
	}
}
