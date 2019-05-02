/**
* @file Collision.cpp
* @brief �����蔻��N���X�����t�@�C��
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

	//���������a���傫����ΏՓ˂��Ă��Ȃ�
	if (L >= 0)
	{
		sph->result(pln, false);
		pln->result(sph, false);
		return;
	}

	//�����߂�
	sph->Position += L * normal;

	sph->Pt = sph->Position + sph->Radius * normal;

	//���̏Փˉ^���̌v�Z
	//�d�S����Փ˓_�̃x�N�g���A�ڐ������̃x�N�g��
	Vector3 vRg = (sph->Pt - sph->Position);

	//��]���x��(�ڐ��������x)����i�^���ɉ�����
	Vector3 vp;
	D3DXVec3Cross(&vp, &sph->Omega, &vRg);
	vp += sph->Vel;

	//��p���̒��s�x�N�g�� t = n �~ (vp �~ n)
	Vector3 vp_n;
	D3DXVec3Cross(&vp_n, &vp, &normal);
	Vector3 tangent;
	D3DXVec3Cross(&tangent, &normal, &vp_n);

	//�͐� -(e+1)n�Evp*m
	float J = -(sph->E + 1) * (D3DXVec3Dot(&normal, &vp)) * sph->Mass;

	//���i�^��
	sph->Force += J * normal;// / dt;

	//��]���󂯂�͐�(�n�ʂƕ��s�ȕ����̗͐�)
	Vector3 Rg_t;
	D3DXVec3Cross(&Rg_t, &vRg, &tangent);
	D3DXVec3Cross(&Rg_t, &Rg_t, &vRg);// *sph->InverseInertia;
	float B = -D3DXVec3Dot(&tangent, &vp) / (1 / sph->Mass + D3DXVec3Dot(&tangent, &Rg_t));

	//���C�W��
	if (sph->UK >= abs(B / J))
	{
		//���炸�]����ꍇ�Ɏ󂯂��
		sph->Force += tangent * B;
		Vector3 tmp;
		D3DXVec3Cross(&tmp, &vRg, &tangent);
		sph->Torque += tmp * B;
	}
	else
	{
		//����Ȃ���]����ꍇ�Ɏ󂯂��
		sph->Force += tangent * J * sph->UK;
		Vector3 tmp;
		D3DXVec3Cross(&tmp, &vRg, &tangent);
		sph->Torque += tmp * J * sph->UK;
	}

	//�Փˌ��ʂ�o�^
	sph->result(pln, true);
	pln->result(sph, true);
}

void Collision::collision(PlaneCollider * pln1, PlaneCollider * pln2)
{

}

/* End of File *****************************************************/