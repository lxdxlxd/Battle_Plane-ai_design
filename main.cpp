#include "model.h"
#include "controller.h"
#include "view.h"
#include <iostream>
int main(){
    for(int i=0;i<10000;++i){
   GameEngine *m=new GameEngine();
   GameController c(m);
   c.run();
   std::cout<<i<<std::endl;
    }
}
