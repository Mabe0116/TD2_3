#include "Trackingbullet.h"
#include <cassert>

Trackingbullet::~Trackingbullet() { }

void Trackingbullet::Initialize(Model* bullet_) {
	assert(bullet_);
	model_ = bullet_;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {0.3f, 0.3f, 0.3f};
}


void Trackingbullet::Update() { worldTransform_.UpdateMatrix(); }

//void Trackingbullet::Draw(ViewProjection& viewProjection_) {
//	// 3Dモデルを描画
//	model_->Draw(worldTransform_, viewProjection_);
//}
