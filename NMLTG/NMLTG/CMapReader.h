#ifndef _CMAP_READER_H_
#define _CMAP_READER_H_

#include <fstream>
#include <string>
#include <map>
#include <Windows.h>
#include "CObjectMapFactory.h"

class CMapReader
{
protected:
	LPCWSTR _map_name;
	map<int, CObject*> _list_object;
	map<SpecificType, BasicType> _map_type;
	CObjectMapFactory* _object_factory;
	CObject* CreateObject(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height);
	int _total_object;
	

public:
	CMapReader(LPCWSTR map_name);
	~CMapReader();

	void LoadResources();
	map<int, CObject*> GetListObject();
	


};
#endif // !_CMAP_READER_H_
