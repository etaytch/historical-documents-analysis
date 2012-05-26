#ifndef _GLOBALBINARIZER_H 
#define _GLOBALBINARIZER_H 

#include "Binarizer.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Global binarizer implment a global binarization algorithm </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class MANUSCRIPT_EXPORT GlobalBinarizer : public Binarizer {
	float  _thershold ;

public:
	GlobalBinarizer(void);
	GlobalBinarizer(float thershold);
	~GlobalBinarizer(void);
	
	void setThershold(float threshold){
		_thershold = threshold ;
	}

	DImage* binarize();
};

#endif 