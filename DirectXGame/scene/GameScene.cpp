#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <ImGuiManager.h>
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete modelSkydome_;
	delete skydome_;
	delete modelGround_;
	delete ground_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 3Dモデルデータの生成
	model_.reset(Model::Create());

	TitleTexture_ = TextureManager::Load("scene/title.png");
	OperationTexture_ = TextureManager::Load("scene/operation.png");
	ClearTexture_ = TextureManager::Load("scene/clear.png");
	GameOperationTexture_ = TextureManager::Load("scene/gameoperation.png");
	GameOverTexture_ = TextureManager::Load("scene/gameover.png");

	TitleSprite_ = std::make_unique<Sprite>();
	OperationSprite_ = std::make_unique<Sprite>();
	ClearSprite_ = std::make_unique<Sprite>();
	GameOperationSprite_ = std::make_unique<Sprite>();
	GameOverSprite_ = std::make_unique<Sprite>();

	TitleSprite_.reset(Sprite::Create(TitleTexture_, {0, 0}));
	OperationSprite_.reset(Sprite::Create(OperationTexture_, {0, 0}));
	ClearSprite_.reset(Sprite::Create(ClearTexture_, {0, 0}));
	GameOperationSprite_.reset(Sprite::Create(GameOperationTexture_, {900, 500}));
	GameOverSprite_.reset(Sprite::Create(GameOverTexture_, {0, 0}));

	//サウンド読み込み
	GameSound_ = audio_->LoadWave("game.wav");



	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	modelGround_ = Model::CreateFromOBJ("ground", true);

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	viewProjection_.translation_ = {
	    0.0f,
	    1.0f,
	    0.0f,
	};

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	viewProjection_.farZ = 1400.0f;

	// 自キャラの生成
	player_ = std::make_unique<Player>();
	// 3Dモデルの生成
	modelPlayerHead_.reset(Model::CreateFromOBJ("player_Head", true));
	modelPlayerBody1_.reset(Model::CreateFromOBJ("player_Body1", true));
	modelPlayerBody2_.reset(Model::CreateFromOBJ("player_Body2", true));
	modelPlayerBody3_.reset(Model::CreateFromOBJ("player_Body3", true));

	modelPlayerBullet_.reset(Model::CreateFromOBJ("PlayerBullet1", true));

	// 自キャラの初期化
	player_->Initialize(
	    modelPlayerHead_.get(), modelPlayerBody1_.get(), modelPlayerBody2_.get(),
	    modelPlayerBody3_.get(), modelPlayerBullet_.get());

	// 敵キャラの生成
	enemy_ = std::make_unique<Enemy>();
	// 3Dモデルの生成
	modelEnemyHead_.reset(Model::CreateFromOBJ("Enemy_Head", true));
	modelEnemyBody1_.reset(Model::CreateFromOBJ("Enemy_Body1", true));
	modelEnemyBody2_.reset(Model::CreateFromOBJ("Enemy_Body2", true));
	modelEnemyBody3_.reset(Model::CreateFromOBJ("Enemy_Body3", true));
	// 敵キャラの初期化
	enemy_->Initialize(
	    modelEnemyHead_.get(), modelEnemyBody1_.get(), modelEnemyBody2_.get(),
	    modelEnemyBody3_.get()/*, modelSuitableBullet_.get()*/);


	//敵の弾
	//追尾
	//trackingBullet_ = std::make_unique<Trackingbullet>();
	// 3Dモデルの生成
	//modelTrackingBullet_.reset(Model::CreateFromOBJ("bullet", true));
	// 追尾弾の初期化
	//trackingBullet_->Initialize(modelTrackingBullet_.get());

	//複数
	//suitableBullet_ = std::make_unique<SuitableBullet>();
	// 3Dモデルの生成
	//modelSuitableBullet_.reset(Model::CreateFromOBJ("Enemy_Head", true));
	// 複数弾の初期化
	/*suitableBullet_->Initialize(
	    modelSuitableBullet_.get(), worldTransformsu.translation_, velocity_);*/

	// デバッグカメラの生成
	debugCamera_ = std::make_unique<DebugCamera>(2000, 2000);

	// 追従カメラの生成
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();

	// 自キャラに追従カメラのビュープロジェクションをアドレス渡しする
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	// 自キャラのワールドトランスフォームを追従カメラにセット
	followCamera_->SetTarget(&player_->GetWorldTransform());

	// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する (アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	// skydomeの生成
	skydome_ = new Skydome();
	ground_ = new Ground();

	// skydomeの初期化
	skydome_->Initialize(modelSkydome_);

	ground_->Initialize(modelGround_);


	


}

void GameScene::Update() {
	
	switch (scene) {
	case GameScene::TITLE: // タイトルシーン

		//audio_->StopWave(Gamevoice_);
	
		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			if (Input::GetInstance()->GetJoystickStatePrevious(0, prevjoyState)) {
				if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A &&
				    !(prevjoyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {

					scene = OPERATION;
				}
			}
		}
			//コントローラー忘れた
			/*if (input_->TriggerKey(DIK_SPACE)) {
				scene = OPERATION;
			}*/

		break;

	case GameScene::OPERATION: // 操作説明
		
		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			if (Input::GetInstance()->GetJoystickStatePrevious(0, prevjoyState)) {
				if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A &&
				    !(prevjoyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
					scene = GAME;
				}
			}
		}

			// コントローラー忘れた
			/*if (input_->TriggerKey(DIK_SPACE)) {
				scene = GAME;
			}*/

	
		break;

	case GameScene::GAME:

		if (!audio_->IsPlaying(voiceHandle_)) {
			voiceHandle_ = audio_->PlayWave(Gamevoice_, true, 0.5);
		}

		audio_->ResumeWave(voiceHandle_);

		// 自キャラの更新
		player_->Update();

	// 敵キャラの更新
	enemy_->Update();
	

		skydome_->Update();

		// デバッグカメラの更新
		debugCamera_->Update();

			
#ifdef _DEBUG
		if (input_->TriggerKey(DIK_RETURN)) {
			isDebugCameraActive_ = true;
		}
#endif
		// カメラの処理
		if (isDebugCameraActive_) {
			debugCamera_->Update();
			viewProjection_.matView = debugCamera_->GetViewProjection().matView;
			viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
			// ビュープロジェクション行列の転送
			viewProjection_.TransferMatrix();
		} else if (isDebugCameraActive_ == false) {
			// 追従カメラの更新
			followCamera_->Update();
			viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
			viewProjection_.matView = followCamera_->GetViewProjection().matView;
			viewProjection_.TransferMatrix();

			//Gameoverにいく
				if (Input::GetInstance()->GetJoystickState(0, joyState)) {
				if (Input::GetInstance()->GetJoystickStatePrevious(0, prevjoyState)) {
					if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A &&
					    !(prevjoyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {

						scene = GAMEOVER;
					}
				}
			}



				// Gameclearにいく
			if (Input::GetInstance()->GetJoystickState(0, joyState)) {
				if (Input::GetInstance()->GetJoystickStatePrevious(0, prevjoyState)) {
					if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B &&
					    !(prevjoyState.Gamepad.wButtons & XINPUT_GAMEPAD_B)) {

						scene = CLEAR;
					}
				}
			}


		};
		break;


		case GameScene::GAMEOVER:

		    player_->Reset();

		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			if (Input::GetInstance()->GetJoystickStatePrevious(0, prevjoyState)) {
				if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A &&
				    !(prevjoyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
					scene = TITLE;
				}
			}
		}
		break;


		case GameScene::CLEAR:
		audio_->StopWave(Gamevoice_);
	
			player_->Reset();

		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			if (Input::GetInstance()->GetJoystickStatePrevious(0, prevjoyState)) {
				if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A &&
				    !(prevjoyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
					scene = TITLE;
				}
			}
		}
		break;



	}

	

	

	CheckAllCollision();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	if (scene == TITLE) {
		TitleSprite_->Draw();
	}
	if (scene == OPERATION) {
		OperationSprite_->Draw();
	}
	
	if (scene == CLEAR) {
		ClearSprite_->Draw();
	}

	if (scene == GAMEOVER) {
		GameOverSprite_->Draw();
	}

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	if (scene == GAME) {

		skydome_->Draw(viewProjection_);

		ground_->Draw(viewProjection_);
		
		/// <summary>
		/// ここに3Dオブジェクトの描画処理を追加できる
		/// </summary>

		// 自キャラの描画
		player_->Draw(viewProjection_);
		// 敵キャラの描画
		enemy_->Draw(viewProjection_);
		// 敵の弾の描画
		//trackingBullet_->Draw(viewProjection_);
		//suitableBullet_->Draw(viewProjection_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	if (scene == GAME) {
		GameOperationSprite_->Draw();
	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollision() {

	//// 判定対象AとBの座標
	// Vector3 posA, posB;

	//// 自弾リストの取得
	// const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
}
