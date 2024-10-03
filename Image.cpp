#include"Image.h"
#include<iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

image::header::header() {
	idLength = 0;
	colorMapType = 0;
	dataTypeCode = 0;
	colorMapOrigin = 0;
	colorMapLength = 0;
	colorMapDepth = 0;
	xOrigin = 0;
	yOrigin = 0;
	width = 0;
	height = 0;
	bitsPerPixel = 0;
	imageDescriptor = 0;
}
image::header::header(char _idLength, char _colorMapType, char _dataTypeCode, short _colorMapOrigin, short _colorMapLength, char _colorMapDepth,
	short _xOrigin, short _yOrigin, short _width, short _height, char _bitsPerPixel, char _imageDescriptor) {
	idLength = _idLength;
	colorMapType = _colorMapType;
	dataTypeCode = _dataTypeCode;
	colorMapOrigin = _colorMapOrigin;
	colorMapLength = _colorMapLength;
	colorMapDepth = _colorMapDepth;
	xOrigin = _xOrigin;
	yOrigin = _yOrigin;
	width = _width;
	height = _height;
	bitsPerPixel = _bitsPerPixel;
	imageDescriptor = _imageDescriptor;
}
image::image(image::header _header, vector<image::pixel> _pixels) {
	thisHeader.idLength = _header.idLength;
	thisHeader.colorMapType = _header.colorMapType;
	thisHeader.dataTypeCode = _header.dataTypeCode;
	thisHeader.colorMapOrigin = _header.colorMapOrigin;
	thisHeader.colorMapLength = _header.colorMapLength;
	thisHeader.colorMapDepth = _header.colorMapDepth;
	thisHeader.xOrigin = _header.xOrigin;
	thisHeader.yOrigin = _header.yOrigin;
	thisHeader.width = _header.width;
	thisHeader.height = _header.height;
	thisHeader.bitsPerPixel = _header.bitsPerPixel;
	thisHeader.imageDescriptor = _header.imageDescriptor;
	

	for (unsigned int i = 0; i < _pixels.size(); i++) {
		unsigned char blueComp; 
		blueComp = _pixels[i].blueComp;

		unsigned char greenComp;
		greenComp = _pixels[i].greenComp;

		unsigned char redComp;
		redComp = _pixels[i].redComp;

		image::pixel currentPixel(blueComp, greenComp, redComp);
		pixels.push_back(currentPixel);
	}
}

void image::displayHeader(image& image) {
	cout << "ID Length: " << (int)thisHeader.idLength << endl << "Color Map Type: " << (int)thisHeader.colorMapType << endl << "Data Type Code: " << (int)thisHeader.dataTypeCode << endl <<
		"Color Map Origin: " << thisHeader.colorMapOrigin << endl << "Color Map Length: " << thisHeader.colorMapLength << endl << "Color Map Depth: " << thisHeader.colorMapDepth
		<< endl << "X Origin: " << thisHeader.xOrigin << endl << "Y Origin: " << thisHeader.yOrigin << endl << "Width: " << thisHeader.width << endl << "Height: " << thisHeader.height <<
		endl << "Bits Per Pixel: " << (int)thisHeader.bitsPerPixel << endl << "Image Descriptor: " << (int)thisHeader.imageDescriptor << endl;
}

image::pixel::pixel(unsigned char _blueComp, unsigned char _greenComp, unsigned char _redComp) {
	blueComp = _blueComp;
	greenComp = _greenComp;
	redComp = _redComp;
}

char image::getIdLength() {
	return thisHeader.idLength;
}
char image::getColorMapType() {
	return thisHeader.colorMapType;
}
char image::getDataTypeCode() {
	return thisHeader.dataTypeCode;
}
short image::getColorMapOrigin() {
	return thisHeader.colorMapOrigin;
}
short image::getColorMapLength() {
	return thisHeader.colorMapLength;
}
char image::getColorMapDepth() {
	return thisHeader.colorMapDepth;
}
short image::getXOrigin() {
	return thisHeader.xOrigin;
}
short image::getYOrigin() {
	return thisHeader.yOrigin;
}
short image::getWidth() {
	return thisHeader.width;
}
short image::getHeight() {
	return thisHeader.height;
}
char image::getBitsPerPixel() {
	return thisHeader.bitsPerPixel;
}
char image::getImageDescriptor() {
	return thisHeader.imageDescriptor;
}
vector<image::pixel>& image::getPixels() {
	return pixels;
}

bool image::operator==(image const& rhs) {
	for (int i = 0; i < rhs.pixels.size(); i++) {
		if ((rhs.pixels[i].blueComp != this->pixels[i].blueComp) || (rhs.pixels[i].greenComp != this->pixels[i].greenComp) ||
			(rhs.pixels[i].redComp != this->pixels[i].redComp)) {
			return false;
		}
	}
	return true;
}