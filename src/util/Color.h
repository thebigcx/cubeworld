#pragma once

#include <stdint.h>

#include "math/Math.h"

class Color {
	public:
		Color()
        {
        	r = 0;
        	g = 0;
        	b = 0;
        	a = 255;
        }

		Color(uint8_t r, uint8_t g, uint8_t b)
        {
        	this->r = r;
        	this->g = g;
        	this->b = b;
        	this->a = 255;
        }

		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        {
            this->r = r;
        	this->g = g;
        	this->b = b;
        	this->a = a;
        }

		static Color normalise(Color p_col)
		{
			p_col.r = Math::map(p_col.r, 0, 255, 0, 1);
			p_col.g = Math::map(p_col.g, 0, 255, 0, 1);
			p_col.b = Math::map(p_col.b, 0, 255, 0, 1);
			p_col.a = Math::map(p_col.a, 0, 255, 0, 1);
			return p_col;
		}

		uint8_t r, g, b, a;

        static const Color Black;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Purple;
		static const Color White;


};

bool operator !=(const Color& left, const Color& right);
bool operator ==(const Color& left, const Color& right);

Color operator +(const Color& left, const Color& right);
Color operator -(const Color& left, const Color& right);
Color operator *(const Color& left, const Color& right);

Color& operator +=(Color& left, const Color& right);
Color& operator -=(Color& left, const Color& right);
Color& operator *=(Color& left, const Color& right);
