#ifndef _BINARIZER_H 
#define _BINARIZER_H 

#include <opencv\cv.h>

#include "DImage.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Binarizer class implements a binarization algorithm. This is a base class that each 
/// 			new algorithm should use and implement the virtual function binarize </summary>
///
/// <remarks>	El Sana, 2/9/2012. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class Binarizer {
protected:
	DImage _image ;

public:
	Binarizer(void){;}
	~Binarizer(void){;}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Sets an image to be binarized. </summary>
	///
	/// <remarks>	El Sana, 2/15/2012. </remarks>
	///
	/// <param name="img">	[in] The image. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void setImage(DImage& img){
		_image = img ;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the image to be binarized </summary>
	///
	/// <remarks>	El Sana, 2/15/2012. </remarks>
	///
	/// <returns>	The image. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	DImage& getImage(){
		return _image ;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Binarize is the virtual function to implement a binarization algorithm in the 
	/// 			extended class </summary>
	///
	/// <remarks>	El Sana, 2/15/2012. </remarks>
	///
	/// <returns>	null if it fails, else. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual DImage* binarize() = 0;
};

#endif 