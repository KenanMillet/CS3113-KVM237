#include "CollisionHandler.h"
#include "Tactile.h"
#include <cstdint>

void CollisionHandler::operator()()
{
	for(auto i = objects.begin(); i != objects.end(); ++i)
	{
		for(auto j = objects.begin(); j != objects.end(); ++j)
		{
			if(i == j) continue;

			uint8_t sides = 0;
			bool collTest = true;
			bool exception = false;

			Tactile* t1 = i->first;
			Tactile* t2 = j->first;

			if(t1->getX() - t1->getCollW() / 2 <= t2->getX() + t2->getCollW() / 2 && t1->getX() - t1->getCollW() / 2 >= t2->getX() - t2->getCollW() / 2) sides |= 1 << 0; //t1 left side overlap
			if(t1->getX() + t1->getCollW() / 2 >= t2->getX() - t2->getCollW() / 2 && t1->getX() + t1->getCollW() / 2 <= t2->getX() + t2->getCollW() / 2) sides |= 1 << 1; //t1 right side overlap
			if(t1->getY() - t1->getCollH() / 2 <= t2->getY() + t2->getCollH() / 2 && t1->getY() - t1->getCollH() / 2 >= t2->getY() - t2->getCollH() / 2) sides |= 1 << 2; //t1 bottom side overlap
			if(t1->getY() + t1->getCollH() / 2 >= t2->getY() - t2->getCollH() / 2 && t1->getY() + t1->getCollH() / 2 <= t2->getY() + t2->getCollH() / 2) sides |= 1 << 3; //t1 top side overlap
			if(t1->getZ() - t1->getCollD() / 2 <= t2->getZ() + t2->getCollD() / 2 && t1->getZ() - t1->getCollD() / 2 >= t2->getZ() - t2->getCollD() / 2) sides |= 1 << 4; //t1 near side overlap
			if(t1->getZ() + t1->getCollD() / 2 >= t2->getZ() - t2->getCollD() / 2 && t1->getZ() + t1->getCollD() / 2 <= t2->getZ() + t2->getCollD() / 2) sides |= 1 << 5; //t1 far side overlap

			collTest = ((sides & (3 << 0)) != 0) && collTest;
			collTest = ((sides & (3 << 2)) != 0) && collTest;
			collTest = ((sides & (3 << 4)) != 0) && collTest;

			if(i->second.find(j->first) != i->second.end())
			{
				exception = true;
				sides = ~sides;
			}

			if((sides & (3 << 0)) == (3 << 0)) sides &= ~((3 << 0));
			if((sides & (3 << 2)) == (3 << 2)) sides &= ~((3 << 2));
			if((sides & (3 << 4)) == (3 << 4)) sides &= ~((3 << 4));

			if(collTest)
			{
				if(exception) t2->collision(t1, sides);
				t1->collision(t2, sides);
			}
		}
	}
}

void CollisionHandler::add(Tactile* t)
{
	objects.insert(std::make_pair(t, std::set<Tactile*>()));
}

void CollisionHandler::addException(Tactile* t, Tactile* e)
{
	objects[t].insert(e);
}

void CollisionHandler::remove(Tactile* t)
{
	objects.erase(t);
}

CollisionHandler handleCollisions;