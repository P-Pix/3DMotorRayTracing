#!/bin/bash

FLAGG	=	`sdl2-config --cflags --libs`\
			-lSDL2 -lSDL2_image\

test_line:
	@(echo "test_line")
	@(g++ -o test/RayTracing/Line src/RayTracing/Line/*.cpp $(FLAGG))

test_drawable:
	@(echo "test_drawable")
	@(g++ -o test/3DObject/Drawable src/3DObject/Drawable/*.cpp $(FLAGG))

test_model:
	@(echo "test_model")
	@(g++ -o test/3DObject/Model src/3DObject/Model/*.cpp src/3DObject/Drawable/[^Test]*.cpp $(FLAGG))

test_raytrace:
	@(echo "test_raytrace")
	@(g++ -o test/RayTracing/RayTrace src/RayTracing/RayTrace/*.cpp src/RayTracing/Line/[^Test]*.cpp $(FLAGG))

test_camera:
	@(echo "test_camera")
	@(g++ -o test/RayTracing/Camera src/RayTracing/Camera/*.cpp src/RayTracing/Object/[^Test]*.cpp $(FLAGG))

test_screen:
	@(echo "test_screen")
	@(g++ -o test/RayTracing/Screen src/RayTracing/Screen/*.cpp src/RayTracing/Object/[^Test]*.cpp $(FLAGG))

delete:
	@(echo "delete")
	@(rm -rf test/RayTracing/* test/3DObject/*)