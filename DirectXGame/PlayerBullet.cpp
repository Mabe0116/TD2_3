#include "PlayerBullet.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include "Mymath.h"
#include <TextureManager.h>

void PlayerBullet::Initalize(Model* model, const Vector3& position, const Vector3& velocity) {
	
	// ���[���h�g�����X�t�H�[���̏�����
	// �����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	////�����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;



}

void PlayerBullet::Update() {

}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {

}

void PlayerBullet::OnCollision() {

}