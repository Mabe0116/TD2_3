#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "FollowCamera.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <DebugCamera.h>
#include <memory>
#include "Skydome.h"
#include "Ground.h"

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

	// 3Dモデルデータ
	std::unique_ptr<Model> model_;

	
	// ワールドトランスフォーム
	WorldTransform worldTransform_;

	// ビュープロジェクション
	ViewProjection viewProjection_;

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

	// 敵キャラ
	std::unique_ptr<Enemy> enemy_;
	// 3Dモデル
	std::unique_ptr<Model> modelEnemyHead_;
	std::unique_ptr<Model> modelEnemyBody1_;
	std::unique_ptr<Model> modelEnemyBody2_;
	std::unique_ptr<Model> modelEnemyBody3_;

	Skydome* skydome_ = nullptr;

	Model* modelSkydome_ = nullptr;

	Ground* ground_ = nullptr;

	Model* modelGround_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};