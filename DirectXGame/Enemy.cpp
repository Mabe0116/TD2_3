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

		if (!isThrown_[0]) {
			worldTransformBody1_.translation_.y -= 0.1f;
		}
		if (!isThrown_[1]) {
			worldTransformBody2_.translation_.y -= 0.1f;
		}
		if (!isThrown_[2]) {
			worldTransformBody3_.translation_.y -= 0.1f;
		}
		if (!isThrown_[3]) {
			worldTransformHead_.translation_.y -= 0.1f;
		}

		if (fallcount >= 2.5f) {
			isfall_ = false;
			fallcount = 0;
		}
	}

	ImGui::Begin("count");
	ImGui::DragFloat("a", &fallcount);
	ImGui::DragFloat3("Velocity", &velocity_[0].x);
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

	// 体が飛ばされる処理
	if (isThrown_[0]) {
		worldTransformBody1_.parent_ = nullptr;
		Move(worldTransformBody1_.translation_, velocity_[0]);
	}
	if (isThrown_[1]) {
		worldTransformBody2_.parent_ = nullptr;
		Move(worldTransformBody2_.translation_, velocity_[1]);
	}
	if (isThrown_[2]) {
		worldTransformBody3_.parent_ = nullptr;
		Move(worldTransformBody3_.translation_, velocity_[2]);
	}
	if (isThrown_[3]) {
		worldTransformHead_.parent_ = nullptr;
		Move(worldTransformHead_.translation_, velocity_[3]);
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
	bodyModel1_->Draw(worldTransformBody1_, viewProjection);
	bodyModel2_->Draw(worldTransformBody2_, viewProjection);
	bodyModel3_->Draw(worldTransformBody3_, viewProjection);
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

	for (int i = 0; i < 4; i++) {
		if (!isThrown_[i]) {
			isThrown_[i] = true;
			break;
		}
	}
}

void Enemy::SetVelocity(const Vector3& velocity) {
	for (int i = 0; i < 4; i++) {
		if (velocity_[i].x == 0.0f && velocity_[i].y == 0.0f && velocity_[i].z == 0.0f) {
			velocity_[i] = velocity;
			velocity_[i].y = 0.0f;
			break;
		}
	}
}