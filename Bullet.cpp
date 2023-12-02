#include "Bullet.h"

void Bullet::Initialize(Vector2 pos, Vector2 speed, int32_t power, uint32_t sprite)
{
	_pos = pos;
	_speed = speed;
	_power = power;
	_sprite = sprite;
	_rad = 10.0f;
	_isDead = false;
}

void Bullet::Update()
{
	// 移動
	_pos += _speed;

	// 消滅
	if (_pos.x >= 1280 + _rad || _pos.x <= -_rad || _pos.y >= 720 + _rad || _pos.y <= -_rad) _isDead = true;
}

void Bullet::OnCollision()
{
	_isDead = true;
}

void Bullet::Draw()
{
	Novice::DrawEllipse(int(_pos.x), int(_pos.y), int(_rad), int(_rad), 0.0f, _sprite, kFillModeSolid);
}
