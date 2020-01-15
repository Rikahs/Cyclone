/*
 * The main entry point for all demos.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */
#include "../src/BehaviourTree.h"
#include "../src/json.hpp"
#include <memory>
#include <iostream>
#include <fstream>
// Include appropriate OpenGL headers.
#include "ogl_headers.h"

// Include the general application structure.
#include "app.h"

// Include the timing functions
#include "timing.h"

using json = nlohmann::json;
using namespace std;
// Forward declaration of the function that will return the
// application object for this particular demo. This should be
// implemented in the demo's .cpp file.
extern Application* getApplication();

// Store the global application object.
Application* app;

/**
 * Creates a window in which to display the scene.
 */
void createWindow(const char* title)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640,320);
    glutInitWindowPosition(0,0);
    glutCreateWindow(title);
}

/**
 * Called each frame to update the 3D scene. Delegates to
 * the application.
 */
void update()
{
    // Update the timing.
    TimingData::get().update();

    // Delegate to the application.
    app->update();
}

/**
 * Called each frame to display the 3D scene. Delegates to
 * the application.
 */
void display()
{
    app->display();

    // Update the displayed content.
    glFlush();
    glutSwapBuffers();
}

/**
 * Called when a mouse button is pressed. Delegates to the
 * application.
 */
void mouse(int button, int state, int x, int y)
{
    app->mouse(button, state, x, y);
}

/**
 * Called when the display window changes size.
 */
void reshape(int width, int height)
{
    app->resize(width, height);
}

/**
 * Called when a key is pressed.
 */
void keyboard(unsigned char key, int x, int y)
{
    // Note we omit passing on the x and y: they are rarely needed.
    app->key(key);
}

/**
 * Called when the mouse is dragged.
 */
void motion(int x, int y)
{
    app->mouseDrag(x, y);
}


unique_ptr<Node> processBNode(const json& node, Application* app)
{
	unique_ptr<Node> result;
	switch (node["type"].get<int>())
	{
	case 0:// Selector
	{
		unique_ptr<Selector> selector = make_unique<Selector>(node["description"].get<string>(), 
			node["id"].get<int>()
			, app);
			
		for (auto& child : node["children"])
		{
			selector->addChild(processBNode(child,app));
		}
		result = move(selector);
		break;
	}
	case 1:// Sequence
	{
		unique_ptr<Sequence> sequence = make_unique<Sequence>(node["id"].get<int>());
		for (auto& child : node["children"])
		{
			sequence->addChild(processBNode(child,app));
		}
		result = move(sequence);
		break;
	}
	case 2:// Action
	{
		unique_ptr<Action> action = make_unique<Action>(node["description"].get<string>(),
			node["parameters"]["probabilityOfSuccess"].get<int>(),
			node["id"].get<int>());
		result = move(action);
		break;
	}
	}
	return result;
}


/**
 * The main entry point. We pass arguments onto GLUT.
 */
int main(int argc, char** argv)
{  
	// Create the application and its window
    app = getApplication();
    createWindow(app->getTitle());



    // Set up GLUT and the timers
    glutInit(&argc, argv);
    TimingData::init();

   

    // Set up the appropriate handler functions
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

		json behaviourFormat;

	{ // Read From File
		ifstream inputFile("Breakfast.json");
		if (inputFile.fail())
		{
			cerr << "Failed to open 'Breakfast.json'." << endl;
			return -1;
		}
		inputFile >> behaviourFormat;
	}

	BehaviourTree Btree;
	Btree.setName(behaviourFormat["title"]);
	Btree.setRootChild(processBNode(behaviourFormat["root"], app));
	
	Btree.run();
    // Run the application
    app->initGraphics();
    glutMainLoop();

    // Clean up the application
    app->deinit();
    delete app;
    TimingData::deinit();
}
