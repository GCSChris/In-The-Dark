#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "../include/TileEditor.h"
#include "../include/Parser.h"
#include "../include/Level.h"
#include "../include/Constants.h"
#include <iostream>

int main() {
	
	TileEditor* te = new TileEditor();

	te->init();

	te->play();

	delete te;
}
