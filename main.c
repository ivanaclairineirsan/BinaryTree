/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ivana
 *
 * Created on February 8, 2017, 11:33 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define length 40
unsigned char array[length];
unsigned char comparator[1];
unsigned short currFree = 0;
unsigned short leftBefore = 0;
unsigned short rightBefore = 0;

struct Node{
    unsigned char key;
    unsigned short left;
    unsigned short right;
};

unsigned short getIndex (unsigned short idx);

void putIndex (unsigned short idx, unsigned short start);
void writeArrayToFile();
unsigned char* readFile();
void printArray (unsigned char* test);
void insertChar (char key, int lastMatch);
void insertString(char* input);

int main(int argc, char** argv) {
    
    
    insertString("udin");
    insertString("uda");
    writeArrayToFile();
    unsigned char *test = readFile();
    
    return (EXIT_SUCCESS);
}

unsigned short getIndex (unsigned short idx){
    return (array[idx] << 8) | array[idx+1];
}

void putIndex (unsigned short idx, unsigned short start){
    array[start] = idx >> 8;
    array[start+1] = idx;
}

void writeArrayToFile(){
    FILE *file = fopen("arrayFile.txt", "wb");
    fwrite(array, sizeof(unsigned char), sizeof(array), file);
    fclose(file);
}

unsigned char* readFile(){
    printf("test");
    unsigned char read[length];
    FILE *file = fopen("arrayFile.txt", "rb");
    fread(read, sizeof(unsigned char), sizeof(read), file );
    fclose(file);
    
    int i;
    printf(" --- Print isi file --- \n");
    printArray(read);
    return read;
}

void printArray(unsigned char* test){
    int i;
    for(i=0; i< length; i++)
        printf("isi test[%d]: %u \n", i, test[i]);
}

void insertChar(char key, int lastMatch){
    printf("free before: %d \n", currFree);
    array[currFree] = key;
    putIndex(0, currFree+1);
    putIndex(0, currFree+3);
    
    if(currFree > 0 && lastMatch == -1){
        putIndex(currFree, currFree-4);
    }
    if(currFree > 0 && lastMatch != -1){
        putIndex(currFree, lastMatch+3);
    }
    
    currFree += 5;
    printf("free after: %d \n", currFree);
}

void insertString(char* input){
    int checker = 0;
    int idxInput = 0;
    char stop='0';
    
    while(stop == '0'){
        comparator[0] = input[idxInput];
        printf("array[%d]: %u -- input[%d]: %u \n", checker, array[checker], idxInput, comparator[0]);
        if((char) array[checker] == comparator[0]) {
            int nextIdx = getIndex(checker+1);
            if(nextIdx != -1)
            {
                checker = getIndex(checker+1);
                idxInput++;
            }
            else {
                printf("checker: %d \n", checker);
                stop = '1';
            }
        } else{
            printf("checker: %d \n", checker);
            stop = '1';
        }
    }
    
    int inputSize = (int) strlen(input);
    int i=idxInput;
    insertChar(input[i], checker);
    for(i=idxInput+1; i<inputSize; i++){
        insertChar(input[i], -1);
    }
}