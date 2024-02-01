#include "SuitableBullet.h"
#include <cassert>
#include <ImGuiManager.h>
#include <Mymath.h>

void SuitableBullet::Initialize(Model* bullet, const Vector3& position, const Vector3& velocity) {
	assert(bullet);
	model_ = bullet;

	//初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	//worldTransform_.scale_ = {0.3f, 0.3f, 0.3f};

	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;

	//deathTimer_ = 0;

	//isDead_ = false;
}

void SuitableBullet::Update() {

	// 時間経過でデス
	if (--deathTimer_ >= 6000) {
		isDead_ = true;
		deathTimer_ = 0;
	}
	
	// 座標を移動させる(1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	

	worldTransform_.UpdateMatrix(); 
}

void SuitableBullet::Draw(ViewProjection& viewProjection_) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection_);
}
