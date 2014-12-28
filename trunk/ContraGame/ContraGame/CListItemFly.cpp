#include "CListItemFly.h"

CListItemFly::CListItemFly()
{
	LoadResources();
}

CListItemFly::~CListItemFly()
{

}

void CListItemFly::LoadResources()
{
	_listItems = CResourcesManager::GetInstance()->listObNoTree;

	vector<CObject*> listObNoneTreeX;
	for (int i = 0; i < _listItems.size(); i++)
	{
		if (_listItems.at(i)->getSpecificType() != RunMan && _listItems.at(i)->getSpecificType() != RunMan_Fire)
		{
			CObject *ob = getObjectTrust(_listItems.at(i));
			listObNoneTreeX.push_back(ob);
		}		
	}

	_listItems = listObNoneTreeX;
}

void CListItemFly::Draw()
{
	for (int i = 0; i < _listItems.size(); i++)
	{
		_listItems.at(i)->Draw();
	}
}

void CListItemFly::Update(int delta_time)
{
	for (int i = 0; i < _listItems.size(); i++)
	{
		setActivity(_listItems.at(i));

		if (_listItems.at(i)->getEnable())
		{
			_listItems.at(i)->Update(delta_time);
		}
	}
}

void CListItemFly::CheckCollisionWithPlayerAndWeapon(CPlayerWeapon* weapon, CBill* player)
{
	for (int i = 0; i < _listItems.size(); i++)
	{
		CObject* item = _listItems.at(i);
		if (!item->getEnable()) continue;

		//Xét va chạm với người chơi
		if (item->_hp == 0)
		{
			if (player->_physical.Collision(&item->_physical) != NoCollision)
			{
				// play soun
				CResourcesManager::GetInstance()->m_audio->playSound(CResourcesManager::GetInstance()->sound_get_item);
				switch (item->_specific_type)
				{
				case ItemM:
					player->setSoundBullet(CResourcesManager::GetInstance()->sound_bullet_m);
					weapon->SetWaeponType(WPM);
					break;
				case ItemR:
					weapon->SetVelocityPowerful(BULLET_REINFORCE);
					break;
				case ItemF:
					player->setSoundBullet(CResourcesManager::GetInstance()->sound_bullet_m);
					weapon->SetWaeponType(WPF);
					break;
				case ItemL:
					player->setSoundBullet(CResourcesManager::GetInstance()->sound_bullet_l);
					weapon->SetWaeponType(WPL);
					break;
				case ItemB:
					break;
				case ItemS:
					player->setSoundBullet(CResourcesManager::GetInstance()->sound_bullet_s);
					weapon->SetWaeponType(WPS);
					break;
				}

				item->_physical.SetBounds(0, 0, 0, 0);
				item->_enable = false;
			}
		}

		//Xét va chạm với đạn người chơi
		if (item->_hp > 0)
		{
			if (weapon->CheckCollision(item) != NoCollision)
			{
				item->_hp--;
			}
		}


	}
}

CObject *CListItemFly::getObjectTrust(CObject *x)
{
	float posX = x->getPosX() + x->getWidth() / 2;
	float posY = x->getPosY() - x->getHeight() / 2;
	
	switch (x->getSpecificType())
	{
		case ItemM:
		case ItemF:
		case ItemB:
		case ItemL:
		case ItemR:
		case ItemS:
			return new CItemFly(x->_id, x->getSpecificType(), D3DXVECTOR3(posX, posY, 0), x->getTrack(), x->getWidth(), x->getHeight());
	}
}

void CListItemFly::setActivity(CObject *x)
{
	if (x->_physical.bounds.left == 0 &&
		x->_physical.bounds.right == 0 &&
		x->_physical.bounds.top == 0 &&
		x->_physical.bounds.bottom == 0) return;

	CCamera *cam = CResourcesManager::GetInstance()->_camera;
	float posX = x->getPosX();
	float posY = x->getPosY();

	switch (x->getTrack())
	{
	case Track_LR:
		if (posX + x->getWidth() / 2 > CResourcesManager::GetInstance()->m_widthMap && x->getEnable())
		{
			x->setEnable(false);
		}
		if (posX + x->getWidth() / 2 < cam->getPosX())
		{
			x->setEnable(true);
		}
		break;
	case Track_RL:
		if (posX - x->getWidth() / 2 < cam->getPosX() && x->getEnable())
		{
			x->setEnable(false);
		}
		if (posX + x->getWidth() / 2 < cam->getPosX() + cam->getWidth())
		{
			x->setEnable(true);
		}
		break;
	case Track_UD:
		break;
	case Track_DU:
		if (x->getEnable() && posY - x->getHeight() / 2 >  CResourcesManager::GetInstance()->m_heightMap)
		{
			x->setEnable(false);
		}
		if (posY + x->getHeight() / 2 < cam->getPosY() - cam->getHeight())
		{
			x->setEnable(true);
		}
		break;
	default:
		break;
	}

}