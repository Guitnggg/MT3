#include <Novice.h>
#include<cmath>
#include<assert.h>

const char kWindowTitle[] = "LE2C_16_タカキ_ケンゴ_MT3";

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Matrix4x4 {
	float m[4][4];
};

Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};
	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
	return result;
}

Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2) {
	Matrix4x4 result{};
	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];

	result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];

	result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];

	result.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
	result.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
	result.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
	result.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];
	return result;
}

#pragma region 逆数
Matrix4x4 Inverse(const Matrix4x4& m) {
	float A = m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]
		+ m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]
		+ m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]
		- m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]
		- m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]
		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]
		- m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]
		- m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]
		+ m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]
		+ m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]
		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]
		+ m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]
		- m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]
		- m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]
		- m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]
		+ m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]
		+ m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];


	Matrix4x4 result{};
	result.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3]
		+ m.m[1][2] * m.m[2][3] * m.m[3][1]
		+ m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[1][3] * m.m[2][2] * m.m[3][1]
		- m.m[1][2] * m.m[2][1] * m.m[3][3]
		- m.m[1][1] * m.m[2][3] * m.m[3][2]) / A;

	result.m[0][1] = (-m.m[0][1] * m.m[2][2] * m.m[3][3]
		- m.m[0][2] * m.m[2][3] * m.m[3][1]
		- m.m[0][3] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[2][2] * m.m[3][1]
		+ m.m[0][2] * m.m[2][1] * m.m[3][3]
		+ m.m[0][1] * m.m[2][3] * m.m[3][2]) / A;

	result.m[0][2] = (m.m[0][1] * m.m[1][2] * m.m[3][3]
		+ m.m[0][2] * m.m[1][3] * m.m[3][1]
		+ m.m[0][3] * m.m[1][1] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[3][1]
		- m.m[0][2] * m.m[1][1] * m.m[3][3]
		- m.m[0][1] * m.m[1][3] * m.m[3][2]) / A;

	result.m[0][3] = (-m.m[0][1] * m.m[1][2] * m.m[2][3]
		- m.m[0][2] * m.m[1][3] * m.m[2][1]
		- m.m[0][3] * m.m[1][1] * m.m[2][2]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1]
		+ m.m[0][2] * m.m[1][1] * m.m[2][3]
		+ m.m[0][1] * m.m[1][3] * m.m[2][2]) / A;


	result.m[1][0] = (-m.m[1][0] * m.m[2][2] * m.m[3][3]
		- m.m[1][2] * m.m[2][3] * m.m[3][0]
		- m.m[1][3] * m.m[2][0] * m.m[3][2]
		+ m.m[1][3] * m.m[2][2] * m.m[3][0]
		+ m.m[1][2] * m.m[2][0] * m.m[3][3]
		+ m.m[1][0] * m.m[2][3] * m.m[3][2]) / A;

	result.m[1][1] = (m.m[0][0] * m.m[2][2] * m.m[3][3]
		+ m.m[0][2] * m.m[2][3] * m.m[3][0]
		+ m.m[0][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[2][2] * m.m[3][0]
		- m.m[0][2] * m.m[2][0] * m.m[3][3]
		- m.m[0][0] * m.m[2][3] * m.m[3][2]) / A;

	result.m[1][2] = (-m.m[0][0] * m.m[1][2] * m.m[3][3]
		- m.m[0][2] * m.m[1][3] * m.m[3][0]
		- m.m[0][3] * m.m[1][0] * m.m[3][2]
		+ m.m[0][3] * m.m[1][2] * m.m[3][0]
		+ m.m[0][2] * m.m[1][0] * m.m[3][3]
		+ m.m[0][0] * m.m[1][3] * m.m[3][2]) / A;

	result.m[1][3] = (m.m[0][0] * m.m[1][2] * m.m[2][3]
		+ m.m[0][2] * m.m[1][3] * m.m[2][0]
		+ m.m[0][3] * m.m[1][0] * m.m[2][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0]
		- m.m[0][2] * m.m[1][0] * m.m[2][3]
		- m.m[0][0] * m.m[1][3] * m.m[2][2]) / A;


	result.m[2][0] = (m.m[1][0] * m.m[2][1] * m.m[3][3]
		+ m.m[1][1] * m.m[2][3] * m.m[3][0]
		+ m.m[1][3] * m.m[2][0] * m.m[3][1]
		- m.m[1][3] * m.m[2][1] * m.m[3][0]
		- m.m[1][1] * m.m[2][0] * m.m[3][3]
		- m.m[1][0] * m.m[2][3] * m.m[3][1]) / A;

	result.m[2][1] = (-m.m[0][0] * m.m[2][1] * m.m[3][3]
		- m.m[0][1] * m.m[2][3] * m.m[3][0]
		- m.m[0][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[2][1] * m.m[3][0]
		+ m.m[0][1] * m.m[2][0] * m.m[3][3]
		+ m.m[0][0] * m.m[2][3] * m.m[3][1]) / A;

	result.m[2][2] = (m.m[0][0] * m.m[1][1] * m.m[3][3]
		+ m.m[0][1] * m.m[1][3] * m.m[3][0]
		+ m.m[0][3] * m.m[1][0] * m.m[3][1]
		- m.m[0][3] * m.m[1][1] * m.m[3][0]
		- m.m[0][1] * m.m[1][0] * m.m[3][3]
		- m.m[0][0] * m.m[1][3] * m.m[3][1]) / A;

	result.m[2][3] = (-m.m[0][0] * m.m[1][1] * m.m[2][3]
		- m.m[0][1] * m.m[1][3] * m.m[2][0]
		- m.m[0][3] * m.m[1][0] * m.m[2][1]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0]
		+ m.m[0][1] * m.m[1][0] * m.m[2][3]
		+ m.m[0][0] * m.m[1][3] * m.m[2][1]) / A;


	result.m[3][0] = (-m.m[1][0] * m.m[2][1] * m.m[3][2]
		- m.m[1][1] * m.m[2][2] * m.m[3][0]
		- m.m[1][2] * m.m[2][0] * m.m[3][1]
		+ m.m[1][2] * m.m[2][1] * m.m[3][0]
		+ m.m[1][1] * m.m[2][0] * m.m[3][2]
		+ m.m[1][0] * m.m[2][2] * m.m[3][1]) / A;

	result.m[3][1] = (m.m[0][0] * m.m[2][1] * m.m[3][2]
		+ m.m[0][1] * m.m[2][2] * m.m[3][0]
		+ m.m[0][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[2][1] * m.m[3][0]
		- m.m[0][1] * m.m[2][0] * m.m[3][2]
		- m.m[0][0] * m.m[2][2] * m.m[3][1]) / A;

	result.m[3][2] = (-m.m[0][0] * m.m[1][1] * m.m[3][2]
		- m.m[0][1] * m.m[1][2] * m.m[3][0]
		- m.m[0][2] * m.m[1][0] * m.m[3][1]
		+ m.m[0][2] * m.m[1][1] * m.m[3][0]
		+ m.m[0][1] * m.m[1][0] * m.m[3][2]
		+ m.m[0][0] * m.m[1][2] * m.m[3][1]) / A;

	result.m[3][3] = (m.m[0][0] * m.m[1][1] * m.m[2][2]
		+ m.m[0][1] * m.m[1][2] * m.m[2][0]
		+ m.m[0][2] * m.m[1][0] * m.m[2][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0]
		- m.m[0][1] * m.m[1][0] * m.m[2][2]
		- m.m[0][0] * m.m[1][2] * m.m[2][1]) / A;

	return result;
}
#pragma endregion

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result{};

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}


Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

	Matrix4x4 resultX{};

	resultX.m[0][0] = 1.0f;
	resultX.m[0][1] = 0.0f;
	resultX.m[0][2] = 0.0f;
	resultX.m[0][3] = 0.0f;
	resultX.m[1][0] = 0.0f;
	resultX.m[1][1] = std::cos(rotate.x);
	resultX.m[1][2] = std::sin(rotate.x);
	resultX.m[1][3] = 0.0f;
	resultX.m[2][0] = 0.0f;
	resultX.m[2][1] = -(std::sin(rotate.x));
	resultX.m[2][2] = std::cos(rotate.x);
	resultX.m[2][3] = 0.0f;
	resultX.m[3][0] = 0.0f;
	resultX.m[3][1] = 0.0f;
	resultX.m[3][2] = 0.0f;
	resultX.m[3][3] = 1.0f;


	Matrix4x4 resultY{};

	resultY.m[0][0] = std::cos(rotate.y);
	resultY.m[0][1] = 0.0f;
	resultY.m[0][2] = -(std::sin(rotate.y));
	resultY.m[0][3] = 0.0f;
	resultY.m[1][0] = 0.0f;
	resultY.m[1][1] = 1.0f;
	resultY.m[1][2] = 0.0f;
	resultY.m[1][3] = 0.0f;
	resultY.m[2][0] = std::sin(rotate.y);
	resultY.m[2][1] = 0.0f;
	resultY.m[2][2] = std::cos(rotate.y);
	resultY.m[2][3] = 0.0f;
	resultY.m[3][0] = 0.0f;
	resultY.m[3][1] = 0.0f;
	resultY.m[3][2] = 0.0f;
	resultY.m[3][3] = 1.0f;


	Matrix4x4 resultZ{};

	resultZ.m[0][0] = std::cos(rotate.z);
	resultZ.m[0][1] = std::sin(rotate.z);
	resultZ.m[0][2] = 0.0f;
	resultZ.m[0][3] = 0.0f;
	resultZ.m[1][0] = -(std::sin(rotate.z));
	resultZ.m[1][1] = std::cos(rotate.z);
	resultZ.m[1][2] = 0.0f;
	resultZ.m[1][3] = 0.0f;
	resultZ.m[2][0] = 0.0f;
	resultZ.m[2][1] = 0.0f;
	resultZ.m[2][2] = 1.0f;
	resultZ.m[2][3] = 0.0f;
	resultZ.m[3][0] = 0.0f;
	resultZ.m[3][1] = 0.0f;
	resultZ.m[3][2] = 0.0f;
	resultZ.m[3][3] = 1.0f;


	Matrix4x4 rotateXYZ = Multiply(resultX, Multiply(resultY, resultZ));


	Matrix4x4 result{};
	result.m[0][0] = scale.x * rotateXYZ.m[0][0];
	result.m[0][1] = scale.x * rotateXYZ.m[0][1];
	result.m[0][2] = scale.x * rotateXYZ.m[0][2];
	result.m[0][3] = 0.0f;
	result.m[1][0] = scale.y * rotateXYZ.m[1][0];
	result.m[1][1] = scale.y * rotateXYZ.m[1][1];
	result.m[1][2] = scale.y * rotateXYZ.m[1][2];
	result.m[1][3] = 0.0f;
	result.m[2][0] = scale.z * rotateXYZ.m[2][0];
	result.m[2][1] = scale.z * rotateXYZ.m[2][1];
	result.m[2][2] = scale.z * rotateXYZ.m[2][2];
	result.m[2][3] = 0.0f;
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 MakePerspectiveFovMatrix(float forY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result;
	float cot = 1 / std::tan(forY / 2);

	result.m[0][0] = (1 / aspectRatio) * cot;
	result.m[1][1] = cot;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;
	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);


	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;
	result.m[1][0] = 0.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][3] = 0.0f;


	return result;
}

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result;
	result.m[0][0] = width / 2;
	result.m[1][1] = -(height / 2);
	result.m[2][2] = maxDepth - minDepth;

	result.m[3][0] = left + (width / 2);
	result.m[3][1] = top + (height / 2);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;

	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;
	result.m[1][0] = 0.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][3] = 0.0f;


	return result;
}


static const int kRowHeight = 20;

static const int kColumnWidth = 60;

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* name) {
	Novice::ScreenPrintf(x, y, "%s", name);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + 20 + row * kRowHeight, "%.02f", matrix.m[row][column]);
		}
	}
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	float rightLeftMove = 0;
	float nearFarMove = 0;

	Vector3 v1 = { 1.2f,-3.9f,2.5f };
	Vector3 v2 = { 2.8f,0.4f,-1.3f };
	Vector3 cross = Cross(v1, v2);

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




		if (keys[DIK_D]) {
			rightLeftMove += 0.01f;
		}

		if (keys[DIK_A]) {
			rightLeftMove -= 0.01f;
		}

		if (keys[DIK_S]) {
			nearFarMove += 0.01f;
		}

		if (keys[DIK_W]) {
			nearFarMove -= 0.01f;
		}

		Vector3 kLocalVartices[3] = {
			{-0.5f ,-0.5f ,0.0f  },
			{0.0f , 0.5f , 0.0f  },
			{0.5f ,-0.5f ,0.0f  }
		};



		Vector3 screenVertice[3] = {
		{0,0,0},
		{0,0,0},
		{0,0,0}
		};


		cross.y += 0.1f;


		Vector3 rotate{ 0.0f,cross.y,0.0f };


		Vector3 translate{ rightLeftMove,0.0f ,0.0f + nearFarMove };

		Vector3 cameraPosition = { 0.0f ,0.0f,-5.0f };




		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(1280.0f) / float(720.0f), 0.1f, 100.0f);
		Matrix4x4 WorldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(1280.0f), float(720.0f), 0.0f, 1.0f);


		for (uint32_t i = 0; i < 3; i++) {
			Vector3 ndcVertex = Transform(kLocalVartices[i], WorldViewProjectionMatrix);
			screenVertice[i] = Transform(ndcVertex, viewportMatrix);
		}





		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf(0, 0, cross, "Cross");

		MatrixScreenPrintf(0, 40, WorldViewProjectionMatrix, "Cross");

		Novice::DrawTriangle(int(screenVertice[0].x), int(screenVertice[0].y), int(screenVertice[1].x), int(screenVertice[1].y), int(screenVertice[2].x), int(screenVertice[2].y), RED, kFillModeSolid);

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

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}