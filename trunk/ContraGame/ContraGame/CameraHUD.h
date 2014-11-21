#ifndef CAMERAHUD_H
#define CAMERAHUD_H

#include "CResourcesManager.h"
#include <vector>

using namespace std;
#define SPACE_BADGE 20


class CameraHUD
{
private:
	CSprite *m_sprite;
	int m_life; // so mang 

public:
	CameraHUD();
	CameraHUD(int life);
	~CameraHUD();

	void draw();
	void update(float time);
	void init();

	int getLife(){ return m_life; }
	void setLife(int x){ m_life = x; }

};



#endif