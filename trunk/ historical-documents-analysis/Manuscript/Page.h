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
	
	void setIndex(int index) {_index = index;}
	int getIndex(){return _index;}
	void setBlocks(vector<Block> blocks) {_blocks = blocks;}
	vector<Block> getBlocks(){return _blocks;}
	void addBlock(Block b){_blocks.push_back(b);}
	void removeBlock(int index);


	~Page(void);
};

#endif 
