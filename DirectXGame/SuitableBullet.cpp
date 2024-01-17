#include "SuitableBullet.h"
#include <cassert>

SuitableBullet::~SuitableBullet() {}

void SuitableBullet::Initialize(Model* bullet_) {
	assert(bullet_);
	model_ = bullet_;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {0.3f, 0.3f, 0.3f};
}

void SuitableBullet::Update() { worldTransform_.UpdateMatrix(); }

void SuitableBullet::Draw(ViewProjection& viewProjection_) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection_);
}
