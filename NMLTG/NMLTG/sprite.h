#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "texture.h"

class Sprite
{
protected:
	Texture *sprite_texture;
	int start;
	int end;
	int index;
	int time_ani;
	DWORD last_time;
public:
	
	Sprite();
	Sprite(const Sprite &sprite);
	Sprite(Texture *texture, int time_ani = 0);
	Sprite(Texture *texture, int start, int end, int time_ani = 0);
	~Sprite();

	void Next(); //Chuyển hình
	void Reset(); //Trở về trạng thái ban đầu
	void SelectFrameOf(int index); //Chọn hiển thị frame bất kỳ
	void UpdateAllEffect(int elapsed_time); //Chạy hiệu ứng
	void UpdateEffect(int start_index, int end_index, int elapsed_time);
	void Draw(int x, int y);
	void DrawFlipX(int x, int y);
	void DrawFlipY(int x, int y);
	void DrawRect(int x, int y, RECT srcRect);
	void DrawTransform(int x, int y, D3DXVECTOR2 scale, float degRotate, float depth);

};
#endif // !_SPRITE_H_
