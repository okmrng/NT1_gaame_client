#include "Player.h"

void Player::Initialize(Vector2 pos, float rad, float hp, float hpMax, float power, uint32_t sprite, Vector2 speed,
	int32_t direction, uint32_t bulletTexture)
{
	//! 自機
	_pos = pos;
	_rad = rad;
	_hpMax = hpMax;
	_hp = hp;
	_power = power;
	_sprite = sprite;
	_speed = speed;
	_bulletCoolTimerParameter = 60;
	_bulletCoolTimer = _bulletCoolTimerParameter;
	if (direction == 0) _direction = Direction::RIGHT;
	if (direction == 1) _direction = Direction::LEFT;
	_isDead = false;
	_isHit = false;
	_hitTime = 120;
	_canPlay = false;
	_attackCount = 0;
	_speedCount = 0;
	_attackTimer = 1800;
	_speedTimer = 1800;
	_isAttackUp = false;
	_isSpeedUp = false;

	//! 弾
	for (int i = 0; i < 15; i++) {
		_bulletPos[i] = Vector2(1500, 1500);
		_bulletMove[i] = false;
	}
	for (int i = 0; i < 5; i++) {
		_bulletSpeed[i] = Vector2(7, 0);
	}
	for (int i = 5; i < 10; i++) {
		_bulletSpeed[i] = Vector2(7, 1.5f);
	}
	for (int i = 10; i < 15; i++) {
		_bulletSpeed[i] = Vector2(7, -1.5f);
	}
	_bulletSprite = bulletTexture;
	_bulletRad = 10;
	_addBullet = false;
}

void Player::Update(char* keys)
{
	//! 自機
	// 移動
	Move(keys);

	// 無敵時間
	if (_isHit) {
		_hitTime--;
		if (_hitTime <= 0) _isHit = false;
	}

	// 最大体力を越さない
	if (_hp > _hpMax) _hp = _hpMax;

	// 死亡
	Dead();

	//! 弾
	BulletUpdate();

	//! アイテム処理
	// 攻撃アップ
	if (_isAttackUp) {
		_attackTimer--;
		_power = 100;
		if (_attackTimer <= 0) {
			_power = 65;
			_isAttackUp = false;
		}
	}
	// 速度アップ
	if (_isSpeedUp) {
		_speedTimer--;
		_speed = Vector2(10, 10);
		if (_speedTimer <= 0) {
			_speed = Vector2(8, 8);
			_isSpeedUp = false;
		}
	}
}

void Player::Move(char* keys)
{
	// キー入力がされたら移動
	// 右
	if (keys[DIK_D] || keys[DIK_RIGHT]) {
		_pos.x += _speed.x;
		// 向きを変える
		_direction = Direction::RIGHT;
	}
	// 左
	if (keys[DIK_A] || keys[DIK_LEFT]) {
		_pos.x -= _speed.x;
		// 向きを変える
		_direction = Direction::LEFT;
	}
	if (keys[DIK_S] || keys[DIK_DOWN]) _pos.y += _speed.y; // 下	
	if (keys[DIK_W] || keys[DIK_UP]) _pos.y -= _speed.y;   // 上

	// 移動制限
	if (_pos.x >= 1280 - _rad) _pos.x = 1280 - _rad; // 右端
	if (_pos.x <= _rad) _pos.x = _rad;		         // 左端
	if (_pos.y >= 640 - _rad) _pos.y = 640 - _rad;   // 下端
	if (_pos.y <= _rad + 80) _pos.y = _rad + 80;     // 上端
}

void Player::BulletUpdate()
{
	// 弾をセット
	--_bulletCoolTimer;
	if (_bulletCoolTimer < 0) _bulletCoolTimer = _bulletCoolTimerParameter;
	if (_bulletCoolTimer == 0) {
		for (int i = 0; i < 5; i++) {
			if (!_bulletMove[i]) {
				_bulletPos[i] = _pos;
				_bulletMove[i] = true;
				break;
			}
		}
		if (_addBullet) {
			for (int i = 5; i < 10; i++) {
				if (!_bulletMove[i]) {
					_bulletPos[i] = _pos;
					_bulletMove[i] = true;
					break;
				}
			}
			for (int i = 10; i < 15; i++) {
				if (!_bulletMove[i]) {
					_bulletPos[i] = _pos;
					_bulletMove[i] = true;
					break;
				}
			}
		}
	}
	// 弾の移動
	for (int i = 0; i < 5; i++) {
		if (_bulletMove[i]) {
			_bulletPos[i] += _bulletSpeed[i];
			if (_bulletPos[i].x >= 1280 + _bulletRad || _bulletPos[i].x <= -_bulletRad ||
				_bulletPos[i].y >= 720 + _bulletRad || _bulletPos[i].y <= -_rad) _bulletMove[i] = false;
		}
	}
	if (_addBullet) {
		for (int i = 5; i < 10; i++) {
			if (_bulletMove[i]) {
				_bulletPos[i] += _bulletSpeed[i];
				if (_bulletPos[i].x >= 1280 + _bulletRad || _bulletPos[i].x <= -_bulletRad ||
					_bulletPos[i].y >= 720 + _bulletRad || _bulletPos[i].y <= -_rad) _bulletMove[i] = false;
			}
		}
		for (int i = 10; i < 15; i++) {
			if (_bulletMove[i]) {
				_bulletPos[i] += _bulletSpeed[i];
				if (_bulletPos[i].x >= 1280 + _bulletRad || _bulletPos[i].x <= -_bulletRad ||
					_bulletPos[i].y >= 720 + _bulletRad || _bulletPos[i].y <= -_rad) _bulletMove[i] = false;
			}
		}
	}

	//! 向きに応じて弾の発射方向を変える
	if (_direction == Direction::RIGHT) {
		for (int i = 0; i < 15; i++) {
			if (!_bulletMove[i]) {
				if (!_bulletSpeedUp)_bulletSpeed[i].x = 7;
				else _bulletSpeed[i].x = 10;
			}
		}
	}
	if (_direction == Direction::LEFT) {
		for (int i = 0; i < 15; i++) {
			if (!_bulletMove[i]) {
				if (!_bulletSpeedUp)_bulletSpeed[i].x = -7;
				else _bulletSpeed[i].x = -10;
			}
		}
	}
}

void Player::Dead()
{
	if (_hp <= 0) _isDead = true;
}

void Player::OnCollision(float damage)
{
	if (!_isHit) {
		_hp -= damage;
		_hitTime = 120;
		_isHit = true;
	}
}

void Player::OnCollisionAttack()
{
	_attackCount++;
	if (_attackCount <= 30) _power += 2;
	if (_attackCount > 30) {
		_attackTimer = 1800;
		_isAttackUp = true;
	}
}

void Player::OnCollisionSpeed()
{
	_speedCount++;
	if (_speedCount <= 30) _speed += Vector2(0.1f, 0.1f);
	if (_speedCount > 30) {
		_speedTimer = 1800;
		_isSpeedUp = true;
	}
}

void Player::OnCollisionMaxHp()
{
	_hpMax += 20;
}

void Player::OnCollisionHeal()
{
	float heal = _hpMax * 0.2f;
	if (_hp < _hpMax) _hp += heal;
}

void Player::OnCollisionStrong()
{
	//! 弾速アップ
	if (!_bulletSpeedUp) {
		for (int i = 0; i < 15; i++) {
			_bulletSpeed[i] += Vector2(3, 0);
		}
		_bulletSpeedUp = true;
	}
	//! 弾のクールタイム低下
	else if (_bulletSpeedUp && !_bulletCoolSub) {
		_bulletCoolTimerParameter /= 2;
		_bulletCoolSub = true;
	}
	//! 弾数増加
	else if (_bulletCoolSub && !_addBullet) { _addBullet = true; }
}

void Player::PlayerCollision()
{
	// 弾を撃たせないようにする
	_bulletCoolTimer = _bulletCoolTimerParameter / 2;
}

void Player::Draw()
{
	//! 弾
	for (int i = 0; i < 5; i++) {
		Novice::DrawEllipse(int(_bulletPos[i].x), int(_bulletPos[i].y), int(_bulletRad), int(_bulletRad),
			0.0f, _bulletSprite, kFillModeSolid);
	}
	if (_addBullet) {
		for (int i = 5; i < 15; i++) {
			Novice::DrawEllipse(int(_bulletPos[i].x), int(_bulletPos[i].y), int(_bulletRad), int(_bulletRad),
				0.0f, _bulletSprite, kFillModeSolid);
		}
	}

	//! 自機
	Novice::DrawEllipse(int(_pos.x), int(_pos.y), int(_rad), int(_rad), 0.0f, _sprite, kFillModeSolid);

	//? デバッグ文字
#ifdef _DEBUG
	//Novice::ScreenPrintf(0, 0, "bulletCollTimer:%d", _bulletCoolTimer);
	//Novice::ScreenPrintf(0, 40, "1P:%d", _hp);
	//if (_isDead) Novice::ScreenPrintf(0, 60, "dead");
	//else Novice::ScreenPrintf(0, 60, "life");
	//Novice::ScreenPrintf(0, 60, "bullet[0]:%f", _bulletPos[0].x);
	//Novice::ScreenPrintf(0, 80, "bullet[1]:%f", _bulletPos[1].x);
	//Novice::ScreenPrintf(0, 80, "bulletspeed[3]:%f,%f", _bulletSpeed[2].x,_bulletSpeed[2].y);
#endif
}

void Player::DrawUI(Vector2 hpGagePos, int32_t hpGageSubDirection)
{
	//! HPゲージ
	if (_hp > 0) {
		Novice::DrawBox(int(hpGagePos.x), int(hpGagePos.y), (int)256 * ((int)hpGageSubDirection * (int)_hp) / (int)_hpMax, 40,
			0.0f, GREEN, kFillModeSolid);
	}
	Novice::DrawBox(int(hpGagePos.x + 256), int(hpGagePos.y), 1200, 40, 0.0f, BLACK, kFillModeSolid);
}

void Player::SetCanPlay(bool canPlay)
{
	_canPlay = canPlay;
}

void Player::Serialize(char* buffer) const
{
	// メモリコピー
	memcpy(buffer, this, sizeof(Player));
}

void Player::Dserialize(const char* buffer)
{
	// メモリコピー
	memcpy(this, buffer, sizeof(Player));
}
