#include <cmath>
#include "tgaimage.h"

constexpr TGAColor white   = {255, 255, 255, 255}; // BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};

void lineSegment(int ax, int bx, int ay, int by, TGAImage &framebuffer, TGAColor color) {
	//Drawing line pixel by pixel (t is the slope)
	for (float t = 0.; t <= 1.; t += 0.02) {
		int xt = std::round(ax + t * (bx - ax));
		int yt = std::round(ay + t * (by - ay));
		framebuffer.set(xt, yt, color);
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

	lineSegment(ax, bx, ay, by, framebuffer, green);
	lineSegment(bx, cx, by, cy, framebuffer, blue);
	lineSegment(cx, ax, cy, ay, framebuffer, yellow);

	//Saving the frame
	framebuffer.write_tga_file("framebuffer.tga");
	return 0;
}

