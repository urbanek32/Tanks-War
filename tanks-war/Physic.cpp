#include "stdafx.h"

#define FACTOR 30.f
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#ifdef CPP_0x11
Physic* ptr=nullptr;
#else
Physic* ptr=NULL;
#endif

Physic* Physic::GetInstance()
{
	if(ptr==NULL) ptr = new Physic();
	return ptr;
}


Physic::Physic()
{

	// create world
	gravity = new b2Vec2(0.f, 0.f); 
	world = new b2World(*gravity);

/*
	// create ground
	groundSprite.SetImage(gResMng.Get_Image("CONTENT//mur3.jpg"));
	groundSprite.SetPosition(0.f, 200.0f);
	groundSprite.SetCenter(groundSprite.GetSize().x / 2, groundSprite.GetSize().y / 2);

	groundBodyDef = new b2BodyDef;
	groundBodyDef->type = b2_staticBody;
	groundBodyDef->position.Set(groundSprite.GetPosition().x, groundSprite.GetPosition().y);
	
	groundBody = world->CreateBody(groundBodyDef);

	groundBox = new b2PolygonShape;
	groundBox->SetAsBox(groundSprite.GetSize().x / 2.0f, groundSprite.GetSize().y / 2.0f);

	groundBody->CreateFixture(groundBox, 0.0f);
*/


	// create an Dynamic Object
	_PO.sprite.SetImage(gResMng.Get_Image("CONTENT//tank.png"));
	_PO.sprite.SetPosition(64.0f, 64.0f);
	_PO.sprite.SetCenter(_PO.sprite.GetSize().x / 2, _PO.sprite.GetSize().y / 2);

	_PO.bodyDef.type = b2_dynamicBody;
	_PO.bodyDef.position.Set(_PO.sprite.GetPosition().x, _PO.sprite.GetPosition().y);
	_PO.bodyDef.linearDamping = 0.0f;
	_PO.body = world->CreateBody(&_PO.bodyDef);

	_PO.box.SetAsBox(_PO.sprite.GetSize().x / 2.0f, _PO.sprite.GetSize().y / 2.0f);

	_PO.fixture.shape = &_PO.box;
	_PO.fixture.density = 5.0f;
	_PO.fixture.friction = 1.0f;

	_PO.body->CreateFixture(&_PO.fixture);
	
	rot = 0;
	v = 0;
	force = 0;

	
}

void Physic::Tick(sf::RenderWindow & App, float frequency)
{
	b2Vec2 vel = _PO.body->GetLinearVelocity();
	rot = _PO.body->GetAngle();
	force = 0;
	

	if(App.GetInput().IsKeyDown(sf::Key::Numpad8)) { v += 5.f; }
	if(App.GetInput().IsKeyDown(sf::Key::Numpad5)) { v =  0.f; }
	if(App.GetInput().IsKeyDown(sf::Key::Numpad2)) { v -= 5.f; }

	if(App.GetInput().IsKeyDown(sf::Key::Numpad4)) { rot += -1.0f * App.GetFrameTime(); _PO.body->SetTransform(_PO.body->GetPosition(), rot);  }
	if(App.GetInput().IsKeyDown(sf::Key::Numpad6)) { rot += 1.0f * App.GetFrameTime(); _PO.body->SetTransform(_PO.body->GetPosition(), rot); }
	
	vel.x = v * cos((b2_pi*(rot*RADTODEG))/180);
    vel.y = v * sin((b2_pi*(rot*RADTODEG))/180);

std::cout<< vel.x << " " << vel.y << " " << v << "\n";

	_PO.body->SetAngularVelocity(0.f);
	_PO.body->SetLinearVelocity( vel );

//float change = force - vel.x;
//force = _PO.body->GetMass() * change;

//	_PO.body->ApplyLinearImpulse(b2Vec2(force, 0), _PO.body->GetWorldCenter());

	world->Step(frequency, 6, 2);

	_PO.sprite.SetPosition( _PO.body->GetPosition().x, _PO.body->GetPosition().y);
	_PO.sprite.SetRotation( -(_PO.body->GetAngle()*(180/b2_pi)) );
	
	
	

	App.Draw(_PO.sprite);
}

void Physic::LoadStaticMapObjects(float OX, float OY, unsigned int TileWidth, unsigned int TileHeigth)
{
	WallObject *WO = new WallObject();

	WO->position = b2Vec2(OX, OY);

	WO->bodyDef = new b2BodyDef;
	WO->bodyDef->type = b2_staticBody;
	WO->bodyDef->position.Set(OX, OY);

	WO->body = world->CreateBody(WO->bodyDef);

	WO->shape = new b2PolygonShape;
	WO->shape->SetAsBox(TileWidth / 2.f, TileHeigth / 2.f);

	WO->body->CreateFixture(WO->shape, 1000.f);
	
	m_WallObjects.push_back(WO);
}