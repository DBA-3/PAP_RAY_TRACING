CC=g++
OBJ=vector3f.o material.o ray3f.o camera.o quad.o sphere.o scene.o main.cpp

all: main

vector3f.o: vector3f.h
material.o: material.h
ray3f.o: ray3f.h
camera.o: camera.h
quad.o: quad.h
sphere.o: sphere.h
scene.o: scene.h

main: $(OBJ)
	$(CC) -o $@ $^ -lpng

clean:
	rm *.o main