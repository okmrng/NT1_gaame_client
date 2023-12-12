#pragma once

#include <Vector2.h>
#include <Novice.h>

/// <summary>
/// アイテム
/// </summary>
class Item
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// バイト列に変換
	/// </summary>
	/// <param name="buffer">送信するバッファ</param>
	void Serialize(char* buffer)const;

	/// <summary>
	/// バイト列から復元
	/// </summary>
	/// <param name="buffer">受信したバッファ</param>
	void Dserialize(const char* buffer);

private:
	Vector2 _pos;  // 位置
	float _rad;     // 半径
	float _speed;
};

