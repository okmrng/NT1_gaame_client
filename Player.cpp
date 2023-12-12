#include "Player.h"

Player::~Player()
{
	//for (Bullet* bullet : _bullets) delete bullet;
}

void Player::Initialize(Vector2 pos, float rad, int32_t hp, int32_t hpMax, int32_t power, uint32_t sprite, Vector2 speed,
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

	//! 弾
	for (int i = 0; i < 5; i++) {
		_bulletPos[i] = Vector2(1500, 1500);
		_bulletSpeed[i].x = 0;
		_bulletSpeed[i].y = 0;
		_bulletMove[i] = false;
	}
	//_bulletSpeed[0].x = 7;
	//_bulletSpeed[0].y = 0;
	_bulletSprite = bulletTexture;
	_bulletRad = 10;
}

void Player::Update(char* keys)
{
	//! 自機
	// 移動
	Move(keys);
	// 死亡
	Dead();

	//! 弾
	// 弾の生成
	//Attack();

	// 弾更新
	//for (Bullet* bullet : _bullets) bullet->Update();
	BulletUpdate();

	// 弾の削除
	/*_bullets.remove_if([](Bullet* bullet) {
		if (bullet->GetIsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});*/
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

	// 右
	//if (keys[DIK_D]) {
	//	_pos.x += _speed.x;
	//	// 向きを変える
	//	_direction = Direction::RIGHT;
	//}
	//// 左
	//if (keys[DIK_A]) {
	//	_pos.x -= _speed.x;
	//	// 向きを変える
	//	_direction = Direction::LEFT;
	//}
	//if (keys[DIK_S]) _pos.y += _speed.y; // 下	
	//if (keys[DIK_W]) _pos.y -= _speed.y; // 上

	// 移動制限
	if (_pos.x >= 1280 - _rad) _pos.x = 1280 - _rad; // 右端
	if (_pos.x <= _rad) _pos.x = _rad;		         // 左端
	if (_pos.y >= 640 - _rad) _pos.y = 640 - _rad;   // 下端
	if (_pos.y <= _rad + 80) _pos.y = _rad + 80;     // 上端
}

void Player::Attack()
{
	//if (_bulletCoolTimer == _bulletCoolTimerParameter) {
	//	// 弾の速度
	//	Vector2 bulletSpeed = Vector2(7, 0);
	//	// 自機の向きに応じて弾の発射方向を変化させる
	//	if (_direction == Direction::RIGHT) bulletSpeed = Vector2(7, 0); // 右
	//	if (_direction == Direction::LEFT) bulletSpeed = Vector2(-7, 0); // 左

	//	// 弾を生成
	//	Bullet* newBullet = new Bullet();
	//	newBullet->Initialize(_pos, bulletSpeed, _power, RED);
	//	_bullets.push_back(newBullet);
	//}
	//// 弾のクールタイム
	//if (_bulletCoolTimer <= _bulletCoolTimerParameter) _bulletCoolTimer--;
	//if (_bulletCoolTimer == 0) _bulletCoolTimer = _bulletCoolTimerParameter;
}

void Player::BulletUpdate()
{
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
	}
	for (int i = 0; i < 5; i++) {
		if (_bulletMove[i]) {
			_bulletPos[i] += _bulletSpeed[i];
			if (_bulletPos[i].x >= 1280 + _bulletRad || _bulletPos[i].x <= -_bulletRad ||
				_bulletPos[i].y >= 720 + _bulletRad || _bulletPos[i].y <= -_rad) _bulletMove[i] = false;
		}
	}
}

void Player::Dead()
{
	if (_hp <= 0) _isDead = true;
}

void Player::OnCollision(int32_t damage)
{
	a++;
	_hp -= damage;
}

void Player::OnCollisionBullet()
{

}

void Player::PlayerCollision()
{
	// 弾を撃たせないようにする
	_bulletCoolTimer = _bulletCoolTimerParameter / 2;
}

void Player::Draw()
{
	//! 弾
	//for (Bullet* bullet : _bullets) bullet->Draw();
	for (int i = 0; i < 15; i++) {
		Novice::DrawEllipse(int(_bulletPos[i].x), int(_bulletPos[i].y), int(_bulletRad), int(_bulletRad),
			0.0f, _bulletSprite, kFillModeSolid);
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
#endif
}

void Player::DrawUI(Vector2 hpGagePos, int32_t hpGageSubDirection)
{
	//! HPゲージ
	Novice::DrawBox(int(hpGagePos.x), int(hpGagePos.y), 256 * (hpGageSubDirection * _hp) / _hpMax, 40,
		0.0f, GREEN, kFillModeSolid);
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
