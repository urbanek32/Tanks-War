#include "stdafx.h"

#define FACTOR 30.f

Physic::Physic()
{

	// create world
	gravity = new b2Vec2(0.f, 0.f); 
	world = new b2World(*gravity);

	// create ground
	groundSprite.SetImage(gResMng.Get_Image("CONTENT//mur3.jpg"));
	groundSprite.SetPosition(50.f, 200.0f);
	groundSprite.SetCenter(groundSprite.GetSize().x / 2, groundSprite.GetSize().y / 2);

	groundBodyDef = new b2BodyDef;
	groundBodyDef->type = b2BodyType::b2_staticBody;
	groundBodyDef->position.Set(groundSprite.GetPosition().x, groundSprite.GetPosition().y);
	
	groundBody = world->CreateBody(groundBodyDef);

	groundBox = new b2PolygonShape;
	groundBox->SetAsBox(groundSprite.GetSize().x / 2.0f, groundSprite.GetSize().y / 2.0f);

	groundBody->CreateFixture(groundBox, 0.0f);


	// create an Dynamic Object
	_PO.sprite.SetImage(gResMng.Get_Image("CONTENT//mur.jpg"));
	_PO.sprite.SetPosition(0.0f, 0.0f);
	_PO.sprite.SetCenter(_PO.sprite.GetSize().x / 2, _PO.sprite.GetSize().y / 2);

	_PO.bodyDef.type = b2_dynamicBody;
	_PO.bodyDef.position.Set(_PO.sprite.GetPosition().x, _PO.sprite.GetPosition().y);
	_PO.body = world->CreateBody(&_PO.bodyDef);

	_PO.box.SetAsBox(_PO.sprite.GetSize().x / 2.0f, _PO.sprite.GetSize().y / 2.0f);

	_PO.fixture.shape = &_PO.box;
	_PO.fixture.density = 50.0f;
	_PO.fixture.friction = 0.3f;

	_PO.body->CreateFixture(&_PO.fixture);
}

void Physic::Tick(sf::RenderWindow & App, float frequency)
{
	b2Vec2 vel = _PO.body->GetLinearVelocity();
	//float desiredVel = 0;
	if(App.GetInput().IsKeyDown(sf::Key::Num1)) { vel.y = b2Max( vel.y - 0.1f, -50.0f ); }
	if(App.GetInput().IsKeyDown(sf::Key::Num2)) { vel.y *=  0.98; }
	if(App.GetInput().IsKeyDown(sf::Key::Num3)) { vel.y = b2Min( vel.y + 0.1f,  50.0f ); }
	//float velChange = desiredVel - vel.y;
	//float force = _PO.body->GetMass() * velChange / App.GetFrameTime();

	_PO.body->SetLinearVelocity( vel );

	world->Step(frequency, 8, 3);

	_PO.sprite.SetPosition( _PO.body->GetPosition().x, _PO.body->GetPosition().y);
	_PO.sprite.SetRotation( -(_PO.body->GetAngle()*(180/b2_pi)) );
	
	
	groundSprite.SetPosition( groundBody->GetPosition().x, groundBody->GetPosition().y);

	App.Draw(_PO.sprite);
	App.Draw(groundSprite);
}