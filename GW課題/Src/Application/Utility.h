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

	//	ブロックとかの矩形データ用

	Math::Vector3		SIZE;		//	サイズ
	Math::Vector3		HALF_SIZE;	//	1/2 サイズ

	Math::Vector3			m_pos;		//	座標
	Math::Vector3			m_move;		//	移動量
	float					m_alpha;	//  透明度
	Math::Matrix			m_mat;		//	行列

	KdTexture* m_pTex;		//	テクスチャ
};

struct BASE
{
	Math::Vector3		SIZE;		//	サイズ
	Math::Vector3		HALF_SIZE;	//	1/2 サイズ

	Math::Vector3			m_pos;		//	座標
	float					m_alpha;	//	アルファ値				
	Math::Matrix			m_mat;		//	行列

	KdTexture* m_pTex;		//	テクスチャ
};
