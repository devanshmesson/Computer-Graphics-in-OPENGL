#include<bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std;

int x,y,edges,choice,angle,direction;
int plot_x,plot_y,z,plot_z;
vector<tuple<int,int,int>>point;
int transX, transY,Sx,Sy,slope,c,shx,shy,transZ,Sz,shz;
char reflex,shear,rot;

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void draw_original_polygon()  //Drawing Original Polygon
{
  glBegin(GL_POLYGON);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0.5, 0.0, 0.1); //Maroonish_red colour
   for(auto z:point)
    {
      int x=get<0>(z),y=get<1>(z),zz=get<2>(z);
      glPushMatrix();
      glVertex3f(x,y,zz);
      glPopMatrix();

    }
  glutSwapBuffers();
}

void draw_translated_polygon() //Drawing translated polygon
{
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.4, 0.75); //Blue color
  for (int i = 0; i < edges; i++)
  {
    glVertex3f(get<0>(point[i])+transX,get<1>(point[i])+transY,get<2>(point[i])+transZ);
  }
  glEnd();
}

void myInit(void)
{
  glViewport(0, 0, 640, 480);
  glClearColor(0, 0,0,0);
  glColor3f(1,1,1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-500,500,-500,500);
 glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
void draw_rotated_polygon()
{
    /*
    Test case:
    100 0 50
    300 0 70
    200 100 90
    */
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.4, 0.75); //Blue color

    //Rotate every vertex of the figure
    for(auto z:point)
    {
      int x=get<0>(z),y=get<1>(z),zz=get<2>(z);

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
      glVertex3f(plot_x,plot_y,plot_z);

    }
  glEnd();

}

void draw_scaled_polygon()
{
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.4, 0.75); //Blue color

  //Scale every vertex of the figure
    for(auto z:point)
    {
      int x=get<0>(z),y=get<1>(z),zz=get<2>(z);
      glVertex3f(x*Sx,y*Sy,zz*Sz);
    }

  glEnd();
}

void draw_reflected_about_plane_polygon()
{
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.4, 0.75); //Blue color
  //Reflect every vertex of the figure
    for(auto z:point)
    {
      int x=get<0>(z),y=get<1>(z),zz=get<2>(z);
      if(reflex=='x')glVertex3f(x,y,zz*(-1));
      else if(reflex=='y')glVertex3f(x*(-1),y,zz);
      else if(reflex=='z')glVertex3f(x,y*(-1),zz);
    }

  glEnd();
}


void draw_sheared_polygon()
{
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.4, 0.75); //Blue color
  //Shear every vertex of the figure
    for(auto z:point)
    {
       int x=get<0>(z),y=get<1>(z),zz=get<2>(z);
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

}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3f(1, 1, 1);
  draw_original_polygon();
  /*if(choice==1) draw_translated_polygon();
  else if(choice==2)draw_rotated_polygon();
  else if(choice==3)draw_scaled_polygon();
  else if(choice==4)draw_reflected_about_plane_polygon();
  else if(choice==5)draw_sheared_polygon();*/
  glFlush();
}




int main(int argc, char** argv)
{
  cout<<"1.Translation"<<endl;
  cout<<"2.Rotation"<<endl;
  cout<<"3.Scaling"<<endl;
  cout<<"4.Reflection about x or y or z axis"<<endl;
  cout<<"5.Shearing"<<endl;
  cin>>choice;
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
      cout<<"Enter Choice:";
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
    cout<<"Press 'x' for Reflection about xy-plane and Press 'y' for Reflection about yz-plane and Press 'z' for Reflection about xz-plane  "<<endl;
    cin>>reflex;
  }

  else if(choice==5)
  {
     cout<<"Press 'x' for shearing about x-axis and Press 'y' for shearing about y-axis and Press 'z' for shearing about z-axis "<<endl;
    cin>>shear;
    if(shear=='x')
    {
    cout<<"Shearing parameter towards Y direction";
    cin>>shy;
    cout<<endl;
    cout<<"Shearing parameter towards Z direction";
    cin>>shz;
    cout<<endl;
    }
    else if(shear=='y')
    {
    cout<<"Shearing parameter towards X direction";
    cin>>shx;
    cout<<endl;
    cout<<"Shearing parameter towards Z direction";
    cin>>shz;
    cout<<endl;
    }
    else if(shear=='z')
    {
    cout<<"Shearing parameter towards X direction";
    cin>>shx;
    cout<<endl;
    cout<<"Shearing parameter towards Y direction";
    cin>>shy;
    cout<<endl;
    }
    cout<<endl;
  }

  cout <<"No of edges: ";
  cin >> edges;

  cout << "Coordinates of vertices: "<<endl;
  for (int i=0;i<edges;i++)
  {
    cin>>x>>y>>z;
    point.push_back(make_tuple(x,y,z));
  }


  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Translation");
  glutDisplayFunc(display);
  myInit();
  glutMainLoop();
}
