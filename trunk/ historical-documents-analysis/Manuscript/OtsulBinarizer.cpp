#include "OtsulBinarizer.h"


OtsulBinarizer::OtsulBinarizer(void)
{
}


OtsulBinarizer::~OtsulBinarizer(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	binarize an image using the Otsu algorithm </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
///
/// <returns>	null if it fails, else. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

DImage* OtsulBinarizer::binarize(){
	DImage* bin_image = new DImage(_image.getMat());
	cv::threshold(_image.getMat(), bin_image->getMat(),0 ,255,cv::THRESH_BINARY|cv::THRESH_OTSU);
	return bin_image ;
}