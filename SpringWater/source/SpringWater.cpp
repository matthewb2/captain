/*
 *  SpringWater.cpp
 *  SpringWater
 *
 *  Created by Henry Smith on Mon May 24 2004.
 *
 */

#include <iostream>
#include "Math.h"
#include "ExposedParameter.h"
#include "SpringWater.h"

////////////////////////////////////////////////////////////////////////////////
//
//  Globals
//
////////////////////////////////////////////////////////////////////////////////

const int MAX_MESH_SIZE         = 50;
const int MAX_SPRINGS           = ((MAX_MESH_SIZE+1) * MAX_MESH_SIZE * 2) // Horizontal and vertical
                                + ((MAX_MESH_SIZE * MAX_MESH_SIZE) * 2); // Diagonal
const float GROUND_DISTANCE     = 20.0f;
const float FIXED_FPS           = 60.0f;
const bool CROSS_SPRINGS        = true;
const bool DIAGONAL_SPRINGS     = true;

float MESH_SIZE                 = 30;

float SPRING_TENSION            = 500.0f;
float SHEAR_TENSION             = 300.0f;
float SPRING_DAMPING            = 2.0f;
float GROUND_TENSION            = 100.0f;
float GROUND_DAMPING            = 0.5f;
float GRAVITY                   = 0.0f;
float SPLASH_FORCE              = 6.0f;

float WATER_DEPTH               = 1.0f;
float REFRACTION_FACTOR         = 0.2f;

SpringWater::Particle s_aParticles [MAX_MESH_SIZE+1][MAX_MESH_SIZE+1];
SpringWater::Spring s_aSprings [MAX_SPRINGS];

////////////////////////////////////////////////////////////////////////////////
//
//  Spring functions
//
////////////////////////////////////////////////////////////////////////////////

void
SpringWater::Spring::Init (Particle& a_oP1, Particle& a_oP2, float a_fTension = SPRING_TENSION)
{
    p1 = &a_oP1;
    p2 = &a_oP2;
    tension = a_fTension;
    damping = SPRING_DAMPING;
    restLength = (a_oP2.position - a_oP1.position).Length();
}

////////////////////////////////////////////////////////////////////////////////
//
//  SpringWater functions
//
////////////////////////////////////////////////////////////////////////////////

SpringWater::SpringWater ()
    : GLUTApplication( "SpringWater" )
    , m_fCameraTilt( -25.0f )
    , m_bWireframe( false )
    , m_bTextured( true )
    , m_bShowParameters( false )
    , m_ptLastMousePosition( 0, 0 )
    , m_bMouseDown( false )
    , m_nNumSprings( 0 )
    , m_idHelpTextDisplayList( 0 )
    , m_idSkyTexture( 0 )
    , m_idGroundTexture( 0 )
{
}

SpringWater::~SpringWater ()
{
}

bool
SpringWater::Startup ()
{
    // Expose parameters
    static ExposedParameter aParams [] =
    {
        ExposedParameter( "Mesh size",          MESH_SIZE,          1.0f, (float) MAX_MESH_SIZE, 1.0f, false, SpringWater::ResetMesh ),
        ExposedParameter( "Spring tension",     SPRING_TENSION,     0.0f, 2000.0f, 10.0f ),
        ExposedParameter( "Shear tension",      SHEAR_TENSION,      0.0f, 2000.0f, 10.0f ),
        ExposedParameter( "Spring damping",     SPRING_DAMPING,     0.0f, 10.0f, 0.5f ),
        ExposedParameter( "Ground tension",     GROUND_TENSION,     0.0f, 1000.0f, 10.0f ),
        ExposedParameter( "Ground damping",     GROUND_DAMPING,     0.0f, 10.0f, 0.5f ),
        ExposedParameter( "Gravity",            GRAVITY,            0.0f, 20.0f, 0.5f ),
        ExposedParameter( "Splash force",       SPLASH_FORCE,       1.0f, 20.0f, 1.0f ),
        ExposedParameter( "Water depth",        WATER_DEPTH,        -10.0f, 10.0f, 1.0f ),
        ExposedParameter( "Refraction factor",  REFRACTION_FACTOR,  0.0f, 2.0f, 0.01f )
    };

    // Load extensions
	/*
    if (!GLEE_ARB_multitexture) {
        cerr << "OpenGL implementation doesn't support multitexture!" << endl;
        return false;
    }
	*/
    
    // Load textures
    m_idGroundTexture = LoadTextureRAW( "ground.raw" );
    if (m_idGroundTexture == 0) {
        cerr << "Ground texture could not be loaded!" << endl;
        return false;
    }
    
    m_idSkyTexture = LoadTextureRAW( "sky.raw" );
    if (m_idSkyTexture == 0) {
        cerr << "Sky texture could not be loaded!" << endl;
        return false;
    }

    // Enable lighting
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glLightfv( GL_LIGHT0, GL_POSITION, MakeFloatArray4( 1.0, -1.0, -1.0, 0.0 ) );
    glMaterialfv( GL_FRONT, GL_AMBIENT, MakeFloatArray4( 0.5, 0.5, 0.5, 1.0 ) );
    glMaterialfv( GL_FRONT, GL_DIFFUSE, MakeFloatArray4( 1.0, 1.0, 1.0, 1.0 ) );
    glMaterialfv( GL_FRONT, GL_SPECULAR, MakeFloatArray4( 1.0, 1.0, 1.0, 1.0 ) );
    glMaterialf( GL_FRONT, GL_SHININESS, 100.0 );
    
    // Create display lists
    m_idHelpTextDisplayList = glGenLists( 1 );
    glNewList( m_idHelpTextDisplayList, GL_COMPILE );
    {
        ScopedScreenProjection ssp;
        glColor( Colour::WHITE );
        Point2D p ( 4, GetWindowHeight() - 20 );

        DrawString( "Click & drag the mouse over the water", p ); p.y -= 20;
        DrawString( "Press 'w' to toggle wireframe", p ); p.y -= 20;
        DrawString( "Press 'r' to reset", p );
    }
    glEndList();
    
    ResetWater();
    ResetCamera();
    
    return true;
}

void
SpringWater::Shutdown ()
{
}

void
SpringWater::Update (float a_fElapsedTime)
{
    // Unlock all particles
    for (int r = 0; r <= MESH_SIZE; ++r) {
        for (int c = 0; c <= MESH_SIZE; ++c) {
            s_aParticles[r][c].fixed = false;
        }
    }

    // Splash!
    if (m_bMouseDown)
    {
        // Project mouse position onto mesh plane

        glMatrixMode( GL_MODELVIEW );
        glPushMatrix();
            glLoadIdentity();
            glMultMatrixf( (float*) m_tCamera.matrix.Invert().m );
            Vector3D vMousePos = WindowToWorldSpace( m_ptLastMousePosition, 0.99f );
        glPopMatrix();

        Vector3D vDirection = vMousePos - m_tCamera.Position();
        float fDistance = ((0.0f - m_tCamera.Position().y) / vDirection.y);
        Vector3D vHit = m_tCamera.Position() + (vDirection * fDistance);
    
        // Find closest particle

        Point2D ptClosest (RoundToNearestInt( vHit.x ), RoundToNearestInt( vHit.z ));
        if (ptClosest.x > 0 && ptClosest.x <= MESH_SIZE &&
            ptClosest.y > 0 && ptClosest.y <= MESH_SIZE )
        {
            // Change particle Y coordinate

            float fRowWeight = 1.0f - fabs( vHit.z - ptClosest.y );
            float fColWeight = 1.0f - fabs( vHit.x - ptClosest.x );

            s_aParticles[ptClosest.y][ptClosest.x].position.y = -SPLASH_FORCE * fRowWeight * fColWeight;
            s_aParticles[ptClosest.y][ptClosest.x].fixed = true;
        }
    }

    // Update particles
    UpdateForces();
    ApplyForces( a_fElapsedTime );
    ComputeNormals();

    glutPostRedisplay();
}

void
SpringWater::UpdateForces ()
{
    Vector3D vSpring;
    Vector3D vSpringDirection;
    Vector3D dv;
    Vector3D f1, f2;
    Particle ground;
    int r, c;

    // Zero forces
    for (r = 0; r <= MESH_SIZE; ++r) {
        for (c = 0; c <= MESH_SIZE; ++c) {
            s_aParticles[r][c].forces = Vector3D::ZERO;
        }
    }

    // Compute gravity force
    if (GRAVITY > 0.0f)
    {
        for (r = 0; r <= MESH_SIZE; ++r) {
            for (c = 0; c <= MESH_SIZE; ++c)
            {
                Particle& p1 = s_aParticles[r][c];

                if (p1.position.y > 0.0f) {
                    p1.forces.y += -GRAVITY;
                }
            }
        }
    }
    
    // Compute ground spring forces
    for (r = 0; r <= MESH_SIZE; ++r) {
        for (c = 0; c <= MESH_SIZE; ++c)
        {
            Particle& p1 = s_aParticles[r][c];

            ground = p1;
            ground.position.y = -GROUND_DISTANCE;
            
            vSpring = p1.position - ground.position;
            dv = p1.velocity;

            float fForce = (
                GROUND_TENSION * (vSpring.Length() - GROUND_DISTANCE) +
                GROUND_DAMPING * (Dot( dv, vSpring ) / vSpring.Length())
            );

            f1 = -fForce * vSpring.Normalized();

            p1.forces.y += f1.y;
        }
    }

    // Compute surface spring forces
    for (int i = 0; i < m_nNumSprings; ++i)
    {
        Spring& s = s_aSprings[i];
        Particle& p1 = *s.p1;
        Particle& p2 = *s.p2;
        
        vSpring = p1.position - p2.position;
        dv = p1.velocity - p2.velocity;

        float fForce = (
            s.tension * (vSpring.Length() - s.restLength) +
            s.damping * (Dot( dv, vSpring ) / vSpring.Length())
        );
        
        f1 = -fForce * vSpring.Normalized();
        f2 = -f1;
        
        p1.forces.y += f1.y;
        p2.forces.y += f2.y;
    }
}

void
SpringWater::ApplyForces (float a_fElapsedTime)
{
    // Fixed update rate
    if (FIXED_FPS > 0) {
        a_fElapsedTime = 1.0f / FIXED_FPS;
    }

    for (int r = 0; r <= MESH_SIZE; ++r) {
        for (int c = 0; c <= MESH_SIZE; ++c)
        {
            Particle& p = s_aParticles[r][c];

            if (!p.fixed)
            {
                p.acceleration = p.forces; // a = F/m (all my particles have mass = 1)
                p.velocity += p.acceleration * a_fElapsedTime;
                p.position += p.velocity * a_fElapsedTime;
            }
        }
    }
}

void
SpringWater::ComputeNormals ()
{
    static Vector3D s_aFaceNormals [MAX_MESH_SIZE][MAX_MESH_SIZE];
    int r, c;

    // Compute face normals
    for (r = 0; r < MESH_SIZE; ++r) {
        for (c = 0; c < MESH_SIZE; ++c)
        {
            const Vector3D& v0 = s_aParticles[r][c].position;
            const Vector3D& v1 = s_aParticles[r][c+1].position;
            const Vector3D& v2 = s_aParticles[r+1][c].position;
        
            s_aFaceNormals[r][c] = Cross( v1 - v0, v2 - v0 ).Normalized();
        }
    }

    // Compute vertex normals
    Vector3D vVertexNormal;
    for (r = 0; r <= MESH_SIZE; ++r) {
        for (c = 0; c <= MESH_SIZE; ++c)
        {
            vVertexNormal = Vector3D::ZERO;

            // Add together the surrounding face normals
            int nNumFaces = 0;
            if (r > 0 && c > 0) {
                vVertexNormal += s_aFaceNormals[r-1][c-1];
                ++nNumFaces;
            }
            if (r > 0 && c < MESH_SIZE) {
                vVertexNormal += s_aFaceNormals[r-1][c];
                ++nNumFaces;
            }
            if (r < MESH_SIZE && c < MESH_SIZE) {
                vVertexNormal += s_aFaceNormals[r][c];
                ++nNumFaces;
            }
            if (r < MESH_SIZE && c > 0) {
                vVertexNormal += s_aFaceNormals[r][c-1];
                ++nNumFaces;
            }
            
            // Average them
            s_aParticles[r][c].normal = vVertexNormal / nNumFaces;
        }
    }

    // Compute refraction rays
    Vector3D vIncidentRay;
    Vector3D vRefractedRay;
    for (r = 0; r <= MESH_SIZE; ++r) {
        for (c = 0; c <= MESH_SIZE; ++c)
        {
            Particle& p = s_aParticles[r][c];

            vIncidentRay = (p.position - m_tCamera.Position()).Normalized();
            vRefractedRay = (-p.normal * REFRACTION_FACTOR + vIncidentRay).Normalized();
            
            float fDepth = WATER_DEPTH + p.position.y;
            float fDepthFactor = fDepth / -vRefractedRay.y;

            p.refractionTexCoords.x = (p.position.x + vRefractedRay.x * fDepthFactor) / MESH_SIZE;
            p.refractionTexCoords.y = (p.position.z + vRefractedRay.z * fDepthFactor) / MESH_SIZE;
        }
    }
}

void
SpringWater::Display ()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    
        glLoadIdentity();

        // Orient the scene with respect to the camera
        glMultMatrixf( (float*) m_tCamera.matrix.Invert().m );

        // Draw water
        DrawWaterMesh();

        // Draw parameters
        if (m_bShowParameters) {
            ExposedParameter::DrawParameters();
        }

        // Draw help text
        glCallList( m_idHelpTextDisplayList );
        
    glPopMatrix();
    
    glutSwapBuffers();
}

void
SpringWater::DrawWaterMesh () const
{
    if (m_bWireframe)
    {
        glDisable( GL_LIGHTING );
        DrawWaterMeshWireframe();
    }
    else
    {
        glEnable( GL_LIGHTING );
        if (m_bTextured) {
            DrawWaterMeshTextured();
        } else {
            DrawWaterMeshPolys();
        }
    }
}

void
SpringWater::DrawWaterMeshWireframe () const
{
    glColor3f( 0.2f, 0.2f, 0.7f );

    for (int r = 0; r <= MESH_SIZE; ++r)
    {
        glBegin( GL_LINE_STRIP );
        for (int c = 0; c <= MESH_SIZE; ++c) {
            glVertex( s_aParticles[r][c].position );
        }
        glEnd();
    }

    for (int c = 0; c <= MESH_SIZE; ++c)
    {
        glBegin( GL_LINE_STRIP );
        for (int r = 0; r <= MESH_SIZE; ++r) {
            glVertex( s_aParticles[r][c].position );
        }
        glEnd();
    }
}

void
SpringWater::DrawWaterMeshPolys () const
{
    glColor( Colour::WHITE );
    
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_NORMAL_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glClientActiveTexture( GL_TEXTURE0 );

    glNormalPointer( GL_FLOAT, sizeof(Particle), &s_aParticles[0][0].normal );
    glTexCoordPointer( 2, GL_FLOAT, sizeof(Particle), &s_aParticles[0][0].refractionTexCoords );
    glVertexPointer( 3, GL_FLOAT, sizeof(Particle), &s_aParticles[0][0].position );

    for (int i = 0; i < MESH_SIZE; ++i)
    {
        glBegin( GL_QUAD_STRIP );
        for (int j = 0; j <= MESH_SIZE; ++j)
        {
            glArrayElement( i*(MAX_MESH_SIZE+1) + j );
            glArrayElement( (i+1)*(MAX_MESH_SIZE+1) + j );
        }
        glEnd();
    }

    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
}

void
SpringWater::DrawWaterMeshTextured () const
{
    // Refracted ground
    glActiveTexture( GL_TEXTURE0 );
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, m_idGroundTexture );
    glTexEnvfv( GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, MakeFloatArray4( 0.3f, 0.3f, 0.3f, 0.3f ) );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE );
    glTexEnvf( GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_INTERPOLATE );
    glDisable( GL_TEXTURE_GEN_S );
    glDisable( GL_TEXTURE_GEN_T );

    // Environment mapped sky
    glActiveTexture( GL_TEXTURE1 );
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, m_idSkyTexture );
    glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
    glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
    glEnable( GL_TEXTURE_GEN_S );
    glEnable( GL_TEXTURE_GEN_T );

    DrawWaterMeshPolys();

    glActiveTexture( GL_TEXTURE0 );
    glDisable( GL_TEXTURE_2D );
    glActiveTexture( GL_TEXTURE1 );
    glDisable( GL_TEXTURE_2D );
}

void
SpringWater::MouseDown (int a_eButton, int a_nX, int a_nY)
{
    m_bMouseDown = true;
    m_ptLastMousePosition = Point2D( a_nX, a_nY );

    if (m_bShowParameters) {
        ExposedParameter::MouseDown( a_nX, GetWindowHeight() - a_nY );
    }
}

void
SpringWater::MouseUp (int a_eButton, int a_nX, int a_nY)
{
    m_bMouseDown = false;
    
    if (m_bShowParameters) {
        ExposedParameter::MouseUp();
    }
}

void
SpringWater::MouseDrag (int a_nX, int a_nY)
{
    int nDeltaX = a_nX - m_ptLastMousePosition.x;
    int nDeltaY = a_nY - m_ptLastMousePosition.y;

    m_ptLastMousePosition = Point2D( a_nX, a_nY );

    if (m_bShowParameters) {
        ExposedParameter::MouseDrag( nDeltaX, nDeltaY );
    }
}

void
SpringWater::KeyDown (unsigned char a_nKey, int a_nX, int a_nY)
{
    switch (a_nKey)
    {
        case 'p':
            m_bShowParameters = !m_bShowParameters;
            break;

        case 'w':
            m_bWireframe = !m_bWireframe;
            break;

        case 't':
            m_bTextured = !m_bTextured;
            break;

        case 'r':
            ResetWater();
            break;

        case '-':
            m_fCameraTilt += 1.0f;
            ResetCamera();
            break;
            
        case '+':
        case '=':
            m_fCameraTilt -= 1.0f;
            ResetCamera();
            break;
    }
}

void
SpringWater::ResetWater ()
{
    int r, c;
    
    // Initialize particles
    for (r = 0; r <= MESH_SIZE; ++r) {
        for (c = 0; c <= MESH_SIZE; ++c)
        {
            Particle& p = s_aParticles[r][c];
            
            p.position = Vector3D( (float) c, 0.0f, (float) r );
            p.velocity = Vector3D::ZERO;
            p.acceleration = Vector3D::ZERO;
            p.forces = Vector3D::ZERO;
            p.fixed = (r == 0 || c == 0 || r == MESH_SIZE || c == MESH_SIZE);
        }
    }
    
    // Initialize springs
    int s = 0;
    for (r = 0; r <= MESH_SIZE; ++r) {
        for (c = 0; c <= MESH_SIZE; ++c)
        {
            if (CROSS_SPRINGS)
            {
                // Connect horizontal spring
                if (c < MESH_SIZE) {
                    s_aSprings[s].Init( s_aParticles[r][c], s_aParticles[r][c+1] );
                    ++s;
                }
                
                // Connect vertical spring
                if (r < MESH_SIZE) {
                    s_aSprings[s].Init( s_aParticles[r][c], s_aParticles[r+1][c] );
                    ++s;
                }
            }
            
            if (DIAGONAL_SPRINGS)
            {
                // Connect diagonal springs
                if (c < MESH_SIZE && r < MESH_SIZE)
                {
                    s_aSprings[s].Init( s_aParticles[r][c], s_aParticles[r+1][c+1], SHEAR_TENSION );
                    ++s;
                    s_aSprings[s].Init( s_aParticles[r+1][c], s_aParticles[r][c+1], SHEAR_TENSION );
                    ++s;
                }
            }
        }
    }
    m_nNumSprings = s;
}

void
SpringWater::ResetCamera ()
{
    m_tCamera.matrix = Matrix4D::IDENTITY;
    m_tCamera.RotateGlobal( m_fCameraTilt, Vector3D( 1.0f, 0.0f, 0.0f ) );
    m_tCamera.TranslateLocal( Vector3D( 0.0f, 0.0f, 0.8f ) * MESH_SIZE );
    m_tCamera.TranslateGlobal( Vector3D( 0.5f, 0.1f, 0.6f ) * MESH_SIZE );
}

// Static function to call after mesh size is changed
// (used as the AfterFunc of the MESH_SIZE ExposedParameter)
void
SpringWater::ResetMesh ()
{
    static_cast<SpringWater*>(s_pApplicationInstance)->ResetWater();
    static_cast<SpringWater*>(s_pApplicationInstance)->ResetCamera();
}

////////////////////////////////////////////////////////////////////////////////
//
//  main function
//
////////////////////////////////////////////////////////////////////////////////

int main (int argc, char* argv [])
{
    glutInit( &argc, argv );
    SpringWater app;
    app.Run();
    return 0;
}

