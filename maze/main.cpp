/*  迷宫问题的递归算法*/


#include <stdio.h>
#include <stdlib.h>
#include<iostream>

#define    M     8
#define    N     11


using namespace std;

int mazePath(int* maze[],int* direction[],int x1,int y1,int x2,int y2, int Number)

/* 迷宫maze[M][N]中求从入口maze[x1][y1]到出口maze[x2][y2]的一条路径 */

/* 其中 1<=x1,x2<=M-2 , 1<=y1,y2<=N-2 */

{	int k,g,h,ResultNo=1;

	//****************************************************************


	for(k=0;k<4;k++)
	{	g= x1 + direction[k][0];
		h = y1 + direction[k][1];
		if(g==x2&&h==y2&&maze[g][h]==0)
            /* 找到路径*/
        {
            printf("The revers path is:\n");
            printf("the node is: %d %d\n",x2,y2);
            printf("the node is: %d %d\n",x1,y1);
            return 1;
        }
		if(maze[g][h]==0)
		{	maze[g][h]=2;
			if(mazePath(maze,direction,g,h,x2,y2 ,Number)==1)
				/*  如果能找到路径 */
            {
                printf("the node is: %d %d\n", x1, y1);
                cout << x1 << "," << y1 << endl;
                return 1;
            }
		}
	}
	return 0;
}


int direction[][2]={0,1,1,0,0,-1,-1,0};
int maze[][N]={
		1,1,1,1,1,1,1,1,1,1,1,
		1,0,1,0,0,1,1,1,0,0,1,
		1,0,0,0,0,0,1,0,0,1,1,
		1,0,1,1,1,0,0,0,1,1,1,
		1,0,0,0,1,0,1,1,0,1,1,
		1,1,0,0,1,0,1,1,0,0,1,
		1,1,1,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1};

int main()
{
	int *m[M] ;
	int *d[4];
    int Number;
	for (int i=0;  i<M;  i++)
		m[i]=maze[i];
	for (int i=0; i<4; i++)
		d[i]=direction[i];

    Number=1;
	while(mazePath(m,d,1,1,6,9,Number)!=0) //一直有解
	{
		Number++;
	}




    for(int i=0;i<8;i++)

        for(int j=0;j<11;j++) {
            if (j == 10)
                cout << maze[i][j] << endl;
            else  cout << maze[i][j] << ',';
        }
    return 0;
}




