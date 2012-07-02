#include "stdafx.h"

#ifdef CPP_0x11
OptionsMenu* ptr=nullptr;
#else
OptionsMenu* ptr=NULL;
#endif


OptionsMenu::OptionsMenu()
{
	
	
	Running = true;


	
#pragma region Labels
	m_YourNickLabel.setPosition(50,100);
	m_YourNickLabel.setFont(LoadContent::GetInstance()->m_font); 
	m_YourNickLabel.setColor(sf::Color(255,100,0,255)); 

	m_YourColorLabel.setPosition(50,150);
	m_YourColorLabel.setFont(LoadContent::GetInstance()->m_font);
	m_YourColorLabel.setColor(sf::Color(255,100,0,255));

	m_YourTankTypeLabel.setPosition(50,200);
	m_YourTankTypeLabel.setFont(LoadContent::GetInstance()->m_font);
	m_YourTankTypeLabel.setColor(sf::Color(255,100,0,255));
#pragma endregion

}

int OptionsMenu::Run(tgui::Window & App)
{
	Running = true;
	
	init_Gui(App);
	

	readDataFromXmlConfigFile(App);

	m_YourNickLabel.setString("Your nick: ");
	m_YourColorLabel.setString("Your color: ");
	m_YourTankTypeLabel.setString("Your tank type: ");
	
	while(Running)
	{
		App.clear();

		while(App.pollEvent(m_Event))
		{
			if(m_Event.type == sf::Event::Closed)
			{
				Running = false;
				return (-1);
			}

			if(m_Event.type == sf::Event::KeyPressed && m_Event.key.code == sf::Keyboard::Escape)
			{
				Running = false;
				return 1;
			}

			App.handleEvent(m_Event);

		} // end of while events
		
		
		tgui::Callback _callback;
		while(App.getCallback(_callback))
		{
			if(_callback.callbackID == 1) // Back button pressed
			{

			}

			if(_callback.callbackID == 2) // Save button pressed
			{
				saveDataToXmlConfigFile();
			}

			if(_callback.callbackID == 3) // NickBox
			{
				if(_callback.trigger == tgui::Callback::textChanged)
				{
					player_nick = _callback.text;
				}
			}

			if(_callback.callbackID == 4) // Color comboBox
			{
				if(_callback.trigger == tgui::Callback::itemSelected)
				{
					player_color = _callback.text;
				}
			}

			if(_callback.callbackID == 5) // TankType comboBox
			{
				if(_callback.trigger == tgui::Callback::itemSelected)
				{
					player_tankType = _callback.text;
				}
			}


		} // end of while callbacks 
		
		App.draw(m_YourNickLabel);
		App.draw(m_YourColorLabel);
		App.draw(m_YourTankTypeLabel);

		App.drawGUI();
		App.display();
		sf::sleep(sf::milliseconds(10));
	} // end of while loop
	return (-1);
}

bool OptionsMenu::readDataFromXmlConfigFile(tgui::Window & App)
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
			player_nick = (t->Value());

		}

		if(elemName == "nick_color")
		{
			TiXmlNode *e = _elem->FirstChild();
			TiXmlText *t = e->ToText();
			if(t == NULL)
				continue;
			player_color = (t->Value());

		}

		if(elemName == "tank_type")
		{
			TiXmlNode *e = _elem->FirstChild();
			TiXmlText *t = e->ToText();
			if(t == NULL)
				continue;
			player_tankType = (t->Value());

		}

		/*for(TiXmlNode* e = _elem->FirstChild(); e != NULL; e = e->NextSibling())
		{
			TiXmlText* text = e->ToText();
			if(text == NULL)
				continue;
			t = text->Value();
		}*/
	}

	App.getEditBox("NICKBOX")->setText(player_nick);
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
	if(player_nick.isEmpty()) player_nick = "empty";
	std::string _tmpNick = player_nick;
	TiXmlText* nickText = new TiXmlText(_tmpNick.c_str());
	nickElem->LinkEndChild(nickText);

	TiXmlElement* nick_colorElem = new TiXmlElement("nick_color");
	root->LinkEndChild(nick_colorElem);
	if(player_color.isEmpty()) player_color = "empty";
	std::string _tmpColorNick = player_color;
	TiXmlText* nickColorText = new TiXmlText(_tmpColorNick.c_str());
	nick_colorElem->LinkEndChild(nickColorText);

	TiXmlElement* tank_typeElem = new TiXmlElement("tank_type");
	root->LinkEndChild(tank_typeElem);
	if(player_tankType.isEmpty()) player_tankType = "empty";
	std::string _tmpTankType = player_tankType;
	TiXmlText* tankTypeText = new TiXmlText(_tmpTankType.c_str());
	tank_typeElem->LinkEndChild(tankTypeText);

	bool _success = doc.SaveFile("CONTENT\\ConfigFile.xml");
	doc.Clear();
	if(_success) return true; else return false;

}

sf::String OptionsMenu::GetPlayerColor()
{
	return player_color;
}

sf::String OptionsMenu::GetPlayerNick()
{
	return player_nick;
}

OptionsMenu* OptionsMenu::GetInstance()
{
	if(ptr==NULL) ptr = new OptionsMenu();
	return ptr;
}

void OptionsMenu::init_Gui(tgui::Window & App)
{
/*	tgui::Button* buttonBack = App.addButton("SAVE");
	buttonBack->load("CONTENT\\TGUI\\objects\\Button\\Black");
	buttonBack->setText("Back");
	buttonBack->setScale(0.6f,0.6f);
	buttonBack->setPosition(20, 400);
	buttonBack->callbackID = 1;

	tgui::Button* buttonSave = App.addButton("BACK");
	buttonSave->load("CONTENT\\TGUI\\objects\\Button\\Black");
	buttonSave->setText("Save");
	buttonSave->setScale(0.6f,0.6f);
	buttonSave->setPosition(200, 400);
	buttonSave->callbackID = 2;

	tgui::EditBox* nickBox = App.addEditBox("NICKBOX");
	nickBox->load("CONTENT\\TGUI\\objects\\EditBox\\Black");
	nickBox->setPosition(300, 100);
	nickBox->setSize(360,40);
	nickBox->callbackID = 3;
*/

	tgui::ComboBox* tankTypeBox = App.addComboBox("TANKTYPEBOX");
	tankTypeBox->load("CONTENT\\TGUI\\objects\\ComboBox\\Black", 150);
	tankTypeBox->setPosition(420, 200);
	tankTypeBox->addItem("Light");
	tankTypeBox->addItem("Medium");
	tankTypeBox->addItem("Heavy");
	tankTypeBox->setSelectedItem(2);
	tankTypeBox->callbackID = 5;

	tankTypeBox->changeColors(sf::Color(50, 50, 50), sf::Color(200, 200, 200), sf::Color(10, 110, 255), sf::Color(255,255,255));


	tgui::ComboBox* colorBox = App.addComboBox("COLORBOX");
	colorBox->load("CONTENT\\TGUI\\objects\\ComboBox\\Black", 150);
	colorBox->setPosition(340, 150);
	colorBox->addItem("Red");
	colorBox->addItem("Blue");
	colorBox->addItem("Yellow");
	colorBox->setSelectedItem(1);
	colorBox->callbackID = 4;

	colorBox->changeColors(sf::Color(50, 50, 50), sf::Color(200, 200, 200), sf::Color(10, 110, 255), sf::Color(255,255,255));

}