
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "di.h" 
#include "ConnectedComponent.h"
#include "OtsulBinarizer.h" 
#include "RadialBinarizer.h"
#include "BinaryComponentExtractor.h"



void display(std::string wname, Mat image){
	cv::namedWindow(wname, CV_WINDOW_NORMAL|CV_GUI_EXPANDED );
	cv::imshow(wname, image);
}

void drawConnectedComponents(Mat img, vector<ConnectedComponent*>& components){
	vector<ConnectedComponent*>::iterator iter ;
	for ( iter = components.begin(); iter != components.end(); iter++ ){
		printf ("Area : %f \n", (*iter)->getContour().getArea());
		//Scalar color( rand()&255, rand()&255, rand()&255 );
		if ( (*iter)->getContour().getArea() > 100 ){
			Scalar color( 255, 0, 0 );
			(*iter)->draw(img, color, true, 1, 8);
		}
	}
}

int main() {
	Mat img ;
	vector<ConnectedComponent*> components ;
	Mat img_in = cv::imread("arabic.jpg") ;
	resize(img_in, img, img_in.size()*2,  2.0, 2.0);
	display("resized", img_in);
	img = imread("pentagon.jpg");
	Mat gray = di::rgb2gray(img);
	OtsulBinarizer binarizer ;
//	RadialBinarizer binarizer ;
	Mat binary = di::binarize(binarizer, gray);
	BinaryComponentExtractor extractor ;
	display("Original", img);
	display("Gray", gray);
	display("Binary", binary);
	di::extractComponents(extractor, binary, components); 
	drawConnectedComponents(img, components);
	display("Components", img);
	cv::waitKey();
	return 1;
}