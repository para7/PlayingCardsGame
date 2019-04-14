#pragma once

#include "Common.hpp"

class Blackjack : public Myapp::Scene
{
private:

	const Font fScore;

	Button<RoundRect, true> hit, stand;

	struct Info
	{
		Array<PlayingCard::Card> hand;
		
		int power(bool dealer = false) const
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

		bool isBlackjack() const
		{
			if (power() == 21 && hand.size() == 2)
			{
				return true;
			}
			return false;
		}

		bool isBurst() const
		{
			if (power() > 21)
			{
				return true;
			}
			return false;
		}

	} player, dealer;


	Deck deck;

	enum _scene
	{
		bet, start, select, enemy, result
	} scene;

	int deckseek;

	int chip;

	PlayingCard::Pack pack;

public:

	Blackjack(const InitData& init);

	void update() override;

	void draw() const override;

};