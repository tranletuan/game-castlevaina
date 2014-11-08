#include "CMapReader.h"

CMapReader::CMapReader(LPCWSTR map_name)
{
	this->_map_name = map_name;
	this->_object_factory = new CObjectMapFactory();
}

CMapReader::~CMapReader()
{
	delete _object_factory;
	_list_object.clear();
}

void CMapReader::LoadResources()
{
	CResourcesManager* rs = CResourcesManager::GetInstance();
	CCamera* c = rs->_camera;
	_map_type = rs->_map_type;

	wstring folder_background(MAP_FOLDER); //Thư mục chứa toàn bộ background
	wstring map_name(_map_name);
	wstring full_folder_path(folder_background + map_name + L"/"); //Đường dẫn full đến background

	wstring file_object(full_folder_path + L"object_" + map_name + L".txt");
	wstring file_quadtree(full_folder_path + L"quadtree_" + map_name + L".png");

	
	ifstream infile(file_object);
	infile >> _total_object;

	int id;
	int type;
	float x;
	float y;
	int width;
	int height;

	while (infile >> id >> type >> x >> y >> width >> height)
	{
		SpecificType ptype = (SpecificType)type;
		D3DXVECTOR3 pos = c->Transform(x, y);
		CObject* obj = CreateObject(id, ptype, pos, width, height);

		if (obj != NULL)
		{
			_list_object[id] = obj;
			obj->LoadResources();
		}
	}
	
}

map<int, CObject*> CMapReader::GetListObject()
{
	return _list_object;
}

//Tạo đối tượng mới, tọa độ đã được transform
CObject* CMapReader::CreateObject(int id, SpecificType specific_type, D3DXVECTOR3 pos, int width, int height)
{
	BasicType basic_type = _map_type[specific_type];

	switch (basic_type)
	{
	case Player:
		return _object_factory->GetPlayer(id, specific_type, pos, width, height);
		break;
	case Ground:
		return _object_factory->GetGround(id, specific_type, pos, width, height);
		break;
	}
}