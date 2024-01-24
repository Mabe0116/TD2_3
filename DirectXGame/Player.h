#pragma once
#include "Model.h"
#include "PlayerBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <XInput.h>

class Enemy;

class Player {
public:
	void Initialize(Model* head, Model* body1, Model* body2, Model* body3, Model* PlayerBullet);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void Attack();

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();
	Vector3 GetWorldPosition();
	// 弾リストを取得
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

	const WorldTransform& GetWorldTransform() { return worldTransformHead_; }

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	void SetEnemy(Enemy* enemy) { enemy_ = enemy; }

private:
	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransform_;
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

	int32_t BulletTimer = 0;

	Model* ModelPlayerBullet_ = nullptr;

	float angle = 1.0f;

	Enemy* enemy_ = nullptr;
};