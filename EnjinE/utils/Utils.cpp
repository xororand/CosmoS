#include "Utils.h"
#include "hashes/sha256.h"

#include "intrin.h"
#include <Windows.h>
#include "stringapiset.h"
#include <codecvt>
// ==================== ENCODING ====================
std::string Utils::encoding::to_utf8(const std::wstring& wstr)
{
    if (wstr.empty()) return std::string();
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}
std::wstring Utils::encoding::to_multibytes(const std::string& str)
{
    if (str.empty()) return std::wstring();
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

// ==================== HASHING ====================

std::wstring Utils::hashing::sha256(std::wstring text)
{
    SHA256 sha;
    sha.update(Utils::encoding::to_utf8(text));
    std::array<uint8_t, 32> digest = sha.digest();
    return Utils::encoding::to_multibytes(SHA256::toString(digest));
}
std::string Utils::hashing::sha256(std::string text)
{
    SHA256 sha;
    sha.update(text);
    std::array<uint8_t, 32> digest = sha.digest();
    return SHA256::toString(digest);
}



// ==================== STRINGS ====================
std::string Utils::string::replace(  std::string s,  char c1, char c2)
{
    int l = s.length();

    // loop to traverse in the string
    for (int i = 0; i < l; i++)
    {
        // check for c1 and replace
        if (s[i] == c1)
            s[i] = c2;

        // check for c2 and replace
        else if (s[i] == c2)
            s[i] = c1;
    }
    return s;
}
std::wstring Utils::string::replace( std::wstring s, char c1, char c2)
{
    int l = s.length();

    // loop to traverse in the string
    for (int i = 0; i < l; i++)
    {
        // check for c1 and replace
        if (s[i] == c1)
            s[i] = c2;
    }
    return s;
}



// ==================== COMPUTER ====================
//std::string Utils::computer::getCpu() {
//    try
//    {
//        int CPUInfo[4] = { -1 };
//        __cpuid(CPUInfo, 0x80000000);
//        unsigned int nExIds = CPUInfo[0];
//
//        char CPUBrandString[0x40] = { 0 };
//        for (unsigned int i = 0x80000000; i <= nExIds; ++i)
//        {
//            __cpuid(CPUInfo, i);
//            if (i == 0x80000002)
//            {
//                memcpy(CPUBrandString,
//                    CPUInfo,
//                    sizeof(CPUInfo));
//            }
//            else if (i == 0x80000003)
//            {
//                memcpy(CPUBrandString + 16,
//                    CPUInfo,
//                    sizeof(CPUInfo));
//            }
//            else if (i == 0x80000004)
//            {
//                memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
//            }
//        }
//
//        return CPUBrandString;
//    }
//    catch (...) { return "NONE"; }
//}
//std::wstring Utils::computer::getGpu() {
//    DISPLAY_DEVICE dd = { sizeof(dd), 0 };
//    BOOL f = EnumDisplayDevicesW(NULL, 0, &dd, EDD_GET_DEVICE_INTERFACE_NAME);
//    return dd.DeviceString;
//}
//void Utils::computer::getRAM(DWORD& max, DWORD& used) {
//    MEMORYSTATUSEX memoryStatus;
//    memoryStatus.dwLength = sizeof(memoryStatus);
//    GlobalMemoryStatusEx(&memoryStatus);
//    max = memoryStatus.ullTotalPhys / 1024 / 1024;
//    used = memoryStatus.dwMemoryLoad; // çàãðóæåííîñòü ÎÏ
//}
//void Utils::computer::getDesktopResolution(int& screen_weight, int& screen_height) {
//    RECT desktop;
//    const HWND hDesktop = GetDesktopWindow();
//
//    GetWindowRect(hDesktop, &desktop);
//
//    screen_weight = desktop.right;
//    screen_height = desktop.bottom;
//}

