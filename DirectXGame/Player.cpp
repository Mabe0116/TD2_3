#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle) {

	// NULLポインタチェック
	assert(model);
	// 代入文の左側がメンバ変数。右側引数
	model_ = model;
	texturHandle_ = textureHandle;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
}

void Player::Update() {

	/*********
	// if () {}
	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

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
	}

	// 座標移動(ベクトルの加算)
	worldTransform_.translation_ += move;


	*********/
}

void Player::Draw() {}
