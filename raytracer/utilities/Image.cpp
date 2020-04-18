//#include "stdafx.h"
#include "Image.hpp"
#include "RGBColor.hpp"
#include "./../world/ViewPlane.hpp"
#include <fstream>

#include <iostream>



// Constructors.
Image::Image(int hres, int vres): hres(hres), vres(vres)
{
	colors = new RGBColor*[hres];
	for (int i = 0; i < hres; i++) {
		colors[i] = new RGBColor[vres];
	}
}
	
Image::Image(const ViewPlane &vp) : hres(vp.hres), vres(vp.vres)
{
	colors = new RGBColor*[hres];
	for (int i = 0; i < hres; i++) {
		colors[i] = new RGBColor[vres];
	}
}

// Destructor.
Image::~Image() {
	for (int i = 0; i < hres; i++) {
		delete colors[i];
	}
	delete colors;
}

// Set pixel color. Convert to integer values.
void Image::set_pixel(int x, int y, const RGBColor& color) {
	try {
		if (x<0 || x>hres-1) {
			throw x;
		}
		else if (y<0 || y>vres-1) {
			throw y;
		}
		else {
			colors[x][y] = color;
		}
	}
	catch (...) {
		std::cout << "1 or both axis out of range while setting pixel" << std::endl;
	}
}

void Image::write_ppm(std::string path) const
{
	std::ofstream img(path);
	img << "P3" << std::endl;
	img << hres << " " << vres << " "<< std::endl;
	img << "255" << std::endl;
	
	for (int y = 0; y < vres; y++) {
		for (int x = 0; x < hres; x++) {
			auto col = colors[x][y];
			img << (int)(col.r * 255) << " " << (int)(col.g * 255) << " " << (int)(col.b * 255) << std::endl;
		}
	}

}//citing: www.youtube.com/watch?v=fbH005SzEMc
