#include "MayhUtilityO.h"

// 演算子オーバーロード
// Vector2同士の加算
Vector2& operator+=(Vector2& v1, const Vector2& v2) {
	v1.x += v2.x;
	v1.y += v2.y;

	return v1;
}

const Vector2 operator+(const Vector2& v1, const Vector2& v2) {
	Vector2 result = v1;
	return result += v2;
}

// Vector2の要素が0
Vector2 Vector2Zero()
{
	Vector2 result = Vector2(0, 0);
	return result;
}

// 当たり判定時に使う距離を算出する関数
float CollisionDistance(Vector2 posA, Vector2 posB)
{
	const float collisionX = (posB.x - posA.x) * (posB.x - posA.x);
	const float collisionY = (posB.y - posA.y) * (posB.y - posA.y);
	const float distance = collisionX + collisionY;

	return distance;
}

// 当たり判定時に使う半径を算出する関数
float CollisionRadius(float radA, float radB)
{
	const float collisionRadiusA = radA;
	const float collisionRadiusB = radB;
	const float collisionRadius = (collisionRadiusA + collisionRadiusB) * (collisionRadiusA + collisionRadiusB);

	return collisionRadius;
}
