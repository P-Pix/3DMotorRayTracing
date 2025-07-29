# Guide d'utilisation du Moteur 3D Ray Tracing

## Vue d'ensemble

Ce moteur de ray tracing 3D implémente une solution complète de rendu par lancer de rayons en C++ avec les fonctionnalités suivantes :

- **Ray tracing physiquement basé** avec réflexions, réfractions et éclairage global
- **Matériaux avancés** : Lambertian, métallique, diélectrique, émissif
- **Multi-threading** pour des performances optimales
- **Export d'images** au format PPM
- **Scènes configurables** avec objets géométriques variés

## Compilation et exécution

### Compilation de base
```bash
# Compiler le moteur principal
make -f Makefile.cpu all

# Compiler tous les exécutables
make -f Makefile.cpu all-targets

# Compilation debug
make -f Makefile.cpu debug
```

### Exécution
```bash
# Scène simple
make -f Makefile.cpu run

# Vues multiples
make -f Makefile.cpu run-multiple

# Scène complexe (haute qualité)
make -f Makefile.cpu complex
```

## Configuration Git et fichiers ignorés

### Fichiers automatiquement ignorés par .gitignore

Le fichier `.gitignore` est configuré pour exclure :

#### Fichiers de compilation
- `*.o`, `*.obj` - Fichiers objets
- `build/`, `obj/`, `bin/` - Dossiers de build
- Exécutables générés (`raytracer_cpu`, `complex_scene`, etc.)

#### Images et sorties du ray tracer
- `*.ppm` - Images PPM générées
- `*.png`, `*.jpg`, `*.jpeg` - Images converties
- `output/` - Dossier de sortie des images

#### Fichiers temporaires et système
- `*.log`, `*.tmp`, `*.bak`, `*~` - Fichiers temporaires
- `.DS_Store`, `Thumbs.db` - Fichiers système
- `.vscode/`, `.idea/` - Configuration IDE

### Commandes Git utiles

```bash
# Voir l'état du repository
git status
git status --ignored  # Voir aussi les fichiers ignorés

# Ajouter le nouveau code
git add include/ src/ *.md Makefile* *.sh

# Nettoyer les fichiers générés avant commit
make -f Makefile.cpu clean

# Commit du nouveau moteur
git commit -m "Moteur 3D Ray Tracing complet"
```

## Architecture technique

### Classes principales

#### Vector3
- Mathématiques vectorielles 3D complètes
- Opérations : addition, soustraction, produit scalaire, produit vectoriel
- Normalisation, réflexion, réfraction

#### Color
- Gestion des couleurs RGBA
- Correction gamma
- Opérations de mélange de couleurs

#### Material
- **Lambertian** : Diffusion parfaite
- **Metal** : Réflexions métalliques avec rugosité
- **Dielectric** : Matériaux transparents (verre, eau)
- **Emissive** : Sources lumineuses

#### Ray
- Représentation des rayons (origine + direction)
- Calcul de points sur le rayon

#### Scene
- Gestion des objets 3D
- Système d'éclairage
- Calcul d'intersections
- Éclairage direct et indirect

#### Camera
- Caméra 3D configurable
- Field of view, aspect ratio
- Profondeur de champ

#### Renderer
- Moteur de ray tracing multi-threadé
- Anti-aliasing par super-échantillonnage
- Contrôle de qualité vs performance

## Objets 3D supportés

### Sphères
```cpp
Material red = Material::lambertian(Color::RED);
scene.addObject(std::make_unique<Sphere>(Vector3(0, 0, -1), 0.5f, red));
```

### Plans
```cpp
Material ground = Material::lambertian(Color(0.5f, 0.5f, 0.5f));
scene.addObject(std::make_unique<Plane>(Vector3(0, -0.5f, 0), Vector3(0, 1, 0), ground));
```

## Configuration des matériaux

### Matériau Lambertian (diffus)
```cpp
Material diffuse = Material::lambertian(Color(0.8f, 0.3f, 0.3f));
```

### Matériau métallique
```cpp
Material metal = Material::metal(Color(0.8f, 0.8f, 0.9f), 0.1f); // roughness = 0.1
```

### Matériau diélectrique (verre)
```cpp
Material glass = Material::dielectric(1.5f); // indice de réfraction
```

### Matériau émissif (lumière)
```cpp
Material light = Material::emissive(Color::WHITE * 5.0f); // intensité x5
```

## Système d'éclairage

### Sources lumineuses ponctuelles
```cpp
scene.addLight(Light(Vector3(2, 2, 0), Color::WHITE, 1.0f));
```

### Éclairage global
- Calcul d'éclairage direct avec ombres
- Éclairage indirect par récursion
- Éclairage ambiant

## Configuration du rendu

### Paramètres de qualité
```cpp
Renderer renderer(
    800,    // largeur
    600,    // hauteur
    100,    // échantillons par pixel
    10,     // profondeur max des rayons
    4       // nombre de threads
);
```

### Contrôle de performance
- **Échantillons** : Plus = meilleure qualité mais plus lent
- **Profondeur** : Limite les réflexions/réfractions récursives
- **Threads** : Parallélisation pour multicore

## Exemples d'utilisation

### Scène simple avec matériaux variés
```cpp
// Matériaux
Material red = Material::lambertian(Color::RED);
Material metal = Material::metal(Color::BLUE, 0.1f);
Material glass = Material::dielectric(1.5f);

// Objets
scene.addObject(std::make_unique<Sphere>(Vector3(0, 0, -1), 0.5f, red));
scene.addObject(std::make_unique<Sphere>(Vector3(-1, 0, -1), 0.5f, glass));
scene.addObject(std::make_unique<Sphere>(Vector3(1, 0, -1), 0.5f, metal));

// Éclairage
scene.addLight(Light(Vector3(2, 2, 0), Color::WHITE, 1.0f));
```

### Configuration caméra
```cpp
Vector3 position(3, 2, 2);
Vector3 target(0, 0, -1);
Vector3 up(0, 1, 0);

camera.lookAt(position, target, up);
camera.setFOV(20.0f);
camera.setAspectRatio(16.0f / 9.0f);
```

## Performance

### Benchmarks typiques
- **Résolution 800x600, 100 échantillons** : ~15-20 secondes
- **Résolution 1200x800, 50 échantillons** : ~30-60 secondes
- **Performance** : ~3M rayons/seconde sur CPU moderne

### Optimisations
- Multi-threading automatique
- Intersection efficace rayon-sphère
- Calculs vectoriels optimisés

## Formats de sortie

### Images PPM
- Format non compressé
- Compatible avec tous les visualiseurs
- Conversion facile vers PNG/JPG

### Conversion d'images
```bash
# Conversion avec ImageMagick
convert raytraced_scene.ppm raytraced_scene.png

# Script automatique
./convert_images.sh
```

## Extensions possibles

### Nouveaux objets géométriques
1. Hériter de la classe `Hitable`
2. Implémenter `hit(const Ray& ray, float tMin, float tMax, HitRecord& record)`
3. Ajouter à la scène

### Nouveaux matériaux
1. Ajouter un type dans `MaterialType`
2. Implémenter la logique dans `Material::scatter()`

### Optimisations avancées
- BVH (Bounding Volume Hierarchy)
- Acceleration structures
- GPU computing avec CUDA/OpenCL

## Dépannage

### Problèmes de compilation
- Vérifier C++17 support : `g++ --version`
- Installer les dépendances : `make install-deps`

### Performance lente
- Réduire les échantillons pour les tests
- Utiliser la compilation optimisée : `-O3`
- Ajuster le nombre de threads

### Images corrompues
- Vérifier l'espace disque disponible
- Permissions d'écriture dans le dossier
- Format PPM peut être volumineux

## Ressources

- **Ray Tracing in One Weekend** : Série de livres de référence
- **Physically Based Rendering** : Techniques avancées
- **Real-Time Rendering** : Optimisations temps réel
