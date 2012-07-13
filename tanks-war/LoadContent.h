#include "stdafx.h"

#ifndef LOADCONTENT_H
#define LOADCONTENT_H
class LoadContent : public cScreen
{
public:
	LoadContent();

	// return instnace to this object
	static LoadContent* GetInstance();

	// main font instance
	sf::Font m_font, m_font2;

	// main function to draw this content
	virtual int Run(sf::RenderWindow &App);

private:

	// load content
	void Init();
	
	// just for once init
	bool m_Inited;

	// displaying progress of loading
	sf::String *m_text;

	// event container
	sf::Event m_Event;

	// special class to load all content in diffrent thead
	class LoadAll* m_loadAll;
};

// special class to load all content in diffrent thead
class LoadAll : public sf::Thread
{
public:
	LoadAll();
	bool done;
private:
	virtual void Run();


};
#endif