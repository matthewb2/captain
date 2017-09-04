/*
 *  SpringWater.h
 *  SpringWater
 *
 *  Created by Henry Smith on Mon May 24 2004.
 *
 */

#ifndef SPRING_WATER_H
#define SPRING_WATER_H

#ifdef WIN32
#   include <windows.h>
#endif

#include "GLUTApplication.h"

class SpringWater
    : public GLUTApplication
{
    typedef GLUTApplication Super;

    public:
    
        ////////////////////////////////////////////////////////////////////////////////
        //
        //  Particle
        //
        ////////////////////////////////////////////////////////////////////////////////

        struct Particle
        {
            Vector3D position;
            Vector3D velocity;
            Vector3D acceleration;
            Vector3D forces;
            Vector3D normal;
            Vector3D refractionTexCoords;
            bool fixed;
        };

        ////////////////////////////////////////////////////////////////////////////////
        //
        //  Spring
        //
        ////////////////////////////////////////////////////////////////////////////////

        struct Spring
        {
            Particle* p1;
            Particle* p2;
            float tension;
            float damping;
            float restLength;
            
            void Init (Particle& a_oP1, Particle& a_oP2, float a_fTension);
        };

    public:
        SpringWater ();
        virtual ~SpringWater ();

        void ResetWater ();
        void ResetCamera ();
        static void ResetMesh ();

    protected:
        virtual bool Startup ();
        virtual void Shutdown ();

        virtual void Update (float a_fElapsedTime);
        virtual void Display ();

        virtual void MouseDown (int a_eButton, int a_nX, int a_nY);
        virtual void MouseUp (int a_eButton, int a_nX, int a_nY);
        virtual void MouseDrag (int a_nX, int a_nY);

        virtual void KeyDown (unsigned char a_nKey, int a_nX, int a_nY);

    private:
        void Update ();
        void UpdateForces ();
        void ApplyForces (float a_fElapsedTime);
        void ComputeNormals ();
    
        void DrawWaterMesh () const;
        void DrawWaterMeshWireframe () const;
        void DrawWaterMeshPolys () const;
        void DrawWaterMeshTextured () const;
        
    private:
        Transform m_tCamera;
        float m_fCameraTilt;
        
        bool m_bWireframe;
        bool m_bTextured;
        bool m_bShowParameters;

        Point2D m_ptLastMousePosition;
        bool m_bMouseDown;

        int m_nNumSprings;

        GLuint m_idHelpTextDisplayList;
        GLuint m_idSkyTexture;
        GLuint m_idGroundTexture;
};

#endif