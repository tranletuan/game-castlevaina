#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Texture.h"

class CSprite
{

public:
	CTexture *sprite_texture;
	int start;
	int end;
	int index;
	int time_ani;
	int last_index;
	DWORD last_time;
	D3DXVECTOR2 _pos;

	CSprite();
	CSprite(const CSprite &sprite);
	CSprite(CTexture *texture);
	CSprite(CTexture *texture, int start, int end, int time_ani = 0);
	~CSprite();

	void Next(); //Chuyển hình
	void Reset(); //Trở về trạng thái ban đầu
	void SelectFrameOf(int index); //Chọn hiển thị frame bất kỳ
	void PerformAllEffect(int time); //Chạy tất cả hiệu ứng
	void PerformEffect(int start, int end, int time, int step = 1); //Chạy hiệu ứng trong phạm vi xác định
	bool PerformEffectOneTime(int start, int end, int time, int step = 1); //Chạy hiệu ứng trong phạm vi xác định 1 lần duy nhất

	void Draw(float x, float y);
	
	void DrawFlipX(float x, float y);
	void DrawFlipY(float x, float y);
	void DrawTransform(float x, float y, D3DXVECTOR2 scale, float degRotate, float depth);
	void DrawWithDirection(D3DXVECTOR3 pos, float direction, int start = 0, int end = 0, int time = 100, int step = 1);
	bool DrawWithDirectionAndOneTimeEffect(D3DXVECTOR3 pos, float direction, int start, int end, int time = 100, int step = 1);


	RECT GetRect(int left, int top, int right, int bottom);
	void Draw(float x, float y, RECT rect);// de ve tile cua back ground, tam o left-top
	void Draw(D3DXVECTOR2 pos);// de ve voi postion , tam o left-top
	void setPostion(D3DXVECTOR2 x){ _pos = x; }

private:
	D3DXVECTOR3 GetCorner(float x, float y, float width, float height);

};
#endif // !_SPRITE_H_
