#ifndef _WORDSPOTTER 
#define _WORDSPOTTER 

#include "DImage.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Base class for Word spotting algorithms  </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class WordSpotter {
protected:
	DImage  _Image ;

public:
	WordSpotter(void);
	~WordSpotter(void);
};

#endif 
