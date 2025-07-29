#!/bin/bash

# Script de gestion Git pour le projet 3DMotorRayTracing

echo "============================================"
echo "  Gestion Git - Moteur 3D Ray Tracing"
echo "============================================"
echo ""

# Fonction pour afficher l'aide
show_help() {
    echo "Usage: $0 [command]"
    echo ""
    echo "Commandes disponibles:"
    echo "  status    - Afficher l'état du repository"
    echo "  clean     - Nettoyer les fichiers générés"
    echo "  add       - Ajouter les fichiers du moteur"
    echo "  commit    - Faire un commit du nouveau moteur"
    echo "  push      - Pousser vers le repository distant"
    echo "  setup     - Configuration complète (add + commit + push)"
    echo "  help      - Afficher cette aide"
    echo ""
}

# Fonction pour nettoyer les fichiers générés
clean_generated() {
    echo "🧹 Nettoyage des fichiers générés..."
    make -f Makefile.cpu clean 2>/dev/null || echo "Pas de Makefile, nettoyage manuel..."
    rm -rf build/ *.ppm output/ *.log *.tmp
    echo "✅ Nettoyage terminé"
    echo ""
}

# Fonction pour afficher le statut
show_status() {
    echo "📊 État du repository Git:"
    echo ""
    git status --short
    echo ""
    echo "📝 Fichiers ignorés (quelques exemples):"
    git status --ignored | grep -E "\.(ppm|o|tmp)" | head -5
    echo ""
}

# Fonction pour ajouter les fichiers
add_files() {
    echo "➕ Ajout des fichiers du moteur..."
    
    # Vérifier que les fichiers existent
    if [ ! -d "include" ] || [ ! -d "src" ]; then
        echo "❌ Erreur: Dossiers include/ ou src/ introuvables"
        exit 1
    fi
    
    # Ajouter les fichiers principaux
    git add .gitignore
    git add README.md
    git add GUIDE.md
    git add Makefile*
    git add include/
    git add src/
    git add *.sh
    
    echo "✅ Fichiers ajoutés"
    echo ""
    
    # Afficher ce qui sera commité
    echo "📋 Fichiers prêts pour commit:"
    git diff --cached --name-only
    echo ""
}

# Fonction pour faire le commit
commit_changes() {
    echo "💾 Création du commit..."
    
    # Vérifier qu'il y a des changements à committer
    if git diff --cached --quiet; then
        echo "⚠️  Aucun changement à committer"
        echo "Utilisez d'abord: $0 add"
        return 1
    fi
    
    # Message de commit détaillé
    commit_message="Implémentation complète du moteur 3D Ray Tracing

🚀 Fonctionnalités principales:
- Moteur ray tracing physiquement basé en C++
- Support matériaux: Lambertian, metal, dielectric, emissive
- Rendu multi-threadé optimisé (3M+ rayons/seconde)
- Réflexions, réfractions et éclairage global
- Export images PPM haute qualité
- Architecture modulaire et extensible

🛠️ Outils inclus:
- Scripts de compilation (Makefile.cpu)
- Script de démonstration (demo.sh)
- Convertisseur d'images (convert_images.sh)
- Documentation complète

📊 Performance:
- Résolution: 800x600 à 1200x800
- Échantillonnage: 50-100 samples/pixel
- Multi-threading: 4-8 threads
- Temps de rendu: 15-60 secondes selon qualité"

    git commit -m "$commit_message"
    
    if [ $? -eq 0 ]; then
        echo "✅ Commit créé avec succès"
        echo ""
        git log --oneline -1
    else
        echo "❌ Erreur lors du commit"
        return 1
    fi
    echo ""
}

# Fonction pour pousser
push_changes() {
    echo "🚀 Push vers le repository distant..."
    
    git push origin main
    
    if [ $? -eq 0 ]; then
        echo "✅ Push réussi"
    else
        echo "❌ Erreur lors du push"
        echo "Vérifiez votre connexion et vos droits d'accès"
        return 1
    fi
    echo ""
}

# Fonction pour la configuration complète
setup_complete() {
    echo "🔧 Configuration complète du repository..."
    echo ""
    
    clean_generated
    add_files
    commit_changes
    
    if [ $? -eq 0 ]; then
        read -p "Voulez-vous pousser vers le repository distant ? (o/N) " -n 1 -r
        echo ""
        if [[ $REPLY =~ ^[OoYy]$ ]]; then
            push_changes
        fi
    fi
    
    echo "✅ Configuration terminée !"
}

# Traitement des arguments
case "${1:-help}" in
    "status")
        show_status
        ;;
    "clean")
        clean_generated
        ;;
    "add")
        clean_generated
        add_files
        ;;
    "commit")
        commit_changes
        ;;
    "push")
        push_changes
        ;;
    "setup")
        setup_complete
        ;;
    "help"|*)
        show_help
        ;;
esac
