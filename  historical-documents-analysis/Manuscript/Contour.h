#ifndef _Contour_H 
#define _Contour_H 

#include <vector>
#include <opencv\cv.h> 
#include <opencv2\core\core.hpp>

using namespace std ;
using namespace cv ;

typedef pair<int, float> VertexWeight;

class Contour {
protected:
	vector<cv::Point> _points ;
	cv::Rect          _brect  ;
	vector<VertexWeight>  _heap ;
public:
	Contour(void)  {;}
	~Contour(void) {;}

	vector<cv::Point>& getPoints(){
		return _points ;
	}

	Rect&  getBoundRect() {

		return _brect ;
	}

	void setPoints(vector<cv::Point> p){
		_points = p ;
	}

	void  setBoundRect();
	
	float getImportance(int i);
	int   getLeastImportant();
	void  removeVertex(int i);
	int   removeLeastImportant() ;
	void  drawOnImage(Mat mat, char filler);
	float getArea();
};

#endif 