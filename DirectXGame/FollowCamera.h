#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Enemy.h"

class FollowCamera {
public:
	void Initialize();

	void Update();

	void SetTarget(const WorldTransform* target) { target_ = target; }

	const ViewProjection& GetViewProjection() { return viewProjection_; }

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	// ビュープロジェクション
	ViewProjection viewProjection_;

	// 追従対象
	const WorldTransform* target_ = nullptr;

	WorldTransform worldTransform_;

	// 敵キャラ
	std::unique_ptr<Enemy> enemy_;
	// カメラ;から敵に向かう差分ベクトル
	Vector3 DiffVector = {0, 0, 0};
};