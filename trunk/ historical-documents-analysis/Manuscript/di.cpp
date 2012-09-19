#include "di.h"
#include "Contour.h" 
#include "Binarizer.h"
#include "ComponentExtractor.h"
#include "TextLineExtractor.h"
#include "ImageTransformation.h"
#include "ImageOperation.h"
#include "ImageCombiner.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Return a gray scale image of the RGB one. </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
///
/// <returns>	null if it fails, else. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

cv::Mat di::rgb2gray(Mat mat){
	Mat gray;
	gray.create(mat.size(), CV_8U);
	cvtColor(mat, gray,CV_BGR2GRAY);
	return gray;
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

cv::MatND di::getHistogram(const Mat* mat, int channel[], const int bin[], const float* range[]) {
	MatND hist;
	cv::calcHist(mat, 1, channel, cv::Mat(), hist, 1, bin, range);
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

Mat di::binarize(Binarizer& binarizer, Mat mat){
	binarizer.setImage(mat);
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

void di::extractComponents(ComponentExtractor& extractor, Mat mat, vector<ConnectedComponent*>& components){
	extractor.setImage(mat);
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

void di::extractTextLine(TextLineExtractor& extractor, Mat mat, vector<TextLine*>& textlines){
	extractor.setImage(mat) ;
	extractor.extract(textlines);
}

void di::print(Mat mat){
	for ( int col = 0 ; col < mat.cols ; col++ ){
		for ( int row = 1 ; row < mat.rows ; row++ )
			printf("%3d",mat.at<char>(row, col));
		printf("\n");
	}

}

Mat di::transform(ImageTransformation& transformation, Mat mat){
	transformation.set(mat);
	return transformation.transform();
}


Mat di::combine(ImageCombiner& combiner, Mat a, Mat b){
	Mat result ;
	combiner.combine(a,b, result);
	return result ;
}

MatND di::project(ImageOperation& operation, Mat mat){
	operation.set(mat);
	return operation.project();
}
