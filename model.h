#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include <cstdlib>
#include "player.h"
#include "point.h"
#include <unordered_set>
using namespace std;


struct SimpleHash {
    size_t operator()(const std::pair<vector<Point>, vector<char> >& pr) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (Point p : (pr.first)) {
            seed ^= hasher(p.x) +hasher(p.y)+ 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};


class GameEngine{
    private:
        Player player1, player2;
        //vector<pair<vector<Point>, vector<char> > > possible;
        vector<vector<int> > head_count;
        //vector<vector<int> > body_count;
        vector<Point> ai_bombed_p;
   public:
        GameEngine();
        ~GameEngine();
        vector<vector<int> > body_count;
        unordered_set<pair<vector<Point>, vector<char> > ,SimpleHash> possible;
        void store(vector<Point>, vector<char>);
        vector<vector<char> > get_board(int p_num);
        vector<vector<char> > get_op(int p_num);
        bool init(vector<Point> p, vector<char> dir, int p_num, int n);
        void clear(int p_num);
        char bomb(Point p, int p_num);
        void possible_init();
        void update_possible(Point, char);
        void ai_config();
        char ai_bomb(int &, int &, double p, bool first);
};

#endif
