#include <iostream>
#include <fstream>
#include <stdio.h>
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




typedef double DataType;

struct  Node;					/* 单链表结点类型 */
typedef struct Node * PNode;	/* 结点指针类型 */
struct  Node
{				/* 单链表结点结构 */
    DataType  info;
    PNode link;
};
typedef struct Node * LinkList;/* 单链表类型 */
typedef LinkList * PLinkList;

struct planet
{
    char name[10];
    double mass;
    double rx,ry,rz,vx,vy,vz,ax,ay,az;
};
typedef struct planet * Pplanet;



PNode locate(LinkList plist,DataType x)
{
    PNode s;
    s = plist->link;
    while(s!=NULL && s->info!=x) {s=s->link;}
    return s;
}



Pplanet createPlanet(const char name0[10],double mass, double rx, double ry, double vx, double vy,
                     double mass0[], double rx0[], double ry0[], double vx0[], double vy0[])
{



    PNode q;
    q = (PNode) malloc(sizeof(struct Node));
    PNode mass1[9], rx1[9], ry1[9], vx1[9], vy1[9];
    for(int i=0; i<9; i++) {
        mass1[i] = (PNode) malloc(sizeof(struct Node));
        rx1[i] = (PNode) malloc(sizeof(struct Node));
        ry1[i] = (PNode) malloc(sizeof(struct Node));
        vx1[i] = (PNode) malloc(sizeof(struct Node));
        vy1[i] = (PNode) malloc(sizeof(struct Node));
    }
    LinkList plist = (LinkList) malloc(sizeof(struct Node));

        plist->link = q;
        q->info =mass0[0];
        q->link = mass1[0];
        for(int i=0 ; i<9 ; i++)
        {
            mass1[i]->info = mass0[i];
            mass1[i]->link = mass1[i+1];
        }
        mass1[8]->info = mass0[8];
        mass1[8]->link = rx1[0];
        for(int i=0 ; i<9 ; i++)
        {
            rx1[i]->info = rx0[i];
            rx1[i]->link = rx1[i+1];
        }
        rx1[8]->info = rx0[8];
        rx1[8]->link = ry1[0];
        for(int i=0 ; i<9 ; i++)
        {
            ry1[i]->info = ry0[i];
            ry1[i]->link = ry1[i+1];
        }
        ry1[8]->info = ry0[8];
        ry1[8]->link = vx1[0];
        for(int i=0 ; i<9 ; i++)
        {
            vx1[i]->info = vx0[i];
            vx1[i]->link = vx1[i+1];
        }
        vx1[8]->info = vx0[8];
        vx1[8]->link = vy1[0];
        for(int i=0 ; i<9 ; i++)
        {
            vy1[i]->info = vy0[i];
            vy1[i]->link = vy1[i+1];
        }
        vy1[8]->info = vy0[8];
        vy1[8]->link =NULL;

    Pplanet p = (Pplanet)malloc(sizeof(struct planet));
    if(p != NULL)
    {
        int i = 0;
        for(; i < 10; i++)
        {p->name[i] =name0[i];}
        p->mass =locate(plist, mass)->info;
        p->rx = locate(plist, rx)->info;
        p->ry = locate(plist, ry)->info;
        p->vx = locate(plist, vx)->info;
        p->vy = locate(plist, vy)->info;
    }
    else {free(p);
    printf("create planet failed");}
    return p;

}




double step = YEAR * 0.001;




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
    double mass[9]= {MS * me, 0.0553 * me, 0.815 * me, me , 0.1074 * me, 317.834 * me, 95.159 * me, 14.5 * me, 14.5 * me};
    double rx[9]={0, 0.3871 * ra, 0.7233 * ra,ra,1.523 * ra,5.202 * ra,9.544 * ra,19.19 * ra,30.13 * ra};
    double ry[9]={0, 0, 0, 0, 0, 0, 0, 0, 0};
    double vx[9]={0,0,0,0,0,0,0,0,0};
    double vy[9]={0,52716.3,35242,29789,25310,13413,9927.7,6978,5670.9};
    int n = 9;
    double force[MAX][MAX][2];
    Pplanet pla[n];

    pla[0] = createPlanet("sun", MS * me, 0, 0, 0, 0,mass,rx,ry,vx,vy);
    cout<<pla[0]->mass<<pla[0]->name<<pla[0]->rx<<endl;
    pla[1] = createPlanet("mercury", 0.0553 * me, 0.3871 * ra, 0, 0, 52716.3,mass,rx,ry,vx,vy);
    cout<<pla[1]->mass<<pla[1]->name<<pla[1]->rx<<endl;
    pla[2] = createPlanet("venus", 0.815 * me, 0.7233 * ra, 0, 0, 35242,mass,rx,ry,vx,vy);
    pla[3] = createPlanet("earth",me,ra,0,0,29789,mass,rx,ry,vx,vy);
    pla[4] = createPlanet("mars",0.1074 * me,1.523 * ra,0,0,25310,mass,rx,ry,vx,vy);
    pla[5] = createPlanet("jupiter",317.834 * me,5.202 * ra,0,0,13413,mass,rx,ry,vx,vy);
    pla[6] = createPlanet("saturn",95.159 * me,9.544 * ra,0,0,9927.7,mass,rx,ry,vx,vy);
    pla[7] = createPlanet("uranus",14.5 * me,19.19 * ra,0,0,6978,mass,rx,ry,vx,vy);
    pla[8] = createPlanet("neptune",14.5 * me,30.13 * ra,0,0,5670.9,mass,rx,ry,vx,vy);
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
