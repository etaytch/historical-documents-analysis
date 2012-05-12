#include "GSCFeatures.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <opencv\cv.h>
#include <opencv\highgui.h>

GSCFeatures::GSCFeatures(){
	_gradientThresh=0;
	_rulesThresh=0;
	_densityThresh=0;
	_verticalStrokeThresh=0;
	_horizontalStrokeThresh=0;
	_concavityThresh=0;
}

//Is not described in the PDF
float GSCFeatures::distance(FeatureVector* f){

	return 0 ;
}


//Used for extracting the gradient direction features and mini structure gradient features, img is a region in the original image
//Returns an int where bits 31..20 each specify if gradient direction i (in quantization of [0..2*pi] to 12 equal segments) is strongly represented in the region
//and bits 19..8 each specify if the relevant rule applies in the region (check the PDF for the rules) (111111111111 means the region is empty)
	
int GSCFeatures::extractGradientFeatures(IplImage *subimg){
		float PI = 3.141592;
		CvMat *gradir=0;
		int regionWidth,regionHeight,regionStep,row,col,l,result,finalGradientThresh,finalRulesThresh,trules1;
		IplImage* dx=0;
		IplImage* dy=0;
		IplImage* dxx=0;
		IplImage* dyy=0;
		IplImage *dxtemp=0;
		IplImage *dytemp=0;
		uchar *subdata;
		char *dxdata;
		char *dydata;
		int gradcounter[12];
		int rulecounter[12];
		int n0,n1,n2,n3,n4,n5,n6,n7;
		char dxd,dyd;
		regionWidth=subimg->width;
		regionHeight=subimg->height;
		regionStep=subimg->widthStep;
		//Initializing counters
		for(l=0;l<12;l++){
			gradcounter[l]=0;
			rulecounter[l]=0;
		}
		result=0;
		 //initializting the gradient direction matrix
		gradir=cvCreateMat(regionHeight,regionWidth,CV_32FC1);
		//assigning a pointer to the data stored in the image
		subdata=(uchar *)subimg->imageData;
			
	//computing the x and y derivatives of the (i,j) region of the image
		dxtemp=cvCreateImage(cvSize(regionWidth,regionHeight),IPL_DEPTH_16S,subimg->nChannels);
		dytemp=cvCreateImage(cvSize(regionWidth,regionHeight),IPL_DEPTH_16S,subimg->nChannels);
		dx=cvCreateImage(cvSize(regionWidth,regionHeight),IPL_DEPTH_8S,subimg->nChannels);
		dy=cvCreateImage(cvSize(regionWidth,regionHeight),IPL_DEPTH_8S,subimg->nChannels);
		cvSobel(subimg,dxtemp,1,0,3);
		cvSobel(subimg,dytemp,0,1,3);
		dxx=cvCreateImage(cvSize(regionWidth,regionHeight),IPL_DEPTH_8U,subimg->nChannels);
		dyy=cvCreateImage(cvSize(regionWidth,regionHeight),IPL_DEPTH_8U,subimg->nChannels);
		cvConvertScaleAbs(dytemp,dyy,1,0);
		cvConvertScaleAbs(dxtemp,dxx,1,0);
		cvConvertScale(dytemp,dy,1,0);
		cvConvertScale(dxtemp,dx,1,0);
		dxdata=(char *)dx->imageData;
		dydata=(char *)dy->imageData;
	//the x and y derivatives , in 16 bit signed format are in dx and dy, data through dxdata and dydata
	//computing the gradient direction in each pixel, using atan(dy/dx) as the general formula, and checking for special cases
		for(row=0;row<regionHeight;row++){
			for(col=0;col<regionWidth;col++){
				//setting the data in dxd and dyd (dereferencing through dxdata and dydata)
				dxd=dxdata[row*regionStep+col];
				dyd=dydata[row*regionStep+col];

				if(dxd==0&&dyd==0){
					cvmSet(gradir,row,col,-1);}
				else if(dxd==0||dyd==0){
					if(dxd==0){
						cvmSet(gradir,row,col,PI+atan2(((double) dyd),((double) dxd)));}
					
					else{
						cvmSet(gradir,row,col,atan2(((double) dyd),((double) dxd)));

					}
				}
				else{
					if(PI/2+atan2(((double) dyd),((double) dxd))<0)
					cvmSet(gradir,row,col,2*PI-(PI/2+atan2(((double) dyd),((double) dxd))));
					else				
					cvmSet(gradir,row,col,PI/2+atan2(((double) dyd),((double) dxd)));
				}
				//done computing the gradient direction, quantization is needed
				if(cvmGet(gradir,row,col)>=0&&cvmGet(gradir,row,col)<PI/6){
					cvmSet(gradir,row,col,1);
				}
				else if(cvmGet(gradir,row,col)>=PI/6&&cvmGet(gradir,row,col)<2*PI/6){
					cvmSet(gradir,row,col,2);	
				}
					
				else if(cvmGet(gradir,row,col)>=2*PI/6&&cvmGet(gradir,row,col)<3*PI/6){
					cvmSet(gradir,row,col,3);	
					
				}
				else if(cvmGet(gradir,row,col)>=3*PI/6&&cvmGet(gradir,row,col)<4*PI/6){
					cvmSet(gradir,row,col,4);
					
				}
				else if(cvmGet(gradir,row,col)>=4*PI/6&&cvmGet(gradir,row,col)<5*PI/6){
					cvmSet(gradir,row,col,5);	
				}
				else if(cvmGet(gradir,row,col)>=5*PI/6&&cvmGet(gradir,row,col)<6*PI/6){
					cvmSet(gradir,row,col,6);	
				}
				else if(cvmGet(gradir,row,col)>=6*PI/6&&cvmGet(gradir,row,col)<7*PI/6){
					cvmSet(gradir,row,col,7);	
				}
				else if(cvmGet(gradir,row,col)>=7*PI/6&&cvmGet(gradir,row,col)<8*PI/6){
					cvmSet(gradir,row,col,8);	
				}
				else if(cvmGet(gradir,row,col)>=8*PI/6&&cvmGet(gradir,row,col)<9*PI/6){
					cvmSet(gradir,row,col,9);	
				}
				else if(cvmGet(gradir,row,col)>=9*PI/6&&cvmGet(gradir,row,col)<10*PI/6){
					cvmSet(gradir,row,col,10);	
					
				}
				else if(cvmGet(gradir,row,col)>=10*PI/6&&cvmGet(gradir,row,col)<11*PI/6){
					cvmSet(gradir,row,col,11);	
				}
				else if(cvmGet(gradir,row,col)>=11*PI/6&&cvmGet(gradir,row,col)<12*PI/6){
					cvmSet(gradir,row,col,12);	
				}
				// done with quantization, feeding data to gradient direction histogram
				//printf("ha ereh hu %f\n", cvmGet(gradir,row,col));
				if(((int) (cvmGet(gradir,row,col)-1))!=-2)
			    gradcounter[((int) (cvmGet(gradir,row,col)-1))]++;
			}//for col
		}//for row
		cvReleaseImage(&dyy);
		cvReleaseImage(&dxx);
		cvReleaseImage(&dy);
		cvReleaseImage(&dx);
		cvReleaseImage(&dytemp);
		cvReleaseImage(&dxtemp);
		
		//gradient direction histogram is now done, handling the medium range features
		for(row=0;row<regionHeight;row++){
			for(col=0;col<regionWidth;col++){
				if(col==regionWidth-1 || row==0)
					n1=-1;
				else
					n1=((int) (cvmGet(gradir,row-1,col+1)));

				if(row==0)
					n2=-1;
				else
					n2=((int) (cvmGet(gradir,row-1,col)));

				if(row==0 || col==0)
					n3=-1;
				else
					n3=((int) (cvmGet(gradir,row-1,col-1)));

				if(col==0)
					n4=-1;
				else
					n4=((int) (cvmGet(gradir,row,col-1)));
				if(col==0 || row==regionHeight-1)
					n5=-1;
				else
					n5=((int) (cvmGet(gradir,row+1,col-1)));
				if(row==regionHeight-1)
					n6=-1;
				else
					n6=((int) (cvmGet(gradir,row+1,col)));
				if(row==regionHeight-1 || col==regionWidth-1)
					n7=-1;
				else
					n7=((int) (cvmGet(gradir,row+1,col+1)));
				if(col==regionWidth-1)
					n0=-1;
				else
					n0=((int) (cvmGet(gradir,row,col+1)));		
				//done gathering data about neighbours, checking for rules that apply
				if((n0==3||n0==4)&&(n4==3||n4==4))
				{
					rulecounter[0]++; //rule 1 applys here.
				}
				else if((n0==9||n0==10)&&(n4==9||n4==10))
				{
					rulecounter[1]++; //rule 2 applys here.
				}
				else if((n2==6||n2==7)&&(n6==6||n6==7))
				{
					rulecounter[2]++; //rule 3 applys here.
				}
				else if((n2==1||n2==12)&&(n6==1||n6==12))
				{
					rulecounter[3]++; //rule 4 applys here.
				}
				else if((n5==4||n5==5||n5==6)&&(n1==4||n1==5||n1==6))
				{
					rulecounter[4]++; //rule 5 applys here.
				}
				else if((n5==10||n5==11||n5==12)&&(n1==10||n1==11||n1==12))
				{
					rulecounter[5]++; //rule 6 applys here.
				}
				else if((n3==1||n3==2||n3==3)&&(n7==1||n7==2||n7==3))
				{
					rulecounter[6]++; //rule 7 applys here.
				}
				else if((n3==7||n3==8||n3==9)&&(n7==7||n7==8||n7==9))
				{
					rulecounter[7]++; //rule 8 applys here.
				}
				else if(((n0==9||n0==10)&&(n2==6||n2==7))||((n0==3||n0==4)&&(n2==1||n2==12)))
				{
					rulecounter[8]++; //rule 9 applys here.
				}
				else if(((n6==5||n6==6||n6==7)&&(n0==2||n0==3||n0==4))||((n6==1||n6==12||n6==11)&&(n0==9||n0==10||n0==11)))
				{
					rulecounter[9]++; //rule 10 applys here.
				}
				else if(((n2==1||n2==12||n2==11)&&(n4==8||n4==9||n4==10))||((n2==6||n2==7||n2==8)&&(n4==2||n4==3||n4==4)))
				{
					rulecounter[10]++; //rule 11 applys here.
				}
				else if(((n6==1||n6==12||n6==11)&&(n4==2||n4==3||n4==4))||((n6==6||n6==7||n6==8)&&(n4==8||n4==9||n4==10)))
				{
					rulecounter[11]++; //rule 12 applys here.
				}
				//done updating rule counter(histogram)
				}//col
			}//row
		//thresholding
		finalGradientThresh = regionWidth*regionHeight/ _gradientThresh;

		//computing threshold for rules
		trules1=rulecounter[0];
		for(l=0;l<12;l++){
			if(rulecounter[l]>trules1)
				trules1=rulecounter[l];
		}
				
		finalRulesThresh=trules1/_rulesThresh;
		result=0;
		for(l=0;l<12;l++){//gradient direction
			if (gradcounter[l]>=finalGradientThresh)
				result |= (1<<(31-l)); // for gradient direction 1 (l=0) we use bit 31 and so on


		 }
		for(l=0;l<12;l++){//rules
			if(rulecounter[l]>=finalRulesThresh || (l>=8&&l<=11&&rulecounter[l]>0))
					result |= (1<<(19-l));
				
		}
		cvReleaseData(gradir);
		return result;

	}


//Used for extracting the density feature, img is a region in the original image
//Returns an int where bit 7 specifies if the region is dense (in terms of black pixels - foreground pixels)
	int GSCFeature::extractDensity(IplImage* subimg){
		int result,row,col,foregroundCounter,regionHeight,regionWidth,regionStep,finalDensityThresh;
		uchar *subdata;
		result=0;
		foregroundCounter=0;
		regionHeight=subimg->height;
		regionWidth=subimg->width;
		regionStep=subimg->widthStep;
		//assigning a pointer to the data stored in the image
		subdata=(uchar *)subimg->imageData;
		//counting the number of foreground pixels ! (black pixels)

		for(row=0;row<regionHeight;row++){
			for(col=0;col<regionWidth;col++){
				if(subdata[regionStep*row+col]==0){
					foregroundCounter++;
				}
			}
		}
	//end of counting, the number of foreground pixels in this region(i,j) is in foregroundCounter	
	finalDensityThresh=regionHeight*regionWidth/_densityThresh;
	if(foregroundCounter>=finalDensityThresh)
		result |= (1<<7);
	return result;
	}


//Used for extracting the large strokes (vertical and horizontal) features, img is a region in the original image
//Returns an int where bits 6,5 specify if any large strokes are appearant in the region (6 for horizontal, 5 for vertical)
	int GSCFeature::extractLargeStrokes(IplImage* subimg){
		int result,row,col,regionHeight,regionWidth,regionStep,finalHorizontalThresh,finalVerticalThresh,verticalRunLength,horizontalRunLength,maxRunLength;
		uchar *subdata;
		result=0;
		regionHeight=subimg->height;
		regionWidth=subimg->width;
		regionStep=subimg->widthStep;
		//assigning a pointer to the data stored in the image
		subdata=(uchar *)subimg->imageData;
		verticalRunLength=0;
		horizontalRunLength=0;
		maxRunLength=0;
		//measuring the vertical and horizontal run lengths in the region
		for(row=0;row<regionHeight;row++){
			  col=0;
			while(col<regionWidth)
			{
				while(col<regionWidth&&subdata[regionStep*row+col]!=0)
				{
					col++;
				}
				horizontalRunLength=0;
				while(col<regionWidth&&subdata[regionStep*row+col]==0){
					horizontalRunLength++;
					col++;
				}
				if (horizontalRunLength>maxRunLength)
					maxRunLength=horizontalRunLength;
				
		}
	  }


	  horizontalRunLength=maxRunLength;
	  maxRunLength=0;
	  	  for(col=0;col<regionWidth;col++){
		  row=0;
		while(row<regionHeight)
		{
				while(row<regionHeight&&subdata[regionStep*row+col]!=0)
				{
					row++;
				}
				verticalRunLength=0;
				while(row<regionHeight&&subdata[regionStep*row+col]==0){
					verticalRunLength++;
					row++;
				}
				if (verticalRunLength>maxRunLength)
					maxRunLength=verticalRunLength;
				
		}
	  }
		  verticalRunLength=maxRunLength;
	
	
	  //done computing run lengths
	  //now we can check if the run lengths are long enough and set the bit.

		finalVerticalThresh=_verticalStrokeThresh*regionHeight;
		finalHorizontalThresh=_horizontalStrokeThresh*regionWidth;
		finalVerticalThresh=((int) finalVerticalThresh);
		finalHorizontalThresh=((int) finalHorizontalThresh);

		if(verticalRunLength>=finalVerticalThresh)
			result |= (1<<5);
	
		if(horizontalRunLength>=finalHorizontalThresh)
			result |= (1<<6);
		return result;
	}


//Used for extracting the concavity features from the image, img is a region in the original image.
//Returns an int where bits 4..0 specify the concavity direction of the region (as specified in the article)
	int GSCFeature::extractConcavityDirection(IplImage* subimg){
		int star[8];
		int up,down,left,right,hole,result,finalConcavityThresh,row,col,l,tmprow,tmpcol,regionHeight,regionWidth,regionStep;
		uchar *subdata;
		//assigning a pointer to the data stored in the image
		subdata=(uchar *)subimg->imageData;
		regionHeight=subimg->height;
		regionWidth=subimg->width;
		regionStep=subimg->widthStep;
		result=0;
		up=0;
		down=0;
		left=0;
		right=0;
		hole=0;
			//concavity features ! UDLRH
				for(row=0;row<regionHeight;row++){
					for(col=0;col<regionWidth;col++){
						//resetting the operator state
						for(l=0;l<8;l++){
							star[l]=0;
						}
						//advancing in each direction until we hit a foreground pixel, and write the termination status down.
						//checking if it even is a background pixel
						if(subdata[row*regionStep+col]!=0){

							if(col<regionWidth-1&&subdata[row*regionStep+col+1]!=0)//can we move right ?
							{
								tmprow=row;
								tmpcol=col;
								while(tmpcol<regionWidth&&subdata[regionStep*tmprow+tmpcol]!=0){
									tmpcol++;
								}//moving right
								if(tmpcol==regionWidth)
								{//we reached the wall
									star[0]=0; // 0 meaning open
								}
								else{//we hit a foreground pixel
									star[0]=1;
								}
							}//termination status for right

							if(col>0&&subdata[row*regionStep+col-1]!=0)//can we move left ?
							{
								tmprow=row;
								tmpcol=col;
								while((tmpcol>-1)&&(subdata[regionStep*tmprow+tmpcol]!=0)){
									tmpcol--;
								}//moving left
								if(tmpcol==-1)
								{//we reached the wall
									star[4]=0; // 0 meaning open
								}
								else{//we hit a foreground pixel
								//	printf("pixel problem is %d %d\n",row,col);
								//	subdata[45*regionWidth+74]=2;
									star[4]=1;
								}
							}//termination status for left

							if(row>0&&subdata[(row-1)*regionStep+col]!=0)//can we move up ?
							{
								tmprow=row;
								tmpcol=col;
								while(tmprow>-1&&subdata[regionStep*tmprow+tmpcol]!=0){
									tmprow--;
								}//moving up
								if(tmprow==-1)
								{//we reached the wall
									star[2]=0; // 0 meaning open
								}
								else{//we hit a foreground pixel
									star[2]=1;
								}
							}//termination status for up

							if(row<regionHeight-1&&subdata[(row+1)*regionStep+col]!=0)//can we move down ?
							{
								tmprow=row;
								tmpcol=col;
								while(tmprow<regionHeight&&subdata[regionStep*tmprow+tmpcol]!=0){
									tmprow++;
								}//moving down
								if(tmprow==regionHeight)
								{//we reached the wall
									star[6]=0; // 0 meaning open
								}
								else{//we hit a foreground pixel
									star[6]=1;
								}
							}//termination status for down

							if(((col<regionWidth-1)&&(row>0))&&subdata[(row-1)*regionStep+col+1]!=0)//can we move right-up ?
							{
								tmprow=row;
								tmpcol=col;
								while(tmpcol<regionWidth&&tmprow>-1&&subdata[regionStep*tmprow+tmpcol]!=0){
									tmpcol++;
									tmprow--;
								}//moving right-up
								if(tmpcol==regionWidth||tmprow==-1)
								{//we reached the wall
									star[1]=0; // 0 meaning open
								}
								else{//we hit a foreground pixel
									star[1]=1;
								}
							}//termination status for right-up
							if((col>0&&row>0)&&subdata[(row-1)*regionStep+col-1]!=0)//can we move left-up ?
							{
								tmprow=row;
								tmpcol=col;
								while(tmpcol>-1&&tmprow>-1&&subdata[regionStep*tmprow+tmpcol]!=0){
									tmpcol--;
									tmprow--;
								}//moving left-up
								if(tmpcol==-1||tmprow==-1)
								{//we reached the wall
									star[3]=0; // 0 meaning open
								}
								else{//we hit a foreground pixel
									star[3]=1;
								}
							}//termination status for left-down
							if((col>0&&row<regionHeight-1)&&subdata[(row+1)*regionStep+col-1]!=0)//can we move left-up ?
							{
								tmprow=row;
								tmpcol=col;
								while(tmpcol>-1&&tmprow<regionHeight&&subdata[regionStep*tmprow+tmpcol]!=0){
									tmpcol--;
									tmprow++;
								}//moving left-down
								if(tmpcol==-1||tmprow==regionHeight)
								{//we reached the wall
									star[5]=0; // 0 meaning open
								}
								else{//we hit a foreground pixel
									star[5]=1;
								}
							}//termination status for right-down
							if((col<regionWidth-1&&row<regionHeight-1)&&subdata[(row+1)*regionStep+col+1]!=0)//can we move right-down ?
							{
								tmprow=row;
								tmpcol=col;
								while(tmpcol<regionWidth&&tmprow<regionHeight&&subdata[regionStep*tmprow+tmpcol]!=0){
									tmpcol++;
									tmprow++;
								}//moving right-down
								if(tmpcol==regionWidth||tmprow==regionHeight)
								{//we reached the wall
									star[7]=0; // 0 meaning open
								}
								else{//we hit a foreground pixel
									star[7]=1;
								}
							}//termination status for right-down
							//deciding the concavity status
							if(star[5]==1&&star[6]==1&&star[7]==1&&((star[2]==0&&star[1]==0&&star[3]==1)||(star[2]==0&&star[1]==1&&star[3]==0)||(star[2]==0&&star[1]==0&&star[3]==0))){
							
								up++;
							}
							else if(star[2]==1&&star[1]==1&&star[3]==1&&((star[5]==0&&star[6]==0&&star[7]==0)||(star[5]==0&&star[6]==0&star[7]==1)||(star[5]==1&&star[6]==0&&star[7]==0))){
			//						subdata[regionStep*row+col]=120;
								down++;
							}
							else if(star[3]==1&&star[4]==1&&star[5]==1&&((star[1]==0&&star[0]==0&&star[7]==0)||(star[1]==0&&star[0]==0&star[7]==1)||(star[1]==1&&star[0]==0&&star[7]==0))){
								//subdata[row*regionWidth+col]=0;
								right++;
							}			
							else if(star[1]==1&&star[0]==1&&star[7]==1&&((star[3]==0&&star[4]==0&&star[5]==0)||(star[3]==0&&star[4]==0&star[5]==1)||(star[3]==1&&star[4]==0&&star[5]==0))){
								left++;
							}
							else if((star[0]==1 &&star[1]==1&& star[2]==1 &&star[3]==1 &&star[4]==1 &&star[5]==1 &&star[6]==1&& star[7]==1)||(star[0]==1 &&star[1]==1&& star[2]==1 &&star[3]==1 &&star[4]==1 &&star[5]==1 &&star[6]==1&& star[7]==0)||(star[0]==1 &&star[1]==1&& star[2]==1 &&star[3]==1 &&star[4]==1 &&star[5]==1 &&star[6]==0&& star[7]==1)||(star[0]==1 &&star[1]==1&& star[2]==1 &&star[3]==1 &&star[4]==1 &&star[5]==0 &&star[6]==1&& star[7]==1)||(star[0]==1 &&star[1]==1&& star[2]==1 &&star[3]==1 &&star[4]==0 &&star[5]==1 &&star[6]==1&& star[7]==1)||(star[0]==1 &&star[1]==1&& star[2]==1 &&star[3]==0 &&star[4]==1 &&star[5]==1 &&star[6]==1&& star[7]==1)||(star[0]==1 &&star[1]==1&& star[2]==0 &&star[3]==1 &&star[4]==1 &&star[5]==1 &&star[6]==1&& star[7]==1)||(star[0]==1 &&star[1]==0&& star[2]==1 &&star[3]==1 &&star[4]==1 &&star[5]==1 &&star[6]==1&& star[7]==1)||(star[0]==0 &&star[1]==1&& star[2]==1 &&star[3]==1 &&star[4]==1 &&star[5]==1 &&star[6]==1&& star[7]==1))
							{
								hole++;
							}

						}//if its a background pixel
					}//col

				}//row
				finalConcavityThresh=regionWidth*regionHeight/_concavityThresh;

				if(hole>=finalConcavityThresh)
					result |= (1<<4);

				if(right>=finalConcavityThresh)
					result |= (1<<3);

				if(left>=finalConcavityThresh)
						result |= (1<<2);

				if(down>=finalConcavityThresh)
					result |= (1<<1);

				if(up>=finalConcavityThresh)
					result |= 1;
				return result;
		}

/*

If provided with a binary (each pixel is either black (0) or white (1)) image,
returns a vector of 16 features, each one corresponding with a rectangle containing 1/16th of the image
In which several features are computed :

bits 31..20 each specify if gradient direction i (in quantization of [0..2*pi] to 12 equal segments) is strongly represented in the region

bits 19..8 each specify if rule i of the mini-structure rules table (as specified in the GSC article) applies in the region

bit 7 specifies if the region is dense (in terms of black pixels - foreground pixels)

bits 6,5 specify if any large strokes are appearant in the region (6 for horizontal, 5 for vertical)

bits 4..0 specify the concavity direction of the region (as specified in the article)


*/
void GSCFeatures::extract(ConnectedComponent& com, FeatureVector* p) {

  IplImage *subimg=0;
  IplImage* img = 0; 
  int height,width,step,channels,regionWidth,regionHeight,regionStep;
  uchar *data;
  int featureCollection;
  int i,j,l,row,col;

  // load the image from the ConnectedComponenet  

  	GSCFeature* pf = (GSCFeature*)p ;
	cv::Mat mat = com.getImage()->getMat() ;
	IplImage dst_img = mat;
	img=&dst_img;

  // get the image data
  height    = img->height;
  width     = img->width;
  step      = img->widthStep;
  channels  = img->nChannels;
  data      = (uchar *)img->imageData;
  regionHeight=height/4;
  regionWidth=width/4;
  regionStep=step/4;
  //binarization (not needed in actual algorithm)
  for(i=0;i<height;i++){
	for(j=0;j<width;j++){
		if(data[width*i+j]>100){
			data[width*i+j]=255;
		}
		else{
			data[width*i+j]=0;
		}
	}
}
  //end of binarization

 for(i=0;i<4;i++){
	for(j=0;j<4;j++){

		//setting the current ROI to be the correct 1/16th of the image
	    subimg=cvCreateImage(cvSize(regionWidth,regionHeight),IPL_DEPTH_8U,img->nChannels);
		cvSetImageROI(img,cvRect(j*regionWidth,i*regionHeight,regionWidth,regionHeight));
		cvCopy(img, subimg,NULL);
		cvResetImageROI(img);
		
		//collecting the different features from the region.
		featureCollection=extractGradientFeatures(subimg);
		featureCollection|=extractDensity(subimg);
		featureCollection|=extractLargeStrokes(subimg);
		featureCollection|=extractConcavityDirection(subimg);

		//adding the feature for the i,j grid region to the feature vector
		printf("bakara %d mosif %d , %d\n",featureCollection,i,j);
		pf->addItem(featureCollection);
		//releasing memory
		cvReleaseImage(&subimg);

}//j
}//i
  


  // release the image
 // cvReleaseImage(&img);
  return;
}
