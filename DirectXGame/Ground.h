#pragma once
#include "Model.h"
#include "WorldTransform.h"

class Ground {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(const ViewProjection& viewprojection);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	// groundモデル
	Model* model_ = nullptr;
};
