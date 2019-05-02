/**
* @file FBXHierarchyMeshID.h
* @brief FBX階層メッシュ管理番号列挙型
* @author Ryunosuke Honda.
*/
#pragma once

#include "StringEnumBase.h"
#include <iostream>

using namespace std;

/**
*	モデルID
*/
class FBXHierarchyMeshID
{
public:
	/*******************************
		使用するIDはここにまとめる
	********************************/
	ENUM(FBX_HIERARCHY_ID,
		tank
	)

	FBXHierarchyMeshID::FBX_HIERARCHY_ID::type LoadID(string& key) {
		if (FBX_HIERARCHY_ID.converter.find(key) != FBX_HIERARCHY_ID.converter.end()) {
			return FBX_HIERARCHY_ID.converter[key];
		}
		else
		{
			cout << "FBXHierarchyMeshID [ " << key.c_str() << " ] is not found." << endl;
		}
	}

};

using FBXHierarchyID = FBXHierarchyMeshID::FBX_HIERARCHY_ID::type;

/****** End of File *****************************************************/
