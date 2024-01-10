#include "PlayerBullet.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include "Mymath.h"
#include <TextureManager.h>

void PlayerBullet::Initalize(Model* model, const Vector3& position, const Vector3& velocity) {
	
	// ワールドトランスフォームの初期化
	// 引数で受け取った初期座標をセット
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	////因数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;



}

void PlayerBullet::Update() {

}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {

}

void PlayerBullet::OnCollision() {

}