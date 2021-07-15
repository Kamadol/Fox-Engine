#include "Mat4x4.hpp"

Mat4x4::Mat4x4(float a)
{
	for (size_t i = 0; i < 16; i++)
	{
		this->vals[i] = a;
	}
}
Mat4x4::Mat4x4()
{
	for (size_t i = 0; i < 16; i++)
	{
		vals[i] = 0.0f;
	}
}

Mat4x4 Mat4x4::diagonal(float diagonal)
{
	Mat4x4 ret;
	ret.vals[0] = diagonal;
	ret.vals[5] = diagonal;
	ret.vals[10] = diagonal;
	ret.vals[15] = diagonal;

	return ret;
}
Mat4x4 Mat4x4::identity()
{
	return diagonal(1.0f);
}
Mat4x4 Mat4x4::translation(const Vector3& m)
{
	Mat4x4 ret = identity();
	ret.vals[12] = m.x;
	ret.vals[13] = m.y;
	ret.vals[14] = m.z;

	return ret;
}
Mat4x4 Mat4x4::rotation(float angle, const Vector3& axis)
{
	float sin = sinf(angle);
	float cos = cosf(angle);

	Mat4x4 ret;
	ret.vals[0] = axis.x * axis.x * (1.0f - cos) + cos;
	ret.vals[1] = axis.x * axis.y * (1.0f - cos) + axis.z * sin;
	ret.vals[2] = axis.x * axis.z * (1.0f - cos) - axis.y * sin;

	ret.vals[4] = axis.y * axis.x * (1.0f - cos) - axis.z * sin;
	ret.vals[5] = axis.y * axis.y * (1.0f - cos) + cos;
	ret.vals[6] = axis.y * axis.z * (1.0f - cos) + axis.x * sin;

	ret.vals[8] = axis.z * axis.x * (1.0f - cos) + axis.y * sin;
	ret.vals[9] = axis.z * axis.y * (1.0f - cos) - axis.x * sin;
	ret.vals[10] = axis.z * axis.z * (1.0f - cos) + cos;

	ret.vals[15] = 1.0f;

	return ret;
}
Mat4x4 Mat4x4::scale(const Vector3& m_V)
{
	Mat4x4 ret;
	ret.vals[0] = m_V.x;
	ret.vals[5] = m_V.y;
	ret.vals[10] = m_V.z;
	ret.vals[15] = 1.0f;

	return ret;
}
Mat4x4 Mat4x4::orthographic(float left, float right, float bottom, float top, float near, float far)
{
	Mat4x4 ret;
	ret.vals[0] = 2.0f / (right - left);
	ret.vals[5] = 2.0f / (top - bottom);
	ret.vals[10] = -2.0f / (far - near);
	ret.vals[15] = 1.0f;

	ret.vals[12] = -(right + left) / (right - left);
	ret.vals[13] = -(top + bottom) / (top - bottom);
	ret.vals[14] = -(far + near) / (far - near);

	return ret;
}
Mat4x4 Mat4x4::perspective(float fov, float aspectRatio, float near, float far)
{
	Mat4x4 ret;
	ret.vals[0] = 1.0f / (aspectRatio * tanf(fov * 0.5f));
	ret.vals[5] = 1.0f / tanf(fov * 0.5f);
	ret.vals[10] = (near + far) / (near - far);

	ret.vals[11] = -1.0f;
	ret.vals[14] = 2.0f * far * near / (near - far);

	return ret;
}

Mat4x4 Mat4x4::operator+(const Mat4x4& m)
{
	Mat4x4 ret = *this;

	for (size_t i = 0; i < 16; i++)
	{
		ret.vals[i] += m.vals[i];
	}

	return ret;
}
Mat4x4 Mat4x4::operator-(const Mat4x4& m)
{
	Mat4x4 ret = *this;

	for (size_t i = 0; i < 16; i++)
	{
		ret.vals[i] -= m.vals[i];
	}

	return ret;
}
Mat4x4 Mat4x4::operator*(const Mat4x4& m)
{
	Mat4x4 ret;

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			for (size_t k = 0; k < 4; k++)
			{
				ret.vals[j + i * 4] += vals[j + k * 4] * m.vals[i * 4 + k];
			}
		}
	}

	return ret;
}
Mat4x4 Mat4x4::operator*(float a)
{
	Mat4x4 ret = *this;

	for (size_t i = 0; i < 16; i++)
	{
		ret.vals[i] *= a;
	}

	return ret;
}
Mat4x4 Mat4x4::operator/(float a)
{
	Mat4x4 ret = *this;

	for (size_t i = 0; i < 16; i++)
	{
		ret.vals[i] /= a;
	}

	return ret;
}

Vector3 Mat4x4::operator*(const Vector3& v)
{
	return Vector3(
		vals[0] * v.x + vals[4] * v.y + vals[ 8] * v.z + vals[11],
		vals[1] * v.x + vals[5] * v.y + vals[ 9] * v.z + vals[12],
		vals[2] * v.x + vals[6] * v.y + vals[10] * v.z + vals[13]
	);
}
Vector4 Mat4x4::operator*(const Vector4& v)
{
	return Vector4(
		vals[0] * v.x + vals[4] * v.y + vals[ 8] * v.z + vals[12] * v.w,
		vals[1] * v.x + vals[5] * v.y + vals[ 9] * v.z + vals[13] * v.w,
		vals[2] * v.x + vals[6] * v.y + vals[10] * v.z + vals[14] * v.w,
		vals[3] * v.x + vals[7] * v.y + vals[11] * v.z + vals[15] * v.w
	);
}

Mat4x4& Mat4x4::operator+=(const Mat4x4& m)
{
	for (size_t i = 0; i < 16; i++)
	{
		vals[i] += m.vals[i];
	}

	return *this;
}
Mat4x4& Mat4x4::operator-=(const Mat4x4& m)
{
	for (size_t i = 0; i < 16; i++)
	{
		vals[i] -= m.vals[i];
	}

	return *this;
}
Mat4x4& Mat4x4::operator*=(const Mat4x4& m)
{
	Mat4x4 ret;

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			for (size_t k = 0; k < 4; k++)
			{
				ret.vals[j + i * 4] += vals[j + k * 4] * m.vals[i * 4 + k];
			}
		}
	}

	*this = ret;

	return *this;
}
Mat4x4& Mat4x4::operator*=(float a)
{
	for (size_t i = 0; i < 16; i++)
	{
		vals[i] *= a;
	}

	return *this;
}
Mat4x4& Mat4x4::operator/=(float a)
{
	for (size_t i = 0; i < 16; i++)
	{
		vals[i] /= a;
	}

	return *this;
}

float& Mat4x4::operator()(size_t x, size_t y)
{
	return vals[x * 4 + y];
}

std::ostream& operator<<(std::ostream& end, const Mat4x4& m)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			end << m.vals[i + j * 4] << " ";
		}
		if (i != 3)
			end << std::endl;
	}
	return end;
}
