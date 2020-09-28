#include "Color.h"

#include <algorithm>

const Color Color::Black (0,   0,   0,   255);
const Color Color::Red   (255, 0,   0,   255);
const Color Color::Green (0,   255, 0,   255);
const Color Color::Blue  (0,   0,   255, 255);
const Color Color::Yellow(255, 255, 0,   255);
const Color Color::Purple(255, 0,   255, 255);
const Color Color::White (255, 255, 255, 255);

bool operator ==(const Color& left, const Color& right)
{
	return (left.r == right.r) &&
		   (left.g == right.g) &&
		   (left.b == right.b) &&
		   (left.a == right.a);
}

bool operator !=(const Color& left, const Color& right)
{
	return !(left == right);
}

Color operator +(const Color& left, const Color& right)
{
	return Color(std::min(int(left.r) + right.r, 255),
				 std::min(int(left.g) + right.g, 255),
				 std::min(int(left.b) + right.b, 255),
				 std::min(int(left.a) + right.a, 255));
}

Color operator -(const Color& left, const Color& right)
{
	return Color(std::max(int(left.r) - right.r, 0),
				 std::max(int(left.g) - right.g, 0),
				 std::max(int(left.b) - right.b, 0),
				 std::max(int(left.a) - right.a, 0));
}

Color operator *(const Color& left, const Color& right)
{
	return Color(int(left.r) * right.r / 255,
                 int(left.g) * right.g / 255,
                 int(left.b) * right.b / 255,
                 int(left.a) * right.a / 255);
}

Color& operator +=(Color& left, const Color& right)
{
	return left = left + right;
}

Color& operator -=(Color& left, const Color& right)
{
	return left = left - right;
}

Color& operator *=(Color& left, const Color& right)
{
	return left = left * right;
}
