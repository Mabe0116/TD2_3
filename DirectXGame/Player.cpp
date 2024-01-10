﻿#include "Player.h"
#include <cassert>
#include <Input.h>
#include <Mymath.h>
#include <ImGuiManager.h>

void Player::Initialize(Model* model, uint32_t textureHandle) {
void Player::Initialize(Model* head, Model* body1, Model* body2, Model* body3) { 
	assert(head);
	headModel_ = head;
	assert(body1);
	body1Model_ = body1;
	assert(body2);
	body2Model_ = body2;
	assert(body3);
	body3Model_ = body3;

	worldTransformHead_.translation_ = {0, 0, 0};
	worldTransformBody1_.translation_ = {0, 0, 0};
	worldTransformBody2_.translation_ = {0, 0, 0};
	worldTransformBody3_.translation_ = {0, 0, 0};

	worldTransformHead_.Initialize();
	worldTransformBody1_.Initialize();
	worldTransformBody2_.Initialize();
	worldTransformBody3_.Initialize();
	// NULLポインタチェック
	assert(model);
	// 代入文の左側がメンバ変数。右側引数
	model_ = model;
	texturHandle_ = textureHandle;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
}

void Player::Update() {
	// ゲームパッドが有効の場合if文が通る
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		// 速さ
		float speed = 0.3f;

		// 移動量
	/*********
	// if () {}
	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;
		move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * speed;
		move.z += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * speed;

		// カメラの角度から回転行列を計算する
		Matrix4x4 RotationMatrix = MakeRotateMatrix(viewProjection_->rotation_);

		// オフセットをカメラの回転に合わせて回転させる
		move = TransformNormal(move, RotationMatrix);
	// 押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_LEFT)) {
	    move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
	    move.x += kCharacterSpeed;
	}

	// 押した方向で移動ベクトルを変更（上下）
	if (input_->PushKey(DIK_UP)) {
	    move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
	    move.y -= kCharacterSpeed;
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
	// 座標移動(ベクトルの加算)
	worldTransform_.translation_ += move;

	ImGui::Begin("window");
	ImGui::DragFloat3("player position", &worldTransformHead_.translation_.x);
	ImGui::End();

	*********/
}

void Player::Draw(ViewProjection& viewProjection) {
	// 3Dモデル描画
	headModel_->Draw(worldTransformHead_, viewProjection);
	body1Model_->Draw(worldTransformBody1_, viewProjection);
	body2Model_->Draw(worldTransformBody2_, viewProjection);
	body3Model_->Draw(worldTransformBody3_, viewProjection);
}
void Player::Draw() {}
