#include"Image.h"
#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

vector<image> images;
void readImage(ifstream& input);
void writeImage(ofstream& output, image& outImage);
void partOne(vector<image>& images);
void partTwo(vector<image>& images);
void partThree(vector<image>& images);
void partFour(vector<image>& images);
void partFive(vector<image>& images);
void partSix(vector<image>& images);
void partSeven(vector<image>& images);
void partEight(vector<image>& images);
void partNine(vector<image>& images);
void partTen(vector<image>& images);

void multiply(vector<image::pixel> topLayer, vector<image::pixel> bottomLayer, vector<image::pixel>& outPixels);
void subtract(vector<image::pixel> topLayer, vector<image::pixel> bottomLayer, vector<image::pixel>& outPixels);
void test(image image1, image image2);

int main(){
	images.clear();

	ifstream car("input/car.tga", ios_base::binary);
	ifstream circles("input/circles.tga", ios_base::binary);
	ifstream layer_blue("input/layer_blue.tga", ios_base::binary);
	ifstream layer_green("input/layer_green.tga", ios_base::binary);
	ifstream layer_red("input/layer_red.tga", ios_base::binary);
	ifstream layer1("input/layer1.tga", ios_base::binary);
	ifstream layer2("input/layer2.tga", ios_base::binary);
	ifstream pattern1("input/pattern1.tga", ios_base::binary);
	ifstream pattern2("input/pattern2.tga", ios_base::binary);
	ifstream text("input/text.tga", ios_base::binary);
	ifstream text2("input/text2.tga", ios_base::binary);

	readImage(car);
	readImage(circles);
	readImage(layer_blue);
	readImage(layer_green);
	readImage(layer_red);
	readImage(layer1);
	readImage(layer2);
	readImage(pattern1);
	readImage(pattern2);
	readImage(text);
	readImage(text2);

	partOne(images);
	partTwo(images);
	partThree(images);
	partFour(images);
	partFive(images);
	partSix(images);
	partSeven(images);
	partEight(images);
	partNine(images);
	partTen(images);
	

	

}

void readImage(ifstream& input) {
	char idLength;
	input.read(&idLength, sizeof(idLength));

	char colorMapType;
	input.read(&colorMapType, sizeof(colorMapType));

	char imageType;
	input.read(&imageType, sizeof(imageType));

	short colorMapOrigin;
	input.read(reinterpret_cast<char*>(&colorMapOrigin), sizeof(colorMapOrigin));

	short colorMapLength;
	input.read(reinterpret_cast<char*>(&colorMapLength), sizeof(colorMapLength));

	char colorMapDepth;
	input.read(&colorMapDepth, sizeof(colorMapDepth));

	short xOrigin;
	input.read(reinterpret_cast<char*>(&xOrigin), sizeof(xOrigin));

	short yOrigin;
	input.read(reinterpret_cast<char*>(&yOrigin), sizeof(yOrigin));

	short width;
	input.read(reinterpret_cast<char*>(&width), sizeof(width));

	short heigth;
	input.read(reinterpret_cast<char*>(&heigth), sizeof(heigth));

	char bitsPerPixel;
	input.read(&bitsPerPixel, sizeof(bitsPerPixel));

	char imageDescriptor;
	input.read(&imageDescriptor, sizeof(imageDescriptor));

	image::header readHeader(idLength, colorMapType, imageType, colorMapOrigin, colorMapLength, colorMapDepth, xOrigin, yOrigin, width, heigth,
		bitsPerPixel, imageDescriptor);

	vector<image::pixel> pixels;
	int pixelNums = (int)width * (int)heigth; 
	for (int i = 0; i < pixelNums; i++){
		unsigned char blueComp;
		input.read(reinterpret_cast<char*>(&blueComp), sizeof(blueComp));

		unsigned char greenComp;
		input.read(reinterpret_cast<char*>(&greenComp), sizeof(greenComp));

		unsigned char redComp;
		input.read(reinterpret_cast<char*>(&redComp), sizeof(redComp));

		image::pixel currentPixel(blueComp, greenComp, redComp);
		pixels.push_back(currentPixel);
	}

	image thisImage(readHeader, pixels);

	images.push_back(thisImage);
}

void writeImage(ofstream& output, image& outImage) {
	char idLength = outImage.getIdLength();
	output.write(&idLength, sizeof(idLength));

	char colorMapType = outImage.getColorMapType();
	output.write(&colorMapType, sizeof(colorMapType));

	char dataTypeCode = outImage.getDataTypeCode();
	output.write(&dataTypeCode, sizeof(dataTypeCode));

	short colorMapOrigin = outImage.getColorMapOrigin();
	output.write(reinterpret_cast<char*>(&colorMapOrigin), sizeof(colorMapOrigin));

	short colorMapLength = outImage.getColorMapLength();
	output.write(reinterpret_cast<char*>(&colorMapLength), sizeof(colorMapLength));

	char colorMapDepth = outImage.getColorMapDepth();
	output.write(&colorMapDepth, sizeof(colorMapDepth));

	short xOrigin = outImage.getXOrigin();
	output.write(reinterpret_cast<char*>(&xOrigin), sizeof(xOrigin));

	short yOrigin = outImage.getYOrigin();
	output.write(reinterpret_cast<char*>(&yOrigin), sizeof(yOrigin));

	short width = outImage.getWidth();
	output.write(reinterpret_cast<char*>(&width), sizeof(width));

	short heigth = outImage.getHeight();
	output.write(reinterpret_cast<char*>(&heigth), sizeof(heigth));

	char bitsPerPixel = outImage.getBitsPerPixel();
	output.write(&bitsPerPixel, sizeof(bitsPerPixel));

	char imageDescriptor = outImage.getImageDescriptor();
	output.write(&imageDescriptor, sizeof(imageDescriptor));

	vector<image::pixel>& pixels = outImage.getPixels();
	for (unsigned int i = 0; i < pixels.size(); i++) {
		unsigned char blueComp = pixels[i].blueComp;
		output.write(reinterpret_cast<char*>(&blueComp), sizeof(blueComp));

		unsigned char greenComp = pixels[i].greenComp;
		output.write(reinterpret_cast<char*>(&greenComp), sizeof(greenComp));

		unsigned char redComp = pixels[i].redComp;
		output.write(reinterpret_cast<char*>(&redComp), sizeof(redComp));
	}
}

void partOne(vector<image>& images) {
	vector<image::pixel> topLayer = images[5].getPixels();
	vector<image::pixel> bottomLayer = images[7].getPixels();
	vector<image::pixel> outPixels;

	multiply(topLayer, bottomLayer, outPixels);

	image outImage(images[5].thisHeader, outPixels);
	ofstream part1("output/part1.tga", ios_base::binary);

	ifstream example1("examples/EXAMPLE_part1.tga", ios_base::binary);
	readImage(example1);
	test(images[11], outImage);

	writeImage(part1, outImage);
}
void partTwo(vector<image>& images) {
	vector<image::pixel> topImage = images[6].getPixels();
	vector<image::pixel> bottomImage = images[0].getPixels();
	vector<image::pixel> outPixels;

	subtract(topImage, bottomImage, outPixels);

	image outImage(images[6].thisHeader, outPixels);

	ifstream example2("examples/EXAMPLE_part2.tga", ios_base::binary);
	readImage(example2);
	test(images[12], outImage);


	ofstream part2("output/part2.tga", ios_base::binary);
	writeImage(part2, outImage);
}
void partThree(vector<image>& images) {
	vector<image::pixel> topLayer = images[8].getPixels();
	vector<image::pixel> bottomLayer = images[5].getPixels();
	vector<image::pixel> tempPixels;

	multiply(topLayer, bottomLayer, tempPixels);

	vector<image::pixel> textLayer = images[9].getPixels();
	vector<image::pixel> outPixels;
	for (int i = 0; i < 262144; i++) {
		float _blue = ((1 - (1 - ((float)textLayer[i].blueComp / 255)) * (1 - ((float)tempPixels[i].blueComp / 255))) * 255 + 0.5);
		float _red = ((1 - (1 - ((float)textLayer[i].redComp / 255)) * (1 - ((float)tempPixels[i].redComp / 255))) * 255 + 0.5);
		float _green = ((1 - (1 - ((float)textLayer[i].greenComp / 255)) * (1 - ((float)tempPixels[i].greenComp / 255))) * 255 + 0.5);


		unsigned char blue = (unsigned char)_blue;
		unsigned char red = (unsigned char)_red;
		unsigned char green = (unsigned char)_green;

		outPixels.push_back(image::pixel(blue, green, red));
	}
	image outImage(images[5].thisHeader, outPixels);

	ifstream example3("examples/EXAMPLE_part3.tga", ios_base::binary);
	readImage(example3);
	test(images[13], outImage);


	ofstream part3("output/part3.tga", ios_base::binary);

	writeImage(part3, outImage);
}
void partFour(vector<image>& images) {
	vector<image::pixel> topLayer = images[6].getPixels();
	vector<image::pixel> circleLayer = images[1].getPixels();
	vector<image::pixel> tempPixels;

	multiply(circleLayer, topLayer, tempPixels);
	vector<image::pixel> pattern2 = images[8].getPixels();
	vector<image::pixel> outPixels;

	subtract(pattern2, tempPixels, outPixels);

	image outImage(images[1].thisHeader, outPixels);

	ifstream example4("examples/EXAMPLE_part4.tga", ios_base::binary);
	readImage(example4);
	test(images[14], outImage);


	ofstream part4("output/part4.tga", ios_base::binary);
	writeImage(part4, outImage);

}
void partFive(vector<image>& images) {
	vector<image::pixel> topLayer = images[5].getPixels();
	vector<image::pixel> bottomLayer = images[7].getPixels();
	vector<image::pixel> outPixels;

	for (int i = 0; i < 262144; i++) {
		float _blue = ((float)bottomLayer[i].blueComp / 255);
		float _green = ((float)bottomLayer[i].greenComp / 255);
		float _red = ((float)bottomLayer[i].redComp / 255);


		if (_blue <= 0.5) {
			_blue = ((2 * ((float)topLayer[i].blueComp / 255) * _blue));
		}
		else {
			_blue = ((1 - (2 * ((1 - ((float)topLayer[i].blueComp / 255)) * (1 - _blue)))));
		}
		if (_green <= 0.5) {
			_green = ((2 * ((float)topLayer[i].greenComp / 255) * _green));
		}
		else {
			_green = ((1 - (2 * ((1 - ((float)topLayer[i].greenComp / 255)) * (1 - _green)))));
		}
		if (_red <= 0.5) {
			_red = ((2 * ((float)topLayer[i].redComp / 255) * _red));
		}
		else {
			_red = ((1 - (2 * ((1 - ((float)topLayer[i].redComp / 255)) * (1 - _red)))));
		}


		_blue = ((_blue * 255) + 0.5);
		_green = ((_green * 255) + 0.5);
		_red = ((_red * 255) + 0.5);

		unsigned char blue = (unsigned char)_blue;
		unsigned char green = (unsigned char)_green;
		unsigned char red = (unsigned char)_red;

		outPixels.push_back(image::pixel(blue, green, red));
	}
	image outImage(images[5].thisHeader, outPixels);

	ifstream example5("examples/EXAMPLE_part5.tga", ios_base::binary);
	readImage(example5);
	test(images[15], outImage);


	ofstream part5("output/part5.tga", ios_base::binary);

	writeImage(part5, outImage);
	
}
void partSix(vector<image>& images) {
	vector<image::pixel> car = images[0].getPixels();
	vector<image::pixel> outPixels;

	for (int i = 0; i < 262144; i++) {
		int _green = (int)car[i].greenComp + 200;
		if (_green > 255) {
			_green = 255;
		}
		unsigned char green = (unsigned char)_green;
		outPixels.push_back(image::pixel(car[i].blueComp, green, car[i].redComp));
	}

	image outImage(images[0].thisHeader, outPixels);

	ifstream example6("examples/EXAMPLE_part6.tga", ios_base::binary);
	readImage(example6);
	test(images[16], outImage);


	ofstream part6("output/part6.tga", ios_base::binary);
	writeImage(part6, outImage);

}
void partSeven(vector<image>& images) {
	vector<image::pixel> car = images[0].getPixels();
	vector<image::pixel> outPixels;

	for (int i = 0; i < 262144; i++) {
		float _red = ((float)car[i].redComp / 255) * 4;
		float _blue = 0;

		if ((_red * 255) >= 255) {
			_red = 255;
		}
		else {
			_red = _red * 255 + 0.5;
		}
		unsigned char red = (unsigned char)_red;
		unsigned char blue = (unsigned char)_blue;

		outPixels.push_back(image::pixel(blue, car[i].greenComp, red));
	}
	image outImage(images[0].thisHeader, outPixels);

	ifstream example7("examples/EXAMPLE_part7.tga", ios_base::binary);
	readImage(example7);
	test(images[17], outImage);


	ofstream part7("output/part7.tga", ios_base::binary);
	writeImage(part7, outImage);
}
void partEight(vector<image>& images) {
	vector<image::pixel> imageToSplit = images[0].getPixels();
	vector<image::pixel> bluePixels;
	vector<image::pixel> greenPixels;
	vector<image::pixel> redPixels;

	for (int i = 0; i < 262144; i++) {
		bluePixels.push_back(image::pixel(imageToSplit[i].blueComp, imageToSplit[i].blueComp, imageToSplit[i].blueComp));
		greenPixels.push_back(image::pixel(imageToSplit[i].greenComp, imageToSplit[i].greenComp, imageToSplit[i].greenComp));
		redPixels.push_back(image::pixel(imageToSplit[i].redComp, imageToSplit[i].redComp, imageToSplit[i].redComp));
	}
	image blueImage(images[0].thisHeader, bluePixels);
	image greenImage(images[0].thisHeader, greenPixels);
	image redImage(images[0].thisHeader, redPixels);

	ofstream part8_b("output/part8_b.tga", ios_base::binary);
	ofstream part8_g("output/part8_g.tga", ios_base::binary);
	ofstream part8_r("output/part8_r.tga", ios_base::binary);

	ifstream example8b("examples/EXAMPLE_part8_b.tga", ios_base::binary);
	readImage(example8b);
	test(images[18], blueImage);
	ifstream example8g("examples/EXAMPLE_part8_g.tga", ios_base::binary);
	readImage(example8g);
	test(images[19], greenImage);
	ifstream example8r("examples/EXAMPLE_part8_r.tga", ios_base::binary);
	readImage(example8r);
	test(images[20], redImage);

	writeImage(part8_b, blueImage);
	writeImage(part8_g, greenImage);
	writeImage(part8_r, redImage);
}
void partNine(vector<image>& images) {
	vector<image::pixel> bluePixels = images[2].getPixels();
	vector<image::pixel> greenPixels = images[3].getPixels();
	vector<image::pixel> redPixels = images[4].getPixels();
	vector<image::pixel> finalPixels;

	for (int i = 0; i < 238800; i++) {
		unsigned char blue = bluePixels[i].blueComp;
		unsigned char green = greenPixels[i].greenComp;
		unsigned char red = redPixels[i].redComp;

		finalPixels.push_back(image::pixel(blue, green, red));
	}
	image outImage(images[2].thisHeader, finalPixels);

	ifstream example9("examples/EXAMPLE_part9.tga", ios_base::binary);
	readImage(example9);
	test(images[21], outImage);


	ofstream part9("output/part9.tga", ios_base::binary);
	writeImage(part9, outImage);

}
void partTen(vector<image>& images) {
	vector<image::pixel> imageToRotate = images[10].getPixels();
	vector<image::pixel> imageRotated;

	for (int i = 0; i < 70656; i++) {
		imageRotated.push_back(imageToRotate[70655 - i]);
	}
	image rotatedImage(images[10].thisHeader, imageRotated);

	ifstream example10("examples/EXAMPLE_part10.tga", ios_base::binary);
	readImage(example10);
	test(images[22], rotatedImage);


	ofstream part10("output/part10.tga", ios_base::binary);
	writeImage(part10, rotatedImage);
}

void multiply(vector<image::pixel> topLayer, vector<image::pixel> bottomLayer, vector<image::pixel>& outPixels) {

	for (int i = 0; i < 262144; i++) {
		float _blue = ((((float)topLayer[i].blueComp / 255) * ((float)bottomLayer[i].blueComp / 255)) * 255 + 0.5);
		float _red = ((((float)topLayer[i].redComp / 255) * ((float)bottomLayer[i].redComp / 255)) * 255 + 0.5);
		float _green = ((((float)topLayer[i].greenComp / 255) * ((float)bottomLayer[i].greenComp / 255)) * 255 + 0.5);

		unsigned char blue = (unsigned char)_blue;
		unsigned char red = (unsigned char)_red;
		unsigned char green = (unsigned char)_green;

		outPixels.push_back(image::pixel(blue, green, red));
	}
}
void subtract(vector<image::pixel> topLayer, vector<image::pixel> bottomLayer, vector<image::pixel>& outPixels) {
	for (int i = 0; i < 262144; i++) {
		int _blue = (int)bottomLayer[i].blueComp - (int)topLayer[i].blueComp;
		if (_blue < 0) {
			_blue = 0;
		}
		else if (_blue > 255) {
			_blue = 255;
		}
		int _red = (int)bottomLayer[i].redComp - (int)topLayer[i].redComp;
		if (_red < 0) {
			_red = 0;
		}
		else if (_red > 255) {
			_red = 255;
		}
		int _green = (int)bottomLayer[i].greenComp - (int)topLayer[i].greenComp;
		if (_green < 0) {
			_green = 0;
		}
		else if (_green > 255) {
			_green = 255;
		}

		unsigned char blue = (unsigned char)_blue;
		unsigned char red = (unsigned char)_red;
		unsigned char green = (unsigned char)_green;

		outPixels.push_back(image::pixel(blue, green, red));
	}
}
void test(image image1, image image2) {
	if (image1 == image2) {
		cout << "test passed" << endl;
	}
	else {
		cout << "test failed" << endl;
	}
}