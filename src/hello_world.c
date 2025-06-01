#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"arrayUtils.h"
#include"linkedList.h"
#include"HashMap.h"
#include"genomeAnalyser.h"


void updateBufferCodon(char newNucleotide, char* bufferCodon) {
    bufferCodon[0] = bufferCodon[1];
    bufferCodon[1] = bufferCodon[2];
    bufferCodon[2] = newNucleotide;
}


int main(void) {
    printf("\n\n\n\n");
    printf("Test file reader\n");

    FILE *file;

    file = fopen("ressources/test.fasta", "r");
    if (file == NULL) {
        printf("The file is not found.\n");
        fclose(file);
        return -1;
    }
    // extract the genome string
    // TODO adjust string capcity to avoid unused ram use ?
    char* genomeString = extractGenomeFromFastaFile(file);
    fclose(file);
    if (genomeString == NULL) {
        printf("Error, cannot allocate enough memory to read the fasta file.\n");
        return -1;
    }




    char bufferCodon[4] = "XXX\0";
    int nbCompleteGenes = 0;
    HashMap** genesInfo = malloc(sizeof(HashMap) * 100); // array of hashmap to store start and end index of the gene,the gene frame, the protein sequence and the gene sequence

    for (int i = 0; i < 100; i++) {
        genesInfo[i] = NULL;
    }

    HashMap* nucleotideCountMap = createHashMap(10);
    // int nucleotideCount = 0;
    // boolean to discard sub ATG codons in the same gene
    HashMap* frameBuilding[3] = {NULL, NULL, NULL};
    int genomeLength = strlen(genomeString);
    
    for (int i = 0; i < genomeLength; i++) {
        char nucleotide = genomeString[i];
        updateBufferCodon(nucleotide, bufferCodon);

        // count the nucleotides
        updateNucleotideCount(nucleotideCountMap, nucleotide);

        // start a new ORF if the codon = ATG
        int frame = i % 3;
        if (strcmp(bufferCodon, "ATG") == 0) {
            // if we have detected a new gene in a new frame
            if (frameBuilding[frame] == NULL) {
                HashMap* newGeneInfo = createHashMap(10);
                putHashMap(newGeneInfo, "start", createIntValue(i));
                putHashMap(newGeneInfo, "frame", createIntValue(frame));
                frameBuilding[frame] = newGeneInfo;
            }
        } else if (strcmp(bufferCodon, "TAA") == 0 || strcmp(bufferCodon, "TGA") == 0 || strcmp(bufferCodon, "TAG") == 0) {

            HashMap* geneInfo = frameBuilding[frame];
            if (geneInfo == NULL)
                continue;
            putHashMap(geneInfo, "end", createIntValue(i));
            genesInfo[nbCompleteGenes] = geneInfo;
            nbCompleteGenes ++;
            frameBuilding[frame] = NULL;
        }
    }

    free(genomeString);

    if (nbCompleteGenes == 0) {
        printf("No complete genes detected.\n");
        return 0;
    }
    
    printf("Complete genes:\n");
    for (int j = 0; j < nbCompleteGenes; j++) {
        HashMap* geneMap = genesInfo[j];
        toPrintHashMap(geneMap);
        freeHashMap(geneMap);
    }
    printf("Incomplete genes:\n");
    for (int i = 0; i < 3; i++) {
        if (frameBuilding[i] != NULL) {
            freeHashMap(frameBuilding[i]);
            frameBuilding[i] = NULL;
        }
    }
    printf("Nucleotide count:\n");
    toPrintHashMap(nucleotideCountMap);
    freeHashMap(nucleotideCountMap);
    free(genesInfo);
    printf("\n\n\n\n");

    return 0;
}

