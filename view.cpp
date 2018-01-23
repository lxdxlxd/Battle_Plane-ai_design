#include "view.h"
#include <iostream>

using namespace std;

GameView::GameView(GameEngine *m): m(m) {}

GameView::~GameView() {}



void GameView::print_b(int p_num){
    vector<vector<char> > temp=p_num==1?m->get_board(1):m->get_board(2);
    if(p_num==1)
        cout<<"Your board:"<<endl;
    else
        cout<<"AI's board:"<<endl;
    cout<< "   A B C D E F G H I J"<< endl;
    cout <<"   ___________________ "<< endl;
    for (int i = 0; i < 10; i++) {
        cout << " " << i << "|" << temp[0][i]<<"|";
        for (int j = 1; j < 10; j++) {
            cout  << temp[j][i]<<"|";
        }
        cout << endl;
    }
    /*
    for(int i=0;i<temp.size();++i){
        for(int j=0;j<temp[i].size();++j){
            cout<<temp[j][i];
        }
        cout<<endl;
    }
    */
}


void GameView::print_op(int p_num){
    if(p_num==1)
        cout<<"Your feedback board:"<<endl;
    else
        cout<<"AI's feedback board:"<<endl;
    vector<vector<char> >temp=p_num==1?m->get_op(1):m->get_op(2);
    cout<< "   A B C D E F G H I J"<< endl;
    cout <<"   ___________________ "<< endl;
    for (int i = 0; i < 10; i++) {
        cout << " " << i << "|" << temp[0][i]<<"|";
        for (int j = 1; j < 10; j++) {
            cout  << temp[j][i]<<"|";
        }
        cout << endl;
    }
}


void GameView::print_blank(){
    cout<<"Blank board:"<<endl;
    cout<< "   A B C D E F G H I J"<< endl;
    cout <<"   ___________________ "<< endl;
    for (int i = 0; i < 10; i++) {
        cout << " " << i << "|" << '_'<<"|";
        for (int j = 1; j < 10; j++) {
            cout  << '_'<<"|";
        }
        cout << endl;
    }
}


