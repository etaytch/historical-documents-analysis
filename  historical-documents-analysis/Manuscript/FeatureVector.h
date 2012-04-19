#ifndef _FEATURE_H 
#define _FEATURE_H 

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary> FeatureVector class is template class that handle vector of features </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ConnectedComponent.h"

class FeatureVector {

public:

	virtual void extract(ConnectedComponent& com) = 0;
    virtual float distance(FeatureVector* f) = 0 ;
};

#endif 