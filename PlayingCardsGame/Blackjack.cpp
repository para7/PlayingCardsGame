#include "Blackjack.hpp"

using namespace s3d::PlayingCard;

Blackjack::Blackjack(const InitData& init)
	: IScene(init)
	, pack(90)
{
	scene = start;
}

void Blackjack::update()
{
	switch (scene)
	{
	case start:
		deck.Shuffle();

		playerhand = deck.CardDraw(2);
		dealerhand = deck.CardDraw(2);

		scene = select;

		break;
	}
}

void Blackjack::draw() const
{
	for (int i = 0; i < playerhand.size(); ++i)
	{
		pack(playerhand[i]).drawAt(300 + (pack.width() +15) *i, 550);
	}
}