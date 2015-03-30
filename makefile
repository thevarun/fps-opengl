

room2:  room2.o loadImage.o objparser.o robotfigure.o readSCN.o objprimitive.h objprimitive.o  text3d.o
	g++  room2.o loadImage.o objparser.o readSCN.o objprimitive.o text3d.o robotfigure.o -o room2 -lGL -lglut -L /usr/lib -lhighgui

room2.o: room2.cpp  loadImage.h robotfigure.cpp objprimitive.h objparser.h readSCN.h
	g++ -c room2.cpp -o room2.o

loadImage.o: loadImage.cpp loadImage.h
	g++ -c loadImage.cpp -o loadImage.o

loadImage: loadImage.o
	g++ loadImage.o -o loadImage -L /usr/lib -lhighgui -lglut

objparser.o: objparser.cpp objparser.h
	g++ -c objparser.cpp

objparser: objparser.o
	g++ objparser.o -o objparser

readSCN.o: readSCN.cpp readSCN.h loadImage.h objparser.h objprimitive.h robotfigure.h enemy.h
	g++ -c readSCN.cpp -o readSCN.o

objprimitive.o: objprimitive.cpp objprimitive.h
	g++ -c objprimitive.cpp -o objprimitive.o

robotfigure.o: robotfigure.cpp robotfigure.h Particle.h
	g++ -c robotfigure.cpp -o robotfigure.o

text3d.o : text3d.cpp text3d.cpp
	g++ -c text3d.cpp -o text3d.o


