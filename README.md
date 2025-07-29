# 🎨 3DMotorRayTracing
##### Moteur 3D par ray tracing avec OpenGL

Un moteur de rendu 3D avancé implémentant le ray tracing en temps réel avec C++ et OpenGL.

## ✨ Fonctionnalités

### 🔆 Ray Tracing
- **Algorithme de ray tracing** complet avec support des réflexions et réfractions
- **Matériaux avancés** : Lambertian, métallique, diélectrique, émissif
- **Éclairage physique** avec sources lumineuses multiples et calcul d'ombres
- **Anti-aliasing** par échantillonnage multiple
- **Rendu multi-threadé** pour de meilleures performances

### 🎯 Objets 3D
- **Sphères** avec matériaux configurables
- **Plans** infinis
- **Système de scène** hiérarchique
- Support facile pour ajouter de nouveaux types d'objets

### 🖥️ Rendu OpenGL
- **Affichage en temps réel** via texture OpenGL
- **Shaders modernes** (OpenGL 3.3+)
- **Interface utilisateur** interactive
- **Contrôles caméra** WASD pour la navigation

### 📷 Caméra
- **Système de caméra 3D** complet
- **Contrôle de la profondeur de champ**
- **Field of View ajustable**
- **Navigation fluide**

## 🚀 Installation

### 📋 Prérequis

**Version CPU (minimum requis)** :
```bash
# Ubuntu/Debian
sudo apt-get install build-essential
```

**Version OpenGL (pour mode interactif)** :
```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install build-essential cmake
sudo apt-get install libgl1-mesa-dev libglew-dev libglfw3-dev pkg-config
```

### 🔨 Compilation

Le système détecte automatiquement les bibliothèques disponibles :

```bash
# Compilation automatique (recommandé)
make check-opengl

# Compilation manuelle
make cpu        # Version CPU uniquement
make opengl     # Version OpenGL (si disponible)
make all        # Toutes les versions
```

# Compilation debug
make debug

# Compilation et exécution
make run
```

## Utilisation

### Contrôles
- **ESC** : Quitter l'application
- **R** : Activer/désactiver le rendu temps réel
- **SPACE** : Rendre une frame unique (mode pause)
- **W/A/S/D** : Déplacer la caméra
- **Souris** : Rotation de la caméra (à implémenter)

### Configuration
Le moteur peut être configuré via le code source :
- Résolution de rendu
- Nombre d'échantillons par pixel
- Profondeur maximale de ray tracing
- Nombre de threads

## Architecture

```
include/
├── Vector3.h          # Mathématiques vectorielles 3D
├── Color.h            # Gestion des couleurs
├── Ray.h              # Classe Ray pour le ray tracing
├── Material.h         # Système de matériaux
├── Hitable.h          # Interface pour les objets intersectables
├── Sphere.h           # Implémentation des sphères
├── Plane.h            # Implémentation des plans
├── Scene.h            # Gestion de scène et éclairage
├── Camera.h           # Système de caméra 3D
├── Renderer.h         # Moteur de ray tracing
└── OpenGLRenderer.h   # Rendu OpenGL et interface

src/
├── Vector3.cpp
├── Color.cpp
├── Ray.cpp
├── Material.cpp
├── Sphere.cpp
├── Plane.cpp
├── Scene.cpp
├── Camera.cpp
├── Renderer.cpp
├── OpenGLRenderer.cpp
└── main.cpp           # Application principale
```

## Exemples de scènes

Le moteur inclut une scène de démonstration avec :
- Sphères avec différents matériaux (Lambertian, métal, verre)
- Éclairage ambiant et direct
- Plan au sol
- Sources lumineuses émissives

## Performance

- **Rendu multi-threadé** : Utilise tous les cœurs CPU disponibles
- **Optimisations** : Intersection efficace des rayons
- **Rendu adaptatif** : Qualité ajustable selon les performances

## Développement

### Ajouter de nouveaux objets
1. Hériter de la classe `Hitable`
2. Implémenter la méthode `hit()`
3. Ajouter à la scène via `scene.addObject()`

### Ajouter de nouveaux matériaux
1. Étendre l'enum `MaterialType`
2. Implémenter la logique dans `Material::scatter()`

## Dépendances

- **OpenGL 3.3+** : Rendu graphique
- **GLEW** : Extensions OpenGL
- **GLFW** : Gestion de fenêtre et événements
- **C++17** : Fonctionnalités modernes du C++

## Licence

Ce projet est sous licence MIT. Voir le fichier LICENSE pour plus de détails.

## Inspiré par

Ce projet s'inspire des techniques modernes de ray tracing et des travaux de recherche en infographie 3D.