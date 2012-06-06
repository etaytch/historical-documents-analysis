#ifndef _DImage_H 
#define _DImage_H 

#include <vector>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include "manuscript_global.h"

class Binarizer ;
class ComponentExtractor ;
class TextLineExtractor ;
class TextLine ;
class ConnectedComponent ;
class ImageTransformation ;
class ImageOperation ;
class ImageCombiner ;

using namespace cv ;

class MANUSCRIPT_EXPORT DImage {
protected:
	Mat _mat ;

private:
	void updateSignedDistaceMap(Mat map, int row, int col, int step, int delta);

public:
	DImage(void);
	DImage(Mat& mat);
	~DImage(void);

	Mat&       getMat()         { return _mat ; }
	void       setMat(Mat& mat) { _mat = mat  ; } 

	DImage*    rgb2gray();

	cv::MatND  getHistogram(int channel[], int bin[], const float* range[]);
	DImage*    binarize(Binarizer& binarizer);
	void       extractComponents(ComponentExtractor& extractor, vector<ConnectedComponent*>& components); 
	void       extractTextLine(TextLineExtractor& extractor, vector<TextLine*>& textlines); 

	// A transformation operate on an image (Mat) and return an Image 
	Mat        transform(ImageTransformation& transformation, Mat mat);
	Mat        combine(ImageCombiner& combiner, Mat a, Mat b);
	MatND      project(ImageOperation& op, Mat mat);

	void       print(Mat mat);
};

#endif 

