#include "BOManager.h"


BOManager* BOManager::instance = nullptr;
BOManager::BOManager() {
	count = 0;
}

void BOManager::setCollisionsFalse(void)
{
	for (auto const &ent : m_BOList) {
		ent.second->SetColliding(false);
	}
}

void BOManager::releaseAllItems(void)
{
	for (auto const &ent : m_BOList) {
		delete ent.second;
	}
}

BOManager * BOManager::GetInstance()
{
	if (instance == nullptr) {
		instance = new BOManager();
	}
	return instance;
}

void BOManager::ReleaseInstance()
{
	if (instance != nullptr) {
		instance->releaseAllItems();
		delete instance;
		instance = nullptr;
	}
}

int BOManager::getCount(void)
{
	return count;
}

int BOManager::addBO(std::vector<vector3> vertexList)
{
	MyBoundingObjectClass* newObj = nullptr;
	newObj = new MyBoundingObjectClass(vertexList);
	if (newObj == nullptr) {
		return -1;
	}
	count++;
	m_BOList[id] = newObj;
	id++;
	return id - 1;
}

void BOManager::setBOColor(int BOID, vector3 color)
{
	m_BOList[BOID]->SetColor(color);
}

void BOManager::setBOVisibility(int BOID, bool AABB, bool sphere, bool ReAABB)
{
	m_BOList[BOID]->SetBoundingBoxVis(AABB);
	m_BOList[BOID]->SetBoundingSphereVis(sphere);
	m_BOList[BOID]->SetReAlignedBoundingBoxVis(ReAABB);
}

void BOManager::setBOModelMatrix(int BOID, matrix4 a_m4ToWorld)
{
	m_BOList[BOID]->SetModelMatrix(a_m4ToWorld);
}

void BOManager::renderBO(int BOID)
{
	m_BOList[BOID]->Render();
}

void BOManager::renderAllBO(void)
{
	for (auto const &ent : m_BOList) {
		ent.second->Render();
	}
}

void BOManager::setAllBOColor(vector3 color)
{
	for (auto const &ent : m_BOList) {
		ent.second->SetColor(color);
	}
}

void BOManager::setAllBOVisibility(bool AABB, bool sphere, bool ReAABB)
{
	for (auto const &ent : m_BOList) {
		ent.second->SetBoundingBoxVis(AABB);
		ent.second->SetBoundingSphereVis(sphere);
		ent.second->SetReAlignedBoundingBoxVis(ReAABB);
	}
}

void BOManager::checkCollisions(void)
{
	setCollisionsFalse();
	setAllBOColor(REGREEN);

	for (auto const &ent : m_BOList) {
		if (ent.second->GetColliding()) {
			continue;
		}

		for (auto const &ent2 : m_BOList) {
			if (ent == ent2) {
				continue;
			}
			if (ent.second->IsColliding(ent2.second)) {
				ent.second->SetColliding(true);
				ent.second->SetColor(RERED);
				ent2.second->SetColliding(true);
				ent2.second->SetColor(RERED);
			}
		}

	}
}
