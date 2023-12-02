#pragma once

#include <Player.h>
#include <Novice.h>

/// <summary>
/// ゲームシーンクラス
/// </summary>
class GameScene2D
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameScene2D();

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
	//! 自機
	Player* _player1 = nullptr; // 1P
	Player* _player2 = nullptr; // 2P
};

