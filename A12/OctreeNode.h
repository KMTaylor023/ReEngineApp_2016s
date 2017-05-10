#pragma once
#include "RE\ReEng.h"
#include "MyBoundingObjectClass.h"


class OctreeNode {

	const float MIN_SIZE = 1.0f;

public:
	OctreeNode(OctreeNode* parentNode, float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
	OctreeNode(OctreeNode* parentNode, vector3 a_minBounds, vector3 a_maxBounds);

	void checkCollisions(void);

	bool addObject(MyBoundingObjectClass* other);

	vector3 getMinBounds(void);
	vector3 getMaxBounds(void);

	float getSize(void);

	OctreeNode* parent;

private:
	vector3 minBounds;
	vector3 maxBounds;
	float size;
	float halfsize;
	bool createdChildren;

	std::vector<MyBoundingObjectClass*> objects;


	OctreeNode* nodelist[8];



};