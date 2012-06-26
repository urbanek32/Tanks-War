#include "stdafx.h"


ImageButton::ImageButton(std::string imageButton_name, sf::String text, std::string buttonLabel, sf::Vector2f poz, sf::Color color)
{
	float t_w, bL_w, t_h, bL_h;

	m_button.SetImage(LoadContent::GetInstance()->ImgMnr->Get_Image(imageButton_name));
	m_button.SetPosition(poz);

	m_text = text;
	m_buttonLabel.SetText(buttonLabel);

	t_w = m_text.GetRect().GetWidth();
	t_h = m_text.GetRect().GetHeight();
	bL_w = m_buttonLabel.GetRect().GetWidth();
	bL_h = m_buttonLabel.GetRect().GetHeight();
	
	m_text.SetPosition( m_button.GetPosition().x + ((m_button.GetSize().x - t_w)/2), m_button.GetPosition().y + ((m_button.GetSize().y-t_h)/2) );
	m_text.SetFont(LoadContent::GetInstance()->m_font);
	m_text.SetColor(color);
	m_text.SetStyle(sf::String::Bold);

	m_buttonLabel.SetPosition( m_button.GetPosition().x + ((m_button.GetSize().x - bL_w)/2), m_button.GetPosition().y - ((m_button.GetSize().y-bL_h)/2) );
	m_buttonLabel.SetFont(LoadContent::GetInstance()->m_font);
	m_buttonLabel.SetColor(sf::Color(255,255,0,255));
	m_buttonLabel.SetStyle(sf::String::Bold);
}
/*
sf::FloatRect ImageButton::GetRectangle()
{
	
}
*/
void ImageButton::Show(sf::RenderWindow &App)
{

	App.Draw(m_button);
	App.Draw(m_buttonLabel);
	App.Draw(m_text);

}

void ImageButton::SetImage(sf::Image image)
{
	m_button.SetImage(image);
}