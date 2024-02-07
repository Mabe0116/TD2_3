#include "Player.h"
#include "Enemy.h"
#include "PlayerBullet.h"
#include <ImGuiManager.h>
#include <Input.h>
#include <Mymath.h>
#include <ImGuiManager.h>
#include "Enemy.h"

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

	// 敵キャラの生成
	enemy_ = std::make_unique<Enemy>();

	worldTransformHead_.translation_ = {0, 1.0f, 0};
	worldTransformBody1_.translation_ = {0, 1.0f, 0};
	worldTransformBody2_.translation_ = {0, 1.0f, 0};
	worldTransformBody3_.translation_ = {0, 1.0f, 0};

	worldTransformHead_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformBody1_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformBody2_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformBody3_.scale_ = {0.5f, 0.5f, 0.5f};

	worldTransform_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformBody1_.Initialize();
	worldTransformBody2_.Initialize();
	worldTransformBody3_.Initialize();

	//worldTransformHead_.parent_ = &worldTransform_;
	//// ボディ1の親をヘッドにする
	//worldTransformBody1_.parent_ = &worldTransform_;
	//// ボディ2の親をヘッドにする
	//worldTransformBody2_.parent_ = &worldTransform_;
	//// ボディ3の親をヘッドにする
	//worldTransformBody3_.parent_ = &worldTransform_;

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

	// プレイヤーから敵に向かう差分ベクトル
	DiffVector.x = enemy_->GetWorldPosition().x - worldTransformHead_.translation_.x;
	DiffVector.z = enemy_->GetWorldPosition().z - worldTransformHead_.translation_.z;

	worldTransformHead_.rotation_.y = std::atan2(DiffVector.x, DiffVector.z);
	worldTransformBody1_.rotation_.y = std::atan2(DiffVector.x, DiffVector.z);
	worldTransformBody2_.rotation_.y = std::atan2(DiffVector.x, DiffVector.z);
	worldTransformBody3_.rotation_.y = std::atan2(DiffVector.x, DiffVector.z);

	// ゲームパッドが有効の場合if文が通る
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		// 速さ
		float speed = 0.3f;
		// 移動量
		Vector3 move = {0, 0, 0};

		angle += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * speed;
		angle += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * speed;

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

	if (isfall_ == true) {
		fallcount += 0.1f;

		worldTransformHead_.translation_.y -= 0.1f;
		worldTransformBody1_.translation_.y -= 0.1f;
		worldTransformBody2_.translation_.y -= 0.1f;
		worldTransformBody3_.translation_.y -= 0.1f;

		if (fallcount >= 1.3f) {
			isfall_ = false;
			fallcount = 0;
		}
	}

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

	worldTransform_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformBody1_.UpdateMatrix();
	worldTransformBody2_.UpdateMatrix();
	worldTransformBody3_.UpdateMatrix();
}

void Player::Attack() {

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			if (--BulletTimer < 0) {
				BulletTimer = 120;

				//// 弾の速度
				const float kBulletSpeed = 1.0f;
				Vector3 sub =
				    Subtract(enemy_->GetWorldTransform().translation_, GetWorldPosition());
				/*sub.y += 5.0f;*/
				sub = Normalize(sub);
				Vector3 velocity{};
				velocity.x = sub.x * kBulletSpeed;
				velocity.y = sub.y * kBulletSpeed;
				velocity.z = sub.z * kBulletSpeed;

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

void Player::OnCollision() { 
	isDead_ = true; 

	isfall_ = true;
}

Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransformHead_.matWorld_.m[3][0];
	worldPos.y = worldTransformHead_.matWorld_.m[3][1];
	worldPos.z = worldTransformHead_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 Player::GetWorldRotationPos() { 
	Vector3 worldRotationPos;

	worldRotationPos.x = worldTransformHead_.rotation_.x;
	worldRotationPos.y = worldTransformHead_.rotation_.y;
	worldRotationPos.z = worldTransformHead_.rotation_.z;

	return worldRotationPos;
}

void Player::Reset() {
	worldTransformHead_.translation_ = {0, 1.0f, 0};
	worldTransformBody1_.translation_ = {0, 1.0f, 0};
	worldTransformBody2_.translation_ = {0, 1.0f, 0};
	worldTransformBody3_.translation_ = {0, 1.0f, 0};

	isfall_ = false;
}
