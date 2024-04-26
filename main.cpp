#include <Novice.h>
#include <Vector3.h>

const char kWindowTitle[] = "LE2C_16_タカキ_ケンゴ_MT3";

struct Matrix4x4
{
	float m[4][4];
};

// 1.平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate)
{

}

// 2.拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{

}

// 3.座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix)
{

}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		Vector3 translate{ 4.1f,2.6f,0.8f };
		Vector3 scale{ 1.5f,5.2f,7.3f };
		
		Matrix4x4 translateMatrix = MakeScaleMatrix(translate);
		Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
		
		Vector3 point{ 2.3f,3.8f,1.4f };
		
		Matrix4x4 transformMatrix =
		{
			1.0f, 2.0f, 3.0f, 4.0f,
			3.0f, 1.0f, 1.0f, 2.0f,
			1.0f, 4.0f, 2.0f, 3.0f,
			2.0f, 2.0f, 1.0f, 3.0f
		};

		Vector3 trasnformed = Transform(point, transformMatrix);


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


