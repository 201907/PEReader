#include "PEData.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

PEData::PEData(string exePath) :exePath(exePath) {
	if (!(hFile = CreateFile(exePath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, 0))) {
		throw hFile;
	}
	if (!(hMapObject = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL))) {
		throw hMapObject;
	}
	if (!(uFileMap = static_cast<PUCHAR>(MapViewOfFile(hMapObject, FILE_MAP_READ, 0, 0, 0)))) {
		throw uFileMap;
	}
	if ((dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(uFileMap))->e_magic != IMAGE_DOS_SIGNATURE) {
		throw dosHeader;
	}
	if ((ntHeader = reinterpret_cast<PIMAGE_NT_HEADERS32>(uFileMap + dosHeader->e_lfanew))->Signature != IMAGE_NT_SIGNATURE) {
		throw ntFHeader;
	}
	ntFHeader = &(ntHeader->FileHeader);
	ntOHeader = &(ntHeader->OptionalHeader);
	secHeader = reinterpret_cast<PIMAGE_SECTION_HEADER>(reinterpret_cast<PUCHAR>(ntOHeader) + ntFHeader->SizeOfOptionalHeader);
	iidArr = reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(rvaToRaw(reinterpret_cast<UINT>(uFileMap + ntOHeader->DataDirectory[1].VirtualAddress)) + reinterpret_cast<UINT>(dosHeader));
};

const string PEData::toString() {
	stringstream ss;
	ss << std::uppercase;
	ss << "�ީ`���󷬺ţ�" << std::hex << ntFHeader->Machine << "\r\n" << std::dec;
	ss << "��������" << ntFHeader->NumberOfSections << "��\r\n";
	ss << "���ץ����إå���������" << ntFHeader->SizeOfOptionalHeader << "�Х���\r\n";
	ss << "���ץ����إå��ީ`���󷬺ţ�" << std::hex << ntOHeader->Magic << "\r\n" << std::dec;
	ss << "EP RVA���ɥ쥹��" << std::hex << ntOHeader->AddressOfEntryPoint << "\r\n" << std::dec;
	ss << "Image Base��" << std::hex << ntOHeader->ImageBase << "\r\n";
	ss << "EIP��" << std::hex << ntOHeader->ImageBase + ntOHeader->AddressOfEntryPoint << "\r\n";
	ss << "File Alignment" << ntOHeader->FileAlignment << "\r\n";
	ss << "Section Alignment" << ntOHeader->SectionAlignment << "\r\n";
	ss << "DataDirectory������" << ntOHeader->NumberOfRvaAndSizes << "\r\n\r\n";
	ss << "IAT ���" << "\r\n";

	return ss.str();
}

PEData::~PEData() {
	try {
		UnmapViewOfFile(uFileMap);
		CloseHandle(hMapObject);
		CloseHandle(hFile);
	}
	catch (...) {
	}
}

// �ե����륪�ե��åȤ�ȡ�ä���
UINT PEData::rvaToRaw(UINT rva) {
	for (int i = 0; i < ntFHeader->NumberOfSections; i++) {
		UINT secHeaderAddress = reinterpret_cast<UINT>(dosHeader) + (secHeader + i)->VirtualAddress;
		UINT secHeaderAddressEnd = secHeaderAddress + (secHeader + i)->SizeOfRawData;
		if (secHeaderAddress < rva&&rva < secHeaderAddressEnd) {
			return rva - secHeaderAddress + (secHeader + i)->PointerToRawData;
		}
	}
	return -1;
}