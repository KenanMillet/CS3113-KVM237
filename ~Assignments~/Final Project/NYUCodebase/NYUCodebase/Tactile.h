#pragma once
#include "Model.h"
#include <cstdint>
#include <set>
#include <typeinfo>
#include <limits>

const float INFINITESIMAL(std::numeric_limits<float>::min());
const float POS_INFINITY(std::numeric_limits<float>::infinity());
const float NEG_INFINITY(std::numeric_limits<float>::lowest());

class CollisionHandler;

class Tactile : virtual public Model
{
public:
	Tactile(float = 0, float = 0, float = 0, bool = false, CollisionHandler* = defaultCollisionHandler);
	Tactile(const Tactile&);
	Tactile(Tactile&&);
	virtual ~Tactile();

	bool immobile() const;

	Tactile& operator=(const Tactile&);
	Tactile& operator=(Tactile&&);

	virtual void onCollision(Tactile*, Vector);
	virtual bool resolveCollision(Tactile*, Vector);
	virtual void touch(Tactile*, Vector);

	float moveX();
	float moveY();
	float moveZ();

	float getCollW();
	float getCollH();
	float getCollD();

	template<class T> bool isOfType() const;

	static CollisionHandler* defaultCollisionHandler;
protected:
	Tactile& noCollisionWith(Tactile*);

	bool posLock;
	float collWidth, collHeight, collDepth;
	float dispX, dispY, dispZ;
private:
	CollisionHandler* thehandler;
};

template<class T>
bool Tactile::isOfType() const
{
	return typeid(T) == typeid(*this);
}