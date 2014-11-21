#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Tiled.h"

class Background
{

private:	
	vector<int> m_listBG; // danh sach cac back ground	
	vector<Tiled*> m_listTiled;
	int m_level;
	int m_rows; // so tile row
	int m_cols; // so tile col
	int m_width;
	int m_height;
	int m_beginRow; // bau dau ve tu hang
	int m_beginCol; // bat dau ve tu col
	int m_endRow;  // hang ket thuc
	int m_endCol;
	CCamera *m_camera;
	

public:
	Background();	
	~Background();
	
	void draw();
	void init();
	void update(float time);
	void setWidthBG(int x){ m_width = x; }
	int getWidthBG(){ return m_width; }
	void setHeightBG(int x){ m_height = x; }
	int getHeightBG(){ return m_height; }


};



#endif 