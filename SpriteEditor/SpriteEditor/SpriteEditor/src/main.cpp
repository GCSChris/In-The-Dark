#include <string>

#undef main

#include "../include/SpriteEditor.h"


int main() {

	// Load an image

	//A simplisitic sprite editor may be a terminal based tool that loads an image, 
	// asks you the dimensions of a sprite, and then which frames to play. 
	//This is considered an acceptable version of a tile editor for this assignment.
	
	SpriteEditor* spriteEditor = new SpriteEditor();
	spriteEditor->init();

	printf("hello\n");
	
	return 0;
}
