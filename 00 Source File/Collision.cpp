/**
* @file Collision.cpp
* @brief 当たり判定クラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "Collision.h"

#include "SphereCollider.h"
#include "PlaneCollider.h"

#include "SphereXSphereJudge.h"

Collision::Collision():
	Singleton<Collision>(),
	mpDevice(nullptr),
	mpDeviceContext(nullptr),
	mpSphXSph(nullptr)
{
}

Collision::~Collision()
{
}

void Collision::init(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
{
	mpDevice = pDevice;
	mpDeviceContext = pDeviceContext;

	mpSphXSph = new SphereXSphereJudge(pDevice, pDeviceContext);
}

void Collision::collision(SphereCollider * sph1, SphereCollider * sph2)
{
	mpSphXSph->judge(mpDevice, mpDeviceContext, sph1, sph2);
}

void Collision::collision(SphereCollider * sph, PlaneCollider * pln)
{
	Vector3 normal = -pln->Up;
	float L = D3DXVec3Dot(&(sph->Position - pln->Position), &(-normal)) - sph->Radius;

	//距離が半径より大きければ衝突していない
	if (L >= 0)
	{
		sph->result(pln, false);
		pln->result(sph, false);
		return;
	}

	//押し戻し
	sph->Position += L * normal;

	sph->Pt = sph->Position + sph->Radius * normal;

	//剛体衝突運動の計算
	//重心から衝突点のベクトル、接線方向のベクトル
	Vector3 vRg = (sph->Pt - sph->Position);

	//回転速度分(接線方向速度)を並進運動に加える
	Vector3 vp;
	D3DXVec3Cross(&vp, &sph->Omega, &vRg);
	vp += sph->Vel;

	//作用線の直行ベクトル t = n × (vp × n)
	Vector3 vp_n;
	D3DXVec3Cross(&vp_n, &vp, &normal);
	Vector3 tangent;
	D3DXVec3Cross(&tangent, &normal, &vp_n);

	//力積 -(e+1)n・vp*m
	float J = -(sph->E + 1) * (D3DXVec3Dot(&normal, &vp)) * sph->Mass;

	//並進運動
	sph->Force += J * normal;// / dt;

	//回転を受ける力積(地面と平行な方向の力積)
	Vector3 Rg_t;
	D3DXVec3Cross(&Rg_t, &vRg, &tangent);
	D3DXVec3Cross(&Rg_t, &Rg_t, &vRg);// *sph->InverseInertia;
	float B = -D3DXVec3Dot(&tangent, &vp) / (1 / sph->Mass + D3DXVec3Dot(&tangent, &Rg_t));

	//摩擦係数
	if (sph->UK >= abs(B / J))
	{
		//滑らず転がる場合に受ける力
		sph->Force += tangent * B;
		Vector3 tmp;
		D3DXVec3Cross(&tmp, &vRg, &tangent);
		sph->Torque += tmp * B;
	}
	else
	{
		//滑りながら転がる場合に受ける力
		sph->Force += tangent * J * sph->UK;
		Vector3 tmp;
		D3DXVec3Cross(&tmp, &vRg, &tangent);
		sph->Torque += tmp * J * sph->UK;
	}

	//衝突結果を登録
	sph->result(pln, true);
	pln->result(sph, true);
}

void Collision::collision(PlaneCollider * pln1, PlaneCollider * pln2)
{

}

/* End of File *****************************************************/