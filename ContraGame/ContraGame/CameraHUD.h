#ifndef CAMERAHUD_H
#define CAMERAHUD_H

#include "CResourcesManager.h"
#include <vector>

using namespace std;
#define SPACE_BADGE 20


class CameraHUD
{
private:
	CSprite *m_spriteBadge;
	CSprite *m_spriteOver;
	int m_life; // so mang 

public:
	CameraHUD();
	
	~CameraHUD();

	void draw();
	void update(int time);
	void init();

	int getLife(){ return m_life; }
	void setLife(int x){ m_life = x; }

};



#endif