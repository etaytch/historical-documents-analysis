#ifndef _COMPONENTFILTER_H 
#define _COMPONENTFILTER_H 
#include "ConnectedComponent.h" 

class ComponentFilter {
protected:
	int _width ;
	int _height ;
	float _area ;
public:
	ComponentFilter(void);
	~ComponentFilter(void);

	void setWidth(int w)   { _width  = w ; }
	void setHeight(int h)  { _height = h ; }
	void setArea(float a)  { _area = a ; }
	virtual bool filter(ConnectedComponent& );
};

#endif 