#ifndef _COMMON_MATH_VEC3_H
#define _COMMON_MATH_VEC3_H

#include "wpmath.h"

namespace wpmath {
class Vec3 {
 public:
  union {
    struct {
      float x, y, z;
    };

    float v[3];
  };

  Vec3() {}

  Vec3(const Vec3 &v) : x(v.x), y(v.y), z(v.z) {}

  Vec3(float vX, float vY, float vZ) : x(vX), y(vY), z(vZ) {}

  Vec3(const float * const xyz) : x(xyz[0]), y(xyz[1]), z(xyz[2]) {}

  inline const float * const get() const { return v; }

  inline void Set(float x, float y, float z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
  }

  inline void Set(const float * const xyz) {
    x = xyz[0];
    y = xyz[1];
    z = xyz[2];
  }

  inline void Set(const Vec3 &v) {
    x = v.x;
    y = v.y;
    z = v.z;
  }

  inline void Update(float x, float y, float z) {
    v[0] += x;
    v[1] += y;
    v[2] += z;
  }

  inline void Update(const float * const xyz) {
    x += xyz[0];
    y += xyz[1];
    z += xyz[2];
  }

  inline void Update(const Vec3 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
  }

  inline void Null() {
    x = 0;
    y = 0;
    z = 0;
  }

  inline bool IsNull() const { return (x == 0 && y == 0 && z == 0); }

  inline void Normalise() {
    const float r = Length();
    if (r != 0) {
      x /= r;
      y /= r;
      z /= r;
    } else {
      Null();
    }
  }

  inline float LengthSq() const { return (x * x + y * y + z * z); }

  inline float Length() const { return sqrt(LengthSq()); }

  inline const Vec3 &operator+=(const Vec3 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  inline const Vec3 &operator-=(const Vec3 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  inline const Vec3 &operator*=(float v) {
    x *= v;
    y *= v;
    z *= v;
    return *this;
  }

  inline const Vec3 &operator/=(float v) {
    x /= v;
    y /= v;
    z /= v;
    return *this;
  }

  inline const Vec3 &operator=(const Vec3 &v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
  }

  inline const Vec3 &operator=(float v) {
    x = v;
    y = v;
    z = v;
    return *this;
  }

  inline bool operator==(const Vec3 &v) const {
    return ((x == v.x) && (y == v.y) && (z == v.z));
  }

  inline bool operator!=(const Vec3 &v) const { return !(*this == v); }

  inline void Truncate(float size) {
    const float ratio = (size * size) / LengthSq();
    if (ratio < 1.0f) {
      x *= ratio;
      y *= ratio;
      z *= ratio;
    }
  }
};

static const Vec3 kNullVec3(0, 0, 0);

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline Vec3 operator*(const Vec3 &v, const float &i) {
  return Vec3(v.x * i, v.y * i, v.z * i);
}

inline Vec3 operator*(const float &i, const Vec3 &v) {
  return Vec3(i * v.x, i * v.y, i * v.z);
}

inline Vec3 operator/(const Vec3 &v, const float &i) {
  return Vec3(v.x / i, v.y / i, v.z / i);
}

inline Vec3 operator/(const float &i, const Vec3 &v) {
  return Vec3(i / v.x, i / v.y, i / v.z);
}

inline Vec3 operator-(const Vec3 &v) {
  return Vec3(-v.x, -v.y, -v.z);
}

inline Vec3 operator++(const Vec3 &v) {
  return Vec3(v.x + 1, v.y + 1, v.z + 1);
}

inline Vec3 operator--(const Vec3 &v) {
  return Vec3(v.x - 1, v.y - 1, v.z - 1);
}

inline float LengthSq(const Vec3 &v) {
  return v.LengthSq();
}

inline float length(const Vec3 &v) {
  return v.Length();
}

inline float DistanceSq(const Vec3 &v1, const Vec3 &v2) {
  return LengthSq(v1 - v2);
}

inline float Distance(const Vec3 &v1, const Vec3 &v2) {
  return sqrt(DistanceSq(v1, v2));
}

inline Vec3 Normalise(const Vec3 &v) {
  const float r = v.Length();
  if (r != 0) return Vec3(v.x / r, v.y / r, v.z / r);

  return kNullVec3;
}

inline float Dot(const Vec3 &v1, const Vec3 &v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vec3 Cross(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
                  v1.x * v2.y - v1.y * v2.x);
}

inline float GetAngle(const Vec3 &v1, const Vec3 &v2) {
  // To calculate the angle between 2 vectors
  // cos(theta) = p . q / |p| * |q|

  // calculate p dot q
  const auto pDotQ = Dot(v1, v2);

  // length of p multiply with length of q
  auto lengths = v1.Length() * v2.Length();
  if (lengths < 0.0001f) lengths = 0.1f;
  // else lengths = sqrt(lengths);

  // calculate the theta value
  const auto value = Clamp(pDotQ / lengths);

  return acos(value);
}

}  // namespace wpmath

#endif
