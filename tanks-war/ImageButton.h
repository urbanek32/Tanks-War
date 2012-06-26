#include "stdafx.h"

class ImageButton
{
public:
	ImageButton(std::string imageButton_name, sf::String text, std::string buttonLabel, sf::Vector2f poz, sf::Color color);
	//sf::FloatRect GetRectangle();
	void Show(sf::RenderWindow&);
	void SetImage(sf::Image);

private:
	sf::Sprite m_button;
	sf::String m_text,m_buttonLabel;
	sf::FloatRect m_fTextRect;

};