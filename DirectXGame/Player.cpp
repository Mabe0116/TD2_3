#include "Player.h"
#include "PlayerBullet.h"
#include <cassert>
#include <Input.h>
#include <Mymath.h>
#include <ImGuiManager.h>


void Player::Initialize(Model* head, Model* body1, Model* body2, Model* body3,Model* PlayerBullet) { 
	assert(head);
	headModel_ = head;

	assert(body1);
	body1Model_ = body1;
	
	assert(body2);
	body2Model_ = body2;
	
	assert(body3);
	body3Model_ = body3;
	
	assert(PlayerBullet);
	ModelPlayerBullet_ = PlayerBullet;


	worldTransformHead_.translation_ = {0, 0, 0};
	worldTransformBody1_.translation_ = {0, 0, 0};
	worldTransformBody2_.translation_ = {0, 0, 0};
	worldTransformBody3_.translation_ = {0, 0, 0};

	worldTransformHead_.Initialize();
	worldTransformBody1_.Initialize();
	worldTransformBody2_.Initialize();
	worldTransformBody3_.Initialize();
}

void Player::Update() {
	// ゲームパッドが有効の場合if文が通る
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		// 速さ
		float speed = 0.3f;

		// 移動量
		Vector3 move = {0, 0, 0};

		move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * speed;
		move.z += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * speed;

		// カメラの角度から回転行列を計算する
		Matrix4x4 RotationMatrix = MakeRotateMatrix(viewProjection_->rotation_);

		// オフセットをカメラの回転に合わせて回転させる
		move = TransformNormal(move, RotationMatrix);

		worldTransformHead_.rotation_.y = std::atan2(move.x, move.z);
		worldTransformBody1_.rotation_.y = std::atan2(move.x, move.z);
		worldTransformBody2_.rotation_.y = std::atan2(move.x, move.z);
		worldTransformBody3_.rotation_.y = std::atan2(move.x, move.z);

		worldTransformHead_.translation_ = Add(worldTransformHead_.translation_, move);
		worldTransformBody1_.translation_ = Add(worldTransformBody1_.translation_, move);
		worldTransformBody2_.translation_ = Add(worldTransformBody2_.translation_, move);
		worldTransformBody3_.translation_ = Add(worldTransformBody3_.translation_, move);
	}

	worldTransformHead_.UpdateMatrix();
	worldTransformBody1_.UpdateMatrix();
	worldTransformBody2_.UpdateMatrix();
	worldTransformBody3_.UpdateMatrix();

	// デスフラグの立った弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// キャラクターの攻撃処理
	Attack();

	// 弾更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}


	ImGui::Begin("window");
	ImGui::DragFloat3("player position", &worldTransformHead_.translation_.x);
	ImGui::End();

}

void Player::Draw(ViewProjection& viewProjection) {
	// 3Dモデル描画
	headModel_->Draw(worldTransformHead_, viewProjection);
	body1Model_->Draw(worldTransformBody1_, viewProjection);
	body2Model_->Draw(worldTransformBody2_, viewProjection);
	body3Model_->Draw(worldTransformBody3_, viewProjection);

	 for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}

}

void Player::Attack() {

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			if (--BulletTimer < 0) {
				BulletTimer = 30;

				// 弾の速度
				const float kBulletSpeed = 1.0f;
				Vector3 velocity(0, 0, kBulletSpeed);

				Vector3 N = Normalize(velocity);

				velocity.x = N.x * kBulletSpeed;

				velocity.y = N.y * kBulletSpeed;

				velocity.z = N.z * kBulletSpeed;

				// 弾を生成し、初期化
				PlayerBullet* newBullet = new PlayerBullet();
				Vector3 position = GetWorldPosition();
				position.y = 1.0f;
				newBullet->Initialize(ModelPlayerBullet_, position, velocity);

				// 弾を登録する
				bullets_.push_back(newBullet);
			}
		}
	}
}

void Player::OnCollision() {}

Vector3 Player::GetWorldPosition() {




	return Vector3(); 

}


