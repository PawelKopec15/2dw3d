#pragma once
#include "objectStructure.hpp"

//unused
class Singleton
{
	virtual void Build()
	{

	}

	virtual void Update()
	{

	}
};

class Engine
{
public:
	friend int main(); //main deals with engine
    friend void PerObjectUpdate(Node& node);
	friend class Node; //engine has access to objects

private:
	//called at the start of the game
	virtual void OnGameStart()
	{
        //std::cout << "wrong start" << std::endl;
	}

	//called on every object each frame
	virtual void OnGameObject(Node& node)
	{

	}

	//called on every frame (but only once) //goes after OnGameObject()
	virtual void OnGameUpdate()
	{

	}

	//called just before exiting application
	virtual void OnGameExit()
	{

	}
};

//global engine and singletons access for objects
//std::vector<Engine> engine;
//std::vector<Singleton> singletons;