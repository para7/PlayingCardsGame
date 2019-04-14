#pragma once

template <class Collision, bool CenterIsFunc>
class Button
{
private:

	const Collision c;
	const std::function<void()> f;
	const Color color;
	const Font font;
	const String text;
	const Color tcolor;
	
	int clicked;
	bool oncursor;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="collision">
	/// 図形
	/// </param>
	/// <param name="_color">
	/// 図形の色
	/// </param>
	/// <param name="func">
	/// 実行する関数
	/// </param>
	/// <param name="_font">
	/// フォント
	/// </param>
	/// <param name="_text">
	/// 表示する文字列
	/// </param>
	/// <param name="textcolor">
	/// 文字色
	/// </param>
	Button(const Collision& collision,
		const Color& _color,
		const std::function<void()>& func,
		const Font& _font,
		const String& _text,
		const Color& textcolor)
		: c(collision)
		, color(_color)
		, f(func)
		, font(_font)
		, text(_text)
		, tcolor(textcolor)
		, clicked(false)
	{

	}

	void Update()
	{
		oncursor = c.intersects(Cursor::Pos());

		if (c.leftClicked())
		{
			f();
			clicked = 4 + 1;
			return;
		}
		--clicked;
	}

	void Draw() const
	{
		Vec2 center;

		if constexpr (CenterIsFunc)
		{
			center = c.center();
		}
		else
		{
			center = c.center;
		}
		c.draw(oncursor ? color.lerp(Palette::Black, 0.1) : color);

		if (0 < clicked)
		{
			c.drawFrame(5, 0, color.lerp(Palette::Black, 0.2));
		}

		font(text).drawAt(center, tcolor);
	}
};