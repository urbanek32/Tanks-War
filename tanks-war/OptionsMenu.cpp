#include "stdafx.h"

OptionsMenu::OptionsMenu()
{
	readDataFromXmlConfigFile();
	

	//m_button_nick = new ImageButton("CONTENT\\button.png", player_nick, "Your Nick: ", sf::Vector2f(200,200), sf::Color(64,64,64,228));

	Running = true;

#pragma region Bools for events
	nickClicked = false;
	colorClicked = false;
	tankTypeClicked = false;
#pragma endregion
#pragma region Colors for events
	colorNick = sf::Color(255,255,0,255);
	colorColor = sf::Color(255,255,0,255);
	colorTankType = sf::Color(255,255,0,255);
#pragma endregion
#pragma region Labels
	YourNick.SetPosition(50,100);
	YourNick.SetFont(LoadContent::GetInstance()->m_font); 
	YourNick.SetColor(sf::Color(30,0,255,255)); 
	YourNick.SetStyle(sf::String::Bold); 
	YourNick.SetText("Your Nick: ");

	YourColor.SetPosition(50,150);
	YourColor.SetFont(LoadContent::GetInstance()->m_font);
	YourColor.SetColor(sf::Color(30,0,255,255));
	YourColor.SetStyle(sf::String::Bold);
	YourColor.SetText("Your Color: ");

	YourTankType.SetPosition(50,200);
	YourTankType.SetFont(LoadContent::GetInstance()->m_font);
	YourTankType.SetColor(sf::Color(30,0,255,255));
	YourTankType.SetStyle(sf::String::Bold);
	YourTankType.SetText("Your Tank Type: ");
#pragma endregion
#pragma region FloatRectangle for events
	nickRect = sf::FloatRect(300, 100, 600, 140);
	colorRect = sf::FloatRect(300, 150, 600, 190);
	tankTypeRect = sf::FloatRect(300, 200, 600, 240);
#pragma endregion
#pragma region Texts typed by user

	player_nick.SetPosition(305, 100);
	player_nick.SetFont(LoadContent::GetInstance()->m_font);
	player_nick.SetColor(sf::Color(255,50,0,255));
	player_nick.SetStyle(sf::String::Bold);

	player_color.SetPosition(305, 150);
	player_color.SetFont(LoadContent::GetInstance()->m_font);
	player_color.SetColor(sf::Color(255,50,0,255));
	player_color.SetStyle(sf::String::Bold);

	player_tankType.SetPosition(305, 200);
	player_tankType.SetFont(LoadContent::GetInstance()->m_font);
	player_tankType.SetColor(sf::Color(255,50,0,255));
	player_tankType.SetStyle(sf::String::Bold);

#pragma endregion
}

int OptionsMenu::Run(sf::RenderWindow& App)
{
	Running = true;

	while(Running)
	{
		App.Clear();

		while(App.GetEvent(m_Event))
		{
			if(m_Event.Type == sf::Event::Closed)
			{
				Running = false;
				return (-1);
			}

			if(m_Event.Type == sf::Event::KeyPressed && m_Event.Key.Code == sf::Key::Escape)
			{
				Running = false;
				return 1;
			}

#pragma region Events for TextEntered
			if(m_Event.Type == sf::Event::TextEntered)
			{
				if(nickClicked)
				{
					std::string tmpNick = player_nick.GetText();
					if(m_Event.Text.Unicode == '\b')
					{
						if(tmpNick.size() > 0) tmpNick.erase(tmpNick.size() -1, 1);
					} 
					else if(m_Event.Text.Unicode < 128)
					{
						if(tmpNick.size() < 20) tmpNick += static_cast<char>(m_Event.Text.Unicode);
					}
					player_nick.SetText(tmpNick);
				}

				if(colorClicked)
				{
					std::string tmpColorNick = player_color.GetText();
					if(m_Event.Text.Unicode == '\b')
					{
						if(tmpColorNick.size() > 0) tmpColorNick.erase(tmpColorNick.size() -1, 1);
					} 
					else if(m_Event.Text.Unicode < 128)
					{
						if(tmpColorNick.size() < 20) tmpColorNick += static_cast<char>(m_Event.Text.Unicode);
					}
					player_color.SetText(tmpColorNick);
				}

				if(tankTypeClicked)
				{
					std::string tmptankType = player_tankType.GetText();
					if(m_Event.Text.Unicode == '\b')
					{
						if(tmptankType.size() > 0) tmptankType.erase(tmptankType.size() -1, 1);
					} 
					else if(m_Event.Text.Unicode < 128)
					{
						if(tmptankType.size() < 20) tmptankType += static_cast<char>(m_Event.Text.Unicode);
					}
					player_tankType.SetText(tmptankType);
				}

				saveDataToXmlConfigFile();
			}
#pragma endregion
#pragma region Events for shapes
			if(m_Event.Type == sf::Event::MouseButtonReleased && m_Event.MouseButton.Button == sf::Mouse::Left )
			{
				if(nickRect.Contains(m_Event.MouseButton.X,m_Event.MouseButton.Y))
				{
					nickClicked = true;
					colorNick = sf::Color(0,255,0,255);
				}
				else
				{
					nickClicked = false;
					colorNick = sf::Color(255,255,0,255);
				}

				if(colorRect.Contains(m_Event.MouseButton.X,m_Event.MouseButton.Y))
				{
					colorClicked = true;
					colorColor = sf::Color(0,255,0,255);
				}
				else
				{
					colorClicked = false;
					colorColor = sf::Color(255,255,0,255);
				}

				if(tankTypeRect.Contains(m_Event.MouseButton.X,m_Event.MouseButton.Y))
				{
					tankTypeClicked = true;
					colorTankType = sf::Color(0,255,0,255);
				}
				else
				{
					tankTypeClicked = false;
					colorTankType = sf::Color(255,255,0,255);
				}
			}
#pragma endregion
			
		} // end of while events loop

#pragma region DEBUG INFO
std::ostringstream bufor;
sf::String tdebug;
tdebug.SetFont(LoadContent::GetInstance()->m_font);
tdebug.SetSize(20); tdebug.SetColor(sf::Color::Red); tdebug.SetPosition(0,0);
bufor <<nickClicked;
tdebug.SetText(bufor.str());
App.Draw(tdebug);
#pragma endregion		

#pragma region Draw Shapes, Labels, Titles
		NickShape = sf::Shape::Rectangle(300, 100, 600, 140,  sf::Color(0,0,0,0), 2.0f, colorNick);
		App.Draw(YourNick);
		App.Draw(player_nick);
		App.Draw(NickShape);

		App.Draw(YourColor);
		ColorShape = sf::Shape::Rectangle(300, 150, 600, 190,  sf::Color(0,0,0,0), 2.0f, colorColor); 
		App.Draw(player_color);
		App.Draw(ColorShape);

		App.Draw(YourTankType);
		TankTypeShape = sf::Shape::Rectangle(300, 200, 600, 240,  sf::Color(0,0,0,0), 2.0f, colorTankType);
		App.Draw(player_tankType);
		App.Draw(TankTypeShape);
#pragma endregion

		
		App.Display();
		sf::Sleep(0.01f);
	} // end of while loop
	return (-1);
}

bool OptionsMenu::readDataFromXmlConfigFile()
{
	

	TiXmlDocument *doc = new TiXmlDocument();

	if(!doc->LoadFile("CONTENT\\ConfigFile.xml"))
	{
		t = doc->ErrorDesc();
		return false;
	}
	
	TiXmlElement* _root = doc->FirstChildElement();

	if(_root == NULL)
	{
		t =  "No root element.";
		doc->Clear();
		return false;
	}
	
	for(TiXmlElement *_elem = _root->FirstChildElement(); _elem != NULL; _elem = _elem->NextSiblingElement())
	{
		elemName = _elem->Value();
		
		/*if(elemName == "Element1")
		{
			attr = _elem->Attribute("atrybut1");
			if(attr.size() > 0)
				std::cout<<attr<<std::endl;
			
		}*/

		if(elemName == "nick")
		{
			TiXmlNode *e = _elem->FirstChild();
			TiXmlText *t = e->ToText();
			if(t == NULL)
				continue;
			player_nick.SetText(t->Value());

		}

		if(elemName == "nick_color")
		{
			TiXmlNode *e = _elem->FirstChild();
			TiXmlText *t = e->ToText();
			if(t == NULL)
				continue;
			player_color.SetText(t->Value());

		}

		if(elemName == "tank_type")
		{
			TiXmlNode *e = _elem->FirstChild();
			TiXmlText *t = e->ToText();
			if(t == NULL)
				continue;
			player_tankType.SetText(t->Value());

		}

		/*for(TiXmlNode* e = _elem->FirstChild(); e != NULL; e = e->NextSibling())
		{
			TiXmlText* text = e->ToText();
			if(text == NULL)
				continue;
			t = text->Value();
		}*/
	}


	return true;
}

bool OptionsMenu::saveDataToXmlConfigFile()
{
	TiXmlDocument doc; 
	TiXmlDeclaration *decl = new TiXmlDeclaration("1.0","utf-8","");
	doc.LinkEndChild(decl);
	TiXmlElement* root = new TiXmlElement("root");
	doc.LinkEndChild(root);

	TiXmlElement* nickElem = new TiXmlElement("nick");
	root->LinkEndChild(nickElem);
	std::string _tmpNick = player_nick.GetText();
	TiXmlText* nickText = new TiXmlText(_tmpNick.c_str());
	nickElem->LinkEndChild(nickText);

	TiXmlElement* nick_colorElem = new TiXmlElement("nick_color");
	root->LinkEndChild(nick_colorElem);
	std::string _tmpColorNick = player_color.GetText();
	TiXmlText* nickColorText = new TiXmlText(_tmpColorNick.c_str());
	nick_colorElem->LinkEndChild(nickColorText);

	TiXmlElement* tank_typeElem = new TiXmlElement("tank_type");
	root->LinkEndChild(tank_typeElem);
	std::string _tmpTankType = player_tankType.GetText();
	TiXmlText* tankTypeText = new TiXmlText(_tmpTankType.c_str());
	tank_typeElem->LinkEndChild(tankTypeText);

	bool _success = doc.SaveFile("CONTENT\\ConfigFile.xml");
	doc.Clear();
	if(_success) return true; else return false;

}