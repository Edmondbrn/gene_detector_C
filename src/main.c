#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"arrayUtils.h"
#include"linkedList.h"
#include"HashMap.h"
#include"genomeAnalyser.h"
#include"geneticCode.h"


void printGeneSequence(char* genomeString, int start, int end, HashMap* geneticCode) {
    int geneSize = end - start + 1;
    char* geneSequence = malloc(geneSize + 1); // +1 for '\0'
    if (geneSequence == NULL) {
        printf("Memory allocation error\n");
        return;
    }  
    // copy the gene sequence  
    snprintf(geneSequence, geneSize + 1, "%.*s", geneSize, genomeString + start);

    printf("Gene sequence (%d bp):\n", geneSize);

    for (int i = 0; i < geneSize; i += 80) {
        printf("%-8d", start + i + 1); // Position
        
        int lineLength = (i + 80 < geneSize) ? 80 : geneSize - i; // adapt for the last line
        printf("%.*s\n", lineLength, geneSequence + i);
    }

    if (geneticCode != NULL) {
        char* protein = translateRNA(geneSequence, geneticCode);
        if (protein != NULL) {
            int proteinLength = strlen(protein);
            printf("\nProteic sequence (%d bp):\n", proteinLength);
            for (int i = 0; i < proteinLength; i += 80) {
                printf("%-8d",  i + 1); // Position

                printf("%.*s\n", 
                       (i + 80 < proteinLength) ? 80 : proteinLength - i, 
                       protein + i);
            }
            free(protein);
        }
    }
    
    free(geneSequence);
    printf("\n");

    printf("\n\n");
}


int main(void) {
    printf("\n\n\n\n");

    FILE *file;
    printf("Reading fasta file...\n");
    file = fopen("ressources/GCF_000005845.2_ASM584v2_genomic.fna", "r");
    if (file == NULL) {
        printf("The file is not found.\n");
        fclose(file);
        return -1;
    }
    // extract the genome string
    char* genomeString = extractGenomeFromFastaFile(file);
    fclose(file);
    if (genomeString == NULL) {
        printf("Error, cannot allocate enough memory to read the fasta file.\n");
        return -1;
    }
    HashMap* nucleotideCountMap = createHashMap(10);
    if (nucleotideCountMap == NULL) {
        free(genomeString);
        return -1;
    }

    int genomeLength = strlen(genomeString);
    printf("Genome length: %d.\n", genomeLength);
    int nbGenes = 0;
    GeneInfo** genesInfo = extractGenesFromFastaString(genomeLength, genomeString, &nucleotideCountMap, &nbGenes);
    
    if (genesInfo == NULL) {
        free(genomeString);
        return -1;
    }

    HashMap* geneticCode = initGeneticCode();
    
    for (int i = 0; i < nbGenes; i ++) {
        GeneInfo* geneInfo = genesInfo[i];
        printf("=================================\n");
        printf("Gene start %d, gene end %d, gene frame %d\n", geneInfo->start, geneInfo->end, geneInfo->frame);
        printGeneSequence(genomeString, geneInfo->start, geneInfo->end, geneticCode);

    }
    toPrintHashMap(nucleotideCountMap);

    free(genomeString);
    freeGeneInfoArray(genesInfo, nbGenes);
    freeHashMap(nucleotideCountMap);
    printf("\n\n\n\n");

    return 0;
}


