#pragma once
#include "Point.h"

using namespace sf;

class Rectangle
{
public:
		float x, y, w, h;
	Rectangle(float _x, float _y, float _w, float _h) :
		x(_x), y(_y), w(_w), h(_h) {}
	bool contains(const Point& p) const
	{
		return p.x >= x - w && p.x <= x + w &&
			p.y >= y - h && p.y <= y + h;
	}

	bool intersects(const Rectangle& other) const
	{
		return !(x - w > other.x + other.w ||
			x + w < other.x - other.w ||
			y - h > other.y + other.h ||
			y + h < other.y - other.h);
	}

	void draw(RenderTarget &t)
	{
		static Vertex vertices[5];
		vertices[0] = Vertex(Vector2f(x - w, y - h), Color::Magenta);
		vertices[1] = Vertex(Vector2f(x + w, y - h), Color::Magenta);
		vertices[2] = Vertex(Vector2f(x + w, y + h), Color::Magenta);
		vertices[3] = Vertex(Vector2f(x - w, y + h), Color::Magenta);
		vertices[4] = Vertex(Vector2f(x - w, y - h), Color::Magenta);
		t.draw(vertices, 5, LinesStrip);
	}
};

