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
    putHashMap(geneticCode, "GCT", createStringValue("A"));
    putHashMap(geneticCode, "GCC", createStringValue("A"));
    putHashMap(geneticCode, "GCA", createStringValue("A"));
    putHashMap(geneticCode, "GCG", createStringValue("A"));
    
    // Arginine (R)
    putHashMap(geneticCode, "CGT", createStringValue("R"));
    putHashMap(geneticCode, "CGC", createStringValue("R"));
    putHashMap(geneticCode, "CGA", createStringValue("R"));
    putHashMap(geneticCode, "CGG", createStringValue("R"));
    putHashMap(geneticCode, "AGA", createStringValue("R"));
    putHashMap(geneticCode, "AGG", createStringValue("R"));
    
    // Asparagine (N)
    putHashMap(geneticCode, "AAT", createStringValue("N"));
    putHashMap(geneticCode, "AAC", createStringValue("N"));
    
    // Aspartic acid (D)
    putHashMap(geneticCode, "GAT", createStringValue("D"));
    putHashMap(geneticCode, "GAC", createStringValue("D"));
    
    // Cysteine (C)
    putHashMap(geneticCode, "TGT", createStringValue("C"));
    putHashMap(geneticCode, "TGC", createStringValue("C"));
    
    // Glutamine (Q)
    putHashMap(geneticCode, "CAA", createStringValue("Q"));
    putHashMap(geneticCode, "CAG", createStringValue("Q"));
    
    // Glutamique acid (E)
    putHashMap(geneticCode, "GAA", createStringValue("E"));
    putHashMap(geneticCode, "GAG", createStringValue("E"));
    
    // Glycine (G)
    putHashMap(geneticCode, "GGT", createStringValue("G"));
    putHashMap(geneticCode, "GGC", createStringValue("G"));
    putHashMap(geneticCode, "GGA", createStringValue("G"));
    putHashMap(geneticCode, "GGG", createStringValue("G"));
    
    // Histidine (H)
    putHashMap(geneticCode, "CAT", createStringValue("H"));
    putHashMap(geneticCode, "CAC", createStringValue("H"));
    
    // Isoleucine (I)
    putHashMap(geneticCode, "ATT", createStringValue("I"));
    putHashMap(geneticCode, "ATC", createStringValue("I"));
    putHashMap(geneticCode, "ATA", createStringValue("I"));
    
    // Leucine (L)
    putHashMap(geneticCode, "TTA", createStringValue("L"));
    putHashMap(geneticCode, "TTG", createStringValue("L"));
    putHashMap(geneticCode, "CTT", createStringValue("L"));
    putHashMap(geneticCode, "CTC", createStringValue("L"));
    putHashMap(geneticCode, "CTA", createStringValue("L"));
    putHashMap(geneticCode, "CTG", createStringValue("L"));
    
    // Lysine (K)
    putHashMap(geneticCode, "AAA", createStringValue("K"));
    putHashMap(geneticCode, "AAG", createStringValue("K"));
    
    // Méthionine (M) - START Codon
    putHashMap(geneticCode, "ATG", createStringValue("M"));
    
    // Phénylalanine (F)
    putHashMap(geneticCode, "TTT", createStringValue("F"));
    putHashMap(geneticCode, "TTC", createStringValue("F"));
    
    // Proline (P)
    putHashMap(geneticCode, "CCT", createStringValue("P"));
    putHashMap(geneticCode, "CCC", createStringValue("P"));
    putHashMap(geneticCode, "CCA", createStringValue("P"));
    putHashMap(geneticCode, "CCG", createStringValue("P"));
    
    // Sérine (S)
    putHashMap(geneticCode, "TCT", createStringValue("S"));
    putHashMap(geneticCode, "TCC", createStringValue("S"));
    putHashMap(geneticCode, "TCA", createStringValue("S"));
    putHashMap(geneticCode, "TCG", createStringValue("S"));
    putHashMap(geneticCode, "AGT", createStringValue("S"));
    putHashMap(geneticCode, "AGC", createStringValue("S"));
    
    // Thréonine (T)
    putHashMap(geneticCode, "ACT", createStringValue("T"));
    putHashMap(geneticCode, "ACC", createStringValue("T"));
    putHashMap(geneticCode, "ACA", createStringValue("T"));
    putHashMap(geneticCode, "ACG", createStringValue("T"));
    
    // Tryptophane (W)
    putHashMap(geneticCode, "TGG", createStringValue("W"));
    
    // Tyrosine (Y)
    putHashMap(geneticCode, "TAT", createStringValue("Y"));
    putHashMap(geneticCode, "TAC", createStringValue("Y"));
    
    // Valine (V)
    putHashMap(geneticCode, "GTT", createStringValue("V"));
    putHashMap(geneticCode, "GTC", createStringValue("V"));
    putHashMap(geneticCode, "GTA", createStringValue("V"));
    putHashMap(geneticCode, "GTG", createStringValue("V"));
    
    // STOP codon
    putHashMap(geneticCode, "TAA", createStringValue("*"));
    putHashMap(geneticCode, "TAG", createStringValue("*"));
    putHashMap(geneticCode, "TGA", createStringValue("*"));
    
    return geneticCode;
}

/**
 * Translate a gene sequence (genomic) into a protein sequence
 * 
 * @param rnaSequence string with the gene sequence
 * @param geneticCode HashMap with the genetic code
 * @return String containing the proteic sequence
 */
char* translateRNA(char* rnaSequence, HashMap* geneticCode) {
    int rnaLength = strlen(rnaSequence);
    int proteinLength = (rnaLength / 3) + 1; // +1 for null character
    
    char* protein = malloc(proteinLength * sizeof(char));
    if (protein == NULL) return NULL;
    
    int proteinIndex = 0;

    for (int i = 0; i < rnaLength - 2; i += 3) {
        char codon[4] = {0}; // 3 char + null char
        codon[0] = rnaSequence[i];
        codon[1] = rnaSequence[i+1];
        codon[2] = rnaSequence[i+2];
        
        GenericValue* amino;
        if (getHashMapValue(geneticCode, codon, &amino) == 0) {
            if (strcmp(amino->data.stringValue, "*") == 0) 
                break;
            
            protein[proteinIndex++] = amino->data.stringValue[0];
        } else {
            protein[proteinIndex++] = 'X'; // unknown amino acid
        }
    }
    
    protein[proteinIndex] = '\0'; // end the string
    return protein;
}

#endif // GENETIC_CODE_H