/*
 *  ExposedParameter.cpp
 *  GLUTApplication
 *
 *  Created by Henry Smith on Thu Jun 10 2004.
 *
 *  A generic parameter that can be drawn on the screen and modified using the mouse.
 *
 */

#include <sstream>
#include "Math.h"
#include "ExposedParameter.h"

////////////////////////////////////////////////////////////////////////////////
//
//  ExposedParameter statics
//
////////////////////////////////////////////////////////////////////////////////

vector<ExposedParameter*> ExposedParameter::s_aParameters;
ExposedParameter* ExposedParameter::s_pActiveParameter = NULL;

void
ExposedParameter::AddParameter (ExposedParameter* p)
{
    static Rect rParameterRect (4, 4, 200, 20);
    
    p->m_rRect = rParameterRect;
    rParameterRect = rParameterRect.Offset( 0, 16 );
    s_aParameters.push_back( p );
}

void
ExposedParameter::DrawParameters ()
{
    GLUTApplication::ScopedScreenProjection ssp;

    for (int i = 0; i < s_aParameters.size(); ++i) {
        s_aParameters[i]->Draw();
    }
}

void
ExposedParameter::MouseDown (int a_nX, int a_nY)
{
    for (int i = 0; i < s_aParameters.size(); ++i) {
        if (s_aParameters[i]->m_rRect.Contains( Point2D( a_nX, a_nY ) ) ) {
            s_pActiveParameter = s_aParameters[i];
        }
    }
}

void
ExposedParameter::MouseUp ()
{
    s_pActiveParameter = NULL;
}

void
ExposedParameter::MouseDrag (int a_nDeltaX, int a_nDeltaY)
{
    if (s_pActiveParameter) {
        s_pActiveParameter->Adjust( a_nDeltaX );
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//  ExposedParameter
//
////////////////////////////////////////////////////////////////////////////////

ExposedParameter::ExposedParameter (const string& a_sName, float& a_fValue, float a_fMin, float a_fMax,
                                    float a_fIncrement, bool a_bShouldMultiply, PostChangeCallback a_fnPostChangeCallback)
    : m_sName(a_sName)
    , m_fValue(a_fValue)
    , m_fMin(a_fMin)
    , m_fMax(a_fMax)
    , m_fIncrement(a_fIncrement)
    , m_bShouldMultiply(a_bShouldMultiply)
    , m_fnPostChangeCallback(a_fnPostChangeCallback)
{
    AddParameter( this );
}

string
ExposedParameter::ToString () const
{
    ostringstream s;
    s << m_sName << " = " << m_fValue;
    return s.str();
}

void
ExposedParameter::Adjust (int a_nDelta)
{
    if (m_bShouldMultiply) {
        if (a_nDelta > 0) {
            m_fValue = Clamp( m_fMin, m_fValue * (a_nDelta * m_fIncrement), m_fMax );
        } else if (a_nDelta < 0) {
            m_fValue = Clamp( m_fMin, m_fValue * (-a_nDelta / m_fIncrement), m_fMax );
        }
    } else {
        m_fValue = Clamp( m_fMin, m_fValue + (a_nDelta * m_fIncrement), m_fMax );
    }
    
    if (m_fnPostChangeCallback) {
        m_fnPostChangeCallback();
    }
}

void
ExposedParameter::Draw () const
{
    if (this == s_pActiveParameter) {
        glColor( Colour::RED );
    } else {
        glColor( Colour::WHITE );
    }
    GLUTApplication::DrawString( ToString(), Point2D( m_rRect.left, m_rRect.top ) );
}
