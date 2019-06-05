#include "Board.h"

string Board::FillNumber(string s, UINT MaxNumber)
{
	while (s.size() < MaxNumber)
		s = "0" + s;
	return s;
}

Board::Board(float X, float Y)
{
	texture = TextureManager::GetInstance()->GetTexture(eType::BOARD);
	sprite = new CSprite(texture, 0);

	//_spriteIconDoubleShot = new GSprite(TextureManager::GetInstance()->GetTexture(eType::ITEMDOUBLESHOT), 0);

	x = X;
	y = Y;

	boardHealth = new BoardHealth(x + 389, y + 50);
}


void Board::Render(Ninja * ninja, int state1, int state2, int RemainingTime, Boss *boss)
{
	sprite->Draw(x, y);

	//điểm
	alpha.Draw(x + 161, y + 30, FillNumber(std::to_string(ninja->GetScore()), 6));

	alpha.Draw(x + 161, y + 48, FillNumber(std::to_string(RemainingTime), 3));

	alpha.Draw(x + 392, y + 30, FillNumber(std::to_string(state1), 1));

	alpha.Draw(x + 427, y + 30, FillNumber(std::to_string(state2), 1));

	//số lượng strength
	alpha.Draw(x + 178, y + 65, FillNumber(std::to_string(ninja->GetStrength()), 2)); 
	
	alpha.Draw(x + 90, y + 65, FillNumber(std::to_string(ninja->GetLives()), 2)); // số mạng sông


	int BloodBoss = 16;
	if (boss != NULL)
	{
		BloodBoss = (int)(boss->GetHealth());// HEALTH =16 -> 16 vạch
		if (BloodBoss == 0 && boss->GetHealth() > 0)
			BloodBoss = 1;
	}

	boardHealth->Draw(ninja->GetHealth(), BloodBoss);

	// vẽ icon vũ khí phụ
	switch (ninja->GetTypeWeaponCollect())
	{
	case eType::WPTHROWINGSTAR:
		WPThrowingStar::getInstance()->RenderIcon(x + 229, y + 52);
		break;
	case eType::WPFIREWHEEL:
		WPFireWheel::getInstance()->RenderIcon(x + 229, y + 52);
		break;
	case eType::WPWINDMILLSTAR:
		WPWindmillStar::getInstance()->RenderIcon(x + 229, y + 52);
		break;
	default:
		break;
	}

	//if (simon->GetIsUseDoubleShot())
	//{
	//	_spriteIconDoubleShot->Draw(x + 465, y + 35);
	//}
}


Board::~Board()
{
	SAFE_DELETE(sprite);
}

void Board::SetTexture(CTexture * tex)
{
	texture = tex;
	sprite->texture = tex;
}
