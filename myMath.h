#pragma once

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Matrix4x4 {
	float m[4][4];
};

class MyMath
{
public:

	Vector3 Add(const Vector3& v1, const Vector3& v2);
	Vector3 Subtract(const Vector3& v1, const Vector3& v2);
	Vector3 Multiply(float f, const Vector3& v);

	Matrix4x4 MakeRotateXMatrix(float radian);
	Matrix4x4 MakeRotateYMatrix(float radian);
	Matrix4x4 MakeRotateZMatrix(float radian);

	Matrix4x4 MultiplyMatrix(const Matrix4x4 m1, const Matrix4x4& m2);
};