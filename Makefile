#!/bin/bash

FLAGG	=	`sdl2-config --cflags --libs`\
			-lSDL2 -lSDL2_image\

test_line:
	@(echo "test_line")
	@(g++ -o test/RayTracing/Line src/Raytracing/Line/*.cpp $(FLAGG))

test_drawable:
	@(echo "test_drawable")
	@(g++ -o test/3DObject/Drawable src/3DObject/Drawable/*.cpp $(FLAGG))

test_model:
	@(echo "test_model")
	@(g++ -o test/3DObject/Model src/3DObject/Model/*.cpp src/3DObject/Drawable/[^Test]*.cpp $(FLAGG))