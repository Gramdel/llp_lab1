#ifndef _INDEX_H_
#define _INDEX_H_

#include <stdbool.h>
#include "format.h"

/* ����� ��� �������� */
typedef enum indexFlag {
	INDEX_NEW = 0, // ������ ������ ��� ������ � ��� �� �������� � �����
	INDEX_ALIVE = 1, // ������ �������� � ��������������� ("������") �����
	INDEX_DEAD = 2 // ������ �������� � ����������������� ("��������") �����
} indexFlag;

/* ��������� ��� ������� � ZGDB ����� */
typedef struct __attribute__((packed)) zgdbIndex {
	uint8_t flags; // ����� (�.�. ����-���������� �� �������)
	uint64_t offset; // �������� ����� ������������ ������ �����
} zgdbIndex;

/* ������� ��� ��������� ������� �� ��� ����������� ������. ���������� null ��� ������� */
zgdbIndex* getIndex(zgdbFile* file, uint64_t i);

/* �������, ���������� ������ ��� INDEX_DEAD �� ��� ����������� ������. ���������� false ��� ������� */
bool killIndex(zgdbFile* file, uint64_t i);

/* �������, �������� offset � INDEX_ALIVE �������. ��� ������� ���������� false */
bool changeOffset(zgdbFile* file, uint64_t order, uint64_t offset);

#endif