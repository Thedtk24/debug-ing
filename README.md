# Debugging

Diagnostiquer et corriger les erreurs en C.

## 1. Compilation

Préparez le terrain :
*   `-g` : Ajoute les symboles (noms variables/lignes) pour GDB/Valgrind.
*   `-O0` : Désactive l'optimisation pour un suivi clair.
*   `-fsanitize=address` : Active la détection immédiate d'erreurs mémoire.

```bash
gcc -g -O0 -fsanitize=address prog.c -o debug_bin
```

## 2. Heap (Tas) : Erreurs mémoire

Pour les crashs (Segfault) ou surconsommation RAM.

### A. Valgrind
Détecte fuites et accès invalides.
```bash
valgrind --leak-check=full ./prog
```
**Cibles :** "definitely lost" (pas de free), "invalid read/write" (hors malloc).

### B. AddressSanitizer (ASAN)
Plus rapide. Stoppe net sur les Buffer Overflows (écrasement données voisines).

## 3. Stack (Pile) : Corruption

Quand une fonction déraille ou une variable change seule.
*   **Cause** : Écriture hors limites d'un tableau local (ex: 12 octets dans un tab de 8).
*   **Effet** : Écrase les variables ou l'adresse de retour.

## 4. GDB : Débogage dynamique

Analyser logique ou crashs.
*   `run` : Lancer.
*   `break <lieu>` : Point d'arrêt.
*   `step` / `next` : Pas à pas (entre / survole fonction).
*   `print <var>` : Voir valeur.
*   `display <var>` : Voir valeur en continu.
*   `backtrace` : Pile d'appels lors du crash (qui a appelé qui).

## 5. Threads & Mutex

Quand ça bloque (freeze) ou résultats aléatoires.

### Deadlock (Blocage)
Deux threads s'attendent.
1.  Lancer GDB, attendre le blocage, `Ctrl+C`.
2.  `info threads` : Liste threads.
3.  `thread apply all bt` : Voir où ils coincent (souvent `pthread_mutex_lock`).

### Race Condition
Utiliser **Helgrind** :
```bash
valgrind --tool=helgrind ./prog
```

## Réflexes

| Symptôme | Outil |
| :--- | :--- |
| Crash / Segfault | **GDB** (`bt`) ou **ASAN** |
| Logique / Boucle fausse | **GDB** (`display`) |
| Fuite mémoire | **Valgrind** |
| Freeze / Blocage | **GDB** (`info threads`) |
| Variable folle | Vérifier débordement (**Stack**) |
