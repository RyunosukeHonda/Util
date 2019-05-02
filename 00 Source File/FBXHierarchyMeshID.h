/**
* @file FBXHierarchyMeshID.h
* @brief FBX�K�w���b�V���Ǘ��ԍ��񋓌^
* @author Ryunosuke Honda.
*/
#pragma once

#include "StringEnumBase.h"
#include <iostream>

using namespace std;

/**
*	���f��ID
*/
class FBXHierarchyMeshID
{
public:
	/*******************************
		�g�p����ID�͂����ɂ܂Ƃ߂�
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
