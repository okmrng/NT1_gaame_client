#pragma once

#include <Vector2.h>
#include <Novice.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

/// <summary>
/// アイテム
/// </summary>
class Item
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
	/// アイテム生成
	/// </summary>
	void Instant();

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	/// <summary>
	/// 攻撃アイテムが当たった時の処理
	/// </summary>
	void AttackCollision();

	/// <summary>
	/// 弾速アップアイテムが当たった時の処理
	/// </summary>
	void SpeedCollision();

	/// <summary>
	/// 最大HPアップアイテムが当たった時の処理
	/// </summary>
	void MaxHpCollision();

	/// <summary>
	/// HP回復アイテムが当たった時の処理
	/// </summary>
	void HealCollision();

	/// <summary>
	/// H弾強化アイテムが当たった時の処理
	/// </summary>
	void StrongCollision();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// ゲッター
	Vector2 GetAttackPos() { return _pos[0]; }
	Vector2 GetSpeedPos() { return _pos[1]; }
	Vector2 GetMaxHpPos() { return _pos[2]; }
	Vector2 GetHealPos() { return _pos[3]; }
	Vector2 GetStrongPos() { return _pos[4]; }
	float GetRadius() { return _rad; }

	/// <summary>
	/// バイト列に変換
	/// </summary>
	/// <param name="buffer">送信するバッファ</param>
	void Serialize(char* buffer)const;

	/// <summary>
	/// バイト列から復元
	/// </summary>
	/// <param name="buffer">受信したバッファ</param>
	void Dserialize(const char* buffer);

private:
	Vector2 _pos[5];                 // 位置
	float _rad;                         // 半径
	float _speed;					   // 速度
	bool _isInstant[5];             // 生成フラグ
	int32_t _instantProbability; // アイテム生成確率
	int32_t _type;                   // アイテムの種類
	uint32_t _sprite[5];           // スプライト
};

