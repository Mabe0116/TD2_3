#include "FollowCamera.h"
#include "Input.h"
#include "MyMath.h"

void FollowCamera::Initialize() {
	viewProjection_.Initialize();
	// 敵キャラの生成
	enemy_ = std::make_unique<Enemy>();
}

void FollowCamera::Update() {

	// カメラから敵に向かう差分ベクトル
	DiffVector.x = enemy_->GetWorldPosition().x - viewProjection_.translation_.x;
	DiffVector.z = enemy_->GetWorldPosition().z - viewProjection_.translation_.z;

	viewProjection_.rotation_.y = std::atan2(DiffVector.x, DiffVector.z);
	viewProjection_.rotation_.y = std::atan2(DiffVector.x, DiffVector.z);
	viewProjection_.rotation_.y = std::atan2(DiffVector.x, DiffVector.z);
	viewProjection_.rotation_.y = std::atan2(DiffVector.x, DiffVector.z); 

	// 追従対象がいれば
	if (target_) {

		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 5.0f, -20.0f};

		// カメラの角度から回転行列を計算する
		Matrix4x4 RotationMatrix = MakeRotateMatrix(viewProjection_.rotation_);

		// オフセットをカメラの回転に合わせて回転させる
		offset = TransformNormal(offset, RotationMatrix);

		// 座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = Add(target_->translation_, offset);
	}

	// ビュー行列の更新
	viewProjection_.UpdateMatrix();
}
