#ifndef TILED_H
#define TILED_H

#include "CResourcesManager.h"
#include "Sprite.h"
#include "Config.h"

class Tiled
{
private:

	CSprite *m_sprite;
	CCamera *m_camera;
	LPD3DXSPRITE m_spriteHandler;

	float m_posX;
	float m_posY;
	int m_width;
	int m_height;
	int m_id;
	int m_level; // level of map
	int m_index; 


public:
	Tiled();
	Tiled(int index, int id, float posX, float posY);
	~Tiled();

	void update(int time);
	void draw();
	void init();	

	
	void setID(int x){ m_id = x; }
	int getID(){ return m_id; }
	void setWidth(int x){ m_width = x; }
	int getWidth(){ return m_width; }
	void setHeight(int x){ m_height = x; }
	int getHeight(){ return  m_height; }
	void setPosX(float x){ m_posX = x; }
	float getPosX(){ return m_posX; }
	void setPosY(float x){ m_posY = x; }
	float getPosY(){ return m_posY; }

};



#endif