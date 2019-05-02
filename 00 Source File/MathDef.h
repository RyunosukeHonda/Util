/**
* @file MathDef.h
* @brief DirectX標準の数学機能のリネームファイル
* @author Ryunosuke Honda.
*/
#pragma once

#include <d3d11.h>
#include <d3dx10.h>

using Vector2 = D3DXVECTOR2;

using Vector3 = D3DXVECTOR3;

using Vector4 = D3DXVECTOR4;

using Color4 = D3DXCOLOR;

using Matrix4x4 = D3DXMATRIX;

using Quaternion = D3DXQUATERNION;

class UVector3 : public Vector3
{
public:
	UVector3() :
		Vector3(0, 0, 0)
	{

	}

	UVector3(float x, float y, float z) :
		Vector3(x, y, z)
	{

	}

	UVector3(Vector3& v) :
		Vector3(v.x, v.y, v.z)
	{

	}

private:
	float X = Vector3::x;
	float Y = Vector3::y;
	float Z = Vector3::z;
public:
	__declspec (property (get = getX)) float x;
	float & getX() { return X; }
	__declspec (property (get = getY)) float y;
	float & getY() { return Y; }
	__declspec (property (get = getZ)) float z;
	float & getZ() { return Z; }

	//float x = Vector3::x;
	//float y = Vector3::y;
	//float z = Vector3::z;
};

/* End of File *****************************************************/