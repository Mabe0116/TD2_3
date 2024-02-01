#pragma once
#include "Model.h"
#include "PlayerBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <XInput.h>

// 前方宣言
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

	Vector3 GetWorldRotationPos();

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	void Reset();

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

	float angle = 90.0f;

	// 敵キャラ
	std::unique_ptr<Enemy> enemy_;
	// プレイヤーから敵に向かう差分ベクトル
	Vector3 DiffVector = {0, 0, 0};



public:
	// 親子関係を結ぶ
	void SetParent(const WorldTransform* parent) { worldTransformHead_.parent_ = parent; };
};