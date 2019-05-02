/**
* @file OBJStaticMeshID.h
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
class OBJStaticMeshID
{
public:
	/*******************************
	使用するIDはここにまとめる
	********************************/
	ENUM(OBJ_STATIC_ID,
		field,
		bullet
	)

	OBJStaticMeshID::OBJ_STATIC_ID::type LoadID(string& key) {
		if (OBJ_STATIC_ID.converter.find(key) != OBJ_STATIC_ID.converter.end()) {
			return OBJ_STATIC_ID.converter[key];
		}
		else
		{
			cout << "OBJStaticMeshID [ " << key.c_str() << " ] is not found." << endl;
		}
	}

};

using OBJMeshID = OBJStaticMeshID::OBJ_STATIC_ID::type;

/****** End of File *****************************************************/
