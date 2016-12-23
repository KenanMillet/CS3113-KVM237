#pragma once
#include <initializer_list>
#include <unordered_set>
#include "Matrix.h"
#include "Tactile.h"

class Entity;

class Spawner
{
public:
	Spawner(const Vector& = Vector());

	//Disable copying
	Spawner(const Spawner&) = delete;
	Spawner(Spawner&&) = delete;
	Spawner& operator=(const Spawner&) = delete;
	Spawner& operator=(Spawner&&) = delete;

	~Spawner();

	template<class E, class Arg, class... Args> E* spawn(std::initializer_list<Vector>, Arg, Args...);
	template<class E> E* spawn(std::initializer_list<Vector>);
	template<class E> bool despawn(E*);
	template<class E> bool disown(E*);

	size_t numSpawn() const;

private:
	void setupEntity(Entity*, const Vector&, const Vector&, const Vector&);
	std::unordered_set<Entity*> entities;
	std::unordered_set<Entity*> corpses;
	Vector location;
};

template<class E, class Arg, class... Args>
inline E* Spawner::spawn(std::initializer_list<Vector> spatialInfo, Arg arg, Args... args)
{
	if(!(std::is_base_of<Entity, E>::value)) return nullptr;
	E* e = nullptr;
	bool recyclable = !corpses.empty();
	if(recyclable)
	{
		for(Entity* entity : corpses)
		{
			if(typeid(E) == typeid(*entity))
			{
				e = dynamic_cast<E*>(entity);
				corpses.erase(entity);
				*e = E(arg, args...);
				break;
			}
		}
		recyclable = (e != nullptr);
	}
	if(!recyclable)
	{
		e = new E(arg, args...);
	}
	Vector info[3];
	int i = 0;
	for(auto v : spatialInfo) info[i++] = v;
	if(i == 0) info[i++] = location;
	if(i == 1) info[i++] = Vector();
	if(i == 2) info[i] = Vector(1.0f, 1.0f, 1.0f);
	setupEntity(e, info[0], info[1], info[2]);
	return e;
}

template<class E>
inline E* Spawner::spawn(std::initializer_list<Vector> spatialInfo)
{
	if(!(std::is_base_of<Entity, E>::value)) return nullptr;
	E* e = nullptr;
	bool recyclable = !corpses.empty();
	if(recyclable)
	{
		for(Entity* entity : corpses)
		{
			if(typeid(E) == typeid(*entity))
			{
				e = dynamic_cast<E*>(entity);
				corpses.erase(entity);
				*e = E();
				break;
			}
		}
		recyclable = (e != nullptr);
	}
	if(!recyclable)
	{
		e = new E();
	}
	Vector info[3];
	int i = 0;
	for(auto v : spatialInfo) info[i++] = v;
	if(i == 0) info[i++] = location;
	if(i == 1) info[i++] = Vector();
	if(i == 2) info[i] = Vector(1.0f, 1.0f, 1.0f);
	setupEntity(e, info[0], info[1], info[2]);
	return e;
}

template<class E>
inline bool Spawner::despawn(E* e)
{
	bool success = disown(e);
	if(success)
	{
		corpses.insert(e);
		((Entity*) e)->xPos = NEG_INFINITY;
		((Entity*) e)->yPos = NEG_INFINITY;
		((Entity*) e)->zPos = NEG_INFINITY;
	}
	return success;
}

template<class E>
inline bool Spawner::disown(E* e)
{
	if(entities.empty()) return false;
	return (entities.erase(e) == 1);
}