/**
* @file SphereXSphereJudge.h
* @brief 境界球同士の衝突判定クラス定義ファイル
* @author Ryunosuke Honda.
*/
#pragma once

struct ID3D11Device;
struct ID3D11DeviceContext;

class SphereCollider;
struct CSResult;
struct ID3D11ComputeShader;
struct ID3D11Buffer;
struct ID3D11ShaderResourceView;
struct ID3D11UnorderedAccessView;
struct ID3D11Buffer;

/**
*	境界球同士の衝突判定クラス・Collisionクラスでのみ使用される
*/
class SphereXSphereJudge
{
public:
	/**
	 * @fn
	 * コンストラクタ
	 */
	SphereXSphereJudge(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	
	/**
	 * @fn
	 * デストラクタ
	 */
	~SphereXSphereJudge();

	/**
	* @fn
	* 判定実行
	* @param (pDevice) デバイスポインタ
	* @param (pDeviceContext) デバイスコンテキストポインタ
	* @param (sph1) 判定を行う球のポインタ１
	* @param (sph2) 判定を行う球のポインタ２
	*/
	void judge(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, SphereCollider* sph1, SphereCollider* sph2);

private:
	//!判定を行うコンピュートシェーダー
	ID3D11ComputeShader* mpSphereXSphereCS;
	//!球情報送信用コンスタントバッファー
	ID3D11Buffer* mpSphereInfoBuffer;
	//!データ入力用シェーダーリソースビュー(SRV)
	ID3D11ShaderResourceView* mpBufferInputSRV;
	//!結果受取用シェーダーアクセスビュー(UAV)
	ID3D11UnorderedAccessView* mpBufferResultUAV;
	//!結果受取バッファー
	ID3D11Buffer* mpBufferResult;
	//!計算結果構造体・cpp側で使用するのはこれ
	CSResult* mpResult;
};

/* End of File *****************************************************/