#include<string>
#include<windows.h>
using namespace std;

class PEData {
public:
	PEData(string exePath);
	~PEData();
	const string toString();
private:
	UINT rvaToRaw(UINT rva);
	string exePath;
	PIMAGE_DOS_HEADER dosHeader;
	PIMAGE_NT_HEADERS32 ntHeader;
	PIMAGE_FILE_HEADER ntFHeader;
	PIMAGE_OPTIONAL_HEADER ntOHeader;
	PIMAGE_SECTION_HEADER secHeader;
	PIMAGE_IMPORT_DESCRIPTOR iidArr;
	HANDLE hFile;
	HANDLE hMapObject;
	PUCHAR uFileMap;
};

