/*
Co-ordinates of 3D Pyramid
0 1 0
-1 -1 1
1 -1 1

0 1 0
1 -1 1
1 -1 -1

0 1 0
1 -1 -1
-1 -1 -1

0 1 0
-1 -1 -1
-1 -1 1
*/
#include<bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std;

float edges,choice,angle,direction;
float plot_x,plot_y,plot_z;
float x,y,z;
vector<tuple<float,float,float>>point;
float transX, transY,Sx,Sy,slope,c,shx,shy,transZ,Sz,shz;
char reflex,shear,rot;

  void reshape(GLsizei width, GLsizei height)
  {
   if (height == 0) height = 20;
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0f, aspect, 0.1f, 100.0f);
}


void draw_original_polygon()  //Drawing Original Polygon
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(-1.5f, 0.0f, -6.0f);

   float g=0,h=0,i=0;
   glBegin(GL_TRIANGLES);           // Draw the pyramid with 4 triangles
      for(int i=0;i<point.size();i++)
      {
        float p,q,r;
        p=get<0>(point[i]);
        q=get<1>(point[i]);
        r=get<2>(point[i]);
        g+=0.04; //colour
        h+=0.02; //colour
        i+=0.3; //colour
        glColor3f(g,h,i); //Maroonish_red colour
        glVertex3f(p,q,r);

      }
   glEnd();
   glutSwapBuffers();
}

void draw_translated_polygon() //Drawing translated polygon
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(-1.5f, 0.0f, -6.0f);
   glColor3f(0.5, 0.0, 0.1);     //Maroonish_red colour
   glBegin(GL_TRIANGLES);
      float g=0,h=0,i=0;
      for(int i=0;i<point.size();i++)
      {
        float p,q,r;
        g+=0.04; //colour
        h+=0.02; //colour
        i+=0.01; //colour
        glColor3f(g,h,i);
        p=get<0>(point[i])+transX;
        q=get<1>(point[i])+transY;
        r=get<2>(point[i])+transZ;
        glVertex3f(p,q,r);
      }
  glEnd();
  glutSwapBuffers();
}

void initGL()
{
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClearDepth(1.0f);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glShadeModel(GL_SMOOTH);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void draw_rotated_polygon()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1.5f, 0.0f, -6.0f);
    glColor3f(0.5, 0.0, 0.1);
    glBegin(GL_TRIANGLES);
    float g=0,h=0,i=0;
    //Rotate every vertex of the figure
    for(auto z:point)
    {
      float x=get<0>(z),y=get<1>(z),zz=get<2>(z);
        g+=0.04; //colour
        h+=0.02; //colour
        i+=0.3; //colour
      if(rot=='x')  //Clockwise direction
      {
        plot_x=x;
        plot_y=y*cos(angle)-zz*sin(angle);
        plot_z=y*sin(angle)+zz*cos(angle);
      }
      else if(rot=='y') //Anti-clockwise direction
      {
        plot_x=x*cos(angle)+ zz*sin(angle);
        plot_y=y;
        plot_z=y*cos(angle)-x*sin(angle);
      }
      else if(rot=='z')
      {
        plot_x=x*cos(angle)- y*sin(angle);
        plot_y=x*sin(angle)+ y*cos(angle);
        plot_z=zz;
      }
      glColor3f(g,h,i);
      glVertex3f(plot_x,plot_y,plot_z);
    }
  glEnd();
  glutSwapBuffers();
}

void draw_scaled_polygon()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1.5f, 0.0f, -6.0f);
    glBegin(GL_TRIANGLES);

    float g=0,h=0,i=0;

  //Scale every vertex of the figure
    for(auto z:point)
    {
      float x=get<0>(z),y=get<1>(z),zz=get<2>(z);
        g+=0.02; //colour
        h+=0.01; //colour
        i+=0.1; //colour
      glColor3f(g,h,i);
      glVertex3f(x*Sx,y*Sy,zz*Sz);
    }

  glEnd();
  glutSwapBuffers();
}

void draw_reflected_about_plane_polygon()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1.5f, 0.0f, -6.0f);
    glColor3f(0.5, 0.0, 0.1);
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.4, 0.75);
    float g=0,h=0,i=0;

  //Reflect every vertex of the figure
    for(auto z:point)
    {
        g+=0.06; //colour
        h+=0.01; //colour
        i+=0.3; //colour
        glColor3f(g,h,i);
      float x=get<0>(z),y=get<1>(z),zz=get<2>(z);
      if(reflex=='x')glVertex3f(x,y,zz*(-1));
      else if(reflex=='y')glVertex3f(x*(-1),y,zz);
      else if(reflex=='z')glVertex3f(x,y*(-1),zz);
    }

  glEnd();
  glutSwapBuffers();
}


void draw_sheared_polygon()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1.5f, 0.0f, -6.0f);
    glBegin(GL_TRIANGLES);
    float g=0,h=0,i=0;

  //Shear every vertex of the figure
    for(auto z:point)
    {
      float x=get<0>(z),y=get<1>(z),zz=get<2>(z);
         g+=0.06; //colour
        h+=0.01; //colour
        i+=0.3; //colour
        glColor3f(g,h,i);
      if(shear=='x')
      {
       plot_x=x;
       plot_y=y+(shy*x);
       plot_z=zz+(shz*x);
      }
      else if(shear=='y')
      {
        plot_x=x+(shx*y);
        plot_y=y;
        plot_z=zz+(shz*y);
      }
      else if(shear=='z')
      {
        plot_x=x+(shx*zz);
        plot_y=y+(shy*zz);
        plot_z=zz;
      }
      glVertex3f(plot_x,plot_y,plot_z);
    }
  glEnd();
  glutSwapBuffers();
}

void display()
{

  if(choice==1) draw_translated_polygon();
  else if(choice==2)draw_rotated_polygon();
  else if(choice==3)draw_scaled_polygon();
  else if(choice==4)draw_reflected_about_plane_polygon();
  else if(choice==5)draw_sheared_polygon();
  else draw_original_polygon();
 //glutSwapBuffers();
}

int main(int argc, char** argv)
{
  cout<<"3D-transformation"<<endl<<endl;
  cout<<"Choose which Transformation to apply:"<<endl<<endl;
  cout<<"1.Translation"<<endl;
  cout<<"2.Rotation"<<endl;
  cout<<"3.Scaling"<<endl;
  cout<<"4.Reflection about x or y or z axis"<<endl;
  cout<<"5.Shearing"<<endl;
  cout<<"6.Display Original Pyramid"<<endl;
  cout<<endl<<"Enter your choice:";
  cin>>choice;
  cout<<endl;

  if(choice==1)
  {
      cout <<"Translation factor for X and Y and Z: ";
      cin >> transX >> transY>>transZ;
  }
  else if(choice==2)
  {
      cout<<"For x axis rotation press 'x'"<<endl;
      cout<<"For y axis rotation press 'y'"<<endl;
      cout<<"For z axis rotation press 'z'"<<endl;
      cout<<"\nEnter Choice:";
      cin>>rot;
      cout<<endl;
      cout<<"Enter Rotation Angle:";
      cin>>angle;
      cout<<endl;
  }
  else if(choice==3)
  {
    cout<<"Scaling factor for x-axis:";
    cin>>Sx;
    cout<<endl;
    cout<<"Scaling factor for y-axis:";
    cin>>Sy;
    cout<<endl;
    cout<<"Scaling factor for z-axis:";
    cin>>Sz;
    cout<<endl;
  }
  else if(choice==4)
  {
    cout<<"Press 'x' for Reflection about xy-plane\nPress 'y' for Reflection about yz-plane\nPress 'z' for Reflection about xz-plane  \n"<<endl;
    cout<<"Enter choice:";
    cin>>reflex;
  }

  else if(choice==5)
  {
     cout<<"Press 'x' for shearing about x-axis\nPress 'y' for shearing about y-axis\nPress 'z' for shearing about z-axis "<<endl;
     cout<<"\nEnter choice:";
    cin>>shear;
    cout<<endl;
    if(shear=='x')
    {
    cout<<"Shearing parameter towards Y direction:";
    cin>>shy;
    cout<<endl;
    cout<<"Shearing parameter towards Z direction:";
    cin>>shz;
    cout<<endl;
    }
    else if(shear=='y')
    {
    cout<<"Shearing parameter towards X direction:";
    cin>>shx;
    cout<<endl;
    cout<<"Shearing parameter towards Z direction:";
    cin>>shz;
    cout<<endl;
    }
    else if(shear=='z')
    {
    cout<<"Shearing parameter towards X direction:";
    cin>>shx;
    cout<<endl;
    cout<<"Shearing parameter towards Y direction:";
    cin>>shy;
    cout<<endl;
    }
    cout<<endl;
  }



 cout<<"\nEnter Number of edges:";
  cin>>edges;

  cout << "\nEnter Coordinates of vertices:"<<endl;
  for (int i=0;i<edges;i++)
  {
    cin>>x>>y>>z;
    point.push_back(make_tuple(x,y,z));
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(500,500);
  glutCreateWindow("Author-Devansh");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  initGL();
  glutMainLoop();
  return 0;
}

