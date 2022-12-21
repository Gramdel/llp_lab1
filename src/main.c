﻿#include <stdio.h>
#include <malloc.h>
#include "zgdb/document_public.h"
//#include "zgdb/element_public.h" TODO: почему-то есть проблемы
#include "zgdb/element.h"

int main(int argc, char** argv) {
    zgdbFile* file = loadFile("test");
    if (!file) {
        file = createFile("test");
        if (!file) {
            printf("Error\n");
            exit(-1);
        }
    }
    //printf("%08X\n", file->header.fileType);

    documentSchema* schema1 = createSchema(2); // size 64
    if (schema1) {
        addIntegerToSchema(schema1, "first1", 111);
        addIntegerToSchema(schema1, "first2", 222);
    }

    documentSchema* schema2 = createSchema(2); // size 82
    if (schema2) {
        addIntegerToSchema(schema2, "sec1", 123);
        addIntegerToSchema(schema2, "sec2", 456);
        addIntegerToSchema(schema2, "sec3", 789);
    }

    documentSchema* schema3 = createSchema(2); // size 112
    if (schema3) {
        addIntegerToSchema(schema3, "thi1", 123);
        addIntegerToSchema(schema3, "thi2", 456);
        addIntegerToSchema(schema3, "thi3", 789);
        addBooleanToSchema(schema3, "isFirst", false);
        addBooleanToSchema(schema3, "isFoo", true);
        addStringToSchema(schema3, "testString", "BLA");
    }

    documentSchema* schema4 = createSchema(2); // size 168
    if (schema4) {
        addIntegerToSchema(schema4, "fou1", 123);
        addIntegerToSchema(schema4, "fou2", 456);
        addIntegerToSchema(schema4, "fou3", 789);
        addBooleanToSchema(schema4, "isFirst", true);
        addDoubleToSchema(schema4, "testDouble", 128.128);
        addStringToSchema(schema4, "testString", "I AM STRING");
        addDocumentToSchema(schema4, "testDoc", 0);
    }

    printf("i: %d\n", writeDocument(file, schema1)); // 0
    printf("i: %d\n", writeDocument(file, schema3)); // 1
    printf("i: %d\n", writeDocument(file, schema3)); // 2
    printf("i: %d\n", writeDocument(file, schema2)); // 3
    printf("i: %d\n", writeDocument(file, schema2)); // 4
    printf("i: %d\n", writeDocument(file, schema2)); // 5
    printf("i: %d\n", writeDocument(file, schema2)); // 6
    printf("i: %d\n", writeDocument(file, schema2)); // 7
    printf("i: %d\n", writeDocument(file, schema2)); // 8
    printf("i: %d\n", writeDocument(file, schema2)); // 9

    printf("removed? %d\n", removeDocument(file, 1));
    //printf("i: %d\n", writeDocument(file, schema3)); // 1


    //printf("updated? %d\n", updateIntegerValue(file, "fou2", 808, 2));
    //printf("updated? %d\n", updateBooleanValue(file, "isFirst", false, 2));
    //printf("updated? %d\n", updateDoubleValue(file, "testDouble", -2.5, 2));
    printf("updated? %d\n", updateStringValue(file, "testString", "I AM STRINGG", 2));
    //printf("updated? %d\n", updateDocumentValue(file, "testDoc", 1, 2));
    printf("i: %d\n", writeDocument(file, schema4)); // 9

    element el1 = readElement(file, "fou2", 2);
    element el2 = readElement(file, "isFirst", 2);
    element el3 = readElement(file, "testDouble", 2);
    element el4 = readElement(file, "testString", 2);
    element el5 = readElement(file, "testDoc", 2);

    printElement(el1);
    printElement(el2);
    printElement(el3);
    printElement(el4);
    printElement(el5);

    destroyElement(el4);
    //*/

    destroySchema(schema1);
    destroySchema(schema2);
    destroySchema(schema3);
    destroySchema(schema4);

    closeFile(file);
    return 0;
}