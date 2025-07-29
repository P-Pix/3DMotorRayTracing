#!/bin/bash

# Script de démonstration du moteur 3D Ray Tracing

echo "============================================"
echo "  Démonstration Moteur 3D Ray Tracing"
echo "============================================"
echo ""

# Vérifier que le projet est compilé
if [ ! -f "build/raytracer_cpu" ]; then
    echo "Compilation du moteur principal..."
    make -f Makefile.cpu all
    if [ $? -ne 0 ]; then
        echo "❌ Erreur de compilation"
        exit 1
    fi
    echo "✅ Compilation réussie"
    echo ""
fi

# Nettoyer les images précédentes
echo "Nettoyage des images précédentes..."
rm -f *.ppm
rm -rf output
echo ""

# Démonstration 1 : Scène simple
echo "🎯 Démonstration 1 : Scène simple avec matériaux variés"
echo "   - Sphères avec matériaux Lambertian, métal, verre"
echo "   - Éclairage direct et ombres"
echo "   - Résolution : 800x600, 100 échantillons"
echo ""
echo "⏱️  Rendu en cours..."
time ./build/raytracer_cpu
echo ""

# Démonstration 2 : Vues multiples
echo "🎯 Démonstration 2 : Angles de vue multiples"
echo "   - 4 angles différents de la même scène"
echo "   - Démonstration de la caméra 3D"
echo ""
echo "⏱️  Rendu en cours..."
time ./build/raytracer_cpu --multiple
echo ""

# Compilation de la scène complexe si nécessaire
if [ ! -f "build/complex_scene" ]; then
    echo "Compilation de la scène complexe..."
    make -f Makefile.cpu complex
    if [ $? -ne 0 ]; then
        echo "❌ Erreur de compilation de la scène complexe"
        exit 1
    fi
    echo ""
fi

# Demander à l'utilisateur s'il veut la scène complexe
echo "🎯 Démonstration 3 : Scène complexe (optionnelle)"
echo "   - Résolution haute : 1200x800"
echo "   - Nombreux objets avec matériaux variés"
echo "   - Sources lumineuses multiples"
echo "   - ⚠️  ATTENTION : Peut prendre plusieurs minutes"
echo ""
read -p "Voulez-vous lancer la scène complexe ? (o/N) " -n 1 -r
echo ""

if [[ $REPLY =~ ^[OoYy]$ ]]; then
    echo "⏱️  Rendu de la scène complexe en cours..."
    time ./build/complex_scene
    echo ""
fi

# Afficher les résultats
echo "📊 Résultats de la démonstration :"
echo ""
echo "Images générées :"
for ppm_file in *.ppm; do
    if [ -f "$ppm_file" ]; then
        size=$(du -h "$ppm_file" | cut -f1)
        echo "  📄 $ppm_file ($size)"
    fi
done

echo ""
echo "🛠️  Pour convertir les images en PNG :"
echo "   ./convert_images.sh"
echo ""

# Statistiques de performance
total_images=$(ls *.ppm 2>/dev/null | wc -l)
if [ $total_images -gt 0 ]; then
    total_size=$(du -ch *.ppm 2>/dev/null | tail -1 | cut -f1)
    echo "📈 Statistiques :"
    echo "   Images générées : $total_images"
    echo "   Taille totale : $total_size"
    
    # Calculer le nombre approximatif de rayons
    basic_rays=$((800 * 600 * 100))  # Image de base
    multi_rays=$((800 * 600 * 100 * 4))  # 4 vues multiples
    
    if [ -f "complex_scene.ppm" ]; then
        complex_rays=$((1200 * 800 * 50))
        total_rays=$(($basic_rays + $multi_rays + $complex_rays))
    else
        total_rays=$(($basic_rays + $multi_rays))
    fi
    
    echo "   Rayons calculés : ~$(($total_rays / 1000000))M"
fi

echo ""
echo "🎨 Fonctionnalités démontrées :"
echo "   ✅ Ray tracing physiquement basé"
echo "   ✅ Matériaux : Lambertian, métal, diélectrique, émissif"
echo "   ✅ Réflexions et réfractions"
echo "   ✅ Éclairage direct et indirect"
echo "   ✅ Ombres dynamiques"
echo "   ✅ Anti-aliasing par super-échantillonnage"
echo "   ✅ Rendu multi-threadé"
echo "   ✅ Caméra 3D configurable"
echo "   ✅ Export d'images haute qualité"

echo ""
echo "🚀 Moteur 3D Ray Tracing - Démonstration terminée !"
echo "============================================"
