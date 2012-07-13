#include "stdafx.h"

#ifndef TEXTBOX_H
#define TEXTBOX_H
class TextBox
{
public:
	TextBox(sf::Vector2f XY1, sf::String Text, sf::Color TextColor, float TextSize = 30.f, float Width = 300.f, sf::Color nonActive = sf::Color(0,255,0,255), sf::Color Active= sf::Color(255,255,255,255) );

	// Display TextBox on the screen
	void Show(sf::RenderWindow & App);

	// Handling events for TextBox
	void HandleEvent(sf::Event & Event);

	// You can change text in TextBox
	void SetText(std::string & NewText);

	// Returns text in TextBox
	std::string GetText();

	// You can set if current box is now Active
	void SetActive(bool state);

	// Returns current state of TextBox
	bool isActive();

	// You can add label on top of TextBox
	void SetLabel(sf::String Label, float LabelSize, sf::Color LabelColor, float Interspace=0.f );

private:
	sf::String m_text;
	sf::Vector2f m_XY1;
	sf::String m_label;
	sf::Shape m_shape;
	sf::FloatRect m_fRect;
	bool m_state;
	sf::Color ActiveColor, nonActiveColor;
};
#endif