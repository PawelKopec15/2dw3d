#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "engine.hpp"
#include "rendering.hpp"
//#include "physics.hpp"
#include "objectStructure.hpp"
#include "scene.hpp"

std::vector<Engine*> engine;

int main()
{
    //not full screen for debugging
    sf::Window window(sf::VideoMode(800, 600), "CMake SFML Project");
    window.setFramerateLimit(144);
    //window.resetGLStates();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //ENGINE INITIALIZATION
    //engine.push_back(&scene);
    engine.push_back(&rendering);

    //Initializing player (just for now)
    rendering.resolution = Vect2<int>(800, 600);
    scene.player = new SpacialNode();
    scene.mainCamera = scene.player;
    scene.GetMainCamera().transform.position = Vect3<float>(0, 0, 0);
    scene.GetMainCamera().transform.rotation = Vect3<float>(30, 0, 0);
    scene.GetMainCamera().transform.scale = Vect3<float>(5, 4, 0);

    sf::Clock clock;
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

        //GAME UPDATE
        for (unsigned int i = 0; i < engine.size(); ++i)
        {
            engine[i]->OnGameUpdate();
        }

        //window.clear(); //we don't have to clear as main renderer clears anyway
        window.display();
    }

    //propably shouldn't be here
    for (unsigned int i = 0; i < engine.size(); ++i)
    {
        engine[i]->OnGameExit();
    }
}