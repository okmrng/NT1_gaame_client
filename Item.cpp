#include "Item.h"

#define WINDOW_XMIN 10
#define WINDOW_XMAX 1270

void Item::Initialize()
{
	for (int i = 0; i < 5; i++) {
		_pos[i] = Vector2(2000, -10);
		_isInstant[i] = false;
	}
	_rad = 10;
	_speed = 2;
	_instantProbability = 0;
	_type = 0;

	//! 乱数の初期化
	srand((uint32_t)time(NULL));
}

void Item::Update()
{
	//! アイテム生成
	Instant();

	//! 移動
	Move();
}

void Item::Instant()
{
	//! 確率でアイテムを生成
	_instantProbability = rand() % 100 + 1;
	_type = rand() % 13 + 1;

	if (_instantProbability == 1) {
		//! アイテム抽選
		switch (_type)
		{
		case 1: // 攻撃力アップ
		case 2: // 攻撃力アップ
		case 3: // 攻撃力アップ
			if (!_isInstant[0]) {
				_pos[0].x = (rand() % (WINDOW_XMAX - WINDOW_XMIN + 1)) + (float)WINDOW_XMIN;
				_isInstant[0] = true;
			}

			break;
		case 4: // 速度アップ
		case 5: // 速度アップ
		case 6: // 速度アップ
			if (!_isInstant[1]) {
				_pos[1].x = (rand() % (WINDOW_XMAX - WINDOW_XMIN + 1)) + (float)WINDOW_XMIN;
				_isInstant[1] = true;
			}

			break;
		case 7: // 最大体力アップ
		case 8: // 最大体力アップ
		case 9: // 最大体力アップ
			if (!_isInstant[2]) {
				_pos[2].x = (rand() % (WINDOW_XMAX - WINDOW_XMIN + 1)) + (float)WINDOW_XMIN;
				_isInstant[2] = true;
			}

			break;
		case 10: // HP回復
		case 11: // HP回復
		case 12: // HP回復
			if (!_isInstant[3]) {
				_pos[3].x = (rand() % (WINDOW_XMAX - WINDOW_XMIN + 1)) + (float)WINDOW_XMIN;
				_isInstant[3] = true;
			}

			break;
		case 13: // 弾強化
			if (!_isInstant[4]) {
				_pos[4].x = (rand() % (WINDOW_XMAX - WINDOW_XMIN + 1)) + (float)WINDOW_XMIN;
				_isInstant[4] = true;
			}

			break;

		default:
			break;
		}
	}
}

void Item::Move()
{
	for (int i = 0; i < 5; i++) {
		// フラグがtrueの時、上から降ってくる
		if (_isInstant[i]) _pos[i].y += _speed;
		// 下画面外まで行ったら元に戻す
		if (_pos[i].y >= 720 + _rad) {
			_isInstant[i] = false;
			_pos[i].y = -_rad;
		}
	}
}

void Item::AttackCollision()
{
	_isInstant[0] = false;
	_pos[0].y = -_rad;
}

void Item::SpeedCollision()
{
	_isInstant[1] = false;
	_pos[1].y = -_rad;
}

void Item::MaxHpCollision()
{
	_isInstant[2] = false;
	_pos[2].y = -_rad;
}

void Item::HealCollision()
{
	_isInstant[3] = false;
	_pos[3].y = -_rad;
}

void Item::StrongCollision()
{
	_isInstant[4] = false;
	_pos[4].y = -_rad;
}

void Item::Draw()
{
	//! 攻撃
	Novice::DrawEllipse(int(_pos[0].x), int(_pos[0].y), int(_rad), int(_rad), 0.0f, RED, kFillModeSolid);
	//! 弾速
	Novice::DrawEllipse(int(_pos[1].x), int(_pos[1].y), int(_rad), int(_rad), 0.0f, 0xff69b4, kFillModeSolid);
	//! 最大体力
	Novice::DrawEllipse(int(_pos[2].x), int(_pos[2].y), int(_rad), int(_rad), 0.0f, 0x7fffb4, kFillModeSolid);
	//! 回復
	Novice::DrawEllipse(int(_pos[3].x), int(_pos[3].y), int(_rad), int(_rad), 0.0f, 0x4169e1, kFillModeSolid);
	//! 弾数
	Novice::DrawEllipse(int(_pos[4].x), int(_pos[4].y), int(_rad), int(_rad), 0.0f, GREEN, kFillModeSolid);
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

//TODO アイテムの種類
//x 1.弾数を増やす、弾速アップ、クールタイムを短くする、弾強化
//x 2.攻撃力アップ
//x 3.HPの回復
//x 4.速度アップ
//x 5.最大体力アップ