#ifndef _COMPONENTCOMPARATOR_H_
#define _COMPONENTCOMPARATOR_H_

#include "ConnectedComponent.h"

class ComponentComparator{
public:
	ComponentComparator(void);
	~ComponentComparator(void);

	virtual float distance(ConnectedComponent&, ConnectedComponent&) = 0 ;
};

#endif 