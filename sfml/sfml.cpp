#include "Common.h"

#include "tile.h"
#include "labyrinth.h"
#include "MainMenu.h"

int main(int argc, char** argv) {
    MainMenu menu("Generator Labiryntów", 700, 600, 300);
    menu.run();
    
 
    return EXIT_SUCCESS;
}