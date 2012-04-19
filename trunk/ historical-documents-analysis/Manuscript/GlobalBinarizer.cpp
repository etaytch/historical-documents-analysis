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

DImage* GlobalBinarizer::binarize(){
	DImage* bin_image = new DImage(_image.getMat());
	cv::threshold(_image.getMat(), bin_image->getMat(), _thershold,255,cv::THRESH_BINARY);
	return bin_image ;
}