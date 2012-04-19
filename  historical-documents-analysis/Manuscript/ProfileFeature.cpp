#include "ProfileFeature.h"

float ProfileFeature::distance(FeatureVector* f){
	ProfileFeature* pf = (ProfileFeature*)f ;
	vector<byte>&  pvector = pf->getVector() ;
	float sum = 0 ;
	for ( int i = 0 ; i < (int)pvector.size() ; i++ ){
		sum += abs(pvector[i] - _fvector[i]) ;
	}
	return sum  ;
}


void ProfileFeature::extract(ConnectedComponent& com) {
	cv::Rect rect = com.getBoundRect() ;
	cv::Mat mat = com.getImage().getMat() ;
	for ( int col = rect.x ; col < rect.width ; col++ ){
		byte sum = 0 ;
		for ( int row = rect.y ; row < rect.height ; row++ ){
			sum += mat.at<uchar>(row, col) ;
		}
		this->addItem(sum);
	}
}
