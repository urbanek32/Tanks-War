#include "stdafx.h"

TextBox::TextBox(sf::Vector2f XY1, sf::Vector2f XY2, sf::String Label, sf::Color LabelColor, float LabelSize, sf::Color nonActive, sf::Color Active, sf::String Text, sf::Color TextColor, float TextSize, float Interspace)
{
	m_shape = sf::Shape::Rectangle(XY1, XY2, sf::Color(0,0,0,0), 2.0f, nonActive);
	m_fRect = sf::FloatRect(XY1.x, XY1.y, XY2.x, XY2.y);

	ActiveColor = Active;
	nonActiveColor = nonActive;

	m_text = Text;
	m_label = Label;

	m_text.SetSize(TextSize);
	m_label.SetSize(LabelSize);

	float _labelW = m_label.GetRect().GetWidth();
	float _labelH = m_label.GetRect().GetHeight();

	float _textW = m_text.GetRect().GetWidth();
	float _textH = m_text.GetRect().GetHeight();

	m_label.SetFont(LoadContent::GetInstance()->m_font);
	m_label.SetColor(LabelColor);
	m_label.SetPosition(XY1.x + (m_fRect.GetWidth() - _labelW)/2 , XY1.y - (m_fRect.GetHeight() + _labelH)/2 - Interspace );
	m_label.SetStyle(sf::String::Italic|sf::String::Bold);
	

	m_text.SetFont(LoadContent::GetInstance()->m_font);
	m_text.SetColor(TextColor);
	m_text.SetPosition( XY1.x + 5 /*(m_fRect.GetWidth() - _textW)/2 */, XY1.y + (m_fRect.GetHeight() - _textH)/2 );
}

void TextBox::Show(sf::RenderWindow & App)
{

	App.Draw(m_label);
	App.Draw(m_text);
	App.Draw(m_shape);

}

void TextBox::SetText(std::string& NewText)
{
	m_text.SetText(NewText);

	float _textW = m_text.GetRect().GetWidth();
	float _textH = m_text.GetRect().GetHeight();

	m_text.SetPosition( m_fRect.Left + 5 /*(m_fRect.GetWidth() - _textW)/2 */, m_fRect.Top + (m_fRect.GetHeight() - _textH)/2 );
}

void TextBox::SetActive(bool state)
{
	if(state)
	{
		m_shape.SetPointOutlineColor(1, ActiveColor);
		m_shape.SetPointOutlineColor(3, ActiveColor);
	}
	if(!state)
	{
		m_shape.SetPointOutlineColor(1, nonActiveColor);
		m_shape.SetPointOutlineColor(3, nonActiveColor);
	}
}

std::string TextBox::GetText()
{
	return m_text.GetText();
}
