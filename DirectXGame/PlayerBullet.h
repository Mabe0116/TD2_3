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
	//ワールド座標データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//速度
	Vector3 velocity_;
	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;

};
