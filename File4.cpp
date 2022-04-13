#pragma hdrstop
#pragma argsused

#include <windows.h>
#include <iostream>
#include <cstdlib>
#include "NTFSDriverPCH1.h"

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <stdio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleOutputCP(1251);

	BYTE databuffer[512];
	NTFS_BootRecord *pNTFS_BootRecord = (NTFS_BootRecord*)databuffer;

	HANDLE filehandle = CreateFileW(
	L"\\\\.\\C:",
	GENERIC_READ,
	FILE_SHARE_READ | FILE_SHARE_WRITE,
	NULL,
	OPEN_EXISTING,
	FILE_ATTRIBUTE_NORMAL,
	NULL);

	if (filehandle == INVALID_HANDLE_VALUE) {
		std::cout << "Для корректного запуска файла требуются права администратора.\n";
		system("pause");
		exit(-1);
	}

	LARGE_INTEGER sectoroffset;
	sectoroffset.QuadPart = 0;

	unsigned long currentposition = SetFilePointer(
	filehandle,
	sectoroffset.LowPart,
	&sectoroffset.HighPart,
	FILE_BEGIN);

	DWORD bytestoread = 512;
	DWORD bytesread;

	bool readresult = ReadFile(
	filehandle,
	databuffer,
	bytestoread,
	&bytesread,
	NULL);

	if(readresult == false || bytesread != bytestoread)
	{
		std::cout << "Ошибка чтения последовательности байт:)\n";
		system("pause");
		exit(-1);
	}

	UINT name_lo = pNTFS_BootRecord->name_lo;
	UINT name_hi = pNTFS_BootRecord->name_hi;
	USHORT sec_size = pNTFS_BootRecord->sec_size;
	BYTE secs_cluster = pNTFS_BootRecord->secs_cluster;
	ULONGLONG num_secs = pNTFS_BootRecord->num_secs;
	ULONGLONG mft_clus = pNTFS_BootRecord->mft_clus;
	ULONGLONG mft2_clus = pNTFS_BootRecord->mft2_clus;
	UINT mft_rec_size = pNTFS_BootRecord->mft_rec_size;
	UINT volume_id_lo = pNTFS_BootRecord->volume_id_lo;
	UINT volume_id_hi = pNTFS_BootRecord->volume_id_hi;
	USHORT sign = pNTFS_BootRecord->sign;

	if (name_lo != 1397118030 && name_hi != 538976288) {
		std::cout << "Error: The transition to the bootstrap program was not detected.\nTry again.\n";
		system("pause");
		exit(-1);
	}
	if (sign != 43605) {
		std::cout << "Error: The signature not detected.\nTry again.\n";
		system("pause");
		exit(-1);
	}
	std::cout << "Количество байт в секторе: " << sec_size << "\n";
	std::cout << "Количество секторов в кластере " << static_cast<int>(secs_cluster) << "\n";
	std::cout << "Количество секторов в блоке " << num_secs << "\n";
	std::cout << "Начальный кластер MFT таблицы: " << mft_clus << "\n";
	std::cout << "Начальный кластер копии MFT таблицы:" << mft2_clus << "\n";
	std::cout << "Размер записи MFT в кластерах: " << mft_rec_size << "\n";
	std::cout << "Наименьшее слово в загрузочном диске: " << volume_id_lo << "\n";
	std::cout << "Наибольшее слово в загрузочном диске: " << volume_id_hi << "\n";

	std::cout << "\n";
	system("pause");
	CloseHandle(filehandle);
	return 0;
}
