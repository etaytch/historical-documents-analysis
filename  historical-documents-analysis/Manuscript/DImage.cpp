#include "DImage.h"
#include "Contour.h" 
#include "Binarizer.h"
#include "ComponentExtractor.h"
#include "TextLineExtractor.h"
#include "ImageTransformation.h"
#include "ImageOperation.h"

DImage::DImage(void){
}

DImage::DImage(Mat& mat){
	_mat = mat.clone();
}


DImage::~DImage(void){
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Return a gray scale image of the RGB one. </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
///
/// <returns>	null if it fails, else. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

DImage* DImage::rgb2gray(){
	DImage *gray_image = new DImage(_mat);
	cvtColor(_mat, gray_image->getMat(),CV_BGR2GRAY);
	return gray_image ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets a histogram of the image, its assumes the image is gray scale </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
///
/// <param name="channel">	The channel. </param>
/// <param name="bin">	  	The bin. </param>
/// <param name="range">  	The range. </param>
///
/// <returns>	The histogram. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

cv::MatND DImage::getHistogram(int channel[], int bin[], const float* range[]) {
	MatND hist;
	calcHist(&_mat, 1, channel, cv::Mat(), hist, 1, bin, range );
	return hist;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Apply the binarizer to the image and returns a bindary one. </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
///
/// <param name="binarizer">	[in] The binarizer. </param>
///
/// <returns>	null if it fails, else. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

DImage* DImage::binarize(Binarizer& binarizer){
	binarizer.setImage(*this);
	return binarizer.binarize() ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Extracts the components from a bindary image using the extractor algorithm </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
///
/// <param name="extractor"> 	[in,out] The extractor. </param>
/// <param name="components">	[in,out] [in,out] If non-null, the components. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void DImage::extractComponents(ComponentExtractor& extractor, vector<ConnectedComponent*>& components){
	extractor.setImage(*this);
	extractor.extract(components);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Extracts the text line in a document image </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
///
/// <param name="extractor">	[in] The extractor. </param>
/// <param name="textlines">	[out] The extracted textlines in a vector </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void DImage::extractTextLine(TextLineExtractor& extractor, vector<TextLine*>& textlines){
	extractor.setImage(*this) ;
	extractor.extract(textlines);
}

void DImage::print(Mat mat){
	for ( int col = 0 ; col < mat.cols ; col++ ){
		for ( int row = 1 ; row < mat.rows ; row++ )
			printf("%3d",mat.at<char>(row, col));
		printf("\n");
	}

}

Mat DImage::transform(ImageTransformation& transformation, Mat mat){
	transformation.set(mat);
	return transformation.transform();
}

MatND DImage::project(ImageOperation& operation, Mat mat){
	operation.set(mat);
	return operation.project();
}