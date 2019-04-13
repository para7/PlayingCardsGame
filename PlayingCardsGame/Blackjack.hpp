#pragma once

#include "Common.hpp"

class Blackjack :public Myapp::Scene
{
private:

	Deck deck;

	enum _scene
	{
		bet, start, select, player, enemy, check
	} scene;

	int deckseek;

	int chip;

	Array<PlayingCard::Card> playerhand;
	Array<PlayingCard::Card> dealerhand;


	PlayingCard::Pack pack;

public:

	Blackjack(const InitData& init);

	void update() override;

	void draw() const override;

};