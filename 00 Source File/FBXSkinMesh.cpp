/**
* @file FBXSkinMesh.cpp
* @brief FBXスキンメッシュクラス実装ファイル
* @author Ryunosuke Honda.
*/
#include "FBXSkinMesh.h"
#include <stdlib.h>
#include <d3dx11.h>
#include "Camera.h"

#include "MySkinMaterial.h"
#include "ShaderWorldColor.h"
#include "MySkinVertex.h"
#include "Bone.h"
#include "PolyTable.h"
#include "FBXSkinMeshRenderDesc.h"

FBXSkinMesh::FBXSkinMesh(ID3D11Device* pDevice, CHAR* fileName)
{
	ZeroMemory(this, sizeof(FBXSkinMesh));
	createFromFBX(pDevice, fileName);
}

FBXSkinMesh::~FBXSkinMesh()
{
	delete[] mBoneArray;
	delete[] mpMaterial;
	delete[] mppCluster;
	SAFE_RELEASE(mpVertexBuffer);
	SAFE_RELEASE(mpSampleLinear);
	for (DWORD i = 0; i < mMaterialCount; i++)
	{
		SAFE_RELEASE(mppIndexBuffer[i]);
	}
	delete[] mppIndexBuffer;
	if (mpSdkManager) mpSdkManager->Destroy();
}

HRESULT FBXSkinMesh::initFBX(CHAR* fileName)
{
	mpSdkManager = FbxManager::Create();

	mpImporter = FbxImporter::Create(mpSdkManager, "my importer");

	int iFormat = -1;
	mpImporter->Initialize((const char*)fileName, iFormat);

	mpmyScene = FbxScene::Create(mpSdkManager, "my scene");

	mpImporter->Import(mpmyScene);

	return S_OK;
}

//
//HRESULT FBXSkinMesh::ReadSkinInfo(FbxMesh* pFbxMesh,MY_SKIN_VERTEX* pvVB,POLY_TABLE* polyTable)
//FBXからスキン関連の情報を読み出す　
HRESULT FBXSkinMesh::readSkinInfo(FbxMesh* pFbxMesh, MySkinVertex* pvVB, PolyTable* PolyTable)
{
	//FBXから抽出すべき情報は、頂点ごとのボーンインデックス、頂点ごとのボーンウェイト、バインド行列、ポーズ行列　の4項目

	int i, k;
	int iNumBone = 0;//ボーン数

	//デフォーマーを得る 
	FbxDeformer* pDeformer = pFbxMesh->GetDeformer(0);
	FbxSkin* pSkinInfo = static_cast<FbxSkin*>(pDeformer);
	//
	//ボーンを得る
	iNumBone = pSkinInfo->GetClusterCount();
	mppCluster = new  FbxCluster*[iNumBone];
	for (i = 0; i < iNumBone; i++)
	{
		mppCluster[i] = pSkinInfo->GetCluster(i);
	}

	//通常の場合　（頂点数＞=UV数　pvVBが頂点インデックスベースの場合）
	if (mdwNumVert >= mdwNumUV)
	{
		//それぞれのボーンに影響を受ける頂点を調べる　そこから逆に、頂点ベースでボーンインデックス・重みを整頓する
		for (i = 0; i < iNumBone; i++)
		{
			int iNumIndex = mppCluster[i]->GetControlPointIndicesCount();//このボーンに影響を受ける頂点数
			int* piIndex = mppCluster[i]->GetControlPointIndices();
			double* pdWeight = mppCluster[i]->GetControlPointWeights();
			//頂点側からインデックスをたどって、頂点サイドで整理する
			for (k = 0; k < iNumIndex; k++)
			{
				for (int m = 0; m < 4; m++)//FBXやCGソフトがボーン4本以内とは限らない。5本以上の場合は、重みの大きい順に4本に絞る 
				{
					if (pdWeight[k] > pvVB[piIndex[k]].bBoneWeight[m])
					{
						pvVB[piIndex[k]].bBoneIndex[m] = i;
						pvVB[piIndex[k]].bBoneWeight[m] = pdWeight[k];
						break;
					}
				}
			}
		}
	}
	//UVインデックスベースの場合　（頂点数<UV数）
	else
	{
		int PolyIndex = 0;
		int UVIndex = 0;
		//それぞれのボーンに影響を受ける頂点を調べる　そこから逆に、頂点ベースでボーンインデックス・重みを整頓する
		for (i = 0; i < iNumBone; i++)
		{
			int iNumIndex = mppCluster[i]->GetControlPointIndicesCount();//このボーンに影響を受ける頂点数
			int* piIndex = mppCluster[i]->GetControlPointIndices();
			double* pdWeight = mppCluster[i]->GetControlPointWeights();
			//頂点側からインデックスをたどって、頂点サイドで整理する
			for (k = 0; k < iNumIndex; k++)
			{
				//その頂点を含んでいるポリゴンすべてに、このボーンとウェイトを適用
				for (int p = 0; p < PolyTable[piIndex[k]].NumRef; p++)
				{
					//頂点→属すポリゴン→そのポリゴンのUVインデックス　と逆引き
					PolyIndex = PolyTable[piIndex[k]].PolyIndex[p];
					UVIndex = pFbxMesh->GetTextureUVIndex(PolyIndex, PolyTable[piIndex[k]].Index123[p], FbxLayerElement::eTextureDiffuse);

					for (int m = 0; m < 4; m++)//FBXやCGソフトがボーン4本以内とは限らない。5本以上の場合は、重みの大きい順に4本に絞る 
					{
						if (pdWeight[k] > pvVB[UVIndex].bBoneWeight[m])
						{
							pvVB[UVIndex].bBoneIndex[m] = i;
							pvVB[UVIndex].bBoneWeight[m] = pdWeight[k];
							break;
						}
					}
				}

			}
		}
	}

	//
	//ボーンを生成
	mBoneCount = iNumBone;
	mBoneArray = new Bone[iNumBone];

	for (i = 0; i < mBoneCount; i++)
	{
		FbxAMatrix mat;
		mppCluster[i]->GetTransformLinkMatrix(mat);

		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				mBoneArray[i].mBindPose(y, x) = mat.Get(y, x);
				mBoneArray[i].mBindPose._11 *= -1;
			}
		}
	}
	return S_OK;
}

HRESULT FBXSkinMesh::createFromFBX(ID3D11Device* pDevice, CHAR* fileName)
{
	//FBXローダーを初期化
	SetVisualDirectory();
	if (FAILED(initFBX(fileName)))
	{
		MessageBox(0, L"FBXローダー初期化失敗", NULL, MB_OK);
		return E_FAIL;
	}

	FbxNode* pNode = mpmyScene->GetRootNode();

	int index = 0;
	FbxNodeAttribute* pAttr = pNode->GetNodeAttribute();
	while (!pAttr || pAttr->GetAttributeType() != FbxNodeAttribute::eMesh)//1メッシュを想定しているので、eMeshが見つかった時点で、それを使う
	{
		pNode = pNode->GetChild(index);
		index++;
		pAttr = pNode->GetNodeAttribute();
	}

	FbxMesh* pFbxMesh = pNode->GetMesh();

	//事前に頂点数、ポリゴン数等を調べる
	mdwNumVert = pFbxMesh->GetControlPointsCount();
	mdwNumUV = pFbxMesh->GetTextureUVCount();
	mdwNumFace = pFbxMesh->GetPolygonCount();
	//一時的なメモリ確保（頂点バッファとインデックスバッファ）
	MySkinVertex* pvVB = NULL;
	mdwNumVert < mdwNumUV ? pvVB = new MySkinVertex[mdwNumUV] : pvVB = new MySkinVertex[mdwNumVert];
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
		pvVB[iIndex0].vPos.x = (float)-coord.mData[0];
		pvVB[iIndex0].vPos.y = (float)coord.mData[1];
		pvVB[iIndex0].vPos.z = (float)coord.mData[2];

		index = pFbxMesh->GetPolygonVertex(i, 1);
		coord = pFbxMesh->GetControlPointAt(index);
		pvVB[iIndex1].vPos.x = (float)-coord.mData[0];
		pvVB[iIndex1].vPos.y = (float)coord.mData[1];
		pvVB[iIndex1].vPos.z = (float)coord.mData[2];

		index = pFbxMesh->GetPolygonVertex(i, 2);
		coord = pFbxMesh->GetControlPointAt(index);
		pvVB[iIndex2].vPos.x = (float)-coord.mData[0];
		pvVB[iIndex2].vPos.y = (float)coord.mData[1];
		pvVB[iIndex2].vPos.z = (float)coord.mData[2];
		//法線
		pFbxMesh->GetPolygonVertexNormal(i, 0, normal);
		pvVB[iIndex0].vNorm.x = -(float)normal[0];
		pvVB[iIndex0].vNorm.y = (float)normal[1];
		pvVB[iIndex0].vNorm.z = (float)normal[2];

		pFbxMesh->GetPolygonVertexNormal(i, 1, normal);
		pvVB[iIndex1].vNorm.x = -(float)normal[0];
		pvVB[iIndex1].vNorm.y = (float)normal[1];
		pvVB[iIndex1].vNorm.z = (float)normal[2];

		pFbxMesh->GetPolygonVertexNormal(i, 2, normal);
		pvVB[iIndex2].vNorm.x = -(float)normal[0];
		pvVB[iIndex2].vNorm.y = (float)normal[1];
		pvVB[iIndex2].vNorm.z = (float)normal[2];
		//テクスチャー座標
		int UVindex = pFbxMesh->GetTextureUVIndex(i, 0, FbxLayerElement::eTextureDiffuse);
		FbxLayerElementUV* pUV = 0;

		FbxLayerElementUV* uv = pFbxMesh->GetLayer(0)->GetUVs();

		if (mdwNumUV && uv->GetMappingMode() == FbxLayerElement::eByPolygonVertex)
		{
			//この取得の仕方は、UVマッピングモードがeByPolygonVertexの時じゃないとできない
			UVindex = pFbxMesh->GetTextureUVIndex(i, 0, FbxLayerElement::eTextureDiffuse);
			pUV = pFbxMesh->GetLayer(0)->GetUVs();
			FbxVector2 v2 = pUV->GetDirectArray().GetAt(UVindex);
			pvVB[iIndex0].vTex.x = v2.mData[0];
			pvVB[iIndex0].vTex.y = 1.0f - v2.mData[1];

			UVindex = pFbxMesh->GetTextureUVIndex(i, 1, FbxLayerElement::eTextureDiffuse);
			v2 = pUV->GetDirectArray().GetAt(UVindex);
			pvVB[iIndex1].vTex.x = v2.mData[0];
			pvVB[iIndex1].vTex.y = 1.0f - v2.mData[1];

			UVindex = pFbxMesh->GetTextureUVIndex(i, 2, FbxLayerElement::eTextureDiffuse);
			v2 = pUV->GetDirectArray().GetAt(UVindex);
			pvVB[iIndex2].vTex.x = v2.mData[0];
			pvVB[iIndex2].vTex.y = 1.0f - v2.mData[1];
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
			pvVB[k].vTex.x = v2.mData[0];
			pvVB[k].vTex.y = 1.0f - v2.mData[1];
		}
	}

	//マテリアル読み込み
	pNode = pFbxMesh->GetNode();
	mMaterialCount = pNode->GetMaterialCount();

	mpMaterial = new MySkinMaterial[mMaterialCount];

	//マテリアルの数だけインデックスバッファーを作成
	mppIndexBuffer = new ID3D11Buffer*[mMaterialCount];

	for (DWORD i = 0; i < mMaterialCount; i++)
	{
		//フォンモデルを想定
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);
		FbxSurfacePhong* pPhong = (FbxSurfacePhong*)pMaterial;

		//環境光
		FbxDouble3 d3Ambient = pPhong->Ambient;
		mpMaterial[i].Ka.r = (float)d3Ambient.mData[0];
		mpMaterial[i].Ka.g = (float)d3Ambient.mData[1];
		mpMaterial[i].Ka.b = (float)d3Ambient.mData[2];
		mpMaterial[i].Ka.a = 1;
		//拡散反射光
		FbxDouble3 d3Diffuse = pPhong->Diffuse;
		mpMaterial[i].Kd.r = (float)d3Diffuse.mData[0];
		mpMaterial[i].Kd.g = (float)d3Diffuse.mData[1];
		mpMaterial[i].Kd.b = (float)d3Diffuse.mData[2];
		mpMaterial[i].Kd.a = 1;
		//鏡面反射光
		FbxDouble3 d3Specular = pPhong->Diffuse;
		mpMaterial[i].Ks.r = (float)d3Specular.mData[0];
		mpMaterial[i].Ks.g = (float)d3Specular.mData[1];
		mpMaterial[i].Ks.b = (float)d3Specular.mData[2];
		mpMaterial[i].Ks.a = 1;
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
				_splitpath(mpMaterial[i].szTextureName, 0, 0, mpMaterial[i].szTextureName, ext);
				//_splitpath_s(mpMaterial[i].szTextureName, 0, 0,0,0,mpMaterial[i].szTextureName,sizeof(mpMaterial[i].szTextureName),ext,sizeof(ext) );
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
		if (iCount > 0) createIndexBuffer(pDevice, iCount * sizeof(int), pIndex, &mppIndexBuffer[i]);
		mpMaterial[i].dwNumFace = iCount / 3;//そのマテリアル内のポリゴン数		
		delete[] pIndex;
	}

	//頂点からポリゴンを逆引きしたいので、逆引きテーブルを作る 
	PolyTable* polyTable = new PolyTable[mdwNumVert];

	for (DWORD i = 0; i < mdwNumVert; i++)
	{
		for (DWORD k = 0; k < mdwNumFace; k++)
		{
			for (int m = 0; m < 3; m++)
			{
				if (pFbxMesh->GetPolygonVertex(k, m) == i)
				{
					polyTable[i].PolyIndex[polyTable[i].NumRef] = k;
					polyTable[i].Index123[polyTable[i].NumRef] = m;
					polyTable[i].NumRef++;
				}
			}
		}
	}

	//スキン情報（ジョイント、ウェイト　）読み込み
	readSkinInfo(pFbxMesh, pvVB, polyTable);

	//バーテックスバッファーを作成
	if (mdwNumVert < mdwNumUV) mdwNumVert = mdwNumUV;
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(MySkinVertex) *mdwNumVert;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = pvVB;
	if (FAILED(pDevice->CreateBuffer(&bd, &InitData, &mpVertexBuffer)))
		return FALSE;

	//一時的な入れ物は、もはや不要
	delete[] pvVB;

	//テクスチャー用サンプラー作成
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));

	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	pDevice->CreateSamplerState(&SamDesc, &mpSampleLinear);

	return S_OK;
}

HRESULT FBXSkinMesh::createIndexBuffer(ID3D11Device* pDevice, DWORD dwSize, int* pIndex, ID3D11Buffer** ppIndexBuffer)
{
	//Direct3D11& d3D = singleton<Direct3D11>::get_instance();
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
		return FALSE;
	}

	return S_OK;
}
//
//void FBXSkinMesh::SetNewPoseMatrices(int frame)
//ボーンを次のポーズ位置にセットする
void FBXSkinMesh::setNewPoseMatrices(int frame)
{
	Matrix4x4 m(-1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	int i;
	FbxTime time;
	time.SetTime(0, 0, 0, frame, 0, FbxTime::eFrames30);//30フレーム/秒　と推定　厳密には状況ごとに調べる必要あり

	for (i = 0; i < mBoneCount; i++)
	{
		FbxMatrix mat = mppCluster[i]->GetLink()->EvaluateGlobalTransform(time);

		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				mBoneArray[i].mNewPose(y, x) = mat.Get(y, x);
			}
		}
		mBoneArray[i].mNewPose *= m;//FBX右手座標系なのでｘが逆　補正する
	}
}
//
//Matrix4x4 FBXSkinMesh::GetCurrentPoseMatrix(int index)
//次の（現在の）ポーズ行列を返す
Matrix4x4 FBXSkinMesh::getCurrentPoseMatrix(int index)
{
	Matrix4x4 inv;
	D3DXMatrixInverse(&inv, 0, &mBoneArray[index].mBindPose);//FBXのバインドポーズは初期姿勢（絶対座標）
	Matrix4x4 ret = inv*mBoneArray[index].mNewPose;//バインドポーズの逆行列とフレーム姿勢行列をかける。なお、バインドポーズ自体が既に逆行列であるとする考えもある。（FBXの場合は違うが）

	return ret;
}

void FBXSkinMesh::render(ID3D11DeviceContext* pDeviceContext, ID3D11Buffer* pConstantBuffer, const Camera* pCamera, const FBXSkinMeshRenderDesc* pDesc)
{
	//バーテックスバッファーをセット（バーテックスバッファーは一つでいい）
	UINT stride = sizeof(MySkinVertex);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);

	//マテリアルの数だけ、それぞれのマテリアルのインデックスバッファ－を描画
	for (DWORD i = 0; i < mMaterialCount; i++)
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
		Matrix4x4 world;
		pDesc->mpTransform->makeWorld(&world);
		//ワールド・ビュー・プロジェクション行列をシェーダーに渡す
		//ディフューズカラーをシェーダーに渡す
		//スペキュラーをシェーダーに渡す
		//スペキュラーのパワーをシェーダーに渡す
		//アンビエントをシェーダーに渡す
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(pDeviceContext->Map(pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			ShaderWorldColor sg;
			sg.mW = world;
			D3DXMatrixTranspose(&sg.mW, &sg.mW);
			sg.mWVP = world * pCamera->getView() * pCamera->getProj();
			D3DXMatrixTranspose(&sg.mWVP, &sg.mWVP);
			sg.ambient = mpMaterial[i].Ka + pDesc->mAmbient;
			sg.diffuse = mpMaterial[i].Kd + pDesc->mDiffuse;
			sg.diffuse.a = pDesc->mDiffuse.a;
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