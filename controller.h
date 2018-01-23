#include "view.h"

using namespace std;

//class GameView;

class GameController{
    private:
        GameEngine *m;
        GameView v;
    public:
        GameController(GameEngine *m);
        ~GameController();
        void run();
};
