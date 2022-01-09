#!/bin/bash

FLAGG	=	`sdl2-config --cflags --libs`\
			-lSDL2 -lSDL2_image\

test_line:
	@(echo "test line")
	@(g++ -o test/RayTracing/Line src/RayTracing/Line/*.cpp $(FLAGG))

test_drawable:
	@(echo "test drawable")
	@(g++ -o test/3DObject/Drawable src/3DObject/Drawable/*.cpp $(FLAGG))

test_model:
	@(echo "test model")
	@(g++ -o test/3DObject/Model src/3DObject/Model/*.cpp src/3DObject/Drawable/[^Test]*.cpp $(FLAGG))

test_color:
	@(echo "test color")
	@(g++ -o test/3DObject/Color src/3DObject/Color/*.cpp $(FLAGG))

test_raytrace:
	@(echo "test raytrace")
	@(g++ -o test/RayTracing/RayTrace src/RayTracing/RayTrace/*.cpp src/RayTracing/Line/[^Test]*.cpp $(FLAGG))

test_camera:
	@(echo "test camera")
	@(g++ -o test/RayTracing/Camera src/RayTracing/Camera/*.cpp src/RayTracing/Object/[^Test]*.cpp $(FLAGG))

test_screen:
	@(echo "test screen")
	@(g++ -o test/RayTracing/Screen src/RayTracing/Screen/*.cpp src/RayTracing/Object/[^Test]*.cpp $(FLAGG))

delete:
	@(echo "delete")
	@(rm -rf test/RayTracing/* test/3DObject/*)