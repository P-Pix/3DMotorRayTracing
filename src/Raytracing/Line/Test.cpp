#include "../../../include/RayTracing/Line.hpp"

int main(int argc, char **argv) {
    RayTracing::Line line(0, 0, 0, 1, 1, 1);
    std::cout << line.getLength() << std::endl;
    Object::Point3D<int> point(2, 2, 2);
    line.setEnd(&point);
    line.setStart(line.getEnd());
    std::cout << line.getLength() << std::endl;
    return EXIT_SUCCESS;
}