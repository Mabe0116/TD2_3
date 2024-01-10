#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <XInput.h>

class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);
	void Initialize(Model* head, Model* body1, Model* body2, Model* body3);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	void Draw(ViewProjection& viewProjection);

	const WorldTransform& GetWorldTransform() { return worldTransformHead_; }

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}
	/// <summary>
	/// 　描画
	/// </summary>
	void Draw();

private:
	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformBody1_;
	WorldTransform worldTransformBody2_;
	WorldTransform worldTransformBody3_;
	WorldTransform worldTransform_;
	// モデル
	Model* headModel_ = nullptr;
	Model* body1Model_ = nullptr;
	Model* body2Model_ = nullptr;
	Model* body3Model_ = nullptr;
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t texturHandle_ = 0u;
	// キーボード入力
	Input* input_ = nullptr;
};
