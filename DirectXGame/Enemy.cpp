#include "Enemy.h"
#include <Mymath.h>
#include <cassert>
#include <ImGuiManager.h>

Enemy::~Enemy() {
	for (SuitableBullet* suitablenum : suitableBulletNums_) {
		delete suitablenum;
	}
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
	/*assert(modelSuitable);
	suitableModel_ = modelSuitable;*/

	worldTransform_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformBody1_.Initialize();
	worldTransformBody2_.Initialize();
	worldTransformBody3_.Initialize();
	//弾
	worldTransformSuitable_.Initialize();
	//親子関係これでいろんなところに打てた
	worldTransformSuitable_.parent_ = &worldTransform_;
	SuitableModel = Model::CreateFromOBJ("bullet", true);


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
	//タイマー初期化
	SuitableTiming = FireInterval;
	TrackingTiming = FireInterval;
	
//phase_ = Phase::Second;
//	phase_ = Phase::First;
}

void Enemy::Update() {

	
	//switch (phase_) {
	//case Phase::First:
	//default:

	//		break;
	//case Phase::Second:
	//	    SecondAttack();
	//	    SuitableTiming++; 
	//		 for (SuitableBullet* suitablenum : suitableBulletNums_) {
	//		    if (suitablenum) {
	//			    // 複数弾の更新
	//			    suitablenum->Update();
	//		    }
	//	    }
	//	    break;
	//case Phase::Third:
	//	    //ThirdAttack();
	//	    break;
	//case Phase::Final:
	//	    //SecondAttack(); 
	//		//ThirdAttack();
	//	break;
	//}

	//敵回転
	 worldTransform_.rotation_.y += RotateSpeed;
	//複数弾のタイマー
	 SuitableTiming--;
	if (SuitableTiming <= 0) {
		SecondAttack();
	}
	for (SuitableBullet* suitablenum : suitableBulletNums_) {
		// 複数弾の更新
		suitablenum->Update();
	}

	// デスフラグの経った敵の削除
	suitableBulletNums_.remove_if([](SuitableBullet* enemynum) {
		if (enemynum->IsDead()) {
			delete enemynum;
			return true;
		}
		return false;
	});


	worldTransform_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformBody1_.UpdateMatrix();
	worldTransformBody2_.UpdateMatrix();
	worldTransformBody3_.UpdateMatrix();
	//弾
	worldTransformSuitable_.UpdateMatrix();

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
		  
		    const float kBulletSpeed = 1.0f;
			    Vector3 velocity(kBulletSpeed, 0, kBulletSpeed);

			    velocity = TransformNormal(velocity, worldTransformSuitable_.matWorld_);
	   
	        SuitableBullet* newSuitableBullet = new SuitableBullet();
		  // 複数弾の更新
	        newSuitableBullet->Initialize(
	            SuitableModel, worldTransformHead_.translation_, velocity);
				// 複数弾の登録
			   suitableBulletNums_.push_back(newSuitableBullet);
				//タイマー初期化
			    SuitableTiming =FireInterval ;
		    
	 
}
void Enemy::OnCollision() { isDead_ = true; }

//void Enemy::ThirdAttack() {}

// 親子関係を結ぶ
void Enemy::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos; 
	worldPos.x = worldTransformHead_.translation_.x;
	worldPos.y = worldTransformHead_.translation_.y;
	worldPos.z = worldTransformHead_.translation_.z;
	return worldPos;
}
