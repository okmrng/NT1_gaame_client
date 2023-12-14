#pragma once

#include <stdint.h>
#include <Novice.h>
#include <Background.h>

/// <summary>
/// チュートリアルクラス
/// </summary>
class Tutorial
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 初期化
	/// </summary>
	void Update(char* keys, char* preKeys);

	// ゲッター
	bool GetIsNext() { return _isNext; }

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	//! 押せるようになるまでのフラグ
	bool _isPush;
	int32_t _pushCount;

	//! 画像
	uint32_t _info1;
	uint32_t _info2;
	uint32_t _space;
	uint32_t _spaceStart;
	bool _isInfo1;
	bool _isInfo2;

	//! 次のシーンへ
	bool _isNext;

	//! 背景
	Background* _backgorund = nullptr;
};

