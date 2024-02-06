#pragma once
#include <vector>
#include <sstream>
#include <fstream>
#include "shapes.hpp"
#include "engine.hpp"

class Rendering : private Engine
{
private:
    std::vector<ShapeObject> renderQueue;

    //also basic shaders for that:
    const char* screenVertexShaderSource = R"(#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uvs;
out vec2 UVs;
void main()
{
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
	UVs = uvs;
})";
    const char* screenFragmentShaderSource = R"(#version 460 core
out vec4 FragColor;
uniform sampler2D screen;
in vec2 UVs;
void main()
{
	FragColor = texture(screen, UVs);
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
            //special overload for inputing custom fractals
            //it comes before main and shapesManager to be able to use other dependencies
            if (i == filepaths.size() - 3)
            {
                //carefully place function for custom shape so it does not breaks the program
                std::ifstream file(filepaths[i]);
                std::string line;
                while (std::getline(file, line))
                {
                    program << line << '\n';
                }
            }
            else
            {
                //join each file
                std::ifstream file(filepaths[i]);
                std::string line;
                while (std::getline(file, line))
                {
                    program << line << '\n';
                }
            }

        }

        return program.str();
    }

    private:
        void OnGameStart() override
        {
            const unsigned int sizeX = 1280;
            const unsigned int sizeY = 720;

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
        }

        void OnGameUpdate() override
        {

        }
};

Rendering rendering;