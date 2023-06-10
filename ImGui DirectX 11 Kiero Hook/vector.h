#pragma once
#include "types.h"

// Vector addition.
vec2 vec2_add(vec2 v1, vec2 v2);

// Vector dot product.
float vec2_dot(vec2 v1, vec2 v2);

// Identity vector.
vec2 vec2_identity(void);

// Vector length.
float vec2_len(vec2 v1);

// Vector linear interpolation.
vec2 vec2_lerp(vec2 v1, vec2 v2, float k);

// Vector multiplication.
vec2 vec2_mul(vec2 v1, vec2 v2);

// Vector negation.
vec2 vec2_neg(vec2 v1);

// Vector normalization.
vec2 vec2_norm(vec2 v1);

// Returns the perpendicular vector to v1.
vec2 vec2_perp(vec2 v1);

// Vector projection of v1 on v2.
vec2 vec2_proj(vec2 v1, vec2 v2);

// Vector scaling.
vec2 vec2_scale(vec2 v1, float k);

// Sets vector components.
vec2 vec2_set(float x, float y);

// Vector subtraction.
vec2 vec2_sub(vec2 v1, vec2 v2);

// Zero vector.
vec2 vec2_zero(void);

// Vector addition.
vec3 vec3_add(vec3 v1, vec3 v2);

// Vector cross product.
vec3 vec3_cross(vec3 v1, vec3 v2);

// Vector dot product.
float vec3_dot(vec3 v1, vec3 v2);

// Identity vector.
vec3 vec3_identity();

// Vector length.
float vec3_len(vec3 v1);

// Vector linear interpolation.
vec3 vec3_lerp(vec3 v1, vec3 v2, float k);

// Vector multiplication.
vec3 vec3_mul(vec3 v1, vec3 v2);

// Vector negation.
vec3 vec3_neg(vec3 v1);

// Vector normalization.
vec3 vec3_norm(vec3 v1);

// Vector projection of v1 on v2.
vec3 vec3_proj(vec3 v1, vec3 v2);

// Vector scaling.
vec3 vec3_scale(vec3 v1, float k);

// Sets vector components.
vec3 vec3_set(float x, float y, float z);

// Vector subtraction.
vec3 vec3_sub(vec3 v1, vec3 v2);

// Zero vector.
vec3 vec3_zero();

// Vector addition.
vec4 vec4_add(vec4 v1, vec4 v2);

// Vector dot product.
float vec4_dot(vec4 v1, vec4 v2);

// Identity vector.
vec4 vec4_identity(void);

// Vector length.
float vec4_len(vec4 v1);

// Vector linear interpolation.
vec4 vec4_lerp(vec4 v1, vec4 v2, float k);

// Vector multiplication.
vec4 vec4_mul(vec4 v1, vec4 v2);

// Vector negation.
vec4 vec4_neg(vec4 v1);

// Vector normalization.
vec4 vec4_norm(vec4 v1);

// Vector projection of v1 on v2.
vec4 vec4_proj(vec4 v1, vec4 v2);

// Vector scaling.
vec4 vec4_scale(vec4 v1, float k);

// Sets vector components.
vec4 vec4_set(float x, float y, float z, float w);

// Vector subtraction.
vec4 vec4_sub(vec4 v1, vec4 v2);

// Zero vector.
vec4 vec4_zero(void);
