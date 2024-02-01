#include "Enemy.h"
#include <ImGuiManager.h>
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
	worldTransformBase_.Initialize();

	worldTransformHead_.parent_ = &worldTransformBase_;
	// ボディ1の親をヘッドにする
	worldTransformBody1_.parent_ = &worldTransformBase_;
	// ボディ2の親をヘッドにする
	worldTransformBody2_.parent_ = &worldTransformBase_;
	// ボディ3の親をヘッドにする
	worldTransformBody3_.parent_ = &worldTransformBase_;

	worldTransformHead_.translation_ = {0.0f, 2.0f, 0.0f};
	worldTransformBody1_.translation_ = {0.0f, 2.0f, 0.0f};
	worldTransformBody2_.translation_ = {0.0f, 2.0f, 0.0f};
	worldTransformBody3_.translation_ = {0.0f, 2.0f, 0.0f};
}

void Enemy::Update() {

	if (isfall_ == true) {

		fallcount += 0.1f;

		/*worldTransformBody3_.translation_.y = -0.5f;
		worldTransformBody2_.translation_.y = -0.5f;
		worldTransformBody1_.translation_.y = -0.5f;
		worldTransformHead_.translation_.y = -0.5f;*/

		// if (worldTransformBody1_.translation_.y > -0.5f) {
		worldTransformBody3_.translation_.y -= 0.1f;
		worldTransformBody2_.translation_.y -= 0.1f;
		worldTransformBody1_.translation_.y -= 0.1f;
		worldTransformHead_.translation_.y -= 0.1f;
		//}

		//// if (worldTransformBody2_.translation_.y > -0.5f) {
		//worldTransformBody3_.translation_.y -= 0.1f;
		//worldTransformBody2_.translation_.y -= 0.1f;
		//worldTransformBody1_.translation_.y -= 0.1f;
		//worldTransformHead_.translation_.y -= 0.1f;
		////}

		//// if (worldTransformBody3_.translation_.y > -1.5f) {
		//worldTransformBody3_.translation_.y -= 0.1f;
		//worldTransformBody2_.translation_.y -= 0.1f;
		//worldTransformBody1_.translation_.y -= 0.1f;
		//worldTransformHead_.translation_.y -= 0.1f;
		////}

		//if (worldTransformHead_.translation_.y > 2.0f) {
		//	worldTransformBody3_.translation_.y -= 0.1f;
		//	worldTransformBody2_.translation_.y -= 0.1f;
		//	worldTransformBody1_.translation_.y -= 0.1f;
		//	worldTransformHead_.translation_.y -= 0.1f;
		//}

		if (fallcount >= 2.5f) {
			isfall_ = false;
			fallcount = 0;
		}
	}

	ImGui::Begin("count");
	ImGui::DragFloat("a", &fallcount);
	ImGui::End();

	if (isDelete_ == true) {
		/*const float kAcceleration = -0.02f;
		velocity_.y += kAcceleration;
		worldTransformHead_.translation_.y += velocity_.y;*/

		if (worldTransformHead_.translation_.y <= 0.0f) {
			// velocity_ = {0.0f, 0.0f, 0.0f};
			worldTransformHead_.translation_.y = 0.0f;
		}
	}

	worldTransformBase_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformBody1_.UpdateMatrix();
	worldTransformBody2_.UpdateMatrix();
	worldTransformBody3_.UpdateMatrix();
}

void Enemy::Draw(ViewProjection& viewProjection) {
	// 3Dモデル描画
	headModel_->Draw(worldTransformHead_, viewProjection);
	bodyModel3_->Draw(worldTransformBody3_, viewProjection);

	if (isDelete_ == false) {
		bodyModel1_->Draw(worldTransformBody1_, viewProjection);
	}

	if (isDelete_ == false) {
		bodyModel2_->Draw(worldTransformBody2_, viewProjection);
	}
}

// 親子関係を結ぶ
void Enemy::SetParent(const WorldTransform* parent) { worldTransformHead_.parent_ = parent; }

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransformBase_.matWorld_.m[3][0];
	worldPos.y = worldTransformBase_.matWorld_.m[3][1];
	worldPos.z = worldTransformBase_.matWorld_.m[3][2];
	return worldPos;
}

void Enemy::OnCollision() {
	isDead_ = true;

	// isDelete_ = true;

	isfall_ = true;
}
