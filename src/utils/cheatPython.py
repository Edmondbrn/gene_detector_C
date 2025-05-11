def fusionner(liste_triee1, liste_triee2, liste_fusio):
    """
    Fonction récursive qui trie par fusion deux listes au préalablement triées. 
    Entrées: 2 listes triées au préalable, et une liste vide qui va servir de stockage pour la liste triée
    Sortie: 1 liste triée
    """
    # Vérifie si une des deux listes est vide, donc si on a déjà trié tous ses éléments
    if liste_triee1 == []:
        # On colle alors la reste de la 2e liste déja triée
        liste_fusio += liste_triee2
        return liste_fusio
    # Idem mais pour l'autre liste
    elif liste_triee2 == []:
        liste_fusio += liste_triee1
        return liste_fusio
    # Comparaison des premiers éléments des deux listes
    else:
        if liste_triee1[0] < liste_triee2[0]:
            # On ajoute l'élément le plus petit entre les deux
            liste_fusio.append(liste_triee1[0]) 
            # Renvoie la fonction fusionner en enlevant l'élément ajouté au préalable
            return fusionner(liste_triee1[1:], liste_triee2, liste_fusio)
        # Idem mais pour l'autre liste
        else:
            liste_fusio.append(liste_triee2[0])
            return fusionner(liste_triee1, liste_triee2[1:], liste_fusio)
        
def triFusion(Liste_a_trie):
    """
    Fonction récursive qui prend en entrée une listre non triée et qui la trie par fusion
    Entrée: une liste non triée
    Sortie: la liste triée
    """
    # Vérifie si la liste ne contient qu'un élément (ou vide), donc si elle est déjà triée ou non
    if len(Liste_a_trie) <= 1:
        # Renvoie la liste alors triée
        return Liste_a_trie
    
    # Calcul du milieu de la liste
    milieu = len(Liste_a_trie) // 2
    # Partie récursive: on prend la partie gauche de la liste (première partie) et on lui applique la fonction trifusion jusqu'à n'avoir qu'un élément dans la liste
    # Une fois à 1 élément, la fonction va commencer à fusionner les bouts de liste
    gauche_triee = triFusion(Liste_a_trie[:milieu])
    # Idem pour la 2e partie de la liste
    droite_triee = triFusion(Liste_a_trie[milieu:])
    # Fusionne les bouts de liste en les triant à l'aide de la fonction précédente
    return fusionner(gauche_triee, droite_triee, [])

import time
import sys
if __name__ == "__main__":
    sys.setrecursionlimit(10**6)
    liste = list(range(100000));
    liste = liste[::-1]
    start = time.time();
    triFusion(liste)
    print(time.time() - start)