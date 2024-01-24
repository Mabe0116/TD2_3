#include "PlayerBullet.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include "Mymath.h"
#include <TextureManager.h>

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);

	model_ = model;

	// ワールドトランスフォームの初期化
	// 引数で受け取った初期座標をセット
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	////因数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
}

void PlayerBullet::Update() {
	//座標を移動させる(1フレーム分の移動量を足しこむ)
	Move(worldTransform_.translation_,velocity_);

	//時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	worldTransform_.UpdateMatrix();

}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	
		// モデルの描画
		model_->Draw(worldTransform_, viewProjection);

}

void PlayerBullet::OnCollision() { 
	isDead_ = true; 

}

Vector3 PlayerBullet::GetWorldPosition() {
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}


