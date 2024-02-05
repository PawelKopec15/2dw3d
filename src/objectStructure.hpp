#pragma once
#include <vector>
//#include "Physics.hpp"

template <typename nodeType>
class Component
{
public:
    friend class Scene;

private:
    bool active;

public:
    nodeType* node;

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
    void Build()
    {

    }

    //called every time the object is created
    void Awake()
    {

    }

    // on enabling object
    void Start()
    {

    }

    //on disabling object
    void Sleep()
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
protected:
	std::vector<Node> children;
	std::vector<Component<Node>> components;
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

    /*
	SpacialNode& ToSpacial()
	{
		return nullptr;
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

class Node3D : public SpacialNode
{
protected:
	Vector3<float> pos;
	Vector3<float> rot;
	Vector3<float> scale;

	Vector3<float> lpos;
	Vector3<float> lrot;
	Vector3<float> lscale;

	void Synchronize()
	{
		Node* par = GetParent();
		while (par == nullptr) //skip all parents that aren't spacial
		{
			par = par->ToSpacial();
		}
		//actualSynch
		
		//synch children
		for (int i = 0; i < children.size(); ++i)
		{
			children[i].Synchronize();
		}

		isSynched = true;
	}
};

class Node25D : public SpacialNode
{
protected:
	Vector2<float> lpos;
	Vector2<float> lrot; //y and z
	Vector2<float> lscale;
};

class Node2D : private SpacialNode
{
protected:
	Vector2<float> lpos;
	float lrot; //only z
	Vector2<float> lscale;
};

/*
class Node2.5D : private Node2D
{
	convTo3D
};
*/

/*
Update()
{
	//daj mi obiekt

	//
	//
	//
	private bool IamEngine
		opreator =
	{
		if (IamEngine)
		{

		}
	}
public:
	operator =

protected:
		operator =
}
*/