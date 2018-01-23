#include "controller.h"
#include "point.h"
#include "view.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <map>

using namespace std;


GameController::GameController(GameEngine *m): m(m), v(m){
}

GameController::~GameController() {
    delete m;
}


void GameController::run(int i){
   cout<<"Initializing..."<<endl;
   // m->possible_init();
   // init
   fstream in;
   in.open("data.txt");
    while(1){
        int i1, j1, i2,j2, i3, j3; char c1, c2 ,c3;
        if(!(in>>i1)) break;
        in>>j1>>i2>>j2>>i3>>j3; in>>c1>>c2>>c3;
        vector<Point> v_p; vector<char> v_dir;
        v_p.push_back(Point(i1,j1));
        v_p.push_back(Point(i2,j2));
        v_p.push_back(Point(i3,j3));
        v_dir.push_back(c1);
        v_dir.push_back(c2);
        v_dir.push_back(c3);
        m->store(v_p, v_dir);
    }
    int sum=0;
    for(const auto &i: m->body_count){
        for(const auto &j: i){
            cout<<j<<" ";
            sum+=j;
        }
        cout<<endl;
    }
    cout<<sum;
   cout<<"Game starts!"<<endl;
   while(1){
       cout<<"Please enter your configuration:"<<endl;
       v.print_blank();
       int i, j; char c, col;
       vector<Point > v_p; vector<char> v_dir;
       for(int n=1;n<=3;++n){
           cout<<"Enter plane"<<n<<":"<<endl;
           cin>>j>>col>>c;
           i=col-65;
           if((c!='U'&&c!='D'&&c!='L'&&c!='R')||i<0||i>9||j<0||j>9) {cout<<"Error input!"<<endl; n--; continue; }
           Point p(i, j);
           v_p.push_back(p); v_dir.push_back(c);
           if(m->init(v_p, v_dir, 1, n-1)){
               v.print_b(1);
           }
           else{
               cout<<"Error input!"<<endl; 
               n--;
               v_p.erase(v_p.begin()+n);
               v_dir.erase(v_dir.begin()+n);
               continue; 
           }
       }
       while(1){
           cout<<"To continue tap [Y], to draw again tap [D]."<<endl;
           char temp; cin>>temp;
           if(temp=='Y')
               goto end1;
           else if(temp=='D'){
               m->clear(1);
               break;
           }
           else
               cout<<"Error input!"<<endl;
       }
   }
end1:;
    m->ai_config();
    int turn=1;
    vector<Point>p1, p2;
    int count=0;
    bool first=true;
    while(1){
        if(turn==1){
            cout<<"Your turn:"<<endl;
            v.print_op(turn);
            int i, j; char col;
            while(1){
                cout<<"Please bomb!"<<endl;
                cin>>j>>col; i=col-65;
                if(i<0||i>9||j<0||j>9){ cout<<"Error input!"<<endl; continue; }
                Point temp(i, j);
                if(is_in(p1, temp)!=-1) {cout<<"Point has been bombed!"<<endl; continue;}
                break;
            }
            Point p(i, j);
            p1.push_back(p);
            char temp;
            try{
                temp =m->bomb(p, 2);
            }catch(char const *s){
                cout<<"Destroyed!"<<endl;
                cout<<s<<endl;
                v.print_b(1); 
                v.print_b(2);
                v.print_op(1);
                v.print_op(2);
                cout<<"Game over!"<<endl;
                return;
            }
            if(temp=='E')
                cout<<"Empty!"<<endl;
            else if(temp=='H')
                cout<<"Hit!"<<endl;
            else if(temp=='D')
                cout<<"Destroyed!"<<endl;
        }
        else{
            cout<<"Waiting for AI's turn..."<<endl;
            count++;
            int x=0; int y=0;
            char temp;
            try{
                temp=m->ai_bomb(x, y, 0.5, first);
                first=false;
            }catch(char const *s){
                /*
                cout<<"Possibilities: "<<m->possible.size()<<endl;
                for(auto it=m->possible.begin();it!=m->possible.end();++it){
                    cout<<(*it).first[0].x<<" "<<(*it).first[0].y<<" ";
                    cout.put((*it).second[0])<<endl;
                    cout<<(*it).first[1].x<<" "<<(*it).first[1].y<<" ";
                    cout.put((*it).second[1])<<endl;
                    cout<<(*it).first[2].x<<" "<<(*it).first[2].y<<" ";
                    cout.put((*it).second[2])<<endl;
                }
                */
                cout<<"AI has bombed ("<<y<<", "<<(char)(x+65)<<")!"<<endl;
                cout<<"Destroyed!"<<endl;
                cout<<s<<endl;
                v.print_b(1); 
                v.print_b(2);
                v.print_op(1);
                v.print_op(2);
                cout<<"Game over!"<<endl;
                cout<<"Total turns: "<<count<<endl;
                return;
            }
            Point p (x, y);
            m->update_possible(p, temp);
            cout<<"Possibilities: "<<m->possible.size()<<endl;
            cout<<"AI has bombed ("<<y<<", "<<(char)(x+65)<<")!"<<endl;
            if(temp=='E')
                 cout<<"Empty!"<<endl; 
            else if(temp=='H')
                cout<<"Hit!"<<endl;
            else if(temp=='D')
                cout<<"Destroyed!"<<endl;
            v.print_b(1);
        }
        turn=3-turn;
    }
}

