#define GLFW_INCLUDE_GLCOREARB
#define GL_SILENCE_DEPRECATION

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <chrono>

using namespace std;

int h = 900;
int w = 900;

int angle = 0;


float theta = 0;
float phi = 0;
float beta = 0;

int last_x = w / 2;
int last_y = h / 2;
float X = 0, Y = 0, Z = 0;
float s_radius = 15;
float t = 0;
float tX = 0, tY = 0, tZ = 0;
float S = 1;
bool first_click = true;
int iter = 0;
bool ready_to_roll = false;
float s1 = 1, s2 = 1, s3 = 1;
bool x_ray_mode = false;
bool motion_is_done = false;
bool start_motion = false;
vector<float> cam = {100.0f, 0.0f};

class Obj
{
    string name;
    vector<float> rot_axis;
    int velocity;
    int rot_angle;
    vector<float> position;
    vector<float> end_position;
    vector<float> temp_position;
    float movement_speed;
    float alpha;
    bool is_selected;
    float col[37][3];

    void cuboid()
    {

        if (s1 > 5)
        {
            s1 = 1;
            radius = 2.9;
        }

        glScalef(s1, s1, s1);

        float w = 1.7;

        //front face
        glBegin(GL_TRIANGLES);
        glNormal3f(0, 0, 1);

        glColor3fv(col[0]);
        glVertex3f(-1.0, -1.0, w);

        glColor3fv(col[1]);
        glVertex3f(1.0, -1.0, w);

        glColor3fv(col[2]);
        glVertex3f(1.0, 1.0, w);

        glEnd();

        glBegin(GL_TRIANGLES);
        glNormal3f(0, 0, 1);

        glColor3fv(col[4]);
        glVertex3f(1.0, 1.0, w);

        glColor3fv(col[5]);
        glVertex3f(-1.0, 1.0, w);

        glColor3fv(col[6]);
        glVertex3f(-1.0, -1.0, w);

        glEnd();

        glBegin(GL_TRIANGLES);
        glNormal3f(1, 0, 0);

        glColor3fv(col[7]);
        glVertex3f(1, -1, w);

        glColor3fv(col[8]);
        glVertex3f(1, 1, w);

        glColor3fv(col[9]);
        glVertex3f(1, 1, -w);

        glEnd();

        glBegin(GL_TRIANGLES);
        glNormal3f(1, 0, 0);

        glColor3fv(col[10]);
        glVertex3f(1, 1, -w);

        glColor3fv(col[11]);
        glVertex3f(1, -1, -w);

        glColor3fv(col[12]);
        glVertex3f(1, -1, w);

        glEnd();

        //back face
        glBegin(GL_TRIANGLES);
        glNormal3f(0, 0, -1);

        glColor3fv(col[13]);
        glVertex3f(-1, -1, -w);

        glColor3fv(col[14]);
        glVertex3f(1, -1, -w);

        glColor3fv(col[15]);
        glVertex3f(1, 1, -w);

        glEnd();

        glBegin(GL_TRIANGLES);
        glNormal3f(0, 0, -1);

        glColor3fv(col[16]);
        glVertex3f(1, 1, -w);

        glColor3fv(col[17]);
        glVertex3f(-1, 1, -w);

        glColor3fv(col[18]);
        glVertex3f(-1, -1, -w);

        glEnd();

        //    right face
        glBegin(GL_TRIANGLES);
        glNormal3f(-1, 0, 0);

        glColor3fv(col[19]);
        glVertex3f(-1, -1, w);

        glColor3fv(col[20]);
        glVertex3f(-1, 1, w);

        glColor3fv(col[21]);
        glVertex3f(-1, 1, -w);

        glEnd();

        glBegin(GL_TRIANGLES);
        glNormal3f(-1, 0, 0);

        glColor3fv(col[22]);
        glVertex3f(-1, 1, -w);

        glColor3fv(col[23]);
        glVertex3f(-1, -1, -w);

        glColor3fv(col[24]);
        glVertex3f(-1, -1, w);

        glEnd();

        //topface
        glColor3f(0.0f, 1.0f, 1.0f);

        glBegin(GL_TRIANGLES);
        glNormal3f(0, 1, 0);

        glColor3fv(col[25]);
        glVertex3f(1, 1, w);

        glColor3fv(col[26]);
        glVertex3f(-1, 1, w);

        glColor3fv(col[27]);
        glVertex3f(-1, 1, -w);

        glEnd();

        glBegin(GL_TRIANGLES);
        glNormal3f(0, 1, 0);

        glColor3fv(col[28]);
        glVertex3f(-1, 1, -w);

        glColor3fv(col[29]);
        glVertex3f(1, 1, -w);

        glColor3fv(col[30]);
        glVertex3f(1, 1, w);

        glEnd();

        //bottom face
        glColor3f(1.0f, 0.0f, 1.0f);

        glBegin(GL_TRIANGLES);
        glNormal3f(0, -1, 0);

        glColor3fv(col[31]);
        glVertex3f(1, -1, w);

        glColor3fv(col[32]);
        glVertex3f(-1, -1, w);

        glColor3fv(col[33]);
        glVertex3f(-1, -1, -w);

        glEnd();

        glBegin(GL_TRIANGLES);
        glNormal3f(0, -1, 0);

        glColor3fv(col[34]);
        glVertex3f(-1, -1, -w);

        glColor3fv(col[35]);
        glVertex3f(1, -1, -w);

        glColor3fv(col[36]);
        glVertex3f(1, -1, w);

        glEnd();
        glFlush();
    }

    void hexagonalPyramid()
    {
        if (s2 > 5)
        {
            s2 = 1;
            radius = 2.75;
        }

        glScalef(s2, s2, s2);
        float wdth_1 = 1;
        float wdth_2 = 0.5;
        float wdth_3 = 2.5;

        //        0.0f,   0.0f, 0.0f,    //center
        //        -0.5f,   1.0f, 0.0f,    // left top
        //        0.5f,   1.0f, 0.0f,    // right top
        //        1.0f,   0.0f, 0.0f,    // right
        //        0.5f,   -1.0f, 0.0f,    // right bottom (notice sign)
        //        -0.5f,  -1.0f, 0.0f,    // left bottom
        //        -1.0f,   0.0f, 0.0f,     //

        // bottom plane triangles
        glBegin(GL_TRIANGLES);
        glNormal3f(0, -1, 0);

        glColor3fv(col[36]);
        glVertex3f(0.0f, 0.0f, 0.0f);

        glColor3fv(col[35]);
        glVertex3f(wdth_2, wdth_1, 0.0f);

        glColor3fv(col[34]);
        glVertex3f(wdth_1, 0.0f, 0.0f);

        glEnd();

        glBegin(GL_TRIANGLES);
        glNormal3f(0, -1, 0);

        glColor3fv(col[34]);
        glVertex3f(0.0f, 0.0f, 0.0f);

        glColor3fv(col[32]);
        glVertex3f(wdth_1, 0.0f, 0.0f);

        glColor3fv(col[31]);
        glVertex3f(wdth_2, -wdth_1, 0.0f);

        glEnd();

        glBegin(GL_TRIANGLES);
        glNormal3f(0, -1, 0);

        glColor3fv(col[30]);
        glVertex3f(0.0f, 0.0f, 0.0f);

        glColor3fv(col[29]);
        glVertex3f(wdth_2, -wdth_1, 0.0f);

        glColor3fv(col[28]);
        glVertex3f(-wdth_2, -wdth_1, 0.0f);

        glEnd();

        glBegin(GL_TRIANGLES);
        glNormal3f(0, -1, 0);

        glColor3fv(col[27]);
        glVertex3f(0.0f, 0.0f, 0.0f);

        glColor3fv(col[26]);
        glVertex3f(-wdth_2, -wdth_1, 0.0f);

        glColor3fv(col[25]);
        glVertex3f(-wdth_1, 0.0f, 0.0f);

        glEnd();

        glBegin(GL_TRIANGLES);
        glNormal3f(0, -1, 0);

        glColor3fv(col[24]);
        glVertex3f(0.0f, 0.0f, 0.0f);

        glColor3fv(col[23]);
        glVertex3f(-wdth_1, 0.0f, 0.0f);

        glColor3fv(col[22]);
        glVertex3f(-wdth_2, wdth_1, 0.0f);

        glEnd();

        glBegin(GL_TRIANGLES);
        glNormal3f(0, -1, 0);

        glColor3fv(col[21]);
        glVertex3f(0.0f, 0.0f, 0.0f);

        glColor3fv(col[20]);
        glVertex3f(-wdth_2, wdth_1, 0.0f);

        glColor3fv(col[19]);
        glVertex3f(wdth_2, wdth_1, 0.0f);

        glEnd();

        //apex planes
        glBegin(GL_TRIANGLES);
        //    glNormal3f(0, -1, 0);

        glColor3fv(col[18]);
        glVertex3f(0.0f, 0.0f, wdth_3);

        glColor3fv(col[17]);
        glVertex3f(wdth_2, wdth_1, 0.0f);

        glColor3fv(col[16]);
        glVertex3f(wdth_1, 0.0f, 0.0f);

        glEnd();

        glBegin(GL_TRIANGLES);
        //glNormal3f(0, -1, 0);

        glColor3fv(col[15]);
        glVertex3f(0.0f, 0.0f, wdth_3);

        glColor3fv(col[14]);
        glVertex3f(wdth_1, 0.0f, 0.0f);

        glColor3fv(col[13]);
        glVertex3f(wdth_2, -wdth_1, 0.0f);

        glEnd();

        glBegin(GL_TRIANGLES);
        //glNormal3f(0, -1, 0);

        glColor3fv(col[12]);
        glVertex3f(0.0f, 0.0f, wdth_3);

        glColor3fv(col[11]);
        glVertex3f(wdth_2, -wdth_1, 0.0f);

        glColor3fv(col[10]);
        glVertex3f(-wdth_2, -wdth_1, 0.0f);

        glEnd();

        glBegin(GL_TRIANGLES);
        //glNormal3f(0, -1, 0);

        glColor3fv(col[9]);
        glVertex3f(0.0f, 0.0f, wdth_3);

        glColor3fv(col[8]);
        glVertex3f(-wdth_2, -wdth_1, 0.0f);

        glColor3fv(col[7]);
        glVertex3f(-wdth_1, 0.0f, 0.0f);

        glEnd();

        glBegin(GL_TRIANGLES);
        //glNormal3f(0, -1, 0);

        glColor3fv(col[6]);
        glVertex3f(0.0f, 0.0f, wdth_3);

        glColor3fv(col[5]);
        glVertex3f(-wdth_1, 0.0f, 0.0f);

        glColor3fv(col[4]);
        glVertex3f(-wdth_2, wdth_1, 0.0f);

        glEnd();

        glBegin(GL_TRIANGLES);
        //glNormal3f(0, -1, 0);

        glColor3fv(col[3]);
        glVertex3f(0.0f, 0.0f, wdth_3);

        glColor3fv(col[2]);
        glVertex3f(-wdth_2, wdth_1, 0.0f);

        glColor3fv(col[1]);
        glVertex3f(wdth_2, wdth_1, 0.0f);

        glEnd();

        glFlush();
    }

    void pentagonalPrism()
    {
        if (s3 > 5)
        {
            s3 = 1;
            radius = 1.8;
        }

        glScalef(s3, s3, s3);

        float h = 1;

        //bottom face
        glBegin(GL_TRIANGLES);
        glNormal3f(0, 0, -1);

        glColor3fv(col[36]);
        glVertex3f(-0.7, -1.0, 0);
        glColor3fv(col[35]);
        glVertex3f(-1.0, 0.3, 0);
        glColor3fv(col[34]);
        glVertex3f(0.0, 1.0, 0);

        glColor3fv(col[33]);
        glVertex3f(-0.7, -1.0, 0);
        glColor3fv(col[32]);
        glVertex3f(0.0, 1.0, 0);
        glColor3fv(col[31]);
        glVertex3f(1.0, 0.3, 0);

        glColor3fv(col[30]);
        glVertex3f(-0.7, -1.0, 0);
        glColor3fv(col[29]);
        glVertex3f(1.0, 0.3, 0);
        glColor3fv(col[28]);
        glVertex3f(0.7, -1.0, 0);

        glEnd();

        //top face
        glBegin(GL_TRIANGLES);
        glNormal3f(0, 0, 1);

        glColor3fv(col[27]);
        glVertex3f(-0.7, -1.0, h);
        glColor3fv(col[26]);
        glVertex3f(-1.0, 0.3, h);
        glColor3fv(col[25]);
        glVertex3f(0.0, 1.0, h);

        glColor3fv(col[24]);
        glVertex3f(-0.7, -1.0, h);
        glColor3fv(col[22]);
        glVertex3f(0.0, 1.0, h);
        glColor3fv(col[21]);
        glVertex3f(1.0, 0.3, h);

        glColor3fv(col[23]);
        glVertex3f(-0.7, -1.0, h);
        glColor3fv(col[20]);
        glVertex3f(1.0, 0.3, h);
        glColor3fv(col[19]);
        glVertex3f(0.7, -1.0, h);

        glEnd();

        //    side faces
        glBegin(GL_TRIANGLES);
        //    glNormal3f(0, 0, 1);

        glColor3fv(col[18]);
        glVertex3f(-0.7, -1.0, h);
        glColor3fv(col[17]);
        glVertex3f(-0.7, -1.0, 0);
        glColor3fv(col[16]);
        glVertex3f(0.7, -1.0, h);

        glColor3fv(col[15]);
        glVertex3f(-0.7, -1.0, h);
        glColor3fv(col[14]);
        glVertex3f(-0.7, -1.0, 0);
        glColor3fv(col[13]);
        glVertex3f(-1.0, 0.3, h);

        glColor3fv(col[12]);
        glVertex3f(-1.0, 0.3, h);
        glColor3fv(col[11]);
        glVertex3f(-1.0, 0.3, 0);
        glColor3fv(col[10]);
        glVertex3f(0.0, 1.0, h);

        glColor3fv(col[9]);
        glVertex3f(-1.0, 0.3, h);
        glColor3fv(col[7]);
        glVertex3f(-1.0, 0.3, 0);
        glColor3fv(col[8]);
        glVertex3f(-0.7, -1.0, 0);

        glColor3fv(col[6]);
        glVertex3f(0.0, 1.0, h);
        glColor3fv(col[5]);
        glVertex3f(0.0, 1.0, 0);
        glColor3fv(col[4]);
        glVertex3f(-1.0, 0.3, 0);

        glColor3fv(col[3]);
        glVertex3f(0.0, 1.0, h);
        glColor3fv(col[2]);
        glVertex3f(0.0, 1.0, 0);
        glColor3fv(col[1]);
        glVertex3f(1.0, 0.3, h);

        glColor3fv(col[0]);
        glVertex3f(1.0, 0.3, h);
        glColor3fv(col[1]);
        glVertex3f(1.0, 0.3, 0);
        glColor3fv(col[2]);
        glVertex3f(0.7, -1.0, h);

        glColor3fv(col[3]);
        glVertex3f(1.0, 0.3, h);
        glColor3fv(col[4]);
        glVertex3f(1.0, 0.3, 0);
        glColor3fv(col[5]);
        glVertex3f(0.0, 1.0, 0);

        glColor3fv(col[6]);
        glVertex3f(0.7, -1.0, h);
        glColor3fv(col[7]);
        glVertex3f(0.7, -1.0, 0);
        glColor3fv(col[8]);
        glVertex3f(-0.7, -1.0, 0);

        glColor3fv(col[9]);
        glVertex3f(0.7, -1.0, h);
        glColor3fv(col[10]);
        glVertex3f(0.7, -1.0, 0);
        glColor3fv(col[11]);
        glVertex3f(1.0, 0.3, 0);

        glEnd();

        glFlush();
    }

    static float generateRandomNumber(int l, int h)
    {
        random_device device;
        mt19937 generator(device());
        if (l == 0 && h == 1)
        {

            uniform_int_distribution<int> distribution(0, 100);
            return float(distribution(generator)) / 100;
        }
        uniform_int_distribution<int> distribution(l, h);
        //        generate a random number between l and h

        return distribution(generator);
    }

    static vector<float> generateRandomVector(int lim)
    {


        return {generateRandomNumber(-lim, lim), generateRandomNumber(-lim, lim), generateRandomNumber(-lim, lim)};
    }

    static vector<float> generateRandomPointOnSphere(float r)
    {
        // centered at origin
        float t = generateRandomNumber(0, 360);
        float p = generateRandomNumber(0, 180);

        t = t * 0.0174533;
        p = p * 0.0174533;

        float x = r * sin(p) * cos(t);
        float y = r * sin(p) * sin(t);
        float z = r * cos(p);

        return {x, y, z};
    }

    void initCol()
    {
        for (int i = 0; i < 37; i++)
        {
            col[i][0] = generateRandomNumber(0, 1);
            col[i][1] = generateRandomNumber(0, 1);
            col[i][2] = generateRandomNumber(0, 1);
        }
    }

public:
    float radius;

    Obj(string n, float r)
    {
        name = n;
        radius = r;
        rot_angle = generateRandomNumber(1, 360);
        rot_axis = generateRandomVector(radius);  // generate a random vector
        velocity = generateRandomNumber(-25, 25); // generate a random angle

        movement_speed = 0.0000000001;
        alpha = 0;

        while (velocity == 0)
        {
            velocity = generateRandomNumber(-25, 25);
        }

        //
        ////    testing
        //        position = {0,0,0};
        position = generateRandomVector(s_radius - radius - 2); // generate a random spawn point inside the sphere

        temp_position = position;

        end_position = generateRandomPointOnSphere(s_radius - radius);

        is_selected = false;
        initCol();
    }

    void drawObj()
    {
        glPushMatrix();

        if (is_selected)
        {
            glTranslatef(tX, tY, tZ);
            glRotatef(angle, X, Y, Z);
        }
        else
        {
            //random motion
            glTranslatef(temp_position[0], temp_position[1], temp_position[2]);

            //random rot
            glRotatef(rot_angle, rot_axis[0], rot_axis[1], rot_axis[2]);
        }

        if (name == "cuboid")
            cuboid();
        else if (name == "hex_pyramid")
            hexagonalPyramid();
        else if (name == "pent_prism")
            pentagonalPrism();

        glPopMatrix();
    }

    void setAngle()
    {
        rot_angle = (rot_angle + velocity) % 360;
    }

    void moveObj(float delta_time, bool reset)
    {
        if (reset)
        {

            position = generateRandomVector(s_radius - radius - 2); // generate a random spawn point inside the sphere

            temp_position = position;

            end_position = generateRandomPointOnSphere(s_radius - radius);
            alpha = 0;
        }
        else if (!is_selected)
        {
            if (alpha >= 1)
            {
                //reset points

                position = end_position;
                end_position = generateRandomPointOnSphere(s_radius - radius);

                alpha = 0;
                return;
            }
            else
            {
                //            alpha += movement_speed * delta_time;
                alpha += 0.01;
                //            clamp(alpha, 0, 1);
                //            vec3 currentPos = startPos * alpha + (1 - alpha) * Endpos;
                temp_position[0] = end_position[0] * alpha + (1 - alpha) * position[0];
                temp_position[1] = end_position[1] * alpha + (1 - alpha) * position[1];
                temp_position[2] = end_position[2] * alpha + (1 - alpha) * position[2];

                //            cout << "new posiotn " << temp_position[0] << " " << temp_position[1] << " " << temp_position[2] << endl;
            }
            //        glutPostRedisplay();
            //        drawObj();
        }
    }

    void test(float time)
    {

        //biezer curve testing



        GLfloat controlPointsGirl[4][3] = {
            {position[0], position[1], position[2]}, {1.0, -0.5, 0.0}, {1.0, 0.0, 0.0}, {end_position[0], end_position[1], end_position[2]}};

        X = ((1 - time) * (1 - time) * (1 - time) * controlPointsGirl[0][0] + (3 * time * (1 - time) * (1 - time)) * controlPointsGirl[1][0] + (3 * time * time * (1 - time)) * controlPointsGirl[2][0] + time * time * time * controlPointsGirl[3][0]) / 10;

        Y = ((1 - time) * (1 - time) * (1 - time) * controlPointsGirl[0][1] + (3 * time * (1 - time) * (1 - time)) * controlPointsGirl[1][1] + (3 * time * time * (1 - time)) * controlPointsGirl[2][1] + time * time * time * controlPointsGirl[3][1]) / 10;

        

        glutPostRedisplay();
        //    time += dt;
    }

    void setSelected()
    {
        is_selected = true;
    }

    void setDeselected()
    {
        is_selected = false;
    }

    string getName()
    {
        return name;
    }
};

Obj hex_pyramid = Obj("hex_pyramid", 2.75); // radius calculated using euclidian dist
Obj pent_prism = Obj("pent_prism", 1.8);    // radius calculated using euclidian dist
Obj cuboid = Obj("cuboid", 2.9);            // radius calculated using euclidian dist
Obj sphere = Obj("sphere", 0);
Obj selected = sphere;

void init()
{
    glClearColor(0.9, 0.9, 0.9, 0.9);
    glEnable(GL_DEPTH_TEST);
}

void setMaterial(float ambientR, float ambientG, float ambientB, float diffuseR, float diffuseG, float diffuseB, float specularR, float specularG, float specularB, float shine)
{
    GLfloat ambient[] = {ambientR, ambientG, ambientB};
    GLfloat diffuse[] = {diffuseR, diffuseG, diffuseB};
    GLfloat specular[] = {specularR, specularG, specularB};
    //    GLfloat emission[] = {1, 1, 1, 1};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
    //    glMaterialf(GL_FRONT_AND_BACK, GL_EMISSION,1 );
}

void initLight()
{
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    //Tell the opengl to allow us to change the colors of the material
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0, 0, 0);

    GLfloat ambient[] = {0, 0, 0, 1};
    GLfloat diffuse[] = {1, 1, 1, 1};
    GLfloat specular[] = {1, 1, 1};
    GLfloat position[] = {-10.5, -10.5, 0, 0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void initLight2()
{
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    //Tell the opengl to allow us to change the colors of the material
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0, 0, 0);

    GLfloat ambient[] = {0, 0, 0, 1};
    GLfloat diffuse[] = {1, 1, 1, 1};
    GLfloat specular[] = {1, 1, 1};
    GLfloat position[] = {10.5, 10.5, 0, 0};

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT1, GL_POSITION, position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);

    //    GLfloat ambient[] = { 0.5, 0.5, 0.5 };
    //    GLfloat diffuse[] = { 1, 1, 1 };
    //    GLfloat specular[] = { 0.5, 0.5, 0.5 };
    //    GLfloat position[] = { 13, 0, 0, 0 };
    //
    //    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    //    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    //    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    //    glLightfv(GL_LIGHT0, GL_POSITION, position);
    //
    //    glEnable(GL_LIGHTING);
    //    glEnable(GL_LIGHT0);
    //
    //    //Tell the opengl to allow us to change the colors of the material
    //    glEnable(GL_COLOR_MATERIAL);
}

void drawBitmapText(string str, float x,
                    float y, float z)
{
    char c;
    glRasterPos3f(x, y, z);

    // Traverse the string
    for (int i = 0; i < str.length(); i++)
    {
        c = str[i];
        glutBitmapCharacter(
            GLUT_BITMAP_9_BY_15, c);
    }
}

void display()
{

    glClearStencil(0);

    // Clear your Window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    //selecting the Model View Matrix for making modification to the view
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_AUTO_NORMAL);

    //clearing the model view matrix
    glLoadIdentity();

    //    gluLookAt(cam_pos.x, cam_pos.y, cam_pos.z, 0, 0, 0, 0, 1, 0);
    gluLookAt(cam[0], 0, cam[1], 0, 0, 0, 0, 1, 0);
    glRotatef(theta, 0, 0, 1);
    glRotatef(phi, 0, 1, 0);

    if (!motion_is_done)
    {
        glPushMatrix();
        glScalef(3, 3, 3);
        glColor3f(0.0f, 0.0f, 0.0f);
        drawBitmapText("Welcome to OpenGL project :-)", -80, 45, 40);
        drawBitmapText("-> Right click for X-ray mode", -80, 42, 40);
        drawBitmapText("-> Left click to select object", -80, 39, 40);
        drawBitmapText("-> Press x, y or z to rotate selected object in axis", -80, 36, 40);
        drawBitmapText("-> Use arrow and f, b keys to move object ", -80, 33, 40);
        drawBitmapText("-> Press s to scale up S to scale down", -80, 30, 40);
        drawBitmapText("-> Hit enter or n to skip this info and enter the sphere", -80, 27, 40);
        glPopMatrix();
    }

    glPushMatrix();

    setMaterial(0, 0, 0, 0.5, 0.5, 0.5, 1, 1, 1, 128);
    glColor3f(.6f, .6f, .0f);
    glLineWidth(1);
    glStencilFunc(GL_ALWAYS, 4, 0xFF);
    glutSolidSphere(15, 50, 50);

    setMaterial(1, 1, 1, 0.5, 0.5, 0.5, 1, 1, 1, 128);

    glLineWidth(5);
    glPointSize(2);

    if (x_ray_mode)
    {
        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    //    glPushMatrix();
    if (motion_is_done)
    {
        glStencilFunc(GL_ALWAYS, 2, 0xFF);
        hex_pyramid.drawObj();
       
        glStencilFunc(GL_ALWAYS, 3, 0xFF);
        pent_prism.drawObj();
       
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        cuboid.drawObj();
        
    }


    initLight();
    initLight2();
    glPopMatrix();

    glutSwapBuffers();
}

void reset()
{
    X = 0;
    Y = 0;
    Z = 0;
    tX = 0;
    tY = 0;
    tZ = 0;
    S = 1;
    cuboid.setDeselected();
    hex_pyramid.setDeselected();
    pent_prism.setDeselected();
    selected = sphere;
    ready_to_roll = false;
    selected.moveObj(0.000005, true);
}

void myKeyboardFunc(unsigned char key, int x, int y)
{
    if (tZ >= 11 || tZ <= -11)
    {
        tX = 0;
        tY = 0;
        tZ = 0;
    }

    if (selected.getName() != "sphere")
    {

        switch (key)
        {
        case 'x':
            ready_to_roll = true;
            X = 1;
            Y = 0;
            Z = 0;
            break;

        case 'y':
            ready_to_roll = true;
            X = 0;
            Y = 1;
            Z = 0;
            break;

        case 'z':
            ready_to_roll = true;
            X = 0;
            Y = 0;
            Z = 1;
            break;

        case 'f':
            tZ = tZ + 0.2;
            break;

        case 'b':
            tZ = tZ - 0.2;
            break;
        case 's':
            //
            if (selected.getName() == "cuboid")
            {
                s1 += 0.1;
                selected.radius = 2.9 * s1;
            }

            else if (selected.getName() == "hex_pyramid")
            {
                s2 += 0.1;
                selected.radius = 2.75 * s2;
            }

            else if (selected.getName() == "pent_prism")
            {
                s3 += 0.1;
                selected.radius = 1.8 * s3;
            }

            break;
        case 'S':
            if (selected.getName() == "cuboid")
            {
                s1 -= 0.1;
                selected.radius = 2.75 * s1;
            }

            else if (selected.getName() == "hex_pyramid")
            {
                s2 -= 0.1;
                selected.radius = 2.5 * s2;
            }

            else if (selected.getName() == "pent_prism")
            {

                s3 -= 0.1;
                selected.radius = 1.6 * s3;
            }
    

            break;

        default:
            break;
        }
    }
    else
    {
        reset();
        switch (key)
        {
        case 13:
        case 'n':
            start_motion = true;
            break;

        default:
            break;
        }
    }

    glutPostRedisplay();
    return;
}

void mySpecialFunc(int key, int x, int y)
{
    if (tX >= 11 || tY >= 11 || tZ >= 11 || tX <= -11 || tY <= -11 || tZ <= -11)
    {
        tX = 0;
        tY = 0;
        tZ = 0;
    }
    if (selected.getName() != "sphere")
    {
        switch (key)
        {
        case GLUT_KEY_UP:
            tY = tY + 0.2;
            break;
        case GLUT_KEY_DOWN:
            tY = tY - 0.2;
            break;
        case GLUT_KEY_RIGHT:
            tX = tX + 0.2;
            break;
        case GLUT_KEY_LEFT:
            tX = tX - 0.2;
            break;
        }
    }
    else
    {
        reset();
    }

    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

void timer(int val)
{
    glutTimerFunc(1000 / 60, timer, 0);
    if (ready_to_roll)
        angle = (angle + 10) % 360;


    if (start_motion and beta < 180)
    {
        beta += 2.5;
        cam[0] = (85 / 2 + s_radius) + (85 / 2) * cos(beta * 0.0174533);
        cam[1] = (85 / 2) * sin(beta * 0.0174533);
    }

    if (beta == 180)
    {
        cam[0] = s_radius;
        cam[1] = 0;
        beta += 100;
        motion_is_done = true;
    }

    cuboid.setAngle();
    hex_pyramid.setAngle();
    pent_prism.setAngle();

    if (iter % 60 == 0)
    {
        cuboid.moveObj(0.000005, false);
        hex_pyramid.moveObj(0.000005, false);
        pent_prism.moveObj(0.000005, false);
    }

    glutPostRedisplay();
}

void selectionFunction(int x, int y)
{
    GLuint index;
    glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    switch (index)
    {

    case 1:
        cout << "cuboid selected" << endl;
        hex_pyramid.setDeselected();
        pent_prism.setDeselected();
        cuboid.setSelected();
        selected = cuboid;
        break;
    case 2:
        cout << "hexpyramid selected" << endl;
        cuboid.setDeselected();
        pent_prism.setDeselected();
        hex_pyramid.setSelected();
        selected = hex_pyramid;
        break;
    case 3:
        cout << "pentprism selected" << endl;
        cuboid.setDeselected();
        hex_pyramid.setDeselected();
        pent_prism.setSelected();
        selected = pent_prism;
        break;

    default:
        reset();
        break;
    }
}

void myMouseFunc(int button, int state, int x, int y)
{
    if (state != GLUT_DOWN)
        return;

    switch (button)
    {
    case 0:
        selectionFunction(x, y);
        break;

    case 2:
        x_ray_mode = !x_ray_mode;
        break;

    default:
        break;
    }

    glutPostRedisplay();
    return;
}

void myMouseMotion(int x, int y)
{

    if (first_click)
    {
        last_x = x;
        last_y = y;
        first_click = false;
    }

    float xoffset = x - last_x;
    float yoffset = last_y - y; // reversed since y-coordinates go from bottom to top
    last_x = x;
    last_y = y;

    float sensitivity = 0.75f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    phi += xoffset;
    theta += yoffset;
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);

    glutInitWindowPosition(10, 10);
    glutInitWindowSize(h, w);

    glutCreateWindow(" OpenGL Project ");
    init();

    glutDisplayFunc(display);

    glutTimerFunc(1000, timer, 1);

    //define callback for keyboard interactions
    glutKeyboardFunc(myKeyboardFunc);

    //define the special keyboard callback function
    glutSpecialFunc(mySpecialFunc);

    // define a callback for mouse event
    glutMouseFunc(myMouseFunc);

    // defining callback for mouse movement
    glutMotionFunc(myMouseMotion);

    //Setup projection window
    glMatrixMode(GL_PROJECTION); // Select Projection Matrix
    glLoadIdentity();
    gluPerspective(60, 1, 0.5, 1000);

    glutReshapeFunc(reshape);

    glutMainLoop();
}

