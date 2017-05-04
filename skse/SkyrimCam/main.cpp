#include "skse/PluginAPI.h"
#include "skse/skse_version.h"
#include "skse/SafeWrite.h"
#include "skse/ScaleformCallbacks.h"
#include "skse/ScaleformMovie.h"
#include "skse/GameAPI.h"

IDebugLog	gLog("Skyrim Camemberizator.log");

PluginHandle	g_pluginHandle = kPluginHandle_Invalid;

SKSEScaleformInterface	* scaleform = NULL;

void ApplyPatch(UInt32 base, UInt8 * buf, UInt32 len)
{
	for(UInt32 i = 0; i < len; i++)
		SafeWrite8(base + i, buf[i]);
}

void GameplayPatches(void)
{
	

/*  

1) FRENCHIFIED CONTAINER OWNERSHIP by MagikMike

Original Code : 1.9.32.0

004A49A3                                                 .  68 03010000          PUSH    103
004A49A8                                                 .  8BF8                 MOV     EDI, EAX
004A49AA                                                 .  8D4424 1D            LEA     EAX, DWORD PTR SS:[ESP+1D]
004A49AE                                                 .  6A 00                PUSH    0
004A49B0                                                 .  50                   PUSH    EAX
004A49B1                                                 .  C64424 24 00         MOV     BYTE PTR SS:[ESP+24], 0
004A49B6                                                 .  E8 85D8AA00          CALL    00F52240
004A49BB                                                 .  0FBE4D 65            MOVSX   ECX, BYTE PTR SS:[EBP+65]
004A49BF                                                 .  C1E9 02              SHR     ECX, 2
004A49C2                                                 .  83C4 0C              ADD     ESP, 0C
004A49C5                                                 .  F6C1 01              TEST    CL, 1
004A49C8                                                 .  74 31                JE      SHORT 004A49FB
004A49CA                                                 .  85FF                 TEST    EDI, EDI
004A49CC                                                 .  74 2D                JE      SHORT 004A49FB
004A49CE                                                 .  57                   PUSH    EDI
004A49CF                                                 .  E8 2CD9FAFF          CALL    <GetOwner>
004A49D4                                                 .  50                   PUSH    EAX
004A49D5                                                 .  8D5424 20            LEA     EDX, DWORD PTR SS:[ESP+20]
004A49D9                                                 .  68 04010000          PUSH    104
004A49DE                                                 .  52                   PUSH    EDX                                                                         ;  TESV.01084D43
004A49DF                                                 .  E8 B0D9AA00          CALL    <CopyToBuffer>
004A49E4                                                 .  68 044F0801          PUSH    01084F04                                                                    ; |Arg3 = 01084F04 ASCII "'s "
004A49E9                                                 .  8D4424 2C            LEA     EAX, DWORD PTR SS:[ESP+2C]                                                  ; |
004A49ED                                                 .  68 04010000          PUSH    104                                                                         ; |Arg2 = 00000104
004A49F2                                                 .  50                   PUSH    EAX                                                                         ; |Arg1 = 215BB214 ASCII "Cercueil"
004A49F3                                                 .  E8 35EDAA00          CALL    <Concat>                                                                    ; \TESV.00F5372D
004A49F8                                                 .  83C4 1C              ADD     ESP, 1C
004A49FB                                                 >  8BCE                 MOV     ECX, ESI
004A49FD                                                 .  E8 1E9E0300          CALL    <GetObjectName>
004A4A02                                                 .  50                   PUSH    EAX                                                                         ; /Arg3 = 215BB214 ASCII "Cercueil"
004A4A03                                                 .  8D4C24 1C            LEA     ECX, DWORD PTR SS:[ESP+1C]                                                  ; |
004A4A07                                                 .  68 04010000          PUSH    104                                                                         ; |Arg2 = 00000104
004A4A0C                                                 .  51                   PUSH    ECX                                                                         ; |Arg1 = 0000003C
004A4A0D                                                 .  E8 1BEDAA00          CALL    <Concat>                                                                    ; \TESV.00F5372D
004A4A12                                                 .  83C4 0C              ADD     ESP, 0C
004A4A15                                                 .  84DB                 TEST    BL, BL
004A4A17                                                 .  74 07                JE      SHORT 004A4A20
004A4A19                                                 .  A1 2084B101          MOV     EAX, DWORD PTR DS:[1B18420]
004A4A1E                                                 .  EB 2F                JMP     SHORT 004A4A4F


PATCH CHANGE TO 

004A49CA                                                 .  85FF                 TEST    EDI, EDI
004A49CC                                                 .  74 2D                JE      SHORT 004A49FB
004A49CE                                                    E9 2B5FBC00          JMP     0106A8FE   >> JUMP TO CODE_CAVE_1, AT END OF .text SECTION IN MEMORY
004A49D3                                                    90                   NOP
004A49D4                                                 .  50                   PUSH    EAX
004A49D5                                                 .  8D5424 20            LEA     EDX, DWORD PTR SS:[ESP+20]
004A49D9                                                 .  68 04010000          PUSH    104


NOW WE MUST CODE OUR PATCH AT CODE_CAVE_1


0106A8FE                                                 .  8BCE                  MOV     ECX, ESI
0106A900                                                 .  E8 1B3F47FF           CALL    <GetObjectName>
0106A905                                                 .  50                    PUSH    EAX                                                                         ; /Arg3 = 00000000
0106A906                                                 .  8D5424 1C             LEA     EDX, DWORD PTR SS:[ESP+1C]                                                  ; |
0106A90A                                                 .  68 04010000           PUSH    104                                                                         ; |Arg2 = 00000104
0106A90F                                                 .  52                    PUSH    EDX                                                                         ; |Arg1 = 00000000
0106A910                                                 .  E8 7F7AEEFF           CALL    <CopyToBuffer>                                                              ; \CopyToBuffer
0106A915                                                 .  83C4 0C               ADD     ESP, 0C
0106A918                                                 .  E8 3B000000           CALL    <GetSuffix>
0106A91D                                                 .  50                    PUSH    EAX
0106A91E                                                 .  8D4424 1C             LEA     EAX, DWORD PTR SS:[ESP+1C]
0106A922                                                 .  68 04010000           PUSH    104
0106A927                                                 .  50                    PUSH    EAX
0106A928                                                 .  E8 008EEEFF           CALL    <Concat>
0106A92D                                                 .  57                    PUSH    EDI
0106A92E                                                 .  E8 CD793EFF           CALL    <GetOwner>
0106A933                                                 .  50                    PUSH    EAX                                                                         ; |Arg3 = 00000000
0106A934                                                 .  8D4C24 2C             LEA     ECX, DWORD PTR SS:[ESP+2C]                                                  ; |
0106A938                                                 .  68 04010000           PUSH    104                                                                         ; |Arg2 = 00000104
0106A93D                                                 .  51                    PUSH    ECX                                                                         ; |Arg1 = 00000004
0106A93E                                                 .  E8 EA8DEEFF           CALL    <Concat>                                                                    ; \Concat
0106A943                                                 .  83C4 1C               ADD     ESP, 1C
0106A946                                                 .^ E9 CAA043FF           JMP     004A4A15
0106A94B <TESV.de>                                       .  20 64 65 20 00        ASCII   " de ",0
0106A950 <TESV.d'>                                       .  20 64 27 00           ASCII   " d'",0
0106A954                                                    00                    DB      00
0106A955                                                    00                    DB      00
0106A956                                                    00                    DB      00
0106A957                                                    00                    DB      00
0106A958 <TESV.GetSuffix>                               /$  60                    PUSHAD
0106A959                                                    57                    PUSH    EDI
0106A95A                                                    E8 A1793EFF           CALL    <GetOwner>
0106A95F                                                    83C4 04               ADD     ESP, 4
0106A962                                                    0FBE18                MOVSX   EBX, BYTE PTR DS:[EAX]
0106A965                                                    80CB 20               OR      BL, 20
0106A968                                                    80FB 68               CMP     BL, 68                                                                      ;  cmp, bl, "h"
0106A96B                                                    75 03                 JNZ     SHORT 0106A970
0106A96D                                                    40                    INC     EAX
0106A96E                                                  ^ EB F2                 JMP     SHORT 0106A962
0106A970                                                    80FB 61               CMP     BL, 61
0106A973                                                    74 23                 JE      SHORT 0106A998
0106A975                                                    80FB 65               CMP     BL, 65
0106A978                                                    74 1E                 JE      SHORT 0106A998
0106A97A                                                    80FB 69               CMP     BL, 69
0106A97D                                                    74 19                 JE      SHORT 0106A998
0106A97F                                                    80FB 6F               CMP     BL, 6F
0106A982                                                    74 14                 JE      SHORT 0106A998
0106A984                                                    80FB 75               CMP     BL, 75
0106A987                                                    74 0F                 JE      SHORT 0106A998
0106A989                                                    80FB 79               CMP     BL, 79
0106A98C                                                    74 0A                 JE      SHORT 0106A998
0106A98E                                                    C74424 1C 4BA90601    MOV     DWORD PTR SS:[ESP+1C], <de>                                                 ;  ASCII " de "
0106A996                                                    61                    POPAD
0106A997                                                    C3                    RET
0106A998                                                    C74424 1C 50A90601    MOV     DWORD PTR SS:[ESP+1C], <d'>                                                 ;  ASCII " d'"
0106A9A0                                                    61                    POPAD
0106A9A1                                                    C3                    RET




*/

   
	UInt8 Patch_ContainerOwnerJmp[] = 
	{
		0xE9, 0x2B,0x5F,0xBC,0x00,
		0x90
	};

	UInt8 Patch_ContainerName[] = 
	{

		/*
		0x8B,0xCE,
		0xE8,0x1B,0x3F,0x47,0xFF,
		0x50,
		0x8D,0x54,0x24,0x1C,
		0x68,0x04,0x01,0x00,0x00,
		0x52,
		0xE8,0x7F,0x7A,0xEE,0xFF,
		0x83,0xC4,0x0C,
		0x68,0x4A,0xA9,0x06,0x01,
		0x8D,0x44,0x24,0x1C,
		0x68,0x04,0x01,0x00,0x00,
		0x50,
		0xE8,0x01,0x8E,0xEE,0xFF,
		0x57,
		0xE8,0xCE,0x79,0x3E,0xFF,
		0x50,
		0x8D,0x4C,0x24,0x2C,
		0x68,0x04,0x01,0x00,0x00,
		0x51,
		0xE8,0xEB,0x8D,0xEE,0xFF,
		0x83,0xC4,0x1C,
		0xE9,0xCB,0xA0,0x43,0xFF,
		0x20,0x64,0x65,0x20
*/
		
	0x8B,0xCE,
	0xE8,0x1B,0x3F,0x47,0xFF,
	0x50,
	0x8D,0x54,0x24,0x1C,
	0x68,0x04,0x01,0x00,0x00,
	0x52,
	0xE8,0x7F,0x7A,0xEE,0xFF,
	0x83,0xC4,0x0C,
	0xE8,0x3B,0x00,0x00,0x00,
	0x50,
	0x8D,0x44,0x24,0x1C,
	0x68,0x04,0x01,0x00,0x00,
	0x50,
	0xE8,0x00,0x8E,0xEE,0xFF,
	0x57,
	0xE8,0xCD,0x79,0x3E,0xFF,
	0x50,
	0x8D,0x4C,0x24,0x2C,
	0x68,0x04,0x01,0x00,0x00,
	0x51,
	0xE8,0xEA,0x8D,0xEE,0xFF,
	0x83,0xC4,0x1C,
	0xE9,0xCA,0xA0,0x43,0xFF,
	0x20,0x64,0x65,0x20,0x00,
	0x20,0x64,0x27,0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x60,
	0x57,
	0xE8,0xA1,0x79,0x3E,0xFF,
	0x83,0xC4,0x04,
	0x0F,0xBE,0x18,
	0x80,0xCB,0x20,
	0x80,0xFB,0x68,
	0x75,0x03,
	0x40,
	0xEB,0xF2,
	0x80,0xFB,0x61,
	0x74,0x23,
	0x80,0xFB,0x65,
	0x74,0x1E,
	0x80,0xFB,0x69,
	0x74,0x19,
	0x80,0xFB,0x6F,
	0x74,0x14,
	0x80,0xFB,0x75,
	0x74,0x0F,
	0x80,0xFB,0x79,
	0x74,0x0A,
	0xC7,0x44,0x24,0x1C,0x4B,0xA9,0x06,0x01,
	0x61,
	0xC3,
	0xC7,0x44,0x24,0x1C,0x50,0xA9,0x06,0x01,
	0x61,
	0xC3



	};

	UInt32 Offset_ContainerOwnerJmp = 0x004A49CE; // our jmp here
	UInt32 Offset_ContainerOwnerCodeCave = 0x0106A8FE ; // Code cave 1


	ApplyPatch(Offset_ContainerOwnerJmp, Patch_ContainerOwnerJmp, sizeof(Patch_ContainerOwnerJmp));
    ApplyPatch(Offset_ContainerOwnerCodeCave, Patch_ContainerName, sizeof(Patch_ContainerName));



/*

2) FRENCHIFIED HOUR DISPLAY by MagikMike

ORIGINAL CODE  : 1.9.32.0


00898E77                                                |.  FF15 48B00601        CALL    DWORD PTR DS:[<&KERNEL32.FileTimeToSystemTime>]                             ; \FileTimeToSystemTime
00898E7D                                                |.  85C0                 TEST    EAX, EAX
00898E7F                                                |.  74 61                JE      SHORT 00898EE2
00898E81                                                |.  66:8B4C24 1C         MOV     CX, WORD PTR SS:[ESP+1C]
00898E86                                                |.  0FB7C1               MOVZX   EAX, CX
00898E89                                                |.  99                   CDQ
00898E8A                                                |.  BE 0C000000          MOV     ESI, 0C
00898E8F                                                |.  F7FE                 IDIV    ESI
00898E91                                                |.  0FB7C2               MOVZX   EAX, DX
00898E94                                                |.  66:85C0              TEST    AX, AX
00898E97                                                |.  75 02                JNZ     SHORT 00898E9B
00898E99                                                |.  8BC6                 MOV     EAX, ESI
00898E9B                                                |>  66:3BCE              CMP     CX, SI
00898E9E                                                |.  B9 F8FB0701          MOV     ECX, 0107FBF8                                                               ;  ASCII "AM"
00898EA3                                                |.  72 05                JB      SHORT 00898EAA
00898EA5                                                |.  B9 04FC0701          MOV     ECX, 0107FC04                                                               ;  ASCII "PM"
00898EAA                                                |>  51                   PUSH    ECX
00898EAB                                                |.  0FB74C24 22          MOVZX   ECX, WORD PTR SS:[ESP+22]
00898EB0                                                |.  51                   PUSH    ECX
00898EB1                                                |.  0FB74C24 22          MOVZX   ECX, WORD PTR SS:[ESP+22]
00898EB6                                                |.  0FB7D0               MOVZX   EDX, AX
00898EB9                                                |.  0FB74424 1C          MOVZX   EAX, WORD PTR SS:[ESP+1C]
00898EBE                                                |.  52                   PUSH    EDX
00898EBF                                                |.  0FB75424 22          MOVZX   EDX, WORD PTR SS:[ESP+22]
00898EC4                                                |.  50                   PUSH    EAX
00898EC5                                                |.  8B4424 3C            MOV     EAX, DWORD PTR SS:[ESP+3C]
00898EC9                                                |.  51                   PUSH    ECX
00898ECA                                                |.  52                   PUSH    EDX
00898ECB                                                |.  68 A08F0E01          PUSH    010E8FA0                                                                    ;  ASCII "%d/%d/%d, %d:%02d %s"
00898ED0                                                |.  50                   PUSH    EAX
00898ED1                                                |.  E8 DAA5B6FF          CALL    004034B0
00898ED6                                                |.  83C4 20              ADD     ESP, 20
00898ED9                                                |.  B0 01                MOV     AL, 1
00898EDB                                                |.  5E                   POP     ESI                                                                         
00898EDC                                                |.  83C4 20              ADD     ESP, 20
00898EDF                                                |.  C2 0800              RET     8
00898EE2                                                |>  32C0                 XOR     AL, AL
00898EE4                                                |.  5E                   POP     ESI                                                                         
00898EE5                                                |.  83C4 20              ADD     ESP, 20
00898EE8                                                \.  C2 0800              RET     8

PATCH CHANGE TO

00898E77                                                |.  FF15 48B00601        CALL    DWORD PTR DS:[<&KERNEL32.FileTimeToSystemTime>]                             ; \FileTimeToSystemTime
00898E7D                                                |.  85C0                 TEST    EAX, EAX
00898E7F                                                |.  74 61                JE      SHORT 00898EE2
00898E81                                                |.  66:8B4C24 1C         MOV     CX, WORD PTR SS:[ESP+1C]
00898E86                                                |.  0FB7C1               MOVZX   EAX, CX
00898E89                                                |.  99                   CDQ
00898E8A                                                |.  BE 01000000          MOV     ESI, 01                   <<< DIVIDE BY 1 
00898E8F                                                |.  F7FE                 IDIV    ESI
00898E91                                                                         NOP                              <<< NOP ME
00898E92                                                                         NOP                              <<< NOP ME 
00898E93                                                                         NOP                              <<< NOP ME 
00898E94                                                |.  66:85C0              TEST    AX, AX
00898E97                                                |.  75 02                JNZ     SHORT 00898E9B
00898E99                                                |.  8BC6                 MOV     EAX, ESI
00898E9B                                                |>  66:3BCE              CMP     CX, SI
00898E9E                                                |.  B9 F8FB0701          MOV     ECX, 0107FBF8                                                               <<"AM" to nullify
00898EA3                                                |.  72 05                JB      SHORT 00898EAA
00898EA5                                                |.  B9 04FC0701          MOV     ECX, 0107FC04                                                               << "PM" to nullify
00898EAA                                                |>  51                   PUSH    ECX
00898EAB                                                |.  0FB74C24 22          MOVZX   ECX, WORD PTR SS:[ESP+22]
00898EB0                                                |.  51                   PUSH    ECX
00898EB1                                                |.  0FB74C24 22          MOVZX   ECX, WORD PTR SS:[ESP+22]
00898EB6                                                |.  0FB7D0               MOVZX   EDX, AX
00898EB9                                                |.  0FB74424 1C          MOVZX   EAX, WORD PTR SS:[ESP+1C]
00898EBE                                                |.  52                   PUSH    EDX
00898EBF                                                |.  0FB75424 22          MOVZX   EDX, WORD PTR SS:[ESP+22]
00898EC4                                                |.  50                   PUSH    EAX
00898EC5                                                |.  8B4424 3C            MOV     EAX, DWORD PTR SS:[ESP+3C]
00898EC9                                                |.  52                   PUSH    EDX       <<<< INVERT THE PUSH ORDER
00898ECA                                                |.  51                   PUSH    ECX       <<<< INVERT THE PUSH ORDER
00898ECB                                                |.  68 A08F0E01          PUSH    010E8FA0                                                                    ;  ASCII "%d/%d/%d, %d:%02d %s"
00898ED0                                                |.  50                   PUSH    EAX
00898ED1                                                |.  E8 DAA5B6FF          CALL    004034B0
00898ED6                                                |.  83C4 20              ADD     ESP, 20
00898ED9                                                |.  B0 01                MOV     AL, 1
00898EDB                                                |.  5E                   POP     ESI                                                                         
00898EDC                                                |.  83C4 20              ADD     ESP, 20
00898EDF                                                |.  C2 0800              RET     8
00898EE2                                                |>  32C0                 XOR     AL, AL
00898EE4                                                |.  5E                   POP     ESI                                                                         
00898EE5                                                |.  83C4 20              ADD     ESP, 20
00898EE8                                                \.  C2 0800              RET     8

	*/
	UInt8 Patch_DoNotDivideHour[] = 
	{
		0xBE, 0x01,0x00,0x00,0x00,
		0xF7, 0xFE,
		0x90,
		0x90, 
		0x90
	};

    UInt8 Patch_NullAMPM[] = 
	{
		0x00
	};


       UInt8 Patch_InvertDateAndMonthPush[] = 
	{
		0x52, 0x51
	};


	UInt32 Offset_HourDivision = 0x00898E8A;
	UInt32 Offset_AM = 0x0107FBF8;  
	UInt32 Offset_PM = 0x0107FC04;
	UInt32 Offset_HourTwoPush = 0x00898EC9;

	ApplyPatch(Offset_HourDivision, Patch_DoNotDivideHour, sizeof(Patch_DoNotDivideHour));
    ApplyPatch(Offset_AM, Patch_NullAMPM, sizeof(Patch_NullAMPM));
    ApplyPatch(Offset_PM, Patch_NullAMPM, sizeof(Patch_NullAMPM));
	ApplyPatch(Offset_HourTwoPush, Patch_InvertDateAndMonthPush, sizeof(Patch_InvertDateAndMonthPush));


}



/*
class SKSEScaleform_ExampleFunction : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args)
	{
		Console_Print("hello world from example plugin");
	}
};

bool RegisterScaleform(GFxMovieView * view, GFxValue * root)
{
	RegisterFunction <SKSEScaleform_ExampleFunction>(root, view, "ExampleFunction");

	return true;
}

*/

extern "C"
{

bool SKSEPlugin_Query(const SKSEInterface * skse, PluginInfo * info)
{
	_MESSAGE("Wiwiland_Skyrim_Camemberizator");

	// populate info structure
	info->infoVersion =	PluginInfo::kInfoVersion;
	info->name =		"Wiwiland Skyrim Camemberizator 1.9.32";
	info->version =		1;

	// store plugin handle so we can identify ourselves later
	g_pluginHandle = skse->GetPluginHandle();

	if(skse->isEditor)
	{
		_MESSAGE("loaded in editor, marking as incompatible");

		return false;
	}
	else if(skse->runtimeVersion != RUNTIME_VERSION_1_9_32_0)
	{
		_MESSAGE("unsupported runtime version %08X", skse->runtimeVersion);

		return false;
	}

	// get the scaleform interface and query its version
	scaleform = (SKSEScaleformInterface *)skse->QueryInterface(kInterface_Scaleform);
	if(!scaleform)
	{
		_MESSAGE("couldn't get scaleform interface");

		return false;
	}

	if(scaleform->interfaceVersion < SKSEScaleformInterface::kInterfaceVersion)
	{
		_MESSAGE("scaleform interface too old (%d expected %d)", scaleform->interfaceVersion, SKSEScaleformInterface::kInterfaceVersion);

		return false;
	}

	// ### do not do anything else in this callback
	// ### only fill out PluginInfo and return true/false

	// supported runtime version
	return true;
}

bool SKSEPlugin_Load(const SKSEInterface * skse)
{
	//_MESSAGE("load");

	// apply patches to the game here
	GameplayPatches();

	// register scaleform callbacks
	//scaleform->Register("example_plugin", RegisterScaleform);

	return true;
}

};
