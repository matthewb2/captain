/*
 *  Math.h
 *  GLUTApplication
 *
 *  Created by Henry Smith on Sat Nov 29 2003.
 *
 *  Simple 3D math utility functions. Normally I would use a library for this but I wanted to keep things simple and self-contained.
 *
 */

#ifndef MATH_H
#define MATH_H

#include <cmath>
#include <algorithm>
#include "glee.h"

typedef char                sint8;
typedef unsigned char       uint8;
typedef short               sint16;
typedef unsigned short      uint16;
typedef long                sint32;
typedef unsigned long       uint32;

////////////////////////////////////////////////////////////////////////////////
//
//  Point2D
//
////////////////////////////////////////////////////////////////////////////////

struct Point2D
{
    int x;
    int y;

    Point2D () : x(0), y(0) {}
    Point2D (int inX, int inY) : x(inX), y(inY) {}
    
    inline friend Point2D operator + (const Point2D& lhs, const Point2D& rhs);
    inline friend Point2D operator - (const Point2D& lhs, const Point2D& rhs);
};


Point2D
operator + (const Point2D& lhs, const Point2D& rhs) {
    return Point2D( lhs.x + rhs.x, lhs.y + rhs.y );
}

Point2D
operator - (const Point2D& lhs, const Point2D& rhs) {
    return Point2D( lhs.x - rhs.x, lhs.y - rhs.y );
}

////////////////////////////////////////////////////////////////////////////////
//
//  Rect
//
////////////////////////////////////////////////////////////////////////////////

struct Rect
{
    int left;
    int top;
    int right;
    int bottom;

    Rect () : left(0), top(0), right(0), bottom(0) {}
    Rect (int l, int t, int r, int b) : left(l), top(t), right(r), bottom(b) {}
    
    int Width () const { return right - left; }
    int Height () const { return bottom - top; }
    int HalfWidth () const { return Width() / 2; }
    int HalfHeight () const { return Height() / 2; }
    int XMid () const { return left + HalfWidth(); }
    int YMid () const { return top + HalfHeight(); }

    bool Contains (const Point2D& p) const;
    
    Rect Offset (int inX, int inY) const;
};


////////////////////////////////////////////////////////////////////////////////
//
//  Vector3D
//
////////////////////////////////////////////////////////////////////////////////

struct Vector3D
{
    float x;
    float y;
    float z;

    Vector3D () : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3D (float inX, float inY, float inZ) : x(inX), y(inY), z(inZ) {}

    inline float Length () const;
    inline float LengthSquared () const;
    inline Vector3D Normalized () const;
    
    inline Vector3D operator - () const;
    inline void operator += (const Vector3D& v);
    inline void operator -= (const Vector3D& v);
    
    inline friend Vector3D operator * (const Vector3D& v, float s);
    inline friend Vector3D operator * (float s, const Vector3D& v);
    inline friend Vector3D operator / (const Vector3D& v, float s);
    inline friend Vector3D operator + (const Vector3D& lhs, const Vector3D& rhs);
    inline friend Vector3D operator - (const Vector3D& lhs, const Vector3D& rhs);
    
    inline friend Vector3D Midpoint (const Vector3D& a, const Vector3D& b);
    inline friend float Dot (const Vector3D& a, const Vector3D& b);
    inline friend float operator * (const Vector3D& a, const Vector3D& b); // Vector3D * Vector3D --> Synonym for Dot
    friend Vector3D Cross (const Vector3D& a, const Vector3D& b);
    
    // Vector3D constants
    
    static const Vector3D ZERO;
    static const Vector3D X_UNIT;
    static const Vector3D Y_UNIT;
    static const Vector3D Z_UNIT;
};

float
Vector3D::Length () const {
    return sqrt( LengthSquared() );
}

float
Vector3D::LengthSquared () const {
    return (x*x + y*y + z*z);
}

Vector3D
Vector3D::Normalized () const {
    return (*this) / Length();
}

Vector3D
Vector3D::operator - () const {
    return Vector3D( -x, -y, -z );
}

void
Vector3D::operator += (const Vector3D& v) {
    x += v.x;
    y += v.y;
    z += v.z;
}

void
Vector3D::operator -= (const Vector3D& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

Vector3D operator * (const Vector3D& v, float s) {
    return Vector3D( v.x * s, v.y * s, v.z * s );
}

Vector3D operator * (float s, const Vector3D& v) {
    return Vector3D( v.x * s, v.y * s, v.z * s );
}

Vector3D operator / (const Vector3D& v, float s) {
    return Vector3D( v.x / s, v.y / s, v.z / s );
}

Vector3D operator + (const Vector3D& lhs, const Vector3D& rhs) {
    return Vector3D( lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z );
}

Vector3D operator - (const Vector3D& lhs, const Vector3D& rhs) {
    return Vector3D( lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z );
}

Vector3D Midpoint (const Vector3D& a, const Vector3D& b) {
    return Vector3D( (a.x + b.x) * 0.5f, (a.y + b.y) * 0.5f, (a.z + b.z) * 0.5f );
}

float Dot (const Vector3D& a, const Vector3D& b) {
    return (a.x*b.x + a.y*b.y + a.z*b.z);
}

float operator * (const Vector3D& a, const Vector3D& b) {
    return Dot( a, b );
}

//
// OpenGL utitlity functions for Vectors

inline void
glVertex (const Vector3D& v) {
    glVertex3f( v.x, v.y, v.z );
}

inline void
glNormal (const Vector3D& v) {
    glNormal3f( v.x, v.y, v.z );
}

inline void
glTranslate (const Vector3D& v) {
    glTranslatef( v.x, v.y, v.z );
}


////////////////////////////////////////////////////////////////////////////////
//
//  Matrix4D
//
////////////////////////////////////////////////////////////////////////////////

struct Matrix4D
{
    float m[16];
    
    Matrix4D ();

    inline float& At (int i, int j);
    inline const float& At (int i, int j) const;
    
    Vector3D Position () const;
    Vector3D Right () const;
    Vector3D Up () const;
    Vector3D Forward () const;

    Matrix4D Invert () const;
    
    friend Matrix4D operator * (const Matrix4D& m1, const Matrix4D& m2);
    friend Vector3D operator * (const Matrix4D& m, const Vector3D& v);

    // Matrix4D constants
    
    static const Matrix4D IDENTITY;
    
private:
    // Helper functions for Invert
    static void SwapRows (Matrix4D& m, int r1, int r2);
    static void DivideRow (Matrix4D& m, int r, float f);
    static void SubMultRow (Matrix4D& m, int dest, int src, float f);
};


float&
Matrix4D::At (int i, int j) {
    return m[j*4 + i];
}

const float&
Matrix4D::At (int i, int j) const {
    return m[j*4 + i];
}

////////////////////////////////////////////////////////////////////////////////
//
//  Colour
//
////////////////////////////////////////////////////////////////////////////////

struct Colour
{
    GLfloat components[4];

    Colour (GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f) {
        components[0] = r;
        components[1] = g;
        components[2] = b;
        components[3] = a;
    };

    const GLfloat& operator[] (int i) const { return components[i]; }
    GLfloat& operator[] (int i) { return components[i]; }

    GLfloat r () const { return components[0]; }
    GLfloat g () const { return components[1]; }
    GLfloat b () const { return components[2]; }
    GLfloat a () const { return components[2]; }
    
    // Colour constants
    
    static const Colour WHITE;
    static const Colour BLACK;
    static const Colour RED;
    static const Colour GREEN;
    static const Colour BLUE;
};

typedef Colour Color;

inline void
glColor (const Colour& c) {
    glColor4f( c.r(), c.g(), c.b(), c.a() );
}

inline void
glColour (const Colour& c) {
    glColor( c );
}

////////////////////////////////////////////////////////////////////////////////
//
//  Transform
//
////////////////////////////////////////////////////////////////////////////////

class Transform
{
    public:
        Transform ();
        virtual ~Transform ();

        inline Vector3D Position () const;
        inline Vector3D Right () const;
        inline Vector3D Up () const;
        inline Vector3D Forward () const;

        void TranslateLocal (const Vector3D& inDelta);
        void RotateLocal (float inAngle, const Vector3D& inAxis);
        void TranslateGlobal (const Vector3D& inDelta);
        void RotateGlobal (float inAngle, const Vector3D& inAxis);

    public:
        Matrix4D matrix;
};

inline Vector3D
Transform::Position () const {
    return matrix.Position();
}

inline Vector3D
Transform::Right () const {
    return matrix.Right();
}

inline Vector3D
Transform::Up () const {
    return matrix.Up();
}

inline Vector3D
Transform::Forward () const {
    return matrix.Forward();
}

////////////////////////////////////////////////////////////////////////////////
//
//  FloatArray4
//
////////////////////////////////////////////////////////////////////////////////

class FloatArray4
{
    public:
        FloatArray4 (GLfloat f0, GLfloat f1, GLfloat f2, GLfloat f3) {
            array[0] = f0;
            array[1] = f1;
            array[2] = f2;
            array[3] = f3;
        }
        
        operator const GLfloat* () const { return array; }
        
    private:
        GLfloat array[4];
};

inline FloatArray4
MakeFloatArray4 (GLfloat f0, GLfloat f1, GLfloat f2, GLfloat f3) {
    return FloatArray4( f0, f1, f2, f3 );
}

////////////////////////////////////////////////////////////////////////////////
//
//  Clamps a value between a given min and max (inclusive)
//
////////////////////////////////////////////////////////////////////////////////

template< typename T >
T Clamp (const T& inMin, const T& inValue, const T& inMax) {
    return max( inMin, min( inMax, inValue ) );
}

////////////////////////////////////////////////////////////////////////////////
//
//  Rounds a float to the nearest integer value
//
////////////////////////////////////////////////////////////////////////////////

inline int
RoundToNearestInt (float x) {
    return static_cast<int>(floor( x + 0.5f ));
}

#endif
