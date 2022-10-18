#ifndef _FORMAT_H_
#define _FORMAT_H_

#include <stdint.h>
#include <stdio.h>

/* ��������� ��� ��������� ZGDB ����� */
typedef struct __attribute__((packed)) zgdbHeader {
	uint32_t fileType; // ������ ���� �������� 4 ����� � UTF-8: ZGDB
	uint64_t indexNumber : 40; // (5 ����) ���������� ���� �������� �����
} zgdbHeader;

/* ������ ��� ����� �������� �������� ��������� ����� � ��������� ������ */
typedef struct zgdbFile {
	FILE* file; // ��������� �� �������� ����
	zgdbHeader* header; // ��������� �� ���������
} zgdbFile;

/* ������� ��� �������� ��� �������� ����� */
zgdbFile* loadOrCreateFile(const char* fileName);

/* ������� ��� �������� ����� */
uint8_t closeFile(zgdbFile* file);

/* ������� ��� ���������� ��������� */
uint8_t saveHeader(zgdbFile* file);

#endif