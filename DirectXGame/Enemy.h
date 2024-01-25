#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

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

private:
	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformBody1_;
	WorldTransform worldTransformBody2_;
	WorldTransform worldTransformBody3_;
	// モデル
	Model* headModel_ = nullptr;
	Model* bodyModel1_ = nullptr;
	Model* bodyModel2_ = nullptr;
	Model* bodyModel3_ = nullptr;

	// デスフラグ
	bool isDead_ = false;
};