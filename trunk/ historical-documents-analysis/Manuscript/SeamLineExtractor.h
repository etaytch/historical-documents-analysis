#ifndef _SEAMLINEEXTRACTOR_H 
#define _SEAMLINEEXTRACTOR_H 

#include <opencv\cv.h>
#include <opencv\highgui.h>

#include "seprateLine.h"
#include "TextLine.h"
#include "TextLineExtractor.h"

using namespace cv;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	SeamLineExtractor extends TextLineExtractor , extracts lines of a text image. </summary>
///
/// <remarks>	Mohamad Khateeb & Nabeel Saabna 3/22/12. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class SeamLineExtractor : public TextLineExtractor{
private:
	   Mat _image;
	   Mat _distanceMap;
	   Mat _seamMap;
	   int _lines;
	   double _seedFilterThreshold;
protected:

	TextLine* removeLineAndAddPoints(Mat seamMap, int* seprateUpSeem, int* seprateDownSeem,float setMax);
	void buildSeamMap();
	void buildSeamMapCol(Mat seam,int col,int pos);
	void findMedialSeam(int* medial,Mat temoSeamMap);
	void sepratingSeeds(int row,int col, int* seprate,int pos);
	void sepratingSeedsBorder(int row,int col,int* seprate,int pos, int dir);
	int  getLongestSeed(vector<seprateLine*>& seperate_seeds );
	seprateLine* findSepratingSeed(int* seperateSeedCols, int* medialCols);

	void  mergeContinuosSeeds(int* seprateSeedCols, vector<seprateLine*>& seprateSeeds);
	void  filterShortSeeds(vector<seprateLine*>& seprateSeeds);
	void  filterLightSeeds(vector<seprateLine*>& seprateSeeds);
	float getRowMax(Mat m, int row) ;

public:
	SeamLineExtractor(void) {;}
	~SeamLineExtractor(void) {;}
	
	void extract(vector<TextLine*>& textLine);
	void setDistance(Mat& dist){_distanceMap = dist.clone();};
	void setImage(Mat& image){_image = image.clone();};
	void setLinesNumber(int linesNumber){_lines = linesNumber;};
	void setThreshold(double threshold) {_seedFilterThreshold = threshold;};
	
};

#endif