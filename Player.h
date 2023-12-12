#pragma once

#include <Vector2.h>
#include <Novice.h>
#include <MayhUtilityO.h>
#include <stdint.h>
#include <list>

/// <summary>
/// playerクラス
/// </summary>
class Player
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="rad">半径</param>
	/// <param name="hpMax">HP</param>
	/// <param name="hpMax">最大HP</param>
	/// <param name="power">攻撃力</param>
	/// <param name="sprite">スプライト</param>
	/// <param name="speed">速度</param>
	/// <param name="direction">自機の向き。0 = 右, 1 = 左</param>
	/// <param name="bulletTexture">弾のテクスチャ</param>
	void Initialize(Vector2 pos, float rad, int32_t hp, int32_t hpMax, int32_t power, uint32_t sprite, Vector2 speed,
		int32_t direction, uint32_t bulletTexture);

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
	/// 弾の更新
	/// </summary>
	void BulletUpdate();

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
	/// 弾の当たった時の処理
	/// </summary>
	void OnCollisionBullet();

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
	int32_t GetPower() { return _power; }
	int32_t GetHP() { return _hp; }
	//const std::list<Bullet*>& GetBullet() { return _bullets; }
	float GetBulletRadius() { return _bulletRad; }
	Vector2 GetBulletPosition() { return*_bulletPos; }
	bool GetIsDead() { return _isDead; }
	bool GetIsHit() { return _isHit; }
	int GetHitTime() { return _hitTime; }
	bool GetCanPlay() { return _canPlay; }

	// セッター
	void SetCanPlay(bool canPlay);

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

	int32_t	 _hp;             // HP
	Vector2 _bulletPos[5];    // 弾の位置
private:
	// メンバ変数
	//! 自機
	Vector2	 _pos;	                    // 位置
	float	 _rad;	                    // 半径
	int32_t	 _hpMax;                    // 最大HP
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
	bool _isHit;          // ヒットフラグ
	int _hitTime;         // 無敵時
	bool _canPlay;        // プレイフラグ

	//! 弾
	//std::list<Bullet*> _bullets; // 弾のリスト
	int32_t _bulletLength = 1; // 現在の弾数
	Vector2 _bulletSpeed[5];  // 弾速
	bool _bulletMove[5];      // 弾の移動フラグ
	uint32_t _bulletSprite;    // 弾のスプライト
	float _bulletRad;          // 弾の半径
};

