#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "shapes.hpp"
#include "engine.hpp"

class Rendering : public Engine
{
public:
    friend int main(); //need to find a way to not copy this to every "engine" object

private:
    std::vector<ShapeObject> renderQueue;
    Vect2<int> resolution;
    sf::Window mainWindow;
    sf::Shader mainRenderer;

    //template shaders for covering entire screen
    const std::string screenVertexShaderSource = R"(
        attribute vec3 vertexPosition_modelspace;

    void main()
    {
        gl_Position = vec4(vertexPosition_modelspace, 1.0);
    })";

    const std::string screenFragmentShaderSource = R"(
        uniform vec2 iResolution;

    void main()
    {
        vec2 uv = gl_FragCoord.xy / iResolution.xy;

        vec4 col = vec4(uv.x, uv.y, 1.0, 1.0);

        gl_FragColor = col;
    })";
    

    //-------------------------------------
    //this load multi-filed shader program
    //actually it is in fact single filed shader
    //that is just simply joined from several files
    static const std::string ParseShaderProject(std::vector<std::string> filepaths)
    {
        std::stringstream program;
        for (int i = 0; i < filepaths.size(); ++i)
        {
            //join each file
            std::ifstream file(filepaths[i]);
            std::string line;
            while (std::getline(file, line))
            {
                program << line << '\n';
            }
        }

        return program.str();
    }

    private:
        void OnGameStart() override
        {
            resolution.x = 1280;
            resolution.y = 720;

            //scene initialization
            //List<ShapeObject<GLfloat>> mainScene;

            //loading shader from file:
            //"shaders/customShape.glsl",
            std::vector<std::string> projectFiles = {
                /*"shaders/uniforms.glsl",
                "shaders/calculations.glsl",
                "shaders/shapes.glsl",
                "shaders/connections.glsl",
                "shaders/repeatings.glsl",
                "shaders/textures.glsl",
                "customShape.glsl",
                "shaders/shapesManager.glsl",*/
                "shaders/main.glsl"
            };

            std::string shaderSource = ParseShaderProject(projectFiles);
            
            if (!sf::Shader::isAvailable())
            {
                std::cout << "Main shader not available."  << std::endl;
                exit(EXIT_FAILURE);
            }

            if (!mainRenderer.loadFromMemory(screenVertexShaderSource, screenFragmentShaderSource))
            {
                std::cout << "Failed to load main shader." << std::endl;
                exit(EXIT_FAILURE);
            }

            //one off serialize
            mainRenderer.setUniform("iResolution", sf::Vector2f((float)resolution.x, (float)resolution.y));
            //mainRenderer.setParameter("iResolution", sf::Vector2f((float)resolution.x, (float)resolution.y));
            sf::Shader::bind(&mainRenderer);
        }

        void OnGameUpdate() override
        {
            //here render whole scene
            float ratio = resolution.x / resolution.y;

            sf::Vector2f res(resolution.x, resolution.y);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            glOrtho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glPushMatrix();
            glBegin(GL_QUADS);
            glNormal3f(0.0, 0.0, 1.0);
            glVertex3f(-1.0f, -1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 0.0f);
            glVertex3f(1.0f, 1.0f, 0.0f);
            glVertex3f(-1.0f, 1.0f, 0.0f);
            glEnd();
            glPopMatrix();
        }
};

Rendering rendering;