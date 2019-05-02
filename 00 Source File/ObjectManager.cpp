/**
* @file ObjectManager.cpp
* @brief IObject管理クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "ObjectManager.h"

#include "IObject.h"
#include "EntityVisitorMemFun1.h"

ObjectManager::ObjectManager():
	mObjList()
{
}

ObjectManager::~ObjectManager()
{
	clear();
}

void ObjectManager::add(IObject * pObj)
{
	mObjList.add(pObj);
}

void ObjectManager::draw(IRenderer & renderer)
{
	EntityVisitorMemFun1<IObject, IRenderer&, &IObject::draw> draw(renderer);
	mObjList.accept(draw);
}

void ObjectManager::clear()
{
	mObjList.clear();
}

/* End of File *****************************************************/