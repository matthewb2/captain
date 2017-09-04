/*
 *  GLUTApplication.h
 *  GLUTApplication
 *
 *  Created by Henry Smith on Thu Nov 13 2003.
 *
 */

#ifndef GLUTAPPLICATION_H
#define GLUTAPPLICATION_H

#include <string>
#include "Math.h"
#include "GLee.h""

#ifdef __APPLE__
#   include <GLUT/glut.h>
#else
#   include <GL/glut.h>
#endif

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//
//  GLUTApplication
//
////////////////////////////////////////////////////////////////////////////////

class GLUTApplication
{
    public:

        ////////////////////////////////////////////////////////////////////////////////
        //
        //  ScopedScreenProjection
        //  Stack-based helper class for drawing in 2D screen coordinates
        //
        ////////////////////////////////////////////////////////////////////////////////

        struct ScopedScreenProjection
        {
            ScopedScreenProjection ();
            ~ScopedScreenProjection ();
        };
        friend struct ScopedScreenProjection;

    public:
        GLUTApplication (const string& a_sName);
        virtual ~GLUTApplication ();

        void Run ();

        int GetWindowWidth () const { return m_nWindowWidth; }
        int GetWindowHeight () const { return m_nWindowHeight; }

        // Utility functions
        static void DrawString (const string& a_sString, const Point2D& a_ptPos);
        static void GetPlaneCoefficients (const Vector3D& v1, const Vector3D& v2, const Vector3D& v3, float out_aCoeff[4]);

    protected:
        virtual void CreateGLWindow ();
        virtual void InitGL ();
        
        virtual bool Startup ();
        virtual void Shutdown ();
        
        // GLUT callbacks for subclasses to override

        virtual void Update (float a_fElapsedTime);
        virtual void Display ();
        virtual void Visible (int a_nState);
        virtual void Reshape (int a_nWidth, int a_nHeight);

        virtual void MouseDown (int a_eButton, int a_nX, int a_nY);
        virtual void MouseUp (int a_eButton, int a_nX, int a_nY);
        virtual void MouseDrag (int a_nX, int a_nY);
        virtual void MouseMove (int a_nX, int a_nY);

        virtual void KeyDown (unsigned char a_nKey, int a_nX, int a_nY);
        virtual void KeyUp (unsigned char a_nKey, int a_nX, int a_nY);

        // Utility functions

        void CalculateFrustumPlanes (float out_aPlanes[6][4] = NULL);
        bool IsPointInFrustum (const Vector3D& a_vPoint, float a_fTolerance) const;

        Vector3D WorldToWindowSpace (const Vector3D& a_vPos) const;
        Vector3D WindowToWorldSpace (const Point2D& a_ptPixel, float a_fZ = -1.0f) const;
        
        GLuint LoadTextureRAW (const string& a_sFilename) const;

    protected:
        Vector3D m_aFrustumCorners[8];
        float m_aFrustumPlanes[6][4];

        // Stub callbacks that forward the call on to the application instance
        static GLUTApplication* s_pApplicationInstance;

    protected:
        // Key map holding 'down' values for each ASCII keycode
        static bool s_aKeyMap[256];

    private:
        void RegisterCallbacks ();

    private:
        const string m_sApplicationName;
        int m_nWindowWidth;
        int m_nWindowHeight;
        int m_nUpdatesPerSecond;
        bool m_bVisible;

        static int s_nLastFrameTime;

        static inline void DisplayCallback ();
        static inline void ReshapeCallback (int a_nWidth, int a_nHeight);
        static inline void MouseCallback (int a_eButton, int a_nState, int a_nX, int a_nY);
        static inline void MotionCallback (int a_nX, int a_nY);
        static inline void PassiveMotionCallback (int a_nX, int a_nY);
        static inline void KeyDownCallback (unsigned char a_nKey, int a_nX, int a_nY);
        static inline void KeyUpCallback (unsigned char a_nKey, int a_nX, int a_nY);
        static void UpdateCallback (int a_nValue);
        static inline void VisibleCallback (int a_nState);
};

////////////////////////////////////////////////////////////////////////////////

inline void
GLUTApplication::DisplayCallback () {
    s_pApplicationInstance->Display();
}

inline void
GLUTApplication::ReshapeCallback (int a_nWidth, int a_nHeight) {
    s_pApplicationInstance->Reshape( a_nWidth, a_nHeight );
}

inline void
GLUTApplication::MouseCallback (int a_eButton, int a_nState, int a_nX, int a_nY) {
    (a_nState == GLUT_DOWN) ?
        s_pApplicationInstance->MouseDown( a_eButton, a_nX, a_nY ) :
        s_pApplicationInstance->MouseUp( a_eButton, a_nX, a_nY );
}

inline void
GLUTApplication::MotionCallback (int a_nX, int a_nY) {
    s_pApplicationInstance->MouseDrag( a_nX, a_nY );
}

inline void
GLUTApplication::PassiveMotionCallback (int a_nX, int a_nY) {
    s_pApplicationInstance->MouseMove( a_nX, a_nY );
}

inline void
GLUTApplication::KeyDownCallback (unsigned char a_nKey, int a_nX, int a_nY) {
    s_aKeyMap[a_nKey] = true;
    s_pApplicationInstance->KeyDown( a_nKey, a_nX, a_nY );
}

inline void
GLUTApplication::KeyUpCallback (unsigned char a_nKey, int a_nX, int a_nY) {
    s_aKeyMap[a_nKey] = false;
    s_pApplicationInstance->KeyUp( a_nKey, a_nX, a_nY );
}

inline void
GLUTApplication::VisibleCallback (int a_nState) {
    s_pApplicationInstance->Visible( a_nState );
}

#endif
