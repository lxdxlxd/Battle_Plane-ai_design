PROG = battle_plane
CC = g++
CPPFLAGS = -g -std=c++11
OBJS = main.o controller.o model.o view.o player.o
$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)
main.o :
	$(CC) $(CPPFLAGS) -c main.cpp
controller.o: controller.h
	$(CC) $(CPPFLAGS) -c controller.cpp
model.o: model.h
	$(CC) $(CPPFLAGS) -c model.cpp
player.o: player.h
	$(CC) $(CPPFLAGS) -c player.cpp
view.o: view.h
	$(CC) $(CPPFLAGS) -c view.cpp
clean:
	rm -f core $(PROG) $(OBJS)
