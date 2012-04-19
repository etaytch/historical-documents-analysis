#include "Contour.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Sets the bounding rectangle of the contour, using its points. </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Contour::setBoundRect(){
	vector<Point>::iterator iter = _points.begin() ;
	Point min = (*iter) ;
	Point max = (*iter) ;
	while ( iter != _points.end() ){
		if ( (*iter).x < min.x )
			min.x = (*iter).x ;

		if ( (*iter).x  > max.x )
			max.x = (*iter).x ;

		if ( (*iter).y < min.y )
			min.y = (*iter).y ;

		if ( (*iter).y  > max.y )
			max.y = (*iter).y ;
		iter++ ;
	}
	_brect.x = min.x ;
	_brect.y = min.y ;
	_brect.height = max.y - min.y ;
	_brect.width  = max.x - min.x ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets the area of a contour, the area is computed each time it is called, i.e., it is
/// 			not stored  </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
///
/// <returns>	The area. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

float Contour::getArea(){
	Point p ;
	p.x = _brect.x + _brect.width/2 ;
	p.y = _brect.y + _brect.height/2 ;
	Point u, v ;
	float area = 0 ;
	for ( int i = 0 ; i < _points.size() - 1; i++ ){
		u = _points[i] - p  ;
		v = _points[i+1] - p ;
		area += u.x * v.y - u.y * v.x ;
	}
	u = _points[_points.size()-1] - p  ;
	v = _points[0] - p ;
	area += u.x * v.y - u.y * v.x ;

	return area ;
}

void Contour::drawOnImage(Mat mat, char value){
	vector<Point>::iterator iter = _points.begin() ;
	while ( iter != _points.end() ){
		mat.at<char>(*iter) = value ;
		iter++ ;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets an importance, which is computed as the size of the thriangle defined by the 
/// 			vertex and its two adjacent neighbors </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
///
/// <param name="i">	Zero-based index of the. </param>
///
/// <returns>	The importance. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

float Contour::getImportance(int i){
	cv::Point vp = _points[i-1] - _points[i]  ;
	cv::Point vn = _points[i+1] - _points[i] ;

	
	return (float)abs(vp.x * vn.y - vp.y * vn.x );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Return the vertex with the least importance value </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
///
/// <returns>	The least important. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

int Contour::getLeastImportant(){
	int   min_idx = 0 ;
	float min_val = getImportance(0) ;
	for (unsigned int i = 1 ; i < _points.size() ; i++ ){
		float val = getImportance(i) ;
		if ( val < min_val ){
			min_idx = i ;
			min_val = val ;
		}
	}
	return min_idx ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Removes the vertex i from the contour (boundary). </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
///
/// <param name="i">	Zero-based index of the. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Contour::removeVertex(int i){
	_points.erase(_points.begin() + i);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Removes the vertex with least importance value </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
///
/// <returns>	. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

int Contour::removeLeastImportant(){
	int vert_idx = getLeastImportant();
	_points.erase(_points.begin() + vert_idx);
	return vert_idx ;
}

