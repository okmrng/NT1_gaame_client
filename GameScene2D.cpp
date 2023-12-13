#include "GameScene2D.h"
#include <fstream>

#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "winmm.lib")

//! 通信
DWORD WINAPI Threadfunc(void*);
HWND hwMain;

//! 自機
Player* player1 = nullptr; // 1P
Player* player2 = nullptr; // 2P

//! アイテム
Item* item = nullptr;

GameScene2D::~GameScene2D()
{
	//! 自機
	delete player1;  // 1P
	delete player2; // 2P
}

void GameScene2D::Initialize()
{
	//! 通信
	WSADATA wdData;
	static HANDLE hThread;
	static DWORD dwID;

	// ウィンドウ取得
	hwMain = GetDesktopWindow();

	//! 自機
	// 1P
	player1 = new Player();
	player1->Initialize(Vector2{ 50.0f, 360.0f }, 20.0f, 100, 100, 5, BLUE, Vector2(5, 5), 0, RED);

	// 2P
	player2 = new Player();
	player2->Initialize(Vector2{ 1230.0f, 360.0f }, 20.0f, 100, 100, 5, GREEN, Vector2(5, 5), 1, RED);

	//! アイテム
	item = new Item();
	item->Initialize();

	//! 通信
	// winsock初期化
	WSAStartup(MAKEWORD(2, 0), &wdData);

	// ソケット通信用スレッド作成
	hThread = (HANDLE)CreateThread(NULL, 0, &Threadfunc, (LPVOID)&player1, 0, &dwID);
}

void GameScene2D::Update(char* keys)
{
	if (player1 && player2) {
		if (player1->GetCanPlay() && player2->GetCanPlay()) {
			if (!player1->GetIsDead() && !player2->GetIsDead()) {
				//! 自機
				//player1->Update(keys);  // 1P
				player2->Update(keys); // 2P

				//! 当たり判定
				CheckAllColision();
			}
		}
	}
}

void GameScene2D::CheckAllColision()
{
	Vector2 posA, posB; // 当たり判定用の変数

	//! 2Pと1Pの弾の当たり判定
#pragma region
	posA = player2->GetPosition(); // 2Pの位置
	for (int i = 0; i < 5; i++) {
		posB = player1->_bulletPos[i];  // 1Pの弾の位置

		// AとBの距離を求める
		const float distance = CollisionDistance(posA, posB);
		const float radius = CollisionRadius(player2->GetRadius(), player1->GetBulletRadius());

		// 当たったか判定
		if (distance <= radius) {
			// 2Pの弾の当たった時の処理
			player2->OnCollision(player1->GetPower());
		}
	}
	if (player1->GetAddBullet()) {
		for (int i = 5; i < 15; i++) {
			posB = player1->_bulletPos[i];  // 1Pの弾の位置

			// AとBの距離を求める
			const float distance = CollisionDistance(posA, posB);
			const float radius = CollisionRadius(player2->GetRadius(), player1->GetBulletRadius());

			// 当たったか判定
			if (distance <= radius) {
				// 2Pの弾の当たった時の処理
				player2->OnCollision(player1->GetPower());
			}
		}
	}
#pragma endregion

	//! 1Pと2Pの弾の当たり判定
#pragma region
	//for (Bullet* bullet : p2Bullets) {
	//	posA = player1->GetPosition(); // 1Pの位置
	//	posB = bullet->GetPosition();  // 2Pの弾の位置

	//	// AとBの距離を求める
	//	const float distance = CollisionDistance(posB, posA);
	//	const float radius = CollisionRadius(player1->GetRadius(), bullet->GetRadius());

	//	// 当たったか判定
	//	if (distance <= radius) {
	//		// 2Pの弾の当たった時の処理
	//		bullet->OnCollision();
	//		// 1Pの弾の当たった時の処理
	//		player1->OnCollision(bullet->GetPower());
	//	}
	//}
#pragma endregion

	//! 1Pと2Pの当たり判定
#pragma region
	{
		posA = player1->GetPosition();  // 1Pの位置
		posB = player2->GetPosition(); // 2Pの弾の位置

		// AとBの距離を求める
		const float distance = CollisionDistance(posB, posA);
		const float radius = CollisionRadius(player1->GetRadius(), player2->GetRadius());

		// 当たったか判定
		if (distance <= radius) {
			// 1Pの当たった時の処理
			player1->PlayerCollision();
			// 2Pの当たった時の処理
			player2->PlayerCollision();
		}
	}
#pragma endregion

	//! 1Pと攻撃アイテムの当たり判定
#pragma region
	{
		posA = player1->GetPosition(); // 1Pの位置
		posB = item->GetAttackPos();  // アイテムの位置

		// AとBの距離を求める
		const float distance = CollisionDistance(posA, posB);
		const float radius = CollisionRadius(item->GetRadius(), player1->GetBulletRadius());

		// 当たったか判定
		if (distance <= radius) {
			// 1Pの当たった時の処理
			player1->OnCollisionAttack();
			// アイテムの当たった時の処理
			item->AttackCollision();
		}
	}
#pragma endregion

	//! 1Pと速度アップアイテムの当たり判定
#pragma region
	{
		posA = player1->GetPosition(); // 1Pの位置
		posB = item->GetSpeedPos();  // アイテムの位置

		// AとBの距離を求める
		const float distance = CollisionDistance(posA, posB);
		const float radius = CollisionRadius(item->GetRadius(), player1->GetBulletRadius());

		// 当たったか判定
		if (distance <= radius) {
			// 1Pの当たった時の処理
			player1->OnCollisionSpeed();
			// アイテムの当たった時の処理
			item->SpeedCollision();
		}
	}
#pragma endregion

	//! 1Pと最大HPアップアイテムの当たり判定
#pragma region
	{
		posA = player1->GetPosition(); // 1Pの位置
		posB = item->GetMaxHpPos();  // アイテムの位置

		// AとBの距離を求める
		const float distance = CollisionDistance(posA, posB);
		const float radius = CollisionRadius(item->GetRadius(), player1->GetBulletRadius());

		// 当たったか判定
		if (distance <= radius) {
			// 1Pの当たった時の処理
			player1->OnCollisionMaxHp();
			// アイテムの当たった時の処理
			item->MaxHpCollision();
		}
	}
#pragma endregion

	//! 1Pと回復アイテムの当たり判定
#pragma region
	{
		posA = player1->GetPosition(); // 1Pの位置
		posB = item->GetHealPos();  // アイテムの位置

		// AとBの距離を求める
		const float distance = CollisionDistance(posA, posB);
		const float radius = CollisionRadius(item->GetRadius(), player1->GetBulletRadius());

		// 当たったか判定
		if (distance <= radius) {
			// 1Pの当たった時の処理
			player1->OnCollisionHeal();
			// アイテムの当たった時の処理
			item->HealCollision();
		}
	}
#pragma endregion

	//! 1Pと弾強化アイテムの当たり判定
#pragma region
	{
		posA = player1->GetPosition(); // 1Pの位置
		posB = item->GetStrongPos();  // アイテムの位置

		// AとBの距離を求める
		const float distance = CollisionDistance(posA, posB);
		const float radius = CollisionRadius(item->GetRadius(), player1->GetBulletRadius());

		// 当たったか判定
		if (distance <= radius) {
			// 1Pの当たった時の処理
			player1->OnCollisionStrong();
			// アイテムの当たった時の処理
			item->StrongCollision();
		}
	}
#pragma endregion
}

void GameScene2D::Draw()
{
	//! 自機
	player1->Draw();  // 1P
	player2->Draw(); // 2P

	//! フレーム
	Novice::DrawBox(0, 0, 1280, 80, 0.0f, BLACK, kFillModeSolid);
	Novice::DrawBox(0, 640, 1280, 80, 0.0f, BLACK, kFillModeSolid);

	//! UI
	player1->DrawUI(Vector2(20, 20), 1);     //1P
	player2->DrawUI(Vector2(1260, 660), -1); //2P

	//!  アイテム
	item->Draw();
}
// 通信スレッド関数
DWORD WINAPI Threadfunc(void*) {

	SOCKET sConnect;// 待機用と接続用
	struct sockaddr_in saConnect;// 待機用と接続用
	WORD wPort = 8000;
	int iLen;// accept関数で使用
	char ipAddr[20];                                           // IPアドレス用配列

	// ファイル読み込み
	std::ifstream ifs("ip.txt");
	ifs.getline(ipAddr, sizeof(ipAddr));
	sConnect = socket(PF_INET, SOCK_STREAM, 0);

	ZeroMemory(&saConnect, sizeof(sockaddr_in));
	saConnect.sin_family = AF_INET;
	saConnect.sin_addr.s_addr = inet_addr(ipAddr);  // IPアドレス設定
	saConnect.sin_port = htons(wPort);

	// ソケットをオープン
	sConnect = socket(AF_INET, SOCK_STREAM, 0);
	if (sConnect == INVALID_SOCKET) {
		return 1;
	}

	iLen = sizeof(saConnect);

	if (connect(sConnect, (LPSOCKADDR)&saConnect, iLen) == SOCKET_ERROR) {

		return 1;
	}

	while (1)
	{
		player2->SetCanPlay(true);

		// データ送信
		char sendBuffer[sizeof(Player)];
		player2->Serialize(sendBuffer);
		send(sConnect, (const char*)&sendBuffer, sizeof(Player), 0);

		// データ受信
		char recvBuffer[sizeof(Player)];
		int nRcv = recv(sConnect, (char*)&recvBuffer, sizeof(Player), 0);
		player1->Dserialize(recvBuffer);

		if (nRcv == SOCKET_ERROR)break;

		//!  アイテム
		// データ受信
		char recvItem[sizeof(Item)];
		int itemRcv = recv(sConnect, (char*)&recvItem, sizeof(Player), 0);
		item->Dserialize(recvItem);

		if (itemRcv == SOCKET_ERROR)break;
	}

	shutdown(sConnect, 2);
	closesocket(sConnect);

	return 0;
}