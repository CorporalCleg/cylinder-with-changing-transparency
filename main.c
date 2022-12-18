#include "vectors.h"

void display(); 
void reshape(int, int);

void processNormalKeys(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);

float rx = -2;
float ry = 4;
float rz = -10;
float angle_x = 90;
float angle_y = 0;
float angle_z = 0;
float sc = 1;
int n = 202;
float h = 2;
float k = 10;

float phi = 0.1;


void init()
{
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowPosition(200, 200);
    glutInitWindowSize(900, 900);

    glutCreateWindow("win-1");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(processNormalKeys);
    glutMouseFunc(mouse);

    init();

    glutMainLoop();
    return 0;
}



void display()
{    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(rx, ry, rz);///here
    glRotatef(angle_x, 1, 0, 0);
    glRotatef(angle_y, 0, 1, 0);
    glRotatef(angle_z, 0, 0, 1);
    glScalef(sc, sc, sc);
    glPointSize(3.0);
    //draw
    
    /// first: calculating coordintates of figure's dots
    vector a[n];
    int i;
    for(i = 0; i < n-2; i++){
        a[i].x = cos(2*3.1415*i/(n-2));
        a[i].y = sin(2*3.1415*i/(n-2));
        a[i].z = 0;
    }

    a[n-2].x = a[0].x;
    a[n-2].y = a[0].y;
    a[n-2].z = a[0].z;

    vector v;
    v.x = 0;
    v.y = 0;
    v.z = 0;

    vector source;
    source.x = 1.5 * cos(phi);
    source.y = 1.5 * sin(phi);
    source.z = 1.4;

    /// then draw figure
    glBegin(GL_TRIANGLES);
    
    /// drawing botom base
    for(i = 0; i < n-2; i++)
    {
        glColor4f(1, 0, 0.7, 1.5/distance(v, source) - 0.5);    /// here alpha-component is a function
        glVertex3f(v.x, v.y, v.z);                              /// of distance between dot called "source"
        glColor4f(1, 0, 0.7, 1.5/distance(a[i], source) - 0.5); /// and vertex
        glVertex3f(a[i].x, a[i].y, a[i].z);
        glColor4f(1, 0, 0.7, 1.5/distance(a[i+1], source) - 0.5);
        glVertex3f(a[i+1].x, a[i+1].y, a[i+1].z);
    }
    glEnd();

    v.x += 0;
    v.z += h;
    v.y = 0;

    /// drawing top base
    glBegin(GL_TRIANGLES);
    
    for(i = 0; i < n-2; i++)
    {
        ///float p = intensity(sum(a[i], v),sum(a[i + 1], v), v, source);
        glColor4f(0, 1, 0.7, 1.5/distance(v, source) - 0.5);
        glVertex3f(v.x, v.y, v.z);
        glColor4f(0, 1, 0.7, 1.5/distance(sum(v, a[i]), source) - 0.5);
        glVertex3f(a[i].x + v.x, a[i].y + v.y, a[i].z + v.z);
        glColor4f(0, 1, 0.7, 1.5/distance(sum(v, a[i+1]), source) - 0.5);
        glVertex3f(a[i+1].x + v.x, a[i+1].y + v.y, a[i+1].z + v.z);
    }
    glEnd();

    /// drawing side faces
    glBegin(GL_QUAD_STRIP);
    
    for(i = 0; i < n-2; i++)
    {
        ///float k = intensity(a[i], a[i+1], sum(a[i+1], v), source);
        ///printf("r = %f/n", distance(a[i], source));
        glColor4f(1, 0, 0.7, 1.5/distance(a[i], source) - 0.5);
        glVertex3f(a[i].x, a[i].y, a[i].z);
        glColor4f(1, 0, 0.7, 1.5/distance(a[i+1], source) - 0.5);
        glVertex3f(a[i+1].x, a[i+1].y, a[i+1].z);
        glColor4f(0, 1, 0.7, 1.5/distance(sum(a[i], v), source) - 0.5);
        glVertex3f(a[i].x + v.x, a[i].y + v.y, a[i].z + v.z);
        glColor4f(0, 1, 0.7, 1.5/distance(sum(a[i+1], v), source) - 0.25);
        glVertex3f(a[i+1].x + v.x, a[i+1].y + v.y, a[i+1].z + v.z);
    }
    glEnd();




    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 2, 50);
    glMatrixMode(GL_MODELVIEW);

}

/// mouse control function
void mouse(int button, int state, int x, int y)
{
    // Save the left button state
    if (button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
            if(y >= 700 &&(x > 200 && x < 700))
                angle_x+=10;
            else if(y < 200  && (x > 200 && x < 700))
                angle_x-=10;
            if(x >= 700  &&(y > 200 && y < 700))
                angle_z-=10;
            else if(x < 200  &&(y > 200 && y < 700))
                angle_z+=10;

    }
}

/// keyboard control function
void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 'a')
		rx+=1;
    else if (key == 'd')
		rx-=1;
    else if (key == 'w')
		rz+=1;
    else if (key == 's')
		rz-=1;
    else if (key == 'q')
		ry+=1;
    else if (key == 'e')
		ry-=1;
    else if (key == '+')
    {
        sc*=2;
    }
    else if (key == '0')
    {
        phi+=0.05;
    }
    else if (key == '-')
    {
        sc*=0.5;
    }
    else if (key == '2')
    {
        angle_y +=1;
    }
    else if (key == '3')
    {
        angle_z +=1;
    }
    else if (key == '1')
    {
        angle_x +=1;
    }
    else
        exit(0);///here
    glutPostRedisplay();
}