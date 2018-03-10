#include <string>

#undef main

#include "../include/SpriteEditor.h"

int main() {

	// Load an image

	//A simplisitic sprite editor may be a terminal based tool that loads an image, 
	// asks you the dimensions of a sprite, and then which frames to play. 
	//This is considered an acceptable version of a tile editor for this assignment.
	
	std::cout << "What is the width of your sprite?" << std::endl;
	int w;
	std::cin >> w;

	std::cout << "What is the height of your sprite?" << std::endl;
	int h;
	std::cin >> h;

	std::cout << "What is the number of frames in your sprite's animation cycle?" << std::endl;
	int f;
	std::cin >> f;

	SpriteEditor* spriteEditor = new SpriteEditor(w, h, f);
	spriteEditor->play();

	//SpriteEditor* spriteEditor = new SpriteEditor(20, 30, 3);
	//spriteEditor->play();
	
	return 0;
}
