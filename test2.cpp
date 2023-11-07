/*其实在求最大 最小的时候只要用一个模板就行了,把边的权值去相反数即可得到另外一个.求结果的时候再去相反数即可*/
/*最大最小有一些地方不同。。*/
#include <iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
//赤裸裸的模板啊。。
const int maxn = 101;
const int INF = (1<<31)-1;
int w[maxn][maxn];
int lx[maxn],ly[maxn]; //顶标  
int linky[maxn];
int visx[maxn],visy[maxn];
int slack[maxn];
int nx,ny;

bool find(int x)
{
    visx[x] = true;
    for(int y = 0; y < ny; y++)
    {
        if(visy[y])
            continue;
        int t = lx[x] + ly[y] - w[x][y];
        if(t==0)
        {
            visy[y] = true;
            if(linky[y]==-1 || find(linky[y]))
            {
                linky[y] = x;
                return true;        //找到增广轨
            }
        }
        else if(slack[y] > t)
            slack[y] = t;
    }
    return false;                   //没有找到增广轨（说明顶点x没有对应的匹配，与完备匹配(相等子图的完备匹配)不符）
}

int KM()                //返回最优匹配的值
{
    int i,j;

    memset(linky,-1,sizeof(linky));
    memset(ly,0,sizeof(ly));
    for(i = 0; i < nx; i++)
        for(j = 0,lx[i] = -INF; j < ny; j++)
            if(w[i][j] > lx[i])
                lx[i] = w[i][j];
    for(int x = 0; x < nx; x++)
    {
        for(i = 0; i < ny; i++)
            slack[i] = INF;
        while(true)
        {
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(find(x))                     //找到增广轨，退出
                break;
            int d = INF;
            for(i = 0; i < ny; i++)          //没找到，对l做调整(这会增加相等子图的边)，重新找
            {
                if(!visy[i] && d > slack[i])
                    d = slack[i];
            }
            for(i = 0; i < nx; i++)
            {
                if(visx[i])
                    lx[i] -= d;
            }
            for(i = 0; i < ny; i++)
            {
                if(visy[i])
                     ly[i] += d;
                else
                     slack[i] -= d;
            }
        }
    }
    int result = 0;
    for(i = 0; i < ny; i++)
    if(linky[i]>-1)
    {
        result += w[linky[i]][i];
        std::cout << linky[i] << " - " << i << " cost " << w[linky[i]][i] << std::endl;
    }
    return result;
}

#define W w
#define Nx nx
#define Ny ny
int main()
{
    while (true)
    {
        Nx = 4;
        Ny = 4;
        W[0][0] = 2;  W[0][1] = 5;   W[0][2] = 1;  W[0][3] = 2; 
        W[1][0] = 8;   W[1][1] = 3;   W[1][2] = 9;  W[1][3] = 3;  
        W[2][0] = 4;  W[2][1] = 9;  W[2][2] = 2; W[2][3] = 4; 
        W[3][0] = 3;   W[3][1] = 5;  W[3][2] = 6; W[3][3] = 5; 
        printf("%d\n", KM());
        break;
    }
    return 0;
}