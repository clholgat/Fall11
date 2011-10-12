#ifdef _M_IX86
#include <windows.h>
#else
#include <iostream>
#endif

#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

/*--------------------------------------------------------------------------*/
/*  GLUT_DEMO.C								    */
/*    Demonstration of GLUT program with an OpenGL canvas running under	    */
/*    Windows 2000							    */
/*									    */
/*- Modification History: --------------------------------------------------*/
/*  When:	Who:			Comments:			    */
/*  12-Jun-98	Christopher G. Healey	Initial implementation		    */
/*--------------------------------------------------------------------------*/

  //  Prototypes for external C functions

extern "C" {
  void exit( int );
};

  //  Module global prototypes

void  display_obj( void );
void  draw_string( float, float, float, char * );
void  handle_menu( int );
void  handle_motion( int, int );
void  handle_mouse( int, int, int, int );

  //  Module global variables

typedef enum {
  TRANSLATE,
  ROTATE_X,
  ROTATE_Y,
  ROTATE_Z
} mode;

int    btn[ 3 ] = { 0 };		// Current button state
mode   cur_mode = TRANSLATE;		// Current mouse mode
float  translate[ 3 ] = { 0 };		// Current translation values
float  rotate[ 3 ] = { 0 };		// Current rotation values
int    mouse_x, mouse_y;		// Current mouse position


void display_obj( void )

  //  This routine displays a Goroud-shaded RGB cube
{
  int    f[ 6 ][ 4 ] = {		// Face vertex indices
    { 0, 1, 2, 3 },
    { 7, 6, 5, 4 },
    { 1, 5, 6, 2 },
    { 0, 3, 7, 4 },
    { 3, 2, 6, 7 },
    { 1, 0, 4, 5 }
  };
  int	 i, j;				// Loop counters
  float  mat[ 6 ][ 4 ] = {		// Face material properties
    { 1, 0, 0, 0 },
    { 0, 1, 0, 0 },
    { 0, 0, 1, 0 },
    { 1, 1, 0, 0 },
    { 0, 1, 1, 0 },
    { 1, 0, 1, 0 }
  };
  float  n[ 6 ][ 3 ] = {		// Face normals
    {  0,  0,  1 },
    {  0,  0, -1 },
    {  1,  0,  0 },
    { -1,  0,  0 },
    {  0,  1,  0 },
    {  0, -1,  0 }
  };
  float  v[ 8 ][ 4 ] = {		// Cube vertices
    { -1, -1,  1 },
    {  1, -1,  1 },
    {  1,  1,  1 },
    { -1,  1,  1 },
    { -1, -1, -1 },
    {  1, -1, -1 },
    {  1,  1, -1 },
    { -1,  1, -1 }
  };


  glMatrixMode( GL_MODELVIEW );		// Setup model transformations
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glPushMatrix();
  glTranslatef( translate[ 0 ], translate[ 1 ], translate[ 2 ] );
  glRotatef( rotate[ 0 ], 1, 0, 0 );
  glRotatef( rotate[ 1 ], 0, 1, 0 );
  glRotatef( rotate[ 2 ], 0, 0, 1 );

  for( i = 0; i < 6; i++ ) {		// For all faces

    //  Set ambient and diffuse material property

    glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat[ i ] );

    glBegin( GL_POLYGON );		// Begin face polygon

    //  Specify face normal

    glNormal3f( n[ i ][ 0 ], n[ i ][ 1 ], n[ i ][ 2 ] );

    for( j = 0; j < 4; j++ ) {		// For all face vertices
      glVertex3fv( v[ f[ i ][ j ] ] );
    }
    glEnd();
  }

  glPopMatrix();
  glFlush();				// Flush OpenGL queue

  glutSwapBuffers();			// Display back buffer
}					// End routine display_obj


void draw_string( float x, float y, float z, char *txt )

  //  This routine draws the text string at the given (x,y,z) position
  //
  //  x,y,z:  Raster position for text
  //  txt:    String to draw
{
  glRasterPos3f( x, y, z );
  while( *txt != '\0' ) {
    glutBitmapCharacter( GLUT_BITMAP_9_BY_15, *txt );
    txt++;
  }
}					// End routine draw_string


void handle_menu( int ID )

  //  This routine handles popup menu selections
  //
  //  ID:  Menu entry ID
{
  switch( ID ) {
  case 0:				// XY translation
    cur_mode = TRANSLATE;
    break;
  case 1:				// X rotation
    cur_mode = ROTATE_X;
    break;
  case 2:				// Y rotation
    cur_mode = ROTATE_Y;
    break;
  case 3:				// Z rotation
    cur_mode = ROTATE_Z;
    break;
  case 4:				// Quit
    exit( 0 );
  }
}					// End routine handle_menu


void handle_motion( int x, int y )

  //  This routine acts as a callback for GLUT mouse motion events
  //
  //  x, y:  Cursor position
{
  float	 x_ratchet;			// X ratchet value
  float	 y_ratchet;			// Y ratchet value


  if ( !btn[ 0 ] ) {			// Left button not depressed?
    return;
  }

  x_ratchet = glutGet( GLUT_WINDOW_WIDTH ) / 10.0;
  y_ratchet = glutGet( GLUT_WINDOW_HEIGHT ) / 10.0;

  //  Windows XP has y = 0 at top, GL has y = 0 at bottom, so reverse y

  y = glutGet( GLUT_WINDOW_HEIGHT ) - y;

  switch( cur_mode ) {
  case TRANSLATE:			// XY translation
    translate[ 0 ] += (float) ( x - mouse_x ) / x_ratchet;
    translate[ 1 ] += (float) ( y - mouse_y ) / y_ratchet;
    break;
  case ROTATE_X:			// X rotation
    x_ratchet /= 10.0;
    rotate[ 0 ] += (float) ( x - mouse_x ) / x_ratchet;
    break;
  case ROTATE_Y:			// Y rotation
    x_ratchet /= 10.0;
    rotate[ 1 ] += (float) ( x - mouse_x ) / x_ratchet;
    break;
  case ROTATE_Z:			// Z rotation
    x_ratchet /= 10.0;
    rotate[ 2 ] += (float) ( x - mouse_x ) / x_ratchet;
    break;
  }

  mouse_x = x;				// Update cursor position
  mouse_y = y;

  glutPostRedisplay();
}					// End routine handle_motion


void handle_mouse( int b, int s, int x, int y )

  //  This routine acts as a callback for GLUT mouse events
  //
  //  b:     Mouse button (left, middle, or right)
  //  s:     State (button down or button up)
  //  x, y:  Cursor position
{
  if ( s == GLUT_DOWN ) {		// Store button state if mouse down
    btn[ b ] = 1;
  } else {
    btn[ b ] = 0;
  }

  mouse_x = x;
  mouse_y = glutGet( GLUT_WINDOW_HEIGHT ) - y;
}					// End routine handle_mouse


int main( int argc, char *argv[] )
{
  float  amb[] = { 0, 0, 0, 1 };	// Ambient material property
  float  lt_amb[] = { .2, .2, .2, 1 };	// Ambient light property
  float  lt_dif[] = { .8, .8, .8, 1 };	// Ambient light property
  float  lt_pos[] = {			// Light position
           0, .39392, .91914, 0
         };
  float  lt_spc[] = { 0, 0, 0, 1 };	// Specular light property


  glutInit( &argc, argv );		// Initialize GLUT
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutCreateWindow( "GLUT/XP Demo" );

  glutDisplayFunc( display_obj );	// Setup GLUT callbacks
  glutMotionFunc( handle_motion );
  glutMouseFunc( handle_mouse );

  glutCreateMenu( handle_menu );	// Setup GLUT popup menu
  glutAddMenuEntry( "Translate", 0 );
  glutAddMenuEntry( "Rotate X", 1 );
  glutAddMenuEntry( "Rotate Y", 2 );
  glutAddMenuEntry( "Rotate Z", 3 );
  glutAddMenuEntry( "Quit", 4 );
  glutAttachMenu( GLUT_RIGHT_BUTTON );

  glMatrixMode( GL_PROJECTION );	// Setup perspective projection
  glLoadIdentity();
  gluPerspective( 70, 1, 1, 40 );

  glMatrixMode( GL_MODELVIEW );		// Setup model transformations
  glLoadIdentity();
  gluLookAt( 0, 0, 5, 0, 0, -1, 0, 1, 0 );

  //  Set default ambient light in scene

  glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb );

  //  Set Light 0 position, ambient, diffuse, specular intensities

  glLightfv( GL_LIGHT0, GL_POSITION, lt_pos );
  glLightfv( GL_LIGHT0, GL_AMBIENT, lt_amb );
  glLightfv( GL_LIGHT0, GL_DIFFUSE, lt_dif );
  glLightfv( GL_LIGHT0, GL_SPECULAR, lt_spc );

  //  Enable Light 0 and GL lighting

  glEnable( GL_LIGHT0 );
  glEnable( GL_LIGHTING );

  glShadeModel( GL_FLAT );		// Flat shading
  glEnable( GL_NORMALIZE );		// Normalize normals

  glClearDepth( 1.0 );			// Setup background colour
  glClearColor( 0, 0, 0, 0 );
  glEnable( GL_DEPTH_TEST );

  glutMainLoop();			// Enter GLUT main loop
  return 1;
}					// End mainline
