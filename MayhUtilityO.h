#include <Vector2.h>

// 演算子オーバーロード
// Vector2同士の加算
Vector2& operator+=(Vector2& v1, const Vector2& v2);
const Vector2 operator+(const Vector2& v1, const Vector2& v2);

// 関数
// Vector2の要素が0
Vector2 Vector2Zero();

/// <summary>
/// 当たり判定時に使う距離を算出する関数
/// </summary>
/// <param name="posA">当たり判定を行うオブジェクト1</param>
/// <param name="posB">当たり判定を行うオブジェクト2</param>
/// /// <returns>二つのオブジェクトの距離</returns>
float CollisionDistance(Vector2 posA, Vector2 posB);

/// <summary>
/// 当たり判定時に使う半径を算出する関数
/// </summary>
/// <param name="radA">当たり判定を行うオブジェクト1</param>
/// <param name="radB">当たり判定を行うオブジェクト2</param>
/// /// <returns>二つのオブジェクトの半径</returns>
float CollisionRadius(float radA, float radB);