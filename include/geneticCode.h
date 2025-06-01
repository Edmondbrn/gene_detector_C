#ifndef GENETIC_CODE_H
#define GENETIC_CODE_H

#include "HashMap.h"
#include "GenericValue.h"
#include<string.h>

/**
 * Init a hashmap that contains codon (keys) and the corresponding amino acid
 * 
 * @return a hashmap containg the standard genetic code
 */
HashMap* initGeneticCode() {
    HashMap* geneticCode = createHashMap(128);  // 64 combinaison, so 128 to avoid collisions
    
    // Alanine (A)
    putHashMap(geneticCode, "GCU", createStringValue("A"));
    putHashMap(geneticCode, "GCC", createStringValue("A"));
    putHashMap(geneticCode, "GCA", createStringValue("A"));
    putHashMap(geneticCode, "GCG", createStringValue("A"));
    
    // Arginine (R)
    putHashMap(geneticCode, "CGU", createStringValue("R"));
    putHashMap(geneticCode, "CGC", createStringValue("R"));
    putHashMap(geneticCode, "CGA", createStringValue("R"));
    putHashMap(geneticCode, "CGG", createStringValue("R"));
    putHashMap(geneticCode, "AGA", createStringValue("R"));
    putHashMap(geneticCode, "AGG", createStringValue("R"));
    
    // Asparagine (N)
    putHashMap(geneticCode, "AAU", createStringValue("N"));
    putHashMap(geneticCode, "AAC", createStringValue("N"));
    
    // Aspartic acid (D)
    putHashMap(geneticCode, "GAU", createStringValue("D"));
    putHashMap(geneticCode, "GAC", createStringValue("D"));
    
    // Cysteine (C)
    putHashMap(geneticCode, "UGU", createStringValue("C"));
    putHashMap(geneticCode, "UGC", createStringValue("C"));
    
    // Glutamine (Q)
    putHashMap(geneticCode, "CAA", createStringValue("Q"));
    putHashMap(geneticCode, "CAG", createStringValue("Q"));
    
    // Glutamique acid (E)
    putHashMap(geneticCode, "GAA", createStringValue("E"));
    putHashMap(geneticCode, "GAG", createStringValue("E"));
    
    // Glycine (G)
    putHashMap(geneticCode, "GGU", createStringValue("G"));
    putHashMap(geneticCode, "GGC", createStringValue("G"));
    putHashMap(geneticCode, "GGA", createStringValue("G"));
    putHashMap(geneticCode, "GGG", createStringValue("G"));
    
    // Histidine (H)
    putHashMap(geneticCode, "CAU", createStringValue("H"));
    putHashMap(geneticCode, "CAC", createStringValue("H"));
    
    // Isoleucine (I)
    putHashMap(geneticCode, "AUU", createStringValue("I"));
    putHashMap(geneticCode, "AUC", createStringValue("I"));
    putHashMap(geneticCode, "AUA", createStringValue("I"));
    
    // Leucine (L)
    putHashMap(geneticCode, "UUA", createStringValue("L"));
    putHashMap(geneticCode, "UUG", createStringValue("L"));
    putHashMap(geneticCode, "CUU", createStringValue("L"));
    putHashMap(geneticCode, "CUC", createStringValue("L"));
    putHashMap(geneticCode, "CUA", createStringValue("L"));
    putHashMap(geneticCode, "CUG", createStringValue("L"));
    
    // Lysine (K)
    putHashMap(geneticCode, "AAA", createStringValue("K"));
    putHashMap(geneticCode, "AAG", createStringValue("K"));
    
    // Méthionine (M) - START Codon
    putHashMap(geneticCode, "AUG", createStringValue("M"));
    
    // Phénylalanine (F)
    putHashMap(geneticCode, "UUU", createStringValue("F"));
    putHashMap(geneticCode, "UUC", createStringValue("F"));
    
    // Proline (P)
    putHashMap(geneticCode, "CCU", createStringValue("P"));
    putHashMap(geneticCode, "CCC", createStringValue("P"));
    putHashMap(geneticCode, "CCA", createStringValue("P"));
    putHashMap(geneticCode, "CCG", createStringValue("P"));
    
    // Sérine (S)
    putHashMap(geneticCode, "UCU", createStringValue("S"));
    putHashMap(geneticCode, "UCC", createStringValue("S"));
    putHashMap(geneticCode, "UCA", createStringValue("S"));
    putHashMap(geneticCode, "UCG", createStringValue("S"));
    putHashMap(geneticCode, "AGU", createStringValue("S"));
    putHashMap(geneticCode, "AGC", createStringValue("S"));
    
    // Thréonine (T)
    putHashMap(geneticCode, "ACU", createStringValue("T"));
    putHashMap(geneticCode, "ACC", createStringValue("T"));
    putHashMap(geneticCode, "ACA", createStringValue("T"));
    putHashMap(geneticCode, "ACG", createStringValue("T"));
    
    // Tryptophane (W)
    putHashMap(geneticCode, "UGG", createStringValue("W"));
    
    // Tyrosine (Y)
    putHashMap(geneticCode, "UAU", createStringValue("Y"));
    putHashMap(geneticCode, "UAC", createStringValue("Y"));
    
    // Valine (V)
    putHashMap(geneticCode, "GUU", createStringValue("V"));
    putHashMap(geneticCode, "GUC", createStringValue("V"));
    putHashMap(geneticCode, "GUA", createStringValue("V"));
    putHashMap(geneticCode, "GUG", createStringValue("V"));
    
    // STOP codon
    putHashMap(geneticCode, "UAA", createStringValue("*"));
    putHashMap(geneticCode, "UAG", createStringValue("*"));
    putHashMap(geneticCode, "UGA", createStringValue("*"));
    
    return geneticCode;
}

/**
 * Traduit une séquence d'ARN en acides aminés en utilisant le code génétique standard.
 * 
 * @param rnaSequence Chaîne de caractères représentant la séquence d'ARN
 * @param geneticCode HashMap contenant le code génétique
 * @return Une chaîne de caractères représentant la séquence d'acides aminés
 */
char* translateRNA(char* rnaSequence, HashMap* geneticCode) {
    int rnaLength = strlen(rnaSequence);
    int proteinLength = (rnaLength / 3) + 1; // +1 pour le caractère nul
    
    char* protein = malloc(proteinLength * sizeof(char));
    if (protein == NULL) return NULL;
    
    int proteinIndex = 0;
    
    // Traduction par triplets (codons)
    for (int i = 0; i < rnaLength - 2; i += 3) {
        char codon[4] = {0}; // 3 caractères + caractère nul
        codon[0] = rnaSequence[i];
        codon[1] = rnaSequence[i+1];
        codon[2] = rnaSequence[i+2];
        
        GenericValue* amino;
        if (getHashMapValue(geneticCode, codon, &amino) == 0) {
            // Si c'est un codon STOP, terminer la traduction
            if (strcmp(amino->data.stringValue, "*") == 0) {
                break;
            }
            
            // Ajouter l'acide aminé à la protéine
            protein[proteinIndex++] = amino->data.stringValue[0]; // On prend seulement la première lettre
        } else {
            protein[proteinIndex++] = 'X'; // Acide aminé inconnu
        }
    }
    
    protein[proteinIndex] = '\0'; // Terminer la chaîne
    return protein;
}

#endif // GENETIC_CODE_H