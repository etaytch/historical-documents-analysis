#ifndef _Page_H 
#define _Page_H 

#include "di.h"
#include "SubPage.h"
#include "manuscript_global.h"
#include "string.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Page class maintains the properties of one page in a manuscript </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class MANUSCRIPT_EXPORT Page: public SubPage {
protected:
	int                 _index ;
	vector<SubPage*>    _subpages;
	vector<Page*>	    _pages;
	string			    _name;
	bool				_active;
	bool                _cached;
public:
	Page(void) {
		_cached = false	;
		_active = false ;
	}
	virtual ~Page(void);

	void   setIndex(int index) { _index = index;}
	int    getIndex()          { return _index;}

	string getName()           { return _name;}
	void setName(string name)  { _name = name;}

	void             setSubImages(vector<SubPage*> subpages)   { _subpages = subpages;}
	vector<SubPage*> getSubImages()                            { return _subpages;}
	
	void addSubPage(SubPage* b)                                { _subpages.push_back(b);}
	void removeSubPage(int index);

	void addPage(Page* p)			                { _pages.push_back(p);} 
	void setActiveState(int active)		            { _active = active;} 
	int  isActive()		                            { return _active;} 
	vector<Page*>& getPages()                       { return _pages; }
	Page*          getPage(int idx)                 { return _pages[idx] ;}
	void loadMat() ;
	
};

#endif 
