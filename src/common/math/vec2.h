#ifndef _COMMON_MATH_VEC2_H
#define _COMMON_MATH_VEC2_H

#include "wpmath.h"

namespace wpmath {
class Vec2 {
 public:
  union {
    struct {
      float x, y;
    };

    float v[2];
  };

  Vec2() {}

  Vec2(const Vec2 &v) : x(v.x), y(v.y) {}

  Vec2(float vX, float vY) : x(vX), y(vY) {}

  Vec2(const float * const xy) : x(xy[0]), y(xy[1]) {}

  inline const float * const get() const { return v; }

  inline void Set(float x, float y) {
    v[0] = x;
    v[1] = y;
  }

  inline void Set(const float * const xy) {
    x = xy[0];
    y = xy[1];
  }

  inline void Set(const Vec2 &v) {
    x = v.x;
    y = v.y;
  }

  inline void Update(float x, float y) {
    v[0] += x;
    v[1] += y;
  }

  inline void Update(const float * const xy) {
    x += xy[0];
    y += xy[1];
  }

  inline void Update(const Vec2 &v) {
    x += v.x;
    y += v.y;
  }

  inline void Null() {
    x = 0;
    y = 0;
  }

  inline bool IsNull() const { return (x == 0 && y == 0); }

  inline void Normalise() {
    const float r = Length();
    if (r != 0) {
      x /= r;
      y /= r;
    } else {
      Null();
    }
  }

  inline float LengthSq() const { return (x * x + y * y); }

  inline float Length() const { return sqrt(LengthSq()); }

  inline const Vec2 &operator+=(const Vec2 &v) {
    x += v.x;
    y += v.y;
    return *this;
  }

  inline const Vec2 &operator-=(const Vec2 &v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  inline const Vec2 &operator*=(float v) {
    x *= v;
    y *= v;
    return *this;
  }

  inline const Vec2 &operator/=(float v) {
    x /= v;
    y /= v;
    return *this;
  }

  inline const Vec2 &operator=(const Vec2 &v) {
    x = v.x;
    y = v.y;
    return *this;
  }

  inline const Vec2 &operator=(float v) {
    x = v;
    y = v;
    return *this;
  }

  inline bool operator==(const Vec2 &v) const {
    return ((x == v.x) && (y == v.y));
  }

  inline bool operator!=(const Vec2 &v) const { return !(*this == v); }

  inline Vec2 operator-() {
    x = -x;
    y = -y;
    return *this;
  }

  inline Vec2 operator++() {
    x++;
    y++;
    return *this;
  }

  inline Vec2 operator--() {
    x--;
    y--;
    return *this;
  }

  inline void Truncate(float size) {
    const float ratio = (size * size) / LengthSq();
    if (ratio < 1.0f) {
      x *= ratio;
      y *= ratio;
    }
  }
};

static const Vec2 kNullVec2(0, 0);

inline Vec2 operator+(const Vec2 &v1, const Vec2 &v2) {
  return Vec2(v1.x + v2.x, v1.y + v2.y);
}

inline Vec2 operator-(const Vec2 &v1, const Vec2 &v2) {
  return Vec2(v1.x - v2.x, v1.y - v2.y);
}

inline Vec2 operator*(const Vec2 &v, const float &i) {
  return Vec2(v.x * i, v.y * i);
}

inline Vec2 operator*(const float &i, const Vec2 &v) {
  return Vec2(i * v.x, i * v.y);
}

inline Vec2 operator/(const Vec2 &v, const float &i) {
  return Vec2(v.x / i, v.y / i);
}

inline Vec2 operator/(const float &i, const Vec2 &v) {
  return Vec2(i / v.x, i / v.y);
}

inline Vec2 operator-(const Vec2 &v) {
  return Vec2(-v.x, -v.y);
}

inline Vec2 operator++(const Vec2 &v) {
  return Vec2(v.x + 1, v.y + 1);
}

inline Vec2 operator--(const Vec2 &v) {
  return Vec2(v.x - 1, v.y - 1);
}

inline float LengthSq(const Vec2 &v) {
  return v.LengthSq();
}

inline float length(const Vec2 &v) {
  return v.Length();
}

inline float DistanceSq(const Vec2 &v1, const Vec2 &v2) {
  return LengthSq(v1 - v2);
}

inline float Distance(const Vec2 &v1, const Vec2 &v2) {
  return sqrt(DistanceSq(v1, v2));
}

inline Vec2 Normalise(const Vec2 &v) {
  const float r = v.Length();
  if (r != 0) return Vec2(v.x / r, v.y / r);

  return kNullVec2;
}

inline float Dot(const Vec2 &v1, const Vec2 &v2) {
  return v1.x * v2.x + v1.y * v2.y;
}

}  // namespace wpmath

#endif
