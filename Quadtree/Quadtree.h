#pragma once
#include"Entity.h"
#include<vector>

using namespace std;

class Quadtree
{
private:
	Quadtree *topLeft;
	Quadtree *topRight;
	Quadtree *bottomLeft;
	Quadtree* bottomRight;
	size_t LEVEL_MAX = 2;
	size_t CAPACITY = 0;
	Rectangle boundaries;
	bool divided;
	size_t capacity;
	size_t level;
	//vector<Point*> children;
	vector<Entity*> children;
	void subdivide()
	{
		static Vector2f halfSize;
		halfSize.x = boundaries.w / 2.0f;
		halfSize.y = boundaries.h / 2.0f;
		topLeft = new Quadtree(Rectangle(boundaries.x - halfSize.x,
			boundaries.y - halfSize.y,
			halfSize.x, halfSize.y),
			capacity, level + 1);
		topRight = new Quadtree(Rectangle(boundaries.x + halfSize.x,
			boundaries.y - halfSize.y,
			halfSize.x, halfSize.y),
			capacity, level + 1);
		bottomLeft = new Quadtree(Rectangle(boundaries.x - halfSize.x,
			boundaries.y + halfSize.y,
			halfSize.x, halfSize.y),
			capacity, level + 1);
		bottomRight = new Quadtree(Rectangle(boundaries.x + halfSize.x,
			boundaries.y + halfSize.y,
			halfSize.x, halfSize.y),
			capacity, level + 1);
		divided = true;
	}
public:
	Quadtree(const Rectangle& _boundaries, size_t _capacity, size_t _level) :
		topLeft(NULL), topRight(NULL), bottomLeft(NULL), bottomRight (NULL),
		boundaries(_boundaries), divided(false), capacity(_capacity), level(_level)
	{
		if (level >= LEVEL_MAX)
			capacity = 0;
	}
	void setLevelMax(int l) {
		LEVEL_MAX = l;
	}
	void setCapacity(int c) {
		CAPACITY = c;
	}
	~Quadtree()
	{
		if (divided)
		{
			delete topLeft;
			delete topRight;
			delete bottomLeft;
			delete bottomRight;
		}
	}
	void insert(/*Point* p*/ Entity *e) {
		if (!boundaries.intersects(*e))
			return;
		if (!divided)
		{
			children.push_back(e);
			if (children.size() > capacity && capacity != 0)
			{
				subdivide();
				//vector<Point*>::iterator it = children.begin();
				vector<Entity*>::iterator it = children.begin();
				while (it != children.end())
				{
					topLeft->insert(*it);
					topRight->insert(*it);
					bottomLeft->insert(*it);
					bottomRight->insert(*it);

					it = children.erase(it);
				}
			}
		}
		else
		{
			topLeft->insert(e);
			topRight->insert(e);
			bottomLeft->insert(e);
			bottomRight->insert(e);
		}
	}

	void query(const Rectangle &area, /*vector<Point*>& found*/ vector<Entity*>& found) const
	{
		if (!area.intersects(boundaries))
			return;
		if (divided)
		{
			topLeft->query(area, found);
			topRight->query(area, found);
			bottomLeft->query(area, found);
			bottomRight->query(area, found);
		}
		else
		{
			for (size_t i = 0; i < children.size(); ++i) 
			{
				if (area.intersects(*children[i]))
					found.push_back(children[i]);
			}
		}
	}

	void draw(RenderTarget& t) {
		if (divided) {
			static Vertex vertices[4];
			vertices[0] = Vertex(Vector2f(boundaries.x,
				boundaries.y + boundaries.h), Color::White);
			vertices[1] = Vertex(Vector2f(boundaries.x,
				boundaries.y - boundaries.h), Color::White);
			vertices[2] = Vertex(Vector2f(boundaries.x-boundaries.w,
				boundaries.y), Color::White);
			vertices[3] = Vertex(Vector2f(boundaries.x+boundaries.w,
				boundaries.y), Color::White);
			t.draw(vertices, 4, Lines);
			topLeft->draw(t);
			topRight->draw(t);
			bottomLeft->draw(t);
			bottomRight->draw(t);
		}
	}

	void checkCollision()
	{
		if (divided)
		{
			topLeft->checkCollision();
			topRight->checkCollision();
			bottomLeft->checkCollision();
			bottomRight->checkCollision();
		}
		else 
		{
			for (vector<Entity*>::iterator i = children.begin(); i != children.end(); ++i)
			{
				for (vector<Entity*>::iterator j = i; j != children.end(); ++j)
				{
					if (i != j && (*i)->intersects(**j))
					{
						(*i)->collides = true;
						(*j)->collides = true;
					}
				}
			}
		}
	}
	void resize(int c) {
		children.resize(c-1);

	}
};

