#pragma once
#include "vectors.hpp"
#include <vector>

//FORWARD DECLARATIONS
class Node;
class SpacialNode;
struct TransVect3;
struct Transform;

//TRANS VECT DECLARATION
//special vector for transform
//the only existance of it is to maintain nice transform edition
//while correctly synchronizing transforms
struct TransVect3
{
	//this trick makes a "read only" public variable:
private:
	Transform* transform;
	int synchId;
	float x_;
	float y_;
	float z_;

public:
	const float& x = x_;
	const float& y = y_;
	const float& z = z_;

	TransVect3();

	TransVect3(int id);

	TransVect3(Vect3<float> vect);

	TransVect3(Vect3<float> vect, int id);

	TransVect3(float x, float y, float z);

	TransVect3(float x, float y, float z, int id);

	//synch triggers
	TransVect3& operator=(Vect3<float>& other);

	TransVect3& operator=(Vect3<float>&& other);

	TransVect3& operator=(TransVect3& other);

	//ummm I just want to keep it for now
	TransVect3& operator=(TransVect3&& other);

	//well unfortunately we have to rewrite everything as for vect3

	//we also converts transVect into regular vect for all r values
	//(because we do not need "secured" vector in vetor expressions)
	Vect3<float> operator+(Vect3<float>& other);

	Vect3<float> operator-(Vect3<float>& other);

	Vect3<float> operator-(Vect3<float>&& other);

	Vect3<float> operator-(TransVect3& other);

	Vect3<float> operator*(Vect3<float>& other);

	Vect3<float> operator*(float& other);

	Vect3<float> operator*(float&& other);

	Vect3<float> operator/(float& other);

	Vect3<float> operator/(float&& other);

	Vect3<float> operator%(float& other);

	Vect3<float> operator%(float&& other);

	//subscpription operators:
	TransVect3& operator+=(Vect3<float>&& other);

	TransVect3& operator-=(Vect3<float>&& other);

	TransVect3& operator*=(Vect3<float>&& other);

	TransVect3& operator/=(Vect3<float>&& other);

	TransVect3& operator%=(Vect3<float>&& other);

	bool operator==(Vect3<float>&& other);
};

//TRANSFORM DECLARATION
//contains only 3d coordinates as 2d objects are placed in 3d space
struct Transform
{
	friend struct TransVect3; //allows to change transform while not synching internally
	SpacialNode* node;
	TransVect3 position;
	TransVect3 rotation;
	TransVect3 globalScale;

	TransVect3 localPosition;
	TransVect3 localRotation;
	TransVect3 scale; //usually when devs change scale they mean local scale

	//for 2d manipulation
	Vect2 <float> flatPosition;

	Transform(SpacialNode* node);

	//synchronization
	void SynchPassive(SpacialNode* syncher);
	void SynchActive(int changeType);
};

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

//NODE DECLARATION
class Node
{
protected:
	std::vector<Node> children;
	std::vector<Component> components;
	bool active;
public:
	friend class Scene;
	std::string name;
	Node* parent;

public:
	Node();

	virtual SpacialNode* ToSpacial();

	SpacialNode* GetSpacialParent();

	void ForEachChild(void (*func)(Node& child));

	void SetActive();

	void AddComponent();
};

//SPACIAL NODE DECLARATION
//the only diffrence is that it contains transform
class SpacialNode : public Node
{
protected:
	Transform transform_;
public:
	//TRANSFORM ASSIGNING IS NOT SUPPORTED!!!
	Transform& const transform = transform_;
public:
	SpacialNode();

	SpacialNode* ToSpacial() override;
};