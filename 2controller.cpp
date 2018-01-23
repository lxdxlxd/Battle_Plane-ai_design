#include "controller.h"
#include "point.h"
#include "view.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;


GameController::GameController(GameEngine *m): m(m), v(m){
}

GameController::~GameController() {
    delete m;
}


void GameController::run(){
    cout<<"Initializing..."<<endl;
    // init
    std::fstream in;
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
    /*
    m->possible_init();
    cout<<m->possible.size();
    std::fstream out;
    out.open("data.txt");
    for(const auto &i: m->possible){
        for(int j=0;j<3;++j){
            out<<i.first[j].x<<" "<<i.first[j].y<<" ";
        }
        out<<"   ";
        for(int j=0;j<3;++j){
            out.put(i.second[j]);
            out<<" ";
        }
        out<<endl;
    }
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
*/
    //m->ai_config();
    srand(time(NULL));
     pair<vector<Point>, vector<char> > p=*(std::next(m->possible.begin(), rand()%(m->possible.size())));
     m->init(p.first, p.second, 1, 0);
     m->init(p.first, p.second, 1, 1);
     m->init(p.first, p.second, 1, 2);

    int turn=2;
    vector<Point>p1, p2;
        int count=0;
        bool first=true;
        double pr=1;
        while(1){/*
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
        */
        
            //cout<<"Waiting for AI's turn..."<<endl;
            int x=0; int y=0;
            char temp;
            try{
                count++;
                temp=m->ai_bomb(x, y,pr,first);
                first=false;
                if(count==2)
                    pr=0;;
            }catch(char const *s){
            /*    
                cout<<"AI has bombed ("<<y<<", "<<(char)(x+65)<<")!"<<endl;
                cout<<"Destroyed!"<<endl;
                cout<<s<<endl;
                v.print_b(1); 
                v.print_b(2);
                v.print_op(1);
                v.print_op(2);
                cout<<"Game over!"<<endl;
             */ 
                fstream out;
                out.open("result3.txt", ios::out|ios::app);  
                out<<setw(4)<<count;
                return;
            }
            Point p (x, y);
            m->update_possible(p, temp);
            /*
            cout<<"AI has bombed ("<<y<<", "<<(char)(x+65)<<")!"<<endl;
            if(temp=='E')
                 cout<<"Empty!"<<endl; 
            else if(temp=='H')
                cout<<"Hit!"<<endl;
            else if(temp=='D')
                cout<<"Destroyed!"<<endl;
            v.print_b(1);
            */
        }
}

