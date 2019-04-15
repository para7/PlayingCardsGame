#pragma once

#include "Common.hpp"

class Blackjack : public Myapp::Scene
{
private:

	const Font fScore;

	Button<RoundRect, true> hit, stand, doubledown, surrender;

	struct Info
	{
		Array<PlayingCard::Card> hand;

		int power(bool dealer = false) const;

		inline bool isBlackjack() const
		{
			return power() == 21 && hand.size() == 2;
		}

		inline bool isBurst() const
		{
			return power() > 21;
		}

	} player, dealer;


	struct DrawEffect
	{
		const Vec2 startpos, targetpos;
		Info& info;
		PlayingCard::Pack pack;
		double ease;

		DrawEffect(const Vec2& _targetpos, Info& _info, const Pack& _pack)
			: targetpos(_targetpos)
			, startpos(targetpos.movedBy(Window::Width(), 0))
			, info(_info)
			, pack(_pack)
		{
		}

		void update()
		{
			//イージングして0になったら実行
		}

		void draw()
		{
			//背面描画
		}
	};

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