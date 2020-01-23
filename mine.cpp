//清华大学机试2017年 扫雷
#include<cstdio>
#include<cstdlib>
#include <cstring>
#include<queue>
#include<algorithm>
using namespace std;
char m_map[1001][1001];
unsigned char m_status[1001][1001];
int m_bombs[1001][1001];
bool succ=false;
bool game_over=false;
enum{unflagged,swept,flagged};
//enum{undiscovered,discovered,visited};
struct node{
    int x;
    int y;
    int bombs;
    int type;
};
bool cmp(node a,node b){
    if(a.y!=b.y) return a.y<b.y;
    else{
        return a.x<b.x;
    }
}
int n,m;
int n_swept;
int total_bombs;
bool detect_bomb(int y,int x){
    if(y<=0||y>n||x<=0||x>m) return false;
    else{
        if(m_map[y][x]=='*') return true;
        else return false;
    }

}
bool detect_flag(int y,int x){
    if(y<=0||y>n||x<=0||x>m) return false;
    else{
        if(m_status[y][x]==flagged) return true;
        else return false;
    }

}


int count_neighbors(node& t,vector<node>& v,queue<node>& q){
    //int count=0;
    // t.y=s.y-1;t.x=s.x-1;
    if(t.x<=0||t.x>m||t.y<=0||t.y>n) return -1;
     int t_count=0;
     if(detect_bomb(t.y-1, t.x-1)) t_count++;
     if(detect_bomb(t.y, t.x-1)) t_count++;
     if(detect_bomb(t.y+1, t.x-1)) t_count++;
     if(detect_bomb(t.y-1, t.x)) t_count++;
     if(detect_bomb(t.y+1, t.x)) t_count++;
     if(detect_bomb(t.y-1, t.x+1)) t_count++;
     if(detect_bomb(t.y, t.x+1)) t_count++;
     if(detect_bomb(t.y+1, t.x+1)) t_count++;
     t.bombs=t_count;
    int status = (int)m_status[t.y][t.x];
    if(m_status[t.y][t.x]==unflagged)
    {
        n_swept++;
        v.push_back(t);
    }
    if(t_count==0&&m_status[t.y][t.x]==unflagged) {q.push(t); }
    m_status[t.y][t.x]=swept;

    m_bombs[t.y][t.x]=t_count;
    return t_count;
}
int count_flags(node t){
    //int count=0;
    // t.y=s.y-1;t.x=s.x-1;
    if(t.x<=0||t.x>m||t.y<=0||t.y>n) return -1;
     int t_count=0;
     if(detect_flag(t.y-1, t.x-1)) t_count++;
     if(detect_flag(t.y, t.x-1)) t_count++;
     if(detect_flag(t.y+1, t.x-1)) t_count++;
     if(detect_flag(t.y-1, t.x)) t_count++;
     if(detect_flag(t.y+1, t.x)) t_count++;
     if(detect_flag(t.y-1, t.x+1)) t_count++;
     if(detect_flag(t.y, t.x+1)) t_count++;
     if(detect_flag(t.y+1, t.x+1)) t_count++;
     return t_count;
}
bool detect(int y,int x,vector<node>& v){
    if(m_status[y][x]==flagged){
        return true;
    }
    else if(m_map[y][x]=='*'){
        //succ=false;
        game_over=true;
        return false;
    }

    queue<node> q;
    node s;
    s.y=y;
    s.x=x;
    //int count=0;
    count_neighbors(s, v, q);
    while(!q.empty()){
        s=q.front();
        q.pop();
        node t1;
        t1.y=s.y-1;
        t1.x=s.x-1;
        count_neighbors(t1, v, q);
        node t2;
        t2.y=s.y-1;
        t2.x=s.x;
        count_neighbors(t2, v, q);
        node t3;
        t3.y=s.y-1;
        t3.x=s.x+1;
        count_neighbors(t3, v, q);
        node t4;
        t4.y=s.y;
        t4.x=s.x-1;
        count_neighbors(t4, v, q);
        node t5;
        t5.y=s.y;
        t5.x=s.x+1;
        count_neighbors(t5, v, q);
        node t6;
        t6.y=s.y+1;
        t6.x=s.x-1;
        count_neighbors(t6, v, q);
        node t7;
        t7.y=s.y+1;
        t7.x=s.x;
        count_neighbors(t7, v, q);
        node t8;
        t8.y=s.y+1;
        t8.x=s.x+1;
        count_neighbors(t8, v, q);

    }
    return true;
}
int n_steps=0;
int main(){

    scanf("%d %d\n",&n,&m);
    char command[20];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%c",&m_map[i][j]);
            m_status[i][j]=unflagged;
            if(m_map[i][j]=='*') total_bombs++;
        }
        getchar();
    }
//    for(int i=1;i<=n;i++){
//        for(int j=1;j<=m;j++){
//            putchar(m_map[i][j]);
//        }
//        putchar('\n');
//
//
//    }

    while(scanf("%s ",command)!=-1){
        if(strcmp(command, "Quit")==0) break;
        int y,x;
        scanf("%d %d",&y,&x);
        n_steps++;
        if(strcmp(command,"Sweep")==0){
            if(m_status[y][x]==swept){
                printf("swept\n");
            }
            else if(m_status[y][x]==flagged){
                printf("flagged\n");
            }
            else if(m_status[y][x]==unflagged){
                if(m_map[y][x]=='*'){
                    printf("boom\n");
                    printf("game over\n");
                    printf("total step %d",n_steps);
                    succ=false;
                    break;
                }
                else if(m_map[y][x]=='.'){
                    vector<node> detected;
                    detect(y,x,detected);
                    //sort(detected,detected+detected.size(),cmp);
                    //sort(detected,detected+detected.size(),cmp);
                    sort(detected.begin(),detected.end(),cmp);
                    if(detected.size()>0){
                    printf("%d cell(s) detected\n",detected.size());
                    for(int i=0;i<detected.size();i++){
                        printf("%d %d %d\n",detected[i].y,detected[i].x,detected[i].bombs);
                    }
                    }
                    else{
                        printf("no cell detected\n");
                    }
                }
            }

        }
        else if(strcmp(command,"Flag")==0){
            if(m_status[y][x]==swept){
                printf("swept\n");
            }
            else if(m_status[y][x]==unflagged){

                m_status[y][x]=flagged;
                printf("success\n");
            }
            else if(m_status[y][x]==flagged){
                m_status[y][x]=unflagged;
                printf("cancelled\n");
            }
        }
        else if(strcmp(command, "DSweep")==0){
            if(m_status[y][x]!=swept){
                printf("not swept\n");
            }
            else{
                vector<node> v;
                queue<node> q;
                node s;
                s.x=x;
                s.y=y;
                int s_count=count_flags(s);
                if(s_count==m_bombs[s.y][s.x]){
                   vector<node> detected;
                    detect(y-1, x-1, detected);
                    detect(y-1, x, detected);
                    detect(y-1, x+1, detected);
                    detect(y, x-1, detected);
                    detect(y, x+1, detected);
                    detect(y+1, x-1, detected);
                    detect(y+1, x, detected);
                    detect(y+1, x+1, detected);
                    if(game_over==false){
//                    sort(detected.begin(),detected.end(),cmp);
//                    printf("%d cell(s) detected\n",detected.size());
                        if(detected.size()>0){
                        sort(detected.begin(),detected.end(),cmp);
                        printf("%d cell(s) detected\n",detected.size());
                        for(int i=0;i<detected.size();i++){
                            printf("%d %d %d\n",detected[i].y,detected[i].x,detected[i].bombs);}
                        }
                        else{
                            printf("no cell detected\n");
                        }
                    }
                    else{
                        printf("bomb\n");
                        printf("game over\n");
                        printf("total step %d",n_steps);
                    }
                }
                else{
                    printf("failed\n");
                }

            }
        }
        if((n*m-total_bombs)==n_swept){
            printf("finish\n");
            printf("total step %d\n",n_steps);
            break;
        }
    }
}

