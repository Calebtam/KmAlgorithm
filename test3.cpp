#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=110;
const int inf=0x7fffffff;
int n,m,w[maxn][maxn];//n表示x边点的个数，y表示y边点的个数，w表示边权值 
int lx[maxn],ly[maxn];//lx表示x边的标杆，ly表示y边的标杆 
int from[maxn],to[maxn];//from[i]=j表示y边的i由x边的j连接。to[i]=j表示x边的i可以到达y边的j 
bool s[maxn],t[maxn];//s表示x边的点集，t表示y边的点集 
bool find(int x)//匈牙利算法 
{
    s[x]=1;
    for(int i=0;i<=m;i++)
    if(lx[x]+ly[i]==w[x][i]&&!t[i])
    {
        t[i]=1;
        if(!from[i]||find(from[i]))
        {
            from[i]=x;
            to[x]=i;
            return 1;
        }
    }
    return 0;
}
void update()//更新标杆 
{
    int d=inf;
    for(int i=0;i<=n;i++){
      if(s[i]){
        for(int j=0;j<=m;j++){
          if(!t[j]){
            d=min(d,lx[i]+ly[j]-w[i][j]);//按照上面给出的原则计算d 
          }
        }
      }
    }

    for(int i=0;i<=n;i++){//点集s中的点的标杆lx[i]-d 
      if(s[i]) {
        lx[i]-=d;
      }
    }
    for(int j=0;j<=m;j++){//点集t中的点的标杆ly[j]+d 
      if(t[j]) {
        ly[j]+=d;
      }
    }
}
void km()//km算法 
{
  for(int i=0;i<=n;i++)//初始化标杆 
    for(int j=0;j<=m;j++)
      lx[i]=max(lx[i],w[i][j]);
      for(int i=0;i<=n;i++)//x边每个点的匹配 
        for(;;)
        {
          memset(s,0,sizeof(s));
          memset(t,0,sizeof(t));
          if(find(i)) break;
          else update();
        }
}
// int main()
// {
//     scanf("%d%d",&n,&m);//输入 
//     for(int i=1;i<=n;i++)
//       for(int j=1;j<=m;j++)
//       scanf("%d",&w[i][j]);
//     km();
//     int ans=0;
//     for(int i=1;i<=n;i++)//计算答案 
//     ans+=w[i][to[i]];
//     printf("%d",ans);//输出 
//     return 0;
// }
#define W w
int main()
{
    // while (true)
    // {
        n = 3;
        m = 3;
        W[0][0] = 2;  W[0][1] = 5;   W[0][2] = 1;  W[0][3] = 2;
        W[1][0] = 8;   W[1][1] = 3;   W[1][2] = 9;  W[1][3] = 3;  
        W[2][0] = 4;  W[2][1] = 9;  W[2][2] = 2; W[2][3] = 4; 
        W[3][0] = 3;   W[3][1] = 5;  W[3][2] = 6; W[3][3] = 5; 
        // printf("%d\n", KM());
        km();
        
        int ans=0;
        for(int i=0;i<=n;i++)//计算答案 
        {
          ans+=w[i][to[i]];
          std::cout << i << " - " << to[i] << " cost " << w[i][to[i]] << std::endl;
        }
        // printf("%d",ans);//输出 
        std::cout << ans << std::endl;
    //     break;
    // }
    return 0;
}
