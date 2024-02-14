#pragma once
#include "objectStructureDeclarations.hpp"

//TRANS VECT DEFINITION
	TransVect3::TransVect3() : x_(0), y_(0), z_(0)
	{

	}

	TransVect3::TransVect3(int id) : synchId(id), x_(0), y_(0), z_(0)
	{

	}

	TransVect3::TransVect3(Vect3<float> vect) : x_(vect.x), y_(vect.y), z_(vect.z)
	{

	}

	TransVect3::TransVect3(Vect3<float> vect, int id) : synchId(id), x_(vect.x), y_(vect.y), z_(vect.z)
	{

	}

	TransVect3::TransVect3(float x, float y, float z) : x_(x), y_(y), z_(z)
	{

	}

	TransVect3::TransVect3(float x, float y, float z, int id) : synchId(id), x_(x), y_(y), z_(z)
	{

	}

	//synch triggers
	TransVect3& TransVect3::operator=(Vect3<float>& other)
	{
		transform->SynchActive(synchId);
		x_ = other.x;
		y_ = other.y;
		z_ = other.z;
		return *this;
	}

	TransVect3& TransVect3::operator=(Vect3<float>&& other)
	{
		std::cout << "= overloaded" << std::endl;
		x_ = other.x;
		y_ = other.y;
		z_ = other.z;
		return *this;
	}

	TransVect3& TransVect3::operator=(TransVect3& other)
	{
		std::cout << "= overloaded" << std::endl;
		x_ = other.x;
		y_ = other.y;
		z_ = other.z;
		return *this;
	}

	//ummm I just want to keep it for now
	TransVect3& TransVect3::operator=(TransVect3&& other)
	{
		std::cout << "= overloaded" << std::endl;
		x_ = other.x;
		y_ = other.y;
		z_ = other.z;
		return *this;
	}

	//well unfortunately we have to rewrite everything as for vect3

	//we also converts transVect into regular vect for all r values
	//(because we do not need "secured" vector in vetor expressions)
	Vect3<float> TransVect3::operator+(Vect3<float>& other)
	{
		return Vect3<float>(other.x + x_, other.y + y_, other.z + z_);
	}

	Vect3<float> TransVect3::operator-(Vect3<float>& other)
	{
		return Vect3<float>(other.x - x_, other.y - y_, other.z - z_);
	}

	Vect3<float> TransVect3::operator-(Vect3<float>&& other)
	{
		return Vect3<float>(x_ - other.x, y_ - other.y, z_ - other.z);
	}

	Vect3<float> TransVect3::operator-(TransVect3& other)
	{
		return Vect3<float>(x_ - other.x, y_ - other.y, z_ - other.z);
	}

	Vect3<float> TransVect3::operator*(Vect3<float>& other)
	{
		return Vect3<float>(other.x * x_, other.y * y_, other.z * z_);
	}

	Vect3<float> TransVect3::operator*(float& other)
	{
		return Vect3<float>(other * x_, other * y_, other * z_);
	}

	Vect3<float> TransVect3::operator*(float&& other)
	{
		return Vect3<float>(x_ * other, y_ * other, z_ * other);
	}

	Vect3<float> TransVect3::operator/(float& other)
	{
		return Vect3<float>(other / x_, other / y_, other / z_);
	}

	Vect3<float> TransVect3::operator/(float&& other)
	{
		return Vect3<float>(x_ / other, y_ / other, z_ / other);
	}

	Vect3<float> TransVect3::operator%(float& other)
	{
		return Vect3<float>(fmod(other, x_), fmod(other, y_), fmod(other, z_));
	}

	Vect3<float> TransVect3::operator%(float&& other)
	{
		return Vect3<float>(fmod(x_, other), fmod(y_, other), fmod(z_, other));
	}

	//subscpription operators:
	TransVect3& TransVect3::operator+=(Vect3<float>&& other)
	{
		x_ = x_ + other.x;
		y_ = y_ + other.y;
		z_ = z_ + other.z;
		return *this;
	}

	TransVect3& TransVect3::operator-=(Vect3<float>&& other)
	{
		x_ = x_ - other.x;
		y_ = y_ - other.y;
		z_ = z_ - other.z;
		return *this;
	}

	TransVect3& TransVect3::operator*=(Vect3<float>&& other)
	{
		x_ = x_ * other.x;
		y_ = y_ * other.y;
		z_ = z_ * other.z;
		return *this;
	}

	TransVect3& TransVect3::operator/=(Vect3<float>&& other)
	{
		x_ = x_ / other.x;
		y_ = y_ / other.y;
		z_ = z_ / other.z;
		return *this;
	}

	TransVect3& TransVect3::operator%=(Vect3<float>&& other)
	{
		x_ = fmod(x_, other.x);
		y_ = fmod(y_, other.x);
		z_ = fmod(z_, other.x);
		return *this;
	}

	bool TransVect3::operator==(Vect3<float>&& other)
	{
		return (x_ == other.x && y_ == other.y && z_ == other.z);
	}


//TRANSFORM DEFINITION

	Transform::Transform(SpacialNode* node) : node(node), position(1), rotation(2), globalScale(3), localPosition(4), localRotation(5), scale(1, 1, 1, 6)
	{
		//maybe, will be checked later
		SpacialNode* synchingParent = node->GetSpacialParent();
		if (synchingParent != nullptr)
		{
			SynchPassive(synchingParent);
		}
	}

	//synchs all globals, but not locals
	//usually called when not changed directly, but still requires synching
	void Transform::SynchPassive(SpacialNode* node)
	{
		//position = 
	}

	void Transform::SynchActive(int changeType)
	{
		if (changeType == 0) //position
		{
			//*
			Node* parent = node->parent;
			//Node* parent = node->parent;
			//parent synch
			if (!(parent == nullptr))
			{
				//localPosition = position - parent->transform.position;
			}
			else
			{
				localPosition = position;
			}
		}
		else if (changeType == 1) //rotation
		{

		}
		else if (changeType == 2) //scale (global)
		{

		}
		else if (changeType == 3) //local pos
		{

		}
		else if (changeType == 3) //local rot
		{

		}
		else if (changeType == 3) //local scale
		{

		}
		else if (changeType == 3) //2d pos
		{

		}
	}

//NODE DEFINITION

	Node::Node() : active(true)
	{
        
	}

	SpacialNode* Node::ToSpacial()
	{
		return nullptr;
	}

	//gets to the first suitable spacial parent
	SpacialNode* Node::GetSpacialParent()
	{
		Node* midParent = parent;
		SpacialNode* res;
		while (midParent != nullptr)
		{
			res = midParent->ToSpacial();
			if (res != nullptr)
			{
				return res;
			}
		}
		//no spacial parent
		return nullptr;
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

//SPACIAL NODE DEFINITION
	SpacialNode::SpacialNode() : transform_(this)
	{
		active = true;
	}

	SpacialNode* SpacialNode::ToSpacial()
	{
		return this;
	}