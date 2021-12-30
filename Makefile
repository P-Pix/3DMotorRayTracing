#!/bin/bash

FLAGG	=	`sdl2-config --cflags --libs`\
			-lSDL2 -lSDL2_image\

test_line:
	@(echo "test_line")
	@(g++ -o test/RayTracing/Line src/Raytracing/Line/*.cpp $(FLAGG))
