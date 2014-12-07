#include "CAutoDestroyBridge.h"

CAutoDestroyBridge::CAutoDestroyBridge(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
	:CGround(id, specific_type, pos, width, height)
{
	_is_destroy = false;

	for (int i = 0; i < GROUND_BRIDGE_DESTROY_EFFECT_COUNT; i++)
	{
		int sign_x = (rand() % 2) == 1 ? 1 : -1;
		int sign_y = (rand() % 2) == 1 ? 1 : -1;
		float x = (rand() % GROUND_BRIDGE_ELAPSED_RANDOM_POSITION) * sign_x + pos.x - 50;
		float y = (rand() % GROUND_BRIDGE_ELAPSED_RANDOM_POSITION) * sign_y + pos.y;
		_position_effect_destroy[i] = D3DXVECTOR3(x, y, 0);
	}
	LoadResources();
}

CAutoDestroyBridge::~CAutoDestroyBridge()
{
	CGround::~CGround();
	delete _effect_destroy_sprite;
}

void CAutoDestroyBridge::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	_current_sprite = new CSprite(rs->_ground_auto_destroy_bridge);
	_effect_destroy_sprite = new CSprite(rs->_effect_destroy);
}

void CAutoDestroyBridge::Update(int delta_time)
{
	int x_target = CResourcesManager::GetInstance()->m_posBill.x;
	//Cần so sánh x của bill và lance

	SetTarget(x_target);

	if (_is_destroy && _current_sprite->index < 5)
	{
		if (_current_sprite->last_index != _current_sprite->index)
		{
			for (int i = 0; i < GROUND_BRIDGE_DESTROY_EFFECT_COUNT; i++)
			{
				_position_effect_destroy[i].x += GROUND_BRIDGE_DISTANCE_DESTROY;
			}

			_current_sprite->last_index = _current_sprite->index;
			_physical.bounds.left += GROUND_BRIDGE_DISTANCE_DESTROY;
		}
	}
	else if (_current_sprite->index == 5)
	{
		_physical.SetBounds(0, 0, 0, 0);
	}
}

void CAutoDestroyBridge::Draw()
{
	CCamera* c = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);
	_current_sprite->Draw(pos.x, pos.y);

	//Cầu tự phá hủy
	if (_is_destroy && _current_sprite->index < 5)
	{
		//Thay đổi effect theo hiệu ứng của sprite chính
		_effect_destroy_sprite->PerformAllEffect(EFFECT_DESTROY_TIME);

		//Vẽ hiệu ứng phá cầu
		for (int i = 0; i < GROUND_BRIDGE_DESTROY_EFFECT_COUNT; i++)
		{
			D3DXVECTOR3 pos_effect = c->Transform(_position_effect_destroy[i]);
			_effect_destroy_sprite->Draw(pos_effect.x, pos_effect.y);
		}

		_current_sprite->PerformEffectOneTime(2, 5, GROUND_BRIDGE_DESTROY_TIME);

	}
	else if (!_is_destroy)
	{
		_current_sprite->PerformEffect(0, 1, GROUND_TIME_EFFECT);
	}

}

void CAutoDestroyBridge::SetTarget(float x)
{
	if (x >= _physical.bounds.left && !_is_destroy)
	{
		_is_destroy = true;
		_current_sprite->index = 2;
		_current_sprite->last_index = _current_sprite->index;
		_physical.bounds.left += (GROUND_BRIDGE_DISTANCE_DESTROY - 5);
	}
}