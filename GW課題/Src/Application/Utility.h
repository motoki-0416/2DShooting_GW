#pragma once

namespace Screen
{
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	const int HALF_WIDTH = WIDTH / 2;
	const int HALF_HEIGHT = HEIGHT / 2;	
}

namespace Alpha
{
	static const int MAX_ALPHA = 1;
	static const int MIN_ALPHA = 0;

}


struct OBJData {

	//	�u���b�N�Ƃ��̋�`�f�[�^�p

	Math::Vector3		SIZE;		//	�T�C�Y
	Math::Vector3		HALF_SIZE;	//	1/2 �T�C�Y

	Math::Vector3			m_pos;		//	���W
	Math::Vector3			m_move;		//	�ړ���
	float					m_alpha;	//  �����x
	Math::Matrix			m_mat;		//	�s��

	KdTexture* m_pTex;		//	�e�N�X�`��
};

struct BASE
{
	Math::Vector3		SIZE;		//	�T�C�Y
	Math::Vector3		HALF_SIZE;	//	1/2 �T�C�Y

	Math::Vector3			m_pos;		//	���W
	float					m_alpha;	//	�A���t�@�l				
	Math::Matrix			m_mat;		//	�s��

	KdTexture* m_pTex;		//	�e�N�X�`��
};
