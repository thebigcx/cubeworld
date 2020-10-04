#pragma once

template <typename T>
class Rect {
	public:
		Rect() {}

		Rect(T x, T y, T width, T height)
		{
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
		}

		Rect(Vector2<T> pos, Vector2<T> size)
		{
			this->x = pos.x;
			this->y = pos.y;
			this->width = size.x;
			this->height = size.y;
		}

		bool contains(Vector2<T> point) const
		{
			return point.x > x && point.x < x + width && point.y > y && point.y < y + height;
		}

		bool intersects(Rect<T> other) const
		{
			return other.x < x + width  && other.x + other.width > x && 
			       other.y < y + height && other.y + other.height > y;
		}

		Vector2<T> getIntersection(Rect<T> other) const
		{
			Vector2<T> amount;
			amount.x = abs(other.x - x + width);
			amount.y = abs(other.y - y + height);
			return amount;
		}

		T x, y, width, height;
};

typedef Rect<int> IntRect;
typedef Rect<float> FloatRect;