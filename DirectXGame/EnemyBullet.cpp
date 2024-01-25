#include "EnemyBullet.h"
#include <TextureManager.h>
#include <cassert>

void EnemyBullet::Initialize(Model* model, const Vector3& position) { 
	assert(model); 

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("white1x1.png");

	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
}

void EnemyBullet::Update() { worldTransform_.UpdateMatrix(); }

void EnemyBullet::Draw(const ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
