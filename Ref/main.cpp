#include<iostream>
#include<cstdlib>
#include<fstream>
#include<cmath>
#define G 0.000118
//宏定义行星质量以地球质量为单位
#define M_sun 330000
#define M_mercury 0.0553
#define M_venus 0.815
#define M_earth 1
#define M_mars 0.1074
#define M_jupiter 317.834
#define M_saturn 95.159
#define M_uranus 14.5
#define M_neptune 17.2
#define N 1000000

using namespace std;

class Planet
{
public:
	float ax, ay;
	float dt;								//对每个行星有一个时间间隔，它会与行星的周期成正比
	void SetPlanet(float,float,float,float,float,double);
	Planet(void);
	Planet(float x_new, float y_new, float vx_new, float vy_new, float mass_new);
	~Planet(void);
	friend float acceleration_x(Planet&, Planet&);
	friend float acceleration_y(Planet&, Planet&);
	void accel(float, float);
	void pos_chan(float,float);
	void show(void);
	float GetX(void){ return x; };
	float GetY(void){ return y; };
private:
	float x, y, vx, vy;
	float mass;
};
void Planet::SetPlanet(float x_new=0, float y_new=0, float vx_new=0, float vy_new=0, float mass_new=0,double T=0)
{
	this->x = x_new;
	this->y = y_new;
	this->vx = vx_new;
	this->vy = vy_new;
	this->mass = mass_new;
	this->ax = 0;
	this->ay = 0;
	this->dt = T / N;
}
Planet::~Planet(void)
{
	cout << "has been distroyed" << endl;
}
Planet::Planet(void){
	cout << "creating" << endl;
}
Planet::Planet(float x_new, float y_new, float vx_new, float vy_new, float mass_new)
{
	this->x = x_new;
	this->y = y_new;
	this->vx = vx_new;
	this->vy = vy_new;
	this->mass = mass_new;
	this->ax = 0;
	this->ay = 0;
	this->dt = 0;
}
float acceleration_x(Planet&p1, Planet&p2)						//星体2对1的引力产生的加速度
{
	float ax;
	ax = G*(p2.mass)*(p2.x - p1.x) /( pow((pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2)), 1.5));
	return ax;
}
float acceleration_y(Planet&p1, Planet&p2)
{
	float ay;
	ay = G*(p2.mass)*(p2.y - p1.y) /( pow((pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2)), 1.5));
	return ay;
}
void Planet::accel(float ax, float ay)
{
	vx += ax*dt;
	vy += ay*dt;
}
void Planet::pos_chan(float ax,float ay)
{
	x += vx*dt+0.5*ax*dt*dt;
	y += vy*dt+0.5*ay*dt*dt;
}
void Planet::show(void)
{
	cout << '(' << x << ',' << y << ')' << endl;
}
//计算合加速度分量的函数
float Sum_Accelx(int Planet_num,Planet*ptr,Planet&center)
{
	float sum_accelx=0;
	for (int i = 0; i < 8; i++)
	{
		if (i == Planet_num) continue;
		sum_accelx += acceleration_x(ptr[Planet_num], ptr[i]);
	}
	sum_accelx += acceleration_x(ptr[Planet_num], center);
	return sum_accelx;
};
float Sum_Accely(int Planet_num, Planet*ptr,Planet&center)
{
	float sum_accely = 0;
	for (int i = 0; i < 8; i++)
	{
		if (i == Planet_num) continue;
		sum_accely += acceleration_y(ptr[Planet_num], ptr[i]);
	}
	sum_accely += acceleration_y(ptr[Planet_num], center);
	return sum_accely;
};
Planet*CreatePlanets(void)
{
	//生成行星并更新值
	Planet*ptr;
	ptr = new Planet[8]();
	ptr[0].SetPlanet(0.39, 0, 0, 10.1638, M_mercury,0.241096);		//更新函数，分别为初始(x,y,vx,vy,mass,period)
	ptr[1].SetPlanet(0.72, 0, 0, 7.33876, M_venus,0.616438);
	ptr[2].SetPlanet(1, 0, 0, 6.28319, M_earth,1);
	ptr[3].SetPlanet(1.52, 0, 0, 5.08002, M_mars,1.88);
	ptr[4].SetPlanet(5.20, 0, 0, 2.74559, M_jupiter,11.9);
	ptr[5].SetPlanet(9.54, 0, 0, 2.03192, M_saturn,29.5);
	ptr[6].SetPlanet(19.2, 0, 0, 1.43616, M_uranus,84);
	ptr[7].SetPlanet(30.1, 0, 0, 1.14621, M_neptune,165);
	return ptr;
}

int main()
{
	//生成行星与太阳
	Planet Sun(0, 0, 0, 0, M_sun);
	Planet *plaptr = CreatePlanets();
	//open a file as .txt
	ofstream MyFile[8];
	MyFile[0].open("Mercury", ios::app);
	MyFile[1].open("Venus", ios::app);
	MyFile[2].open("Earth", ios::app);
	MyFile[3].open("Mars", ios::app);
	MyFile[4].open("Jupiter", ios::app);
	MyFile[5].open("Saturn", ios::app);
	MyFile[6].open("Uranus", ios::app);
	MyFile[7].open("Neptune", ios::app);

	for (int i = 1; i<=1.5*N; i++)
	{
		for (int k = 0; k < 8; k++)						//共8个星体，依次更新位置，速度并输出
		{
			//通过循环模拟运动
			plaptr[k].ax = Sum_Accelx(k, plaptr, Sun);
			plaptr[k].ay = Sum_Accely(k, plaptr, Sun);
			plaptr[k].pos_chan(plaptr[k].ax, plaptr[k].ay);
			plaptr[k].accel(plaptr[k].ax, plaptr[k].ay);
			if (i % 2000 == 0 && i > 2001) {
				//plaptr[1].show();
				MyFile[k] << plaptr[k].GetX() << ',' << plaptr[k].GetY() << endl;
			}	//每隔2000次输出
		}
	}

	//扫尾工作
	Sun.~Planet();
	delete[] plaptr;
	plaptr = NULL;
	system("pause");
	return 0;
}
