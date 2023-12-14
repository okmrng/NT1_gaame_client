#pragma once

#include <Novice.h>
#include <Background.h>

/// <summary>
/// タイトルクラス
/// </summary>
class Title
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="keys">キー1</param>
	/// <param name="preKeys">キー2</param>
	void Update(char* keys, char* preKeys);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// ゲッター
	bool GetIsNext() { return _isNext; }

private:
	bool _isNext; // シーン遷移フラグ

	//! 背景
	Background* _background = nullptr;

	uint32_t _title = 0u;
	uint32_t _space = 0u;
};

