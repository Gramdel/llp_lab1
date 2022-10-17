#ifndef _INDEX_H_
#define _INDEX_H_

#include <stdint.h>
#include "format.h"

/* ��������� ��� id, ������������ � ����� */
typedef struct __attribute__((packed)) blockId {
	uint32_t timestamp; // ����� �������� ����� � �������� � ����� UNIX
	uint64_t offset : 40; // �������� ����� (5 ����) ������������ ����� �������� � ����� �� ������ �������� �����
} blockId;

/* ����� ��� �������� */
typedef enum indexFlags {
	INDEX_NEW = 0, // ������ ������ ��� ������ � ��� �� �������� � �����
	INDEX_ALIVE = 1, // ������ �������� � ��������������� ("������") �����
	INDEX_DEAD = 2 // ������ �������� � ����������������� ("��������") �����
} indexFlags;

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

#endif