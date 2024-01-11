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

	worldTransform_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformBody1_.Initialize();
	worldTransformBody2_.Initialize();
	worldTransformBody3_.Initialize();

	// 基底クラスのベースキャラクターworldTransformを親子関係のベースとする
	// ヘッドの親をにする
	worldTransformHead_.parent_ = &worldTransform_;
	// ボディ1の親をヘッドにする
	worldTransformBody1_.parent_ = &worldTransformHead_;
	// ボディ2の親をヘッドにする
	worldTransformBody2_.parent_ = &worldTransformHead_;
	// ボディ3の親をヘッドにする
	worldTransformBody3_.parent_ = &worldTransformHead_;

	worldTransform_.translation_ = {10, 0, 0};
	worldTransformHead_.translation_ = {0, 0, 0};
	worldTransformBody1_.translation_ = {0, 0, 0};
	worldTransformBody2_.translation_ = {0, 0, 0};
	worldTransformBody3_.translation_ = {0, 0, 0};
}

void Enemy::Update() {

	switch (phase_) {
	case Phase::First:
			break;
	case Phase::Second:
		    SecondAttack();
		    break;
	case Phase::Third:
		    ThirdAttack();
		    break;
	case Phase::Final:
		    SecondAttack(); 
			ThirdAttack();
		break;
	}


	worldTransform_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformBody1_.UpdateMatrix();
	worldTransformBody2_.UpdateMatrix();
	worldTransformBody3_.UpdateMatrix();
}

void Enemy::Draw(ViewProjection& viewProjection) {
	// 3Dモデル描画
	if (phase_ == Phase::First || phase_ == Phase::Second || phase_ == Phase::Third ||
	    phase_ == Phase::Final) {
	  headModel_->Draw(worldTransformHead_, viewProjection);
	 }
	if (phase_ == Phase::First || phase_ == Phase::Second||phase_ == Phase::Third) {
 	    bodyModel3_->Draw(worldTransformBody3_, viewProjection);
     }
	 if (phase_ == Phase::First || phase_ == Phase::Second) {
	  bodyModel2_->Draw(worldTransformBody2_, viewProjection);
	 }
	 if (phase_ == Phase::First) {
	 	    bodyModel1_->Draw(worldTransformBody1_, viewProjection);
	 }
}

void Enemy::SecondAttack() {}

void Enemy::ThirdAttack() {}

// 親子関係を結ぶ
void Enemy::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }