#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Ground.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Skydome.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include <memory>
#include <DebugCamera.h>
#include "FollowCamera.h"
#include <memory>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// スプライト
	Sprite* sprite_ = nullptr;

	// 3Dモデル
	// Model* model_ = nullptr;
	std::unique_ptr<Model> model_;

	// スカイドーム3Dモデル
	// std::unique_ptr<Model> modelSkydome_;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

	float inputFloat3[3] = {0, 0, 0};

	// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;

	// 自キャラ
	// Player* player_ = nullptr;
	std::unique_ptr<Player> player_;

	// std::unique_ptr<Skydome> skydome_;
	Skydome* skydome_ = nullptr;

	Model* modelSkydome_ = nullptr;

	Ground* ground_ = nullptr;

	Model* modelGround_ = nullptr;

	// デバッグカメラ
	std::unique_ptr<DebugCamera> debugCamera_;
	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;
	// 追従カメラ
	std::unique_ptr<FollowCamera> followCamera_;

	// 自キャラ
	std::unique_ptr<Player> player_;
	// 3Dモデルデータ
	std::unique_ptr<Model> modelPlayerHead_;
	std::unique_ptr<Model> modelPlayerBody1_;
	std::unique_ptr<Model> modelPlayerBody2_;
	std::unique_ptr<Model> modelPlayerBody3_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
