#ifndef _Page_H 
#define _Page_H 

#include "DImage.h"
#include "Block.h"
#include "manuscript_global.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Page class maintains the properties of one page in a manuscript </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class MANUSCRIPT_EXPORT Page : DImage {
protected:
	int                _index ;
	vector<Block>      _blocks ;
public:
	Page(void);
	~Page(void);
};

#endif 
