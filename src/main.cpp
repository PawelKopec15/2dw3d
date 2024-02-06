#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>

#include "engine.hpp"
#include "rendering.hpp"
//#include "physics.hpp"
#include "objectStructure.hpp"
#include "scene.hpp"

std::vector<Engine*> engine;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "CMake SFML Project");
    window.setFramerateLimit(144);

    //ENGINE INITIALIZATION
    engine.push_back(&scene);
    //engine.push_back(&rendering);
    //typedef void (*engineObjectFunc)(Node&);
    //engineObjectFunc objectFunc[1] = { PerObjectUpdate };

    //GAME START
    for (unsigned int i = 0; i < engine.size(); ++i)
    {
        engine[i]->OnGameStart();
    }

    //GAME LOOP
    while (window.isOpen())
    {
        /*
        //engine[i]->OnObjectUpdate();
        scene.ScanAllObjects(objectFunc, 1);
        for (unsigned int i = 0; i < engine.size(); ++i)
        {
            engine[i]->OnGameUpdate();
        }
        */

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }

    //propably shouldn't be here
    for (unsigned int i = 0; i < engine.size(); ++i)
    {
        engine[i]->OnGameExit();
    }
}