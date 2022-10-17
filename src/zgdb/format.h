#ifndef _FORMAT_H_
#define _FORMAT_H_

#include <stdint.h>
#include <stdio.h>

/* ��������� ��� ��������� ZGDB ����� */
typedef struct __attribute__((packed)) zgdbHeader {
	uint32_t fileType; // ������ ���� �������� 4 ����� � UTF-8: ZGDB
	uint64_t indexNumber; // ���������� ���� �������� �����
} zgdbHeader;

/* ������ ��� ����� �������� �������� ��������� ����� � ��������� ������ */
typedef struct zgdbFile {
	FILE* file; // ��������� �� �������� ����
	zgdbHeader* header; // ��������� �� ���������
} zgdbFile;

/* ������� ��� �������� ��� �������� ����� */
zgdbFile* loadOrCreateFile(const char* fileName);

/* ������� ��� �������� ����� */
int closeFile(zgdbFile* file);

/* ������� ��� ���������� ��������� */
int saveHeader(zgdbFile* file);

#endif