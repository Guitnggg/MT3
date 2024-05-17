#include <Novice.h>
#include <Vector3.h>
#include <Matrix4x4.h>
#include <cmath>

const char kWindowTitle[] = "LE2C_16_タカキ_ケンゴ_MT3";

// 3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
    // スケーリング行列
    Matrix4x4 scaleMatrix = {
        scale.x, 0, 0, 0,
        0, scale.y, 0, 0,
        0, 0, scale.z, 0,
        0, 0, 0, 1
    };

    // 回転行列（X軸）
    float cosX = cosf(rotate.x);
    float sinX = sinf(rotate.x);
    Matrix4x4 rotateXMatrix = {
        1, 0, 0, 0,
        0, cosX, -sinX, 0,
        0, sinX, cosX, 0,
        0, 0, 0, 1
    };

    // 回転行列（Y軸）
    float cosY = cosf(rotate.y);
    float sinY = sinf(rotate.y);
    Matrix4x4 rotateYMatrix = {
        cosY, 0, sinY, 0,
        0, 1, 0, 0,
        -sinY, 0, cosY, 0,
        0, 0, 0, 1
    };

    // 回転行列（Z軸）
    float cosZ = cosf(rotate.z);
    float sinZ = sinf(rotate.z);
    Matrix4x4 rotateZMatrix = {
        cosZ, -sinZ, 0, 0,
        sinZ, cosZ, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    // 平行移動行列
    Matrix4x4 translateMatrix = {
        1, 0, 0, translate.x,
        0, 1, 0, translate.y,
        0, 0, 1, translate.z,
        0, 0, 0, 1
    };

    // 全ての行列を掛け合わせる（S * Rz * Ry * Rx * T の順番）
    Matrix4x4 worldMatrix = scaleMatrix * rotateZMatrix * rotateYMatrix * rotateXMatrix * translateMatrix;
    return worldMatrix;
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    Vector3 scale{ 1.2f, 0.79f, -2.1f };
    Vector3 rotate{ 0.4f, 1.43f, -0.8f };
    Vector3 translate{ 2.7f, -4.15f, 1.57f };
    Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotate, translate);

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
        MatrixScreenPrintf(0, 0, worldMatrix, "worldMatrix");
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
