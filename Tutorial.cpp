#include "Tutorial.h"

void Tutorial::Initialize()
{
	//! 押せるようになるまでのフラグ
	_isPush = false;
	_pushCount = 5;

	//! 画像
	_info1 = Novice::LoadTexture("./Resouces/Images/info1.png");
	_info2 = Novice::LoadTexture("./Resouces/Images/info2.png");
	_space = Novice::LoadTexture("./Resouces/Images/space.png");
	_spaceStart = Novice::LoadTexture("./Resouces/Images/spaceStart.png");
	_isInfo1 = true;
	_isInfo2 = false;

	//! 次のシーンへ
	_isNext = false;

	//! 背景
	_backgorund = new Background();
	_backgorund->Initialize();
}

void Tutorial::Update(char* keys, char* preKeys)
{
	//! 連続で受付防止
	if (_pushCount >= 0)_pushCount--;

	//! キーで画像切り替え
	if (_isInfo1) {
		if (_pushCount <= 0) {
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				_isInfo2 = true;
				_isInfo1 = false;
				_pushCount = 5;
			}
		}
	}
	if (_isInfo2) {
		if (_pushCount <= 0) {
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				_isNext = true;
				_isInfo2 = false;
				_pushCount = 5;
			}
		}
	}
}

void Tutorial::Draw()
{
	_backgorund->Draw();

	if (_isInfo1) {
		Novice::DrawSprite(225, 231, _info1, 1, 1, 0.0f, WHITE);
		Novice::DrawSprite(842, 418, _space, 1, 1, 0.0f, WHITE);
	}
	if (_isInfo2) {
		Novice::DrawSprite(5, 15, _info2, 1, 1, 0.0f, WHITE);
		Novice::DrawSprite(714, 636, _spaceStart, 1, 1, 0.0f, WHITE);
	}
}
