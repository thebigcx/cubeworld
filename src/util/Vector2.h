#pragma once

template <typename T>
class Vector2 {
	public:
		Vector2()
		{
			x = 0;
			y = 0;
		};

		Vector2(T p_x, T p_y)
		{
			x = p_x;
			y = p_y;
		};

		Vector2& operator =(const Vector2& p_other) noexcept
		{
			if (x != p_other.x && y != p_other.y)
			{
				x = p_other.x;
				y = p_other.y;
			}

			return *this;
		}

		Vector2 operator +(const Vector2& p_other) noexcept
		{
			Vector2 vec;
			vec.x = x + p_other.x;
			vec.y = y + p_other.y;

			return vec;
		}

		T x, y;

	private:

};

typedef Vector2<int>          Vector2i;
typedef Vector2<float>        Vector2f;
typedef Vector2<unsigned int> Vector2u;
typedef Vector2<double>       Vector2d;
