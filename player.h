#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "point.h"
using namespace std;

class Player{
    private:
        vector<vector<char> > board;
        vector<vector<char> > op_board;
        vector<Point > head;
        void update_b(Point p);
    public:
        Player();
        ~Player();
        vector<vector<char> > get_board();
        vector<vector<char> > get_op_board();
        void update_b(vector<vector<char> >, vector<Point> p);
        void update_op(Point p, char c);
        char being_bombed(Point p);
        bool check_end();
        void clear();
};

#endif        
