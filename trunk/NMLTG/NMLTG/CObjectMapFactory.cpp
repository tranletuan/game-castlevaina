#include "CObjectMapFactory.h"

CObjectMapFactory::CObjectMapFactory()
{
}

CGround* CObjectMapFactory::GetGround(int id, SpecificType specific_type, D3DXVECTOR3 pos)
{
	CGround* ground;

	switch (specific_type)
	{
	case GroundBridge:
		ground = new CAutoDestroyBridge(id, specific_type, pos);
		break;
	default:
		ground = new CGround(id, specific_type, pos);
		break;
	}

	return ground;
}

CBill* CObjectMapFactory::GetPlayer(int id, SpecificType specific_type, D3DXVECTOR3 pos)
{
	CBill* bill;

	bill = new CBill(id, specific_type, pos);

	return bill;
}