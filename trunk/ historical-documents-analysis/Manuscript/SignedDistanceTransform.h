#ifndef _SIGNED_DISTANCE_TRANSFORMATION_ 
#define _SIGNED_DISTANCE_TRANSFORMATION_

#include <vector>

#include "imagetransformation.h"
#include "ConnectedComponent.h"

class MANUSCRIPT_EXPORT SignedDistanceTransform : public ImageTransformation {
	vector<ConnectedComponent*>* _components ;
protected:
	void updateSignedDistaceMap(Mat map, int row, int col, int step, int delta);


public:
	SignedDistanceTransform(void) {;}
	~SignedDistanceTransform(void){;}

	void setComponents(vector<ConnectedComponent*>* components){
		_components = components ;
	}
	Mat transform();
};

#endif 