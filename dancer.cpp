
//清华大学机试 2017年 舞蹈团
#include<cstdio>
#include<cstdlib>
using namespace std;
//int height[100001];
int dancers[100001];
int picks[100001];
int main(){
    int n,m,k;
    while(scanf("%d %d %d\n",&n,&m,&k)!=-1){
        for(int i=1;i<=n;i++){
            scanf("%d ",&dancers[i]);
        }
        for(int i=0;i<=n;i++){
            picks[i]=0;
        }
       // int max_gap=-1;
        //int picked=0;
        int i=1;
        bool flag=false;
        for(;i<=n;i++){
            int curr_height=dancers[i];

            int maxp=0,maxq=0;
            for(int j=i-1;j>=0;j--){
                if(picks[j]>maxp) maxp=picks[j];
                if(dancers[j]<=curr_height+k&&dancers[j]>=curr_height-k&&maxq<picks[j]) maxq=picks[j];
            }
            if(maxq+1>maxp) picks[i]=maxq+1;
            else picks[i]=maxp;
            if(picks[i]>=m){
                flag=true;
                break;
            }
        }
        if(flag){
            printf("%d\n",i);
        }
        else{
            printf("impossible\n");
        }
    }
}
