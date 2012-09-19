#ifndef _OTSUBINARIZER_H 
#define _OTSUBINARIZER_H 

#include "Binarizer.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Otsul binarizer class implements the Otsu binarization algorithm </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class MANUSCRIPT_EXPORT OtsulBinarizer : public Binarizer {

public:
	OtsulBinarizer(void);
	~OtsulBinarizer(void);

	Mat binarize();
};

#endif 