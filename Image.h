#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

class image {
public:
	struct pixel {
		unsigned char blueComp;
		unsigned char greenComp;
		unsigned char redComp;
		pixel(unsigned char _blueComp, unsigned char _greenComp, unsigned char _redComp);
	};

	struct header {
		char idLength;
		char colorMapType;
		char dataTypeCode;
		short colorMapOrigin;
		short colorMapLength;
		char colorMapDepth;
		short xOrigin;
		short yOrigin;
		short width;
		short height;
		char bitsPerPixel;
		char imageDescriptor;
		header(char _idLength, char _colorMapType, char _dataTypeCode, short _colorMapOrigin, short _colorMapLength, char _colorMapDepth,
			short _xOrigin, short _yOrigin, short _width, short _height, char _bitsPerPixel, char _imageDescriptor);
		header();
	};
	vector<image::pixel> pixels;
	header thisHeader;

public:
	image(image::header _header, vector<image::pixel> _pixels);
	void displayHeader(image& image);
	char getIdLength();
	char getColorMapType();
	char getDataTypeCode();
	short getColorMapOrigin();
	short getColorMapLength();
	char getColorMapDepth();
	short getXOrigin();
	short getYOrigin();
	short getWidth();
	short getHeight();
	char getBitsPerPixel();
	char getImageDescriptor();
	vector<image::pixel>& getPixels();
	bool operator==(image const& rhs);
};
