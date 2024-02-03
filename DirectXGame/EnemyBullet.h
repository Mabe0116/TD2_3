#pragma once
#include <Model.h>
#include <WorldTransform.h>

class EnemyBullet {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);

	bool IsDead() const { return isDead_; }

	Vector3 GetWorldPosition();

	void OnCollision();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;

	// 速度
	Vector3 velocity_;

	// 寿命<frm>
	static const int32_t kLifeTime = 60 * 5;
	// デスフラグ
	bool isDead_ = false;
	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
};
