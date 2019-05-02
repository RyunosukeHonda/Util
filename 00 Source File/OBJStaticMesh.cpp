/**
* @file OBJStaticMesh.cpp
* @brief OBJ形式のスタティックメッシュクラス実装ファイル
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
//マテリアルファイルを読み込む関数
HRESULT OBJStaticMesh::LoadMaterialFromFile(ID3D11Device* pDevice, LPSTR FileName, MyMaterial** ppMaterial, DWORD* pdwNUmMaterial)
{
	//マテリアルファイルを開いて内容を読み込む
	FILE* fp = NULL;
	fopen_s(&fp, FileName, "rt");
	char key[100] = { 0 };
	Color4 c(0, 0, 0, 1);

	//マテリアル数を調べる
	DWORD dwNumMaterial = 0;
	while (!feof(fp))
	{
		//キーワード読み込み
		fscanf_s(fp, "%s ", key, sizeof(key));
		//マテリアル名
		if (strcmp(key, "newmtl") == 0)
		{
			dwNumMaterial++;
		}
	}
	MyMaterial* pMaterial = new MyMaterial[dwNumMaterial];
	//本読み込み
	fseek(fp, SEEK_SET, 0);
	INT iMCount = -1;

	while (!feof(fp))
	{
		//キーワード読み込み
		fscanf_s(fp, "%s ", key, sizeof(key));
		//マテリアル名
		if (strcmp(key, "newmtl") == 0)
		{
			iMCount++;
			fscanf_s(fp, "%s ", key, sizeof(key));
			strcpy_s(pMaterial[iMCount].szName, key);
		}
		//Ka　アンビエント
		if (strcmp(key, "Ka") == 0)
		{
			fscanf_s(fp, "%f %f %f", &c.r, &c.g, &c.b);
			pMaterial[iMCount].Ka = c;
		}
		//Kd　ディフューズ
		if (strcmp(key, "Kd") == 0)
		{
			fscanf_s(fp, "%f %f %f", &c.r, &c.g, &c.b);
			pMaterial[iMCount].Kd = c;
		}
		//Ks　スペキュラー
		if (strcmp(key, "Ks") == 0)
		{
			fscanf_s(fp, "%f %f %f", &c.r, &c.g, &c.b);
			pMaterial[iMCount].Ks = c;
		}
		//map_Kd　テクスチャー
		if (strcmp(key, "map_Kd") == 0)
		{
			fscanf_s(fp, "%s", &pMaterial[iMCount].szTextureName, sizeof(pMaterial[iMCount].szTextureName));
			//テクスチャーを作成
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
	DWORD dwVCount = 0;//読み込みカウンター
	DWORD dwVNCount = 0;//読み込みカウンター
	DWORD dwVTCount = 0;//読み込みカウンター
	DWORD dwFCount = 0;//読み込みカウンター
	DWORD dwNumVert = 0;
	DWORD dwNumFace = 0;

	char key[200] = { 0 };
	//OBJファイルを開いて内容を読み込む
	SetVisualDirectory();
	FILE* fp = NULL;
	fopen_s(&fp, FileName, "rt");

	//事前に頂点数、ポリゴン数を調べる
	while (!feof(fp))
	{
		//キーワード読み込み
		fscanf_s(fp, "%s ", key, sizeof(key));
		//マテリアル読み込み
		if (strcmp(key, "mtllib") == 0)
		{
			fscanf_s(fp, "%s ", key, sizeof(key));
			LoadMaterialFromFile(pDevice, key, &mpMaterial, &mdwNumMaterial);
		}
		//頂点
		if (strcmp(key, "v") == 0)
		{
			dwNumVert++;
		}
		//法線
		if (strcmp(key, "vn") == 0)
		{
			dwVNCount++;
		}
		//テクスチャー座標
		if (strcmp(key, "vt") == 0)
		{
			dwVTCount++;
		}
		//フェイス（ポリゴン）
		if (strcmp(key, "f") == 0)
		{
			dwNumFace++;
		}
	}

	mpvVertexBuffer = new MyVertex[dwNumVert];
	//一時的なメモリ確保（頂点バッファとインデックスバッファ）	
	Vector3* pvCoord = new Vector3[dwNumVert];
	Vector3* pvNormal = new Vector3[dwVNCount];
	Vector2* pvTexture = new Vector2[dwVTCount];

	//本読み込み	
	fseek(fp, SEEK_SET, 0);
	dwVCount = 0;
	dwVNCount = 0;
	dwVTCount = 0;
	dwFCount = 0;

	while (!feof(fp))
	{
		//キーワード 読み込み
		ZeroMemory(key, sizeof(key));
		fscanf_s(fp, "%s ", key, sizeof(key));

		//頂点 読み込み
		if (strcmp(key, "v") == 0)
		{
			fscanf_s(fp, "%f %f %f", &x, &y, &z);
			pvCoord[dwVCount].x = -x;//OBJは右手座標系なのでxあるいはｚを反転
			pvCoord[dwVCount].y = y;
			pvCoord[dwVCount].z = z;
			dwVCount++;
		}

		//法線 読み込み
		if (strcmp(key, "vn") == 0)
		{
			fscanf_s(fp, "%f %f %f", &x, &y, &z);
			pvNormal[dwVNCount].x = -x;//OBJは右手座標系なのでxあるいはｚを反転
			pvNormal[dwVNCount].y = y;
			pvNormal[dwVNCount].z = z;
			dwVNCount++;
		}

		//テクスチャー座標 読み込み
		if (strcmp(key, "vt") == 0)
		{
			fscanf_s(fp, "%f %f", &x, &y);
			pvTexture[dwVTCount].x = x;
			pvTexture[dwVTCount].y = 1 - y;//OBJファイルはY成分が逆なので合わせる
			dwVTCount++;
		}
	}

	//マテリアルの数だけインデックスバッファーを作成
	mppIndexBuffer = new ID3D11Buffer*[mdwNumMaterial];

	//フェイス　読み込み　バラバラに収録されている可能性があるので、マテリアル名を頼りにつなぎ合わせる
	bool boFlag = false;
	int* piFaceBuffer = new int[dwNumFace * 3];//３頂点ポリゴンなので、1フェイス=3頂点(3インデックス)
	mppiVertexIndex = new int*[mdwNumMaterial];
	mdwNumFaceInMaterial = new DWORD[mdwNumMaterial];

	//インデックスバッファー作成に使用
	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA data;
	for (DWORD i = 0; i < mdwNumMaterial; i++)
	{
		fseek(fp, SEEK_SET, 0);
		dwFCount = 0;

		while (!feof(fp))
		{
			//キーワード 読み込み
			ZeroMemory(key, sizeof(key));
			fscanf_s(fp, "%s ", key, sizeof(key));

			//フェイス 読み込み→頂点インデックスに
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
				if (mpMaterial[i].pTexture != NULL)//テクスチャーありサーフェイス
				{
					fscanf_s(fp, "%d/%d/%d %d/%d/%d %d/%d/%d", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);
				}
				else//テクスチャー無しサーフェイス
				{
					fscanf_s(fp, "%d//%d %d//%d %d//%d", &v1, &vn1, &v2, &vn2, &v3, &vn3);
				}

				piFaceBuffer[dwFCount * 3] = v1 - 1;
				piFaceBuffer[dwFCount * 3 + 1] = v2 - 1;
				piFaceBuffer[dwFCount * 3 + 2] = v3 - 1;
				dwFCount++;
				//頂点構造体に代入
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
		if (dwFCount == 0)//使用されていないマテリアル対策
		{
			mppIndexBuffer[i] = NULL;
			mdwNumFaceInMaterial[i] = 0;
			continue;
		}

		//インデックスバッファーを作成
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

		//頂点インデックスデータを保存しておく
		mppiVertexIndex[i] = new int[dwFCount * 3];
		memcpy(mppiVertexIndex[i], piFaceBuffer, sizeof(int)*dwFCount * 3);

		mdwNumFaceInMaterial[i] = dwFCount;
	}

	delete[] piFaceBuffer;
	fclose(fp);

	//バーテックスバッファーを作成
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(MyVertex) *dwNumVert;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	data.pSysMem = mpvVertexBuffer;
	if (FAILED(pDevice->CreateBuffer(&bd, &data, &mpVertexBuffer)))
		return FALSE;

	//一時的な入れ物は、もはや不要
	delete pvCoord;
	delete pvNormal;
	delete pvTexture;

	//テクスチャー用サンプラー作成
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
	//バーテックスバッファーをセット
	UINT stride = sizeof(MyVertex);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);

	//マテリアルの数だけ、それぞれのマテリアルのインデックスバッファ－を描画
	for (DWORD i = 0; i < mdwNumMaterial; i++)
	{
		//使用されていないマテリアル対策
		if (mpMaterial[i].dwNumFace == 0)
		{
			continue;
		}

		//インデックスバッファーをセット
		stride = sizeof(int);
		offset = 0;
		pDeviceContext->IASetIndexBuffer(mppIndexBuffer[i], DXGI_FORMAT_R32_UINT, 0);

		//マテリアルの各要素をエフェクト（シェーダー）に渡す
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(pDeviceContext->Map(mpConstantBuffer1, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			ColorConstantBuffer cb;
			//テクスチャーをシェーダーに渡す
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
			cb.ambient = mpMaterial[i].Ka +pDesc->mAmbient;//アンビエントをシェーダーに渡す
			cb.diffuse = mpMaterial[i].Kd +pDesc->mDiffuse;//ディフューズカラーをシェーダーに渡す
			cb.diffuse.a = pDesc->mDiffuse.a;//簡易透過処理・ディフューズ色のアルファ値で透過する
			cb.specular = mpMaterial[i].Ks +pDesc->mSpecular;//スペキュラーをシェーダーに渡す
			memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ColorConstantBuffer));
			pDeviceContext->Unmap(mpConstantBuffer1, 0);
		}
		pDeviceContext->VSSetConstantBuffers(1, 1, &mpConstantBuffer1);
		pDeviceContext->PSSetConstantBuffers(1, 1, &mpConstantBuffer1);

		//プリミティブをレンダリング
		pDeviceContext->DrawIndexed(mpMaterial[i].dwNumFace * 3, 0, 0);
	}
}

/****** End of File *****************************************************/

