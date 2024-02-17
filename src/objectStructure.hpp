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

	//conversion
	TransVect3::operator Vect3<float>()
	{
		return Vect3<float>(x_, y_, z_);
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
		transform->SynchActive(synchId);
		x_ = other.x;
		y_ = other.y;
		z_ = other.z;
		return *this;
	}

	TransVect3& TransVect3::operator=(TransVect3& other)
	{
		transform->SynchActive(synchId);
		x_ = other.x;
		y_ = other.y;
		z_ = other.z;
		return *this;
	}

	//ummm I just want to keep it for now
	TransVect3& TransVect3::operator=(TransVect3&& other)
	{
		x_ = other.x;
		y_ = other.y;
		z_ = other.z;
		transform->SynchActive(synchId);
		return *this;
	}

	//well unfortunately we have to rewrite everything as for vect3

	//we also converts transVect into regular vect for all r values
	//(because we do not need "secured" vector in vetor expressions)
	Vect3<float> TransVect3::operator+(Vect3<float> other)
	{
		return Vect3<float>(x_ + other.x, y_ + other.y, z_ + other.z);
	}

	Vect3<float> TransVect3::operator-(Vect3<float> other)
	{
		return Vect3<float>(x_ - other.x, y_ - other.y, z_ - other.z);
	}

	Vect3<float> TransVect3::operator-()
	{
		return Vect3<float>(-x_, -y_, -z_);
	}

	Vect3<float> TransVect3::operator*(Vect3<float> other)
	{
		return Vect3<float>(x_ * other.x, y_ * other.y, z_ * other.z);
	}

	Vect3<float> TransVect3::operator*(float& other)
	{
		return Vect3<float>(x_ * other, y_ * other, z_ * other);
	}

	Vect3<float> TransVect3::operator/(Vect3<float> other)
	{
		return Vect3<float>(x_ / other.x, y_ / other.y, z_ / other.z);
	}

	Vect3<float> TransVect3::operator/(float& other)
	{
		return Vect3<float>(x_ / other, y_ / other, z_ / other);
	}

	Vect3<float> TransVect3::operator%(Vect3<float> other)
	{
		return Vect3<float>(fmod(x_, other.x), fmod(y_, other.y), fmod(z_, other.z));
	}

	Vect3<float> TransVect3::operator%(float& other)
	{
		return Vect3<float>(fmod(x_, other), fmod(y_, other), fmod(z_, other));
	}

	//subscpription operators:
	TransVect3& TransVect3::operator+=(Vect3<float>&& other)
	{
		x_ += other.x;
		y_ += other.y;
		z_ += other.z;
		transform->SynchActive(synchId);
		return *this;
	}

	TransVect3& TransVect3::operator-=(Vect3<float>&& other)
	{
		x_ -= other.x;
		y_ -= other.y;
		z_ -= other.z;
		transform->SynchActive(synchId);
		return *this;
	}

	TransVect3& TransVect3::operator*=(Vect3<float>&& other)
	{
		x_ *= other.x;
		y_ *= other.y;
		z_ *= other.z;
		transform->SynchActive(synchId);
		return *this;
	}

	TransVect3& TransVect3::operator/=(Vect3<float>&& other)
	{
		x_ /= other.x;
		y_ /= other.y;
		z_ /= other.z;
		transform->SynchActive(synchId);
		return *this;
	}

	TransVect3& TransVect3::operator%=(Vect3<float>&& other)
	{
		x_ = fmod(x_, other.x);
		y_ = fmod(y_, other.x);
		z_ = fmod(z_, other.x);
		transform->SynchActive(synchId);
		return *this;
	}

	bool TransVect3::operator==(Vect3<float>&& other)
	{
		return (x_ == other.x && y_ == other.y && z_ == other.z);
	}

	void TransVect3::Set(Vect3<float> vect)
	{
		x_ = vect.x;
		y_ = vect.y;
		z_ = vect.z;
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
		//pos
		Vect3<float> newVect = node->transform.position;
		newVect += Vect3<float>::Rotated3D(localPosition * node->transform.globalScale, node->transform.rotation);
		position.x_ = newVect.x;
		position.y_ = newVect.y;
		position.z_ = newVect.z;
		//rot
		rotation.Set(node->transform.rotation + localRotation);
		//scale
		globalScale.Set(node->transform.globalScale * scale);
	}

	void Transform::SynchActive(int changeType)
	{
		SpacialNode* parent = node->GetSpacialParent();
		//setting according to parent
		if (parent != nullptr)
		{
			if (changeType == 0) //position
			{
				//find relative position
				Vect3<float> unroatedLocalPos = position - parent->transform.position;
				localPosition.Set(Vect3<float>::Rotated3D(unroatedLocalPos, -rotation) / parent->transform.globalScale);
			}
			else if (changeType == 1) //rotation
			{
				localRotation.Set(rotation - parent->transform.rotation);
			}
			else if (changeType == 2) //scale (global)
			{
				scale.Set(globalScale / parent->transform.globalScale);
			}
			else if (changeType == 3) //local pos
			{
				position.Set(parent->transform.position + Vect3<float>::Rotated3D(localPosition, parent->transform.rotation) * parent->transform.globalScale);
			}
			else if (changeType == 4) //local rot
			{
				rotation.Set((parent->transform.rotation + localRotation));
			}
			else if (changeType == 5) //local scale
			{
				globalScale.Set(parent->transform.scale * scale);
			}
			else if (changeType == 6) //2d pos
			{

			}
		}
		else //no parent
		{
			if (changeType == 0) //position
			{
				localPosition.Set(position);
			}
			else if (changeType == 1) //rotation
			{
				localRotation.Set(rotation);
			}
			else if (changeType == 2) //scale (global)
			{
				scale.Set(globalScale);
			}
			else if (changeType == 3) //local pos
			{
				position.Set(localPosition);
			}
			else if (changeType == 4) //local rot
			{
				rotation.Set(localRotation);
			}
			else if (changeType == 5) //local scale
			{
				globalScale.Set(scale);
			}
			else if (changeType == 6) //2d pos
			{

			}
		}

		//activate synching in node
		node->SynchTransforms(node);
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

	//does synch of all child transforms
	void Node::SynchTransforms(SpacialNode* originator)
	{
		for (int i = 0; i < children.size(); ++i)
		{
			SpacialNode* spaceChild = children[i].ToSpacial();
			if (spaceChild != nullptr)
			{
				spaceChild->transform.SynchPassive(originator);
			}
			children[i].SynchTransforms(originator);
		}
	}

	void Node::SetActive()
	{

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

	void SpacialNode::SynchTransforms(SpacialNode* originator)
	{
		for (int i = 0; i < children.size(); ++i)
		{
			SpacialNode* spaceChild = children[i].ToSpacial();
			if (spaceChild != nullptr)
			{
				spaceChild->transform.SynchPassive(this);
			}
			children[i].SynchTransforms(this);
		}
	}