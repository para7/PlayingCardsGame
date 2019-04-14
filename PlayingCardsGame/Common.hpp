#pragma once

#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Button.hpp"

using namespace s3d::PlayingCard;

struct Common
{

};

using Myapp = SceneManager<String, Common>;

class DelayEvent
{
private:

	Stopwatch watch;
	double time;
	std::function<void()> func;
	bool used;

public:

	DelayEvent(double _time, std::function<void()> _func)
		: time(_time)
		, func(_func)
		, used(false)
	{

	}

	void update()
	{
		if (time < watch.sF())
		{
			func();
			watch.reset();
			used = true;
		}
	}
};

class Deck
{
	using Decktype = Array<PlayingCard::Card>;
	Array<PlayingCard::Card> deck;
	int seek;

public:
	Deck(Decktype& dtype)
		:deck(dtype)
		, seek(0)
	{
		deck = dtype;
	}

	Deck()
		:deck(PlayingCard::CreateDeck())
		, seek(0)
	{

	}

	inline PlayingCard::Card CardDraw()
	{
		return deck[seek++];
	}

	Decktype CardDraw(unsigned num)
	{
		Decktype d;

		for (unsigned i = 0; i < num; ++i)
		{
			d.push_back(CardDraw());
		}

		return d;
	}

	void Reset()
	{
		deck.shuffle();
		seek = 0;
	}

	void Shuffle()
	{
		deck.shuffle();
	}
};
