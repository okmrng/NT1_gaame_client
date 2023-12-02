#include "Player2.h"

Player2::~Player2()
{
	for (Bullet* bullet : _bullets) delete bullet;
}

void Player2::Initialize(Vector2 pos, float rad, int32_t hpMax, int32_t power, Vector2 speed)
{
	_pos = pos;
	_rad = rad;
	_hpMax = hpMax;
	_hp = _hpMax;
	_power = power;
	_sprite = GREEN;
	_speed = speed;
	_bulletCoolTimerParameter = 60;
	_bulletCoolTimer = _bulletCoolTimerParameter;
	_direction = Direction::LEFT;
	_isDead = false;
}

void Player2::Update(char* keys)
{
	//! 自機
	Move(keys);
	// 死亡
	Dead();

	//! 弾
	// 弾の生成
	Attack();

	// 弾更新
	for (Bullet* bullet : _bullets) bullet->Update();

	// 弾の削除
	_bullets.remove_if([](Bullet* bullet) {
		if (bullet->GetIsDead()) {
			delete bullet;
			return true;
		}
		return false;
		});
}

void Player2::Move(char* keys)
{
	// キー入力がされたら移動
	// 右
	if (keys[DIK_RIGHT]) {
		_pos.x += _speed.x;
		// 向きを変える
		_direction = Direction::RIGHT;
	}
	// 左
	if (keys[DIK_LEFT]) {
		_pos.x -= _speed.x;
		// 向きを変える
		_direction = Direction::LEFT;
	}
	if (keys[DIK_DOWN]) _pos.y += _speed.y; // 下	
	if (keys[DIK_UP]) _pos.y -= _speed.y;   // 上

	// 移動制限
	if (_pos.x >= 1280 - _rad) _pos.x = 1280 - _rad; // 右端
	if (_pos.x <= _rad) _pos.x = _rad;               // 左端
	if (_pos.y >= 640 - _rad) _pos.y = 640 - _rad;   // 下端
	if (_pos.y <= _rad + 80) _pos.y = _rad + 80;     // 上端
}

void Player2::Attack()
{
	if (_bulletCoolTimer == _bulletCoolTimerParameter) {
		// 弾の速度
		Vector2 bulletSpeed = Vector2(-7, 0);
		// 自機の向きに応じて弾の発射方向を変化させる
		if (_direction == Direction::RIGHT) bulletSpeed = Vector2(7, 0); // 右
		if (_direction == Direction::LEFT) bulletSpeed = Vector2(-7, 0); // 左

		// 弾を生成
		Bullet* newBullet = new Bullet();
		newBullet->Initialize(_pos, bulletSpeed, _power, RED);
		_bullets.push_back(newBullet);
	}
	// 弾のクールタイム
	if (_bulletCoolTimer <= _bulletCoolTimerParameter) _bulletCoolTimer--;
	if (_bulletCoolTimer == 0) _bulletCoolTimer = _bulletCoolTimerParameter;
}

void Player2::Dead()
{
	if (_hp <= 0) _isDead = true;
}

void Player2::OnCollision(int32_t damage)
{
	_hp -= damage;
}

void Player2::PlayerCollision()
{
	// 弾を撃たせないようにする
	_bulletCoolTimer = _bulletCoolTimerParameter / 2;
}

void Player2::Draw()
{
	//! 弾
	for (Bullet* bullet : _bullets) bullet->Draw();

	//! 自機
	Novice::DrawEllipse(int(_pos.x), int(_pos.y), int(_rad), int(_rad), 0.0f, _sprite, kFillModeSolid);

	//? デバッグ文字
#ifdef _DEBUG
	Novice::ScreenPrintf(0, 20, "2P:%d", _hp);
#endif // _DEBUG
}

void Player2::DrawUI()
{
	//! UI
	//! HPゲージ
	Novice::DrawBox(1260, 660, 256 * -(_hp) / _hpMax, 40, 0.0f, GREEN, kFillModeSolid);
}
