#ifndef GENOME_ANALYSER_H
#define GENOME_ANALYSER_H

#include<stdio.h>
#include "HashMap.h"


typedef struct {
    int frame;
    int start;
    int end;
} GeneInfo;

/**
 * Function to update the nucleotide count for the genome
 * 
 * @param nucleotide_count the pointer to the hashmap to keep in memory the nucleotide count
 * @param nucleotide the current nucleotide
 */
void updateNucleotideCount(HashMap* map, char nucleotide);


/**
 * Function to read a fasta file (80 nucleotides by line !!!) and extract the genome to store it in a string
 */
char* extractGenomeFromFastaFile(FILE *file);


/**
 * Function to extract gene info from the fasta string
 * 
 * @param genomeLength the size of the genome string
 * @param genomeString the genome string
 * @param nucleotideCountMap the hashmap of nucleotides
 * @param nbGenesFound pointer of int to return the number of complete genes
 *  
 */
GeneInfo** extractGenesFromFastaString(int genomeLength, char* genomeString, HashMap** nucleotideCountMap, int* nbGenesFound);

/**
 * Function to free the gene info array
 */
void freeGeneInfoArray(GeneInfo** genesInfo, int nbGenes);

/**
 * Function to increase the array that store gene data
 */
GeneInfo** increaseGeneStorage(GeneInfo** genesInfo);

/**
 * Function to count the occurences of ATGC in the genome
 */
void updateNucleotideCount(HashMap* nucleotide_count, char nucleotide);

/**
 * Function to print a progress bar during gene extraction process
 */
void printProgress(int current, int total);



#endif // GENOME_ANALYSER_H