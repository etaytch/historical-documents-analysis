#ifndef _LINESEGMENT_H 
#define _LINESEGMENT_H 

#include <opencv\cv.h>
#include <opencv\cxcore.h>

template<class T> class LineSegment{
	cv::Point_<T> _start ;
	cv::Point_<T> _end   ;
public:

	LineSegment(void){}
	LineSegment(cv::Point_<T>& start, cv::Point_<T>& end)  { _start = start ; _end = _end ;}
	~LineSegment(void){}

	void setStart(cv::Point_<T>& start)                {_start = start ; }
	void setEnd(cv::Point_<T>& end)                    {_end = end ; }

	cv::Point_<T>& getStart() { return _start ; }
	cv::Point_<T>& getEnd()   { return _end ; }
};

#endif 