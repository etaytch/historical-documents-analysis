#ifndef _IMAGECOMBINER_H_
#define _IMAGECOMBINER_H_ 
#include <opencv\cv.h>

class ImageCombiner {
public:
	virtual void combine(cv::Mat a, cv::Mat b, cv::Mat r){
		cv::add(a,b,r);
	}
};

#endif 

