
# include <Siv3D.hpp> // OpenSiv3D v0.3.2
#include <HamFramework.hpp>
#include "Blackjack.hpp"
#include "Common.hpp"

void Main()
{
	Graphics::SetBackground(Palette::Lightgreen);

	Myapp app;

	app.add<Blackjack>(U"Blackjack");

	Window::Resize(1280, 720);

	while (System::Update())
	{
		app.update();
	}
}
