#ifndef _COMMON_MATH_MAT44_H
#define _COMMON_MATH_MAT44_H

#include <cmath>

#include "vec2.h"
#include "vec3.h"

/*
    m11  m12  m13  m14    m0  m4  m8  m12
M = m21  m22  m23  m24  = m1  m5  m9  m13
    m31  m32  m33  m34    m2  m6  m10 m14
    m41  m42  m43  m44    m3  m7  m11 m15
*/

namespace wpmath {
class Mat44 {
 public:
  union {
    struct {
      float m11, m21, m31, m41,
            m12, m22, m32, m42,
            m13, m23, m33, m43,
            m14, m24, m34, m44;
    };

    float m[16];
  };

  Mat44() { Identity(); }

  Mat44(const float * const matrix) {
    Set(matrix);
  }

  /*
      m11  m12   m13   m14     a1    a2    a3    a4
  M = m21  m22   m23   m24  =  a5    a6    a7    a8
      m31  m32   m33   m34     a9    a10   a11   a12
      m41  m42   m43   m44     a13   a14   a15   a16
  */
  Mat44(float a1, float a2, float a3, float a4,
        float a5, float a6, float a7, float a8,
        float a9, float a10, float a11, float a12,
        float a13, float a14, float a15, float a16)
      : m11(a1),
        m21(a5),
        m31(a9),
        m41(a13),
        m12(a2),
        m22(a6),
        m32(a10),
        m42(a14),
        m13(a3),
        m23(a7),
        m33(a11),
        m43(a15),
        m14(a4),
        m24(a8),
        m34(a12),
        m44(a16)
  {
    //  Empty
  }

  inline void Null() {
    for (auto i = 0; i < 16; i++) {
      m[i] = 0;
    }
  }

  inline void Identity() {
    m11 = 1.0f; m21 = 0;    m31 = 0;    m41 = 0;
    m12 = 0;    m22 = 1.0f; m32 = 0;    m42 = 0;
    m13 = 0;    m23 = 0;    m33 = 1.0f; m43 = 0;
    m14 = 0;    m24 = 0;    m34 = 0;    m44 = 1.0f;
  }

  inline bool IsNull() const {
    return (m11 == 0 && m21 == 0 && m31 == 0 && m41 == 0 &&
            m12 == 0 && m22 == 0 && m32 == 0 && m42 == 0 &&
            m13 == 0 && m23 == 0 && m33 == 0 && m43 == 0 &&
            m14 == 0 && m24 == 0 && m34 == 0 && m44 == 0);
  }

  inline void Set(float a1, float a2, float a3, float a4,
                  float a5, float a6, float a7, float a8,
                  float a9, float a10, float a11, float a12,
                  float a13, float a14, float a15, float a16) {
    //m11 = a1;  m21 = a2;  m31 = a3; m41 = a4;
    //m12 = a5;  m22 = a6;  m32 = a7; m42 = a8;
    //m13 = a9;  m23 = a10; m33 = a11; m43 = a12;
    //m14 = a13; m24 = a14; m34 = a15; m44 = a16;
    m11 = a1;  m21 = a2;  m31 = a3; m41 = a4;
    m21 = a5;  m22 = a6;  m23 = a7; m24 = a8;
    m31 = a9;  m32 = a10; m33 = a11; m34 = a12;
    m41 = a13; m42 = a14; m43 = a15; m44 = a16;
  }

  inline void Set(const float * const matrix) {
    for (int i = 0; i < 16; i++)
      m[i] = matrix[i];
  }

  inline void Scale(float k) {
    m11 *= k; m21 *= k; m31 *= k; m41 *= k;
    m12 *= k; m22 *= k; m32 *= k; m42 *= k;
    m13 *= k; m23 *= k; m33 *= k; m43 *= k;
    m14 *= k; m24 *= k; m34 *= k; m44 *= k;
  }

  inline void Translate(float x, float y, float z) {
    m14 += x;
    m24 += y;
    m34 += z;
  }

  inline void TranslateTo(float x, float y, float z) {
    m14 = x;
    m24 = y;
    m34 = z;
  }

  //inline void RotateX(float theta) {
  //  /*
  //    m * RX
  //           1   0  0
  //    RX  =  0   c  s
  //           0  -s  c
  //  */
  //  float s = sin(theta), c = cos(theta);
  //  float sn = -s;
  //  m12 = m12 * c + m13 * sn;
  //  m22 = m22 * c + m23 * sn;
  //  m32 = m32 * c + m33 * sn;
  //  m42 = m42 * c + m43 * sn;

  //  m13 = m12 * s + m13 * c;
  //  m23 = m22 * s + m23 * c;
  //  m33 = m32 * s + m33 * c;
  //  m43 = m42 * s + m43 * c;
  //}

  //inline void RotateY(float theta) {
  //  /*
  //    m * RY
  //           c  0  -s
  //    RY  =  0  1   0
  //           s  0   c
  //  */
  //  float s = sin(theta), c = cos(theta);
  //  m11 = m11 * c + m13 * s;
  //  m21 = m21 * c + m23 * s;
  //  m31 = m31 * c + m33 * s;
  //  m41 = m41 * c + m43 * s;

  //  float sn = -s;
  //  m13 = m11 * sn + m13 * c;
  //  m23 = m21 * sn + m23 * c;
  //  m33 = m31 * sn + m33 * c;
  //  m43 = m41 * sn + m43 * c;
  //}

  //inline void RotateZ(float theta) {
  //  /*
  //    m * RZ
  //           c  s  0
  //    RZ  = -s  c  0
  //           0  0  1
  //  */
  //  float s = sin(theta), c = cos(theta);
  //  float sn = -s;
  //  m11 = m11 * c + m12 * sn;
  //  m21 = m21 * c + m22 * sn;
  //  m31 = m31 * c + m32 * sn;
  //  m41 = m41 * c + m42 * sn;

  //  m12 = m11 * s + m12 * c;
  //  m22 = m21 * s + m22 * c;
  //  m32 = m31 * s + m32 * c;
  //  m42 = m41 * s + m42 * c;
  //}

  inline float Determinant() const {
    return (m11 * m22 - m12 * m21) * (m33 * m44 - m34 * m43) -
           (m11 * m23 - m13 * m21) * (m32 * m44 - m34 * m42) +
           (m11 * m24 - m14 * m21) * (m32 * m43 - m33 * m42) +
           (m12 * m23 - m13 * m22) * (m31 * m44 - m34 * m41) -
           (m12 * m24 - m14 * m22) * (m31 * m43 - m33 * m41) +
           (m13 * m24 - m14 * m23) * (m31 * m42 - m32 * m41);
  }

  inline void Inverse() {
    float det = Determinant();
    if (det * det < epsilon) {
      return;
    }
    float s = 1 / det;
    Set(s * (m22 * (m33 * m44 - m34 * m43) + m23 * (m34 * m42 - m32 * m44) +
             m24 * (m32 * m43 - m33 * m42)),
        s * (m32 * (m13 * m44 - m14 * m43) + m33 * (m14 * m42 - m12 * m44) +
             m34 * (m12 * m43 - m13 * m42)),
        s * (m42 * (m13 * m24 - m14 * m23) + m43 * (m14 * m22 - m12 * m24) +
             m44 * (m12 * m23 - m13 * m22)),
        s * (m12 * (m24 * m33 - m23 * m34) + m13 * (m22 * m34 - m24 * m32) +
             m14 * (m23 * m32 - m22 * m33)),
        s * (m23 * (m31 * m44 - m34 * m41) + m24 * (m33 * m41 - m31 * m43) +
             m21 * (m34 * m43 - m33 * m44)),
        s * (m33 * (m11 * m44 - m14 * m41) + m34 * (m13 * m41 - m11 * m43) +
             m31 * (m14 * m43 - m13 * m44)),
        s * (m43 * (m11 * m24 - m14 * m21) + m44 * (m13 * m21 - m11 * m23) +
             m41 * (m14 * m23 - m13 * m24)),
        s * (m13 * (m24 * m31 - m21 * m34) + m14 * (m21 * m33 - m23 * m31) +
             m11 * (m23 * m34 - m24 * m33)),
        s * (m24 * (m31 * m42 - m32 * m41) + m21 * (m32 * m44 - m34 * m42) +
             m22 * (m34 * m41 - m31 * m44)),
        s * (m34 * (m11 * m42 - m12 * m41) + m31 * (m12 * m44 - m14 * m42) +
             m32 * (m14 * m41 - m11 * m44)),
        s * (m44 * (m11 * m22 - m12 * m21) + m41 * (m12 * m24 - m14 * m22) +
             m42 * (m14 * m21 - m11 * m24)),
        s * (m14 * (m22 * m31 - m21 * m32) + m11 * (m24 * m32 - m22 * m34) +
             m12 * (m21 * m34 - m24 * m31)),
        s * (m21 * (m33 * m42 - m32 * m43) + m22 * (m31 * m43 - m33 * m41) +
             m23 * (m32 * m41 - m31 * m42)),
        s * (m31 * (m13 * m42 - m12 * m43) + m32 * (m11 * m43 - m13 * m41) +
             m33 * (m12 * m41 - m11 * m42)),
        s * (m41 * (m13 * m22 - m12 * m23) + m42 * (m11 * m23 - m13 * m21) +
             m43 * (m12 * m21 - m11 * m22)),
        s * (m11 * (m22 * m33 - m23 * m32) + m12 * (m23 * m31 - m21 * m33) +
             m13 * (m21 * m32 - m22 * m31)));
  }

  inline const Mat44& operator = (const Mat44 &mat) {
    Set(mat.m);
    return *this;
  }

  inline const float &operator[](size_t i) const {
    if (i > 16) i = 15;
    return m[i];
  }

  inline float &operator[](size_t i) {
    if (i > 16) i = 15;
    return m[i];
  }

  inline bool operator==(const Mat44 &mat) const {
    return m11 == mat.m11 && m21 == mat.m21 && m31 == mat.m31 && m41 == mat.m41 &&
           m12 == mat.m12 && m22 == mat.m22 && m32 == mat.m32 && m42 == mat.m42 &&
           m13 == mat.m13 && m23 == mat.m23 && m33 == mat.m33 && m43 == mat.m43 &&
           m14 == mat.m14 && m24 == mat.m24 && m34 == mat.m34 && m44 == mat.m44;
  }

  inline bool operator!=(const Mat44 &m) const { return !(*this == m); }

  inline const Mat44 &operator*=(const Mat44 &mat) {
    Set(m11 * mat.m11 + m12 * mat.m21 + m13 * mat.m31 + m14 * mat.m41,
        m11 * mat.m12 + m12 * mat.m22 + m13 * mat.m32 + m14 * mat.m42,
        m11 * mat.m13 + m12 * mat.m23 + m13 * mat.m33 + m14 * mat.m43,
        m11 * mat.m14 + m12 * mat.m24 + m13 * mat.m34 + m14 * mat.m44,

        m21 * mat.m11 + m22 * mat.m21 + m23 * mat.m31 + m24 * mat.m41,
        m21 * mat.m12 + m22 * mat.m22 + m23 * mat.m32 + m24 * mat.m42,
        m21 * mat.m13 + m22 * mat.m23 + m23 * mat.m33 + m24 * mat.m43,
        m21 * mat.m14 + m22 * mat.m24 + m23 * mat.m34 + m24 * mat.m44,

        m31 * mat.m11 + m32 * mat.m21 + m33 * mat.m31 + m34 * mat.m41,
        m31 * mat.m12 + m32 * mat.m22 + m33 * mat.m32 + m34 * mat.m42,
        m31 * mat.m13 + m32 * mat.m23 + m33 * mat.m33 + m34 * mat.m43,
        m31 * mat.m14 + m32 * mat.m24 + m33 * mat.m34 + m34 * mat.m44,

        m41 * mat.m11 + m42 * mat.m21 + m43 * mat.m31 + m44 * mat.m41,
        m41 * mat.m12 + m42 * mat.m22 + m43 * mat.m32 + m44 * mat.m42,
        m41 * mat.m13 + m42 * mat.m23 + m43 * mat.m33 + m44 * mat.m43,
        m41 * mat.m14 + m42 * mat.m24 + m43 * mat.m34 + m44 * mat.m44);
    return *this;
  }
};

inline void MatrixIdentity(Mat44 &m) {
  m.Identity();
}

inline Mat44 MatrixIdentity() {
  return Mat44(1.0f, 0, 0, 0, 0, 1.0f, 0, 0, 0, 0, 1.0f, 0, 0, 0, 0, 1.0f);
}

inline Mat44 MatrixTranslation(float x, float y) {
  return Mat44(1.0f, 0, 0, x, 0, 1.0f, 0, y, 0, 0, 1.0f, 0, 0, 0, 0, 1.0f);
}

inline Mat44 MatrixTranslation(float x, float y, float z) {
  return Mat44(1.0f, 0, 0, x, 0, 1.0f, 0, y, 0, 0, 1.0f, z, 0, 0, 0, 1.0f);
}

inline Mat44 MatrixTranslation(const Vec2 &v) {
  return Mat44(1.0f, 0, 0, v.x, 0, 1.0f, 0, v.y, 0, 0, 1.0f, 0, 0, 0, 0, 1.0f);
}

inline Mat44 MatrixTranslation(const Vec3 &v) {
  return Mat44(1.0f, 0, 0, v.x, 0, 1.0f, 0, v.y, 0, 0, 1.0f, v.z, 0, 0, 0, 1.0f);
}

inline Vec3 GetTranslation(const Mat44 &mat) {
  return Vec3(mat.m41, mat.m42, mat.m43);
}

inline Mat44 MatrixRotationX(float theta) {
  const float s = sin(theta), c = cos(theta);
  return Mat44(1.0f, 0, 0, 0, 0, c, s, 0, 0, -s, c, 0, 0, 0, 0, 1.0f);
}

inline Mat44 MatrixRotationY(float theta) {
  const float s = sin(theta), c = cos(theta);
  return Mat44(c, 0, -s, 0, 0, 1.0f, 0, 0, s, 0, c, 0, 0, 0, 0, 1.0f);
}

inline Mat44 MatrixRotationZ(float theta) {
  const float s = sin(theta), c = cos(theta);
  return Mat44(c, s, 0, 0, -s, c, 0, 0, 0, 0, 1.0f, 0, 0, 0, 0, 1.0f);
}

inline Mat44 MatrixRotationArbitrary(float angle, float x, float y, float z) {
  const float s = -sin(angle), c = cos(angle), k = 1 - c,
              kx = k * x, ky = k * y, kz = k * z,
              kxy = kx * y, kxz = kx * z, kyz = ky * z;
  return Mat44( kx * x + c,   kxy + z * s,  kxz - y * s,  0,
                kxy - z * s,  ky * y + c,   kyz + x * s,  0,
                kxz + y * s,  kyz - x * s,  kz * z + c,   0,
                0, 0, 0, 1.0f);
}

inline Mat44 MatrixRotationArbitrary(float angle, const Vec3 &axis) {
  return MatrixRotationArbitrary(angle, axis.x, axis.y, axis.z);
}

inline Mat44 MatrixFromEulerAngles(float x, float y, float z) {
  const float sX = sin(x), sY = sin(y), sZ = sin(z),
              cX = cos(x), cY = cos(y), cZ = cos(z);
  return Mat44( cY * cZ + sX * sY * sZ, cX * sZ, -sY * cZ + sX * cY * sZ, 0,
                -cY * sZ + sX * sY * cZ, cX * cZ, sY * sZ + sX * cY * cZ, 0,
                cX * sY, -sX, cX * cY, 0,
                0, 0, 0, 1.0f);
}

inline Mat44 MatrixFromEulerAngles(const Vec3 &axis) {
  return MatrixFromEulerAngles(axis.x, axis.y, axis.z);
}

//inline Mat44 MatrixFromEulerAngles(const EulerAngles &a) {
//  return MatrixFromEulerAngles(a.x, a.y, a.z);
//}

//inline EulerAngles EulerAnglesFromMatrix(const Mat44 &m) {
//  return EulerAngles(asin(-m.m23), atan2(m.m13, m.m33), atan2(m.m21, m.m22));
//}

inline Mat44 MatrixScale(float x, float y, float z) {
  return Mat44(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1.0f);
}

inline Mat44 MatrixScale(const Vec3 &scale) {
  return Mat44(scale.x, 0, 0, 0, 0, scale.y, 0, 0, 0, 0, scale.z, 0, 0, 0, 0, 1.0f);
}

inline Mat44 MatrixScale(float scale) {
  return Mat44(scale, 0, 0, 0, 0, scale, 0, 0, 0, 0, scale, 0, 0, 0, 0, 1.0f);
}

inline Mat44 MatrixScaleArbitrary(float scale, float x, float y, float z) {
  const float k = scale - 1.0f,
              kx = k * x, ky = k * y, kz = k * z,
              kxy = kx * y, kxz = kx * z, kyz = ky * z;
  return Mat44( 1.0f + kx * x, kxy, kxz, 0,
                kxy, 1.0f - ky * y, kyz, 0,
                kxz, kyz, 1.0f - kz * z, 0,
                0, 0, 0, 1.0f);
}

inline Mat44 MatrixScaleArbitrary(float scale, const Vec3 &axis) {
  return MatrixScaleArbitrary(scale, axis.x, axis.y, axis.z);
}

inline Mat44 MatrixTranspose(const Mat44 &m) {
  return Mat44(m.m11, m.m12, m.m13, m.m14,
               m.m21, m.m22, m.m23, m.m24,
               m.m31, m.m32, m.m33, m.m34,
               m.m41, m.m42, m.m43, m.m44);
}

inline Mat44 MatrixView(const Vec3 &u, const Vec3 &v,
                        const Vec3 &n, const Vec3 &eye) {
  return Mat44(u.x, u.y, u.z, -Dot(u, eye),
               v.x, v.y, v.z, -Dot(v, eye),
               n.x, n.y, n.z, -Dot(n, eye),
               0,   0,   0,   1.0f);
}

inline Mat44 MatrixLookAt(const Vec3 &eye, const Vec3 &center,
                              const Vec3 &up) {
  const Vec3 n = Normalise(eye - center);
  const Vec3 u = Normalise(Cross(up, n));

  return MatrixView(u, Cross(n, u), n, eye);
}

inline Mat44 OrthoProjection(float left, float right, float bottom, float top,
                         float zNear = -1.0f, float zFar = 1.0f) {
  /*
    2/r-l   0       0       -((r+l)/(r-l))
    0       2/t-b   0       -((t+b)/(t-b))
    0       0       -2/f-n  -((f+n)/(f-n))
    0       0       0       1
  */
  const float inv_w = 1.0f / (right - left),
              inv_h = 1.0f / (top - bottom),
              inv_fn = -1.0f / (zFar - zNear);
  return Mat44( 2.0f * inv_w, 0,            0,             -((right + left) * inv_w),
                0,            2.0f * inv_h, 0,             -((top + bottom) * inv_h),
                0,            0,            2.0f * inv_fn, (zFar + zNear) * inv_fn,
                0,            0,            0,             1.0f);
}

inline Mat44 OrthoProjection(float width, float height) {
  return OrthoProjection(0, width, height, 0, -1.0f, 1.0f);
}

inline Mat44 PerspectiveProjection(float fov, float aspect, float zNear, float zFar) {
  const float cot = 1.0f / tan(ToRadian(fov / 2.0f)),
              inv_nf = 1.0f / (zNear - zFar);
  return Mat44( cot / aspect, 0,   0,                       0,
                0,            cot, 0,                       0,
                0,            0,   (zNear + zFar) * inv_nf, (2.0f * zNear * zFar) * inv_nf,
                0,            0,   -1.0f,                   0);
}

inline Mat44 FrustumProjection(float left, float right, float bottom, float top,
                               float zNear, float zFar) {
  /*
    2n/(r-l)  0         (r+l)/(r-l)    0
    0         2n/(t-b)  (t+b)/(t-b)    0
    0         0         -((f+n)/(f-n)) -(2fn)/(f-n)
    0         0         -1             0
  */

  const float n2 = 2.0f * zNear,
              inv_w = 1.0f / (right - left),
              inv_h = 1.0f / (top - bottom),
              inv_fn = 1.0f / (zNear - zFar);
  return Mat44( n2 * inv_w, 0,          (right + left) * inv_w,  0,
                0,          n2 * inv_h, (top + bottom) * inv_h,  0,
                0,          0,          (zFar + zNear) * inv_fn, (n2 * zFar) * inv_fn,
                0,          0,          -1.0f,                   0);
}

inline Mat44 FrustumProjection(float width, float height, float zNear, float zFar) {
  return FrustumProjection(0, width, height, 0, zNear, zFar);
}

inline Mat44 operator*(float k, const Mat44 &m) {
  return Mat44(
    k * m.m11, k * m.m21, k * m.m31, k * m.m41,
    k * m.m12, k * m.m22, k * m.m32, k * m.m42,
    k * m.m13, k * m.m23, k * m.m33, k * m.m43,
    k * m.m14, k * m.m24, k * m.m34, k * m.m44
  );
}

inline Mat44 operator*(const Mat44 &m, float k) {
  return Mat44(
    m.m11 * k, m.m21 * k, m.m31 * k, m.m41 * k,
    m.m12 * k, m.m22 * k, m.m32 * k, m.m42 * k,
    m.m13 * k, m.m23 * k, m.m33 * k, m.m43 * k,
    m.m14 * k, m.m24 * k, m.m34 * k, m.m44 * k
  );
}
/*
    return Mat44(
  m11 * mat.m11 + m12 * mat.m21 + m13 * mat.m31 + m14 * mat.m41,
  m21 * mat.m11 + m22 * mat.m21 + m23 * mat.m31 + m24 * mat.m41,
  m31 * mat.m11 + m32 * mat.m21 + m33 * mat.m31 + m34 * mat.m41,
  m41 * mat.m11 + m42 * mat.m21 + m43 * mat.m31 + m44 * mat.m41,

  m11 * mat.m12 + m12 * mat.m22 + m13 * mat.m32 + m14 * mat.m42,
  m21 * mat.m12 + m22 * mat.m22 + m23 * mat.m32 + m24 * mat.m42,
  m31 * mat.m12 + m32 * mat.m22 + m33 * mat.m32 + m34 * mat.m42,
  m41 * mat.m12 + m42 * mat.m22 + m43 * mat.m32 + m44 * mat.m42,

  m11 * mat.m13 + m12 * mat.m23 + m13 * mat.m33 + m14 * mat.m43,
  m21 * mat.m13 + m22 * mat.m23 + m23 * mat.m33 + m24 * mat.m43,
  m31 * mat.m13 + m32 * mat.m23 + m33 * mat.m33 + m34 * mat.m43,
  m41 * mat.m13 + m42 * mat.m23 + m43 * mat.m33 + m44 * mat.m43,

  m11 * mat.m14 + m12 * mat.m24 + m13 * mat.m34 + m14 * mat.m44,
  m21 * mat.m14 + m22 * mat.m24 + m23 * mat.m34 + m24 * mat.m44,
  m31 * mat.m14 + m32 * mat.m24 + m33 * mat.m34 + m34 * mat.m44,
  m41 * mat.m14 + m42 * mat.m24 + m43 * mat.m34 + m44 * mat.m44);
  }
  */
inline Mat44 operator*(const Mat44 &m1, const Mat44 &m2) {
  return Mat44(
    m1.m11 * m2.m11 + m1.m12 * m2.m21 + m1.m13 * m2.m31 + m1.m14 * m2.m41,
    m1.m11 * m2.m12 + m1.m12 * m2.m22 + m1.m13 * m2.m32 + m1.m14 * m2.m42,
    m1.m11 * m2.m13 + m1.m12 * m2.m23 + m1.m13 * m2.m33 + m1.m14 * m2.m43,
    m1.m11 * m2.m14 + m1.m12 * m2.m24 + m1.m13 * m2.m34 + m1.m14 * m2.m44,

    m1.m21 * m2.m11 + m1.m22 * m2.m21 + m1.m23 * m2.m31 + m1.m24 * m2.m41,
    m1.m21 * m2.m12 + m1.m22 * m2.m22 + m1.m23 * m2.m32 + m1.m24 * m2.m42,
    m1.m21 * m2.m13 + m1.m22 * m2.m23 + m1.m23 * m2.m33 + m1.m24 * m2.m43,
    m1.m21 * m2.m14 + m1.m22 * m2.m24 + m1.m23 * m2.m34 + m1.m24 * m2.m44,

    m1.m31 * m2.m11 + m1.m32 * m2.m21 + m1.m33 * m2.m31 + m1.m34 * m2.m41,
    m1.m31 * m2.m12 + m1.m32 * m2.m22 + m1.m33 * m2.m32 + m1.m34 * m2.m42,
    m1.m31 * m2.m13 + m1.m32 * m2.m23 + m1.m33 * m2.m33 + m1.m34 * m2.m43,
    m1.m31 * m2.m14 + m1.m32 * m2.m24 + m1.m33 * m2.m34 + m1.m34 * m2.m44,

    m1.m41 * m2.m11 + m1.m42 * m2.m21 + m1.m43 * m2.m31 + m1.m44 * m2.m41,
    m1.m41 * m2.m12 + m1.m42 * m2.m22 + m1.m43 * m2.m32 + m1.m44 * m2.m42,
    m1.m41 * m2.m13 + m1.m42 * m2.m23 + m1.m43 * m2.m33 + m1.m44 * m2.m43,
    m1.m41 * m2.m14 + m1.m42 * m2.m24 + m1.m43 * m2.m34 + m1.m44 * m2.m44
  );
}

//inline Vec3 operator*(const Mat44 &m, const Vec3 &v) {
//  return Vec3(m.m11 * v.x + m.m12 * v.y + m.m13 * v.z,
//                  m.m21 * v.x + m.m22 * v.y + m.m23 * v.z,
//                  m.m31 * v.x + m.m32 * v.y + m.m33 * v.z);
//}

inline Mat44 Inverse(const Mat44 &m) {
  Mat44 inverse(m);
  inverse.Inverse();
  return inverse;
}

}  // namespace wpmath

#endif