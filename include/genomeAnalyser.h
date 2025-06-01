#ifndef GENOME_ANALYSER_H
#define GENOME_ANALYSER_H

#include<stdio.h>
#include "HashMap.h"

/**
 * Function to update the nucleotide count for the genome
 * 
 * @param nucleotide_count the pointer to the hashmap to keep in memory the nucleotide count
 * @param nucleotide the current nucleotide
 */
void updateNucleotideCount(HashMap* map, char nucleotide);


char* extractGenomeFromFastaFile(FILE *file);

#endif // GENOME_ANALYSER_H