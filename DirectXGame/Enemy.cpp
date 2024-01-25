#include "Enemy.h"
#include <Mymath.h>
#include <cassert>
#include <ImGuiManager.h>

Enemy::~Enemy() {
}

void Enemy::Initialize(
    Model* head, Model* body1, Model* body2, Model* body3/*, Model* modelSuitable*/) {
	assert(head);
	headModel_ = head;
	assert(body1);
	bodyModel1_ = body1;
	assert(body2);
	bodyModel2_ = body2;
	assert(body3);
	bodyModel3_ = body3;
	//弾
	//assert(modelSuitable);
	//modelSuitable_ = modelSuitable;

	worldTransform_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformBody1_.Initialize();
	worldTransformBody2_.Initialize();
	worldTransformBody3_.Initialize();
	//弾
	worldTransformSuitable_.Initialize();
	worldTransformSuitable_.parent_ = &worldTransform_;

	// 基底クラスのベースキャラクターworldTransformを親子関係のベースとする
	// ヘッドの親をにする
	worldTransformHead_.parent_ = &worldTransform_;
	// ボディ1の親をヘッドにする
	worldTransformBody1_.parent_ = &worldTransformHead_;
	// ボディ2の親をヘッドにする
	worldTransformBody2_.parent_ = &worldTransformHead_;
	// ボディ3の親をヘッドにする
	worldTransformBody3_.parent_ = &worldTransformHead_;

	worldTransform_.translation_ = {0, 0, 0};
	worldTransformHead_.translation_ = {0, 0, 0};
	worldTransformBody1_.translation_ = {0, 0, 0};
	worldTransformBody2_.translation_ = {0, 0, 0};
	worldTransformBody3_.translation_ = {0, 0, 0};

	RotateSpeed = 0.1f;
	SuitableTiming = 0;
	
phase_ = Phase::Second;
//	phase_ = Phase::First;

	}

void Enemy::Update() {

	//switch (phase_) {
	//case Phase::First:

	//		break;
	//case Phase::Second:
	//	    SecondAttack();
	//		 for (SuitableBullet* suitablenum : suitableBullet_) {
	//		    if (suitablenum) {
	//			    // 複数弾の更新
	//			    suitablenum->Update();
	//		    }
	//	    }
	//	    break;
	//case Phase::Third:
	//	    ThirdAttack();
	//	    break;
	//case Phase::Final:
	//	    SecondAttack(); 
	//		ThirdAttack();
	//	break;
	//}

	  SecondAttack();

worldTransform_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformBody1_.UpdateMatrix();
	worldTransformBody2_.UpdateMatrix();
	worldTransformBody3_.UpdateMatrix();
	//弾
	worldTransformSuitable_.UpdateMatrix();

		ImGui::Begin("window");
	ImGui::DragFloat("count", &SuitableTiming);
	ImGui::End();
}

void Enemy::Draw(ViewProjection& viewProjection) {
	// 3Dモデル描画
	if (phase_ == Phase::First || phase_ == Phase::Second || phase_ == Phase::Third ||
	    phase_ == Phase::Final) {
	  headModel_->Draw(worldTransformHead_, viewProjection);
	 }
	if (phase_ == Phase::First || phase_ == Phase::Second||phase_ == Phase::Third) {
	   bodyModel1_->Draw(worldTransformBody1_, viewProjection);
     }
	 if (phase_ == Phase::First || phase_ == Phase::Second) {
	  bodyModel2_->Draw(worldTransformBody2_, viewProjection);
	 }
	 if (phase_ == Phase::First) {
	  bodyModel3_->Draw(worldTransformBody3_, viewProjection);
	 }
	 // 複数弾の描画複数
	 for (SuitableBullet* suitablenum : suitableBulletNums_) {
		    suitablenum->Draw(viewProjection);
	 }
}

void Enemy::SecondAttack() {
		  
		    worldTransform_.rotation_.y += RotateSpeed;
		    SuitableTiming++;
	
	 for (SuitableBullet* suitablenum : suitableBulletNums_) {
		    // 複数弾の更新
		    suitablenum->Update();
		    if (SuitableTiming >=20) {
			    Vector3 velocity(0.2f, 0, 0.2f);
			    // 速度ベクトルを自機の向きに合わせて回転させる
			    velocity = TransformNormal(velocity, worldTransformSuitable_.matWorld_);
			    // 複数弾の生成
			 //   SuitableBullet* newSuitablenum = new SuitableBullet();
			    suitablenum->Initialize(
			        SuitableModel, worldTransformSuitable_.translation_, velocity);
			    // 複数弾の登録
			    suitableBulletNums_.push_back(suitablenum);
			    SuitableTiming = 0;
		    }
	 }
}

void Enemy::ThirdAttack() {}

// 親子関係を結ぶ
void Enemy::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }