# include "stdio.h"
# include "string.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;
typedef signed int i32;
// ⋯
enum : u8
{
    OP_0 = 0x00, OP_PUSHDATA1 = 0x4c, OP_PUSHDATA2, OP_PUSHDATA4, OP_1NEGATE, OP_RESERVED, OP_1, OP_2, OP_3, OP_4, OP_5, OP_6, OP_7,
    OP_8, OP_9, OP_10, OP_11, OP_12, OP_13, OP_14, OP_15, OP_16, OP_NOP, OP_VER, OP_IF, OP_NOTIF, OP_VERIF, OP_VERNOTIF, OP_ELSE,
    OP_ENDIF, OP_VERIFY, OP_RETURN, OP_TOALTSTACK, OP_FROMALTSTACK, OP_2DROP, OP_2DUP, OP_3DUP, OP_2OVER, OP_2ROT, OP_2SWAP, OP_IFDUP,
    OP_DEPTH, OP_DROP, OP_DUP, OP_NIP, OP_OVER, OP_PICK, OP_ROLL, OP_ROT, OP_SWAP, OP_TUCK, OP_CAT, OP_SUBSTR, OP_LEFT, OP_RIGHT, OP_SIZE,
    OP_INVERT, OP_AND, OP_OR, OP_XOR, OP_EQUAL, OP_EQUALVERIFY, OP_RESERVED1, OP_RESERVED2, OP_1ADD, OP_1SUB, OP_2MUL, OP_2DIV, OP_NEGATE,
    OP_ABS, OP_NOT, OP_0NOTEQUAL, OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD, OP_LSHIFT, OP_RSHIFT, OP_BOOLAND, OP_BOOLOR, OP_NUMEQUAL,
    OP_NUMEQUALVERIFY, OP_NUMNOTEQUAL, OP_LESSTHAN, OP_GREATERTHAN, OP_LESSTHANOREQUAL, OP_GREATERTHANOREQUAL, OP_MIN, OP_MAX, OP_WITHIN,
    OP_RIPEMD160, OP_SHA1, OP_SHA256, OP_HASH160, OP_HASH256, OP_CODESEPARATOR, OP_CHECKSIG, OP_CHECKSIGVERIFY, OP_CHECKMULTISIG,
    OP_CHECKMULTISIGVERIFY, OP_NOP1, OP_NOP2, OP_NOP3, OP_NOP4, OP_NOP5, OP_NOP6, OP_NOP7, OP_NOP8, OP_NOP9, OP_NOP10, OP_CHECKSIGADD
}
script [4096] = { [0 ... 4095] = OP_NOP }; // bitcoin script
u16 pc = 0; // program counter
struct
{
	i32 integer;
	i32 reference;
}
const⁺ [64] = { [0 ... 63].integer = 0, [0 ... 63].reference = 0 };
// ⋯
enum : u16 { x₀, x₁, x₂, x₃, x₄, x₅, x₆, x₇, x₈, x₉, x₁₀, x₁₁, x₁₂, x₁₃, x₁₄, x₁₅, x₁₆, x₁₇, x₁₈, x₁₉, x₂₀, x₂₁, x₂₂, x₂₃ };
struct
{
    u8 opcode;
    u8 reference;
    u16 operand_0;
    u16 operand_1;
    u16 operand_2;
}
trace [4096] = { [x₀ ... x₂₃].reference = 1, [x₀ ... x₂₃].opcode = OP_RESERVED, [x₂₃ + 1 ... 4095].opcode = OP_NOP };
u16 öp = x₂₃ + 1;
// ⋯
u16 stack⁻ [16] [1024] = { x₂₃, x₂₂, x₂₁, x₂₀, x₁₉, x₁₈, x₁₇, x₁₆, x₁₅, x₁₄, x₁₃, x₁₂, x₁₁, x₁₀, x₉, x₈, x₇, x₆, x₅, x₄, x₃, x₂, x₁, x₀ };
u16 fp⁻ = 0, ap [16], ap⁻ = x₂₃ + 1 - x₀;
// ⋯
u16 stack⁺ [1024] = { x₂₃, x₂₂, x₂₁, x₂₀, x₁₉, x₁₈, x₁₇, x₁₆, x₁₅, x₁₄, x₁₃, x₁₂, x₁₁, x₁₀, x₉, x₈, x₇, x₆, x₅, x₄, x₃, x₂, x₁, x₀ };
u16 ap⁺ = x₂₃ + 1 - x₀;
// ⋯
void preprocess (const u8 * data,  u16 size)
{
	u8 opcode = OP_NOP;
	// CONSTANT PREPROCESS
	for (u8 cc = 0; size --> 0; ) switch (opcode = * data ++)
	{
		case OP_0:
			script [pc ++] = OP_0;
			continue;
		case 1: // 8-bit
			const⁺ [cc].integer = * data ++;
			// TODO: Check for duplication
			script [pc ++] = cc ++ | 0xC0;
			continue;
		case 2: // 16-bit
			const⁺ [cc].integer = script [pc ++];
			const⁺ [cc].integer |= script [pc ++] << 8;
			// TODO: Check for duplication
			script [pc ++] = cc ++ | 0xC0;
			continue;
		case 3: // 24-bit
			const⁺ [cc].integer = script [pc ++];
			const⁺ [cc].integer |= script [pc ++] << 8;
			const⁺ [cc].integer |= script [pc ++] << 16;
			// TODO: Check for duplication
			script [pc ++] = cc ++ | 0xC0;
			continue;
		case 4: // 32-bit
			const⁺ [cc].integer = script [pc ++];
			const⁺ [cc].integer |= script [pc ++] << 8;
			const⁺ [cc].integer |= script [pc ++] << 16;
			const⁺ [cc].integer |= script [pc ++] << 24;
			// TODO: Check for duplication
			script [pc ++] = cc ++ | 0xC0;
			continue;
		default: // ⋯
			script [pc ++] = opcode;
			continue;
	}
	// REVERSED EXECUTION
	while (pc --> 0) switch (opcode = script [pc])
	{
		case OP_0:
		{
			u16 𝟘 = stack⁻ [fp⁻] [-- ap⁻];
			trace [𝟘].opcode = OP_0;
			continue;
		}
		// ⋯
		// OP_PUSHDATA1
		// OP_PUSHDATA2
		// OP_PUSHDATA4
		// OP_1NEGATE
		// OP_RESERVED
		case OP_1:
		case OP_2:
		case OP_3:
		case OP_4:
		case OP_5:
		case OP_6:
		case OP_7:
		case OP_8:
		case OP_9:
		case OP_10:
		case OP_11:
		case OP_12:
		case OP_13:
		case OP_14:
		case OP_15:
		case OP_16:
		{
			u16 𝟙𝟞 = stack⁻ [fp⁻] [-- ap⁻];
			trace [𝟙𝟞].opcode = opcode;
			continue;
		}
		// OP_NOP
		// OP_VER
		case OP_IF:
		{
			for (u16 _ = 0; _ < ap⁻; ++ _)
			{
				u16 A₁ = stack⁻ [fp⁻] [_];
				u16 A₀ = stack⁻ [fp⁻] [_ - 1];
				if (A₀ == A₁) continue;
				u16 ？ = öp ++;
				trace [？].opcode = OP_IF;
				trace [？].operand_0 = öp;
				trace [？].operand_1 = A₁;
				trace [？].operand_2 = A₀;
				trace [öp ++].reference = 1;
				++ trace [A₀].reference;
				++ trace [A₁].reference;
			}
			if (ap⁻ != ap [-- fp⁻])
			; // WARNING
			continue;
		}
		// OP_NOTIF
		// OP_VERIF
		// OP_VERNOTIF
		case OP_ELSE:
		{
			u16 ap₀ = ap [fp⁻ - 1];
			ap [fp⁻ - 1] = ap⁻, ap⁻ = ap₀;
			memcpy (stack⁻ [fp⁻ + 1], stack⁻ [fp⁻ - 1], sizeof stack⁻ [fp⁻]);
			memcpy (stack⁻ [fp⁻ - 1], stack⁻ [fp⁻], sizeof stack⁻ [fp⁻]);
			memcpy (stack⁻ [fp⁻], stack⁻ [fp⁻ + 1], sizeof stack⁻ [fp⁻]);
			continue;
		}
		case OP_ENDIF:
		{
			ap [fp⁻ ++] = ap⁻;
			memcpy (stack⁻ [fp⁻], stack⁻ [fp⁻ - 1], sizeof stack⁻ [fp⁻]);
			continue;
		}
		// OP_VERIFY
		// OP_RETURN
		// OP_TOALTSTACK
		// OP_FROMALTSTACK
		// OP_2DROP
		// OP_2DUP
		// OP_3DUP
		// OP_2OVER
		// OP_2ROT
		// OP_2SWAP
		// OP_IFDUP
		// OP_DEPTH
		case OP_DROP:
		{
			stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			continue;
		}
		case OP_DUP:
		{
			u16 A₁ = stack⁻ [fp⁻] [-- ap⁻];
			u16 A₀ = stack⁻ [fp⁻] [-- ap⁻];
			stack⁻ [fp⁻] [ap⁻ ++] = A₀; // A₀ == A₁
			continue;
		}
		case OP_NIP:
		{
			u16 A = stack⁻ [fp⁻] [-- ap⁻];
			stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			stack⁻ [fp⁻] [ap⁻ ++] = A;
			continue;
		}
		case OP_OVER:
		{
			u16 A = stack⁻ [fp⁻] [-- ap⁻];
			stack⁻ [fp⁻] [ap⁻ - 2] = A;
			continue;
		}
		case OP_PICK:
		{
			u16 const⁻ = script [-- pc];
			u16 A⁺ = stack⁻ [fp⁻] [-- ap⁻];
			u16 N⁺ = const⁻ && const⁻ <= OP_16 ? const⁻ - OP_RESERVED : const⁻ >= 0xC0 ? const⁺ [const⁻ - 0xC0].integer : 0;
			stack⁻ [fp⁻] [ap⁻ - N⁺ - 1] = A⁺;
			continue;
		}
		case OP_ROLL:
		{
			u16 const⁻ = script [-- pc];
			u16 A⁺ = stack⁻ [fp⁻] [-- ap⁻];
			u16 N⁺ = const⁻ && const⁻ <= OP_16 ? const⁻ - OP_RESERVED : const⁻ >= 0xC0 ? const⁺ [const⁻ - 0xC0].integer : 0;
			memmove (stack⁻ [fp⁻] + ap⁻ - N⁺, stack⁻ [fp⁻] + ap⁻ - N⁺ - 1, N⁺ * sizeof stack⁻ [fp⁻] [ap⁻]);
			stack⁻ [fp⁻] [ap⁻ - N⁺ - 1] = A⁺;
		}
		case OP_ROT:
		{
			u16 A = stack⁻ [fp⁻] [ap⁻ - 1];
			stack⁻ [fp⁻] [ap⁻ - 1] = stack⁻ [fp⁻] [ap⁻ - 2];
			stack⁻ [fp⁻] [ap⁻ - 2] = stack⁻ [fp⁻] [ap⁻ - 3];
			stack⁻ [fp⁻] [ap⁻ - 3] = A;
			continue;
		}
		case OP_SWAP:
		{
			u16 A = stack⁻ [fp⁻] [ap⁻ - 1];
			stack⁻ [fp⁻] [ap⁻ - 1] = stack⁻ [fp⁻] [ap⁻ - 2];
			stack⁻ [fp⁻] [ap⁻ - 2] = A;
			continue;
		}
		case OP_TUCK:
		{
			stack⁻ [fp⁻] [ap⁻ - 3] = stack⁻ [fp⁻] [ap⁻ - 2];
			stack⁻ [fp⁻] [ap⁻ - 2] = stack⁻ [fp⁻] [ap⁻ - 1];
			-- ap⁻;
			continue;
		}
		// OP_CAT
		// OP_SUBSTR
		// OP_LEFT
		// OP_RIGHT
		// OP_SIZE
		// OP_INVERT
		// OP_AND
		// OP_OR
		// OP_XOR
		case OP_EQUAL:
		{
			u16 A＝B = stack⁻ [fp⁻] [-- ap⁻];
			u16 A = trace [A＝B].operand_0 = stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			u16 B = trace [A＝B].operand_1 = stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			trace [A＝B].opcode = OP_EQUAL;
			trace [A].reference = 1;
			trace [B].reference = 1;
			continue;
		}
		// OP_EQUALVERIFY
		// OP_RESERVED1
		// OP_RESERVED2
		case OP_1ADD:
		{
			u16 A＋1 = stack⁻ [fp⁻] [-- ap⁻];
			u16 A = trace [A＋1].operand_0 = stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			trace [A＋1].opcode = OP_1ADD;
			trace [A].reference = 1;
			continue;
		}
		case OP_1SUB:
		{
			u16 A－1 = stack⁻ [fp⁻] [-- ap⁻];
			u16 A = trace [A－1].operand_0 = stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			trace [A－1].opcode = OP_1ADD;
			trace [A].reference = 1;
			continue;
		}
		// OP_2MUL
		// OP_2DIV
		// OP_NEGATE
		// OP_ABS
		// OP_NOT
		// OP_0NOTEQUAL
		case OP_ADD:
		{
			u16 A＋B = stack⁻ [fp⁻] [-- ap⁻];
			u16 A = trace [A＋B].operand_0 = stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			u16 B = trace [A＋B].operand_1 = stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			trace [A＋B].opcode = OP_ADD;
			trace [A].reference = 1;
			trace [B].reference = 1;
			continue;
		}
		case OP_SUB:
		{
			u16 A－B = stack⁻ [fp⁻] [-- ap⁻];
			u16 A = trace [A－B].operand_0 = stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			u16 B = trace [A－B].operand_1 = stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			trace [A－B].opcode = OP_SUB;
			trace [A].reference = 1;
			trace [B].reference = 1;
			continue;
		}
		// OP_MUL
		// OP_DIV
		// OP_MOD
		// OP_LSHIFT
		// OP_RSHIFT
		case OP_BOOLAND:
		{
			u16 A＆B = stack⁻ [fp⁻] [-- ap⁻];	
			u16 A = trace [A＆B].operand_0 = stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			u16 B = trace [A＆B].operand_1 = stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			trace [A＆B].opcode = OP_BOOLAND;
			trace [A].reference = 1;
			trace [B].reference = 1;
			continue;
		}
		// OP_BOOLOR
		// OP_NUMEQUAL
		// OP_NUMEQUALVERIFY
		// OP_NUMNOTEQUAL
		case OP_LESSTHAN:
		{
			u16 A＜B = stack⁻ [fp⁻] [-- ap⁻];	
			u16 A = trace [A＜B].operand_0 = stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			u16 B = trace [A＜B].operand_1 = stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			trace [A＜B].opcode = OP_LESSTHAN;
			trace [A].reference = 1;
			trace [B].reference = 1;
			continue;
		}
		case OP_GREATERTHAN:
		{
			u16 A＞B = stack⁻ [fp⁻] [-- ap⁻];	
			u16 A = trace [A＞B].operand_0 = stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			u16 B = trace [A＞B].operand_1 = stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			trace [A＞B].opcode = OP_GREATERTHAN;
			trace [A].reference = 1;
			trace [B].reference = 1;
			continue;
		}
		case OP_LESSTHANOREQUAL:
		{
			u16 A＜BᵒʳA＝B = stack⁻ [fp⁻] [-- ap⁻];	
			u16 A = trace [A＜BᵒʳA＝B].operand_0 = stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			u16 B = trace [A＜BᵒʳA＝B].operand_1 = stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			trace [A＜BᵒʳA＝B].opcode = OP_LESSTHANOREQUAL;
			trace [A].reference = 1;
			trace [B].reference = 1;
			continue;
		}
		case OP_GREATERTHANOREQUAL:
		{
			u16 A＞BᵒʳA＝B = stack⁻ [fp⁻] [-- ap⁻];	
			u16 A = trace [A＞BᵒʳA＝B].operand_0 = stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			u16 B = trace [A＞BᵒʳA＝B].operand_1 = stack⁻ [fp⁻] [ap⁻ ++] = öp ++;
			trace [A＞BᵒʳA＝B].opcode = OP_GREATERTHANOREQUAL;
			trace [A].reference = 1;
			trace [B].reference = 1;
			continue;
		}
		// OP_MIN
		// OP_MAX
		// OP_WITHIN
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
		// ⋯
		default:
		{
			if (opcode < 0xC0) continue; // WARNING
			u16 _ = stack⁻ [fp⁻] [-- ap⁻];
			trace [_].opcode = opcode;
			continue;
		}
	}
	// UNLOCK INPUT
	for (; stack⁻ [fp⁻] [ap⁺] == x₂₃ - ap⁺; ++ ap⁺);
	for (ap⁺ = 0; ap⁺ <= x₂₃ - ap⁻; ++ ap⁺) stack⁺ [ap⁺] = stack⁻ [fp⁻] [ap⁺];
}
// ⋯
void serialize (u16 xᵢ)
{
	for (u16 n = 0; n < ap⁺; ++ n) if (stack⁺ [n] == xᵢ)
	{
		if (trace [xᵢ].reference == 0) return; // WARNING
		if (0 <-- trace [xᵢ].reference) switch (ap⁺ - n - 1)
		{
			case 0:
			{
				u16 x₀ = stack⁺ [-- ap⁺] = xᵢ;
				stack⁺ [ap⁺ ++] = x₀;
				stack⁺ [ap⁺ ++] = x₀;
				puts ("OP_DUP"); // fwrite (& OP_DUP, 1, 1, stdout)
				return;
			}
			case 1:
			{
				u16 x₀ = stack⁺ [-- ap⁺];
				u16 x₁ = stack⁺ [-- ap⁺] = xᵢ;
				stack⁺ [ap⁺ ++] = x₁;
				stack⁺ [ap⁺ ++] = x₀;
				stack⁺ [ap⁺ ++] = x₁;
				puts ("OP_OVER"); // fwrite (& OP_OVER, 1, 1, stdout)
				return;
			}
			default:
			{
				u16 xₙ = stack⁺ [ap⁺ - n - 1] = xᵢ;
				stack⁺ [ap⁺ ++] = xₙ;
				printf ("%hu OP_PICK\n", n); // fwrite (& OP_PICK, 1, 1, stdout)
				return;
			}
		}
		else switch (ap⁺ - n - 1)
		{
			case 0: return;
			case 1:
			{
				u16 tmp = stack⁺ [ap⁺ - 2];
				stack⁺ [ap⁺ - 2] = stack⁺ [ap⁺ - 1];
				stack⁺ [ap⁺ - 1] = tmp = xᵢ;
				puts ("OP_SWAP"); // fwrite (& OP_SWAP, 1, 1, stdout)
				return;
			}
			case 2:
			{
				u16 tmp = stack⁺ [ap⁺ - 3];
				stack⁺ [ap⁺ - 3] = stack⁺ [ap⁺ - 2];
				stack⁺ [ap⁺ - 2] = stack⁺ [ap⁺ - 1];
				stack⁺ [ap⁺ - 1] = tmp = xᵢ;
				puts ("OP_ROT"); // fwrite (& OP_ROT, 1, 1, stdout)
				return;
			}
			default:
			{
				u16 tmp = stack⁺ [ap⁺ - n - 1];
				stack⁺ [ap⁺ - n - 1] = stack⁺ [ap⁺ - n];
				stack⁺ [ap⁺ - 3] = stack⁺ [ap⁺ - 2];
				stack⁺ [ap⁺ - 2] = stack⁺ [ap⁺ - 1];
				stack⁺ [ap⁺ - 1] = tmp = xᵢ;
				printf ("%hu OP_ROLL\n", n); // fwrite (& OP_ROLL, 1, 1, stdout)
				return;
			}
		}
	}
	// RECURSIVE SERIALIZE
	switch (trace [xᵢ].opcode)
	{
		case OP_0:
			puts ("0"); // fwrite (& trace [xᵢ].opcode, 1, 1, stdout)
			return serialize (stack⁺ [ap⁺ ++] = xᵢ);
		// ⋯
		// OP_PUSHDATA1
		// OP_PUSHDATA2
		// OP_PUSHDATA4
		case OP_1NEGATE:
			puts ("-1"); // fwrite (& trace [xᵢ].opcode, 1, 1, stdout)
			return serialize (stack⁺ [ap⁺ ++] = xᵢ);
		// OP_RESERVED
		case OP_1:
		case OP_2:
		case OP_3:
		case OP_4:
		case OP_5:
		case OP_6:
		case OP_7:
		case OP_8:
		case OP_9:
		case OP_10:
		case OP_11:
		case OP_12:
		case OP_13:
		case OP_14:
		case OP_15:
		case OP_16:
			printf ("%i\n", trace [xᵢ].opcode - OP_RESERVED); // fwrite (& trace [xᵢ].opcode, 1, 1, stdout)
			return serialize (stack⁺ [ap⁺ ++] = xᵢ);
		case OP_NOP:
			puts ("OP_NOP");
			return;
		// OP_VER
		case OP_IF:
			serialize (trace [xᵢ].operand_1);
			serialize (trace [xᵢ].operand_2);
			serialize (trace [xᵢ].operand_0);
			stack⁺ [-- ap⁺] = trace [xᵢ].operand_0;
			puts ("OP_IF OP_NIP OP_ELSE OP_DROP OP_ENDIF");
			// u8 ？ [ ] = { OP_IF, OP_NIP, OP_ELSE, OP_DROP, OP_ENDIF }
			// fwrite (？, 1, sizeof ？, stdout)
			return serialize (stack⁺ [ap⁺ ++] = xᵢ);
		// OP_NOTIF
		// OP_VERIF
		// OP_VERNOTIF
		// OP_ELSE
		// OP_ENDIF
		// OP_VERIFY
		// OP_RETURN
		// OP_TOALTSTACK
		// OP_FROMALTSTACK
		// OP_2DROP
		// OP_2DUP
		// OP_3DUP
		// OP_2OVER
		// OP_2ROT
		// OP_2SWAP
		// OP_IFDUP
		// OP_DEPTH
		// OP_DROP
		// OP_DUP
		// OP_NIP
		// OP_OVER
		// OP_PICK
		// OP_ROLL
		// OP_ROT
		// OP_SWAP
		// OP_TUCK
		// OP_CAT
		// OP_SUBSTR
		// OP_LEFT
		// OP_RIGHT
		// OP_SIZE
		// OP_INVERT
		// OP_AND
		// OP_OR
		// OP_XOR
		case OP_EQUAL:
			serialize (trace [xᵢ].operand_0);
			serialize (trace [xᵢ].operand_1);
			stack⁺ [-- ap⁺] = trace [xᵢ].operand_1;
			stack⁺ [-- ap⁺] = trace [xᵢ].operand_0;
			puts ("OP_EQUAL"); // fwrite (& trace [xᵢ].opcode, 1, 1, stdout)
			return serialize (stack⁺ [ap⁺ ++] = xᵢ);
		// OP_EQUALVERIFY
		// OP_RESERVED1
		// OP_RESERVED2
		case OP_1ADD:
		case OP_1SUB:
			serialize (trace [xᵢ].operand_0);
			stack⁺ [ap⁺ - 1] = trace [xᵢ].operand_0;
			puts (trace [xᵢ].opcode == OP_1ADD ? "OP_1ADD" : "OP_1SUB"); // fwrite (& trace [xᵢ].opcode, 1, 1, stdout)
			return serialize (stack⁺ [ap⁺ - 1] = xᵢ);
		// OP_2MUL
		// OP_2DIV
		// OP_NEGATE
		// OP_ABS
		// OP_NOT
		// OP_0NOTEQUAL
		case OP_ADD:
		case OP_SUB:
			serialize (trace [xᵢ].operand_0);
			serialize (trace [xᵢ].operand_1);
			stack⁺ [-- ap⁺] = trace [xᵢ].operand_1;
			stack⁺ [-- ap⁺] = trace [xᵢ].operand_0;
			puts (trace [xᵢ].opcode == OP_ADD ? "OP_ADD" : "OP_SUB"); // fwrite (& trace [xᵢ].opcode, 1, 1, stdout)
			return serialize (stack⁺ [ap⁺ ++] = xᵢ);
		// OP_MUL
		// OP_DIV
		// OP_MOD
		// OP_LSHIFT
		// OP_RSHIFT
		case OP_BOOLAND:
			serialize (trace [xᵢ].operand_0);
			serialize (trace [xᵢ].operand_1);
			stack⁺ [-- ap⁺] = trace [xᵢ].operand_1;
			stack⁺ [-- ap⁺] = trace [xᵢ].operand_0;
			puts ("OP_BOOLAND"); // fwrite (& trace [xᵢ].opcode, 1, 1, stdout)
			return serialize (stack⁺ [ap⁺ ++] = xᵢ);
		// OP_BOOLOR
		// OP_NUMEQUAL
		// OP_NUMEQUALVERIFY
		// OP_NUMNOTEQUAL
		case OP_LESSTHAN:
		case OP_GREATERTHAN:
			serialize (trace [xᵢ].operand_0);
			serialize (trace [xᵢ].operand_1);
			stack⁺ [-- ap⁺] = trace [xᵢ].operand_1;
			stack⁺ [-- ap⁺] = trace [xᵢ].operand_0;
			puts (trace [xᵢ].opcode == OP_LESSTHAN ? "OP_LESSTHAN" : "OP_GREATERTHAN"); // fwrite (& trace [xᵢ].opcode, 1, 1, stdout)
			return serialize (stack⁺ [ap⁺ ++] = xᵢ);
		case OP_LESSTHANOREQUAL:
		case OP_GREATERTHANOREQUAL:
			serialize (trace [xᵢ].operand_0);
			serialize (trace [xᵢ].operand_1);
			stack⁺ [-- ap⁺] = trace [xᵢ].operand_1;
			stack⁺ [-- ap⁺] = trace [xᵢ].operand_0;
			puts (trace [xᵢ].opcode == OP_LESSTHANOREQUAL ? "OP_LESSTHANOREQUAL" : "OP_GREATERTHANOREQUAL"); // fwrite (& trace [xᵢ].opcode, 1, 1, stdout)
			return serialize (stack⁺ [ap⁺ ++] = xᵢ);
		// OP_MIN
		// OP_MAX
		// OP_WITHIN
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
		default:
			if (trace [xᵢ].opcode < 0xC0) return; // WARNING
			i32 const⁻ = const⁺ [trace [xᵢ].opcode - 0xC0].integer;
			printf ("%i\n", const⁻); // fwrite (& const⁻, 1, __builtin_clz (const⁻) / 8, stdout)
			return serialize (stack⁺ [ap⁺ ++] = xᵢ);
	}
}
