#include "stdafx.h"

TextBox::TextBox(sf::Vector2f XY1, sf::String Text, sf::Color TextColor, float TextSize, float Width, sf::Color nonActive, sf::Color Active )
{
	m_XY1 = XY1;

	m_text = Text;
	m_text.SetSize(TextSize);
	
	float _textW = m_text.GetRect().GetWidth();
	float _textH = m_text.GetRect().GetHeight();

	m_shape = sf::Shape::Rectangle(XY1.x, XY1.y, XY1.x + Width, XY1.y + _textH + 2, sf::Color(0,0,0,0), 2.0f, nonActive);
	m_fRect = sf::FloatRect(XY1.x, XY1.y, XY1.x + Width, XY1.y + _textH + 2);

	ActiveColor = Active;
	nonActiveColor = nonActive;

	

	m_text.SetFont(LoadContent::GetInstance()->m_font2);
	m_text.SetColor(TextColor);
	m_text.SetPosition( XY1.x + 5 /*(m_fRect.GetWidth() - _textW)/2 */, XY1.y + (m_fRect.GetHeight() - _textH)/2 );

	m_state = false;
}

void TextBox::SetLabel(sf::String Label, float LabelSize, sf::Color LabelColor, float Interspace )
{
	m_label = Label;
	m_label.SetSize(LabelSize);

	float _labelW = m_label.GetRect().GetWidth();
	float _labelH = m_label.GetRect().GetHeight();

	m_label.SetFont(LoadContent::GetInstance()->m_font2);
	m_label.SetColor(LabelColor);
	m_label.SetPosition(m_XY1.x + (m_fRect.GetWidth() - _labelW)/2 , m_XY1.y - (m_fRect.GetHeight() + _labelH)/2 - Interspace );
	m_label.SetStyle(sf::String::Italic|sf::String::Bold);
}

void TextBox::Show(sf::RenderWindow & App)
{

	App.Draw(m_label);
	App.Draw(m_text);
	App.Draw(m_shape);

}

void TextBox::HandleEvent(sf::Event & Event)
{
	if(Event.Type == sf::Event::MouseButtonPressed && m_fRect.Contains((float)(Event.MouseButton.X), (float)(Event.MouseButton.Y)) )
	{
		m_state = true;
		SetActive(true);
	}
	else if(Event.Type == sf::Event::MouseButtonPressed)
	{
		m_state = false;
		SetActive(false);
	}
	
	if(Event.Type == sf::Event::TextEntered && isActive() )
	{
		std::string _tmp = GetText();
		if(Event.Text.Unicode == '\b')
		{
			if(_tmp.size() > 0) _tmp.erase( _tmp.size() -1, 1);
		}
		else if(Event.Text.Unicode < 127)
		{
			if(_tmp.size() < 20) _tmp += static_cast<char>(Event.Text.Unicode);
		}

		SetText(_tmp);
	}
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
	m_state = state;
	if(m_state)
	{
		m_shape.SetPointOutlineColor(1, ActiveColor);
		m_shape.SetPointOutlineColor(3, ActiveColor);
	}
	if(!m_state)
	{
		m_shape.SetPointOutlineColor(1, nonActiveColor);
		m_shape.SetPointOutlineColor(3, nonActiveColor);
	}
}

std::string TextBox::GetText()
{
	return m_text.GetText();
}

bool TextBox::isActive()
{
	return m_state;
}