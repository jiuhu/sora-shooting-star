#ifndef _COMMON_MATH_WPMATH_H
#define _COMMON_MATH_WPMATH_H

namespace wpmath {
constexpr float epsilon = 1E-6f;
constexpr float FullDegree = 360.0f;
constexpr float HalfDegree = 180.0f;
constexpr float PI = 3.141592654f;
constexpr float TwoPI = 6.283185307f;
constexpr float OneDivPI = 0.318309886f;
constexpr float PIDivTwo = 1.570796327f;
constexpr float PIDivFour = 0.785398163f;
constexpr float RadianToDegree = HalfDegree / PI;
constexpr float DegreeToRadian = PI / HalfDegree;

template <class T>
inline float ToRadian(T degree) {
  return degree * DegreeToRadian;
}

template <class T>
inline float ToDegree(T radian) {
  return radian * RadianToDegree;
}

template <class T>
inline T MinValue(const T& value1, const T& value2) {
  return (value1 > value2) ? value2 : value1;
}

template <class T>
inline T MaxValue(const T& value1, const T& value2) {
  return (value1 > value2) ? value1 : value2;
}

template <class T>
inline T Clamp(T v, T min, T max) {
  return v < min ? min : (v > max ? max : v);
}

template <class T>
inline T Clamp(T v) {
  return Clamp(v, -1.0f, 1.0f);
}

}  // namespace wpmath

#endif
