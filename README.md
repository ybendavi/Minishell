# Minishell

## Description

Ce projet consiste à développer un **mini-interpréteur de commandes** en C, similaire à un shell Unix (comme Bash).

## Compétences acquises

### 1. Gestion des processus et des descripteurs de fichiers
- Création et gestion des processus via `fork`, `execve`, et `pipe`.
- Gestion des signaux comme `ctrl-C`, `ctrl-D`, et `ctrl-\`.

### 2. Implémentation des redirections et pipelines
- Redirection d'entrée et de sortie :
  - `<` : redirection d'entrée.
  - `>` : redirection de sortie.
  - `<<` : lecture jusqu'à un délimiteur spécifique (heredoc).
  - `>>` : redirection en mode append.
- Gestion des pipelines (`|`) pour connecter les commandes entre elles.

### 3. Gestion des variables d'environnement
- Expansion des variables (`$VAR`) pour accéder à leur contenu.
- Gestion de `$?` pour afficher le statut de la commande précédente.

### 4. Implémentation de commandes intégrées (builtins)
- `echo` : affichage de texte, avec prise en charge de l'option `-n`.
- `cd` : navigation dans les répertoires (chemin relatif ou absolu).
- `pwd` : affichage du répertoire courant.
- `export` : gestion des variables d'environnement.
- `unset` : suppression des variables d'environnement.
- `env` : affichage des variables d'environnement.
- `exit` : fermeture du shell.

### 5. Interface utilisateur interactive
- Affichage d’un prompt en attente d’une commande.
- Gestion de l’historique des commandes via la librairie `readline`.
- Prise en charge des quotes simples (`'`) et doubles (`"`).

### 6. Normes et robustesse
- Respect des conventions de codage et des normes du projet.
- Gestion rigoureuse de la mémoire pour éviter les fuites.
- Limitation à une seule variable globale pour les signaux.

## Usage

1. Clonez le dépôt :
   ```bash
   make
   ./minishell
