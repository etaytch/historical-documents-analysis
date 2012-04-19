#include "RadialBinarizer.h"

RadialBinarizer::RadialBinarizer(void){
}

RadialBinarizer::~RadialBinarizer(void){
}

bool RadialBinarizer::getRadialLevel(int row, int col, int radius){
	int   threshold ;
	uchar hist[255] ;
	Mat mat = _image.getMat() ;
	
	memset(hist,0,255);
	for ( int i = row - radius; i <=  row + radius; i++ )
		for ( int j = col - radius; j <= col + radius ; j++ )
			hist[(int)mat.at<uchar>(i, j)]++ ;

	int area = (2*radius+1)*(2*radius+1) ;
	int sum = 0 ;
	for ( threshold = 0 ; threshold < 255 && sum < area/2 ; threshold++ ){
		sum += (int)hist[threshold] ;
	}
	return (int)mat.at<uchar>(row, col) >= threshold ;

	
	//_image.getMat().adjustROI(row-radius, row+radius, col - radius, col+radius);
	//result.create(2*row+1, 2*col+1, CV_8U);
	//cv::threshold(_image.getMat(), result,0 ,255,cv::THRESH_BINARY|cv::THRESH_OTSU);
	//printf("%d %d %d %d\n", row, col, radius, result.at<uchar>(row, col));
	//return (result.at<uchar>(row, col) == 255) ;
	//return true ;
}

void RadialBinarizer::computeRadialMap(){
	_radial_map.create(_image.getMat().size(), CV_8U);
	for (int row = 10 ; row < _radial_map.rows -10; row++ ){
		for ( int col = 10 ; col < _radial_map.cols -10; col++)
			//for ( int chan = 0; chan < 3 ; chan++ )
			{
				int chan = 0 ;
				unsigned char bit  = 1 ;
				unsigned char code = 0 ;
				for ( int radius = 1 ; radius < 8; radius++ ){
					if ( getRadialLevel(row, col, 8*chan + radius ))
						code |= bit ;
					bit = bit << 1 ;
					//printf("%X ", code );
				}
				//_radial_map.at<uchar>(row, col) = code ;
				_radial_map.at<uchar>(row, col) = code ;
				//printf("\n");
			}
	}
}

int RadialBinarizer::getOneCount(uchar b){
	int count = 0  ;
	for ( int i = 0 ; i < 8 ;i++ ){
		if ( b & 0x01) 
			count ++ ;
		b = b >> 1 ; 
	}
	return count ;
}


DImage* RadialBinarizer::binarize(){
	Mat bin_img ;
	computeRadialMap();
	bin_img.create(_image.getMat().size(), CV_8U);
	for (int row = 10 ; row < _radial_map.rows -10; row++ )
		for ( int col = 10 ; col < _radial_map.cols -10; col++){
			int count = getOneCount(_radial_map.at<uchar>(row, col));
			if ( count > 4 )
				bin_img.at<uchar>(row, col) = 255 ;
			else
				bin_img.at<uchar>(row, col) = 0 ;
		}
	return new DImage(bin_img) ;
}