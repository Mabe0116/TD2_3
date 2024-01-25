#include "Enemy.h"
#include <Mymath.h>
#include <cassert>

Enemy::~Enemy() {}

void Enemy::Initialize(Model* head, Model* body1, Model* body2, Model* body3) {
	assert(head);
	headModel_ = head;
	assert(body1);
	bodyModel1_ = body1;
	assert(body2);
	bodyModel2_ = body2;
	assert(body3);
	bodyModel3_ = body3;

	worldTransformHead_.Initialize();
	worldTransformBody1_.Initialize();
	worldTransformBody2_.Initialize();
	worldTransformBody3_.Initialize();

	// ボディ1の親をヘッドにする
	worldTransformBody1_.parent_ = &worldTransformHead_;
	// ボディ2の親をヘッドにする
	worldTransformBody2_.parent_ = &worldTransformHead_;
	// ボディ3の親をヘッドにする
	worldTransformBody3_.parent_ = &worldTransformHead_;

	worldTransformHead_.translation_ = {0, 3.0f, 0};
	worldTransformBody1_.translation_ = {0, 0, 0};
	worldTransformBody2_.translation_ = {0, 0, 0};
	worldTransformBody3_.translation_ = {0, 0, 0};
}

void Enemy::Update() {
	worldTransformHead_.UpdateMatrix();
	worldTransformBody1_.UpdateMatrix();
	worldTransformBody2_.UpdateMatrix();
	worldTransformBody3_.UpdateMatrix();
}

void Enemy::Draw(ViewProjection& viewProjection) {
	// 3Dモデル描画
	 headModel_->Draw(worldTransformHead_, viewProjection);
 	 bodyModel3_->Draw(worldTransformBody3_, viewProjection);
	 bodyModel2_->Draw(worldTransformBody2_, viewProjection);	 	    
	 bodyModel1_->Draw(worldTransformBody1_, viewProjection);
}

// 親子関係を結ぶ
void Enemy::SetParent(const WorldTransform* parent) { worldTransformHead_.parent_ = parent; }

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos; 
	worldPos.x = worldTransformBody2_.translation_.x;
	worldPos.y = worldTransformBody2_.translation_.y;
	worldPos.z = worldTransformBody2_.translation_.z;
	return worldPos;
}
