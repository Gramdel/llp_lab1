#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include <stdbool.h>
#include "format.h"

/* ��������� ��� id, ������������ � ��������� (����� � ����� ���� == ��������). ��� ��������� - id ������� */
typedef struct __attribute__((packed)) documentId {
	uint32_t timestamp; // ����� �������� ��������� � �������� � ����� UNIX
	uint64_t offset; // �������� ��������� ������������ ������ ����� �� ������ �������� ���������
} documentId;

/* ��������� ��� ��������� ��������� */
typedef struct __attribute__((packed)) documentHeader {
	uint64_t size : 40; // (5 ����) ������ ��������� � ������
	union {
		uint64_t indexOrder : 40; // (5 ����) ���������� ����� �������, �������������� � ���������
		uint64_t internalOffset : 40; // (5 ����) �������� ���������� ��������� �������������� �������������
	};
	documentId id; // id, ����������� � ���������
} documentHeader;

/* �������������� ��� ����� ������ � ��������� */
typedef enum elementType {
	TYPE_INT = 0x01, // ��� int32_t
	TYPE_DOUBLE = 0x02, // ��� double
	TYPE_BOOLEAN = 0x03, // ��� boolean (uint8_t)
	TYPE_STRING = 0x04, // ��� ������
	TYPE_EMBEDDED_DOCUMENT = 0x05 // ��� ���������� ���������
} elementType;

/* ����������� � ��������� */
typedef enum terminator {
	NULL_TERMINATOR = 0x00, // ���������� ��� ����� � ������ � ���������
	DOCUMENT_TERMINATOR = 0xFF, // ���������� ��� ����������� ������ ����������
	EMBEDDED_DOCUMENT_TERMINATOR = 0xFE // ���������� ��� ���������� ���������
} terminator;

/* ��������� ��� ������ */
typedef struct string {
	uint32_t size;
	unsigned char* data;
} string;

typedef struct document document;

/* ��������� ��� �������� ��������� */
typedef struct element {
	uint8_t type; // ��� ��������
	unsigned char key[13]; // ���� ��������
	union {
		int32_t integerValue;
		double doubleValue;
		uint8_t booleanValue;
		string* stringValue; // ��������� �� ������
		document* documentValue; // ��������� �� ��������� ��������
	};
} element;

/* ��������� ��� ��������� (���������) */
typedef struct document {
	documentHeader header;
	element* elements;
	size_t elementNumber;
} document;

/* ��������� ��� ����� ������ */
typedef struct documentSchema {
	element* elements;
	size_t elementNumber;
} documentSchema;

/* ������� ��� ���������� ������ � �����. ���������� false ��� ������� */
bool addIntegerToSchema(documentSchema* schema, unsigned char* key, int32_t value);

bool addDoubleToSchema(documentSchema* schema, unsigned char* key, double value);

bool addBooleanToSchema(documentSchema* schema, unsigned char* key, uint8_t value);

bool addStringToSchema(documentSchema* schema, unsigned char* key, string* value);

bool addDocumentToSchema(documentSchema* schema, unsigned char* key, document* value);

/* ������� ��� ������������� ����� � ����������� ����������� ��������� */
documentSchema createSchema(size_t elementNumber);

/* ������� ��� ���������� ������ (INDEX_NEW) ������� � ����. ���������� indexNumber �� ��������� ��� ������� */
uint64_t createIndex(zgdbFile* file);

/* ������� ��� ���������� ������ ��������� � ����. ���������� false ��� ������� */
bool createDocument(zgdbFile* file, documentSchema* schema);

#endif