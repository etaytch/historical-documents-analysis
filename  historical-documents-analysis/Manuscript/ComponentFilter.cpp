#include "ComponentFilter.h"

ComponentFilter::ComponentFilter(void){
}


ComponentFilter::~ComponentFilter(void){
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	This is a virtual function that Filters one connected component </summary>
///
/// <remarks>	El Sana, 2/15/2012. </remarks>
///
/// <param name="comp">	[in] The component. </param>
///
/// <returns>	true if it succeeds, false if it fails. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

bool ComponentFilter::filter(ConnectedComponent& comp){
	return ( comp.getContour().getArea() < _area );
}
