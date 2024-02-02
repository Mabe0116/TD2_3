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

	//フェード初期化
	/*uint32_t fadeTexturHandle = TextureManager::Load("scene/fade.png");
	fadeSprite_ = Sprite::Create(fadeTexturHandle, {0, 0});*/

	uint32_t fadeTitleTexturHandle = TextureManager::Load("scene/title.png");
	fadeTitleSprite = Sprite::Create(fadeTitleTexturHandle, {0, 0});
	
	uint32_t fadeOperationTexturHandle = TextureManager::Load("scene/operation.png");
	fadeOperationSprite_ = Sprite::Create(fadeOperationTexturHandle, {0, 0});

	FadeFake_ = TextureManager::Load("scene/fade.png");
	TitleTexture_ = TextureManager::Load("scene/title.png");
	OperationTexture_ = TextureManager::Load("scene/operation.png");
	ClearTexture_ = TextureManager::Load("scene/clear.png");

	FadeFakeSprite = std::make_unique<Sprite>();
	TitleSprite_ = std::make_unique<Sprite>();
	//OperationSprite_ = std::make_unique<Sprite>();
	ClearSprite_ = std::make_unique<Sprite>();

	FadeFakeSprite.reset(Sprite::Create(FadeFake_, {0, 0}));
	TitleSprite_.reset(Sprite::Create(TitleTexture_, {0, 0}));
	//OperationSprite_.reset(Sprite::Create(OperationTexture_, {0, 0}));
	ClearSprite_.reset(Sprite::Create(ClearTexture_, {0, 0}));


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
	    modelEnemyBody3_.get());

	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_.get());

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
	// フェード更新
	//fadeColor_.w += 0.005f;
	//fadeSprite_->SetColor(fadeColor_);
	

	switch (scene) {
	case GameScene::TITLE: // タイトルシーン

		audio_->StopWave(Gamevoice_);
	
		fadeTitleColor_.w += 0.05f;
		fadeTitleSprite->SetColor(fadeTitleColor_);

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
		fadeOperationColor_.w += 0.05f;
		fadeOperationSprite_->SetColor(fadeOperationColor_);

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
		fadeOperationColor_.w -= 0.005f;
		fadeOperationSprite_->SetColor(fadeOperationColor_);
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
		};
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
		//TitleSprite_->Draw();
		// フェード描画
		FadeFakeSprite->Draw();
		fadeTitleSprite->Draw();
	}
	if (scene == OPERATION) {
		TitleSprite_->Draw();
		fadeOperationSprite_->Draw();
	}
	if (scene == CLEAR) {
		ClearSprite_->Draw();
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

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollision() {

	Vector3 posA, posB;

	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

	posA = enemy_->GetWorldPosition();

	for (PlayerBullet* bullet : playerBullets) {

		posB = bullet->GetWorldPosition();

		float X = (posB.x - posA.x);
		float Y = (posB.y - posA.y);
		float Z = (posB.z - posA.z);

		float center = sqrtf(X * X + Y * Y + Z * Z);
		float R1 = 1.5f; // 自分で決める
		float R2 = 0.5f; // 自分で決める
		float RR = (R1 + R2);

		if (center <= RR) {
			// 敵キャラの衝突時コールバックを呼び出す
			enemy_->OnCollision();
			// 自弾の衝突時コールバックを呼び出す
			bullet->OnCollision();

			ImGui::Begin("a");
			ImGui::End();

			EnemyLife--;

		}
	}
}
