#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"../include/HashMap.h"           
#include"../include/linkedList.h"           
#include"../include/genomeAnalyser.h"


void updateBufferCodon(char newNucleotide, char* bufferCodon) {
    bufferCodon[0] = bufferCodon[1];
    bufferCodon[1] = bufferCodon[2];
    bufferCodon[2] = newNucleotide;
}

      
char* extractGenomeFromFastaFile(FILE *file) {
    int genomeLength = 0;
    int genomeBufferSize = 5000000; // init value for 5Mbp genome
    char* genomeString = malloc(sizeof(char) * genomeBufferSize); // init to 5 Mbp;
    if (genomeString == NULL) return NULL;

    // extract the genome sequence from the fasta file
    char bufferReader[82];
    while(fgets(bufferReader, 82, file)) {
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
    genomeString[genomeLength] = '\0';
    return genomeString;
}


void updateNucleotideCount(HashMap* nucleotide_count, char nucleotide) {
    // convert the char to a string for the hashmap
    char strNucl[2];
    strNucl[0] = nucleotide;
    strNucl[1] = '\0';
    GenericValue* nbNucl;
    if (getHashMapValue(nucleotide_count, strNucl, &nbNucl) == 0) {
        GenericValue newValue = createIntValue(nbNucl->data.intValue + 1);
        putHashMap(nucleotide_count, strNucl, newValue);
    } else {
        GenericValue nbNucl = createIntValue(0);
        putHashMap(nucleotide_count, strNucl, nbNucl);
    }

}

int initGenesNb = 10000;

GeneInfo** increaseGeneStorage(GeneInfo** genesInfo) {
    int newCapacity = initGenesNb * 2;
    GeneInfo** newGenesInfo = malloc(sizeof(GeneInfo*) * newCapacity);
    if (newGenesInfo == NULL) return NULL;
    // copy pointers, so no need to free original structures
    memcpy(newGenesInfo, genesInfo, initGenesNb * sizeof(GeneInfo*));
    free(genesInfo);
    initGenesNb = newCapacity;
    return newGenesInfo;
}

void freeGeneInfoArray(GeneInfo** genesInfo, int nbGenes) {
    if (genesInfo == NULL) return;
    for (int i = 0; i < nbGenes; i++) {
        if (genesInfo[i] != NULL) 
            free(genesInfo[i]);
    }
    free(genesInfo);
}



GeneInfo** extractGenesFromFastaString(int genomeLength, char* genomeString, HashMap** nucleotideCountMap, int* nbGenesFound) {
    char bufferCodon[4] = "XXX\0";
    int nbCompleteGenes = 0;
    // boolean to discard sub ATG codons in the same gene
    GeneInfo* frameBuilding[3] = {NULL, NULL, NULL};
    
    GeneInfo** genesInfo = malloc(sizeof(GeneInfo*) * initGenesNb); 
    if (genesInfo == NULL) return NULL;
    // iterate on the genome
    for (int i = 0; i < genomeLength; i++) {
        if (i % 1000 == 0 || i == genomeLength-1) {
            printProgress(i, genomeLength);
        }        
        char nucleotide = genomeString[i];
        updateBufferCodon(nucleotide, bufferCodon);
        // count the nucleotides
        updateNucleotideCount(*nucleotideCountMap, nucleotide);

        int frame = i % 3;
        if (strcmp(bufferCodon, "ATG") == 0) {
            if (frameBuilding[frame] == NULL) {
                GeneInfo* newGeneInfo = malloc(sizeof(GeneInfo));
                if (newGeneInfo == NULL) continue;
                
                newGeneInfo->frame = frame;
                newGeneInfo->start = i - 2;  // index of the A of ATG
                newGeneInfo->end = 0;        // updated later
                frameBuilding[frame] = newGeneInfo;
            }
        } else if (strcmp(bufferCodon, "TAA") == 0 || 
                  strcmp(bufferCodon, "TGA") == 0 || 
                  strcmp(bufferCodon, "TAG") == 0) {

            GeneInfo* geneInfo = frameBuilding[frame];
            if (geneInfo == NULL) {continue;}
                
            geneInfo->end = i + 1;  // index of the last nucleotide of the STOP codon
            genesInfo[nbCompleteGenes] = geneInfo;
            nbCompleteGenes++;
            frameBuilding[frame] = NULL;
            if (nbCompleteGenes == initGenesNb)
                genesInfo = increaseGeneStorage(genesInfo);
        }
    }
    printf("Nucleotide %d/%d", genomeLength, genomeLength);

    
    // clean incomplete genes
    for (int i = 0; i < 3; i++) {
        if (frameBuilding[i] != NULL)
            free(frameBuilding[i]);
    }
    
    // return the genes number
    if (nbCompleteGenes > 0) {
        *nbGenesFound = nbCompleteGenes;
        return genesInfo;
    } else {
        printf("No complete genes detected.\n");
        free(genesInfo);
        return NULL;
    }
}

void printProgress(int current, int total) {
    float percentage = (float)current/total*100;
    int barWidth = 50;
    int pos = barWidth * current / total;
    printf("\r[");
    for (int i = 0; i < barWidth; i++) {
        if (i < pos) printf("=");
        else if (i == pos) printf(">");
        else printf(" ");
    }
    
    printf("] %d/%d (%.2f%%)   ", current, total, percentage);
    
    fflush(stdout);
}