#pragma once

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <initializer_list>
#include <iostream>
//#include "demos\bridge\bridge.cpp"

#include "demos\app.h"

class Node
{
public:
	Node() = default;
	Node(const Node&) = delete;
	virtual ~Node() {}
	virtual bool run() = 0;
};

class CompositeNode : public Node
{
public:

	virtual ~CompositeNode() {}

	bool run() override
	{
		return true;
	}



	const std::vector<std::unique_ptr<Node>>& getChildren() const
	{
		return children;
	}

	void addChild(std::unique_ptr<Node>& child)
	{
		children.emplace_back(std::move(child));
	}
	/*
	void addChildren(std::initializer_list<std::unique_ptr<Node>&>&& newChildren)
	{
		for (std::unique_ptr<Node> child : newChildren)
		{
			addChild(child);
		}
	}*/
	template <typename CONTAINER>
	void addChildren(CONTAINER& newChildren)
	{
		for (std::unique_ptr<Node>& child : newChildren)
		{
			addChild(child);
		}
	}
protected:
	void childrenShuffle()
	{
		std::random_shuffle(children.begin(), children.end());
	}
private:
	std::vector<std::unique_ptr<Node>> children;
};

class Selector : public CompositeNode
{
public:
	Selector() = default;
	Selector(const std::string& newName, const int myid, Application* myApp)//
	: name(newName), Id(myid), app(myApp){}
	virtual ~Selector() {}

	bool run() override
	{
		std::cout << name << std::endl;

		int emo=app->addForce();// function call to the latice returns emotion putting a number in emo
		if (getChildren().size() == 2)
		{
			if (emo == 0)			
				getChildren()[0]->run();			
			else
				getChildren()[1]->run();

			return true;
		}

		if (getChildren().size() == 3)
		{
			if (emo == 0)
				getChildren()[0]->run();
			else if(emo==1)
				getChildren()[1]->run();
			else
				getChildren()[2]->run();

			return true;
		}
		
		if (getChildren().size() == 0)
			return true;

		return false;
	}
	void setId(const int id)
	{
		Id = id;
	}
	int getId() const 
	{ 
		return Id;
	}
private:
	int Id = 0;
	std::string name;
	float probabilityOfSuccess;
	Application* app;
	
};

class RandomSelector : public CompositeNode
{
	RandomSelector() = default;
	virtual ~RandomSelector() {}

	bool run() override
	{
		childrenShuffle();
		for (auto& child : getChildren())
		{
			if (child->run())
				return true;
		}
		return false;
	}
};

class Sequence : public CompositeNode
{
public:
	Sequence() = default;
	Sequence(const int id) : Id(id) {}
	virtual ~Sequence() {}

	bool run() override
	{
		for (auto& child : getChildren())
		{
			if (!child->run())
				return false;
		}
		return true;
	}
	void setId(const int id)
	{
		Id = id;
	}
	int getId() const
	{
		return Id;
	}
private:
	int Id = 0;
};

class Action : public Node
{
public:
	Action() = default;
	Action(const std::string& newName, const int prob, const int myid)
		: name(newName), probabilityOfSuccess(0), Id(myid) {}
	int getId() { return Id; }
private:
	virtual bool run() override
	{
		//work out the math for this part
		if (probabilityOfSuccess == 0)
		{
			//probabilityOfSuccess = willing;
		}
		else
		{
			//probabilityOfSuccess += willing/.15;
		}
		
		if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) < probabilityOfSuccess)
		{
			std::cout << name << " succeeded." << std::endl;
			return true;
		}
		std::cout << name << " failed." << std::endl;
		return false;
	}

	int Id;
	std::string name;
	float probabilityOfSuccess;
};

class Root : public Node
{
public:
	Root() = default;
	
private:
	std::unique_ptr<Node> child;
	std::string name;
	void setChild(std::unique_ptr<Node>& newChild)
	{
		child.swap(newChild);
	}

	bool run() override
	{
		if (child)
			return child->run();
		return false;
	}
	void setName(std::string& Name) { name = Name; }
	
	friend class BehaviourTree;
};

class BehaviourTree
{
public:
	BehaviourTree()
	{
		root = std::make_unique<Root>();
	}

	void setRootChild(std::unique_ptr<Node>& newChild)
	{
		root->setChild(newChild);
	}

	void setName(const std::string& names)
	{
		name = names;
		root->setName(name);
	}
	std::string getName()
	{
		return name;
	}

	Root* getRoot()
	{
		return root.get();
	}

	bool run() const
	{
		return root->run();
	}
private:
	std::unique_ptr<Root> root;
	std::string name;
};