#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "EnemyBullet.h"

class Enemy {
public:
	~Enemy();

	void Initialize(Model* head, Model* body1, Model* body2, Model* body3);

	void Update();

	void Draw(ViewProjection& viewProjection);

	const WorldTransform& GetWorldTransform() { return worldTransformHead_; }

	// 親となるワールドトランスフォーム
	void SetParent(const WorldTransform* parent);

	// 当たり判定
	void OnCollision();

	Vector3 GetWorldPosition();

	void SetVelocity(const Vector3& velocity);

private:
	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransformBase_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformBody1_;
	WorldTransform worldTransformBody2_;
	WorldTransform worldTransformBody3_;
	// モデル
	Model* headModel_ = nullptr;
	Model* bodyModel1_ = nullptr;
	Model* bodyModel2_ = nullptr;
	Model* bodyModel3_ = nullptr;

	// 敵キャラ
	std::unique_ptr<EnemyBullet> enemyBullet_;

	// デスフラグ
	bool isDead_ = false;

	bool isDelete_ = false;

	//敵落下
	bool isfall_ = false;

	float fallcount = 0;

	//体がはじかれたかを判別するフラグ
	bool isThrown_[4]{};
	//飛ばされる速度ベクトル
	Vector3 velocity_[4]{};
};