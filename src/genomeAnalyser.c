#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"../include/HashMap.h"           
#include"../include/linkedList.h"           
#include"../include/genomeAnalyser.h"            
      
char* extractGenomeFromFastaFile(FILE *file) {
    int genomeLength = 0;
    int genomeBufferSize = 1000000;
    char* genomeString = malloc(sizeof(char) * genomeBufferSize); // init to 1 Mbp;
    if (genomeString == NULL) return NULL;

    // extract the genome sequence from the fasta file
    char bufferReader[150];
    while(fgets(bufferReader, 150, file)) {
        if (bufferReader[0] == '>') // skip fasta first line
            continue;

        int size = strlen(bufferReader);
        for(int i = 0; i < size; i++) {
            char nucl = bufferReader[i];
            if (nucl == '\n') // skip the end of line character
                continue;
            
            genomeString[genomeLength] = nucl;
            genomeLength++;
            // if we reached the limit, we have to increase it
            if (genomeLength >= genomeBufferSize) {
                genomeBufferSize *= 2;
                char* newGenomeString = malloc(sizeof(char) * genomeBufferSize);
                if (newGenomeString == NULL) return NULL;

                memcpy(newGenomeString, genomeString, genomeLength);
                free(genomeString);
                genomeString = newGenomeString;
            } 
        }
    }
    return genomeString;
}


void updateNucleotideCount(HashMap* nucleotide_count, char nucleotide) {
    // convert the char to a string for the hashmap
    char strNucl[2];
    strNucl[0] = nucleotide;
    strNucl[1] = '\0';
    if (containsKey(nucleotide_count, strNucl)) {
        GenericValue* nbNucl;
        getHashMapValue(nucleotide_count, strNucl, &nbNucl);
        GenericValue newValue = createIntValue(nbNucl->data.intValue + 1);
        putHashMap(nucleotide_count, strNucl, newValue);
    } else {
        GenericValue nbNucl = createIntValue(0);
        putHashMap(nucleotide_count, strNucl, nbNucl);
    }

}