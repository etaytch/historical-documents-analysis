#include "SignedDistanceTransform.h"

void SignedDistanceTransform::updateSignedDistaceMap(Mat map, int row, int col, int step, int delta){
	if ( map.at<char>(row, col) > 0 ){
		if ( map.at<char>(row-step, col) > map.at<char>(row, col-step) ){
			if ( map.at<char>(row, col-step) < map.at<char>(row, col)) {
				map.at<char>(row, col) = map.at<char>(row, col-step) + delta ;
				if ( map.at<char>(row, col) < map.at<char>(row-step, col))
					map.at<char>(row-step, col) = map.at<char>(row, col) + delta ;
			}
		}
		else {
			if ( map.at<char>(row-step, col) < map.at<char>(row, col)) {
				map.at<char>(row, col) = map.at<char>(row-step, col) + delta ;
				if ( map.at<char>(row, col) < map.at<char>(row, col-step))
					map.at<char>(row, col-step) = map.at<char>(row, col) + delta ;
			}
		}
	}
	if ( map.at<char>(row, col) < 0 ){
	    if ( map.at<char>(row-step, col) > map.at<char>(row, col-step) ){
			if ( map.at<char>(row-step, col) > map.at<char>(row, col)) {
				map.at<char>(row, col) = map.at<char>(row-step, col) - delta ;
				if ( map.at<char>(row, col) > map.at<char>(row, col-step))
					map.at<char>(row, col-step) = map.at<char>(row, col) - delta ;
			}
		}
		else {
			if ( map.at<char>(row, col-step) > map.at<char>(row, col)) {
				map.at<char>(row, col) = map.at<char>(row, col-step) - delta ;
				if ( map.at<char>(row, col) > map.at<char>(row-step, col))
					map.at<char>(row-step, col) = map.at<char>(row, col) - delta ;
			}
		}
	}
}

Mat SignedDistanceTransform::transform(){
	int col, row ;
	Mat map(_mat.size(), CV_8S, Scalar(127));
	vector<ConnectedComponent*>::iterator iter = _components->begin() ;
	while ( iter != _components->end() ){
		(*iter)->getContour().drawOnImage(map, 0);
		(*iter)->fillComponentOnMat(map, 0, -127);
		iter++ ;
	}
	// Forward traversal 
	for ( col = 1 ; col < map.cols ; col++ )
		for ( row = 1 ; row < map.rows ; row++ )
			updateSignedDistaceMap(map, row, col, 1, 1);
	for ( col = map.cols-2 ; col >= 0  ; col-- )
		for ( row = map.rows-2 ; row >= 0 ; row-- )
			updateSignedDistaceMap(map, row, col, -1, 1);
	return map ;
}

