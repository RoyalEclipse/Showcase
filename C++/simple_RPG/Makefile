novot118: main.o CMenu.o CGame.o CMap.o CRoom.o CActor.o CActorEnemySlime.o CActorEnemyZombie.o CActorItem.o CActorObstacle.o CActorPlayer.o CActorPlayerInventory.o CActorProjectile.o CItem.o
	g\+\+ -Wall --pedantic -g src/main.o src/CMenu.o src/CGame.o src/CMap.o src/CRoom.o src/CActor.o src/CActorEnemySlime.o src/CActorEnemyZombie.o src/CActorItem.o src/CActorObstacle.o src/CActorPlayer.o src/CActorPlayerInventory.o src/CActorProjectile.o src/CItem.o -lncurses -o  novot118

main.o: src/main.cpp src/CGame.hpp src/CActor.hpp src/CRoom.hpp \
 src/CActorEnemySlime.hpp src/CActorEnemyZombie.hpp src/CActorItem.hpp \
 src/CActorObstacle.hpp src/CActorPlayer.hpp \
 src/CActorPlayerInventory.hpp src/CItem.hpp src/CActorProjectile.hpp \
 src/CMenu.hpp src/CMap.hpp
	g\+\+ -Wall --pedantic -g -c src/main.cpp -lncurses -o ./src/main.o

CMenu.o: src/CMenu.cpp src/CMenu.hpp
	g\+\+ -Wall --pedantic -g -c src/CMenu.cpp -lncurses -o ./src/CMenu.o

CGame.o: src/CGame.cpp src/CGame.hpp src/CActor.hpp src/CRoom.hpp \
 src/CActorEnemySlime.hpp src/CActorEnemyZombie.hpp src/CActorItem.hpp \
 src/CActorObstacle.hpp src/CActorPlayer.hpp \
 src/CActorPlayerInventory.hpp src/CItem.hpp src/CActorProjectile.hpp \
 src/CMenu.hpp src/CMap.hpp
	g\+\+ -Wall --pedantic -g -c src/CGame.cpp -lncurses -o ./src/CGame.o

CMap.o: src/CMap.cpp src/CMap.hpp src/CRoom.hpp src/CActor.hpp src/CActorProjectile.hpp
	g\+\+ -Wall --pedantic -g -c src/CMap.cpp -lncurses -o ./src/CMap.o

CRoom.o: src/CRoom.cpp src/CRoom.hpp src/CActor.hpp
	g\+\+ -Wall --pedantic -g -c src/CRoom.cpp -o ./src/CRoom.o

CActor.o: src/CActor.cpp src/CActor.hpp src/CRoom.hpp
	g\+\+ -Wall --pedantic -g -c src/CActor.cpp -o ./src/CActor.o

CActorEnemySlime.o: src/CActorEnemySlime.cpp src/CActorEnemySlime.hpp \
 src/CActor.hpp src/CRoom.hpp
	g\+\+ -Wall --pedantic -g -c src/CActorEnemySlime.cpp -o ./src/CActorEnemySlime.o

CActorEnemyZombie.o: src/CActorEnemyZombie.cpp src/CActorEnemyZombie.hpp \
 src/CActor.hpp src/CRoom.hpp
	g\+\+ -Wall --pedantic -g -c src/CActorEnemyZombie.cpp -o ./src/CActorEnemyZombie.o

CActorObstacle.o: src/CActorObstacle.cpp src/CActorObstacle.hpp \
 src/CActor.hpp src/CRoom.hpp
	g\+\+ -Wall --pedantic -g -c src/CActorObstacle.cpp -o ./src/CActorObstacle.o

CActorItem.o: src/CActorItem.cpp src/CActorItem.hpp src/CActor.hpp \
 src/CRoom.hpp
	g\+\+ -Wall --pedantic -g -c src/CActorItem.cpp -o ./src/CActorItem.o

CActorPlayer.o: src/CActorPlayer.cpp src/CActorPlayer.hpp src/CActor.hpp \
 src/CRoom.hpp
	g\+\+ -Wall --pedantic -g -c src/CActorPlayer.cpp -o ./src/CActorPlayer.o

CActorPlayerInventory.o: src/CActorPlayerInventory.cpp \
 src/CActorPlayerInventory.hpp src/CActorPlayer.hpp src/CActor.hpp \
 src/CRoom.hpp src/CItem.hpp
	g\+\+ -Wall --pedantic -g -c src/CActorPlayerInventory.cpp -o ./src/CActorPlayerInventory.o

CActorProjectile.o: src/CActorProjectile.cpp src/CActorProjectile.hpp \
 src/CActor.hpp src/CRoom.hpp
	g\+\+ -Wall --pedantic -g -c src/CActorProjectile.cpp -o ./src/CActorProjectile.o

CItem.o: src/CItem.cpp src/CItem.hpp
	g\+\+ -Wall --pedantic -g -c src/CItem.cpp -o ./src/CItem.o

compile:
	make

all:
	make doc; make

doc: doc src/*.hpp
	doxygen 'Doxyfile'

run:
	./novot118

clean:
	rm -r src/*.o novot118 doc