#include "Ground.h"
#include <cassert>

void Ground::Initialize(Model* model) { 
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, -0.5f, 0.0f};
}

void Ground::Update() { 
	worldTransform_.UpdateMatrix();
}

void Ground::Draw(const ViewProjection& viewprojection) {
	model_->Draw(worldTransform_, viewprojection);

}
