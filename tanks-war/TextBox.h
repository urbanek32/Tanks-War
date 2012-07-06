#include "stdafx.h"

class TextBox
{
public:
	TextBox(sf::Vector2f XY1, sf::Vector2f XY2, sf::String Label, sf::Color LabelColor, float LabelSize, sf::Color nonActive, sf::Color Active, sf::String Text, sf::Color TextColor, float TextSize, float Interspace=0.f);
	void Show(sf::RenderWindow & App);
	void SetText(std::string& NewText);
	std::string GetText();
	void SetActive(bool state);

private:
	sf::String m_text;
	sf::String m_label;
	sf::Shape m_shape;
	sf::FloatRect m_fRect;
	sf::Color ActiveColor, nonActiveColor;
};