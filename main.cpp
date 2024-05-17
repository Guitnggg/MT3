#include <Novice.h>
#include <Vector3.h>
#include <Matrix4x4.h>
#include <cmath>

const char kWindowTitle[] = "LE2C_16_タカキ_ケンゴ_MT3";

// X軸周りの回転行列を作成
Matrix4x4 MakeRotateXMatrix(float radian) {
    Matrix4x4 result = {};
    result.m[0][0] = 1.0f;
    result.m[1][1] = cosf(radian);
    result.m[1][2] = -sinf(radian);
    result.m[2][1] = sinf(radian);
    result.m[2][2] = cosf(radian);
    result.m[3][3] = 1.0f;
    return result;
}

// Y軸周りの回転行列を作成
Matrix4x4 MakeRotateYMatrix(float radian) {
    Matrix4x4 result = {};
    result.m[0][0] = cosf(radian);
    result.m[0][2] = sinf(radian);
    result.m[1][1] = 1.0f;
    result.m[2][0] = -sinf(radian);
    result.m[2][2] = cosf(radian);
    result.m[3][3] = 1.0f;
    return result;
}

// Z軸周りの回転行列を作成
Matrix4x4 MakeRotateZMatrix(float radian) {
    Matrix4x4 result = {};
    result.m[0][0] = cosf(radian);
    result.m[0][1] = -sinf(radian);
    result.m[1][0] = sinf(radian);
    result.m[1][1] = cosf(radian);
    result.m[2][2] = 1.0f;
    result.m[3][3] = 1.0f;
    return result;
}

// 行列の乗算
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result = {};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += m1.m[i][k] * m2.m[k][j];
            }
        }
    }
    return result;
}

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
    Novice::ScreenPrintf(x, y, "%s", label);
    for (int row = 0; row < 4; row++) {
        for (int column = 0; column < 4; column++) {
            Novice::ScreenPrintf(x + column * kColumnWidth, y + (row + 1) * kRowHeight, "%6.02f", matrix.m[row][column]);
        }
    }
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    Vector3 rotate{ 0.4f, 1.43f, -0.8f };

    Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
    Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
    Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
    Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

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

        MatrixScreenPrintf(0, 0, rotateXMatrix, "rotateXMatrix");
        MatrixScreenPrintf(0, kRowHeight * 5, rotateYMatrix, "rotateYMatrix");
        MatrixScreenPrintf(0, kRowHeight * 5 * 2, rotateZMatrix, "rotateZMatrix");
        MatrixScreenPrintf(0, kRowHeight * 5 * 3, rotateXYZMatrix, "rotateXYZMatrix");

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
