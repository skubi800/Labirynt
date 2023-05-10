#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <thread>

#include "maze.h"
#include "tile.h"
#include "labyrinth.h"

int main(int argc, char** argv) {
   // 10 10 60 6
    
    unsigned int height = 60;
    unsigned int width = 60;
    unsigned int resolution = 10;
    unsigned int borderSize = 1;

    unsigned int totalWidth = width * resolution + (width + 1) * borderSize;
    unsigned int totalHeight = height * resolution + (height + 1) * borderSize;

    //optymalizacja rozmiarow

    sf::RenderWindow window(sf::VideoMode(totalWidth, totalHeight), "Labirynt");

 //   window.setVerticalSyncEnabled(true);

    Labyrinth* testowy = new Labyrinth(window, height, width, resolution, borderSize);
 
    testowy->draw();
    window.display();

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::Resized) {
                window.clear();
                testowy->draw();
                window.display();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                window.clear();
                testowy->primsAlgorithm();
                testowy->draw();
                window.display();
            }
          /*  else if (event.type == sf::Event::MouseMoved) {
                window.clear();
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                testowy->changeColor(pos);
                testowy->draw();
                window.display();                
            }
            */
        }   
     //   std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
    }

    return EXIT_SUCCESS;
}