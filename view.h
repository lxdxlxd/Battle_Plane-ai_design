#ifndef VIEW_H
#define VIEW_H

#include "model.h"

using namespace std;

class GameView{
    private:
        GameEngine *m;
    public:
        GameView(GameEngine *m);
        ~GameView();
        void print_b(int p_num);
        void print_op(int p_num);
        void print_blank();
};

#endif
