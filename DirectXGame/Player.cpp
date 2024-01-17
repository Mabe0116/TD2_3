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


	worldTransformHead_.translation_ = {0, 1.0f, 0};
	worldTransformBody1_.translation_ = {0, 1.0f, 0};
	worldTransformBody2_.translation_ = {0, 1.0f, 0};
	worldTransformBody3_.translation_ = {0, 1.0f, 0};

	worldTransformHead_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformBody1_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformBody2_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformBody3_.scale_ = {0.5f, 0.5f, 0.5f};

	worldTransformHead_.Initialize();
	worldTransformBody1_.Initialize();
	worldTransformBody2_.Initialize();
	worldTransformBody3_.Initialize();
}

void Player::Update() {

	// 半径
	float radius = 50.0f;
	// ラジアン
	float radian = angle * 3.14f / 180.0f;
	float add_x = 0;
	float add_z = 0;
	add_x = cosf(radian) * radius;
	add_z = sinf(radian) * radius;

	// ゲームパッドが有効の場合if文が通る
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		// 速さ
		float speed = 0.3f;
		// 移動量
		Vector3 move = {0, 0, 0};

		angle += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * speed;
		angle += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * speed;

		// カメラの角度から回転行列を計算する
		Matrix4x4 RotationMatrix = MakeRotateMatrix(viewProjection_->rotation_);

		// オフセットをカメラの回転に合わせて回転させる
		move = TransformNormal(move, RotationMatrix);

		worldTransformHead_.rotation_.y = std::atan2(move.x, move.z);
		worldTransformBody1_.rotation_.y = std::atan2(move.x, move.z);
		worldTransformBody2_.rotation_.y = std::atan2(move.x, move.z);
		worldTransformBody3_.rotation_.y = std::atan2(move.x, move.z);
		
		// 結果ででた位置を中心位置に加算し、それを描画位置とする
		worldTransformHead_.translation_.x = add_x;
		worldTransformHead_.translation_.z = add_z;
		worldTransformBody1_.translation_.x = add_x;
		worldTransformBody1_.translation_.z = add_z;
		worldTransformBody2_.translation_.x = add_x;
		worldTransformBody2_.translation_.z = add_z;
		worldTransformBody3_.translation_.x = add_x;
		worldTransformBody3_.translation_.z = add_z;


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
	ImGui::DragFloat3("player head", &worldTransformHead_.translation_.x);
	ImGui::DragFloat3("player body1", &worldTransformBody1_.translation_.x);
	ImGui::DragFloat3("player body2", &worldTransformBody2_.translation_.x);
	ImGui::DragFloat3("player body3", &worldTransformBody3_.translation_.x);
	ImGui::DragFloat("angle", &angle);
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


