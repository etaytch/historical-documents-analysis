#ifndef _IMAGE_OPERATION_ 
#define _IMAGE_OPERATION_

#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include "manuscript_global.h"

using namespace cv ;

class MANUSCRIPT_EXPORT ImageOperation{
protected:
	Mat _mat ;

public:
	ImageOperation() {;}
	~ImageOperation(void)   { _mat.release() ; }

	void    set(Mat mat)    { _mat = mat ; }
	virtual MatND project()   { return _mat.clone() ; }
};

#endif
