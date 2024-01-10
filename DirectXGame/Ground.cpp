#include "Ground.h"
#include <cassert>

void Ground::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, -0.5f, 0.0f};
}

void Ground::Update() {

	// AL3でやったUpdateMatrixも持ってくる
	// worldTransform_.TransferMatrix();

	worldTransform_.UpdateMatrix();
}

void Ground::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}
