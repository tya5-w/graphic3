//クリック全体が回転,右クリックで逆回転、cを押すと全てのリングがカメラに対して正面になる、qを押すと終了

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <math.h>
int rotation = 0; //rotation angle for animation
double sheeta = 0;
int count = 0;
double move;

const GLfloat AmbientMat[4] = {1.0, 1.0, 1.0, 1.0};
const GLfloat DiffuseMat[4] = {0.1, 0.1, 0.1, 1.0};
const GLfloat SpecularMat[4] = {1.0, 1.0, 1.0, 1.0};
const GLfloat ShininessMat[1] = {20.0};

//Light0
const GLfloat lightPosition0[4] = {5, 0, 0, 1.0};
const GLfloat Ambient0[4]       = {1.0, 0.0, 0.0, 1.0};
const GLfloat Diffuse0[4]       = {1.0, 0.0, 2.0, 1.0};
const GLfloat Specular0[4]      = {3.0, 1.0, 1.0, 1.0};
const GLfloat Shininess0[1]     = {100.0};

//Light1
const GLfloat lightPosition1[4] = {3, -5, 0, 1.0};
const GLfloat Ambient1[4]       = {0.1, 0.1, 0.1, 1.0};
const GLfloat Diffuse1[4]       = {0.0, 1.0, 0.0, 1.0};
const GLfloat Specular1[4]      = {1.0, 3.0, 1.0, 1.0};
const GLfloat Shininess1[1]     = {100.0};

//Light3
const GLfloat lightPosition2[4] = {-5, 0, 0, 1.0};
const GLfloat Ambient2[4]       = {0.1, 0.1, 0.1, 1.0};
const GLfloat Diffuse2[4]       = {0.0, 0.0, 1.0, 1.0};
const GLfloat Specular2[4]      = {1.0, 1.0, 3.0, 1.0};
const GLfloat Shininess2[1]     = {100.0};



void setup(){
 glEnable(GL_DEPTH_TEST); //enable shading (depth test)
 glEnable(GL_LIGHTING); //enable lighting
    //Material
    glMaterialfv(GL_FRONT, GL_AMBIENT, AmbientMat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, DiffuseMat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, SpecularMat);
    glMaterialfv(GL_FRONT, GL_SHININESS, ShininessMat);
    
    //  LIGHT 0
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
        glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse0);
        glLightfv(GL_LIGHT0, GL_SPECULAR, Specular0);
        glLightfv(GL_LIGHT0, GL_SHININESS, Shininess0);

    //  LIGHT 1
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
        glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, Specular1);
        glLightfv(GL_LIGHT1, GL_SHININESS, Shininess1);

    //  LIGHT 2
        glEnable(GL_LIGHT2);
        glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2);
        glLightfv(GL_LIGHT2, GL_AMBIENT, Ambient2);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, Diffuse2);
        glLightfv(GL_LIGHT2, GL_SPECULAR, Specular2);
        glLightfv(GL_LIGHT2, GL_SHININESS, Shininess2);
    
}
void reshape(int width, int height){
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width/height, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0 );
}
void idle(void){
    rotation-=10;
    if(rotation >= 360 ) rotation = 0;
    count -= 10;
    if(count >= 720) count = 0;
    sheeta = count*3.14/360;
    glutPostRedisplay();
}

void idle_1(void){
    rotation+=10;
    if(rotation >= 360 ) rotation = 0;
    count += 10;
    if(count >= 720) count = 0;
    sheeta = count*3.14/360;
    glutPostRedisplay();
}
void display(void){
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //affine transformation
    glPushMatrix();//左端
    glTranslated(-0.25-0.25*cos(sheeta), 0.0,-sin(sheeta));//平行移動値の設定
    glRotatef(rotation, 0.5, 0.5, 0.5); //x軸を中心に回転
    glutSolidTorus(0.05, 0.2, 100, 100);
    glPopMatrix();
    glPushMatrix();//真ん中
    glTranslated(0.0, 0.0, 0.0);//平行移動値の設定
    glRotatef(rotation, 0.5, 0.5, 0.5); //x軸を中心に回転
     glutSolidTorus(0.05, 0.2, 100, 100);
    glPopMatrix();
    glPushMatrix();//左下
    glTranslated(-0.125-0.125*cos(sheeta), -0.1-0.1*cos(sheeta), -0.1);//平行移動値の設定
    glRotatef(rotation, 0.5, 0.5, 0.5); //x軸を中心に回転
     glutSolidTorus(0.05, 0.2, 100, 100);
    glPopMatrix();
    glPushMatrix();//右下
    glTranslated(0.125+0.125*cos(sheeta), -0.1-0.1*cos(sheeta), -0.1);//平行移動値の設定
    glRotatef(rotation, 0.5, 0.5, 0.5); //x軸を中心に回転
     glutSolidTorus(0.05, 0.2, 100, 100);
    glPopMatrix();
    glPushMatrix();//右端
    glTranslated(0.25+0.25*cos(sheeta), 0.0, sin(sheeta));//平行移動値の設定
    glRotatef(rotation, 0.5, 0.5, 0.5); //x軸を中心に回転
     glutSolidTorus(0.05, 0.2, 100, 100);
    glPopMatrix();
    glPushMatrix();//右端
    glTranslated(0.25+0.25*cos(sheeta), 0.0, sin(sheeta));//平行移動値の設定
    glRotatef(rotation, 0.5, 0.5, 0.5); //x軸を中心に回転
     glutSolidTorus(0.05, 0.2, 100, 100);
    glPopMatrix();
    glutSwapBuffers();
}

void mouse(int button,int state,int x,int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        glutIdleFunc(idle);
    }
    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        glutIdleFunc(idle_1);
    }
    else{
        glutIdleFunc(0);
    }
}

void key(unsigned char key, int x, int y){
    switch (key){
        case'q':
            exit(0);
            break;
        case'c':
            rotation = 0;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}
int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    glutCreateWindow("hello animation");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMouseFunc(mouse);  //mousefunction
    glutKeyboardFunc(key);
    setup();

    glutMainLoop();
    return 0;
 }

