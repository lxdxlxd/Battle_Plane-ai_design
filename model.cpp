#include "model.h"
#include <ctime>
#include <iostream>
#include <algorithm>
#include <assert.h>

GameEngine::GameEngine(): player1(), player2(),head_count(vector<vector<int> >(10, vector<int>(10,0))), body_count(vector<vector<int> >(10, vector<int>(10,0))) {}

GameEngine::~GameEngine() {}

vector<vector<char> > GameEngine::get_board(int p_num){
    return p_num==1?player1.get_board():player2.get_board();
}

vector<vector<char> > GameEngine::get_op(int p_num){
    return p_num==1?player1.get_op_board():player2.get_op_board();
}


void GameEngine::clear(int p_num){
    if(p_num==1)
        player1.clear();
    else 
        player2.clear();
}

bool GameEngine::init(vector<Point> p, vector<char> dir, int p_num, int n){
    vector<vector<char> >temp=p_num==1?player1.get_board():player2.get_board();
        if(dir[n]=='D'){
            if(p[n].x<2||p[n].x>7||p[n].y<3)
                return false;
            for(int i=p[n].x-2; i<=p[n].x+2 ;++i){
                if(temp[i][p[n].y-1]=='X') return false;
                temp[i][p[n].y-1]='X';
            }
            if(temp[p[n].x][p[n].y]=='X'||temp[p[n].x][p[n].y-2]=='X'||temp[p[n].x][p[n].y-3]=='X'||temp[p[n].x-1][p[n].y-3]=='X'||temp[p[n].x+1][p[n].y-3]=='X')
                return false;
            temp[p[n].x][p[n].y]='X';
            temp[p[n].x][p[n].y-2]='X';
            temp[p[n].x][p[n].y-3]='X';
            temp[p[n].x-1][p[n].y-3]='X';
            temp[p[n].x+1][p[n].y-3]='X';
        }
        else if(dir[n]=='U'){
            if(p[n].x<2||p[n].x>7||p[n].y>6)
                return false;
            for(int i=p[n].x-2; i<=p[n].x+2 ;++i){
                if(temp[i][p[n].y+1]=='X') return false;
                temp[i][p[n].y+1]='X';
            }
            if(temp[p[n].x][p[n].y]=='X'||temp[p[n].x][p[n].y+2]=='X'||temp[p[n].x][p[n].y+3]=='X'||temp[p[n].x-1][p[n].y+3]=='X'||temp[p[n].x+1][p[n].y+3]=='X')
                return false;
            temp[p[n].x][p[n].y]='X';
            temp[p[n].x][p[n].y+2]='X';
            temp[p[n].x][p[n].y+3]='X';
            temp[p[n].x-1][p[n].y+3]='X';
            temp[p[n].x+1][p[n].y+3]='X';
        }    
        else if(dir[n]=='L'){
            if(p[n].y<2||p[n].y>7||p[n].x>6)
                return false;
            for(int i=p[n].y-2; i<=p[n].y+2 ;++i){
                if(temp[p[n].x+1][i]=='X') return false;
                temp[p[n].x+1][i]='X';
            }
            if(temp[p[n].x][p[n].y]=='X'||temp[p[n].x+2][p[n].y]=='X'||temp[p[n].x+3][p[n].y]=='X'||temp[p[n].x+3][p[n].y-1]=='X'||temp[p[n].x+3][p[n].y+1]=='X')
                return false;
            temp[p[n].x][p[n].y]='X';
            temp[p[n].x+2][p[n].y]='X';
            temp[p[n].x+3][p[n].y]='X';
            temp[p[n].x+3][p[n].y-1]='X';
            temp[p[n].x+3][p[n].y+1]='X';
        }
        else if(dir[n]=='R'){
            if(p[n].y<2||p[n].y>7||p[n].x<3)
                return false;
            for(int i=p[n].y-2; i<=p[n].y+2 ;++i){
                if(temp[p[n].x-1][i]=='X') return false;
                temp[p[n].x-1][i]='X';
            }
            if(temp[p[n].x][p[n].y]=='X'||temp[p[n].x-2][p[n].y]=='X'||temp[p[n].x-3][p[n].y]=='X'||temp[p[n].x-3][p[n].y-1]=='X'||temp[p[n].x-3][p[n].y+1]=='X')
                return false;
            temp[p[n].x][p[n].y]='X';
            temp[p[n].x-2][p[n].y]='X';
            temp[p[n].x-3][p[n].y]='X';
            temp[p[n].x-3][p[n].y-1]='X';
            temp[p[n].x-3][p[n].y+1]='X';
        }
    if(p_num==1)
        player1.update_b(temp,p);
    else
        player2.update_b(temp,p);
    return true;

}

char GameEngine::bomb(Point p, int p_num){    
    if(p_num==1){
        char temp= player1.being_bombed(p);
        switch(temp){
            case 'E':
                player2.update_op(p, 'E');
                return 'E';
            case 'H':
                player2.update_op(p, 'H');
                return 'H';
            case 'D':
                player2.update_op(p, 'D');
                if(player1.check_end())
                    throw "Player2 wins!";
                return 'D';
        }
    }
    else{
        char temp= player2.being_bombed(p);
        switch(temp){
            case 'E':
                player1.update_op(p, 'E');
                return 'E';
            case 'H':
                player1.update_op(p, 'H');
                return 'H';
            case 'D':
                player1.update_op(p, 'D');
                if(player2.check_end())
                    throw "Player1 wins!";                
                return 'D';
        }
    } 
}




void  GameEngine::store(vector<Point> v_p, vector<char> v_dir){
    if(v_p[0]< v_p[2]&&v_p[2]<v_p[1]){
        std::swap(v_p[1],v_p[2]);
        std::swap(v_dir[1],v_dir[2]);
    }
    else if(v_p[1]< v_p[0]&&v_p[0]< v_p[2]){
        std::swap(v_p[0],v_p[1]);
        std::swap(v_dir[0],v_dir[1]);
    }
    else if(v_p[1]< v_p[2]&&v_p[2]< v_p[0]){
        std::swap(v_p[0],v_p[2]);
        std::swap(v_dir[0],v_dir[2]);
        std::swap(v_p[0],v_p[1]);
        std::swap(v_dir[0], v_dir[1]);
    }else if(v_p[2]< v_p[0]&&v_p[0]< v_p[1]){
        std::swap(v_p[0],v_p[2]);
        std::swap(v_dir[0],v_dir[2]);
        std::swap(v_p[2],v_p[1]);
        std::swap(v_dir[2],v_dir[1]);
    }else if(v_p[2]< v_p[1]&&v_p[1]< v_p[0]){
        std::swap(v_p[0],v_p[2]);
        std::swap(v_dir[0],v_dir[2]);
    }
    else if(v_p[0]< v_p[1]&&v_p[1]< v_p[2]){
    }
    else{ assert(0);}
    /*
    for(int i=0;i<possible.size();++i){
        if(v_p==possible[i].first&&v_dir==possible[i].second)
            return;
    }
    */
    pair<vector<Point>, vector<char> > temp(v_p, v_dir);
    if(possible.insert(temp).second){
        head_count[v_p[0].y][v_p[0].x]++;
        head_count[v_p[1].y][v_p[1].x]++;
        head_count[v_p[2].y][v_p[2].x]++;
        for(int n=0;n<3;++n){
            Point head=v_p[n];
            char dir=v_dir[n];
            if(dir=='U'){
               body_count[head.y+1] [head.x-2]++;
               body_count[head.y+1] [head.x-1]++;
               body_count[head.y+1] [head.x]++;
               body_count[head.y+1] [head.x+1]++;
               body_count[head.y+1] [head.x+2]++;
               body_count[head.y+2] [head.x]++;
               body_count[head.y+3] [head.x]++;
               body_count[head.y+3] [head.x-1]++;
               body_count[head.y+3] [head.x+1]++;
            }
            else if(dir=='D'){
               body_count[head.y-1] [head.x-2]++;
               body_count[head.y-1] [head.x-1]++;
               body_count[head.y-1] [head.x]++;
               body_count[head.y-1] [head.x+1]++;
               body_count[head.y-1] [head.x+2]++;
               body_count[head.y-2] [head.x]++;
               body_count[head.y-3] [head.x]++;
               body_count[head.y-3] [head.x-1]++;
               body_count[head.y-3] [head.x+1]++;
            }
            else if(dir=='L'){
               body_count[head.y-2] [head.x+1]++;
               body_count[head.y-1] [head.x+1]++;
               body_count[head.y ] [head.x+1]++;
               body_count[head.y+1] [head.x+1]++;
               body_count[head.y+2] [head.x+1]++;
               body_count[head.y ] [head.x+2]++;
               body_count[head.y ] [head.x+3]++;
               body_count[head.y-1] [head.x+3]++;
               body_count[head.y+1] [head.x+3]++;
            }
            else if(dir=='R'){
               body_count[head.y-2] [head.x-1]++;
               body_count[head.y-1] [head.x-1]++;
               body_count[head.y ] [head.x-1]++;
               body_count[head.y+1] [head.x-1]++;
               body_count[head.y+2] [head.x-1]++;
               body_count[head.y ] [head.x-2]++;
               body_count[head.y ] [head.x-3]++;
               body_count[head.y-1] [head.x-3]++;
               body_count[head.y+1] [head.x-3]++;
            }
        }
    }
}



void GameEngine::possible_init(){
    char dir_arr[4]={'U', 'D', 'L','R'};
    char c1,c2,c3;
    vector<Point > v_p; vector<char> v_dir;
    for(int i1=0;i1<10;++i1){
        for(int j1=0;j1<10;++j1){
            if(i1<2&&j1<2||i1>7&&j1<2||i1<2&&j1>7||i1>7&&j1>7)
                continue;
            for(int k1=0;k1<4;++k1){
                c1=dir_arr[k1];
                Point p1(i1,j1);
                v_p.push_back(p1);
                v_dir.push_back(c1);
                if(!init(v_p, v_dir, 1, 0)){
                    v_p.erase(v_p.begin());
                    v_dir.erase(v_dir.begin());
                    if(k1==3)
                        goto cntj1;
                    continue;
                }
                for(int i2=0;i2<10;++i2){
                    for(int j2=0;j2<10;++j2){
                        if(i2<2&&j2<2||i2>7&&j2<2||i2<2&&j2>7||i2>7&&j2>7)
                            continue;
                        for(int k2=0;k2<4;++k2){
                            c2=dir_arr[k2];
                            Point p2(i2,j2);
                            v_p.push_back(p2);
                            v_dir.push_back(c2);
                            if(!init(v_p, v_dir, 1, 1)){
                                v_p.erase(v_p.begin()+1);
                                v_dir.erase(v_dir.begin()+1);
                                if(k2==3)
                                    goto cntj2;
                                continue;
                            }
                            for(int i3=0;i3<10;++i3){
                                for(int j3=0;j3<10;++j3){
                                    if(i3<2&&j3<2||i3>7&&j3<2||i3<2&&j3>7||i3>7&&j3>7)
                                        continue;
                                    for(int k3=0;k3<4;++k3){
                                        c3=dir_arr[k3];
                                        Point p3(i3,j3); 
                                        v_p.push_back(p3);
                                        v_dir.push_back(c3);
                                        if(init(v_p, v_dir, 1, 2)){
                                            //v.print_b(1);
                                            store(v_p, v_dir);
                                            clear(1);
                                            init(v_p, v_dir, 1, 0);
                                            init(v_p, v_dir, 1, 1);
                                        }
                                        v_p.erase(v_p.begin()+2);
                                        v_dir.erase(v_dir.begin()+2);
                                    }
                                }
                            }
                            clear(1);
                            init(v_p, v_dir, 1, 0);
                            v_p.erase(v_p.begin()+1);
                            v_dir.erase(v_dir.begin()+1);
                        }
cntj2:;
                    }
                }
                clear(1);
                v_p.erase(v_p.begin()+0);
                v_dir.erase(v_dir.begin()+0);
            }
cntj1:;
        }
      }
}

void GameEngine::update_possible(Point p, char result){
    for(auto it=possible.begin() ;it!=possible.end();){
        char possible_result='E';
        for(int n=0;n<3;++n){
            Point head=(*it).first[n];
            if(head==p){
                possible_result='D';
                break;
            }
            char dir=(*it).second[n];
            if(dir=='U'){
               Point p1(head.x-2, head.y+1);
               Point p2(head.x-1, head.y+1);
               Point p3(head.x, head.y+1);
               Point p4(head.x+1, head.y+1);
               Point p5(head.x+2, head.y+1);
               Point p6(head.x, head.y+2);
               Point p7(head.x, head.y+3);
               Point p8(head.x-1, head.y+3);
               Point p9(head.x+1, head.y+3);
               if(p==p1||p==p2||p==p3||p==p4||p==p5||p==p6||p==p7||p==p8||p==p9){
                   possible_result='H';
                   break;
               }
            }
            else if(dir=='D'){
               Point p1(head.x-2, head.y-1);
               Point p2(head.x-1, head.y-1);
               Point p3(head.x, head.y-1);
               Point p4(head.x+1, head.y-1);
               Point p5(head.x+2, head.y-1);
               Point p6(head.x, head.y-2);
               Point p7(head.x, head.y-3);
               Point p8(head.x-1, head.y-3);
               Point p9(head.x+1, head.y-3);
               if(p==p1||p==p2||p==p3||p==p4||p==p5||p==p6||p==p7||p==p8||p==p9){
                   possible_result='H';
                   break;
               }
            }
            else if(dir=='L'){
               Point p1(head.x+1, head.y-2);
               Point p2(head.x+1, head.y-1);
               Point p3(head.x+1, head.y);
               Point p4(head.x+1, head.y+1);
               Point p5(head.x+1, head.y+2);
               Point p6(head.x+2, head.y);
               Point p7(head.x+3, head.y);
               Point p8(head.x+3, head.y-1);
               Point p9(head.x+3, head.y+1);
               if(p==p1||p==p2||p==p3||p==p4||p==p5||p==p6||p==p7||p==p8||p==p9){
                   possible_result='H';
                   break;
               }
            }
            else if(dir=='R'){
               Point p1(head.x-1, head.y-2);
               Point p2(head.x-1, head.y-1);
               Point p3(head.x-1, head.y);
               Point p4(head.x-1, head.y+1);
               Point p5(head.x-1, head.y+2);
               Point p6(head.x-2, head.y);
               Point p7(head.x-3, head.y);
               Point p8(head.x-3, head.y-1);
               Point p9(head.x-3, head.y+1);
               if(p==p1||p==p2||p==p3||p==p4||p==p5||p==p6||p==p7||p==p8||p==p9){
                   possible_result='H';
                   break;
               }
            }
        }
        if(possible_result!=result){
            for(int n=0;n<3;++n){
                int x=(*it).first[n].x; int y= (*it).first[n].y;
                char dir=(*it).second[n];
                head_count[y][x]--;
                if(head_count==vector<vector<int> > (10, vector<int> (10, 0))) {
                    // assert(0);
                }
                if(dir=='U'){
                    body_count[y+1] [x-2]--;
                    body_count[y+1] [x-1]--;
                    body_count[y+1] [x]--;
                    body_count[y+1] [x+1]--;
                    body_count[y+1] [x+2]--;
                    body_count[y+2] [x]--;
                    body_count[y+3] [x]--;
                    body_count[y+3] [x-1]--;
                    body_count[y+3] [x+1]--;
                }
                else if(dir=='D'){
                    body_count[y-1] [x-2]--;
                    body_count[y-1] [x-1]--;
                    body_count[y-1] [x]--;
                    body_count[y-1] [x+1]--;
                    body_count[y-1] [x+2]--;
                    body_count[y-2] [x]--;
                    body_count[y-3] [x]--;
                    body_count[y-3] [x-1]--;
                    body_count[y-3] [x+1]--;
                 }
                 else if(dir=='L'){
                    body_count[y-2] [x+1]--;
                    body_count[y-1] [x+1]--;
                    body_count[y ]  [x+1]--;
                    body_count[y+1] [x+1]--;
                    body_count[y+2] [x+1]--;
                    body_count[y ]  [x+2]--;
                    body_count[y ]  [x+3]--;
                    body_count[y-1] [x+3]--;
                    body_count[y+1] [x+3]--;
                 }
                 else if(dir=='R'){
                    body_count[y-2] [x-1]--;
                    body_count[y-1] [x-1]--;
                    body_count[y ]  [x-1]--;
                    body_count[y+1] [x-1]--;
                    body_count[y+2] [x-1]--;
                    body_count[y ]  [x-2]--;
                    body_count[y ]  [x-3]--;
                    body_count[y-1] [x-3]--;
                    body_count[y+1] [x-3]--;
                 }
            }
            it=possible.erase(it);
        }
       else
           ++it;
    }
}


char GameEngine::ai_bomb(int &x, int &y, double p, bool first){
    srand(time(NULL));
    if(first){
        int rnd=rand()%4;
        if(rnd==0){
            x=3, y=3;
            ai_bombed_p.push_back(Point(3,3));
            return bomb(Point(3,3), 1);
        }
        else if(rnd==1){
            x=3, y=6;
            ai_bombed_p.push_back(Point(3,6));
            return bomb(Point(3,6), 1);
        }
        else if(rnd==2){
            x=6, y=3;
            ai_bombed_p.push_back(Point(6,3));
            return bomb(Point(6,3), 1);
        }
        else if(rnd==3){
            x=y=6;
            ai_bombed_p.push_back(Point(6,6));
            return bomb(Point(6,6), 1);
        }
    }

    srand(time(NULL));
    double val=(double)rand()/RAND_MAX;
    if(val<p){
        int max_u=0;
        unordered_set<pair<vector<Point>, vector<char> > ,SimpleHash> temp(possible);
        vector<vector<int> > temp_head(head_count);
        vector<vector<int> > temp_body(body_count);
        int head_sum=0; int body_sum=0;
        for(int i=0; i<10; ++i){
            for(int j=0; j<10; ++j){
                head_sum+=head_count[i][j];
                body_sum+=body_count[i][j];
            }
        }
        int max_utility=0;
        vector<vector<int> > utility_list (vector<vector<int> >(10, vector<int>(10,0)));
        for(int i=0;i<10;++i){
            for(int j=0;j<10;++j){
                Point p(j, i);
                if(i==0&&j==0||i==9&&j==9||i==0&&j==9||i==9&&j==0||is_in(ai_bombed_p, p)!=-1)
                    continue;
                int utility=0;
                update_possible(p,'D');
                head_count=temp_head;
                body_count=temp_body;
                utility+=head_count[i][j]/head_sum * (temp.size()-possible.size());
                possible=temp;
                update_possible(p,'H');
                head_count=temp_head;
                body_count=temp_body;
                utility+=body_count[i][j]/body_sum * (temp.size()-possible.size());
                possible=temp;
                update_possible(p,'E');
                head_count=temp_head;
                body_count=temp_body;
                utility+=(1-head_count[i][j]/head_sum -body_count[i][j]/body_sum)* (temp.size()-possible.size());
                possible=temp;
                if(utility>max_utility){
                    max_utility=utility;
                }
                utility_list[i][j]=utility;   
            }
        }
        int sum_weight=0;
        for(int i=0;i<10;++i){
            for(int j=0;j<10;++j){
                if(utility_list[i][j]==max_utility)
                    sum_weight++;
            }
        }
        srand(time(NULL));
        int rnd=rand()%sum_weight;
        for(int i=0;i<10;++i){
            for(int j=0;j<10;++j){
                if(utility_list[i][j]!=max_utility)
                    continue;
                if(rnd<max_utility){
                    x=j, y=i;
                    ai_bombed_p.push_back(Point(x, y));
                    return bomb(Point(x ,y),1);
                }
                rnd-=max_utility;
            }
        }
        assert(0);
    }
    int max_p=0;
    for(int j=0; j<10;++j){
        for(int i=0; i<10;++i){
            if(is_in(ai_bombed_p, Point(i,j))==-1&&head_count[j][i]>max_p){
                max_p=head_count[j][i];
            }
        }
    }
    int sum_max=0;
    for(int j=0;j<10;++j){
        for(int i=0;i<10;++i){
            if(head_count[j][i]==max_p&&is_in(ai_bombed_p, Point(i,j))==-1)
                sum_max+=head_count[j][i];
        }
    }
    srand(time(NULL));
    int rnd = rand()%sum_max;
    for(int j=0;j<10;++j){
        for(int i=0; i<10;++i){
            if(head_count[j][i]!=max_p||is_in(ai_bombed_p, Point(i,j))!=-1)
                continue;
            if(rnd<max_p){
                x=i, y=j;
                ai_bombed_p.push_back(Point(x, y));
                return bomb(Point(x ,y),1);
            }
            rnd-=max_p;
        }
    }
    assert(0);

    /*
    int sum_weight=0;
    for(int j=0;j<10;++j){
        for(int i=0;i<10;++i){
            Point temp(i, j);
            if(is_in(ai_bombed_p, temp)==-1)
                sum_weight+=head_count[j][i];
        }
    }
    srand(time(NULL));
    int rnd = rand()%sum_weight;
    for(y=0; y<10; ++y) { 
        for(x=0;x<10;++x){
            Point temp(x, y);
            if(head_count[y][x]==0||is_in(ai_bombed_p, temp)!=-1)
                continue;
            if(rnd < head_count[y][x]){
                ai_bombed_p.push_back(temp);
                return bomb(temp, 1);
            }
            rnd -= head_count[y][x];
        }
    }
    assert(0);
    */
}
    

void GameEngine::ai_config(){
    srand(time(NULL));
    pair<vector<Point>, vector<char> > p=*(std::next(possible.begin(), rand()%possible.size()));
    init(p.first, p.second, 2, 0);
    init(p.first, p.second, 2, 1);
    init(p.first, p.second, 2, 2);
}

