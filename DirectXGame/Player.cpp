#include "Player.h"
#include <cassert>

void Player::Initialize(Model* head, Model* body1, Model* body2, Model* body3) { 
	assert(head);
	headModel_ = head;
	assert(body1);
	body1Model_ = body1;
	assert(body2);
	body2Model_ = body2;
	assert(body3);
	body3Model_ = body3;

	worldTransformHead_.translation_ = {0, 0, 0};
	worldTransformBody1_.translation_ = {0, 0, 0};
	worldTransformBody2_.translation_ = {0, 0, 0};
	worldTransformBody3_.translation_ = {0, 0, 0};

	worldTransformHead_.Initialize();
	worldTransformBody1_.Initialize();
	worldTransformBody2_.Initialize();
	worldTransformBody3_.Initialize();
}

void Player::Update() {
	worldTransformHead_.UpdateMatrix();
	worldTransformBody1_.UpdateMatrix();
	worldTransformBody2_.UpdateMatrix();
	worldTransformBody3_.UpdateMatrix();
}

void Player::Draw(ViewProjection& viewProjection) {
	// 3Dモデル描画
	headModel_->Draw(worldTransformHead_, viewProjection);
	body1Model_->Draw(worldTransformBody1_, viewProjection);
	body2Model_->Draw(worldTransformBody2_, viewProjection);
	body3Model_->Draw(worldTransformBody3_, viewProjection);
}