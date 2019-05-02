/**
* @file FBXMesh.cpp
* @brief FBX(スタティック)メッシュクラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "FBXMesh.h"
#include <stdlib.h>
#include <d3dx11.h>
#include "Camera.h"
#include "ShaderWorldColor.h"
#include "Fbx_Material.h"
#include "Fbx_Vertex.h"
#include "FBXHierarchyMeshRenderDesc.h"

//
//
//
FBXMesh::FBXMesh()
{
	ZeroMemory(this, sizeof(FBXMesh));
	D3DXMatrixIdentity(&mmFBXOrientation);
}

//
//
//
FBXMesh::~FBXMesh()
{
	delete[] mpMaterial;
	SAFE_RELEASE(mpVertexBuffer);
	for (DWORD i = 0; i < mdwNumMaterial; i++)
	{
		SAFE_RELEASE(mppIndexBuffer[i]);
	}
	delete[] mppIndexBuffer;
	delete[] mppChild;
}
//
//
//素材（FBX)のほうは、三角ポリゴンにすること
HRESULT FBXMesh::createFromFBX(ID3D11Device* pDevice, FbxMesh* pFbxMesh)
{
	//事前に頂点数、ポリゴン数等を調べる
	mdwNumVert = pFbxMesh->GetControlPointsCount();
	mdwNumUV = pFbxMesh->GetTextureUVCount();
	mdwNumFace = pFbxMesh->GetPolygonCount();
	//一時的なメモリ確保（頂点バッファとインデックスバッファ）
	Fbx_Vertex* pvVB = NULL;
	mdwNumVert < mdwNumUV ? pvVB = new Fbx_Vertex[mdwNumUV] : pvVB = new Fbx_Vertex[mdwNumVert];
	////ポリゴンごとに　頂点読み込み 、法線読み込み、UV読み込み
	FbxVector4 normal;
	for (DWORD i = 0; i < mdwNumFace; i++)
	{
		int iIndex0 = 0;
		int iIndex1 = 0;
		int iIndex2 = 0;

		int iStartIndex = pFbxMesh->GetPolygonVertexIndex(i);
		int* piIndex = pFbxMesh->GetPolygonVertices();//（頂点インデックス）読み込み
		iIndex0 = piIndex[iStartIndex];
		iIndex1 = piIndex[iStartIndex + 1];
		iIndex2 = piIndex[iStartIndex + 2];
		if (mdwNumVert < mdwNumUV)//UV数のほうが多い場合は本来の（頂点ベース）インデックスを利用しない。UVインデックスを基準にする
		{
			iIndex0 = pFbxMesh->GetTextureUVIndex(i, 0, FbxLayerElement::eTextureDiffuse);
			iIndex1 = pFbxMesh->GetTextureUVIndex(i, 1, FbxLayerElement::eTextureDiffuse);
			iIndex2 = pFbxMesh->GetTextureUVIndex(i, 2, FbxLayerElement::eTextureDiffuse);
		}
		//頂点
		int index = pFbxMesh->GetPolygonVertex(i, 0);
		FbxVector4 coord = pFbxMesh->GetControlPointAt(index);
		pvVB[iIndex0].vPos.x = (float)-coord.mData[0];//FBXは右手座標系なのでxあるいはｚを反転
		pvVB[iIndex0].vPos.y = (float)coord.mData[1];
		pvVB[iIndex0].vPos.z = (float)coord.mData[2];

		index = pFbxMesh->GetPolygonVertex(i, 1);
		coord = pFbxMesh->GetControlPointAt(index);
		pvVB[iIndex1].vPos.x = (float)-coord.mData[0];//FBXは右手座標系なのでxあるいはｚを反転
		pvVB[iIndex1].vPos.y = (float)coord.mData[1];
		pvVB[iIndex1].vPos.z = (float)coord.mData[2];

		index = pFbxMesh->GetPolygonVertex(i, 2);
		coord = pFbxMesh->GetControlPointAt(index);
		pvVB[iIndex2].vPos.x = (float)-coord.mData[0];//FBXは右手座標系なのでxあるいはｚを反転
		pvVB[iIndex2].vPos.y = (float)coord.mData[1];
		pvVB[iIndex2].vPos.z = (float)coord.mData[2];
		//法線		
		pFbxMesh->GetPolygonVertexNormal(i, 0, normal);
		pvVB[iIndex0].vNorm.x = -(float)normal[0];//FBXは右手座標系なのでxあるいはｚを反転
		pvVB[iIndex0].vNorm.y = (float)normal[1];
		pvVB[iIndex0].vNorm.z = (float)normal[2];

		pFbxMesh->GetPolygonVertexNormal(i, 1, normal);
		pvVB[iIndex1].vNorm.x = -(float)normal[0];//FBXは右手座標系なのでxあるいはｚを反転
		pvVB[iIndex1].vNorm.y = (float)normal[1];
		pvVB[iIndex1].vNorm.z = (float)normal[2];

		pFbxMesh->GetPolygonVertexNormal(i, 2, normal);
		pvVB[iIndex2].vNorm.x = -(float)normal[0];//FBXは右手座標系なのでxあるいはｚを反転
		pvVB[iIndex2].vNorm.y = (float)normal[1];
		pvVB[iIndex2].vNorm.z = (float)normal[2];
		//テクスチャー座標
		int UVindex = pFbxMesh->GetTextureUVIndex(i, 0, FbxLayerElement::eTextureDiffuse);
		FbxLayerElementUV* pUV = 0;

		FbxLayerElementUV* uv = pFbxMesh->GetLayer(0)->GetUVs();

		if (mdwNumUV && uv->GetMappingMode() == FbxLayerElement::eByPolygonVertex)
		{
			//この取得の仕方は、UVマッピングモードがeBY_POLYGON_VERTEXの時じゃないとできない
			UVindex = pFbxMesh->GetTextureUVIndex(i, 0, FbxLayerElement::eTextureDiffuse);
			pUV = pFbxMesh->GetLayer(0)->GetUVs();
			FbxVector2 v2 = pUV->GetDirectArray().GetAt(UVindex);
			pvVB[iIndex0].vTex.x = (float)v2.mData[0];
			pvVB[iIndex0].vTex.y = 1.0f - (float)v2.mData[1];

			UVindex = pFbxMesh->GetTextureUVIndex(i, 1, FbxLayerElement::eTextureDiffuse);
			v2 = pUV->GetDirectArray().GetAt(UVindex);
			pvVB[iIndex1].vTex.x = (float)v2.mData[0];
			pvVB[iIndex1].vTex.y = 1.0f - (float)v2.mData[1];

			UVindex = pFbxMesh->GetTextureUVIndex(i, 2, FbxLayerElement::eTextureDiffuse);
			v2 = pUV->GetDirectArray().GetAt(UVindex);
			pvVB[iIndex2].vTex.x = (float)v2.mData[0];
			pvVB[iIndex2].vTex.y = 1.0f - (float)v2.mData[1];
		}
	}

	FbxLayerElementUV* uv = pFbxMesh->GetLayer(0)->GetUVs();
	if (mdwNumUV && uv->GetMappingMode() == FbxLayerElement::eByControlPoint)
	{
		FbxLayerElementUV* pUV = pFbxMesh->GetLayer(0)->GetUVs();
		for (DWORD k = 0; k < mdwNumUV; k++)
		{
			FbxVector2 v2;
			v2 = pUV->GetDirectArray().GetAt(k);
			pvVB[k].vTex.x = (float)v2.mData[0];
			pvVB[k].vTex.y = 1.0f - (float)v2.mData[1];
		}
	}

	//マテリアル読み込み
	FbxNode* pNode = pFbxMesh->GetNode();
	mdwNumMaterial = pNode->GetMaterialCount();

	mpMaterial = new Fbx_Material[mdwNumMaterial];

	//マテリアルの数だけインデックスバッファーを作成
	mppIndexBuffer = new ID3D11Buffer*[mdwNumMaterial];

	for (DWORD i = 0; i < mdwNumMaterial; i++)
	{
		//フォンモデルを想定
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);
		FbxSurfacePhong* pPhong = (FbxSurfacePhong*)pMaterial;

		//環境光
		FbxDouble3 d3Ambient = pPhong->Ambient;
		mpMaterial[i].Ka.x = (float)d3Ambient.mData[0];
		mpMaterial[i].Ka.y = (float)d3Ambient.mData[1];
		mpMaterial[i].Ka.z = (float)d3Ambient.mData[2];
		//拡散反射光
		FbxDouble3 d3Diffuse = pPhong->Diffuse;
		mpMaterial[i].Kd.x = (float)d3Diffuse.mData[0];
		mpMaterial[i].Kd.y = (float)d3Diffuse.mData[1];
		mpMaterial[i].Kd.z = (float)d3Diffuse.mData[2];
		//鏡面反射光
		FbxDouble3 d3Specular = pPhong->Specular;
		mpMaterial[i].Ks.x = (float)d3Specular.mData[0];
		mpMaterial[i].Ks.y = (float)d3Specular.mData[1];
		mpMaterial[i].Ks.z = (float)d3Specular.mData[2];
		//テクスチャー（ディフューズテクスチャーのみ）
		FbxProperty lProperty;
		lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
		FbxTexture* texture = FbxCast<FbxTexture>(lProperty.GetSrcObject(0));
		if (texture)
		{
			strcpy_s(mpMaterial[i].szTextureName, texture->GetName());
			//テクスチャーを作成
			if (FAILED(D3DX11CreateShaderResourceViewFromFileA(pDevice, mpMaterial[i].szTextureName, NULL, NULL, &mpMaterial[i].pTexture, NULL)))//絶対パスファイル名は、まず失敗すると思うが、、、
			{
				char ext[10];
				//_splitpath(mpMaterial[i].szTextureName, 0, 0,mpMaterial[i].szTextureName,ext );
				_splitpath_s(mpMaterial[i].szTextureName, 0, 0, 0, 0, mpMaterial[i].szTextureName, sizeof(mpMaterial[i].szTextureName), ext, sizeof(ext));
				strcat_s(mpMaterial[i].szTextureName, ext);

				if (FAILED(D3DX11CreateShaderResourceViewFromFileA(pDevice, mpMaterial[i].szTextureName, NULL, NULL, &mpMaterial[i].pTexture, NULL)))//ファイル名のみでトライ
				{
					MessageBox(0, L"テクスチャー読み込み失敗", NULL, MB_OK);
					return E_FAIL;
				}
			}
		}
		//マテリアルの数だけインデックスバッファーを作成
		int iCount = 0;
		int* pIndex = new int[mdwNumFace * 3];//とりあえず、メッシュ内のポリゴン数でメモリ確保（個々のポリゴングループはかならずこれ以下になるが）

											   //そのマテリアルであるインデックス配列内の開始インデックスを調べる　さらにインデックスの個数も調べる		
		iCount = 0;
		for (DWORD k = 0; k < mdwNumFace; k++)
		{
			FbxLayerElementMaterial* mat = pFbxMesh->GetLayer(0)->GetMaterials();//レイヤーが1枚だけを想定
			int matId = mat->GetIndexArray().GetAt(k);
			if (matId == i)
			{
				if (mdwNumVert < mdwNumUV)
				{
					pIndex[iCount] = pFbxMesh->GetTextureUVIndex(k, 0, FbxLayerElement::eTextureDiffuse);
					pIndex[iCount + 1] = pFbxMesh->GetTextureUVIndex(k, 1, FbxLayerElement::eTextureDiffuse);
					pIndex[iCount + 2] = pFbxMesh->GetTextureUVIndex(k, 2, FbxLayerElement::eTextureDiffuse);
				}
				else
				{
					pIndex[iCount] = pFbxMesh->GetPolygonVertex(k, 0);
					pIndex[iCount + 1] = pFbxMesh->GetPolygonVertex(k, 1);
					pIndex[iCount + 2] = pFbxMesh->GetPolygonVertex(k, 2);
				}
				iCount += 3;
			}
		}
		createIndexBuffer(pDevice, iCount * sizeof(int), pIndex, &mppIndexBuffer[i]);
		mpMaterial[i].dwNumFace = iCount / 3;//そのマテリアル内のポリゴン数

		delete[] pIndex;
	}
	//バーテックスバッファーを作成
	if (mdwNumVert < mdwNumUV) mdwNumVert = mdwNumUV;
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Fbx_Vertex) *mdwNumVert;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = pvVB;
	if (FAILED(pDevice->CreateBuffer(&bd, &InitData, &mpVertexBuffer)))
		return FALSE;

	//一時的な入れ物は、もはや不要
	delete[] pvVB;

	return S_OK;
}

//
//
//
HRESULT FBXMesh::createIndexBuffer(ID3D11Device* pDevice, DWORD dwSize, int* pIndex, ID3D11Buffer** ppIndexBuffer)
{
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = dwSize;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = pIndex;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	if (FAILED(pDevice->CreateBuffer(&bd, &InitData, ppIndexBuffer)))
	{
		MessageBox(0, L"バッファ作成失敗", NULL, MB_OK);
		return FALSE;
	}

	return S_OK;
}
//
//
//
void FBXMesh::renderMesh(ID3D11DeviceContext* pDeviceContext, ID3D11Buffer* pConstantBuffer, Matrix4x4& world, const Camera* pCamera, const FBXHierarchyMeshRenderDesc * pDesc)
{
	//バーテックスバッファーをセット（バーテックスバッファーは一つでいい）
	UINT stride = sizeof(Fbx_Vertex);
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

		//プリミティブ・トポロジーをセット
		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//マテリアルの各要素と変換行列をシェーダーに渡す

		//ワールド行列をシェーダーに渡す
		//ワールド・ビュー・プロジェクション行列をシェーダーに渡す
		//ディフューズカラーをシェーダーに渡す
		//スペキュラーをシェーダーに渡す
		//スペキュラーのパワーをシェーダーに渡す
		//アンビエントをシェーダーに渡す
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(pDeviceContext->Map(pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			ShaderWorldColor sg;
			sg.mW = mmFinalWorld;
			D3DXMatrixTranspose(&sg.mW, &sg.mW);
			sg.mWVP = mmFinalWorld * pCamera->getView() * pCamera->getProj();
			D3DXMatrixTranspose(&sg.mWVP, &sg.mWVP);
			sg.ambient = mpMaterial[i].Ka + pDesc->mAmbient;
			sg.diffuse = mpMaterial[i].Kd + pDesc->mDiffuse;
			sg.specular = mpMaterial[i].Ks + pDesc->mSpecular;
			memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(ShaderWorldColor));
			pDeviceContext->Unmap(pConstantBuffer, 0);
		}
		pDeviceContext->VSSetConstantBuffers(1, 1, &pConstantBuffer);
		pDeviceContext->PSSetConstantBuffers(1, 1, &pConstantBuffer);
		//テクスチャーをシェーダーに渡す
		if (mpMaterial[i].szTextureName[0] != NULL)
		{
			pDeviceContext->PSSetSamplers(0, 1, &mpSampleLinear);
			pDeviceContext->PSSetShaderResources(0, 1, &mpMaterial[i].pTexture);
		}
		//Draw
		pDeviceContext->DrawIndexed(mpMaterial[i].dwNumFace * 3, 0, 0);

	}
}