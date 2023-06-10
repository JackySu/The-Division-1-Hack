#pragma once

// Two dimension vector.
typedef struct vec2
{
	constexpr vec2(
		const float x = 0.f,
		const float y = 0.f) noexcept :
		x(x), y(y) {}
	
	constexpr const vec2 operator-(const vec2 other) const noexcept
	{
		return vec2{ x - other.x, y - other.y };
	}

	constexpr const vec2 operator+(const vec2 other) const noexcept
	{
		return vec2{ x - other.x, y - other.y };
	}

	constexpr const vec2 operator*(const float factor) const noexcept
	{
		return vec2{ x * factor, y * factor };
	}

	constexpr const vec2 operator/(const float factor) const noexcept
	{
		return vec2{ x / factor, y / factor};
	}

	float x;
	float y;
} vec2;




// Three dimension vector.
typedef struct vec3
{
	constexpr vec3(
		const float x = 0.f,
		const float y = 0.f,
		const float z = 0.f) noexcept :
		x(x), y(y), z(z) {}

	constexpr const vec3 operator-(const vec3 other) const noexcept
	{
		return vec3{ x - other.x, y - other.y, z - other.z };
	}

	constexpr const vec3 operator+(const vec3 other) const noexcept
	{
		return vec3{ x + other.x, y + other.y, z + other.z };
	}

	constexpr const vec3 operator*(const float factor) const noexcept
	{
		return vec3{ x * factor, y * factor, z * factor };
	}

	constexpr const vec3 operator/(const float factor) const noexcept
	{
		return vec3{ x / factor, y / factor,z / factor };
	}
	float x;
	float y;
	float z;
} vec3;

// Four dimension vector.
typedef struct vec4
{
	float x;
	float y;
	float z;
	float w;
} vec4;


// 4x4 Matrix.
typedef struct mat4
{
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;
} mat4;
