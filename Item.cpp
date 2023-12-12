#include "Item.h"

void Item::Initialize()
{
	_pos = Vector2(500, 500);
	_rad = 10;
	_speed = 2;
}

void Item::Update()
{
	if (_pos.x <= 200) {
		_speed *= -1;
	}
	if (_pos.x >= 600) {
		_speed *= -1;
	}

	_pos.x += _speed;
}

void Item::Draw()
{
	Novice::DrawEllipse(int(_pos.x), int(_pos.y), int(_rad), int(_rad), 0.0f, WHITE, kFillModeSolid);
}

void Item::Serialize(char* buffer) const
{
	// メモリコピー
	memcpy(buffer, this, sizeof(Item));
}

void Item::Dserialize(const char* buffer)
{
	// メモリコピー
	memcpy(this, buffer, sizeof(Item));
}
