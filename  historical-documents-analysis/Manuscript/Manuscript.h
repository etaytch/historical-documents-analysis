#ifndef _MANUSCRIPT_H 
#define _MANUSCRIPT_H 

#include <list>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>

#include "Page.h" 

using namespace std ;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Manuscript class maintains the information of a manuscript </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class  MANUSCRIPT_EXPORT Manuscript {
protected:
	string     _title;	
	string     _author;
	string     _copyist;
//	Date       _authoring_date;
	string     _region;
	string     _language;
	string     _font_type;
//	PaperType  _paper;
	vector<Page*> _pages; 
public:
	Manuscript(void);
	~Manuscript(void);

	vector<Page*>& getPages()       { return _pages; }
	Page*          getPage(int idx) { return _pages[idx] ;}
};

#endif 
