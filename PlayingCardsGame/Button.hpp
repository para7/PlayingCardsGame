#pragma once

template <class Collision, bool CenterIsFunc>
struct Button
{

	Collision c;
	std::function<void()> f;
	Color color;
	Font font;
	String text;
	Color tcolor;

private:
	int clicked;
	bool oncursor;
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="collision">
	/// �}�`
	/// </param>
	/// <param name="_color">
	/// �}�`�̐F
	/// </param>
	/// <param name="func">
	/// ���s����֐�
	/// </param>
	/// <param name="_font">
	/// �t�H���g
	/// </param>
	/// <param name="_text">
	/// �\�����镶����
	/// </param>
	/// <param name="textcolor">
	/// �����F
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

	Button() {}

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