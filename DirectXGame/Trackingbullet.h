#pragma once
#include <WorldTransform.h>
#include <Model.h>

//追尾
class Trackingbullet {
public:
	~Trackingbullet();
	void Initialize(Model* bullet_);
	void Update();
	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
};
