/*
 *  GLUTApplication.cpp
 *  GLUTApplication
 *
 *  Created by Henry Smith on Thu Nov 13 2003.
 *
 */

#include "GLUTApplication.h"
#include <cassert>
#include <iostream>
#include <fstream>

////////////////////////////////////////////////////////////////////////////////
//
//  ScopedScreenProjection
//
////////////////////////////////////////////////////////////////////////////////

GLUTApplication::ScopedScreenProjection::ScopedScreenProjection ()
{
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    
        glLoadIdentity();
        glOrtho( 0.0, s_pApplicationInstance->GetWindowWidth(), 0.0, s_pApplicationInstance->GetWindowHeight(), -0.1, 0.1 );

        glMatrixMode( GL_MODELVIEW );
        glPushMatrix();
        glLoadIdentity();
}

GLUTApplication::ScopedScreenProjection::~ScopedScreenProjection ()
{
        glMatrixMode( GL_MODELVIEW );
        glPopMatrix();

    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
}

////////////////////////////////////////////////////////////////////////////////
//
//  GLUTApplication
//
////////////////////////////////////////////////////////////////////////////////

GLUTApplication* GLUTApplication::s_pApplicationInstance = NULL;
bool GLUTApplication::s_aKeyMap[256];
int GLUTApplication::s_nLastFrameTime = 0;

GLUTApplication::GLUTApplication (const string& a_sName)
    : m_sApplicationName( a_sName )
    , m_nWindowWidth( 640 )
    , m_nWindowHeight( 480 )
    , m_nUpdatesPerSecond( 60 )
    , m_bVisible( true )
{
    for (int k = 0; k < 256; ++k) {
        s_aKeyMap[k] = false;
    }

    if (s_pApplicationInstance == NULL) {
        s_pApplicationInstance = this;
    } else {
        assert(false);
    }
}

GLUTApplication::~GLUTApplication ()
{
}

void
GLUTApplication::Run()
{
    CreateGLWindow();
    InitGL();
    RegisterCallbacks();
    
    if (Startup())
    {
        glutMainLoop();
    }
    Shutdown();
}

void
GLUTApplication::CreateGLWindow ()
{
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize( m_nWindowWidth, m_nWindowHeight );
    glutInitWindowPosition( 100, 100 );
    glutCreateWindow( m_sApplicationName.c_str() );
}

void
GLUTApplication::InitGL ()
{
    glShadeModel( GL_SMOOTH );
    glPolygonMode( GL_FRONT, GL_FILL );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glEnable( GL_DEPTH_TEST );
}

void
GLUTApplication::RegisterCallbacks ()
{
    glutDisplayFunc( &DisplayCallback );
    glutReshapeFunc( &ReshapeCallback );
    glutMouseFunc( &MouseCallback );
    glutMotionFunc( &MotionCallback );
    glutPassiveMotionFunc( &PassiveMotionCallback );
    glutKeyboardFunc( &KeyDownCallback );
    glutKeyboardUpFunc( &KeyUpCallback );
    glutVisibilityFunc( &VisibleCallback );
    glutTimerFunc( 1000 / m_nUpdatesPerSecond, UpdateCallback, 0 );
}

bool
GLUTApplication::Startup ()
{
    return true;
}

void
GLUTApplication::Shutdown ()
{
}

////////////////////////////////////////////////////////////////////////////////
//
//  Default callbacks
//
////////////////////////////////////////////////////////////////////////////////

void
GLUTApplication::UpdateCallback (int a_nValue)
{
    if (s_nLastFrameTime == 0) {
        s_nLastFrameTime = glutGet( GLUT_ELAPSED_TIME );
    }

    int nNow = glutGet( GLUT_ELAPSED_TIME );
    float fElapsedTime = (nNow - s_nLastFrameTime) / 1000.0f;
    s_nLastFrameTime = nNow;

    if (s_pApplicationInstance->m_bVisible) {
        s_pApplicationInstance->Update( fElapsedTime );
    }
    
    // Reactivate update timer
    glutTimerFunc( 1000 / s_pApplicationInstance->m_nUpdatesPerSecond, UpdateCallback, 0 );
}

void
GLUTApplication::Update (float a_fElapsedTime)
{
}

void
GLUTApplication::Display ()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glutSwapBuffers();
}

void
GLUTApplication::Visible (int a_nState)
{
    if (a_nState == GLUT_VISIBLE) {
        m_bVisible = true;
    } else {
        m_bVisible = false;
    }
}

void
GLUTApplication::Reshape (int a_nWidth, int a_nHeight)
{
    m_nWindowWidth = a_nWidth;
    m_nWindowHeight = a_nHeight;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glViewport( 0, 0, a_nWidth, a_nHeight );
    gluPerspective( 60.0, (GLfloat) a_nWidth / (GLfloat) a_nHeight, 0.01, 1000.0 );
    glMatrixMode( GL_MODELVIEW );
}

void
GLUTApplication::MouseDown (int a_eButton, int a_nX, int a_nY)
{
    // Subclass should override...
}

void
GLUTApplication::MouseUp (int a_eButton, int a_nX, int a_nY)
{
    // Subclass should override...
}

void
GLUTApplication::MouseMove (int a_nX, int a_nY)
{
    // Subclass should override...
}

void
GLUTApplication::MouseDrag (int a_nX, int a_nY)
{
    // Subclass should override...
}

void
GLUTApplication::KeyDown (unsigned char a_nKey, int a_nX, int a_nY)
{
    // Subclass should override...
}

void
GLUTApplication::KeyUp (unsigned char a_nKey, int a_nX, int a_nY)
{
    // Subclass should override...
}


////////////////////////////////////////////////////////////////////////////////

void
GLUTApplication::DrawString (const string& a_sString, const Point2D& a_ptPos)
{
    GLboolean bLightingEnabled;
    glGetBooleanv( GL_LIGHTING, &bLightingEnabled );
    glDisable( GL_LIGHTING );

    glRasterPos2i( a_ptPos.x, a_ptPos.y );
    for (int i = 0; i < a_sString.size(); ++i) {
        glutBitmapCharacter( GLUT_BITMAP_9_BY_15, a_sString[i] );
    }

    if (bLightingEnabled) {
        glEnable( GL_LIGHTING );
    }
}

void
GLUTApplication::GetPlaneCoefficients (const Vector3D& v1, const Vector3D& v2, const Vector3D& v3, float out_aCoeff[4])
{
    Vector3D n = Cross( v3 - v1, v2 - v1 ).Normalized();

    out_aCoeff[0] = n.x;
    out_aCoeff[1] = n.y;
    out_aCoeff[2] = n.z;
    out_aCoeff[3] = -Dot( n, v1 );
}

void
GLUTApplication::CalculateFrustumPlanes (float out_aPlanes[6][4])
{
    if (out_aPlanes == NULL) {
        out_aPlanes = m_aFrustumPlanes;
    }

    GLint aViewport[4];
    glGetIntegerv( GL_VIEWPORT, aViewport );
    GLdouble aModelview[16];
    glGetDoublev( GL_MODELVIEW_MATRIX, aModelview );
    GLdouble aProjection[16];
    glGetDoublev( GL_PROJECTION_MATRIX, aProjection );

    // Unproject the 8 frustum corners
    for (int i = 0; i < 8; ++i)
    {
        GLdouble p[3];
        gluUnProject(
            (i & 1) ? m_nWindowWidth : 0.0f,
            (i & 2) ? m_nWindowHeight : 0.0f,
            (i & 4) ? 0.0f : 1.0f,
            aModelview, aProjection, aViewport,
            &p[0], &p[1], &p[2]
        );
        m_aFrustumCorners[i].x = p[0];
        m_aFrustumCorners[i].y = p[1];
        m_aFrustumCorners[i].z = p[2];
    }
    
    // Calculate the coefficients
    GetPlaneCoefficients( m_aFrustumCorners[0], m_aFrustumCorners[1], m_aFrustumCorners[2], out_aPlanes[0] ); // far
    GetPlaneCoefficients( m_aFrustumCorners[0], m_aFrustumCorners[2], m_aFrustumCorners[4], out_aPlanes[1] ); // left
    GetPlaneCoefficients( m_aFrustumCorners[0], m_aFrustumCorners[4], m_aFrustumCorners[1], out_aPlanes[2] ); // bottom
    GetPlaneCoefficients( m_aFrustumCorners[7], m_aFrustumCorners[5], m_aFrustumCorners[6], out_aPlanes[3] ); // near
    GetPlaneCoefficients( m_aFrustumCorners[7], m_aFrustumCorners[3], m_aFrustumCorners[5], out_aPlanes[4] ); // right
    GetPlaneCoefficients( m_aFrustumCorners[7], m_aFrustumCorners[6], m_aFrustumCorners[3], out_aPlanes[5] ); // top
}

bool
GLUTApplication::IsPointInFrustum (const Vector3D& a_vPoint, float a_vTolerance) const
{
    for (int p = 0; p < 6; ++p) {

        float d = m_aFrustumPlanes[p][0] * a_vPoint.x +
                  m_aFrustumPlanes[p][1] * a_vPoint.y +
                  m_aFrustumPlanes[p][2] * a_vPoint.z + 
                  m_aFrustumPlanes[p][3];

        if (d*d > a_vTolerance) {
            if (d > 0.0f) {
                return false;
            }
        }
    } 
    return true;
}

Vector3D
GLUTApplication::WindowToWorldSpace (const Point2D& a_ptPixel, float a_fZ) const
{
    GLint aViewport[4];
    glGetIntegerv( GL_VIEWPORT, aViewport );
    GLdouble aModelview[16];
    glGetDoublev( GL_MODELVIEW_MATRIX, aModelview );
    GLdouble aProjection[16];
    glGetDoublev( GL_PROJECTION_MATRIX, aProjection );

    GLfloat z;
    if (a_fZ != -1.0f) {
        z = a_fZ;
    } else {
        glReadPixels( a_ptPixel.x, GetWindowHeight() - a_ptPixel.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z );
    }

    GLdouble p[3];
    gluUnProject(
        a_ptPixel.x,
        GetWindowHeight() - a_ptPixel.y,
        z,
        aModelview, aProjection, aViewport,
        &p[0], &p[1], &p[2]
    );

    return Vector3D( p[0], p[1], p[2] );
}

Vector3D
GLUTApplication::WorldToWindowSpace (const Vector3D& a_vPos) const
{
    GLint aViewport[4];
    glGetIntegerv( GL_VIEWPORT, aViewport );
    GLdouble aModelview[16];
    glGetDoublev( GL_MODELVIEW_MATRIX, aModelview );
    GLdouble aProjection[16];
    glGetDoublev( GL_PROJECTION_MATRIX, aProjection );

    GLdouble p[3];
    gluProject(
        a_vPos.x,
        a_vPos.y,
        a_vPos.z,
        aModelview, aProjection, aViewport,
        &p[0], &p[1], &p[2]
    );

    return Vector3D( p[0], p[1], p[2] );
}


GLuint
GLUTApplication::LoadTextureRAW (const string& a_sFilename) const
{
    GLuint nTextureID = 0;

    // Attempt to open file
    ifstream file (a_sFilename.c_str(), ios::binary);
    if (!file) {
        cerr << "Error loading texture " << a_sFilename << "\n";
    }
    else
    {
        // Get file size
        file.seekg( 0, ios::end );
        int nFileSize = file.tellg();
        file.seekg( 0, ios::beg );

        // Guess the texture depth and dimensions
        int nTextureSize;
        GLenum eFormat;
        double fIgnored;

        float fSizeIfRGB = sqrt( (float) nFileSize / 3 );
        float fSizeIfRGBA = sqrt( (float) nFileSize / 4 );
        
        if (modf( fSizeIfRGB, &fIgnored ) == 0.0f) {
            nTextureSize = (int) fSizeIfRGB;
            eFormat = GL_RGB;
        } else if (modf( fSizeIfRGBA, &fIgnored ) == 0.0f) {
            nTextureSize = (int) fSizeIfRGBA;
            eFormat = GL_RGBA;
        } else {
            cerr << "Texture " << a_sFilename << " does not appear to be a square raw RGB or RGBA file.\n";
            return 0;
        }
        
        // Read the texture data
        char* aTextureData = new char [nFileSize];
        file.read( aTextureData, nFileSize );

        // Bind it to an OpenGL texture
        glGenTextures( 1, &nTextureID );
        glBindTexture( GL_TEXTURE_2D, nTextureID );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, nTextureSize, nTextureSize, 0, eFormat, GL_UNSIGNED_BYTE, aTextureData );
        glBindTexture( GL_TEXTURE_2D, 0 );

        // Clean up
        delete [] aTextureData;
        file.close();
    }
    return nTextureID;
}
