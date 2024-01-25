#include "SuitableBullet.h"
#include <cassert>
#include <ImGuiManager.h>

SuitableBullet::~SuitableBullet() {
}

void SuitableBullet::Initialize(Model* bullet_, const Vector3& position, const Vector3& velocity) {
	assert(bullet_);
	model_ = bullet_;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {0.3f, 0.3f, 0.3f};

	velocity_ = velocity;
	// 引数で受け取った速度をメンバ変数に代入
	deathTimer_ = 6000;

	isDead_ = false;
}

void SuitableBullet::Update() {

	Vector3 velocity = {0.2f, 0, 0.2f};
	// 座標を移動させる(1フレーム分の移動量を足しこむ)
	worldTransform_.translation_.x += velocity.x;
	worldTransform_.translation_.y += velocity.y;
	worldTransform_.translation_.z += velocity.z;

	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
		deathTimer_ = 6000;
	}

	worldTransform_.UpdateMatrix(); 
}

void SuitableBullet::Draw(ViewProjection& viewProjection_) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection_);
}
