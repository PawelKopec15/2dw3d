#pragma once
#include "objectStructure.hpp"
#include "enums.hpp"
#include "physics.hpp"

struct ShapeObject : private Component
{
	Enum<int> shapeType;
	float extrude;
	Enum<int> connectType;
	float connectFactor;

	Enum<int> textureType;
	Vect4<float> texColor;
	Vect3<float> texScale;

	//here add constructors:

	void Awake() override
	{
		Start();
	}


	void Start() override
	{
		//rendering.RebuidRenderQueue();
		return;
	}

};