#include "GlobalBinarizer.h"


GlobalBinarizer::GlobalBinarizer(void){
}

GlobalBinarizer::GlobalBinarizer(float thershold){
	_thershold = thershold ;
}

GlobalBinarizer::~GlobalBinarizer(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Binarize the image using an input threshold _thershold. </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
///
/// <returns>	null if it fails, else. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

Mat GlobalBinarizer::binarize(){
	Mat bin_image;
	bin_image.create(_image.rows, _image.cols, CV_8U);
	cv::threshold(_image, bin_image, _thershold,255,cv::THRESH_BINARY);
	return bin_image ;
}