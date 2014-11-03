#include "CEffectObject.h"

CEffectObject::CEffectObject(SpecificType specific_type, D3DXVECTOR3 pos, int effect_time)
	:CObject(-1, specific_type, Effect, pos)
{
	_effect_time = effect_time;
}

CEffectObject::~CEffectObject()
{
	if (_current_sprite != NULL)
	{
		delete _current_sprite;
	}
}

void CEffectObject::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	if (_specific_type == EffectDestroy)
	{
		_current_sprite = new CSprite(rs->_effect_destroy);
	}

}

void CEffectObject::Draw()
{
	CCamera* c = CResourcesManager::GetInstance()->_camera;
	D3DXVECTOR3 pos = c->Transform(_physical.x, _physical.y);

	_current_sprite->PerformAllEffect(_effect_time);
	_current_sprite->Draw(pos.x, pos.y);
}
