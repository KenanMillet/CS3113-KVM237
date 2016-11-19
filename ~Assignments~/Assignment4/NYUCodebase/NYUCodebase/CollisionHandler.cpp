#include "CollisionHandler.h"
#include "Tactile.h"
#include <cstdint>
#include <iterator>

#include "Player.h"
#include "logger.h"

using namespace std;

void CollisionHandler::operator()()
{
	map<Tactile*, map<Tactile*, uint8_t>> collisions;

	for(auto i = objects.begin(); i != objects.end(); ++i)
	{
		Tactile* t1 = i->first;
		if(t1->moveY() == 0) continue;
		for(auto j = objects.begin(); j != objects.end(); ++j)
		{
			if(i == j) continue;
			Tactile* t2 = j->first;

			if(i->second.find(t2) != i->second.end()) continue;
			uint8_t sides = checkCollision(t1, t2);
			if(((sides & 3U) != 0) && ((sides & 12U) != 0) && ((sides & 48U) != 0))
			{
				uint8_t s1 = (sides & 12U);
				uint8_t s2 = (sides & 12U) ^ 12U;
				t1->collisionY(t2, s1 >> 2);
				collisions[t1][t2] |= s1;
				collisions[t2][t1] |= s2;
			}
		}
	}

	for(auto i = objects.begin(); i != objects.end(); ++i)
	{
		Tactile* t1 = i->first;
		if(t1->moveX() == 0) continue;
		for(auto j = objects.begin(); j != objects.end(); ++j)
		{
			if(i == j) continue;
			Tactile* t2 = j->first;

			if(i->second.find(t2) != i->second.end()) continue;
			uint8_t sides = checkCollision(t1, t2);
			if(((sides & 3U) != 0) && ((sides & 12U) != 0) && ((sides & 48U) != 0))
			{
				uint8_t s1 = (sides & 3U);
				uint8_t s2 = (sides & 3U) ^ 3U;
				t1->collisionX(t2, s1 >> 0);
				collisions[t1][t2] |= s1;
				collisions[t2][t1] |= s2;
			}
		}
	}

	for(auto i = objects.begin(); i != objects.end(); ++i)
	{
		Tactile* t1 = i->first;
		if(t1->moveZ() == 0) continue;
		for(auto j = objects.begin(); j != objects.end(); ++j)
		{
			if(i == j) continue;
			Tactile* t2 = j->first;

			if(i->second.find(t2) != i->second.end()) continue;
			uint8_t sides = checkCollision(t1, t2);
			if(((sides & 3U) != 0) && ((sides & 12U) != 0) && ((sides & 48U) != 0))
			{
				uint8_t s1 = (sides & 48U);
				uint8_t s2 = (sides & 48U) ^ 48U;
				t1->collisionZ(t2, s1 >> 4);
				collisions[t1][t2] |= s1;
				collisions[t2][t1] |= s2;
			}
		}
	}

	for(auto i = objects.begin(); i != objects.end(); ++i)
	{
		Tactile* t1 = i->first;
		for(auto j = objects.begin(); j != objects.end(); ++j)
		{
			if(i == j) continue;
			Tactile* t2 = j->first;

			uint8_t sides = checkTouch(t1, t2);

			if(i->second.find(t2) != i->second.end()) continue;

			if(sides) t1->touch(t2, sides);

		}
	}

	for(auto i = collisions.begin(); i != collisions.end(); ++i)
	{
		for(auto j = i->second.begin(); j != i->second.end(); ++j)
		{
			i->first->collision(j->first, j->second);
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

uint8_t CollisionHandler::checkCollision(Tactile* t1, Tactile* t2)
{
	float t1L = t1->getX() - t1->getCollW() / 2;
	float t1R = t1->getX() + t1->getCollW() / 2;
	float t2L = t2->getX() - t2->getCollW() / 2;
	float t2R = t2->getX() + t2->getCollW() / 2;
	float t1B = t1->getY() - t1->getCollH() / 2;
	float t1T = t1->getY() + t1->getCollH() / 2;
	float t2B = t2->getY() - t2->getCollH() / 2;
	float t2T = t2->getY() + t2->getCollH() / 2;
	float t1N = t1->getZ() - t1->getCollD() / 2;
	float t1F = t1->getZ() + t1->getCollD() / 2;
	float t2N = t2->getZ() - t2->getCollD() / 2;
	float t2F = t2->getZ() + t2->getCollD() / 2;

	return uint8_t(((t1L <= t2R && t1L >= t2L) ? 1U : 0U) + ((t1R >= t2L && t1R <= t2R) ? 2U : 0U) + ((t1B <= t2T && t1B >= t2B) ? 4U : 0U) + ((t1T >= t2B && t1T <= t2T) ? 8U : 0U) + ((t1N <= t2F && t1N >= t2N) ? 16U : 0U) + ((t1F >= t2N && t1F <= t2F) ? 32U : 0U));
}

uint8_t CollisionHandler::checkTouch(Tactile* t1, Tactile* t2)
{
	float t1L = t1->getX() - t1->getCollW() / 2;
	float t1R = t1->getX() + t1->getCollW() / 2;
	float t2L = t2->getX() - t2->getCollW() / 2;
	float t2R = t2->getX() + t2->getCollW() / 2;
	float t1B = t1->getY() - t1->getCollH() / 2;
	float t1T = t1->getY() + t1->getCollH() / 2;
	float t2B = t2->getY() - t2->getCollH() / 2;
	float t2T = t2->getY() + t2->getCollH() / 2;
	float t1N = t1->getZ() - t1->getCollD() / 2;
	float t1F = t1->getZ() + t1->getCollD() / 2;
	float t2N = t2->getZ() - t2->getCollD() / 2;
	float t2F = t2->getZ() + t2->getCollD() / 2;
	float adj = INFINITESIMAL;

	uint8_t l = ((t1L - adj == t2R) && ((t1B <= t2T && t1B >= t2B) || (t1T >= t2B && t1T <= t2T)) && ((t1N <= t2F && t1N >= t2N) || (t1F >= t2N && t1F <= t2F))) ?  1U : 0U;
	uint8_t r = ((t1R + adj == t2L) && ((t1B <= t2T && t1B >= t2B) || (t1T >= t2B && t1T <= t2T)) && ((t1N <= t2F && t1N >= t2N) || (t1F >= t2N && t1F <= t2F))) ?  2U : 0U;
	uint8_t b = ((t1B - adj == t2T) && ((t1N <= t2F && t1N >= t2N) || (t1F >= t2N && t1F <= t2F)) && ((t1L <= t2R && t1L >= t2L) || (t1R >= t2L && t1R <= t2R))) ?  4U : 0U;
	uint8_t t = ((t1T + adj == t2B) && ((t1N <= t2F && t1N >= t2N) || (t1F >= t2N && t1F <= t2F)) && ((t1L <= t2R && t1L >= t2L) || (t1R >= t2L && t1R <= t2R))) ?  8U : 0U;
	uint8_t n = ((t1N - adj == t2F) && ((t1L <= t2R && t1L >= t2L) || (t1R >= t2L && t1R <= t2R)) && ((t1B <= t2T && t1B >= t2B) || (t1T >= t2B && t1T <= t2T))) ? 16U : 0U;
	uint8_t f = ((t1F + adj == t2N) && ((t1L <= t2R && t1L >= t2L) || (t1R >= t2L && t1R <= t2R)) && ((t1B <= t2T && t1B >= t2B) || (t1T >= t2B && t1T <= t2T))) ? 32U : 0U;

	return l + r + b + t + n + f;
}

CollisionHandler handleCollisions;