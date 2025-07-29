#!/bin/bash

# Script pour convertir et visualiser les images du ray tracer

echo "=== Ray Tracer Image Converter ==="

# Vérifier si ImageMagick est installé
if ! command -v convert &> /dev/null; then
    echo "ImageMagick n'est pas installé. Installation..."
    sudo apt-get update
    sudo apt-get install -y imagemagick
fi

# Créer un dossier pour les PNG
mkdir -p output

# Convertir toutes les images PPM en PNG
echo "Conversion des images PPM en PNG..."

for ppm_file in raytraced*.ppm; do
    if [ -f "$ppm_file" ]; then
        basename=$(basename "$ppm_file" .ppm)
        png_file="output/${basename}.png"
        
        echo "  Conversion: $ppm_file -> $png_file"
        convert "$ppm_file" "$png_file"
        
        if [ $? -eq 0 ]; then
            echo "    ✓ Succès"
        else
            echo "    ✗ Échec"
        fi
    fi
done

# Afficher les informations sur les fichiers générés
echo ""
echo "=== Images générées ==="
ls -la output/*.png 2>/dev/null || echo "Aucune image PNG générée"

echo ""
echo "=== Informations sur les images ==="
for png_file in output/*.png; do
    if [ -f "$png_file" ]; then
        echo "$(basename "$png_file"):"
        identify "$png_file" | sed 's/^/  /'
    fi
done

echo ""
echo "=== Instructions ==="
echo "Les images PNG sont disponibles dans le dossier 'output/'"
echo "Vous pouvez les ouvrir avec n'importe quel visualiseur d'images."
echo ""
echo "Pour voir rapidement une image :"
echo "  display output/raytraced_scene.png    # (si X11 forwarding est activé)"
echo "  eog output/raytraced_scene.png        # (si gnome est installé)"
echo ""
echo "Ou copiez les fichiers vers Windows pour les visualiser."
