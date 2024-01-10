#pragma once
#include "Model.h"
#include "WorldTransform.h"


class PlayerBullet {
public: 
	void Initalize();

	void Update();

	void Draw();

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Vector3 velocity_;


};
