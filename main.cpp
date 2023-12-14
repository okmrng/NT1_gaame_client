#include <Novice.h>
#include "GameScene2D.h"
#include "Title.h"

const char kWindowTitle[] = "NT1-Client";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//! シーン
	enum class Scene
	{
		TITLE,
		GAME,
		RESET
	};
	Scene scene = Scene::TITLE;

	//! タイトル
	Title* title = new Title();
	title->Initialize();

	//! ゲームシーン
	GameScene2D* gameScene2D = new GameScene2D();
	gameScene2D->Initialize();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		//! タイトル
		if (scene == Scene::TITLE) {
			title->Update(keys, preKeys);
			if (title->GetIsNext()) scene = Scene::GAME;
		}

		//! ゲームシーン
		if (scene == Scene::GAME) {
			gameScene2D->Update(keys, preKeys);
			if (gameScene2D->GetIsNext()) scene = Scene::RESET;
		}

		//! リセット
		if (scene == Scene::RESET) {
			title->Initialize();
			gameScene2D->Initialize();
			scene = Scene::TITLE;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//! タイトル
		if (scene == Scene::TITLE) title->Draw();

		//! ゲームシーン
		if (scene == Scene::GAME)  gameScene2D->Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// 解放
	delete gameScene2D;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
