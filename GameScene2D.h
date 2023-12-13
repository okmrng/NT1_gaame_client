#pragma once

#include <Player.h>
#include <Novice.h>
#include <process.h>
#include <mmsystem.h>
#include <Item.h>
#include <Background.h>

/// <summary>
/// ゲームシーンクラス
/// </summary>
class GameScene2D
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene2D();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="keys">キー1</param>
	void Update(char* keys);

	/// <summary>
	/// 当たり判定処理
	/// </summary>
	void CheckAllColision();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();



private:
	//! スプライト
	uint32_t _player1Sprite = 0u; // 1P本体
	uint32_t _player2Sprite = 0u; // 2P本体
	uint32_t _bullet1Sprite = 0u; // 1P弾
	uint32_t _bullet2Sprite = 0u; // 2P弾

	//! 背景
	Background* _background = nullptr;
};

