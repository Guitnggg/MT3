#include <Novice.h>
#include <Vector3.h>

const char kWindowTitle[] = "LE2C_16_タカキ_ケンゴ_MT3";

struct Matrix4x4
{
	float m[4][4];
};

// 1.行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++) {
				result.m[i][j] = m1.m[i][k] + m2.m[k][j];
			}
		}
	}
	return result;
}

// 2.行列の現法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++) {
				result.m[i][j] = m1.m[i][k] - m2.m[k][j];
			}
		}
	}
	return result;
}

// 3.行列の積
Matrix4x4 Multiply(Matrix4x4 matrix1, Matrix4x4 matrix2)
{
	Matrix4x4 result;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				result.m[i][j] += matrix1.m[i][k] * matrix2.m[k][j];
			}
		}
	}
	return result;
}

// 4.逆行列
//Matrix4x4 Inverse(const Matrix4x4& m)
//{
//	Matrix4x4 result;
//
//	return result;
//}

// 5.転置行列
Matrix4x4 Transpose(const Matrix4x4& m)
{
	Matrix4x4 result;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = m.m[j][i]; // 行と列を入れ替える
		}
	}

	return result;
}

// 6.単位行列の作成
Matrix4x4 MakeIdentity()
{
	Matrix4x4 identity;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
				identity.m[i][j] = 1.0f; // 対角成分は1
			else
				identity.m[i][j] = 0.0f; // それ以外は0
		}
	}

	return identity;
}

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix)
{
	for (int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 4; column++)
		{
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Matrix4x4 m1 = { 3.2f, 0.7f, 9.6f, 4.4f,
					 5.5f, 1.3f, 7.8f, 2.1f,
					 6.9f, 8.0f, 2.6f, 1.0f,
					 0.5f, 7.2f, 5.1f, 3.3f
	};

	Matrix4x4 m2 = { 4.1f, 6.5f, 3.3f, 2.2f,
					 8.8f, 0.6f, 9.9f, 7.7f,
					 1.1f, 5.5f, 6.6f, 0.0f,
					 3.3f, 9.9f, 8.8f, 2.2f
	};

	Matrix4x4 resultAdd = Add(m1, m2);
	Matrix4x4 resultMutiply = Multiply(m1, m2);
	Matrix4x4 resultSubtract = Subtract(m1, m2);
	/*Matrix4x4 inverseM1 = Inverse(m1);
	Matrix4x4 inverseM2 = Inverse(m2);*/
	Matrix4x4 transposeM1 = Transpose(m1);
	Matrix4x4 transposeM2 = Transpose(m2);
	Matrix4x4 identity = MakeIdentity();

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, resultAdd);
		MatrixScreenPrintf(0, kRowHeight * 5, resultSubtract);
		MatrixScreenPrintf(0, kRowHeight * 5 * 2, resultMutiply);
		/*MatrixScreenPrintf(0, kRowHeight * 5 * 3, inverseM1);
		MatrixScreenPrintf(0, kRowHeight * 5 * 4, inverseM2);*/
		MatrixScreenPrintf(kColumnWidth * 5, 0, transposeM1);
		MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5, transposeM2);
		MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5 * 2, identity);

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
