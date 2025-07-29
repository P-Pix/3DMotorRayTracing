#!/bin/bash

echo "🎬 Lancement du moteur 3D avec animation automatique"
echo "======================================================"
echo ""
echo "🚀 DÉMO SIMPLIFIÉE - Une seule touche pour tout activer !"
echo ""
echo "Instructions :"
echo "1. Appuyez sur 'A' pour activer l'animation automatique"
echo "   → Active automatiquement le rendu temps réel"
echo "   → La caméra tourne automatiquement autour de la scène"
echo "2. Appuyez de nouveau sur 'A' pour désactiver l'animation"
echo "3. Profitez de la démo spectaculaire en 3D !"
echo ""
echo "Contrôles additionnels :"
echo "  +/-      - Ajuster la vitesse d'animation"
echo "  1-3      - Changer la qualité de rendu"
echo "  ESC      - Quitter"
echo ""
echo "Démarrage du programme..."
echo ""

cd "$(dirname "$0")"

# Vérifier si le programme existe
if [ ! -f "build/raytracer_opengl" ]; then
    echo "❌ Le programme n'est pas compilé. Compilation en cours..."
    make
    if [ $? -ne 0 ]; then
        echo "❌ Erreur de compilation"
        exit 1
    fi
fi

# Lancer le programme
./build/raytracer_opengl

echo ""
echo "👋 Merci d'avoir testé le moteur 3D avec animation automatique !"
