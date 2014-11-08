#include "CObjectMapFactory.h"

CObjectMapFactory::CObjectMapFactory()
{
}

CGround* CObjectMapFactory::GetGround(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
{
	CGround* ground;

	switch (specific_type)
	{
	case GroundBridge:
		ground = new CAutoDestroyBridge(id, specific_type, pos, width, height);
		break;
	default:
		ground = new CGround(id, specific_type, pos, width, height);
		break;
	}

	return ground;
}

CBill* CObjectMapFactory::GetPlayer(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
{
	CBill* bill;

	bill = new CBill(id, specific_type, pos, width, height);

	return bill;
}