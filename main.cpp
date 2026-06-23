#include <mod/amlmod.h>

MYMOD(spyxxx.nowheelturnback, No Wheel Turn Back, 1.0, Spyxxx)

ON_MOD_LOAD()  
{
    uintptr_t g_libGTASA = aml->GetLib("libGTASA.so");

    if (g_libGTASA != 0)
    {
#ifdef __aarch64__
        // ARM64 (2.10 64-bit)
        // NOP = 0x1F2003D5
        uint32_t nop = 0x1F2003D5;

        // case 4: STR WZR, [X19, #0x600]
        aml->Write(g_libGTASA + 0x678AB8, (uintptr_t)&nop, sizeof(nop));
        // case 9: STR WZR, [X19, #0x600]
        aml->Write(g_libGTASA + 0x678B74, (uintptr_t)&nop, sizeof(nop));

#else
        // Thumb-2 (2.0 32-bit)
        // NOP.W = 0x8000F3AF  (bytes: AF F3 00 80)
        uint32_t nop = 0x8000F3AF;

        // case 4: STR.W R6, [R4, #0x498] (via loc_5582BC)
        aml->Write(g_libGTASA + 0x5582D2, (uintptr_t)&nop, sizeof(nop));
        // case 9: STR.W R6, [R4, #0x498] (via loc_55835C)
        aml->Write(g_libGTASA + 0x558362, (uintptr_t)&nop, sizeof(nop));

#endif
    }
}
