#include "CollisionHandler.h"
#include "Tactile.h"
#include <cstdint>
#include <iterator>
#include <vector>
#include <algorithm>

#include "Player.h"
#include "logger.h"

using namespace std;

void CollisionHandler::operator()()
{
	for(auto i = objects.begin(); i != objects.end(); ++i)
	{
		for(auto j = i; ++j != objects.end();)
		{
			if(i->second.find(j->first) != i->second.end()) continue;
			Vector sepVector = sepAxisTheorem(i->first, j->first);

			if(sepVector != Vector())
			{
				i->first->onCollision(j->first, sepVector);
				j->first->onCollision(i->first, -sepVector);
				i->first->touch(j->first, sepVector);
				j->first->touch(i->first, -sepVector);
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

Vector CollisionHandler::sepAxisTheorem(Tactile* t1, Tactile* t2)
{
	Renderable::Renderpack* rp1 = t1->render();
	Renderable::Renderpack* rp2 = t2->render();

	const Matrix& matrix1 = *rp1->getMatrix();
	const Matrix& matrix2 = *rp2->getMatrix();
	const float* varray1 = rp1->getVertexCoords();
	const float* varray2 = rp2->getVertexCoords();
	size_t vsize1 = rp1->getSize();
	size_t vsize2 = rp2->getSize();

	std::vector<Vector[3]> triangles1(vsize1 / 6);
	std::vector<Vector[3]> triangles2(vsize2 / 6);
	for(size_t i = 0; i < vsize1; i += 2)
	{
		triangles1[i / 6][(i / 2) % 3] = matrix1 * Vector(varray1[i], varray1[i + 1]);
	}
	for(size_t i = 0; i < vsize2; i += 2)
	{
		triangles2[i / 6][(i / 2) % 3] = matrix2 * Vector(varray2[i], varray2[i + 1]);
	}
	t1->postrender();
	t2->postrender();

	float resultMag = POS_INFINITY;
	Vector resultVec;
	Vector touchingVec;
	bool touching = false;
	bool collision = false;

	for(size_t i = 0; i < triangles1.size(); ++i)
	{
		bool tricoll = true;
		for(size_t j = 0; j < triangles2.size(); ++j)
		{
			for(size_t k = 0; k < 6; ++k)
			{
				Vector normal;
				if(k < 3) normal = Vector(triangles1[i][k] - triangles1[i][(k + 1) % 3]) ^ Vector(0.0f, 0.0f, -1.0f);
				else normal = Vector(triangles2[j][k - 3] - triangles2[j][(k - 2) % 3]) ^ Vector(0.0f, 0.0f, -1.0f);

				float min1 = POS_INFINITY;
				float max1 = NEG_INFINITY;
				float min2 = POS_INFINITY;
				float max2 = NEG_INFINITY;
				for(size_t l = 0; l < 3; ++l)
				{
					float d = normal * triangles1[i][l];
					min1 = ((min1 < d) ? min1 : d);
					max1 = ((max1 > d) ? max1 : d);
				}
				for(size_t l = 0; l < 3; ++l)
				{
					float d = normal * triangles2[j][l];
					min2 = ((min2 < d) ? min2 : d);
					max2 = ((max2 > d) ? max2 : d);
				}
				float disp = POS_INFINITY;
				if(min1 == max2 || max1 == min2)
				{
					touching = true;
				}
				if(min1 < max2 && max1 > min2)
				{
					disp = min(max1 - min2, max2 - min1);
				}
				tricoll = tricoll && (disp != POS_INFINITY);
				if(disp < resultMag)
				{
					resultMag = disp;
					resultVec = normal;
				}
			}
			collision = collision || tricoll;
		}
	}
	if(!collision) return Vector();
	//resultVec.normalize();
	//return resultVec * resultMag;
	resultVec = Vector(t1->getX() - t2->getX(), t1->getY() - t2->getY()).normalize();
	float factor = min(fabs(resultVec.x), fabs(resultVec.y));
	if(factor == 0) factor = max(fabs(resultVec.x), fabs(resultVec.y));
	resultVec /= factor;
	resultVec *= INFINITESIMAL;
	return resultVec;
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