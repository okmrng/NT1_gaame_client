#include "Title.h"

void Title::Initialize()
{
	_isNext = false;

	//! 背景
	_background = new Background();
	_background->Initialize();

	_title = Novice::LoadTexture("./Resouces/Images/title.png");
	_space = Novice::LoadTexture("./Resouces/Images/spaceT.png");
}

void Title::Update(char* keys, char* preKeys)
{
	if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
		_isNext = true;
	}

	//! 背景
	_background->Update();
}

void Title::Draw()
{
	//! 背景
	_background->Draw();

	Novice::DrawSprite(126, 150, _title, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(404, 400, _space, 1, 1, 0.0f, WHITE);
}
