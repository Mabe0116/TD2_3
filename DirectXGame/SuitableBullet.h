#pragma once
#include <WorldTransform.h>
#include <Model.h>

class SuitableBullet {
public:
	void Initialize(Model* bullet_, const Vector3& position, const Vector3& velocity);
	void Update();
	void Draw(ViewProjection& viewProjection);
	bool IsDead() const { return isDead_; }

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	private:
	WorldTransform worldTransform_;
	    Model* model_ = nullptr;
		//寿命
	static const int32_t kLifeTime = 60 * 20;
	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;
	// 速度
	Vector3 velocity_ = {0.2f, 0, 0.2f};
	;
};
