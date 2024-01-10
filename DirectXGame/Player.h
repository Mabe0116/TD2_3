#pragma once
#include "Model.h"
#include "WorldTransform.h"

class Player {
public:
	void Initialize(Model* head, Model* body1, Model* body2, Model* body3);

	void Update();

	void Draw(ViewProjection& viewProjection);

private:
	// ワールド変換データ
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformBody1_;
	WorldTransform worldTransformBody2_;
	WorldTransform worldTransformBody3_;
	// モデル
	Model* headModel_ = nullptr;
	Model* body1Model_ = nullptr;
	Model* body2Model_ = nullptr;
	Model* body3Model_ = nullptr;
};