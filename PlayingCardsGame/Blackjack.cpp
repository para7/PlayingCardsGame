#include "Blackjack.hpp"

using namespace s3d::PlayingCard;

Blackjack::Blackjack(const InitData& init)
	: IScene(init)
	, pack(90)
	, fScore(45)
	, hit(RoundRect(Arg::center(Vec2(370 + 150 * 0, Window::Height() / 2)), 130, 70, 20), Palette::Orange,
		[&]() { player.hand.push_back(deck.CardDraw()); }, Font(30), String(U"Hit"), Palette::Black)
	, stand(RoundRect(Arg::center(Vec2(370 + 150 * 1, Window::Height() / 2)), 130, 70, 20), Palette::Orange,
		[&]() { dealer.hand.push_back(deck.CardDraw()); }, Font(30), String(U"Stand"), Palette::Black)
{
	scene = start;
}

void Blackjack::update()
{
	switch (scene)
	{
	case start:
		deck.Shuffle();

		player.hand = deck.CardDraw(2);
		dealer.hand = deck.CardDraw(2);
		dealer.hand[0].flip();

		scene = select;

		break;
	}
	hit.Update();
	stand.Update();
}

void Blackjack::draw() const
{
	static const auto color = [](Info i, bool isdealer) {return i.isBlackjack() ? Palette::Gold : i.power(isdealer) <= 21 ? Palette::White : Palette::Red; };

	for (int i = 0; i < player.hand.size(); ++i)
	{
		pack(player.hand[i]).drawAt(500 + (pack.width() + 15) * i, 600);
	}

	fScore(player.power()).drawAt(550, 500, color(player, false));

	for (int i = 0; i < dealer.hand.size(); ++i)
	{
		pack(dealer.hand[i]).drawAt(500 + (pack.width() + 15) * i, 100);
	}

	fScore(dealer.power(true)).drawAt(550, 200, color(dealer, true));

	hit.Draw();
	stand.Draw();
}