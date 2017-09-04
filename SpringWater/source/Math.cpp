/*
 *  Math.cpp
 *  GLUTApplication
 *
 *  Created by Henry Smith on Sat Nov 29 2003.
 *
 *  Simple 3D math utility functions. Normally I would use a library for this but I wanted to keep things simple and self-contained.
 *
 */

#include "Math.h"

////////////////////////////////////////////////////////////////////////////////
//
//  Constants
//
////////////////////////////////////////////////////////////////////////////////

const Vector3D Vector3D::ZERO   (0.0f, 0.0f, 0.0f);
const Vector3D Vector3D::X_UNIT (1.0f, 0.0f, 0.0f);
const Vector3D Vector3D::Y_UNIT (0.0f, 1.0f, 0.0f);
const Vector3D Vector3D::Z_UNIT (0.0f, 0.0f, 1.0f);

const Matrix4D Matrix4D::IDENTITY;

const Colour Colour::WHITE  ( 1.0f, 1.0f, 1.0f, 1.0f );
const Colour Colour::BLACK  ( 0.0f, 0.0f, 0.0f, 1.0f );
const Colour Colour::RED    ( 1.0f, 0.0f, 0.0f, 1.0f );
const Colour Colour::GREEN  ( 0.0f, 1.0f, 0.0f, 1.0f );
const Colour Colour::BLUE   ( 0.0f, 0.0f, 1.0f, 1.0f );

////////////////////////////////////////////////////////////////////////////////
//
//  Rect functions
//
////////////////////////////////////////////////////////////////////////////////

bool
Rect::Contains (const Point2D& p) const
{
    return (p.x > left && p.x < right && p.y > top && p.y < bottom);
}

Rect
Rect::Offset (int inX, int inY) const
{
    return Rect(
        left + inX,
        top + inY,
        right + inX,
        bottom + inY
    );
}

////////////////////////////////////////////////////////////////////////////////
//
//  Vector3D functions
//
////////////////////////////////////////////////////////////////////////////////

Vector3D Cross (const Vector3D& a, const Vector3D& b)
{
    return Vector3D(
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    );
}

////////////////////////////////////////////////////////////////////////////////
//
//  Matrix4D functions
//
////////////////////////////////////////////////////////////////////////////////

Matrix4D::Matrix4D ()
{
    // Set to identity
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            At(i, j) = (i == j) ? 1.0f : 0.0f;
        }
    }
}

Vector3D
Matrix4D::Position () const
{
    return Vector3D( At(0, 3), At(1, 3), At(2, 3) );
}

Vector3D
Matrix4D::Right () const
{
    return Vector3D( At(0, 0), At(0, 1), At(0, 2) );
}

Vector3D
Matrix4D::Up () const
{
    return Vector3D( At(1, 0), At(1, 1), At(1, 2) );
}

Vector3D
Matrix4D::Forward () const
{
    return Vector3D( At(2, 0), At(2, 1), At(2, 2) );
}

void
Matrix4D::SwapRows (Matrix4D& m, int r1, int r2)
{
    for (int c = 0; c < 4; ++c) {
        std::swap( m.At(r1, c), m.At(r2, c) );
    }
}

void
Matrix4D::DivideRow (Matrix4D& m, int r, float f)
{
    for (int c = 0; c < 4; ++c) {
        m.At(r, c) /= f;
    }
}

void
Matrix4D::SubMultRow (Matrix4D& m, int dest, int src, float f)
{
    for (int c = 0; c < 4; ++c) {
        m.At(dest, c) -= f * m.At(src, c);
    }
}

Matrix4D
Matrix4D::Invert () const
{
    // Use Gauss-Jordan elimination to find the inverse

    Matrix4D m (*this);
    Matrix4D result;

    // For each column...
    for (int j = 0; j < 4; ++j)
    {
        // Find largest pivot
        int pivot = j;
        for (int i = j + 1; i < 4; ++i) {
            if (fabs( m.At(i, j) ) > fabs( m.At(pivot, j) )) {
                pivot = i;
            }
        }

        // Swap pivot row to put it on the diagonal
        SwapRows( m, pivot, j );
        SwapRows( result, pivot, j );

        // Scale row j to have a unit diagonal
        if (m.At(j, j) == 0.0)
        {
            // Singular matrix!
            return result;
        }

        DivideRow( result, j, m.At(j, j) );
        DivideRow( m, j, m.At(j, j) );

        // Eliminate off-diagonal elements in column j
        for (int i = 0; i < 4; ++i)
        {
            if (i != j)
            {
                SubMultRow( result, i, j, m.At(i, j) );
                SubMultRow( m, i, j, m.At(i, j) );
            }
        }
    }
    
    return result;
}

Matrix4D
operator * (const Matrix4D& m1, const Matrix4D& m2)
{
    Matrix4D result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.At(i, j) =
                m1.At(i, 0) * m2.At(0, j) +
                m1.At(i, 1) * m2.At(1, j) +
                m1.At(i, 2) * m2.At(2, j) +
                m1.At(i, 3) * m2.At(3, j);
        }
    }
    return result;
}

Vector3D
operator * (const Matrix4D& m, const Vector3D& v)
{
    // Right-multiply the vector
    return Vector3D(
        m.At(0, 0) * v.x + m.At(0, 1) * v.y + m.At(0, 2) * v.z,
        m.At(1, 0) * v.x + m.At(1, 1) * v.y + m.At(1, 2) * v.z,
        m.At(2, 0) * v.x + m.At(2, 1) * v.y + m.At(2, 2) * v.z
    );
}

////////////////////////////////////////////////////////////////////////////////
//
//  Transform functions
//
////////////////////////////////////////////////////////////////////////////////

Transform::Transform ()
{
}

Transform::~Transform ()
{
}

void
Transform::TranslateLocal (const Vector3D& inDelta)
{
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
        glLoadMatrixf( (float*) matrix.m );
        glTranslatef( inDelta.x, inDelta.y, inDelta.z );
        glGetFloatv( GL_MODELVIEW_MATRIX, (float*) matrix.m );
    glPopMatrix();
}

void
Transform::RotateLocal (float inAngle, const Vector3D& inAxis)
{
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
        glLoadMatrixf( (float*) matrix.m );
        glRotatef( inAngle, inAxis.x, inAxis.y, inAxis.z );
        glGetFloatv( GL_MODELVIEW_MATRIX, (float*) matrix.m );
    glPopMatrix();
}

void
Transform::TranslateGlobal (const Vector3D& inDelta)
{
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
        glLoadIdentity();
        glTranslatef( inDelta.x, inDelta.y, inDelta.z );
        glMultMatrixf( (float*) matrix.m );
        glGetFloatv( GL_MODELVIEW_MATRIX, (float*) matrix.m );
    glPopMatrix();
}

void
Transform::RotateGlobal (float inAngle, const Vector3D& inAxis)
{
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
        glLoadIdentity();
        glRotatef( inAngle, inAxis.x, inAxis.y, inAxis.z );
        glMultMatrixf( (float*) matrix.m );
        glGetFloatv( GL_MODELVIEW_MATRIX, (float*) matrix.m );
    glPopMatrix();
}

