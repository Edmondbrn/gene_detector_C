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
    char* genomeString = extractGenomeFromFastaFile(file);
    fclose(file);
    if (genomeString == NULL) {
        printf("Error, cannot allocate enough memory to read the fasta file.\n");
        return -1;
    }




    // char bufferCodon[4] = "XXX\0";
    // HashMap** geneInfo = malloc(sizeof(HashMap) * 100); // array of hashmap to store start and end index of the gene,the gene frame, the protein sequence and the gene sequence

    // HashMap* map = createHashMap(10);
    // int nuclotideCount = 0;
    // while(fgets(bufferReader, 150, file)) {

        
    //     int size = strlen(bufferReader);
    //     for(int i = 0; i < size; i++) {


    //         char nucleotide = bufferReader[i];
    //         updateBufferCodon(nucleotide, bufferCodon);
            
    //         // count the nucleotides
    //         updateNucleotideCount(map, nucleotide);
    //         // start a new ORF if the codon = ATG
    //         if (strcmp("ATG", bufferCodon) == 0) {
                
    //             int geneFrame = nuclotideCount % 3;
    //             int geneStart = nuclotideCount + 1;
    //             int geneLength = 3;
    //             char orfNucl;
    //             // finish the current file line
    //             for (int j = i = 1; j < size; j++) {
    //                 orfNucl = bufferReader[j];
    //                 updateBufferCodon(orfNucl, bufferCodon); // update the codon

    //                 nuclotideCount++;
    //                 geneLength++;
    //             }


    //         }
    //             // extractORF(file, bufferReader, map)
                
    //         nuclotideCount++;
    //     }
    // }

    // toPrintHashMap(map);
    // freeHashMap(map);
    free(genomeString);


    printf("\n\n\n\n");

    return 0;
}

