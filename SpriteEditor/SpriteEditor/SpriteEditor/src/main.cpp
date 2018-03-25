#include <string>
#include "../include/SpriteEditor.h"
#include "../include/ResourceManager.h"

int main() {
	SpriteEditor* spriteEditor = new SpriteEditor();
	spriteEditor->init();
	spriteEditor->run();

	spriteEditor->cleanUp();
	ResourceManager::instance().cleanUp();
	delete spriteEditor;
	
	return 0;
}
