#pragma once

#include <Vector2.h>
#include <Novice.h>
#include <MayhUtilityO.h>
#include <stdint.h>
#include <Bullet.h>
#include <list>

/// <summary>
/// playerクラス
/// </summary>
class Player
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="rad">半径</param>
	/// <param name="hpMax">最大HP</param>
	/// <param name="power">攻撃力</param>
	/// <param name="speed">速度</param>
	/// <param name="direction">自機の向き。0 = 右, 1 = 左</param>
	void Initialize(Vector2 pos, float rad, int32_t hpMax, int32_t power, Vector2 speed, int32_t direction);

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="keys">キー1</param>
	void Update(char* keys);

	/// <summary>
	/// 移動
	/// </summary>
	/// <param name="keys">キー1</param>
	void Move(char* keys);

	/// <summary>
	/// 弾の生成
	/// </summary>
	void Attack();

	/// <summary>
	/// 死亡
	/// </summary>
	void Dead();

	/// <summary>
	/// 弾が当たった時の関数
	/// </summary>
	/// <param name="power">ダメージ</param>
	void OnCollision(int32_t damage);

	/// <summary>
	/// 自機同士が当たった時の関数
	/// </summary>
	void PlayerCollision();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// UI描画
	/// </summary>
	/// <param name="hpGagePos">HPゲージの位置</param>
	/// <param name="hpGageSubDirection">HPゲージを減らしていく方向</param>
	void DrawUI(Vector2 hpGagePos, int32_t hpGageSubDirection);

	// ゲッター
	Vector2 GetPosition() { return _pos; }
	float GetRadius() { return _rad; }
	const std::list<Bullet*>& GetBullet() { return _bullets; }
	bool GetIsDead() { return _isDead; }

private:
	// メンバ変数
	//! 自機
	Vector2	 _pos;	                    // 位置
	float	 _rad;	                    // 半径
	int32_t	 _hpMax;                    // 最大HP
	int32_t	 _hp;                       // HP
	int32_t	 _power;                    // 攻撃力
	uint32_t _sprite;                   // 色
	Vector2  _speed;                    // 速度
	int32_t  _bulletCoolTimerParameter; // 弾のクールタイムの値
	int32_t  _bulletCoolTimer;          // 弾のクールタイム
	// 向き列挙体
	enum class Direction
	{
		RIGHT, // 右
		LEFT   // 左
	};
	Direction _direction; // 向き
	bool _isDead;         // 死亡フラグ

	//! 弾
	std::list<Bullet*> _bullets; // 弾のリスト
};

