#pragma once


class Random
{
private:

	float a;
	float b;
public:

	Random();
	~Random();
	float random(float a, float b){ rand()%b+a; }
};