#ifndef _Page_H 
#define _Page_H 

#include "DImage.h"
#include "Block.h"
#include "manuscript_global.h"
#include "string.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Page class maintains the properties of one page in a manuscript </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class MANUSCRIPT_EXPORT Page : public DImage {
protected:
	int                _index ;
	vector<Block*>     _blocks;
	vector<Page*>	   _pages;
	string			   _name;

public:
	Page(void);
	void setIndex(int index) {_index = index;}
	int  getIndex(){return _index;}
	string getName(){return _name;}
	void setBlocks(vector<Block*> blocks) {_blocks = blocks;}
	vector<Block*> getBlocks() {return _blocks;}
	void setName(string name)  {_name = name;}
	void addBlock(Block* b)    {_blocks.push_back(b);}
	void removeBlock(int index);
	void addPage(Page* p)			{_pages.push_back(p);} 
	vector<Page*>& getPages()       { return _pages; }
	Page*          getPage(int idx) { return _pages[idx] ;}
	void loadMat();
	virtual ~Page(void);
};

#endif 
