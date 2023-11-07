/*其实在求最大 最小的时候只要用一个模板就行了,把边的权值去相反数即可得到另外一个.求结果的时候再去相反数即可*/
/*最大最小有一些地方不同。。*/
#include <iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
const int MaxN = 101;
const int INF = (1 << 31) - 1;
int W[MaxN][MaxN];
#define w  W
int Lx[MaxN], Ly[MaxN]; //顶标
int MatchY[MaxN];
int VisX[MaxN], VisY[MaxN];
int Slack[MaxN];
int Nx, Ny;

bool find(int x)
{
    VisX[x] = true;                                         // 已经搜索过了
    std::cout << "搜索 x " << x << " 当前期待值 " << Lx[x] << std::endl;
    for (int y = 0; y < Ny; y++)
    {
        if (VisY[y])                                        // 曾经绑定过
            continue;

        int t = Lx[x] + Ly[y] - W[x][y];                    // 期待值与真值
        if (t == 0)
        {
            VisY[y] = true;                                 // 找到合适的
            if(MatchY[y] == -1)
                std::cout << "  x-y合适 " << x  << "-" << y << "  : 期待 x+y "<< Lx[x] << "+" << Ly[y] << "   y没有配对" << std::endl;
            else
                std::cout << "  x-y合适 " << x  << "-" << y << "  : 期待 x+y "<< Lx[x] << "+" << Ly[y] << "   y配对为 " << MatchY[y] << " 对x"<<MatchY[y]<<"递归" <<std::endl;

            if (MatchY[y] == -1 || find(MatchY[y]))         // 没有匹配过 或者 递归已经匹配到其他的x
            {
                MatchY[y] = x;                              // 既然合适那么就绑定他两
                std::cout << "      绑定 x-y " << x  << "-" << y << std::endl;
                return true;        //找到增广轨
            }
        }
        else if (Slack[y] > t)                              // 对于y来说欠缺多少
        {
            // std::cout << "  x-y 不合适" << x  << "-" << y << "  : 期待 x+y-w "<< Lx[x] << "+" << Ly[y] << "-" << W[x][y] << "  : Slack "<< Slack[y] << "  t " << t << std::endl;
            Slack[y] = t;
        }
    }
    return false;                   //没有找到增广轨（说明顶点x没有对应的匹配，与完备匹配(相等子图的完备匹配)不符）
}

int KM()                //返回最优匹配的值
{
    int i, j;
    memset(MatchY, -1, sizeof(MatchY));
    memset(Ly, 0, sizeof(Ly));

    // 沿行方向上的最大  期待值最高
    for (i = 0; i < Nx; i++)
        for (j = 0, Lx[i] = -INF; j < Ny; j++)
            if (W[i][j] > Lx[i])  
                Lx[i] = W[i][j]; 

    for (int x = 0; x < Nx; x++)
    {
        for (i = 0; i < Ny; i++)
            Slack[i] = INF;

        // 
        while (true)
        {
            memset(VisX, 0, sizeof(VisX)); 
            memset(VisY, 0, sizeof(VisY));

            // 当前目标找到合适的，那就帮下一个目标找
            // 找到增广轨，退出
            if (find(x))                     
                break;
            

            std::cout << " ================== 没有找到可行匹配 ================= " << std::endl;

            //没找到，对l做调整(这会增加相等子图的边)，重新找
            int d = INF;
            for (i = 0; i < Ny; i++)          
            {
                // std::cout << "y " << i << " Slack[i] " << Slack[i] << std::endl;
                if (!VisY[i] && d > Slack[i])  // 对于y而言 没有被查阅的最小差值
                    d = Slack[i];
            }
            for (i = 0; i < Nx; i++)
            {
                if (VisX[i])    // x 曾经绑定过 左边要降低要求  降低要求之后呢 原先匹配上的依旧能匹配上  但是会多一些候选人
                {
                    std::cout << " 降低x "<< i << " ： " << Lx[i] << " - d "<< d << "   ||  " ;
                    Lx[i] -= d; //
                }
                else            // 还没遍历到的 先不动要求
                {
                    std::cout << "x "<< i << " = " << Lx[i] << "   ||  " ;
                    ;   
                }
            }
            std::cout << std::endl;
            for (i = 0; i < Ny; i++)
            {
                if (VisY[i])    // y 曾经绑定过 右边增加要求 同样要能够和左边前一次绑定过的要匹配  希望和前面匹配上的依旧匹配上
                {
                    Ly[i] += d;
                    std::cout << " 增加y "<< i << " ： " << Ly[i] << " +d "<< d << "   ||  " ;
                }
                else            // y 曾经没绑定过 就是没有一个合适的  也要降低要求
                    Slack[i] -= d;

                
            }
            std::cout << std::endl;
        }
    }
    int result = 0;
    for (i = 0; i < Ny; i++)
        if (MatchY[i] > -1)
        {
            result += W[MatchY[i]][i];
            std::cout << MatchY[i] << " - " << i << " cost " << W[MatchY[i]][i] << std::endl;
        }
    return result;
}
int main()
{
    while (true)
    {
        Nx = 4;
        Ny = 4;
        w[0][0] = 2;  w[0][1] = 5;   w[0][2] = 1;  w[0][3] = 2; 
        w[1][0] = 8;   w[1][1] = 3;   w[1][2] = 9;  w[1][3] = 3;  
        w[2][0] = 4;  w[2][1] = 9;  w[2][2] = 2; w[2][3] = 4; 
        w[3][0] = 3;   w[3][1] = 5;  w[3][2] = 6; w[3][3] = 5; 
        printf("%d\n", KM());
        break;
    }
    return 0;
}