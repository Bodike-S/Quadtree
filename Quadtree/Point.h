#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>

class Point
{
public:
	float x, y;
	bool highlighted;

	Point() : x(0), y(0), highlighted(false) {}
	Point(float _x, float _y, bool hltd = false) :
		x(_x), y(_y), highlighted(hltd) {}
};

