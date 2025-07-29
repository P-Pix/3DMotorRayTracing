#!/bin/bash

echo "🎨 3D Ray Tracing Engine - Démonstration Complète"
echo "=================================================="

# Vérifier qu'on est dans le bon répertoire
if [ ! -f "Makefile" ]; then
    echo "❌ Erreur: Pas dans le répertoire racine du projet"
    exit 1
fi

echo ""
echo "🔍 Détection de l'environnement..."

# Nettoyer les builds précédents
echo "🧹 Nettoyage des builds précédents..."
make clean >/dev/null 2>&1

# Vérifier les dépendances OpenGL
if command -v pkg-config >/dev/null 2>&1 && pkg-config --exists glfw3 glew; then
    OPENGL_AVAILABLE=true
    echo "✅ OpenGL disponible - Mode interactif possible"
    echo "   GLFW3: $(pkg-config --modversion glfw3)"
    echo "   GLEW: $(pkg-config --modversion glew)"
else
    OPENGL_AVAILABLE=false
    echo "⚠️  OpenGL non disponible - Mode CPU uniquement"
fi

echo ""
echo "🔨 Compilation du moteur de ray tracing..."

# Compiler automatiquement
if make check-opengl; then
    echo "✅ Compilation réussie!"
else
    echo "❌ Échec de la compilation"
    exit 1
fi

echo ""
echo "🎮 Démonstration des fonctionnalités..."

# Démo version CPU
echo ""
echo "📸 === DÉMONSTRATION VERSION CPU ==="
echo "Génération d'images haute qualité..."

if [ -f "build/raytracer_cpu" ]; then
    echo "🚀 Lancement du ray tracer CPU..."
    echo "   (Cela peut prendre 15-30 secondes pour une image de qualité)"
    
    # Lancer le ray tracer CPU
    timeout 60s ./build/raytracer_cpu
    
    # Vérifier les images générées
    echo ""
    echo "📁 Images générées:"
    for img in raytraced_*.ppm; do
        if [ -f "$img" ]; then
            size=$(ls -lh "$img" | awk '{print $5}')
            echo "   ✅ $img ($size)"
        fi
    done
    
    echo ""
    echo "💡 Pour voir les images:"
    echo "   - Utilisez GIMP, ImageMagick ou un autre éditeur"
    echo "   - Ou convertissez avec: ./convert_images.sh"
    
else
    echo "❌ Exécutable CPU non trouvé"
fi

# Démo version OpenGL si disponible
if [ "$OPENGL_AVAILABLE" = true ] && [ -f "raytracer_opengl" ]; then
    echo ""
    echo "🖥️  === DÉMONSTRATION VERSION OPENGL ==="
    echo "Mode interactif temps réel disponible!"
    echo ""
    echo "🎮 Contrôles pour la version interactive:"
    echo "   ESC     - Quitter"
    echo "   R       - Basculer rendu temps réel"
    echo "   SPACE   - Rendre une image haute qualité"
    echo "   S       - Sauvegarder l'image actuelle"
    echo "   1-3     - Préréglages de qualité"
    echo "   H/L     - Augmenter/Diminuer la qualité"
    echo "   WASD    - Déplacer la caméra"
    echo "   Q/E     - Monter/Descendre"
    echo ""
    echo "📺 Pour lancer la version interactive:"
    echo "   ./raytracer_opengl"
    echo ""
    echo "⚠️  Note: La version interactive nécessite un affichage graphique"
    echo "   Dans WSL, utilisez un serveur X11 ou Windows 11 WSLg"
    
elif [ "$OPENGL_AVAILABLE" = false ]; then
    echo ""
    echo "🖥️  === VERSION OPENGL NON DISPONIBLE ==="
    echo "Pour activer le mode interactif:"
    echo "   sudo apt-get install libglfw3-dev libglew-dev"
    echo "   Puis recompilez avec: make opengl"
fi

echo ""
echo "📊 === INFORMATIONS TECHNIQUES ==="
echo "Architecture du projet:"
ls -la include/ | head -10
echo "   ... et plus dans include/"
echo ""
echo "Exécutables générés:"
ls -lh build/raytracer_* raytracer_* 2>/dev/null | head -5
echo ""

echo "🏁 === RÉSUMÉ DE LA DÉMONSTRATION ==="
echo ""
if [ "$OPENGL_AVAILABLE" = true ]; then
    echo "✅ Moteur ray tracing complet avec support OpenGL"
    echo "   - Version CPU: Rendu haute qualité vers fichiers PPM"
    echo "   - Version OpenGL: Interface interactive temps réel"
else
    echo "✅ Moteur ray tracing CPU fonctionnel"
    echo "   - Génération d'images haute qualité"
    echo "   - Multi-threading optimisé"
    echo "   - Export PPM vers images standard possibles"
fi

echo ""
echo "🎯 Prochaines étapes:"
echo "   1. Examiner les images générées"
echo "   2. Modifier les scènes dans src/main_cpu.cpp"
echo "   3. Expérimenter avec les matériaux"
if [ "$OPENGL_AVAILABLE" = true ]; then
    echo "   4. Tester la version interactive OpenGL"
fi
echo "   5. Ajuster la qualité/performance selon vos besoins"

echo ""
echo "📚 Documentation complète: README.md"
echo "🔧 Scripts utilitaires disponibles:"
echo "   ./run_demo.sh, ./convert_images.sh, ./git_setup.sh"

echo ""
echo "🎨 Merci d'avoir testé le moteur 3D Ray Tracing!"
