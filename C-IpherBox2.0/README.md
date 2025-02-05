# C-IpherBox - Security Toolkit Project

### Vue d'Ensemble
C-IpherBox est une suite d'outils de sécurité développée dans le cadre du projet de programmation C à l'ESGI. Ce projet combine trois fonctionnalités essentielles de sécurité informatique :

- **Scanner de ports et d'adresses IP** avec capacités de détection de services
- **Système de compression de fichiers optimisé**
- **Outil de brute force** supportant les mots de passe et les hash cryptographiques

---

## 📝 Installation et Configuration

### Prérequis Système
Le déploiement de C-IpherBox nécessite l'environnement suivant :

- Système d'exploitation **Linux, macOS, ou Windows (via WSL)**
- **Compilateur GCC**
- **Utilitaire Make**

**Bibliothèques requises :**
- `pthread` (gestion du multi-threading)

- **Bibliothèques C standard**

### Processus d'Installation
```bash
# Clonage du dépôt
git clone https://github.com/MrRobboy/C-IpherBox.git
cd C-IpherBox

# Compilation du projet
make

# Lancement de l'application
make run

# Nettoyage des fichiers de compilation
make clean

# Recompilation du projet
make rebuild
```

---

## 🚀 Guide d'Utilisation





### Scanner de Ports et Réseau
L'exécution se fait via la commande :
```bash
make run
```
Le module de scan offre les fonctionnalités suivantes :


- Conversion d'adresses **CIDR** en liste d'IPs
- Analyse des **ports ouverts** sur une adresse IP spécifique
- Scanner réseau complet avec **détection de services**

### Compression de Fichiers
Le module de compression permet :

- La **compression efficace** de fichiers individuels
- L'optimisation du stockage avec **plusieurs niveaux de compression**
- La **décompression** avec vérification d'intégrité

### Brute Force
L'outil de brute force supporte :

- **Attaques par dictionnaire**
- **Cracking de hash MD5 et SHA1**
- Tests de mots de passe avec différentes stratégies

---

## ⚙️ Architecture du Projet
```
C-IpherBox/
├── src/        # Code source
├── include/    # En-têtes
├── build/      # Fichiers de compilation
├── bin/        # Exécutables
├── Makefile      
└── README.md
```


---

## 📊 Organisation et Méthodologie

### Structure de l'Équipe
Notre équipe de trois membres s'est organisée selon une approche fonctionnelle :

- **@MrRobboy** : Scanner de ports et réseau
- **@Pelkarotte** : Module de brute force
- **@hmd_ela** : Système de compression

### Méthodologie de Développement
Nous avons adopté une approche structurée :

- **Planning initial détaillé**
- **Revues de code régulières**
- **Tests d'intégration continus**

---

## 🛠️ Implémentation Technique

### Éléments du Cours Appliqués
Le projet intègre plusieurs concepts clés du cours de programmation C :

#### Gestion de la Mémoire
- Allocation dynamique via pointeurs
- Libération systématique des ressources
- Prévention des fuites mémoire

#### Structures de Données
- Implémentation de structures personnalisées
- Optimisation des accès aux données
- Organisation modulaire du code

#### Programmation Système
- Utilisation des **threads** pour la parallélisation
- Gestion des **entrées/sorties fichier**
- Manipulation des **sockets réseau**

---

## 💡 Optimisations et Performances

### Scanner de Ports
- Implémentation **multi-thread** pour les scans parallèles
- Détection intelligente des services

### Compression


### Brute Force


---

## 🔄 Défis et Solutions

### Défis Rencontrés

- **Gestion de la charge de travail** avec d'autres projets académiques et évaluations
- **Acquisition de nouvelles connaissances techniques** nécessaires à la mise en œuvre des fonctionnalités

### Solutions Apportées

- **Planification minutieuse dès le départ** : L'organisation précoce du projet a permis d'éviter des difficultés organisationnelles et relationnelles.
- **Répartition efficace des tâches** : Chaque membre a pris en charge un module spécifique, réduisant ainsi la charge de travail individuelle.
- **Auto-formation et apprentissage continu** : Les défis techniques ont été résolus en apprenant et en appliquant les notions requises à mesure de l'avancement du projet.

---

## 📈 Impact sur la Formation

### Apports Académiques
Ce projet a permis d'approfondir :
- Les **concepts avancés** de programmation C
- Les **principes de sécurité informatique**
- La **gestion de projet** en équipe

### Développement Professionnel
L'expérience acquise inclut :
- **Gestion d'un projet technique complexe**
- **Travail en équipe** dans un contexte technique
- **Documentation et maintenance de code**

---

## 📄 Licence
Ce projet est distribué sous **licence MIT**. Voir le fichier `LICENSE` pour plus de détails.

---

## ✍️ Auteurs
- **[Membre 1]** - Scanner de Ports et Réseau
- **[Membre 2]** - Module de Brute Force
- **[Membre 3]** - Système de Compression
