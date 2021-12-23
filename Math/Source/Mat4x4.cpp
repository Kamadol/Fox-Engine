#include "Mat4x4.hpp"

/*
|0 4  8 12|
|1 5  9 13|
|2 6 10 14|
|3 7 11 15|
*/

Mat4x4::Mat4x4(float a)
{
	for (size_t i = 0; i < 16; i++)
	{
		this->vals[i] = a;
	}
}
Mat4x4::Mat4x4(float* v)
{
	for (size_t i = 0; i < 16; i++)
	{
		vals[i] = v[i];
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
Mat4x4 Mat4x4::rotation(const Vector3& axis, float angle)
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
Mat4x4 Mat4x4::rotation(const Vector3& eulerXYZ)
{
	float sinX = sinf(eulerXYZ.x);
	float cosX = cosf(eulerXYZ.x);
	float sinY = sinf(eulerXYZ.y);
	float cosY = cosf(eulerXYZ.y);
	float sinZ = sinf(eulerXYZ.z);
	float cosZ = cosf(eulerXYZ.z);

	Mat4x4 ret;
	ret.vals[0] =  cosY * cosZ;
	ret.vals[1] =  cosX * sinZ + cosZ * sinX * sinY;
	ret.vals[2] =  sinX * sinZ - cosX * cosZ * sinY;
	ret.vals[4] = -cosY * sinZ;
	ret.vals[5] =  cosX * cosZ - sinX * sinY * sinZ;
	ret.vals[6] =  cosZ * sinX + cosX * sinY * sinZ;
	ret.vals[8] =  sinY;
	ret.vals[9] = -cosY * sinX;
	ret.vals[10] = cosX * cosY;

	ret.vals[15] = 1.0f;

	return ret;
}
Mat4x4 Mat4x4::rotationX(float angle)
{
	float sin = sinf(angle);
	float cos = cosf(angle);

	Mat4x4 ret;
	ret.vals[0] = 1.0f;
	ret.vals[5] = cos;
	ret.vals[6] = sin;
	ret.vals[9] = -sin;
	ret.vals[10] = cos;

	ret.vals[15] = 1.0f;

	return ret;
}
Mat4x4 Mat4x4::rotationY(float angle)
{
	float sin = sinf(angle);
	float cos = cosf(angle);

	Mat4x4 ret;
	ret.vals[0] = cos;
	ret.vals[2] = -sin;
	ret.vals[5] = 1.0f;
	ret.vals[8] = sin;
	ret.vals[10] = cos;

	ret.vals[15] = 1.0f;

	return ret;
}
Mat4x4 Mat4x4::rotationZ(float angle)
{
	float sin = sinf(angle);
	float cos = cosf(angle);

	Mat4x4 ret;
	ret.vals[0] = cos;
	ret.vals[1] = sin;
	ret.vals[5] = cos;
	ret.vals[4] = -sin;
	ret.vals[10] = 1.0f;

	ret.vals[15] = 1.0f;

	return ret;
}
Mat4x4 Mat4x4::scale(const Vector3& v)
{
	Mat4x4 ret;
	ret.vals[0] = v.x;
	ret.vals[5] = v.y;
	ret.vals[10] = v.z;
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
Mat4x4 Mat4x4::lookAt(Vector3 position, Vector3 target, Vector3 up)
{
	Vector3 direction = (position - target).unit();
	Vector3 right = (up ^ direction).unit();
	Vector3 cameraUp = direction ^ right;

	Mat4x4 view;
	view.vals[0] =     right.x; view.vals[4] =     right.y; view.vals[8]  =     right.z; view.vals[12] =     -right * position;
	view.vals[1] =  cameraUp.x; view.vals[5] =  cameraUp.y; view.vals[9]  =  cameraUp.z; view.vals[13] =  -cameraUp * position;
	view.vals[2] = direction.x; view.vals[6] = direction.y; view.vals[10] = direction.z; view.vals[14] = -direction * position;
	view.vals[3] =        0.0f; view.vals[7] =        0.0f; view.vals[11] =        0.0f; view.vals[15] =                  1.0f;

	return view;
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
Mat4x4 Mat4x4::operator*(const Mat4x4& m) const
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
		vals[0] * v.x + vals[4] * v.y + vals[ 8] * v.z + vals[12],
		vals[1] * v.x + vals[5] * v.y + vals[ 9] * v.z + vals[13],
		vals[2] * v.x + vals[6] * v.y + vals[10] * v.z + vals[14]
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
const float& Mat4x4::operator()(size_t x, size_t y) const
{
	return vals[x * 4 + y];
}
Vector4& Mat4x4::operator()(size_t x)
{
	return columns[x * 4];
}
const Vector4& Mat4x4::operator()(size_t x) const
{
	return columns[x * 4];
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
