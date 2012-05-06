#ifndef _IMAGE_TRANSFORMATION_ 
#define _IMAGE_TRANSFORMATION_

#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include "manuscript_global.h"

using namespace cv ;

class MANUSCRIPT_EXPORT ImageTransformation{
protected:
	Mat _mat ;

public:
	ImageTransformation() {;}
	~ImageTransformation(void)   { _mat.release() ; }

	void    set(Mat mat)    { _mat = mat ; }
	virtual Mat transform() { return _mat.clone() ; }
};

#endif
