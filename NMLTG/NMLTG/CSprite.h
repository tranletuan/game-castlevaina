#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "CTexture.h"

class CSprite
{

public:
	CTexture *sprite_texture;
	int start;
	int end;
	int index;
	int time_ani;
	DWORD last_time;

	
	CSprite();
	CSprite(const CSprite &sprite);
	CSprite(CTexture *texture, int time_ani = 0);
	CSprite(CTexture *texture, int start, int end, int time_ani = 0);
	~CSprite();

	void Next(); //Chuyển hình
	void Reset(); //Trở về trạng thái ban đầu
	void SelectFrameOf(int index); //Chọn hiển thị frame bất kỳ
	void UpdateAllEffect(int elapsed_time); //Chạy hiệu ứng
	void UpdateEffect();
	void Draw(int x, int y);
	void DrawFlipX(int x, int y);
	void DrawFlipY(int x, int y);
	void DrawTransform(int x, int y, D3DXVECTOR2 scale, float degRotate, float depth);
	void DrawWithDirecion(D3DXVECTOR3 pos, float direction, int start =  0, int end = 0, int time = 100, bool start_first_index = false);
private:
	D3DXVECTOR3 GetCorner(int x, int y, int width, int height);

};
#endif // !_SPRITE_H_
