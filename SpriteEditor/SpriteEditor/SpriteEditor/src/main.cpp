#include <string>

#undef main

#include "../include/SpriteEditor.h"

int main() {

	// Load an image

	//A simplisitic sprite editor may be a terminal based tool that loads an image, 
	// asks you the dimensions of a sprite, and then which frames to play. 
	//This is considered an acceptable version of a tile editor for this assignment.
	
	std::cout << "What is the name of the sprite sheet PNG file you wish to preview?" << std::endl;
	std::string file;
	std::cin >> file;

	std::cout << "What is the width of your sprite?" << std::endl;
	int w;
	std::cin >> w;

	std::cout << "What is the height of your sprite?" << std::endl;
	int h;
	std::cin >> h;

	std::cout << "What is the number of columns in your sprite sheet?" << std::endl;
	int columns;
	std::cin >> columns;
	
	std::cout << "What is the number of frames in your sprite's animation cycle?" << std::endl;
	int frames;
	std::cin >> frames;

	std::cout << "Desired framerate (30 or 60 reccomended)" << std::endl;
	int frameRate;
	std::cin >> frameRate;

	SpriteEditor* spriteEditor = new SpriteEditor(file, w, h, frames, columns, frameRate);
	spriteEditor->play();

	//SpriteEditor* spriteEditor = new SpriteEditor(20, 30, 3);
	//spriteEditor->play();
	
	return 0;
}
