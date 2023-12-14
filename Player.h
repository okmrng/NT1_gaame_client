#pragma once

#include <Vector2.h>
#include <Novice.h>
#include <MayhUtilityO.h>
#include <stdint.h>

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
	void Initialize(Vector2 pos, float rad, float hp, float hpMax, float power, uint32_t sprite, Vector2 speed,
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
	/// 弾の更新
	/// </summary>
	void BulletUpdate();

	/// <summary>
	/// 死亡
	/// </summary>
	void Dead();

	/// <summary>
	/// UIの更新処理
	/// </summary>
	void UIUpdate();

	/// <summary>
	/// 弾が当たった時の関数
	/// </summary>
	/// <param name="power">ダメージ</param>
	void OnCollision(float damage);

	/// <summary>
	/// 攻撃アップアイテムと当たった時の処理
	/// </summary>
	void OnCollisionAttack();

	/// <summary>
	/// 弾速アップアイテムと当たった時の処理
	/// </summary>
	void OnCollisionSpeed();

	/// <summary>
	/// 最大HPアップアイテムと当たった時の処理
	/// </summary>
	void OnCollisionMaxHp();

	/// <summary>
	/// 回復アイテムと当たった時の処理
	/// </summary>
	void OnCollisionHeal();

	/// <summary>
	/// 弾強化アイテムと当たった時の処理
	/// </summary>
	void OnCollisionStrong();

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
	/// <param name="attackNumPos">攻撃LVの値の位置</param>
	/// <param name="speedNumPos">速度LVの値の位置</param>
	/// <param name="bulletNumPos">弾LVの値の位置</param>
	void DrawUI(Vector2 hpGagePos, int32_t hpGageSubDirection, Vector2 attackNumPos, Vector2 speedNumPos, Vector2 bulletNumPos,
		Vector2 attackPos, Vector2 hpNumPos, Vector2 speedPos, Vector2 bulletPos);

	// ゲッター
	Vector2 GetPosition() { return _pos; }
	float GetRadius() { return _rad; }
	float GetPower() { return _power; }
	Vector2 GetSpeed() { return _speed; }
	float GetHP() { return _hp; }
	float GetHPM() { return _hpMax; }
	float GetBulletRadius() { return _bulletRad; }
	Vector2 GetBulletPosition() { return*_bulletPos; }
	bool GetIsDead() { return _isDead; }
	bool GetIsHit() { return _isHit; }
	bool GetCanPlay() { return _canPlay; }
	bool GetAddBullet() { return _addBullet; }

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

	float	 _hp;             // HP
	Vector2 _bulletPos[15];    // 弾の位置
private:
	// メンバ変数
	//! 自機
	Vector2	 _pos;	                    // 位置
	float	 _rad;	                    // 半径
	float	 _hpMax;                    // 最大HP
	float	 _power;                    // 攻撃力
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
	Direction _direction;     // 向き
	bool _isDead;              // 死亡フラグ
	bool _isHit;                 // ヒットフラグ
	int _hitTime;               // 無敵時
	bool _canPlay;           // プレイフラグ
	int32_t _attackCount; // 攻撃アップアイテムを取った回数
	int32_t _speedCount; // 速度アップアイテムを取った回数
	int32_t _attackTimer; // 攻撃アップ時間
	int32_t _speedTimer; // 速度アップアイテム時間
	bool _isAttackUp;      // 攻撃アップフラグ
	bool _isSpeedUp;      // 速度アップフラグ

	//! 弾
	Vector2 _bulletSpeed[15]; // 弾速
	bool _bulletMove[15];      // 弾の移動フラグ
	uint32_t _bulletSprite;     // 弾のスプライト
	float _bulletRad;            // 弾の半径
	bool _bulletSpeedUp;     // 弾速度アップフラグ
	bool _bulletCoolSub;      // 弾のクールタイム低下フラグ
	bool _addBullet;            // 弾増加フラグ
	int32_t _bulletLv;

	//! UI
	// アイコン
	uint32_t _attackUI;
	uint32_t _hpUI;
	uint32_t _speedUI;
	uint32_t _bulletUI;
	uint32_t _num[10];
	// 割り当てる数
	int32_t _attackNumber[2];
	int32_t _speedNumber[2];
	int32_t _bulletNumber[2];
	// 桁幅
	int32_t _width;
};

