# 🛠️ Scanner Réseau - Scanner d'Adresses IP et Ports  

C-Ipherbox est un outil comprenant plusieurs fonctionnalités :
- Scan de port 
- Compression de fichiers
- Brute force de mot de passe et de hash


---

## 🌜 Sommaire
- [📝 Installation](#installation)
- [🚀 Utilisation](#utilisation)
- [⚙️ Structure du Projet](#structure-du-projet)
- [🛠️ Développement et Modification](#développement-et-modification)

---

## 📝 Installation  

### 🛠️ **Prérequis**
- Système d'exploitation : Linux, macOS, ou Windows (avec WSL)
- Compilateur **GCC**  
- Outil **Make**  

### 📦 **Cloner le dépôt**
```sh
git clone https://github.com/MrRobboy/C-IpherBox.git
cd C-IpherBox
```


### ⚙️ **Compilation**
```sh
make
```

### 🚀 **Exécution**
```sh
make run
```

### 🧹 **Nettoyage**
```sh
make clean
```

---

## 🚀 Utilisation

1. **Lancer le scanner**
   ```sh
   ./bin/scanner
   ```
2. **Fonctionnalités disponibles :**
   - Convertir un CIDR en liste d’adresses IP  
   - Scanner les ports ouverts sur une adresse IP  
   - Scanner un réseau entier  


## ⚙️ Structure du Projet  

📂 **scanner_project/**  
│── 📂 `src/` → Contient le code source  
│   ├─ `main.c` → Point d’entrée du programme  
│   ├─ `menu.c` → Interface utilisateur CLI  
│   ├─ `cidr_to_ips.c` → Conversion CIDR → IP  
│   ├─ `port_scan.c` → Scan des ports ouverts  
│   └─ `network_scanner.c` → Scan réseau complet  
│── 📂 `include/` → Contient les fichiers `.h`  
│   ├─ `menu.h`  
│   ├─ `cidr_to_ips.h`  
│   ├─ `port_scan.h`  
│   └─ `network_scanner.h`  
│── 📂 `build/` → Contient les fichiers objets `.o`  
│── 📂 `bin/` → Contient l'exécutable `C-IpherBox2.0`  
│── 📝 `Makefile` → Automatisation de la compilation  
│── 📝 `README.md` → Documentation  


---

## 🛠️ Développement et Modification  

### 🛠️ **Ajouter une nouvelle fonctionnalité**
1. **Créer un fichier source dans `src/`**
   ```sh
   touch src/nouvelle_fonction.c
   ```
2. **Ajouter un fichier d’en-tête associé dans `include/`**
   ```sh
   touch include/nouvelle_fonction.h
   ```
3. **Implémenter la nouvelle fonctionnalité dans le code**
4. **Ajouter le nouveau fichier source au `Makefile`**  
   - Ouvre `Makefile` et ajoute `src/nouvelle_fonction.c` dans `SRC`  
5. **Compiler et tester**
   ```sh
   make && make run
   ```

### 🗑 **Supprimer une fonctionnalité**
1. Supprime les fichiers `.c` et `.h` correspondants  
2. Retire le fichier du `Makefile`  
3. Nettoie et recompile :
   ```sh
   make clean && make
   ```

### 🛠 **Corriger un bug**
1. Ajoute des `printf` ou utilise `gdb` pour déboguer :
   ```sh
   gdb ./bin/C-IpherBox2.0
   ```
2. Active le mode debug dans le `Makefile` :
   ```makefile
   CFLAGS += -g
   ```
3. Recompile et teste !

---


## 🐜 Licence  
Ce projet est sous licence **MIT** – voir le fichier `LICENSE` pour plus de détails.  
```

