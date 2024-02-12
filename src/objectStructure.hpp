#pragma once
class Node;
struct Transform;
#include <vector>

//needed for circuar dependency
//struct Transform;

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
protected:
	std::vector<Node> children;
	std::vector<Component> components;
	bool active;
	bool canBeReassigned; //????
	Transform* transform_;
public:
	friend class Scene;
	std::string name;
	Node* parent;
	Transform& transform = *transform_;

public:
	Node();

	virtual Node* GetParent();

	void ForEachChild(void (*func)(Node& child));

	void SetActive();

	void AddComponent();
};
#include "physics.hpp"


	Node::Node() : active(true), transform_(new Transform(this))
	{
        
	}

	Node* Node::GetParent()
	{
		//Pawel smart pointer here!!!!

		return parent;
	}

	void Node::ForEachChild(void (*func)(Node& child))
	{
		for (unsigned int i = 0; i < children.size(); ++i)
		{
			func(children[i]);
		}
	}

	void Node::SetActive()
	{
		//here add / remove from a prefix list in engine parts
	}

	void Node::AddComponent()
	{

	}

/*
//this is practically useless
class SpacialNode : public Node
{

public:
	SpacialNode()
	{
		//transform = Transform(this);
	}
};
*/