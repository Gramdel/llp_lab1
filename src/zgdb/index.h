#ifndef _INDEX_H_
#define _INDEX_H_

#include <stdbool.h>
#include "format.h"

/* ��������� ��� id, ������������ � ����� */
typedef struct __attribute__((packed)) blockId {
	uint32_t timestamp; // ����� �������� ����� � �������� � ����� UNIX
	uint64_t offset : 40; // (5 ����) �������� ����� ������������ ����� �������� � ����� �� ������ �������� �����
} blockId;

/* ����� ��� �������� */
typedef enum indexFlag {
	INDEX_NEW = 0, // ������ ������ ��� ������ � ��� �� �������� � �����
	INDEX_ALIVE = 1, // ������ �������� � ��������������� ("������") �����
	INDEX_DEAD = 2 // ������ �������� � ����������������� ("��������") �����
} indexFlag;

/* ��������� ��� ������� � ZGDB ����� */
typedef struct __attribute__((packed)) zgdbIndex {
	uint8_t flags; // ����� (�.�. ����-���������� �� �������)
	blockId id; // id, ����������� � �����
	uint64_t offset : 40; // �������� ����� ������������ ����� �������� � �����
} zgdbIndex;

/* ������� ��� ��������� ������� �� ��� ����������� ������. ���������� null ��� ������� */
zgdbIndex* getIndexByOrder(zgdbFile* file, uint64_t i);

/* ������� ��� ��������� �������, ����������� ���������� id. ���������� null ��� ������� */
zgdbIndex* getIndexById(zgdbFile* file, blockId id);

/* ������� ��� ��������� ������ �������, ����������� ���������� id. ���������� indexNumber �� ��������� ��� ������� */
uint64_t getIndexOrderById(zgdbFile* file, blockId id);

/* �������, ���������� ������ ��� INDEX_DEAD �� ��� ����������� ������. ���������� false ��� ������� */
bool killIndexByOrder(zgdbFile* file, uint64_t i);

/* �������, ���������� ������, ���������� ���������� id, ��� INDEX_DEAD. ���������� false ��� ������� */
bool killIndexById(zgdbFile* file, blockId id);

/* �������, "�������������" ���� � INDEX_DEAD ��� INDEX_NEW ������� � �������� ��� INDEX_ALIVE. ������� ��������� ������� �����. ���������� false ��� ������� */
bool attachBlockToIndex(zgdbFile* file, uint64_t order, blockId id, uint64_t offset);

/* �������, �������� offset � INDEX_ALIVE �������. ��� ������� ���������� false */
bool changeOffsetByOrder(zgdbFile* file, uint64_t order, uint64_t offset);

#endif