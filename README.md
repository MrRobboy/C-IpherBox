# C-IpherBox - Security Toolkit Project

### Vue d'Ensemble
C-IpherBox est une suite d'outils de sécurité développée dans le cadre d'un projet academique de C à l'ESGI. Ce projet combine trois fonctionnalités essentielles de sécurité informatique :

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
- pthread (gestion du multi-threading)
- **Bibliothèques C standard**

## 🚀 Guide d'Utilisation

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



## Scanner de Ports et Réseau
### 🛠 Défi & ✅ Solution

### Manipulation des sockets TCP
✅ Utilisation de `socket()`, `connect()` et `select()`

### Scalabilité
✅ Multithreading avec `pthread` (jusqu'à 100 threads)

### Blocage sur connexions lentes
✅ Timeout via `select()` pour éviter les blocages

### Difficulté à identifier les erreurs
✅ Gestion améliorée avec `perror()` et `errno`

### Scans trop lents
✅ Exécution parallèle des scans via threads

### Scan IP unique inefficace
✅ Boucle optimisée pour plusieurs ports simultanément

### Énumération des services impossible
✅ Détection avec `getservbyport()`

---

### 🔥 Optimisations apportées

- **Gestion des réseaux CIDR** → Convertit une plage d’IP automatiquement.
- **Timeout intelligent** → Évite les blocages sur les ports inactifs.
- **Gestion des erreurs robuste** → Messages d’erreurs explicites.
- **Multithreading** → Permet un scan 100x plus rapide.
- **Scan flexible** → Mode IP unique ou réseau entier.
- **Détection des services** → Identification des services actifs (HTTP, SSH, etc.).

---

## 📌 Fonctionnalités principales

- 📍 **Scan d’une IP spécifique**
- 🌐 **Scan d’un réseau entier avec notation CIDR**
- ⚡ **Vitesse optimisée grâce aux threads**
- 🔍 **Affichage des services associés aux ports ouverts**
- 🛡 **Évite les blocages et les ralentissements**

## Compression de Fichiers
Le module de compression permet :

- La **compression efficace** de fichiers individuels
- L'optimisation du stockage avec **plusieurs niveaux de compression**
- La **décompression** avec vérification d'intégrité

## Brute Force
L'outil de brute force supporte :

- **Brute Force classique**
- **Cracking de hash MD5 et SHA1**
- **Attaques par dictionnaire**

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

📌 **Répartition du Code**
- Le dossier `src/` contient les fichiers `.c`
- Le dossier `include/` contient les fichiers `.h`
- Le dossier `bin/` contient l'exécutable
- Le dossier `build/` contient les fichiers `.o`
- Le fichier `README.md` contient la documentation qui sera poussée sur GitHub

### Structuration du Code
Si vous avez uniquement un fichier `main.c`, voici comment bien le structurer :

### Étapes de structuration :
1. **Créer un fichier `.c` par fonctionnalité.**
   - Les fichiers `.c` contiennent les fonctions, les variables et les prototypes des fonctions.
2. **Créer un fichier `.h` pour chaque fichier `.c`.**
   - Les fichiers `.h` doivent contenir les déclarations des fonctions et structures.

### Fonctionnement du `Makefile` :
```make
CC = gcc (compiler)
CFLAGS = -Wall -Wextra -pthread -Iinclude (options de compilation)
LDFLAGS = -lpthread (options de lien)
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))
TARGET = $(BIN_DIR)/C-IpherBox2.0

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Compilation terminée : $(TARGET)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)
	@echo " Nettoyage terminé"

rebuild: clean all

run: all
	./$(TARGET)
```

### Commandes `make` :
- `make` : Compile le projet
- `make run` : Compile et exécute
- `make clean` : Nettoie les fichiers compilés
- `make rebuild` : Nettoie et recompile tout

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

## 📄 Licence
Ce projet est distribué sous **licence MIT**. Voir le fichier `LICENSE` pour plus de détails.

---
