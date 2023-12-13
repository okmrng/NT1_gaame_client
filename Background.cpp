#include "Background.h"

void Background::Initialize()
{
	//!  一番後ろの背景
	_mostBackBuildingSprite = Novice::LoadTexture("./Resouces/Images/building_mostBack.png");
	_mostBackBuildingPos1 = 0;
	_mostBackBuildingPos2 = 1280;
	_mostBackBuildingSpeed = 1;

	//!  後ろの背景
	_backBuildingSprite = Novice::LoadTexture("./Resouces/Images/building_back.png");
	_backBuildingPos1 = 0;
	_backBuildingPos2 = 1280;
	_backBuildingSpeed = 3;

	//!  前の背景
	_frontBuildingSprite = Novice::LoadTexture("./Resouces/Images/building_front.png");
	_frontBuildingPos1 = 0;
	_frontBuildingPos2 = 1280;
	_frontBuildingSpeed = 6;

	//! グラデーション
	_guradationSprite = Novice::LoadTexture("./Resouces/Images/gradation.png");
}

void Background::Update()
{
	//! 一番後ろの背景
	_mostBackBuildingPos1 -= _mostBackBuildingSpeed;
	_mostBackBuildingPos2 -= _mostBackBuildingSpeed;
	if (_mostBackBuildingPos1 <= -1280) _mostBackBuildingPos1 = 1280;
	if (_mostBackBuildingPos2 <= -1280) _mostBackBuildingPos2 = 1280;

	//! 後ろの背景
	_backBuildingPos1 -= _backBuildingSpeed;
	_backBuildingPos2 -= _backBuildingSpeed;
	if (_backBuildingPos1 <= -1280) _backBuildingPos1 = 1280;
	if (_backBuildingPos2 <= -1280) _backBuildingPos2 = 1280;

	//! 前の背景
	_frontBuildingPos1 -= _frontBuildingSpeed;
	_frontBuildingPos2 -= _frontBuildingSpeed;
	if (_frontBuildingPos1 <= -1280) _frontBuildingPos1 = 1280;
	if (_frontBuildingPos2 <= -1280) _frontBuildingPos2 = 1280;
}

void Background::Draw()
{
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);

	//! 一番後ろの背景
	Novice::DrawSprite(int(_mostBackBuildingPos1), 0, _mostBackBuildingSprite, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(int(_mostBackBuildingPos2), 0, _mostBackBuildingSprite, 1, 1, 0.0f, WHITE);

	//! 後ろの背景
	Novice::DrawSprite(int(_backBuildingPos1), 0, _backBuildingSprite, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(int(_backBuildingPos2), 0, _backBuildingSprite, 1, 1, 0.0f, WHITE);

	//! 前の背景
	Novice::DrawSprite(int(_frontBuildingPos1), 0, _frontBuildingSprite, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(int(_frontBuildingPos2), 0, _frontBuildingSprite, 1, 1, 0.0f, WHITE);

	//! グラデーション
	Novice::DrawSprite(0, 0, _guradationSprite, 1, 1, 0.0f, WHITE);
}
