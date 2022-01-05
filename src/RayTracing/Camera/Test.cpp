#include "../../../include/RayTracing/Camera.hpp"

int main(int argc, char** argv) {
    Camera camera;
    camera.setPosition(new Point::D3<int>(0, 0, 0));
    camera.moveAngleX(10);
    return EXIT_SUCCESS;
}