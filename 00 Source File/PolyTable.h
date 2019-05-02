/**
* @file PolyTable.h
* @brief １頂点の共有　最大20ポリゴンまで
* @author Ryunosuke Honda.
*/
#pragma once

#include "Base.h"

/**
*	１頂点の共有　最大20ポリゴンまで
*/
struct PolyTable
{
	/**
	* @fn
	* コンストラクタ
	*/
	PolyTable()
	{
		ZeroMemory(this, sizeof(PolyTable));
	}

	//!ポリゴン番号
	int PolyIndex[20]; 
	//!3つの頂点のうち、何番目か
	int Index123[20];
	//!属しているポリゴン数
	int NumRef;
};

/****** End of File *****************************************************/
