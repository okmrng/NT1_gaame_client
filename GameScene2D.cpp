#include "GameScene2D.h"

GameScene2D::GameScene2D()
{
}

GameScene2D::~GameScene2D()
{
	//! 自機
	delete _player1;  // 1P
	delete _player2; // 2P
}

void GameScene2D::Initialize()
{
	//! 自機
	// 1P
	//_player1 = new Player();
	_player1->Initialize(Vector2{ 50.0f, 360.0f }, 20.0f, 100, 5, Vector2(5, 5), 0);

	// 2P
	_player2 = new Player();
	_player2->Initialize(Vector2{ 1230.0f, 360.0f }, 20.0f, 100, 5, Vector2(5, 5), 1);
}

void GameScene2D::Update(char* keys)
{
	if (!_player1->GetIsDead() && !_player2->GetIsDead()) {
		//! 自機
		_player1->Update(keys);  // 1P
		_player2->Update(keys); // 2P

		//! 当たり判定
		CheckAllColision();
	}
}

void GameScene2D::CheckAllColision()
{
	Vector2 posA, posB; // 当たり判定用の変数

	const std::list<Bullet*>& p1Bullets = _player1->GetBullet();  // 1Pの弾
	const std::list<Bullet*>& p2Bullets = _player2->GetBullet(); // 2Pの弾

	//! 2Pと1Pの弾の当たり判定
#pragma region
	for (Bullet* bullet : p1Bullets) {
		posA = _player2->GetPosition(); // 2Pの位置
		posB = bullet->GetPosition();   // 1Pの弾の位置

		// AとBの距離を求める
		const float distance = CollisionDistance(posB, posA);
		const float radius = CollisionRadius(_player2->GetRadius(), bullet->GetRadius());

		// 当たったか判定
		if (distance <= radius) {
			// 1Pの弾の当たった時の処理
			bullet->OnCollision();
			// 2Pの弾の当たった時の処理
			_player2->OnCollision(bullet->GetPower());
		}
	}
#pragma endregion

	//! 1Pと2Pの弾の当たり判定
#pragma region
	for (Bullet* bullet : p2Bullets) {
		posA = _player1->GetPosition(); // 1Pの位置
		posB = bullet->GetPosition();  // 2Pの弾の位置

		// AとBの距離を求める
		const float distance = CollisionDistance(posB, posA);
		const float radius = CollisionRadius(_player1->GetRadius(), bullet->GetRadius());

		// 当たったか判定
		if (distance <= radius) {
			// 2Pの弾の当たった時の処理
			bullet->OnCollision();
			// 1Pの弾の当たった時の処理
			_player1->OnCollision(bullet->GetPower());
		}
	}
#pragma endregion

	//! 1Pと2Pの当たり判定
#pragma region
	posA = _player1->GetPosition();  // 1Pの位置
	posB = _player2->GetPosition(); // 2Pの弾の位置

	// AとBの距離を求める
	const float distance = CollisionDistance(posB, posA);
	const float radius = CollisionRadius(_player1->GetRadius(), _player2->GetRadius());

	// 当たったか判定
	if (distance <= radius) {
		// 1Pの当たった時の処理
		_player1->PlayerCollision();
		// 2Pの当たった時の処理
		_player2->PlayerCollision();
	}
#pragma endregion
}

void GameScene2D::Draw()
{
	//! 自機
	_player1->Draw();  // 1P
	_player2->Draw(); // 2P

	//! フレーム
	Novice::DrawBox(0, 0, 1280, 80, 0.0f, BLACK, kFillModeSolid);
	Novice::DrawBox(0, 640, 1280, 80, 0.0f, BLACK, kFillModeSolid);

	//! UI
	_player1->DrawUI(Vector2(20, 20), 1);     //1P
	_player2->DrawUI(Vector2(1260, 660), -1); //2P
}
