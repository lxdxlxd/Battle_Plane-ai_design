#include "player.h"

using namespace std;


Player::Player(){
    vector<vector<char> > temp(10,vector<char> (10, '_'));
    board=temp;
    op_board=temp;
}

Player::~Player(){}


vector<vector<char> > Player::get_board(){
    return board;
}

vector<vector<char> > Player::get_op_board(){
    return op_board;
}

void Player::update_b(vector<vector<char> > b, vector<Point> p){
    board=b;
    head=p;
}

void Player::update_b(Point p){
    if(board[p.x][p.y]=='_'){
        board[p.x][p.y]='O';
    }
    else{
        board[p.x][p.y]='*';
    }
}


void Player::update_op(Point p, char feedback){
    switch(feedback){
        case 'E':
            op_board[p.x][p.y]='O';
            break;
        case 'H':
            op_board[p.x][p.y]='X';
            break;
        case 'D':
            op_board[p.x][p.y]='*';
            break;
    }
}

void Player::clear(){
    vector<vector<char> > temp(10,vector<char> (10, '_'));
    board=temp;
}




char Player::being_bombed(Point p){
    char temp=board[p.x][p.y];
    update_b(p);
    int i=is_in(head, p);
    if(temp=='X'&&i!=-1){
        head.erase(head.begin()+i);
        return 'D';
    }
    else if(temp=='X'&&i==-1){
        return 'H';
    }
    else{
        return 'E';
    }
}



bool Player::check_end(){
    return head.empty();
}

