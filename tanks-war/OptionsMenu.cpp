#include "stdafx.h"

OptionsMenu::OptionsMenu()
{
	_background.SetImage(LoadContent::GetInstance()->ImgMnr->Get_Image("tlo-opcje-test.png"));
	Running = true;
}

int OptionsMenu::Run(sf::RenderWindow& App)
{
	while(Running)
	{
		App.Clear();
		App.Draw(_background);

		while(App.GetEvent(m_Event))
		{
			if(m_Event.Type == sf::Event::Closed)
			{
				Running = false;
				return (-1);
			}
			if(m_Event.Type == sf::Event::KeyPressed && m_Event.Key.Code == sf::Key::Escape)
			{
				//GameManager::GetInstance()->_gameState = ShowingMenu;
				Running = false;
				return 1;
			}
		}

		//readXmlConfigFile();



		App.Display();
		sf::Sleep(0.01f);
	}
	
}

bool OptionsMenu::readXmlConfigFile()
{
	TiXmlDocument *doc = new TiXmlDocument();

	if(!doc->LoadFile("ConfigFile.xml"))
	{
		std::cerr<< doc->ErrorDesc() << std::endl;
		return false;
	}

	TiXmlElement* _root = doc->FirstChildElement();

	if(_root == NULL)
	{
		std::cerr<<" No root element." << std::endl;
		doc->Clear();
		return false;
	}
	
	for(TiXmlElement* _elem = _root->FirstChildElement(); _elem != NULL; _elem = _elem->NextSiblingElement())
	{
		std::string elemName = _elem->Value();
		std::string attr;
		if(elemName == "Element1")
		{
			attr = _elem->Attribute("atrybut1");
			if(attr.size() > 0)
				std::cerr<<attr<<std::endl;
		}

		for(TiXmlNode* e = _elem->FirstChild(); e != NULL; e = e->NextSibling())
		{
			TiXmlText* text = e->ToText();
			if(text == NULL)
				continue;
			std::string t = text->Value();
			std::cerr<<t<<std::endl;
		}
	}

	

	return true;
}