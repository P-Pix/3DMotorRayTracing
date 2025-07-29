#!/bin/bash

echo "📦 Préparation du projet pour transfert"
echo "======================================"

# Créer un répertoire de distribution
DIST_DIR="3DMotorRayTracing_dist"
echo "📁 Création du répertoire de distribution: $DIST_DIR"

rm -rf "$DIST_DIR"
mkdir -p "$DIST_DIR"

# Copier les fichiers sources essentiels
echo "📋 Copie des fichiers sources..."
cp -r include/ "$DIST_DIR/"
cp -r src/ "$DIST_DIR/"
cp -r lib/ "$DIST_DIR/"
cp Makefile "$DIST_DIR/"
cp README.md "$DIST_DIR/"

# Copier les scripts utilitaires
echo "🔧 Copie des scripts utilitaires..."
cp run_demo.sh "$DIST_DIR/" 2>/dev/null || true
cp convert_images.sh "$DIST_DIR/" 2>/dev/null || true
cp git_setup.sh "$DIST_DIR/" 2>/dev/null || true
cp test_opengl.sh "$DIST_DIR/" 2>/dev/null || true
cp demo_complete.sh "$DIST_DIR/" 2>/dev/null || true

# Copier les exemples
echo "🎨 Copie des exemples..."
cp -r 3D/ "$DIST_DIR/" 2>/dev/null || true

# Créer un .gitignore
echo "📝 Création du .gitignore..."
cat > "$DIST_DIR/.gitignore" << 'EOF'
# Build artifacts
build/
*.o
*.so
*.a
raytracer*
!raytracer.cpp

# Generated images
*.ppm
*.png
*.jpg
*.jpeg
*.bmp

# IDE files
.vscode/
.idea/
*.swp
*.swo
*~

# OS files
.DS_Store
Thumbs.db

# Temporary files
*.tmp
*.temp
EOF

# Créer un script d'installation simplifié
echo "⚙️ Création du script d'installation..."
cat > "$DIST_DIR/install.sh" << 'EOF'
#!/bin/bash

echo "🚀 Installation du moteur 3D Ray Tracing"
echo "========================================"

# Vérifier les dépendances
echo "🔍 Vérification des dépendances..."

if ! command -v g++ >/dev/null 2>&1; then
    echo "❌ g++ non trouvé. Installez build-essential:"
    echo "   sudo apt-get install build-essential"
    exit 1
fi

if ! command -v make >/dev/null 2>&1; then
    echo "❌ make non trouvé. Installez make:"
    echo "   sudo apt-get install make"
    exit 1
fi

echo "✅ Dépendances de base trouvées"

# Vérifier OpenGL (optionnel)
if command -v pkg-config >/dev/null 2>&1 && pkg-config --exists glfw3 glew; then
    echo "✅ OpenGL disponible - Mode interactif possible"
    OPENGL_MODE=true
else
    echo "⚠️  OpenGL non disponible - Mode CPU uniquement"
    echo "   Pour activer OpenGL: sudo apt-get install libglfw3-dev libglew-dev"
    OPENGL_MODE=false
fi

# Compiler
echo ""
echo "🔨 Compilation..."
if make check-opengl; then
    echo "✅ Compilation réussie!"
    
    echo ""
    echo "🎯 Prêt à utiliser:"
    if [ -f "build/raytracer_cpu" ]; then
        echo "   CPU: ./build/raytracer_cpu"
    fi
    if [ -f "raytracer_opengl" ]; then
        echo "   OpenGL: ./raytracer_opengl"
    fi
    
    echo ""
    echo "📚 Voir README.md pour la documentation complète"
    echo "🎮 Lancer: ./demo_complete.sh pour une démonstration"
    
else
    echo "❌ Échec de la compilation"
    exit 1
fi
EOF

chmod +x "$DIST_DIR/install.sh"

# Créer un README rapide
echo "📖 Création du guide de démarrage rapide..."
cat > "$DIST_DIR/QUICKSTART.md" << 'EOF'
# 🚀 Démarrage Rapide - Moteur 3D Ray Tracing

## Installation Express

```bash
# 1. Installer les dépendances (Ubuntu/Debian)
sudo apt-get install build-essential

# 2. Optionnel: Support OpenGL pour mode interactif
sudo apt-get install libglfw3-dev libglew-dev

# 3. Compiler et installer
./install.sh

# 4. Tester
./demo_complete.sh
```

## Utilisation Immédiate

**Version CPU** (toujours disponible):
```bash
./build/raytracer_cpu
```
- Génère des images PPM haute qualité
- Multi-threading automatique

**Version OpenGL** (si disponible):
```bash
./raytracer_opengl
```
- Interface interactive temps réel
- Contrôles: WASD (mouvement), R (temps réel), S (sauvegarder)

## Structure

- `include/` - Headers C++
- `src/` - Code source
- `Makefile` - Configuration de build
- `README.md` - Documentation complète

## Support

Le moteur fonctionne sur tout système avec:
- C++17 (GCC 7+)
- Make
- OpenGL 3.3+ (optionnel pour mode interactif)

Testé sur Ubuntu, Debian, Windows WSL, et autres distributions Linux.
EOF

# Créer un fichier de version
echo "📋 Création du fichier de version..."
cat > "$DIST_DIR/VERSION" << EOF
3D Ray Tracing Engine v2.0
============================

Date: $(date "+%Y-%m-%d %H:%M:%S")
Plateforme: $(uname -s) $(uname -m)

Fonctionnalités:
- Ray tracing CPU multi-thread
- Support OpenGL optionnel
- Matériaux physiques (Lambert, métal, verre)
- Export d'images PPM
- Interface interactive

Build: Production ready
EOF

# Statistiques du projet
echo ""
echo "📊 Statistiques du projet copié:"
echo "   Fichiers sources: $(find "$DIST_DIR" -name "*.cpp" -o -name "*.h" | wc -l)"
echo "   Lignes de code: $(find "$DIST_DIR" -name "*.cpp" -o -name "*.h" -exec cat {} + | wc -l)"
echo "   Taille: $(du -sh "$DIST_DIR" | cut -f1)"

echo ""
echo "✅ Projet prêt pour le transfert dans: $DIST_DIR"
echo ""
echo "📦 Pour créer une archive:"
echo "   tar -czf 3DMotorRayTracing.tar.gz $DIST_DIR"
echo "   zip -r 3DMotorRayTracing.zip $DIST_DIR"
echo ""
echo "🚀 Sur le système cible:"
echo "   1. Extraire l'archive"
echo "   2. cd $DIST_DIR"
echo "   3. ./install.sh"
echo "   4. ./demo_complete.sh"
