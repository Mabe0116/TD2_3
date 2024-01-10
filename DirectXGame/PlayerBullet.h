#pragma once
#include "Model.h"
#include "WorldTransform.h"


class PlayerBullet {
public: 
	void Initalize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void OnCollision();

	// 寿命<frm>
	static const int32_t kLifeTime = 60 * 5;

	bool IsDead() const { return isDead_; }

	Vector3 GetWorldPosition();

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Vector3 velocity_;

	// デスフラグ
	bool isDead_ = false;

};
