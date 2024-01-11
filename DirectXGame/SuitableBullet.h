#pragma once
#include <WorldTransform.h>
#include <Model.h>

class SuitableBullet {
public:
	~SuitableBullet();
	void Initialize();
	void Update();
	void Draw();

	private:
	WorldTransform worldTransform_;
	    Model* model_ = nullptr;
};
