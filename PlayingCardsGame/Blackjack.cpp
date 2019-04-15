#include "Blackjack.hpp"

using namespace s3d::PlayingCard;

constexpr int button_start = 480;
constexpr int button_width = 190;
constexpr int button_margin = 10;


Blackjack::Blackjack(const InitData& init)
	: IScene(init)
	, pack(90)
	, fScore(45)
	, hit(RoundRect(Arg::center(Vec2(button_start + (button_width + button_margin) * 0, Window::Height() / 2)), button_width, 70, 20), Palette::Orange,
		[&]() { player.hand.push_back(deck.CardDraw()); }, Font(30), String(U"Hit"), Palette::Black)
	, stand(RoundRect(Arg::center(Vec2(button_start + (button_width + button_margin) * 1, Window::Height() / 2)), button_width, 70, 20), Palette::Orange,
		[&]() { dealer.hand.push_back(deck.CardDraw()); }, Font(30), String(U"Stand"), Palette::Black)
	, doubledown(RoundRect(Arg::center(Vec2(button_start + (button_width + button_margin) * 2, Window::Height() / 2)), button_width, 70, 20), Palette::Orange,
		[&]() {  }, Font(30), String(U"Double down"), Palette::Black)
	, surrender(RoundRect(Arg::center(Vec2(button_start + (button_width + button_margin) * 3, Window::Height() / 2)), button_width, 70, 20), Palette::Orange,
		[&]() {  }, Font(30), String(U"Surrender"), Palette::Black)
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
	doubledown.Update();
	surrender.Update();
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
	doubledown.Draw();
	surrender.Draw();
}



int Blackjack::Info::power(bool dealer) const

{
	int sum = 0;
	int ace = 0;

	for (const auto& x : hand)
	{
		if (dealer && !x.isFaceSide)
		{
			continue;
		}

		if (x.isAce())
		{
			sum += 11;
			ace++;
		}
		else if (x.isJack() || x.isQueen() || x.isKing())
		{
			sum += 10;
		}
		else
		{
			sum += x.rank;
		}
	}

	for (int i = 0; i < ace; ++i)
	{
		if (21 < sum)
		{
			sum -= 10;
		}
	}


	return sum;
}