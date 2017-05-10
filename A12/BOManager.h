#pragma once
#include "RE\ReEng.h"
#include "MyBoundingObjectClass.h"
class BOManager {
	static BOManager* instance;


	int id = 0;
	std::map<int, MyBoundingObjectClass*>  m_BOList;
	int count;
private:
	BOManager();
	void setCollisionsFalse(void);
	void releaseAllItems(void);

public:

	static BOManager* GetInstance();
	static void ReleaseInstance();

	int getCount(void);

	//Adds a BO to the manager, returns and int that acts as an id for that BO stored in the manager
	int addBO(std::vector<vector3> vertexList);

	//sets color of given BO to color
	void setBOColor(int BOID, vector3 color);

	//sets visibility of individual BO type of given BO
	void setBOVisibility(int BOID, bool AABB, bool sphere, bool ReAABB);

	//sets the modelt matrix of given BO
	void setBOModelMatrix(int BOID, matrix4 a_m4ToWorld);

	//individually renders a BO
	void renderBO(int BOID);

	//Renders all BO at once
	void renderAllBO(void);

	//Sets all BO colors at once
	void setAllBOColor(vector3 color);

	//sets visibility of all BO types at once
	void setAllBOVisibility(bool AABB, bool sphere, bool ReAABB);

	//checks collosions between all BO in manager, and resolves them
	void checkCollisions(void);

};
