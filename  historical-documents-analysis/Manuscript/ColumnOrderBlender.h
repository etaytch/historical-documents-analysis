#ifndef _COLUMORDERBLENDER_H_
#define _COLUMORDERBLENDER_H_ 

#include "ImageCombiner.h"

class ColumnOrderBlender : public ImageCombiner{

public:
	ColumnOrderBlender(void);
	~ColumnOrderBlender(void);

	void combine(cv::Mat a, cv::Mat b, cv::Mat r);
};

#endif