#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
 
#include <SDL.h>
#include <SDL_opengl.h>
 
void Display_InitGL()
{
    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClearDepth( 1.0f );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;
    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;
    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

/* function to reset our viewport after a window resize */
int Display_SetViewport( int width, int height )
{
    GLfloat ratio;
    if ( height == 0 )
        height = 1;
    ratio = ( GLfloat )width / ( GLfloat )height;
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    perspectiveGL( 45.0f, ratio, 0.1f, 100.0f );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    return 1;
}
 
void Display_Render(SDL_Window * window)
{
    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 
    /* Move Left 1.5 Units And Into The Screen 6.0 */
    glLoadIdentity();
    glTranslatef( -1.5f, 0.0f, -6.0f );
 
    glBegin( GL_TRIANGLES );            /* Drawing Using Triangles */
      glVertex3f(  0.0f,  1.0f, 0.0f ); /* Top */
      glVertex3f( -1.0f, -1.0f, 0.0f ); /* Bottom Left */
      glVertex3f(  1.0f, -1.0f, 0.0f ); /* Bottom Right */
    glEnd( );                           /* Finished Drawing The Triangle */
 
    /* Move Right 3 Units */
    glTranslatef( 3.0f, 0.0f, 0.0f );
 
    glBegin( GL_QUADS );                /* Draw A Quad */
      glVertex3f( -1.0f,  1.0f, 0.0f ); /* Top Left */
      glVertex3f(  1.0f,  1.0f, 0.0f ); /* Top Right */
      glVertex3f(  1.0f, -1.0f, 0.0f ); /* Bottom Right */
      glVertex3f( -1.0f, -1.0f, 0.0f ); /* Bottom Left */
    glEnd( );                           /* Done Drawing The Quad */

	SDL_GL_SwapWindow(window);
}
 
int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* displayWindow = SDL_CreateWindow("", 100, 100, 800, 600, SDL_WINDOW_OPENGL);

	SDL_GL_CreateContext(displayWindow);   
    Display_InitGL();
    Display_SetViewport(800, 600);
	Display_Render(displayWindow);
    SDL_Delay(2000);
    SDL_Quit();
    return 0;
}