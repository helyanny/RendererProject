#include <cmath>
#include "tgaimage.h"
#include "geometry.h"
#include "model.h"
#include <tuple>
#include <iostream>
#include <utility>

constexpr TGAColor white   = {255, 255, 255, 255}; // BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};

constexpr int width = 720;
constexpr int height = 720;

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
	int error = 0; 

	for (int xt = ax; xt <= bx; xt++) {
		if (moreVertical) framebuffer.set(yt, xt, color);

		else framebuffer.set(xt, yt, color);

		/* Error for increments of y
		   Since loop is defaulted for lines that are not too steep, y increments
		   don't naturally exceed 1 pixel */

		error += 2 * std::abs(by - ay);
		if (error > (bx - ax)) {
			yt += by > ay ? 1 : -1;
			error -= 2 * (bx - ax);
		}
	}
}

std::tuple<int, int> wireframes(vec3 vector) {
	return { width / 2 * (vector.x + 1.0), height / 2 * (vector.y + 1.0)};
}

int main(int argc, char** argv) {

	if (argc != 2) {
		std::cerr << "Please run the program along with a model object" << std::endl;
		return 1;
	}


	//Making frame and inserting points from image
	Model model(argv[1]);
	TGAImage framebuffer(width, height, TGAImage::RGB);

	for (int i = 0; i < model.nfaces(); i++) {
		auto [ax, ay] = wireframes(model.vert(i, 0));
		auto [bx, by] = wireframes(model.vert(i, 1));
		auto [cx, cy] = wireframes(model.vert(i, 2));
	
		lineSegment(ax, ay, bx, by, framebuffer, blue);
		lineSegment(bx, by, cx, cy, framebuffer, blue);
		lineSegment(cx, cy, ax, ay, framebuffer, blue);
	}

	for (int i = 0; i < model.nfaces(); i++) {
		vec3 vertice = model.vert(i);
		auto [x, y] = wireframes(vertice);
		framebuffer.set(x, y, white);
	}

	//Saving the frame
	framebuffer.write_tga_file("framebuffer.tga");
	return 0;
}

