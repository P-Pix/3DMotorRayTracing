#include <iostream>
#include "Vector3.h"
#include "Color.h"
#include "Material.h"

int main() {
    std::cout << "=== Test des composants de base ===" << std::endl;
    
    // Test Vector3
    std::cout << "\n1. Test Vector3:" << std::endl;
    Vector3 v1(1.0f, 2.0f, 3.0f);
    Vector3 v2(4.0f, 5.0f, 6.0f);
    Vector3 v3 = v1 + v2;
    
    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v2: " << v2 << std::endl;
    std::cout << "v1 + v2: " << v3 << std::endl;
    std::cout << "v1.dot(v2): " << v1.dot(v2) << std::endl;
    std::cout << "v1.length(): " << v1.length() << std::endl;
    
    // Test Color
    std::cout << "\n2. Test Color:" << std::endl;
    Color c1(1.0f, 0.5f, 0.0f);
    Color c2 = Color::RED;
    Color c3 = c1 * 0.5f;
    
    std::cout << "c1: " << c1 << std::endl;
    std::cout << "RED: " << c2 << std::endl;
    std::cout << "c1 * 0.5: " << c3 << std::endl;
    
    // Test Material
    std::cout << "\n3. Test Material:" << std::endl;
    Material lambertian = Material::lambertian(Color::BLUE);
    Material metal = Material::metal(Color::YELLOW, 0.1f);
    Material glass = Material::dielectric(1.5f);
    
    std::cout << "Matériaux créés avec succès!" << std::endl;
    
    std::cout << "\n=== Tous les tests passés! ===" << std::endl;
    
    return 0;
}
