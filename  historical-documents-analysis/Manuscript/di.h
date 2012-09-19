#ifndef _DI_H 
#define _DI_H 

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

namespace di {
	__declspec(dllexport) void updateSignedDistaceMap(Mat map, int row, int col, int step, int delta);

	__declspec(dllexport) Mat        rgb2gray(Mat mat);
	__declspec(dllexport) MatND  getHistogram(const Mat* mat, int channel[], const int bin[], const float* range[]);
	__declspec(dllexport) Mat        binarize(Binarizer& binarizer, Mat m);
	__declspec(dllexport) void       extractComponents(ComponentExtractor& extractor, Mat mat, vector<ConnectedComponent*>& components); 
	__declspec(dllexport) void       extractTextLine(TextLineExtractor& extractor, Mat mat, vector<TextLine*>& textlines); 

	// A transformation operate on an image (Mat) and return an Image 
	__declspec(dllexport) Mat        transform(ImageTransformation& transformation, Mat mat);
	__declspec(dllexport) Mat        combine(ImageCombiner& combiner, Mat a, Mat b);
	__declspec(dllexport) MatND      project(ImageOperation& op, Mat mat);

	__declspec(dllexport) void       print(Mat mat);
};

#endif 

