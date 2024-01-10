﻿#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "PlayerBullet.h"
#include <XInput.h>

class Player {
public:
	void Initialize(Model* head, Model* body1, Model* body2, Model* body3);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void Attack();

	const WorldTransform& GetWorldTransform() { return worldTransformHead_; }

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

private:
	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformBody1_;
	WorldTransform worldTransformBody2_;
	WorldTransform worldTransformBody3_;
	// モデル
	Model* headModel_ = nullptr;
	Model* body1Model_ = nullptr;
	Model* body2Model_ = nullptr;
	Model* body3Model_ = nullptr;

	std::list<PlayerBullet*> bullets_;

};