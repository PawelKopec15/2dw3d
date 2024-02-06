#pragma once
#include <vector>
#include "physics.hpp"

class Node; //needed for circuar dependency

class Component
{
public:
    friend class Scene;

private:
    bool active;

public:
    Node* node;

public:
    void SetActive(bool newState)
    {
        if (active == newState)
        {
            return;
        }
        if (active)
        {
            active = false;
            Sleep();
            return;
        }
        else
        {
            active = true;
            Start();
            return;
        }
    }

private:
    //called upon building/rebuilding a scene
    virtual void Build()
    {

    }

    //called every time the object is created
    virtual void Awake()
    {

    }

    // on enabling object
    virtual void Start()
    {

    }

    //on disabling object
    virtual void Sleep()
    {

    }

    //called every frame
    void Update()
    {

    }
};

class Node
{
public:
	friend class Scene;
	std::string name;
	Transform<float> transform; //make it inchangable in future
protected:
	std::vector<Node> children;
	std::vector<Component> components;
	Node* parent;
	bool active;
	bool isSynched;
	bool canBeReassigned;

public:
    Node(bool canBeReassigned = false) : canBeReassigned(canBeReassigned)
    {

    }

    /*
	Node(): children(std::vector<Node>()), components(std::vector<Component<Node>>()), parent(nullptr), active(true), isSynched(true)
	{
		
	}
    */

	virtual Node GetParent()
	{
		return *parent;
	}

	void ForEachChild(void (*func)(Node& child))
	{
		for (unsigned int i = 0; i < children.size(); ++i)
		{
			func(children[i]);
		}
	}

	virtual void Synchronize()
	{
		/*
		if (isSynched == true)
		{
			return;
		}
		*/
		if (parent->isSynched == false)
		{
			parent->Synchronize();
		}
		//here comes actual synch in spacial

		//isSynched = true;
		//node by itself is never synched
		/*
		for (int i = 0; i < children.size(); ++i)
		{
			children[i].Synchronize();
		}
		*/
	}

	void SetActive()
	{
		//here add / remove from a prefix list in engine parts
	}

	void AddComponent()
	{

	}
};

class Node3d : public Node
{
public:
	Node3d()
	{
		transform = Transform<float>();
	}
};

class Node25d : public Node3d
{
public:
	Node25d()
	{
		transform = Transform<float>();
	}
};

/*
class SpacialNode : public Node
{

	void Synchronize()
	{
		if (isSynched == true)
		{
			return;
		}
		if (parent->isSynched == false)
		{
			parent->Synchronize();
		}
		//here comes actual synch in spacial

		isSynched = true;
	}
};
*/