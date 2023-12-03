#pragma once

#include <Player.h>
#include <Novice.h>
#include <process.h>
#include <mmsystem.h>

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
};

