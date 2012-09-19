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

Mat OtsulBinarizer::binarize(){
	Mat bin_image;
	bin_image.create(_image.rows, _image.cols, CV_8U);
	cv::threshold(_image, bin_image,0 ,255,cv::THRESH_BINARY|cv::THRESH_OTSU);
	return bin_image ;
}