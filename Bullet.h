#pragma once

#include <Vector2.h>
#include <stdint.h>
#include <MayhUtilityO.h>
#include <Novice.h>

/// <summary>
/// 弾クラス
/// </summary>
class Bullet
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="speed">速度</param>
	/// <param name="power">攻撃力</param>
	/// <param name="sprite">画像</param>
	void Initialize(Vector2 pos, Vector2 speed, int32_t power, uint32_t sprite);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 弾が当たった時の関数
	/// </summary>
	void OnCollision();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// ゲッター
	Vector2 GetPosition() { return _pos; }
	float   GetRadius() { return _rad; }
	bool    GetIsDead() { return _isDead; }
	int32_t GetPower() { return _power; }

private:
	Vector2  _pos;    // 位置
	float    _rad;    // 半径
	Vector2  _speed;  // 速度
	int32_t  _power;  // 攻撃力
	uint32_t _sprite; // 画像
	bool     _isDead; // 消滅判定フラグ
};

