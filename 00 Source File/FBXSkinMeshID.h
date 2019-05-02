/**
* @file FBXSkinMeshID.h
* @brief OBJ型スタティックメッシュ管理番号列挙型
* @author Ryunosuke Honda.
*/
#pragma once

#include "StringEnumBase.h"
#include <iostream>

using namespace std;

/**
*	OBJモデルID
*/
class FBXSkinMeshID
{
public:
	/*******************************
	使用するIDはここにまとめる
	********************************/
	ENUM(FBX_SKIN_ID,
		player,
		enemy
	)

		FBXSkinMeshID::FBX_SKIN_ID::type LoadID(string& key) {
		if (FBX_SKIN_ID.converter.find(key) != FBX_SKIN_ID.converter.end()) {
			return FBX_SKIN_ID.converter[key];
		}
		else
		{
			cout << "FBXSkinMeshID [ " << key.c_str() << " ] is not found." << endl;
		}
	}

};

using FBXSkinID = FBXSkinMeshID::FBX_SKIN_ID::type;

/****** End of File *****************************************************/
