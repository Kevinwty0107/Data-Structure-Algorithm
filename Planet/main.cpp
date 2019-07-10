#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>




#define MAX 10
#define GAV 66742800.0
#define MS 332608.0 //相对地球质量
#define RA 1.0 //定义平均日地距离为1
#define me 5980000.0
#define ra 149597870000.0
#define YEAR 31536000.0

using namespace std;


double step = YEAR * 0.001;

struct planet
{
    char name[10];
    double mass;
    double rx,ry,rz,vx,vy,vz,ax,ay,az;
};


typedef struct planet * Pplanet;

Pplanet createPlanet(const char name1[10],double mass1,double rx1,double ry1,double vx1,double vy1)
{
    Pplanet p = (Pplanet)malloc(sizeof(struct planet));
    if(p != NULL)
    {
        int i = 0;
        for(; i < 10; i++)
            p->name[i] =name1[i];
        p->mass =mass1;
        p->rx = rx1;
        p->ry = ry1;
        p->vx = vx1;
        p->vy = vy1;
    }
    else
    {free(p);
        printf("create planet failed");}

    return p;
}

void cleana(Pplanet p)
{
    p->ax = 0;
    p->ay = 0;
    p->az = 0;

}

void cala(Pplanet p,double dax,double day)
{
    p->ax += dax;
    p->ay += day;
}

void calv(Pplanet p)
{
    p->vx += p->ax * step;
    p->vy += p->ay * step;
}

void calr(Pplanet p)
{
    p->rx += p->vx * step + 0.5 * p->ax * step * step;
    p->ry += p->vy * step + 0.5 * p->ay * step * step;
}

int main()
{
    int n = 9;
    double force[MAX][MAX][2];
    Pplanet pla[n];
    pla[0] = createPlanet("sun",MS * me,0,0,0,0);
    cout<<pla[0]->rx;
    pla[1] = createPlanet("mercury",0.0553 * me,0.3871 * ra,0,0,52716.3);
    pla[2] = createPlanet("venus",0.815 * me,0.7233 * ra,0,0,35242);
    pla[3] = createPlanet("earth",me,ra,0,0,29789);
    pla[4] = createPlanet("mars",0.1074 * me,1.523 * ra,0,0,25310);
    pla[5] = createPlanet("jupiter",317.834 * me,5.202 * ra,0,0,13413);
    pla[6] = createPlanet("saturn",95.159 * me,9.544 * ra,0,0,9927.7);
    pla[7] = createPlanet("uranus",14.5 * me,19.19 * ra,0,0,6978);
    pla[8] = createPlanet("neptune",17.2 * me,30.13 * ra,0,0,5670.9);
    double t = 0;
    while(t < 3 * YEAR)
    {
        int i = 0, j = 0;
        for (i = 0; i < n; i++)
            for (j = i + 1; j < n; j++) {
                double x1 = pla[i]->rx;
                double y1 = pla[i]->ry;
                double x2 = pla[j]->rx;
                double y2 = pla[j]->ry;
                double m1 = pla[i]->mass;
                double m2 = pla[j]->mass;
                double f = GAV * m1 * m2 / (((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) *
                                            sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
                force[i][j][0] = f * (x2 - x1);
                force[i][j][1] = f * (y2 - y1);
                force[j][i][0] = f * (x1 - x2);
                force[j][i][1] = f * (y1 - y2);
            }
        for (i = 1; i < n; i++) {
            cleana(pla[i]);
            for (j = 0; j < n; j++)
                if (i != j)
                    cala(pla[i], force[i][j][0] / pla[i]->mass, force[i][j][1] / pla[i]->mass);
            calv(pla[i]);
        }
        t += step;
        for (i = 0; i < n; i++)
            for (j = i + 1; j < n; j++) {
                double x1 = pla[i]->rx;
                double y1 = pla[i]->ry;
                double x2 = pla[j]->rx;
                double y2 = pla[j]->ry;
                double m1 = pla[i]->mass;
                double m2 = pla[j]->mass;
                double f = GAV * m1 * m2 / (((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) *
                                            sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
                force[i][j][0] = f * (x2 - x1);
                force[i][j][1] = f * (y2 - y1);
                force[j][i][0] = f * (x1 - x2);
                force[j][i][1] = f * (y1 - y2);
            }
        for (i = 1; i < n; i++) {
            cleana(pla[i]);
            for (j = 0; j < n; j++)
                if (i != j)
                    cala(pla[i], force[i][j][0] / pla[i]->mass, force[i][j][1] / pla[i]->mass);
            calr(pla[i]);
        }



        ofstream MyFile[8];
        MyFile[0].open("Mercury", ios::app);
        MyFile[1].open("Venus", ios::app);
        MyFile[2].open("Earth", ios::app);
        MyFile[3].open("Mars", ios::app);
        MyFile[4].open("Jupiter", ios::app);
        MyFile[5].open("Saturn", ios::app);
        MyFile[6].open("Uranus", ios::app);
        MyFile[7].open("Neptune", ios::app);
        for (int k = 0; k < 8; k++)                        //共8个星体，依次更新位置，速度并输出
        {
            MyFile[k] << pla[k+1]->name << ',' << pla[k+1]->rx<<','<<pla[k+1]->ry << endl;
        }
        t += step;

    }

}

