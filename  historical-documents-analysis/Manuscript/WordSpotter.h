#ifndef _WORDSPOTTER 
#define _WORDSPOTTER 

#include <opencv/cv.h>
#include <opencv2/core/core.hpp>

#include "manuscript_global.h"

using namespace cv ;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Base class for Word spotting algorithms  </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////


class MANUSCRIPT_EXPORT WordSpotter {
protected:
	Mat  _image ;

public:
	WordSpotter(void);
	~WordSpotter(void);
};

#endif 
