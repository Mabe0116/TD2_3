#pragma once
#include <WorldTransform.h>
#include <Model.h>

class SuitableBullet {
public:
	~SuitableBullet();
	void Initialize(Model* bullet_);
	void Update();
	void Draw(ViewProjection& viewProjection);

	private:
	WorldTransform worldTransform_;
	    Model* model_ = nullptr;
};
