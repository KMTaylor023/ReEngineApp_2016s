#include "OctreeNode.h"

OctreeNode::OctreeNode(OctreeNode* parentNode,float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{

	parent = parentNode;
	minBounds = vector3(minX, minY, minZ);
	maxBounds = vector3(maxX, maxY, maxZ);

	size = maxX - minX;
	halfsize = size / 2.0f;

	createdChildren = false;

	for (int i = 0; i < 8; i++) {
		nodelist[i] = nullptr;
	}
}

OctreeNode::OctreeNode(OctreeNode* parentNode,vector3 a_minBounds, vector3 a_maxBounds)
{
	parent = parentNode;

	minBounds = a_minBounds;
	maxBounds = a_maxBounds;

	size = maxBounds.x - minBounds.x;

	createdChildren = false;

	halfsize = size / 2.0f;
	for (int i = 0; i < 8; i++) {
		nodelist[i] = nullptr;
	}
}

void OctreeNode::checkCollisions(void)
{

	for (int i = 0; i < objects.size(); i++) {
		for (int j = 0; j < objects.size(); j++) {
			if (i == j) {
				continue;
			}

			if (objects[i]->IsColliding(objects[j])) {
				objects[i]->SetColliding(true);
				objects[j]->SetColliding(true);
				objects[i]->SetColor(RERED);
				objects[j]->SetColor(RERED);
			}
		}

		for (int i = 0; i < 8; i++) {
			if (nodelist[i] != nullptr) {
				nodelist[i]->checkCollisions();
			}
		}
	}

}

bool OctreeNode::addObject(MyBoundingObjectClass * other)
{
	if (other->GetMin().x >= minBounds.x &&
		other->GetMin().y >= minBounds.y &&
		other->GetMin().z >= minBounds.z &&
		other->GetMax().x <= maxBounds.x &&
		other->GetMax().y <= maxBounds.y &&
		other->GetMax().z <= maxBounds.z) {

		if (!createdChildren) {

			vector3 nMinBounds = minBounds;

			byte b = 0;
			for (int i = 0; i < 8; i++) {
				nMinBounds = minBounds;
				for(int j = 1; j <= 3; j++)
					nMinBounds[j] += ((b >> j) & 1) * halfsize;

				nodelist[i] = new OctreeNode(this, nMinBounds, vector3(nMinBounds.x + halfsize, nMinBounds.y + halfsize, nMinBounds.z + halfsize));
			}
		}

	}
	else {
		return false;
	}
}

vector3 OctreeNode::getMinBounds(void)
{
	return minBounds;
}

vector3 OctreeNode::getMaxBounds(void)
{
	return maxBounds;
}

float OctreeNode::getSize(void)
{
	return size;
}
