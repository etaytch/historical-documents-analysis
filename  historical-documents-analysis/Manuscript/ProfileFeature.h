#ifndef _PROFILEFEATURE_H_ 
#define _PROFILEFEATURE_H_

#include "FeatureVector.h"
#include "ConnectedComponent.h"

class ProfileFeature : public FeatureVector {
	vector<byte> _fvector ;
public:
	ProfileFeature() ;      
	~ProfileFeature(void){;}

	vector<byte>& getVector() { return _fvector ; }
	void  addItem(byte item)  { _fvector.push_back(item); }

	float distance(FeatureVector* p)  ;
	void  extract(ConnectedComponent& com)  ;
};

#endif 