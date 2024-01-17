#include "Skydome.h"
#include  <cassert>


void Skydome::Initialize(Model* model) {
	assert(model);
	model_ = model;
	/*worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};*/
	worldTransform_.scale_.x = 0.1f;
	worldTransform_.scale_.y = 0.1f;
	worldTransform_.scale_.z = 0.1f;

	worldTransform_.Initialize();
}

void Skydome::Update() { worldTransform_.UpdateMatrix(); }

void Skydome::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}
