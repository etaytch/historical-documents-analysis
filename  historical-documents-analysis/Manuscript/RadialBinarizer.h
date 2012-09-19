#ifndef __binarizer_H_ 
#define __binarizer_H_

#include "binarizer.h"

class MANUSCRIPT_EXPORT RadialBinarizer : public Binarizer{
	cv::Mat _radial_map;

public:
	RadialBinarizer(void);
	~RadialBinarizer(void);

	bool getRadialLevel(int row, int col, int radius);
	int  getOneCount(uchar by);
	void computeRadialMap();
	virtual Mat binarize() ;
};

#endif 