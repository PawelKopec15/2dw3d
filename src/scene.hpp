#pragma once
#include <iostream>
#include "engine.hpp"
#include "objectStructure.hpp"

class Scene : public Engine
{
public:
    friend int main();

private:
	Node* root;
    SpacialNode* mainCamera;
    Node* player;
    std::vector<Singleton> singletons; //unused

private:

    void OnGameStart() override
    {
        //root = new Node();
        //root->name = "root";
    }

    void OnGameObject(Node& node) override
    {
        std::cout << node.name << std::endl;
        for (unsigned int i = 0; i < node.components.size(); ++i)
        {
            node.components[i].Update();
        }
    }

    void OnGameExit() override
    {
        delete root;
    }

public:
    void ScanAllObjects(void (*function)(Node&))
    {
        function(*root);
        for (int i = 0; i < root->children.size(); ++i)
        {
            ScanAllObjects(root->children[i], function);
        }
    }

    void ScanAllObjects(Node& piviot, void (*function)(Node&))
    {
        function(piviot);
        for (int i = 0; i < piviot.children.size(); ++i)
        {
            ScanAllObjects(piviot.children[i], function);
        }
    }

    void ScanAllObjects(void (**function)(Node&), int fnums)
    {
        for (int j = 0; j < fnums; ++j)
        {
            function[j](*root);
        }
        for (int i = 0; i < root->children.size(); ++i)
        {
            ScanAllObjects(root->children[i], function, fnums);
        }
    }

    void ScanAllObjects(Node& piviot, void (**function)(Node&), int fnums)
    {
        for (int j = 0; j < fnums; ++j)
        {
            function[j](piviot);
        }
        for (int i = 0; i < piviot.children.size(); ++i)
        {
            ScanAllObjects(root->children[i], function, fnums);
        }
    }

    //getters:
    SpacialNode& GetMainCamera()
    {
        return *mainCamera;
    }

    Node& GetPlayer()
    {
        return *player;
    }
};

Scene scene;