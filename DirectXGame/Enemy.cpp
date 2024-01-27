#include "Enemy.h"
#include <Mymath.h>
#include <cassert>

Enemy::~Enemy() { 
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Enemy::Initialize(Model* head, Model* body1, Model* body2, Model* body3) {
	assert(head);
	headModel_ = head;
	assert(body1);
	bodyModel1_ = body1;
	assert(body2);
	bodyModel2_ = body2;
	assert(body3);
	bodyModel3_ = body3;

	bulletModel_ = Model::CreateFromOBJ("cube", true);

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

	worldTransformHead_.translation_ = {0, 2.0f, 0};
	worldTransformBody1_.translation_ = {0, 0, 0};
	worldTransformBody2_.translation_ = {0, 0, 0};
	worldTransformBody3_.translation_ = {0, 0, 0};

	// 発射タイマーを初期化
	fireTimer_ = kFireInterval;
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

	 // 弾描画
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::Fire() {
	// 弾の速度
	 const float kBulletSpeed = -0.1f;
	 Vector3 velocity(0, 0, kBulletSpeed);
	 // 速度ベクトルを敵の向きに合わせて回転させる
	 velocity = TransformNormal(velocity, worldTransformHead_.matWorld_);

	 // 弾を発生し、初期化
	 EnemyBullet* newBullet = new EnemyBullet();
	 newBullet->Initialize(bulletModel_, worldTransformHead_.translation_, velocity);
	 // 弾を登録
	 bullets_.push_back(newBullet);
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

void Enemy::OnCollision() { isDead_ = true; }
