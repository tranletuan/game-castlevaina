#include "COBNoneTree.h"

COBNoneTree::COBNoneTree()
{
	LoadResources();
}

COBNoneTree::~COBNoneTree()
{
	
}

void COBNoneTree::LoadResources()
{
	_listObNoneTree = CResourcesManager::GetInstance()->listObNoneTree;
}

void COBNoneTree::Draw()
{
	for (int i = 0; i < _listObNoneTree.size(); i++)
	{
		_listObNoneTree.at(i)->Draw();
	}
}

void COBNoneTree::Update(int delta_time)
{
	for (int i = 0; i < _listObNoneTree.size(); i++)
	{
		_listObNoneTree.at(i)->Update(delta_time);
	}
}