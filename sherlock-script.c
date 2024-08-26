# define _CRT_SECURE_NO_WARNINGS
# include "stdio.h"
# include "ctype.h"
# include "string.h"
# include "stdlib.h"
# include "bitcoin.h"
// NOTE: Make sure you compiled sherlock executable
# ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include "windows.h"
DWORD Δ = 0;
HANDLE stdin⁺, stdout⁻, stderr⁻;
# define STDIN(addr, size) WriteFile (stdin⁺, addr, size, NULL, NULL)
# define STDOUT(addr, size) PeekNamedPipe (stdout⁻, NULL, 0, NULL, & Δ, NULL) && Δ >= size && ReadFile (stdout⁻, addr, size, NULL, NULL)
# define STDERR(addr, size) PeekNamedPipe (stderr⁻, NULL, 0, NULL, & Δ, NULL) && Δ >= size && ReadFile (stderr⁻, addr, size, NULL, NULL)
// > clang sherlock-script.c -o bscript.exe
// > bscript 221b
# else
# include "unistd.h"
# include "sys/types.h"
int stdin⁺ [2], stdout⁻ [2], stderr⁻ [2];
# define STDIN(addr, size) write (stdin⁺[1], addr, size)
# define STDOUT(addr, size) read (stdout⁻[0], addr, size)
# define STDERR(addr, size) read (stderr⁻[0], addr, size)
// $ clang sherlock-script.c -o bscript
// $ ./bscript 221b
# endif
const char * OP_ [0x100] =
{
	[OP_0] = "OP_0",
	[0x01 ... 0x4B] = NULL,
	[OP_PUSHDATA1] = "OP_PUSHDATA1",
	[OP_PUSHDATA2] = "OP_PUSHDATA2",
	[OP_PUSHDATA4] = "OP_PUSHDATA4",
	[OP_1NEGATE] = "OP_1NEGATE",
	[OP_RESERVED] = "OP_RESERVED",
	[OP_1] = "OP_1",
	[OP_2] = "OP_2",
	[OP_3] = "OP_3",
	[OP_4] = "OP_4",
	[OP_5] = "OP_5",
	[OP_6] = "OP_6",
	[OP_7] = "OP_7",
	[OP_8] = "OP_8",
	[OP_9] = "OP_9",
	[OP_10] = "OP_10",
	[OP_11] = "OP_11",
	[OP_12] = "OP_12",
	[OP_13] = "OP_13",
	[OP_14] = "OP_14",
	[OP_15] = "OP_15",
	[OP_16] = "OP_16",
	[OP_NOP] = "OP_NOP",
	[OP_VER] = "OP_VER",
	[OP_IF] = "OP_IF",
	[OP_NOTIF] = "OP_NOTIF",
	[OP_VERIF] = "OP_VERIF",
	[OP_VERNOTIF] = "OP_VERNOTIF",
	[OP_ELSE] = "OP_ELSE",
	[OP_ENDIF] = "OP_ENDIF",
	[OP_VERIFY] = "OP_VERIFY",
	[OP_RETURN] = "OP_RETURN",
	[OP_TOALTSTACK] = "OP_TOALTSTACK",
	[OP_FROMALTSTACK] = "OP_FROMALTSTACK",
	[OP_2DROP] = "OP_2DROP",
	[OP_2DUP] = "OP_2DUP",
	[OP_3DUP] = "OP_3DUP",
	[OP_2OVER] = "OP_2OVER",
	[OP_2ROT] = "OP_2ROT",
	[OP_2SWAP] = "OP_2SWAP",
	[OP_IFDUP] = "OP_IFDUP",
	[OP_DEPTH] = "OP_DEPTH",
	[OP_DROP] = "OP_DROP",
	[OP_DUP] = "OP_DUP",
	[OP_NIP] = "OP_NIP",
	[OP_OVER] = "OP_OVER",
	[OP_PICK] = "OP_PICK",
	[OP_ROLL] = "OP_ROLL",
	[OP_ROT] = "OP_ROT",
	[OP_SWAP] = "OP_SWAP",
	[OP_TUCK] = "OP_TUCK",
	[OP_CAT] = "OP_CAT",
	[OP_SUBSTR] = "OP_SUBSTR",
	[OP_LEFT] = "OP_LEFT",
	[OP_RIGHT] = "OP_RIGHT",
	[OP_SIZE] = "OP_SIZE",
	[OP_INVERT] = "OP_INVERT",
	[OP_AND] = "OP_AND",
	[OP_OR] = "OP_OR",
	[OP_XOR] = "OP_XOR",
	[OP_EQUAL] = "OP_EQUAL",
	[OP_EQUALVERIFY] = "OP_EQUALVERIFY",
	[OP_RESERVED1] = "OP_RESERVED1",
	[OP_RESERVED2] = "OP_RESERVED2",
	[OP_1ADD] = "OP_1ADD",
	[OP_1SUB] = "OP_1SUB",
	[OP_2MUL] = "OP_2MUL",
	[OP_2DIV] = "OP_2DIV",
	[OP_NEGATE] = "OP_NEGATE",
	[OP_ABS] = "OP_ABS",
	[OP_NOT] = "OP_NOT",
	[OP_0NOTEQUAL] = "OP_0NOTEQUAL",
	[OP_ADD] = "OP_ADD",
	[OP_SUB] = "OP_SUB",
	[OP_MUL] = "OP_MUL",
	[OP_DIV] = "OP_DIV",
	[OP_MOD] = "OP_MOD",
	[OP_LSHIFT] = "OP_LSHIFT",
	[OP_RSHIFT] = "OP_RSHIFT",
	[OP_BOOLAND] = "OP_BOOLAND",
	[OP_BOOLOR] = "OP_BOOLOR",
	[OP_NUMEQUAL] = "OP_NUMEQUAL",
	[OP_NUMEQUALVERIFY] = "OP_NUMEQUALVERIFY",
	[OP_NUMNOTEQUAL] = "OP_NUMNOTEQUAL",
	[OP_LESSTHAN] = "OP_LESSTHAN",
	[OP_GREATERTHAN] = "OP_GREATERTHAN",
	[OP_LESSTHANOREQUAL] = "OP_LESSTHANOREQUAL",
	[OP_GREATERTHANOREQUAL] = "OP_GREATERTHANOREQUAL",
	[OP_MIN] = "OP_MIN",
	[OP_MAX] = "OP_MAX",
	[OP_WITHIN] = "OP_WITHIN",
	[OP_RIPEMD160] = "OP_RIPEMD160",
	[OP_SHA1] = "OP_SHA1",
	[OP_SHA256] = "OP_SHA256",
	[OP_HASH160] = "OP_HASH160",
	[OP_HASH256] = "OP_HASH256",
	[OP_CODESEPARATOR] = "OP_CODESEPARATOR",
	[OP_CHECKSIG] = "OP_CHECKSIG",
	[OP_CHECKSIGVERIFY] = "OP_CHECKSIGVERIFY",
	[OP_CHECKMULTISIG] = "OP_CHECKMULTISIG",
	[OP_CHECKMULTISIGVERIFY] = "OP_CHECKMULTISIGVERIFY",
	[OP_NOP1] = "OP_NOP1",
	[OP_NOP2] = "OP_NOP2",
	[OP_NOP3] = "OP_NOP3",
	[OP_NOP4] = "OP_NOP4",
	[OP_NOP5] = "OP_NOP5",
	[OP_NOP6] = "OP_NOP6",
	[OP_NOP7] = "OP_NOP7",
	[OP_NOP8] = "OP_NOP8",
	[OP_NOP9] = "OP_NOP9",
	[OP_NOP10] = "OP_NOP10",
	[OP_CHECKSIGADD] = "OP_CHECKSIGADD",
	[OP_CHECKSIGADD + 1 ... 0xFF] = NULL
};
const int8_t Δap [256] =
{
	[OP_0] = 1,
	[1 ... 4] = 1,
	// ⋯
	// OP_PUSHDATA1
	// OP_PUSHDATA2
	// OP_PUSHDATA4
	[OP_1NEGATE] = 1,
	[OP_RESERVED] = 1,
	[OP_1 ... OP_16] = 1,
	// OP_NOP
	// OP_VER
	[OP_IF] = -1,
	[OP_NOTIF] = -1,
	// OP_VERIF
	// OP_VERNOTIF
	[OP_ELSE] = 0,
	[OP_ENDIF] = 0,
	// OP_VERIFY
	// OP_RETURN
	[OP_TOALTSTACK] = -1,
	[OP_FROMALTSTACK] = 1,
	[OP_2DROP] = -2,
	[OP_2DUP] = 2,
	[OP_3DUP] = 3,
	[OP_2OVER] = 2,
	[OP_2ROT] = 0,
	[OP_2SWAP] = 0,
	[OP_DEPTH] = 1,
	[OP_DROP] = -1,
	[OP_DUP] = 1,
	[OP_NIP] = -1,
	[OP_OVER] = 1,
	[OP_PICK] = 0,
	[OP_ROLL] = -1,
	[OP_ROT] = 0,
	[OP_SWAP] = 0,
	[OP_TUCK] = 1,
	// OP_CAT
	// OP_SUBSTR
	// OP_LEFT
	// OP_RIGHT
	// OP_SIZE
	// OP_INVERT
	// OP_AND
	// OP_OR
	// OP_XOR
	// OP_EQUAL
	// OP_EQUALVERIFY
	// OP_RESERVED1
	// OP_RESERVED2
	[OP_1ADD] = 0,
	[OP_1SUB] = 0,
	[OP_2MUL] = 0,
	[OP_2DIV] = 0,
	[OP_NEGATE] = 0,
	[OP_ABS] = 0,
	[OP_NOT] = 0,
	[OP_0NOTEQUAL] = 0,
	[OP_ADD] = -1,
	[OP_SUB] = -1,
	[OP_MUL] = -1,
	[OP_DIV] = -1,
	[OP_MOD] = -1,
	[OP_LSHIFT] = -1,
	[OP_RSHIFT] = -1,
	[OP_BOOLAND] = -1,
	[OP_BOOLOR] = -1,
	[OP_NUMEQUAL] = -1,
	[OP_NUMEQUALVERIFY] = -1,
	[OP_NUMNOTEQUAL] = -1,
	[OP_LESSTHAN] = -1,
	[OP_GREATERTHAN] = -1,
	[OP_LESSTHANOREQUAL] = -1,
	[OP_GREATERTHANOREQUAL] = -1,
	[OP_MIN] = -1,
	[OP_MAX] = -1,
	[OP_WITHIN] = -2,
	// OP_RIPEMD160
	// OP_SHA1
	// OP_SHA256
	// OP_HASH160
	// OP_HASH256
	// OP_CODESEPARATOR
	// OP_CHECKSIG
	// OP_CHECKSIGVERIFY
	// OP_CHECKMULTISIG
	// OP_CHECKMULTISIGVERIFY
	// OP_NOP1
	// OP_NOP2
	// OP_NOP3
	// OP_NOP4
	// OP_NOP5
	// OP_NOP6
	// OP_NOP7
	// OP_NOP8
	// OP_NOP9
	// OP_NOP10
	// OP_CHECKSIGADD
};
char script [0x8000] = { [0 ... 0x7FFF] = '\0' };
uint16_t length = 0;
uint16_t pc₋ = 0, pc₊ = 0;
uint8_t op = OP_NOP;
uint16_t ap⁻ = 0, ap⁺ = 0, ap₋ᵐᵃˣ = 0, ap₊ᵐᵃˣ = 0, öp = 0;
int main (int argc, const char * argv [ ])
{
	if (argc <= 1) return puts ("\e[0;31merror:\e[0m no input files"), 0;
	// Load Bitcoin script file
	FILE * f = fopen (argv [1], "rb");
	if (f == NULL) return printf ("\e[0;31merror:\e[0m no such file or directory: '%s'\n", argv [1]), 0;
	length = fread (script, 1, sizeof script, f);
	fclose (f);
	// Start sherlock executable
	# ifdef _WIN32
		STARTUPINFO SI₀ = { .cb = sizeof SI₀, .dwFlags = STARTF_USESTDHANDLES };
		SECURITY_ATTRIBUTES SA₀ = { .nLength = sizeof SA₀, .bInheritHandle = TRUE };
		SECURITY_ATTRIBUTES SA₁ = { .nLength = sizeof SA₁, .bInheritHandle = TRUE };
		SECURITY_ATTRIBUTES SA₂ = { .nLength = sizeof SA₂, .bInheritHandle = TRUE };
		PROCESS_INFORMATION PI₀ = { };
		CreatePipe (& SI₀.hStdInput, & stdin⁺, & SA₀, 0), SetHandleInformation (stdin⁺, HANDLE_FLAG_INHERIT, 0);
		CreatePipe (& stdout⁻, & SI₀.hStdOutput, & SA₁, 0), SetHandleInformation (stdout⁻, HANDLE_FLAG_INHERIT, 0);
		CreatePipe (& stderr⁻, & SI₀.hStdError, & SA₂, 0), SetHandleInformation (stderr⁻, HANDLE_FLAG_INHERIT, 0);
		CreateProcess (NULL, "sherlock", NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, & SI₀, & PI₀);
	# else
		pipe (stdin⁺);
		pipe (stdout⁻);
		pipe (stderr⁻);
		if (fork ( ) == 0)
		{
			dup2 (stdin⁺[0], STDIN_FILENO), close (stdin⁺[0]), close (stdin⁺[1]);
			dup2 (stdout⁻[1], STDOUT_FILENO), close (stdout⁻[0]), close (stdout⁻[1]);
			dup2 (stderr⁻[1], STDERR_FILENO), close (stderr⁻[0]), close (stderr⁻[1]);
			char * cli [ ] = {"./sherlock", NULL};
			execv (cli [0], cli);
			return 0;
		}
		close (stdin⁺[0]), close (stdout⁻[1]), close (stderr⁻[1]);
	# endif
	uint16_t tmp = 0;
	uint16_t __ap = 0;
	// Feed Bitcoin script file
	for (char * s = strtok (script, "\t\n\r "); s != NULL && s < & script [length]; s = strtok (NULL, "\t\n\r "))
	{
		if (* s == '\0') continue;
		for (op = OP_0; op <= OP_CHECKSIGADD; ++ op)
		{
			if (OP_ [op] == NULL) continue;
			if (strcmp (s, OP_ [op]) == 0)
			{
				if (op == OP_NOP) continue;
				if (op == OP_ELSE) ap⁻ = __ap;
				if (op == OP_RESERVED) ++ öp;
				ap⁻ += Δap [op];
				if (op == OP_IF || op == OP_NOTIF) __ap = ap⁻;
				if (ap⁻ > ap₋ᵐᵃˣ) ap₋ᵐᵃˣ = ap⁻;
				STDIN (& op, 1), pc₋ += op != OP_RESERVED;
				break;
			}
		}
		if (op <= OP_CHECKSIGADD) continue;
		if (* s < '0' || * s > '9')
		{
			printf ("\e[0;31mERROR\e[0m use of undeclared identifier '%s'\n", s);
			continue;
		}
		int32_t num;
		switch (num = atoi (s))
		{
			case -1: op = OP_1NEGATE; STDIN (& op, 1), ++ pc₋; break;
			case 0: op = OP_0; STDIN (& op, 1), ++ pc₋; break;
			case 1: op = OP_1; STDIN (& op, 1), ++ pc₋; break;
			case 2: op = OP_2; STDIN (& op, 1), ++ pc₋; break;
			case 3: op = OP_3; STDIN (& op, 1), ++ pc₋; break;
			case 4: op = OP_4; STDIN (& op, 1), ++ pc₋; break;
			case 5: op = OP_5; STDIN (& op, 1), ++ pc₋; break;
			case 6: op = OP_6; STDIN (& op, 1), ++ pc₋; break;
			case 7: op = OP_7; STDIN (& op, 1), ++ pc₋; break;
			case 8: op = OP_8; STDIN (& op, 1), ++ pc₋; break;
			case 9: op = OP_9; STDIN (& op, 1), ++ pc₋; break;
			case 10: op = OP_10; STDIN (& op, 1), ++ pc₋; break;
			case 11: op = OP_11; STDIN (& op, 1), ++ pc₋; break;
			case 12: op = OP_12; STDIN (& op, 1), ++ pc₋; break;
			case 13: op = OP_13; STDIN (& op, 1), ++ pc₋; break;
			case 14: op = OP_14; STDIN (& op, 1), ++ pc₋; break;
			case 15: op = OP_15; STDIN (& op, 1), ++ pc₋; break;
			case 16: op = OP_16; STDIN (& op, 1), ++ pc₋; break;
			default: op = 4 - __builtin_clz (num) / 8, STDIN (& op, 1), ++ pc₋, STDIN (& num, op), pc₋ += op; break;
		}
		ap⁻ += Δap [op];
		if (ap⁻ > ap₋ᵐᵃˣ) ap₋ᵐᵃˣ = ap⁻;
	}
	op = OP_NOP, STDIN (& op, 1); // nop-termination
	# ifdef _WIN32
	WaitForSingleObject (PI₀.hProcess, INFINITE);
	# endif
	// Check error message
	char char⁻ = '\n';
	if (STDERR (& char⁻, 1))
	{
		printf ("\e[0;31mERROR\e[0m %c", char⁻);
		while (STDERR (& char⁻, 1)) printf ("%c", char⁻);
		return 0;
	}
	// Show Bitcoin script
	ap₊ᵐᵃˣ = ap⁺ = öp;
	for (uint8_t char⁺; STDOUT (& char⁺, 1); )
	{
		++ pc₊;
		ap⁺ += Δap [char⁺];
		if (char⁺ == OP_ELSE) ap⁺ = __ap;
		if (char⁺ == OP_IF || char⁺ == OP_NOTIF) __ap = ap⁺;
		if (ap⁺ > ap₊ᵐᵃˣ) ap₊ᵐᵃˣ = ap⁺;
		if (char⁺ == 1 || char⁺ == 2 || char⁺ == 3 || char⁺ == 4)
		{
			pc₊ += char⁺;
			int32_t num = 0;
			STDOUT (& num, char⁺);
			printf ("%i\n", num);
			continue;
		}
		printf ("%s\n", OP_ [char⁺]);
	}
	if (pc₊ != pc₋)
	{
		printf (pc₋ >= pc₊ ? "\e[38;5;157m" : "\e[38;5;167m");
		printf ("PC %+iB/%i%%\e[0m\n", pc₊ - pc₋, abs (pc₊ - pc₋) * 100 / pc₋);
		printf (ap₋ᵐᵃˣ >= ap₊ᵐᵃˣ ? "\e[38;5;157m" : "\e[38;5;167m");
		printf ("AP %+i/%hu\e[0m\n", ap₊ᵐᵃˣ - ap₋ᵐᵃˣ, ap₊ᵐᵃˣ);
	}
	return 0;
}