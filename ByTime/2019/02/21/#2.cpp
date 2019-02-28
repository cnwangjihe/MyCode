#include<cstdio>
#define N 400
struct Num{
  int len,v[N];
  Num(){for(int i=len=1;i<N;i++)v[i]=0;}
  Num operator+(const Num&b){
    Num c;
    c.len=b.len+1;
    for(int i=1;i<=c.len;i++)c.v[i]=v[i]+b.v[i];
    for(int i=1;i<=c.len;i++)c.v[i+1]+=c.v[i]>>1,c.v[i]&=1;
    while(!c.v[c.len])c.len--;
    return c;
  }
  Num operator*(const Num&b){
    Num c;
    c.len=len+b.len;
    for(int i=1;i<=len;i++)for(int j=1;j<=b.len;j++){
      if(i+j-1>=N)break;
      c.v[i+j-1]+=v[i]*b.v[j];
    }
    for(int i=1;i<=c.len;i++)c.v[i+1]+=c.v[i]>>1,c.v[i]&=1;
    while(!c.v[c.len])c.len--;
    return c;
  }
}Ten,Pow,y;
struct Big{int len,v[N];Big(){len=0;for(int i=1;i<N;i++)v[i]=0;}}x;
struct P{Big x;Num y;P(){}P(Big _x,Num _y){x=_x,y=_y;}}q0[2][210],q1[2][210];
int t0[2],t1[2],n,i,j,k,o;
inline bool check(int x,Big d,Num b){
  for(int i=1;i<=x;i++)if((i<=d.len?d.v[i]:0)!=(i<=b.len?b.v[i]:0))return 0;
  return 1;
}
int main(){
  Ten.v[2]=Ten.v[4]=1,Ten.len=4;
  Pow.v[1]=1;
  scanf("%d",&n);
  q0[0][t0[0]=1]=P(Big(),Num());
  for(i=1;;i++,o^=1,Pow=Pow*Ten){
    t0[o^1]=t1[o^1]=0;
    for(j=1;j<=t0[o];j++){
      x=q0[o][j].x,y=q0[o][j].y;
      if(check(i,x,y))q0[o^1][++t0[o^1]]=P(x,y);
      x.len=i,x.v[i]=1,y=y+Pow;
      if(check(i,x,y)){
        if(!(--n)){
          for(k=i;k;k--)putchar(x.v[k]+'0');
          return 0;
        }
        q1[o^1][++t1[o^1]]=P(x,y);
      }
    }
    for(j=1;j<=t1[o];j++){
      x=q1[o][j].x,y=q1[o][j].y;
      if(check(i,x,y))q0[o^1][++t0[o^1]]=P(x,y);
      x.len=i,x.v[i]=1,y=y+Pow;
      if(check(i,x,y)){
        if(!(--n)){
          for(k=i;k;k--)putchar(x.v[k]+'0');
          return 0;
        }
        q1[o^1][++t1[o^1]]=P(x,y);
      }
    }
  }
  return 0;
}