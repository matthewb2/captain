/*
 *  ExposedParameter.h
 *  GLUTApplication
 *
 *  Created by Henry Smith on Thu Jun 10 2004.
 * 
 *  A generic parameter that can be drawn on the screen and modified using the mouse.
 *
 */

#ifndef EXPOSED_PARAMETER_H
#define EXPOSED_PARAMETER_H

#include "GLUTApplication.h"
#include <vector>
#include <string>

////////////////////////////////////////////////////////////////////////////////
//
//  ExposedParameter
//
////////////////////////////////////////////////////////////////////////////////

class ExposedParameter
{
    public:
        typedef void (*PostChangeCallback) ();

        // Static parameter list
        
        static vector<ExposedParameter*> s_aParameters;
        static ExposedParameter* s_pActiveParameter; // Parameter currently being modified

        static void AddParameter (ExposedParameter* p);
        static void DrawParameters ();
        static void MouseDown (int a_nX, int a_nY);
        static void MouseUp ();
        static void MouseDrag (int a_nX, int a_nY);

    public:
        ExposedParameter (
            const string& a_sName,
            float& a_fValue,
            float a_fMin,
            float a_fMax,
            float a_fIncrement,
            bool a_bShouldMultiply = false,
            PostChangeCallback a_fnPostChangeCallback = NULL
        );

        string ToString () const;
        void Adjust (int a_nDelta);
        void Draw () const;

    private:
        string m_sName;
        float& m_fValue;
        float m_fMin;
        float m_fMax;
        float m_fIncrement;
        bool m_bShouldMultiply;
        Rect m_rRect;
        PostChangeCallback m_fnPostChangeCallback;
};

#endif
