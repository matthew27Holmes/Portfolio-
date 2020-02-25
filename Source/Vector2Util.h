#pragma once
struct Vector2
{
	float x, y;
	Vector2 operator +(Vector2 a)
	{
		x += a.x;
		y += a.y;
		return{ x,y };
	}
	Vector2 operator -(Vector2 a)
	{
		x -= a.x;
		y -= a.y;
		return {x,y};
	}
	bool operator == (Vector2 a)
	{
		return x == a.x && y == a.y;
	}

	bool operator !=(Vector2 a)
	{
		return !(*this == a);
	}

	float Distance(Vector2 a)
	{
		return sqrt(pow(x - a.x, 2) + pow(y - a.y, 2));
	}
};
