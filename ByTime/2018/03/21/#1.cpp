#include <queue>
#include <cstdio>
#include <algorithm>
#define Rep( i , _begin , _end ) for(int i=(_begin),i##_END=(_end);i<=(i##_END);i++)
#define For( i , _begin , _end ) for(int i=(_begin),i##_END=(_end);i!=(i##_END);i++)
#define Lop( i , _begin , _end ) for(int i=(_begin),i##_END=(_end);i>=(i##_END);i--)
#define Dnt( i , _begin , _end ) for(int i=(_begin),i##_END=(_end);i!=(i##_END);i--)
using std :: max;
using std :: min;
const int maxx = 2000 + 25;
const int maxm = 10000 + 25;
typedef std :: pair<int,int> iii;
std :: priority_queue<iii> quq;
int n,m,x,y,z,num,tot,cnt;
int idx[maxx],c[maxx],idx1[maxx],ans[maxx];
int head[maxm],nxt[maxm<<1],to[maxm<<1];
namespace top_sort{
    void Ins(int x,int y){
        to[++num] = y;nxt[num] = head[x];head[x] = num;
        idx[y] ++;
    }
    int Get(int x){
        while(!quq.empty()) quq.pop();
        Rep( i , 1 , n ) idx1[i] = idx[i];
        Rep( i , 1 , n ) if(i != x && !idx1[i]) quq.push(iii(c[i],i));
        Lop( i , n , 1 ){
            if(quq.empty()) return i;
            iii tmp = quq.top();quq.pop();
            if(tmp.first < i) return i;
            for(int k = head[tmp.second];k;k = nxt[k]){
                idx1[to[k]] --;
                if(to[k] != x && !idx1[to[k]]) quq.push(iii(c[to[k]],to[k]));
            }        
        }
    }
    void GG(){
        Rep( i , 1 , n ) idx1[i] = idx[i];
        Rep( i , 1 , n ) if(!idx1[i]) quq.push(iii(c[i],i));
        Lop( i , n , 1 ){
            iii tmp = quq.top();quq.pop();
            ans[i] = tmp.second;
            for(int k = head[tmp.second];k;k = nxt[k]){
                idx1[to[k]] --;
                if(!idx1[to[k]]) quq.push(iii(c[to[k]],to[k]));
            }
        }
    }
}
using namespace top_sort;
int main(){
    scanf("%d%d",&n,&m);
    Rep( i , 1 , n ) scanf("%d",&c[i]);
    while( m-- ){
        scanf("%d%d",&x,&y);
        Ins(y,x);
    }
    GG();
    Rep( i , 1 , n ) printf("%d ",ans[i]);
    putchar(10);
    Rep( i , 1 , n ) printf("%d ",Get(i));
    return 0;
}