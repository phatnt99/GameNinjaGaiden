#include "Alphabet.h"



Alphabet::Alphabet()
{
	texture = TextureManager::GetInstance()->GetTexture(eType::ALPHABET);
	sprite = new CSprite(texture, 0);
}



Alphabet::~Alphabet()
{
	SAFE_DELETE(sprite);
}

void Alphabet::Draw(float x, float y, const string & s)
{
	for (UINT i = 0; i < s.size(); i++)
	{
		if (s[i] == ' ')
			continue;
		if (s[i] >= 'A' && s[i] <= 'Z')
		{
			sprite->SelectFrame(s[i] - 'A');
		}
		else
			if (s[i] >= '0' && s[i] <= '9')
			{
				sprite->SelectFrame(s[i] - '0' + 26);
			}
			else
				sprite->SelectFrame(36);
		sprite->Draw(x + i * texture->GetFrameWidth(), y);
	}
}
