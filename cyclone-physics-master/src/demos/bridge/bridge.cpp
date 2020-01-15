/*
 * The bridge demo.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */

#include <cstdlib>
#include <ctime>
#include <cyclone/cyclone.h>
#include "../ogl_headers.h"
#include "../app.h"
#include "../timing.h"

#include <stdio.h>
#include <cassert>

#define ROD_COUNT 104
#define CABLE_COUNT 0
#define SUPPORT_COUNT 0

#define BASE_MASS 1
#define EXTRA_MASS 10

/**
 * The main demo class definition.
 */
class BridgeDemo : public MassAggregateApplication
{
    cyclone::ParticleRodConstraint *supports;
    cyclone::ParticleCable *cables;
    cyclone::ParticleRod *rods;

    cyclone::Vector3 massPos;
    cyclone::Vector3 massDisplayPos;

    /**
     * Updates particle masses to take into account the mass
     * that's crossing the bridge.
     */
    void updateAdditionalMass();

public:
    /** Creates a new demo object. */
    BridgeDemo();
    virtual ~BridgeDemo();

    /** Returns the window title for the demo. */
    virtual const char* getTitle();

    /** Display the particles. */
    virtual void display();

    /** Update the particle positions. */
    virtual void update();

    /** Handle a key press. */
    virtual void key(unsigned char key);

	virtual int addForce();

};

// Method definitions
BridgeDemo::BridgeDemo()
:
MassAggregateApplication(48), cables(0), supports(0), rods(0),
massPos(0,0,0.5f)
{
    // Create the masses and connections.

	//TOP ROW
	for (unsigned i = 0; i < 4; i++)
	{
		unsigned x = (i % 12) / 2;
		particleArray[i].setPosition(
			i,
			4,
			0
		);
		particleArray[i].setVelocity(0, 0, 0);
		particleArray[i].setDamping(0.9f);
		particleArray[i].setAcceleration(cyclone::Vector3::GRAVITY);
		particleArray[i].clearAccumulator();
	}

	for (unsigned i = 4; i < 8; i++)
	{
		unsigned x = (i % 12) / 2;
		particleArray[i].setPosition(
			i-4,
			5,
			0
		);
		particleArray[i].setVelocity(0, 0, 0);
		particleArray[i].setDamping(0.9f);
		particleArray[i].setAcceleration(cyclone::Vector3::GRAVITY);
		particleArray[i].clearAccumulator();
	}

	for (unsigned i = 8; i < 12; i++)
	{
		unsigned x = (i % 12) / 2;
		particleArray[i].setPosition(
			i-8,
			6,
			0
		);
		particleArray[i].setVelocity(0, 0, 0);
		particleArray[i].setDamping(0.9f);
		particleArray[i].setAcceleration(cyclone::Vector3::GRAVITY);
		particleArray[i].clearAccumulator();
	}

	for (unsigned i = 12; i < 16; i++)
	{
		unsigned x = (i % 12) / 2;
		particleArray[i].setPosition(
			i-12,
			7,
			0
		);
		particleArray[i].setVelocity(0, 0, 0);
		particleArray[i].setDamping(0.9f);
		particleArray[i].setAcceleration(cyclone::Vector3::GRAVITY);
		particleArray[i].clearAccumulator();
	}

	// SECOND ROW
	
	for (unsigned i = 16; i < 20; i++)
	{
		unsigned x = (i % 12) / 2;
		particleArray[i].setPosition(
			i-16,
			4,
			-1
		);
		particleArray[i].setVelocity(0, 0, 0);
		particleArray[i].setDamping(0.9f);
		particleArray[i].setAcceleration(cyclone::Vector3::GRAVITY);
		particleArray[i].clearAccumulator();
	}

	for (unsigned i = 20; i < 24; i++)
	{
		unsigned x = (i % 12) / 2;
		particleArray[i].setPosition(
			i - 20,
			5,
			-1
		);
		particleArray[i].setVelocity(0, 0, 0);
		particleArray[i].setDamping(0.9f);
		particleArray[i].setAcceleration(cyclone::Vector3::GRAVITY);
		particleArray[i].clearAccumulator();
	}

	for (unsigned i = 24; i < 28; i++)
	{
		unsigned x = (i % 12) / 2;
		particleArray[i].setPosition(
			i - 24,
			6,
			-1
		);
		particleArray[i].setVelocity(0, 0, 0);
		particleArray[i].setDamping(0.9f);
		particleArray[i].setAcceleration(cyclone::Vector3::GRAVITY);
		particleArray[i].clearAccumulator();
	}

	for (unsigned i = 28; i < 32; i++)
	{
		unsigned x = (i % 12) / 2;
		particleArray[i].setPosition(
			i - 28,
			7,
			-1
		);
		particleArray[i].setVelocity(0, 0, 0);
		particleArray[i].setDamping(0.9f);
		particleArray[i].setAcceleration(cyclone::Vector3::GRAVITY);
		particleArray[i].clearAccumulator();
	}

	// THRID RPW
	for (unsigned i = 32; i < 36; i++)
	{
		unsigned x = (i % 12) / 2;
		particleArray[i].setPosition(
			i - 32,
			4,
			-2
		);
		particleArray[i].setVelocity(0, 0, 0);
		particleArray[i].setDamping(0.9f);
		particleArray[i].setAcceleration(cyclone::Vector3::GRAVITY);
		particleArray[i].clearAccumulator();
	}

	for (unsigned i = 36; i < 40; i++)
	{
		unsigned x = (i % 12) / 2;
		particleArray[i].setPosition(
			i - 36,
			5,
			-2
		);
		particleArray[i].setVelocity(0, 0, 0);
		particleArray[i].setDamping(0.9f);
		particleArray[i].setAcceleration(cyclone::Vector3::GRAVITY);
		particleArray[i].clearAccumulator();
	}

	for (unsigned i = 40; i < 44; i++)
	{
		unsigned x = (i % 12) / 2;
		particleArray[i].setPosition(
			i - 40,
			6,
			-2
		);
		particleArray[i].setVelocity(0, 0, 0);
		particleArray[i].setDamping(0.9f);
		particleArray[i].setAcceleration(cyclone::Vector3::GRAVITY);
		particleArray[i].clearAccumulator();
	}

	for (unsigned i = 44; i < 48; i++)
	{
		unsigned x = (i % 12) / 2;
		particleArray[i].setPosition(
			i - 44,
			7,
			-2
		);
		particleArray[i].setVelocity(0, 0, 0);
		particleArray[i].setDamping(0.9f);
		particleArray[i].setAcceleration(cyclone::Vector3::GRAVITY);
		particleArray[i].clearAccumulator();
	}
    // Add the links
  /* cables = new cyclone::ParticleCable[CABLE_COUNT];
    for (unsigned i = 0; i < 14; i++)
    {
        cables[i].particle[0] = &particleArray[i];
        cables[i].particle[1] = &particleArray[i+2];
        cables[i].maxLength = 1.9f;
        cables[i].restitution = 0.3f;
        world.getContactGenerators().push_back(&cables[i]);
    }

    supports = new cyclone::ParticleRodConstraint[SUPPORT_COUNT];
    for (unsigned i = 0; i < SUPPORT_COUNT; i++)
    {
        supports[i].particle = particleArray+i;
        supports[i].anchor = cyclone::Vector3(
            i,
            6,
            cyclone::real(i%2)*1.6f-0.8f
            );
        if (i < 7) supports[i].length = cyclone::real(i/2)*0.5f + 3.0f;
        else supports[i].length = 5.5f - cyclone::real(i/2)*0.5f;
        //supports[i].restitution = 0.5f;
        world.getContactGenerators().push_back(&supports[i]);
    }*/

    rods = new cyclone::ParticleRod[ROD_COUNT];
	//most cross bars
    for (unsigned i = 0; i < 24; i++)
    {
        rods[i].particle[0] = &particleArray[i*2];
        rods[i].particle[1] = &particleArray[i*2+1];
       
    }
	// first row
	rods[24].particle[0] = &particleArray[1];
	rods[24].particle[1] = &particleArray[2];

	rods[25].particle[0] = &particleArray[5];
	rods[25].particle[1] = &particleArray[6];
		
	rods[26].particle[0] = &particleArray[9];
	rods[26].particle[1] = &particleArray[10];

	rods[27].particle[0] = &particleArray[13];
	rods[27].particle[1] = &particleArray[14];

	//second row
	rods[28].particle[0] = &particleArray[17];
	rods[28].particle[1] = &particleArray[18];

	rods[29].particle[0] = &particleArray[21];
	rods[29].particle[1] = &particleArray[22];

	rods[30].particle[0] = &particleArray[25];
	rods[30].particle[1] = &particleArray[26];

	rods[31].particle[0] = &particleArray[29];
	rods[31].particle[1] = &particleArray[30];
	
	//third row
	rods[32].particle[0] = &particleArray[33];
	rods[32].particle[1] = &particleArray[34];

	rods[33].particle[0] = &particleArray[37];
	rods[33].particle[1] = &particleArray[38];

	rods[34].particle[0] = &particleArray[41];
	rods[34].particle[1] = &particleArray[42];

	rods[35].particle[0] = &particleArray[45];
	rods[35].particle[1] = &particleArray[46];

	//down links between rows
	for (unsigned i = 36; i < 68; i++)
	{
		rods[i].particle[0] = &particleArray[i-36];
		rods[i].particle[1] = &particleArray[i-20];

	}

	// up links within rows
	for (unsigned i = 68; i < 80; i++)
	{
		rods[i].particle[0] = &particleArray[i - 68];
		rods[i].particle[1] = &particleArray[i - 64];
	}

	for (unsigned i = 80; i < 92; i++)
	{
		rods[i].particle[0] = &particleArray[i - 64];
		rods[i].particle[1] = &particleArray[i - 60];

	}
	for (unsigned i = 92; i < 104; i++)
	{
		rods[i].particle[0] = &particleArray[i - 60];
		rods[i].particle[1] = &particleArray[i - 56];

	}

	for (unsigned i = 0; i < 104; i++)
	{
		rods[i].length = 2;
		world.getContactGenerators().push_back(&rods[i]);
	}
    updateAdditionalMass();
}


BridgeDemo::~BridgeDemo()
{
    if (cables) delete[] cables;
    if (rods) delete[] rods;
    if (supports) delete[] supports;
}

void BridgeDemo::updateAdditionalMass()
{
    for (unsigned i = 0; i < 0; i++)
    {
        particleArray[i].setMass(BASE_MASS);
    }

    // Find the coordinates of the mass as an index and proportion
    int x = int(massPos.x);
    cyclone::real xp = real_fmod(massPos.x, cyclone::real(1.0f));
    if (x < 0)
    {
        x = 0;
        xp = 0;
    }
    if (x >= 5)
    {
        x = 5;
        xp = 0;
    }

    int z = int(massPos.z);
    cyclone::real zp = real_fmod(massPos.z, cyclone::real(1.0f));
    if (z < 0)
    {
        z = 0;
        zp = 0;
    }
    if (z >= 1)
    {
        z = 1;
        zp = 0;
    }

    // Calculate where to draw the mass
    massDisplayPos.clear();
/*
    // Add the proportion to the correct masses
    particleArray[x*2+z].setMass(BASE_MASS + EXTRA_MASS*(1-xp)*(1-zp));
    massDisplayPos.addScaledVector(
        particleArray[x*2+z].getPosition(), (1-xp)*(1-zp)
        );

    if (xp > 0)
    {
        particleArray[x*2+z+2].setMass(BASE_MASS + EXTRA_MASS*xp*(1-zp));
        massDisplayPos.addScaledVector(
            particleArray[x*2+z+2].getPosition(), xp*(1-zp)
            );

        if (zp > 0)
        {
            particleArray[x*2+z+3].setMass(BASE_MASS + EXTRA_MASS*xp*zp);
            massDisplayPos.addScaledVector(
                particleArray[x*2+z+3].getPosition(), xp*zp
                );
        }
    }
    if (zp > 0)
    {
        particleArray[x*2+z+1].setMass(BASE_MASS + EXTRA_MASS*(1-xp)*zp);
        massDisplayPos.addScaledVector(
            particleArray[x*2+z+1].getPosition(), (1-xp)*zp
            );
    }*/
}

int BridgeDemo::addForce()
{
	srand((unsigned)time(0));
	for (unsigned i = 0; i < 48; i++)
	{
		particleArray[i].setMass(BASE_MASS);
		particleArray[i].setEmotion(rand() % 3);
	}
	cyclone::Particle particle = particleArray[rand()%49];
	particle.setMass(BASE_MASS + EXTRA_MASS);
	return particle.getEmotion();
}

void BridgeDemo::display()
{
    MassAggregateApplication::display();

    glBegin(GL_LINES);
    glColor3f(0,0,1);
    for (unsigned i = 0; i < ROD_COUNT; i++)
    {
        cyclone::Particle **particles = rods[i].particle;
        const cyclone::Vector3 &p0 = particles[0]->getPosition();
        const cyclone::Vector3 &p1 = particles[1]->getPosition();
        glVertex3f(p0.x, p0.y, p0.z);
        glVertex3f(p1.x, p1.y, p1.z);
    }

    glColor3f(0,1,0);
    for (unsigned i = 0; i < CABLE_COUNT; i++)
    {
        cyclone::Particle **particles = cables[i].particle;
        const cyclone::Vector3 &p0 = particles[0]->getPosition();
        const cyclone::Vector3 &p1 = particles[1]->getPosition();
        glVertex3f(p0.x, p0.y, p0.z);
        glVertex3f(p1.x, p1.y, p1.z);
    }

    glColor3f(127, 156, 178);
    for (unsigned i = 0; i < SUPPORT_COUNT; i++)
    {
        const cyclone::Vector3 &p0 = supports[i].particle->getPosition();
        const cyclone::Vector3 &p1 = supports[i].anchor;
        glVertex3f(p0.x, p0.y, p0.z);
        glVertex3f(p1.x, p1.y, p1.z);
    }
    glEnd();

    glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(massDisplayPos.x, massDisplayPos.y+0.25f, massDisplayPos.z);
    glutSolidSphere(0.25f, 20, 10);
    glPopMatrix();
}

void BridgeDemo::update()
{
    MassAggregateApplication::update();

   // updateAdditionalMass();


}



const char* BridgeDemo::getTitle()
{
    return "Cyclone > Bridge Demo";
}

void BridgeDemo::key(unsigned char key)
{
    switch(key)
    {
    case 's': case 'S':
        massPos.z += 0.1f;
        if (massPos.z > 1.0f) massPos.z = 1.0f;
        break;
    case 'w': case 'W':
        massPos.z -= 0.1f;
        if (massPos.z < 0.0f) massPos.z = 0.0f;
        break;
    case 'a': case 'A':
        massPos.x -= 0.1f;
        if (massPos.x < 0.0f) massPos.x = 0.0f;
        break;
    case 'd': case 'D':
        massPos.x += 0.1f;
        if (massPos.x > 5.0f) massPos.x = 5.0f;
        break;

    default:
        MassAggregateApplication::key(key);
    }
}

/**
 * Called by the common demo framework to create an application
 * object (with new) and return a pointer.
 */
Application* getApplication()
{
    return new BridgeDemo();
}