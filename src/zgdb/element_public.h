#ifndef _ELEMENT_PUBLIC_H_
#define _ELEMENT_PUBLIC_H_

#include <stdint.h>
#include <stdbool.h>

#include "format_public.h"

/* Структура для строки. В конце строки обязательно должен быть терминатор! */
typedef struct str str;

/* Тип элемента (а точнее, тип значения элемента). */
typedef enum elementType {
    TYPE_NOT_EXIST = 0, // тип, сигнализирующий об ошибке
    TYPE_INT = 1, // для int32_t
    TYPE_DOUBLE = 2, // для double
    TYPE_BOOLEAN = 3, // для boolean (uint8_t)
    TYPE_STRING = 4, // для строки
    TYPE_EMBEDDED_DOCUMENT = 5 // для вложенного документа
} elementType;

/* Структура для элемента документа. */
typedef struct element element;

/* Функция для чтения элемента из документа по ключу.
 * Возвращает элемент с типом TYPE_NOT_EXIST при неудаче.
 * ВНИМАНИЕ: Если тип полученного элемента - TYPE_STRING, то нужно вызвать destroyElement, чтобы очистить память. */
element readElement(zgdbFile* file, char* neededKey, uint64_t i);

/* Функция для уничтожения элемента типа TYPE_STRING.
 * Если тип другой, то функция ничего не делает, поэтому можно спокойно её вызывать после каждого readElement
 * в качестве перестраховки. */
void destroyElement(element el);

/* Функция для вывода элемента на экран. */
void printElement(element el);

/* Функция для получения типа элемента. */
elementType getTypeOfElement(element el);

/* Функция для получения значения из элемента типа TYPE_INT. */
int32_t getIntegerValue(element el);

/* Функция для получения значения из элемента типа TYPE_DOUBLE. */
double getDoubleValue(element el);

/* Функция для получения значения из элемента типа TYPE_BOOLEAN. */
uint8_t getBooleanValue(element el);

/* Функция для получения значения из элемента типа TYPE_STRING. */
str getStringValue(element el);

/* Функция для получения значения из элемента типа TYPE_EMBEDDED_DOCUMENT. */
uint64_t getDocumentValue(element el);

/* Функция для обновления значения у элемента типа TYPE_INT.
 * Возвращает false при неудаче. */
bool updateIntegerValue(zgdbFile* file, char* neededKey, int32_t value, uint64_t i);

/* Функция для обновления значения у элемента типа TYPE_DOUBLE.
 * Возвращает false при неудаче. */
bool updateDoubleValue(zgdbFile* file, char* neededKey, double value, uint64_t i);

/* Функция для обновления значения у элемента типа TYPE_BOOLEAN.
 * Возвращает false при неудаче. */
bool updateBooleanValue(zgdbFile* file, char* neededKey, uint8_t value, uint64_t i);

/* Функция для обновления значения у элемента типа TYPE_STRING.
 * Возвращает false при неудаче. */
bool updateStringValue(zgdbFile* file, char* neededKey, char* value, uint64_t i);

/* Функция для обновления значения у элемента типа TYPE_EMBEDDED_DOCUMENT.
 * Возвращает false при неудаче. */
bool updateDocumentValue(zgdbFile* file, char* neededKey, uint64_t value, uint64_t i);

#endif