#include "stdafx.h"

#ifdef CPP_0x11
OptionsMenu* om_ptr=nullptr;
#else
OptionsMenu* om_ptr=NULL;
#endif


OptionsMenu::OptionsMenu()
{
	
	Running = true;
	m_Inited = false;

}

int OptionsMenu::Run(sf::RenderWindow & App)
{
	Running = true;
	
	if(!m_Inited)
		Init();

	
	while(Running)
	{
		App.Clear();
		App.Draw(m_background);
		while(App.GetEvent(m_Event))
		{
			if(m_Event.Type == sf::Event::Closed)
			{
				Running = false;
				return (-1);
			}

			if(m_Event.Type == sf::Event::KeyPressed && m_Event.Key.Code == sf::Key::Escape)
			{
				saveDataToXmlConfigFile();
				Running = false;
				return 1;
			}

			m_playerNickBox->HandleEvent(m_Event);

		} // end of while events

#pragma region DEBUG INFO	
std::ostringstream bufor;
sf::String tdebug;
tdebug.SetFont(sf::Font::GetDefaultFont());
tdebug.SetSize(20);
tdebug.SetColor(sf::Color(255,0,0,255));
bufor << "MapSize= " << gResMng.Get_MapSize();
tdebug.SetText(bufor.str());
App.Draw(tdebug);		
#pragma endregion		

		m_playerNickBox->Show(App);
		

		App.Display();
		sf::Sleep(0.01f);
	} // end of while loop
	return (-1);
}

void OptionsMenu::Init()
{
	readDataFromXmlConfigFile();


	m_playerNickBox = new TextBox(sf::Vector2f(150,100), player_nick, sf::Color(255,0,0,255), "PlayerNick", 30.f);
	m_playerNickBox->SetLabel(sf::String("Your nick: "), 30.f, sf::Color(255,110,0,255), 4.f);

	m_Inited = true;

	m_background.SetImage(gResMng.Get_Image("CONTENT//tlo-test.png"));
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
			globals["PlayerNick"] = player_nick.GetText();
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
			globals["TankType"] = player_tankType.GetText();
		}

		if(elemName == "cannon_type")
		{
			TiXmlNode *e = _elem->FirstChild();
			TiXmlText *t = e->ToText();
			if(t == NULL)
				continue;
			player_cannonType.SetText(t->Value());
			globals["CannonType"] = player_cannonType.GetText();
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
	player_nick.SetText(m_playerNickBox->GetText());

	std::string _temp;

	TiXmlDocument doc; 
	TiXmlDeclaration *decl = new TiXmlDeclaration("1.0","utf-8","");
	doc.LinkEndChild(decl);
	TiXmlElement* root = new TiXmlElement("root");
	doc.LinkEndChild(root);

	TiXmlElement* nickElem = new TiXmlElement("nick");
	root->LinkEndChild(nickElem);
	_temp = player_nick.GetText();
	if(_temp.length() <= 0) _temp = "NewPlayer";
	TiXmlText* nickText = new TiXmlText(_temp.c_str());
	nickElem->LinkEndChild(nickText);
	globals["PlayerNick"] = _temp;

	TiXmlElement* nick_colorElem = new TiXmlElement("nick_color");
	root->LinkEndChild(nick_colorElem);
	_temp = player_color.GetText();
	if(_temp.length() <= 0) _temp = "Red";
	TiXmlText* nickColorText = new TiXmlText(_temp.c_str());
	nick_colorElem->LinkEndChild(nickColorText);

	TiXmlElement* tank_typeElem = new TiXmlElement("tank_type");
	root->LinkEndChild(tank_typeElem);
	_temp = player_tankType.GetText();
	if(_temp.length() <= 0) _temp = "TankMedium";
	TiXmlText* tankTypeText = new TiXmlText(_temp.c_str());
	tank_typeElem->LinkEndChild(tankTypeText);
	globals["TankType"] = _temp;

	TiXmlElement* cannon_typeElem = new TiXmlElement("cannon_type");
	root->LinkEndChild(cannon_typeElem);
	_temp = player_cannonType.GetText();
	if(_temp.length() <= 0) _temp = "CannonMedium";
	TiXmlText* cannonTypeText = new TiXmlText(_temp.c_str());
	cannon_typeElem->LinkEndChild(cannonTypeText);
	globals["CannonType"] = _temp;

	bool _success = doc.SaveFile("CONTENT\\ConfigFile.xml");
	doc.Clear();
	if(_success) return true; else return false;

}

OptionsMenu* OptionsMenu::GetInstance()
{
	if(om_ptr==NULL) om_ptr = new OptionsMenu();
	return om_ptr;
}
