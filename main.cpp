#include <cmath>
#include "tgaimage.h"

constexpr TGAColor white   = {255, 255, 255, 255}; // BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};

void lineSegment(int ax, int ay, int bx, int by, TGAImage &framebuffer, TGAColor color) {

	//Swapping if the line is more vertical than horizontal
	bool moreVertical = std::abs(ax - bx) < std::abs(ay - by);
	if (moreVertical){
		std::swap(ax, ay);
		std::swap(bx, by);
	}

	//Swapping in case first point is further right than second one
	if (ax > bx) {
		std::swap(ax, bx);
		std::swap(ay, by);
	}


	/* Drawing line pixel by pixel
	   Making it as a function of x to account for amount of pixels needed
	   at different lengths */

	int yt = ay;
	float error = 0; 

	for (int xt = ax; xt <= bx; xt++) {
		if (moreVertical) framebuffer.set(yt, xt, color);

		else framebuffer.set(xt, yt, color);

		error += std::abs((by - ay)/static_cast<float>(bx - ax));
		if (error > 0.5) {
			yt += by > ay ? 1 : 1;
			error--;
		}
	}
}


int main(int argc, char** argv) {
	//Making frame
	constexpr int width  = 64;
	constexpr int height = 64;
	TGAImage framebuffer(width, height, TGAImage::RGB);

	//Drawing points
	int ax =  7, ay =  3;
	int bx = 12, by = 37;
	int cx = 62, cy = 53;

	framebuffer.set(ax, ay, white);
	framebuffer.set(bx, by, white);
	framebuffer.set(cx, cy, white);

	lineSegment(ax, ay, bx, by, framebuffer, green);
	lineSegment(bx, by, cx, cy, framebuffer, blue);
	lineSegment(cx, cy, ax, ay, framebuffer, yellow);
	lineSegment(ax, ay, cx, cy, framebuffer, red);

	//Saving the frame
	framebuffer.write_tga_file("framebuffer.tga");
	return 0;
}

