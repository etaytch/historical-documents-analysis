#ifndef _GSCFEATURES_H_ 
#define _GSCFEATURES_H_

#include "FeatureVector.h"
#include "ConnectedComponent.h"

typedef struct {


} GSCStruct ;

class GSCFeatures : public FeatureVector {
	vector<int> _fvector ;
	int _gradientThresh;
	int _rulesThresh;
	int _densityThresh;
	float _verticalStrokeThresh;
	float _horizontalStrokeThresh;
	int _concavityThresh;

public:
	GSCFeatures() ;      
	~GSCFeatures(void){;}

	vector<int>& getVector() { return _fvector ; }
	void  addItem(int item)  { _fvector.push_back(item); }


/*
Setter and Getter for the gradient direction threshold.
(the actual threshold will be : (the number of pixels in the region/tgradient) we decide how many votes are required in the region, e.g : more than 1/2 of the pixels are required to vote)
*/
	int getGradientThresh(){return _gradientThresh;}
	void setGradientThresh(int thresh){_gradientThresh=thresh;}
/*
Setter and Getter for the mini structure rule threshold.
(the actual threshold will be : (the number of pixels in the region/trules) )
*/
		int getRulesThresh(){return _rulesThresh;}
	void  setRulesThresh(int thresh){_rulesThresh=thresh;}
/*
Setter and Getter for the region density threshold.
(the actual threshold will be : (the number of pixels in the region/tdensity) which means that we decide how much would be considered a "dense" region, e.g a region with more than a half of the pixels as foreground)
*/
		int getDensityThresh(){return _densityThresh;}
	void setDensityThresh(int thresh){_densityThresh=thresh;}
/*
Setter and Getter for the vertical large stroke threshold.

Note : the threshold is a floating point number in the region [0..1]
*/
		float getVerticalThresh(){return _verticalStrokeThresh;}
	void setVerticalThresh(float thresh){_verticalStrokeThresh=thresh;}
/*
Setter and Getter for the horizontal large stroke threshold.

Note : the threshold is a floating point number in the region [0..1]
*/
		int getHorizontalThresh(){return _horizontalStrokeThresh;}
	void setHorizontalThresh(float thresh){_horizontalStrokeThresh=thresh;}
/*
Setter and Getter for the concavity direction threshold.

(the actual threshold will be : (the number of pixels in the region/tconcavity) )
*/
		int getConcavityThresh(){return _concavityThresh;}
	void setConcavityThresh(int thresh){_concavityThresh=thresh;}

	float distance(FeatureVector* p)  ;
//Used for extracting the gradient direction features and mini structure features, img is a region in the original image
	int extractGradientFeatures(IplImage *subimg);
//Used for extracting the density feature, img is a region in the original image
	int extractDensity(IplImage* subimg);
//Used for extracting the large strokes (vertical and horizontal) features, img is a region in the original image
	int extractLargeStrokes(IplImage* subimg);
//Used for extracting the concavity features from the image, img is a region in the original image.
	int extractConcavityDirection(IplImage* subimg);
//Used to combine all the features to one binary feature.
	void  extract(ConnectedComponent& com, FeatureVector* p)  ;
};

#endif 