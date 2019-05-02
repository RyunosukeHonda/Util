/**
* @file OBJStaticMesh.cpp
* @brief OBJ�`���̃X�^�e�B�b�N���b�V���N���X�����t�@�C��
* @author Ryunosuke Honda.
*/
#include "OBJStaticMesh.h"
#include "MyVertex.h"
#include "MyMaterial.h"
#include "ColorConstantBuffer.h"
#include "Camera.h"
#include "OBJStaticMeshRenderDesc.h"
#include <D3DX11.h>

//
//
//
OBJStaticMesh::OBJStaticMesh(ID3D11Device* pDevice, LPSTR FileName)
{
	ZeroMemory(this, sizeof(OBJStaticMesh));
	InitStaticMesh(pDevice, FileName);
}
//
//
//
OBJStaticMesh::~OBJStaticMesh()
{
	SAFE_RELEASE(mpVertexBuffer);
	SAFE_DELETE_ARRAY(mpMaterial);
	for (int i = 0; i < mdwNumMaterial; i++) SAFE_RELEASE(mppIndexBuffer[i]);
	SAFE_DELETE(mpvVertexBuffer);
	SAFE_RELEASE(mpSampleLinear);
}
//
//
//�}�e���A���t�@�C����ǂݍ��ފ֐�
HRESULT OBJStaticMesh::LoadMaterialFromFile(ID3D11Device* pDevice, LPSTR FileName, MyMaterial** ppMaterial, DWORD* pdwNUmMaterial)
{
	//�}�e���A���t�@�C�����J���ē��e��ǂݍ���
	FILE* fp = NULL;
	fopen_s(&fp, FileName, "rt");
	char key[100] = { 0 };
	Color4 c(0, 0, 0, 1);

	//�}�e���A�����𒲂ׂ�
	DWORD dwNumMaterial = 0;
	while (!feof(fp))
	{
		//�L�[���[�h�ǂݍ���
		fscanf_s(fp, "%s ", key, sizeof(key));
		//�}�e���A����
		if (strcmp(key, "newmtl") == 0)
		{
			dwNumMaterial++;
		}
	}
	MyMaterial* pMaterial = new MyMaterial[dwNumMaterial];
	//�{�ǂݍ���
	fseek(fp, SEEK_SET, 0);
	INT iMCount = -1;

	while (!feof(fp))
	{
		//�L�[���[�h�ǂݍ���
		fscanf_s(fp, "%s ", key, sizeof(key));
		//�}�e���A����
		if (strcmp(key, "newmtl") == 0)
		{
			iMCount++;
			fscanf_s(fp, "%s ", key, sizeof(key));
			strcpy_s(pMaterial[iMCount].szName, key);
		}
		//Ka�@�A���r�G���g
		if (strcmp(key, "Ka") == 0)
		{
			fscanf_s(fp, "%f %f %f", &c.r, &c.g, &c.b);
			pMaterial[iMCount].Ka = c;
		}
		//Kd�@�f�B�t���[�Y
		if (strcmp(key, "Kd") == 0)
		{
			fscanf_s(fp, "%f %f %f", &c.r, &c.g, &c.b);
			pMaterial[iMCount].Kd = c;
		}
		//Ks�@�X�y�L�����[
		if (strcmp(key, "Ks") == 0)
		{
			fscanf_s(fp, "%f %f %f", &c.r, &c.g, &c.b);
			pMaterial[iMCount].Ks = c;
		}
		//map_Kd�@�e�N�X�`���[
		if (strcmp(key, "map_Kd") == 0)
		{
			fscanf_s(fp, "%s", &pMaterial[iMCount].szTextureName, sizeof(pMaterial[iMCount].szTextureName));
			//�e�N�X�`���[���쐬
			if (FAILED(D3DX11CreateShaderResourceViewFromFileA(pDevice, pMaterial[iMCount].szTextureName, NULL, NULL, &pMaterial[iMCount].pTexture, NULL)))
			{
				return E_FAIL;
			}
		}
	}
	fclose(fp);

	*ppMaterial = pMaterial;
	*pdwNUmMaterial = dwNumMaterial;

	return S_OK;
}
//
//
//
HRESULT OBJStaticMesh::InitStaticMesh(ID3D11Device* pDevice, LPSTR FileName)
{
	float x, y, z;
	int v1 = 0, v2 = 0, v3 = 0;
	int vn1 = 0, vn2 = 0, vn3 = 0;
	int vt1 = 0, vt2 = 0, vt3 = 0;
	DWORD dwVCount = 0;//�ǂݍ��݃J�E���^�[
	DWORD dwVNCount = 0;//�ǂݍ��݃J�E���^�[
	DWORD dwVTCount = 0;//�ǂݍ��݃J�E���^�[
	DWORD dwFCount = 0;//�ǂݍ��݃J�E���^�[
	DWORD dwNumVert = 0;
	DWORD dwNumFace = 0;

	char key[200] = { 0 };
	//OBJ�t�@�C�����J���ē��e��ǂݍ���
	SetVisualDirectory();
	FILE* fp = NULL;
	fopen_s(&fp, FileName, "rt");

	//���O�ɒ��_���A�|���S�����𒲂ׂ�
	while (!feof(fp))
	{
		//�L�[���[�h�ǂݍ���
		fscanf_s(fp, "%s ", key, sizeof(key));
		//�}�e���A���ǂݍ���
		if (strcmp(key, "mtllib") == 0)
		{
			fscanf_s(fp, "%s ", key, sizeof(key));
			LoadMaterialFromFile(pDevice, key, &mpMaterial, &mdwNumMaterial);
		}
		//���_
		if (strcmp(key, "v") == 0)
		{
			dwNumVert++;
		}
		//�@��
		if (strcmp(key, "vn") == 0)
		{
			dwVNCount++;
		}
		//�e�N�X�`���[���W
		if (strcmp(key, "vt") == 0)
		{
			dwVTCount++;
		}
		//�t�F�C�X�i�|���S���j
		if (strcmp(key, "f") == 0)
		{
			dwNumFace++;
		}
	}

	mpvVertexBuffer = new MyVertex[dwNumVert];
	//�ꎞ�I�ȃ������m�ہi���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�j	
	Vector3* pvCoord = new Vector3[dwNumVert];
	Vector3* pvNormal = new Vector3[dwVNCount];
	Vector2* pvTexture = new Vector2[dwVTCount];

	//�{�ǂݍ���	
	fseek(fp, SEEK_SET, 0);
	dwVCount = 0;
	dwVNCount = 0;
	dwVTCount = 0;
	dwFCount = 0;

	while (!feof(fp))
	{
		//�L�[���[�h �ǂݍ���
		ZeroMemory(key, sizeof(key));
		fscanf_s(fp, "%s ", key, sizeof(key));

		//���_ �ǂݍ���
		if (strcmp(key, "v") == 0)
		{
			fscanf_s(fp, "%f %f %f", &x, &y, &z);
			pvCoord[dwVCount].x = -x;//OBJ�͉E����W�n�Ȃ̂�x���邢�͂��𔽓]
			pvCoord[dwVCount].y = y;
			pvCoord[dwVCount].z = z;
			dwVCount++;
		}

		//�@�� �ǂݍ���
		if (strcmp(key, "vn") == 0)
		{
			fscanf_s(fp, "%f %f %f", &x, &y, &z);
			pvNormal[dwVNCount].x = -x;//OBJ�͉E����W�n�Ȃ̂�x���邢�͂��𔽓]
			pvNormal[dwVNCount].y = y;
			pvNormal[dwVNCount].z = z;
			dwVNCount++;
		}

		//�e�N�X�`���[���W �ǂݍ���
		if (strcmp(key, "vt") == 0)
		{
			fscanf_s(fp, "%f %f", &x, &y);
			pvTexture[dwVTCount].x = x;
			pvTexture[dwVTCount].y = 1 - y;//OBJ�t�@�C����Y�������t�Ȃ̂ō��킹��
			dwVTCount++;
		}
	}

	//�}�e���A���̐������C���f�b�N�X�o�b�t�@�[���쐬
	mppIndexBuffer = new ID3D11Buffer*[mdwNumMaterial];

	//�t�F�C�X�@�ǂݍ��݁@�o���o���Ɏ��^����Ă���\��������̂ŁA�}�e���A�����𗊂�ɂȂ����킹��
	bool boFlag = false;
	int* piFaceBuffer = new int[dwNumFace * 3];//�R���_�|���S���Ȃ̂ŁA1�t�F�C�X=3���_(3�C���f�b�N�X)
	mppiVertexIndex = new int*[mdwNumMaterial];
	mdwNumFaceInMaterial = new DWORD[mdwNumMaterial];

	//�C���f�b�N�X�o�b�t�@�[�쐬�Ɏg�p
	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA data;
	for (DWORD i = 0; i < mdwNumMaterial; i++)
	{
		fseek(fp, SEEK_SET, 0);
		dwFCount = 0;

		while (!feof(fp))
		{
			//�L�[���[�h �ǂݍ���
			ZeroMemory(key, sizeof(key));
			fscanf_s(fp, "%s ", key, sizeof(key));

			//�t�F�C�X �ǂݍ��݁����_�C���f�b�N�X��
			if (strcmp(key, "usemtl") == 0)
			{
				fscanf_s(fp, "%s ", key, sizeof(key));
				if (strcmp(key, mpMaterial[i].szName) == 0)
				{
					boFlag = true;
				}
				else
				{
					boFlag = false;
				}
			}
			if (strcmp(key, "f") == 0 && boFlag == true)
			{
				if (mpMaterial[i].pTexture != NULL)//�e�N�X�`���[����T�[�t�F�C�X
				{
					fscanf_s(fp, "%d/%d/%d %d/%d/%d %d/%d/%d", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);
				}
				else//�e�N�X�`���[�����T�[�t�F�C�X
				{
					fscanf_s(fp, "%d//%d %d//%d %d//%d", &v1, &vn1, &v2, &vn2, &v3, &vn3);
				}

				piFaceBuffer[dwFCount * 3] = v1 - 1;
				piFaceBuffer[dwFCount * 3 + 1] = v2 - 1;
				piFaceBuffer[dwFCount * 3 + 2] = v3 - 1;
				dwFCount++;
				//���_�\���̂ɑ��
				mpvVertexBuffer[v1 - 1].vPos = pvCoord[v1 - 1];
				mpvVertexBuffer[v1 - 1].vNorm = pvNormal[vn1 - 1];
				mpvVertexBuffer[v1 - 1].vTex = pvTexture[vt1 - 1];
				mpvVertexBuffer[v2 - 1].vPos = pvCoord[v2 - 1];
				mpvVertexBuffer[v2 - 1].vNorm = pvNormal[vn2 - 1];
				mpvVertexBuffer[v2 - 1].vTex = pvTexture[vt2 - 1];
				mpvVertexBuffer[v3 - 1].vPos = pvCoord[v3 - 1];
				mpvVertexBuffer[v3 - 1].vNorm = pvNormal[vn3 - 1];
				mpvVertexBuffer[v3 - 1].vTex = pvTexture[vt3 - 1];
			}
		}
		if (dwFCount == 0)//�g�p����Ă��Ȃ��}�e���A���΍�
		{
			mppIndexBuffer[i] = NULL;
			mdwNumFaceInMaterial[i] = 0;
			continue;
		}

		//�C���f�b�N�X�o�b�t�@�[���쐬
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(int) * dwFCount * 3;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		data.pSysMem = piFaceBuffer;
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;
		if (FAILED(pDevice->CreateBuffer(&bd, &data, &mppIndexBuffer[i])))
			return FALSE;
		mpMaterial[i].dwNumFace = dwFCount;

		//���_�C���f�b�N�X�f�[�^��ۑ����Ă���
		mppiVertexIndex[i] = new int[dwFCount * 3];
		memcpy(mppiVertexIndex[i], piFaceBuffer, sizeof(int)*dwFCount * 3);

		mdwNumFaceInMaterial[i] = dwFCount;
	}

	delete[] piFaceBuffer;
	fclose(fp);

	//�o�[�e�b�N�X�o�b�t�@�[���쐬
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(MyVertex) *dwNumVert;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	data.pSysMem = mpvVertexBuffer;
	if (FAILED(pDevice->CreateBuffer(&bd, &data, &mpVertexBuffer)))
		return FALSE;

	//�ꎞ�I�ȓ��ꕨ�́A���͂�s�v
	delete pvCoord;
	delete pvNormal;
	delete pvTexture;

	//�e�N�X�`���[�p�T���v���[�쐬
	D3D11_SAMPLER_DESC samDesc;
	ZeroMemory(&samDesc, sizeof(D3D11_SAMPLER_DESC));

	samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	pDevice->CreateSamplerState(&samDesc, &mpSampleLinear);

	return S_OK;
}
//
//
//
void OBJStaticMesh::render(ID3D11DeviceContext* pDeviceContext, ID3D11Buffer* mpConstantBuffer1, const OBJStaticMeshRenderDesc* pDesc)
{
	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(MyVertex);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);

	//�}�e���A���̐������A���ꂼ��̃}�e���A���̃C���f�b�N�X�o�b�t�@�|��`��
	for (DWORD i = 0; i < mdwNumMaterial; i++)
	{
		//�g�p����Ă��Ȃ��}�e���A���΍�
		if (mpMaterial[i].dwNumFace == 0)
		{
			continue;
		}

		//�C���f�b�N�X�o�b�t�@�[���Z�b�g
		stride = sizeof(int);
		offset = 0;
		pDeviceContext->IASetIndexBuffer(mppIndexBuffer[i], DXGI_FORMAT_R32_UINT, 0);

		//�}�e���A���̊e�v�f���G�t�F�N�g�i�V�F�[�_�[�j�ɓn��
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer1, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			ColorConstantBuffer cb;
			//�e�N�X�`���[���V�F�[�_�[�ɓn��
			if (mpMaterial[i].szTextureName[0] != NULL)
			{
				pDeviceContext->PSSetSamplers(0, 1, &mpSampleLinear);
				pDeviceContext->PSSetShaderResources(0, 1, &mpMaterial[i].pTexture);
				cb.texture.x = 1;
			}
			else
			{
				cb.texture.x = 0;
			}
			cb.ambient = mpMaterial[i].Ka +pDesc->mAmbient;//�A���r�G���g���V�F�[�_�[�ɓn��
			cb.diffuse = mpMaterial[i].Kd +pDesc->mDiffuse;//�f�B�t���[�Y�J���[���V�F�[�_�[�ɓn��
			cb.diffuse.a = pDesc->mDiffuse.a;//�ȈՓ��ߏ����E�f�B�t���[�Y�F�̃A���t�@�l�œ��߂���
			cb.specular = mpMaterial[i].Ks +pDesc->mSpecular;//�X�y�L�����[���V�F�[�_�[�ɓn��
			memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ColorConstantBuffer));
			pDeviceContext->Unmap(mpConstantBuffer1, 0);
		}
		pDeviceContext->VSSetConstantBuffers(1, 1, &mpConstantBuffer1);
		pDeviceContext->PSSetConstantBuffers(1, 1, &mpConstantBuffer1);

		//�v���~�e�B�u�������_�����O
		pDeviceContext->DrawIndexed(mpMaterial[i].dwNumFace * 3, 0, 0);
	}
}

/****** End of File *****************************************************/

