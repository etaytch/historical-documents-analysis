#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "DImage.h"
#include "ConnectedComponent.h"

#include "OtsulBinarizer.h" 
#include "RadialBinarizer.h"
#include "BinaryComponentExtractor.h"
#include "SignedDistanceTransform.h"
#include "ShiftDistance.h" 

void display(std::string wname, DImage& image){
	cv::namedWindow(wname);
	cv::imshow(wname, image.getMat());
}

void display(std::string wname, Mat image){
	cv::namedWindow(wname, CV_WINDOW_NORMAL|CV_GUI_EXPANDED );
	cv::imshow(wname, image);
}

void drawConnectedComponents(DImage img, vector<ConnectedComponent*>& components){
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

	ShiftDistance dtw ;
	DImage image ;
	Mat img ;
	vector<ConnectedComponent*> components ;
	//Mat img_in = cv::imread("arabic.jpg") ;
	//resize(img_in, img, img_in.size()*2,  2.0, 2.0);
	//image.setMat(img);
	image.setMat(imread("arabic.jpg"));
	DImage* gray = image.rgb2gray();
	OtsulBinarizer binarizer ;
	//RadialBinarizer binarizer ;
	DImage* binary = gray->binarize(binarizer);
	BinaryComponentExtractor extractor ;
	display("Original", image);
	display("Gray", *gray);
	display("Binary", *binary);
	binary->extractComponents(extractor, components);
	drawConnectedComponents(image, components);
	display("Components", image) ;

	SignedDistanceTransform transform ;
	transform.setComponents(&components);
	Mat map = binary->transform(transform, binary->getMat());
	display("Distance", map);
	cv::waitKey();
	return 1;
}
