#include "Title.h"

void Title::Initialize()
{
	_isNext = false;
}

void Title::Update(char* keys, char* preKeys)
{
	if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
		_isNext = true;
	}
}

void Title::Draw()
{
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, GREEN, kFillModeSolid);
}
