#pragma once

#include <stdint.h>
#include <Novice.h>

/// <summary>
/// 背景クラス
/// </summary>
class Background
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	//! 一番後ろの背景
	uint32_t _mostBackBuildingSprite; // 画像
	float _mostBackBuildingPos1;		 // 位置1
	float _mostBackBuildingPos2;		 // 位置2
	float _mostBackBuildingSpeed;     // 速度

	//!  後ろの背景
	uint32_t _backBuildingSprite; // 画像
	float _backBuildingPos1;		 // 位置1
	float _backBuildingPos2;		 // 位置2
	float _backBuildingSpeed;    // 速度

	//!  前の背景
	uint32_t _frontBuildingSprite; // 画像
	float _frontBuildingPos1;		 // 位置1
	float _frontBuildingPos2;		 // 位置2
	float _frontBuildingSpeed;    // 速度

	//!  グラデーション
	uint32_t _guradationSprite; // 画像
};

