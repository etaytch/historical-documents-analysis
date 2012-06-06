#ifndef _COMPONENEXTRACTOR_H 
#define _COMPONENEXTRACTOR_H 

#include <opencv/cv.h>
#include <opencv2/core/core.hpp>

#include "manuscript_global.h" 
#include "DImage.h"
#include "ConnectedComponent.h"

using namespace cv ;

class MANUSCRIPT_EXPORT ComponentExtractor{
protected:
	DImage _image ;

public:
	ComponentExtractor(void)  {;}
	~ComponentExtractor(void) {;}

	void setImage(DImage& img) { _image = img; } 

	virtual void extract(vector<ConnectedComponent*>&) = 0 ;
};

#endif 