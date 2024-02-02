﻿#include "Enemy.h"
#include <ImGuiManager.h>
#include <Mymath.h>
#include "Player.h"
#include <cassert>
#include <ImGuiManager.h>

Enemy::~Enemy() { 
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
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

	


	worldTransformHead_.Initialize();
	worldTransformBody1_.Initialize();
	worldTransformBody2_.Initialize();
	worldTransformBody3_.Initialize();
	worldTransformBase_.Initialize();

	worldTransformBase_.rotation_.y = 0;
	worldTransformBase_.scale_ = {3, 3, 3};
	//弾
	worldTransformSuitable_.Initialize();
	


	// 基底クラスのベースキャラクターworldTransformを親子関係のベースとする
	// ヘッドの親をにする
	worldTransformHead_.parent_ = &worldTransformBase_;
	// ボディ1の親をヘッドにする
	worldTransformBody1_.parent_ = &worldTransformBase_;
	// ボディ2の親をヘッドにする
	worldTransformBody2_.parent_ = &worldTransformBase_;
	// ボディ3の親をヘッドにする
	worldTransformBody3_.parent_ = &worldTransformBase_;

	

	

	// 親子関係
	worldTransformSuitable_.parent_ = &worldTransformBase_;

	//複数弾のモデル
	SuitableModel = Model::CreateFromOBJ("cube", true);
	//自機狙いの弾
	bulletModel_ = Model::CreateFromOBJ("cube", true);

	RotateSpeed = 0.1f;
	//タイマー初期化
	SuitableTiming = SuitableInterval;
	

	// 発射タイマーを初期化
	fireTimer_ = kFireInterval;
	// 自キャラの生成
	//player_ = std::make_unique<Player>();
phase_ = Phase::First;
	worldTransformHead_.translation_ = {0.0f, 2.0f, 0.0f};
	worldTransformBody1_.translation_ = {0.0f, 2.0f, 0.0f};
	worldTransformBody2_.translation_ = {0.0f, 2.0f, 0.0f};
	worldTransformBody3_.translation_ = {0.0f, 2.0f, 0.0f};
}

void Enemy::Update() {
	// デスフラグの立った弾を削除
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	switch (phase_) {
	case Phase::First:
	//攻撃無し
		worldTransformBase_.translation_.y = 2;
		break;
	case Phase::Second:
		//敵の高さ変える
		worldTransformBase_.translation_.y = -2;
		//複数の弾のみ
		// 複数弾の回転
		worldTransformSuitable_.rotation_.y += RotateSpeed;
		// 複数弾のタイマー
		SuitableTiming--;
		if (SuitableTiming <= 0) {
			SecondAttack();
		}
		for (SuitableBullet* suitablenum : suitableBulletNums_) {
			// 複数弾の更新
			suitablenum->Update();
		}
		break;
	case Phase::Third:
		// 敵の高さ変える
		worldTransformBase_.translation_.y = -5;
		//追尾弾のみ
		// 弾更新
		for (EnemyBullet* bullet : bullets_) {
			bullet->Update();
		}
		// 発射タイマーカウントダウン
		--fireTimer_;
		// 指定時間に達したら
		if (fireTimer_ <= 0) {
			// 弾を発射
			Fire();
			// 発射タイマーを初期化
			fireTimer_ = kFireInterval;
		}

		break;
	case Phase::Final:
		// 敵の高さ変える
		worldTransformBase_.translation_.y =-9;
		//複数弾の攻撃
		// 複数弾の回転
		worldTransformSuitable_.rotation_.y += RotateSpeed;
		// 複数弾のタイマー
		SuitableTiming--;
		if (SuitableTiming <= 0) {
			SecondAttack();
		}
		for (SuitableBullet* suitablenum : suitableBulletNums_) {
			// 複数弾の更新
			suitablenum->Update();
		}

		//追尾弾の攻撃
		// 弾更新
		for (EnemyBullet* bullet : bullets_) {
			bullet->Update();
		}
		// 発射タイマーカウントダウン
		--fireTimer_;
		// 指定時間に達したら
		if (fireTimer_ <= 0) {
			// 弾を発射
			Fire();
			// 発射タイマーを初期化
			fireTimer_ = kFireInterval;
		}

		break;
	}
	ImGui::Begin("window");
	ImGui::DragFloat("enemy", &worldTransformBase_.translation_.y);
	ImGui::End();
		

		// デスフラグの経った敵の削除
		suitableBulletNums_.remove_if([](SuitableBullet* enemynum) {
			if (enemynum->IsDead()) {
				delete enemynum;
				return true;
			}
			return false;
		});

		// 弾
		worldTransformSuitable_.UpdateMatrix();

	if (isfall_ == true) {

		fallcount += 0.1f;

		worldTransformBody3_.translation_.y -= 0.1f;
		worldTransformBody2_.translation_.y -= 0.1f;
		worldTransformBody1_.translation_.y -= 0.1f;
		worldTransformHead_.translation_.y -= 0.1f;

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
	

	 // 弾描画
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::SecondAttack() {
		  
		    const float kBulletSpeed = 0.4f;
			    Vector3 velocity(kBulletSpeed, 0, kBulletSpeed);

			    velocity = TransformNormal(velocity, worldTransformSuitable_.matWorld_);
	   
	        SuitableBullet* newSuitableBullet = new SuitableBullet();
		  // 複数弾の更新
	        newSuitableBullet->Initialize(
	            SuitableModel, worldTransformHead_.translation_, velocity);
				// 複数弾の登録
			   suitableBulletNums_.push_back(newSuitableBullet);
				//タイマー初期化
			    SuitableTiming =SuitableInterval ;
}

void Enemy::Fire() {

	            assert(player_);

	            // 弾の速度
	            const Vector3 kBulletSpeed = {-0.6f, 0.0f, -0.6f};
	            Vector3 velocity(kBulletSpeed.x, kBulletSpeed.y, kBulletSpeed.z);

	            Vector3 playerPos = player_->GetWorldPosition();
	            Vector3 enemyPos = this->GetWorldPosition();
	            Vector3 DiffVector = Subtract(enemyPos, playerPos);
	            velocity = Normalize(DiffVector);
	            velocity.x *= kBulletSpeed.x;
	            velocity.y *= kBulletSpeed.y;
	            velocity.z *= kBulletSpeed.z;

	            // 速度ベクトルを敵の向きに合わせて回転させる
	            velocity = TransformNormal(velocity, worldTransformHead_.matWorld_);

	            // 弾を発生し、初期化
	            EnemyBullet* newBullet = new EnemyBullet();
	            newBullet->Initialize(bulletModel_, worldTransformHead_.translation_, velocity);
	            // 弾を登録
	            bullets_.push_back(newBullet);
}



// 親子関係を結ぶ
void Enemy::SetParent(const WorldTransform* parent) { worldTransformBase_.parent_ = parent; }

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransformBase_.matWorld_.m[3][0];
	worldPos.y = worldTransformBase_.matWorld_.m[3][1];
	worldPos.z = worldTransformBase_.matWorld_.m[3][2];
	return worldPos;
}

float Enemy::GetworldRotY() {
	{ return worldTransformBase_.rotation_.y; }
}


void Enemy::OnCollision() {
	isDead_ = true;

	// isDelete_ = true;

	isfall_ = true;
}
