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

#define length 10
unsigned char array[length];
unsigned short place = 0;

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
void insertChar (char key);

int main(int argc, char** argv) {
    
    insertChar('a');
    
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

void insertChar(char key){
    printf("free before: %d \n", place);
    array[place] = key;
    putIndex(0, place+1);
    place += 5;
    printf("free after: %d \n", place);
}

