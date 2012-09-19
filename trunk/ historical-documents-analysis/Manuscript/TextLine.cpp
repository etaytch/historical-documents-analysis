#include "TextLine.h"


TextLine::TextLine(){
	_upper = new vector<Point>();
	_lower = new vector<Point>();
}


TextLine::~TextLine(){
	delete _upper ;
	delete _lower ;
	
}


void TextLine::setPoints(Point upper,Point lower){
	_upper->push_back(upper);
	_lower->push_back(lower);
}
Point TextLine::getUpper(int index){
	return _upper->at(index);
}
Point TextLine::getLower(int index){
	return _lower->at(index);
}

void TextLine::setUpperPoint(Point upper)
{
	_upper->push_back(upper);
}

void TextLine::setUpperPoint(int x,int y)
{
	_upper->push_back(Point(x,y));
}

void TextLine::removeUpperPoint(int index)
{
	_upper->erase(_upper->begin()+index-1);
}

void TextLine::setLowerPoint(Point lower)
{
	_lower->push_back(lower);
}

void TextLine::setLowerPoint(int x,int y)
{
	_lower->push_back(Point(x,y));
}

void TextLine::removeLowerPoint(int index)
{
	_lower->erase(_lower->begin()+index-1);
}

void TextLine::setRect(int x,int y,int height,int width){
	_rect.x = x;
	_rect.y = y;
	_rect.height = height;
	_rect.width = width;
}

Rect TextLine::getRect(){
	return _rect;
}

void TextLine::setRect(Rect rect){
	_rect = rect;
}


