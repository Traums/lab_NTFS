#ifdef _WIN32
#include <tchar.h>
#endif
#include <windows.h>
#pragma once
#pragma pack(push,1)

 typedef struct
{
	BYTE    jump[3];  //    jmp
	UINT name_lo;   //      oem_lo
	UINT name_hi;   // oem_hi
	USHORT  sec_size;  //         ���� �� ������
	BYTE    secs_cluster;   //    �������� �� �������
	BYTE    reserved_0[7];
	BYTE    media_desc;          //
	UINT16  reserved_2;
	UINT16  secs_track;            // ���-�� �������� �� �������
	UINT16  num_heads;               //  ���-�� ���� �������
	BYTE    reserved_3[8];
	UINT16  reserved_4;
	UINT16  reserved_5;
	ULONGLONG  num_secs;               //  ���-�� �������� � �������
	ULONGLONG  mft_clus;                 //   ����� �������� MFT
	ULONGLONG  mft2_clus;                 //   ����� �������� ����� MFT
	UINT  mft_rec_size;                 //    ������ MFT � ���������
	UINT  buf_size;                    //      ������ ������ ������� � ���������
	UINT  volume_id_lo;                 //  ����� ��������� �����
	UINT volume_id_hi;
	BYTE Padding[0x1AE];
	USHORT sign;                         //���������
} NTFS_BootRecord;
# pragma pack(pop)