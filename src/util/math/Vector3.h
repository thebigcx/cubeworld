#pragma once

template <typename T>
class Vector3 {
	public:
		Vector3()
		{
			x = 0;
			y = 0;
			z = 0;
		};

		Vector3(T p_x, T p_y, T p_z)
		{
			x = p_x;
			y = p_y;
			z = p_z;
		};

		Vector3& operator =(const Vector3& p_other) noexcept
		{
			x = p_other.x;
			y = p_other.y;
			z = p_other.z;

			return *this;
		}

		Vector3 operator +(const Vector3& p_other) noexcept
		{
			Vector3 vec;
			vec.x = x + p_other.x;
			vec.y = y + p_other.y;
			vec.z = z + p_other.z;

			return vec;
		}

		T x, y, z;

	private:

};

typedef Vector3<int>          Vector3i;
typedef Vector3<float>        Vector3f;
typedef Vector3<unsigned int> Vector3u;
typedef Vector3<double>       Vector3d;