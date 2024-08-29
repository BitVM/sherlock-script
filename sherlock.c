# define _CRT_SECURE_NO_WARNINGS
# include "stdio.h"
# include "stdlib.h"
# include "assert.h"
# include "string.h"
# include "bitcoin.h"
void memswap (void * x₀, void * x₁, size_t n)
{
	void * tmp = memcpy (__builtin_alloca (n), x₀, n);
	memcpy (x₀, x₁, n), memcpy (x₁, tmp, n);
}
# ifndef min
# define min(x₀, x₁) ((x₀) < (x₁) ? (x₀) : (x₁))
# endif
# ifndef max
# define max(x₀, x₁) ((x₀) > (x₁) ? (x₀) : (x₁))
# endif
// ⋯
struct
{
	uint8_t code; // Sherlock script opcode
	uint8_t reference; // Reference counter
	union
	{
		int64_t num; // Constant
		uint32_t xₙ [3]; // Operands
		struct
		{
			uint32_t x₀, x₁, x₂;
		};
	};
}
# define ÖP_MIN OP_CHECKSIGADD + 1
# define ÖP_MAX 0x3FFF
trace [ÖP_MAX + 1] =
{
	[OP_0].code = OP_0,
	[OP_1NEGATE] = { .code = OP_1NEGATE, .num = -1 },
	[OP_1] = { .code = OP_1, .num = 1 },
	[OP_2] = { .code = OP_2, .num = 2 },
	[OP_3] = { .code = OP_3, .num = 3 },
	[OP_4] = { .code = OP_4, .num = 4 },
	[OP_5] = { .code = OP_5, .num = 5 },
	[OP_6] = { .code = OP_6, .num = 6 },
	[OP_7] = { .code = OP_7, .num = 7 },
	[OP_8] = { .code = OP_8, .num = 8 },
	[OP_9] = { .code = OP_9, .num = 9 },
	[OP_10] = { .code = OP_10, .num = 10 },
	[OP_11] = { .code = OP_11, .num = 11 },
	[OP_12] = { .code = OP_12, .num = 12 },
	[OP_13] = { .code = OP_13, .num = 13 },
	[OP_14] = { .code = OP_14, .num = 14 },
	[OP_15] = { .code = OP_15, .num = 15 },
	[OP_16] = { .code = OP_16, .num = 16 },
};
uint32_t öp = ÖP_MIN, öp⁻¹ = ÖP_MAX; // Trace allocation pointer
// Read nop-terminated script
uint8_t preprocess (void)
{
	uint8_t op;
	uint16_t ap, ap⁻¹;
	uint32_t stack [1000];
	uint32_t x₀, x₁, x₂;
	do switch (op = __builtin_stdin¹)
	{
		case OP_0:
			__builtin_push (OP_0);
			continue;
		case 1:
		case 2:
		case 3:
		case 4:
			// Read multibyte integer
			trace [öp⁻¹].num = __builtin_stdin (op);
			assert (trace [öp⁻¹].num > 16 || trace [öp⁻¹].num <= -1);
			assert (trace [öp⁻¹].num < +2147483648); // x < +2³¹
			assert (trace [öp⁻¹].num > -2147483648); // x > -2³¹
			for (uint32_t öp = ÖP_MAX; öp >= öp⁻¹; -- öp)
			{
				// öp⁻¹ + 0
				if (öp == öp⁻¹)
				{
					// Allocate constant
					assert (öp <= öp⁻¹);
					trace [öp⁻¹].code = op;
					__builtin_push (öp⁻¹ --);
					break;
				}
				// öp⁻¹ + 1 ⋯ 2¹² - 1
				if (trace [öp].code == op && trace [öp].num == trace [öp⁻¹].num)
				{
					// Recycle constant
					__builtin_push (öp);
					trace [öp⁻¹].num = 0;
					break;
				}
			}
			continue;
		// ⋯
		// OP_PUSHDATA1
		// OP_PUSHDATA2
		// OP_PUSHDATA4
		case OP_1NEGATE:
			__builtin_push (OP_1NEGATE);
			continue;
		case OP_RESERVED: // Function variable
			assert (öp <= öp⁻¹);
			// NOTE: OP_RESERVED "x₀"
			trace [öp].code = OP_RESERVED;
			trace [öp].num = öp - ÖP_MIN;
			__builtin_push (öp ++);
			continue;
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
			__builtin_push (op);
			continue;
		case OP_NOP: // nop-terminated
			return OP_NOP;
		case OP_VER: // Function definition
			// NOTE: OP_VER "f₀"
			continue; // WARNING
		case OP_IF:
		case OP_NOTIF:
		{
			x₀ = __builtin_drop;
			memmove (stack, __builtin_stack, sizeof stack);
			memmove (& ap, & __builtin_ap, sizeof ap);
			memmove (& ap⁻¹, & __builtin_ap⁻¹, sizeof ap⁻¹);
			switch (preprocess ( ))
			{
				case OP_ELSE:
					memswap (stack, __builtin_stack, sizeof stack);
					memswap (& ap, & __builtin_ap, sizeof ap);
					memswap (& ap⁻¹, & __builtin_ap⁻¹, sizeof ap⁻¹);
					if (preprocess ( ) != OP_ENDIF) fputs ("Assertion failed: OP_ENDIF\n", stderr);
					memswap (stack, __builtin_stack, sizeof stack);
					memswap (& ap, & __builtin_ap, sizeof ap);
					memswap (& ap⁻¹, & __builtin_ap⁻¹, sizeof ap⁻¹);
					// 🡇
				case OP_ENDIF:
					assert (__builtin_ap == ap);
					assert (__builtin_ap⁻¹ == ap⁻¹);
					break;
				default:
					fputs ("Assertion failed: OP_ENDIF\n", stderr); // WARNING
					break;
			}
			// Merge (alt)stack
			for (uint16_t ap = 0; ap <= 999; ++ ap)
			{
				if (ap == __builtin_ap)
				{
					ap = __builtin_ap⁻¹;
					continue;
				}
				x₁ = __builtin_stack [ap];
				x₂ = stack [ap];
				if (x₁ == x₂) continue;
				trace [öp].code = op;
				trace [öp].x₀ = x₀;
				trace [öp].x₁ = x₁;
				trace [öp].x₂ = x₂;
				__builtin_stack [ap] = öp ++;
			}
			continue;
		}
		// OP_VERIF
		// OP_VERNOTIF
		case OP_ELSE:
		case OP_ENDIF:
			return op;
		// OP_VERIFY
		// OP_RETURN
		case OP_TOALTSTACK:
			__builtin_stack [__builtin_ap⁻¹ --] = __builtin_drop;
			continue;
		case OP_FROMALTSTACK:
			assert (__builtin_ap⁻¹ < 999);
			__builtin_push (__builtin_stack [++ __builtin_ap⁻¹]);
			continue;
		case OP_2DROP:
			__builtin_drop;
			__builtin_drop;
			continue;
		case OP_2DUP:
			__builtin_over;
			__builtin_over;
			continue;
		case OP_3DUP:
			__builtin_pick (2);
			__builtin_pick (2);
			__builtin_pick (2);
			continue;
		case OP_2OVER:
			__builtin_pick (3);
			__builtin_pick (3);
			continue;
		case OP_2ROT:
			__builtin_roll (5);
			__builtin_roll (5);
			continue;
		case OP_2SWAP:
			__builtin_roll (3);
			__builtin_roll (3);
			continue;
		// OP_IFDUP
		case OP_DEPTH:
			assert (öp <= öp⁻¹);
			trace [öp].code = __builtin_ap ? OP_RESERVED + __builtin_ap : OP_0;
			trace [öp].num = __builtin_ap;
			__builtin_push (öp ++);
			continue;
		case OP_DROP:
			__builtin_drop;
			continue;
		case OP_DUP:
			__builtin_pick (0);
			continue;
		case OP_NIP:
			__builtin_swap;
			__builtin_drop;
			continue;
		case OP_OVER:
			__builtin_over;
			continue;
		case OP_PICK:
			__builtin_pick (trace [__builtin_drop].num);
			continue;
		case OP_ROLL:
			__builtin_roll (trace [__builtin_drop].num);
			continue;
		case OP_ROT:
			__builtin_roll (2);
			continue;
		case OP_SWAP:
			__builtin_swap;
			continue;
		case OP_TUCK:
			__builtin_swap;
			__builtin_over;
			continue;
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
		case OP_RESERVED1: // Function inline
			// NOTE: OP_RESERVED1 "f₀"
			continue; // WARNING
		case OP_RESERVED2: // Function call
			// NOTE: OP_RESERVED2 "f₀"
			continue; // WARNING
		case OP_1ADD:
		case OP_1SUB:
		case OP_2MUL:
		case OP_2DIV:
		case OP_NEGATE:
		case OP_ABS:
		case OP_NOT:
		case OP_0NOTEQUAL:
			assert (öp <= öp⁻¹);
			trace [öp].code = op;
			trace [öp].x₀ = __builtin_drop;
			__builtin_push (öp ++);
			continue;
		case OP_ADD:
			assert (öp <= öp⁻¹);
			if (__builtin_stack [__builtin_ap - 1] == __builtin_stack [__builtin_ap - 2]) // OP_ADD → OP_2MUL
			{
				trace [öp].code = OP_2MUL;
				trace [öp].x₀ = __builtin_drop;
				trace [öp].x₀ = __builtin_drop;
				__builtin_push (öp ++);
				continue;
			}
		case OP_SUB:
		case OP_MUL:
		case OP_DIV:
		case OP_MOD:
		case OP_LSHIFT:
		case OP_RSHIFT:
		case OP_BOOLAND:
		case OP_BOOLOR:
		case OP_NUMEQUAL:
		case OP_NUMEQUALVERIFY:
		case OP_NUMNOTEQUAL:
		case OP_LESSTHAN:
		case OP_GREATERTHAN:
		case OP_LESSTHANOREQUAL:
		case OP_GREATERTHANOREQUAL:
		case OP_MIN:
		case OP_MAX:
			assert (öp <= öp⁻¹);
			trace [öp].code = op;
			trace [öp].x₁ = __builtin_drop;
			trace [öp].x₀ = __builtin_drop;
			__builtin_push (öp ++);
			continue;
		case OP_WITHIN:
			assert (öp <= öp⁻¹);
			trace [öp].code = OP_WITHIN;
			trace [öp].x₂ = __builtin_drop;
			trace [öp].x₁ = __builtin_drop;
			trace [öp].x₀ = __builtin_drop;
			__builtin_push (öp ++);
			continue;
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
			continue; // WARNING
	}
	while (1);
}
// Select result
void attach (uint16_t x)
{
	switch (trace [x].code)
	{
		case OP_0:
			return;
		case 1:
		case 2:
		case 3:
		case 4:
			++ trace [x].reference;
			return;
		// ⋯
		// OP_PUSHDATA1
		// OP_PUSHDATA2
		// OP_PUSHDATA4
		case OP_1NEGATE:
			return;
		case OP_RESERVED:
			++ trace [x].reference;
			return;
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
			return;
		// OP_NOP
		// OP_VER
		case OP_IF:
		case OP_NOTIF:
			if (trace [x].reference ++) return;
			attach (trace [x].x₀);
			attach (trace [x].x₁);
			attach (trace [x].x₂);
			return;
		// OP_VERIF
		// OP_VERNOTIF
		// OP_ELSE
		// OP_ENDIF
		// OP_VERIFY
		// OP_RETURN
		// ⋯
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
		case OP_1ADD:
		case OP_1SUB:
		case OP_2MUL:
		case OP_2DIV:
		case OP_NEGATE:
		case OP_ABS:
		case OP_NOT:
		case OP_0NOTEQUAL:
			if (trace [x].reference ++) return;
			attach (trace [x].x₀);
			return;
		case OP_ADD:
		case OP_SUB:
		case OP_MUL:
		case OP_DIV:
		case OP_MOD:
		case OP_LSHIFT:
		case OP_RSHIFT:
		case OP_BOOLAND:
		case OP_BOOLOR:
		case OP_NUMEQUAL:
		case OP_NUMEQUALVERIFY:
		case OP_NUMNOTEQUAL:
		case OP_LESSTHAN:
		case OP_GREATERTHAN:
		case OP_LESSTHANOREQUAL:
		case OP_GREATERTHANOREQUAL:
		case OP_MIN:
		case OP_MAX:
			if (trace [x].reference ++) return;
			attach (trace [x].x₀);
			attach (trace [x].x₁);
			return;
		case OP_WITHIN:
			if (trace [x].reference ++) return;
			attach (trace [x].x₀);
			attach (trace [x].x₁);
			attach (trace [x].x₂);
			return;
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
			return; // WARNING
	}
}
uint32_t reference⁻¹ = 0x80000000;
// Count xᵢ in expression tree
uint16_t count⁺ (uint32_t xᵢ, uint32_t x₀, uint8_t _)
{
	if (x₀ == 0x80000000) return 0; // WARNING
	switch (trace [x₀].code)
	{
		case OP_0:
			return x₀ == xᵢ;
		case 1:
		case 2:
		case 3:
		case 4:
			return x₀ == xᵢ;
		// ⋯
		// OP_PUSHDATA1
		// OP_PUSHDATA2
		// OP_PUSHDATA4
		case OP_1NEGATE:
			return x₀ == xᵢ;
		case OP_RESERVED:
			return x₀ == xᵢ;
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
			return x₀ == xᵢ;
		case OP_NOP:
			return 0;
		// OP_VER
		case OP_IF:
		case OP_NOTIF:
			if (_ == 0) return x₀ == xᵢ;
			return (x₀ == xᵢ) ? 1 : count⁺ (xᵢ, trace [x₀].x₀, 0) + count⁺ (xᵢ, trace [x₀].x₁, 0) + count⁺ (xᵢ, trace [x₀].x₂, 0);
		// OP_VERIF
		// OP_VERNOTIF
		// OP_ELSE
		// OP_ENDIF
		// OP_VERIFY
		// OP_RETURN
		// ⋯
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
		case OP_1ADD:
		case OP_1SUB:
		case OP_2MUL:
		case OP_2DIV:
		case OP_NEGATE:
		case OP_ABS:
		case OP_NOT:
		case OP_0NOTEQUAL:
			if (_ == 0) return x₀ == xᵢ;
			return (x₀ == xᵢ) ? 1 : count⁺ (xᵢ, trace [x₀].x₀, 0);
		case OP_ADD:
		case OP_SUB:
		case OP_MUL:
		case OP_DIV:
		case OP_MOD:
		case OP_LSHIFT:
		case OP_RSHIFT:
		case OP_BOOLAND:
		case OP_BOOLOR:
		case OP_NUMEQUAL:
		case OP_NUMEQUALVERIFY:
		case OP_NUMNOTEQUAL:
		case OP_LESSTHAN:
		case OP_GREATERTHAN:
		case OP_LESSTHANOREQUAL:
		case OP_GREATERTHANOREQUAL:
		case OP_MIN:
		case OP_MAX:
			if (_ == 0) return x₀ == xᵢ;
			return (x₀ == xᵢ) ? 1 : count⁺ (xᵢ, trace [x₀].x₀, 0) + count⁺ (xᵢ, trace [x₀].x₁, 0);
		case OP_WITHIN:
			if (_ == 0) return x₀ == xᵢ;
			return (x₀ == xᵢ) ? 1 : count⁺ (xᵢ, trace [x₀].x₀, 0) + count⁺ (xᵢ, trace [x₀].x₁, 0) + count⁺ (xᵢ, trace [x₀].x₂, 0);
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
			return 0; // WARNING
	}
}
typedef enum : char { LEEWAY, STRICT } workflow;
// Permute stack elements
void translate¹ (uint16_t x)
{
	assert (__builtin_ap >= 1);
	uint32_t apₓ = __builtin_find (x);  assert (apₓ != 0x80000000);
	uint16_t Δap = __builtin_ap - apₓ - 1;
	uint8_t dup = trace [x].reference > count⁺ (x, reference⁻¹, 1) && __builtin_count (x) == 1;
	uint32_t xₙ [ ] = { x };
	switch (__builtin_check⁻¹ (xₙ, 1))
	{
		case 0b1:
			assert (Δap == 0);
			if (dup)
			{
				__builtin_swap;
				__builtin_over;
				__builtin_stdout¹ (OP_TUCK);
			}
			return;
		case 0b10:
			assert (Δap == 1);
			if (dup)
			{
				__builtin_over;
				__builtin_stdout¹ (OP_OVER);
			}
			else
			{
				__builtin_swap;
				__builtin_stdout¹ (OP_SWAP);
			}
			return;
		case 0b100:
			assert (Δap == 2);
			if (! dup)
			{
				__builtin_roll (2);
				__builtin_stdout¹ (OP_ROT);
				return;
			}
			// 🡇
		case 0b1000:
		case 0b10000:
		case 0b100000:
		case 0b1000000:
		case 0b10000000:
		case 0b100000000:
		case 0b1000000000:
		case 0b10000000000:
		case 0b100000000000:
		case 0b1000000000000:
		case 0b10000000000000:
		case 0b100000000000000:
		case 0b1000000000000000:
		case 0b10000000000000000:
			assert (Δap <= 16);
			__builtin_stdout¹ (OP_RESERVED + Δap);
			break;
		default:
			assert (Δap > 16);
			__builtin_stdout (Δap);
			break;
	}
	assert (Δap >= 2);
	if (dup)
	{
		__builtin_pick (Δap);
		__builtin_stdout¹ (OP_PICK);
	}
	else
	{
		__builtin_roll (Δap);
		__builtin_stdout¹ (OP_ROLL);
	}
	assert (__builtin_stack [__builtin_ap - 1] == x);
	return;
}
// Permute stack elements
void translate² (uint16_t x₀, uint16_t x₁, workflow s)
{
	uint32_t ap₀ = __builtin_find (x₀);  assert (ap₀ != 0x80000000);
	uint32_t ap₁ = __builtin_find (x₁);  assert (ap₁ != 0x80000000);
	uint16_t xˡʰˢ = __builtin_stack [min (ap₀, ap₁)];
	uint16_t xʳʰˢ = __builtin_stack [max (ap₀, ap₁)];
	uint32_t xₙ [ ] = {xˡʰˢ, xʳʰˢ};
	uint16_t dupˡʰˢ = trace [xˡʰˢ].reference > count⁺ (xˡʰˢ, reference⁻¹, 1) && __builtin_count (xˡʰˢ) == 1;
	uint16_t dupʳʰˢ = trace [xʳʰˢ].reference > count⁺ (xʳʰˢ, reference⁻¹, 1) && __builtin_count (xʳʰˢ) == 1;
	switch (__builtin_check⁻¹ (xₙ, 2))
	{
		case 0b110000:
			__builtin_roll (5);
			__builtin_roll (5);
			__builtin_stdout¹ (OP_2ROT);
			return translate² (x₀, x₁, s);
		case 0b1100:
			if (dupˡʰˢ && dupʳʰˢ)
			{
				__builtin_pick (3);
				__builtin_pick (3);
				__builtin_stdout¹ (OP_2OVER);
			}
			else
			{
				__builtin_roll (3);
				__builtin_roll (3);
				__builtin_stdout¹ (OP_2SWAP);
			}
			return translate² (x₀, x₁, s);
		case 0b110:
			if (dupˡʰˢ != dupʳʰˢ)
			{
				translate¹ (x₀);
				translate¹ (x₁);
				return;
			}
			if (x₀ == xˡʰˢ)
			{
				__builtin_roll (2);
				__builtin_stdout¹ (OP_ROT);
			}
			else // x₀ == xʳʰˢ
			{
				__builtin_swap;
				__builtin_stdout¹ (OP_SWAP);
			}
			return translate² (x₀, x₁, s);
		case 0b101:
			if (dupˡʰˢ != dupʳʰˢ)
			{
				translate¹ (x₀);
				translate¹ (x₁);
				return;
			}
			__builtin_roll (2);
			__builtin_stdout¹ (OP_ROT);
			return translate² (x₀, x₁, s);
		case 0b11:
			if (dupˡʰˢ && dupʳʰˢ)
			{
				__builtin_over;
				__builtin_over;
				__builtin_stdout¹ (OP_2DUP);
			}
			if (dupˡʰˢ != dupʳʰˢ)
			{
				if (dupˡʰˢ)
				{
					__builtin_over;
					__builtin_stdout¹ (OP_OVER);
				}
				if (dupʳʰˢ)
				{
					__builtin_swap;
					__builtin_over;
					__builtin_stdout¹ (OP_TUCK);
				}
			}
			if (s == STRICT && __builtin_stack [__builtin_ap - 1] == x₀)
			{
				__builtin_swap;
				__builtin_stdout¹ (OP_SWAP);
			}
			return;
		default:
			if (s == STRICT)
			{
				translate¹ (x₀);
				translate¹ (x₁);
			}
			else
			{
				translate¹ (xˡʰˢ);
				translate² (x₀, x₁, s);
			}
			return;
	}	
}
// Permute stack elements
void translate³ (uint16_t x₀, uint16_t x₁, uint16_t x₂, workflow s)
{
	uint32_t ap₀ = __builtin_find (x₀);  assert (ap₀ != 0x80000000);
	uint32_t ap₁ = __builtin_find (x₁);  assert (ap₁ != 0x80000000);
	uint32_t ap₂ = __builtin_find (x₂);  assert (ap₂ != 0x80000000);
	uint16_t xˡʰˢ = __builtin_stack [min (min (ap₀, ap₁), ap₂)];
	uint16_t xᵐⁱᵈ;
	uint16_t xʳʰˢ = __builtin_stack [max (max (ap₀, ap₁), ap₂)];
	if (x₀ != xˡʰˢ && x₀ != xʳʰˢ) xᵐⁱᵈ = x₀;
	if (x₁ != xˡʰˢ && x₁ != xʳʰˢ) xᵐⁱᵈ = x₁;
	if (x₂ != xˡʰˢ && x₂ != xʳʰˢ) xᵐⁱᵈ = x₂;
	uint32_t xₙ [ ] = {xˡʰˢ, xᵐⁱᵈ, xʳʰˢ};
	uint16_t dupˡʰˢ = trace [xˡʰˢ].reference > count⁺ (xˡʰˢ, reference⁻¹, 1) && __builtin_count (xˡʰˢ) == 1;
	uint16_t dupᵐⁱᵈ = trace [xᵐⁱᵈ].reference > count⁺ (xᵐⁱᵈ, reference⁻¹, 1) && __builtin_count (xᵐⁱᵈ) == 1;
	uint16_t dupʳʰˢ = trace [xʳʰˢ].reference > count⁺ (xʳʰˢ, reference⁻¹, 1) && __builtin_count (xʳʰˢ) == 1;
	switch (__builtin_check⁻¹ (xₙ, 3) & 0b111)
	{
		case 0b111:
			if (dupˡʰˢ && dupᵐⁱᵈ && dupʳʰˢ) // xᵢ xⱼ xₖ  →  xᵢ xⱼ xₖ
			{
				__builtin_pick (2);
				__builtin_pick (2);
				__builtin_pick (2);
				__builtin_stdout¹ (OP_3DUP);
				dupˡʰˢ = dupᵐⁱᵈ = dupʳʰˢ = 0;
			}
			if (s == STRICT)
			{
				if (x₁ == xˡʰˢ || x₂ == xˡʰˢ && ! dupˡʰˢ) // xᵢ x₀ xⱼ  →  x₀ xⱼ xᵢ
				{
					__builtin_roll (2);
					__builtin_stdout¹ (OP_ROT);
					translate³ (x₀, x₁, x₂, STRICT);
					return;
				}
			}
		case 0b11:
			if (dupᵐⁱᵈ && dupʳʰˢ) // xᵢ xⱼ  →  xᵢ xⱼ xᵢ xⱼ
			{
				__builtin_over;
				__builtin_over;
				__builtin_stdout¹ (OP_2DUP);
				translate³ (x₀, x₁, x₂, s);
				return;
			}
			if (s == STRICT)
			{
				if (x₂ == xᵐⁱᵈ && x₁ == xʳʰˢ) // x₀ x₂ x₁  →  x₀ x₁ x₂
				{
					__builtin_swap;
					__builtin_stdout¹ (OP_SWAP);
					translate³ (x₀, x₁, x₂, STRICT);
					return;
				}
			}
			if (dupᵐⁱᵈ) // xᵢ xⱼ  →  xᵢ xⱼ xᵢ
			{
				__builtin_over;
				__builtin_stdout¹ (OP_OVER);
				translate³ (x₀, x₁, x₂, s);
				return;
			}
			if (dupʳʰˢ) // xᵢ xⱼ  →  xⱼ xᵢ xⱼ
			{
				__builtin_swap;
				__builtin_over;
				__builtin_stdout¹ (OP_TUCK);
				translate³ (x₀, x₁, x₂, s);
				return;
			}
			if (dupˡʰˢ || __builtin_ap - __builtin_find (xˡʰˢ) - 1 >= 3) // xᵢ ⋯ xⱼ xₖ  →  xᵢ ⋯ xⱼ xₖ xᵢ
			{
				translate¹ (xˡʰˢ);
				if (s == STRICT) translate³ (x₀, x₁, x₂, STRICT);
				return;
			}
			if (x₁ == xᵐⁱᵈ && x₀ == xʳʰˢ) // x₂ ⋯ x₁ x₀  →  x₂ ⋯ x₀ x₁
			{
				__builtin_swap;
				__builtin_stdout¹ (OP_SWAP);
				translate³ (x₀, x₁, x₂, s);
				return;
			}
			if (s == STRICT)
			{
				assert (__builtin_stack [__builtin_ap - 3] == x₀);
				assert (__builtin_stack [__builtin_ap - 2] == x₁);
				assert (__builtin_stack [__builtin_ap - 1] == x₂);
			}
			return;
		case 0b110:
		case 0b101:
			translate² (xᵐⁱᵈ, xʳʰˢ, LEEWAY);
			translate³ (x₀, x₁, x₂, s);
			return;
		default:
			if (s == LEEWAY)
			{
				translate¹ (xʳʰˢ);
				translate¹ (xᵐⁱᵈ);
				translate¹ (xˡʰˢ);
				return;
			}
			if (s == STRICT)
			{
				translate¹ (x₀);
				translate¹ (x₁);
				translate¹ (x₂);
				assert (__builtin_stack [__builtin_ap - 3] == x₀);
				assert (__builtin_stack [__builtin_ap - 2] == x₁);
				assert (__builtin_stack [__builtin_ap - 1] == x₂);
				return;
			}
	}
}
// Dispatch x₀ ⋯ xₙ₋₁
uint32_t translate (const uint32_t xₙ [ ], uint8_t n, workflow s)
{
	uint32_t xᵢ;
	uint32_t x₀, x₁, x₂;
	switch (n)
	{
		case 0:
			return 0x80000000; // WARNING
		case 1:
			x₀ = xₙ [0];
			if (trace [x₀].reference != 0) -- trace [x₀].reference;
			translate¹ (x₀);
			assert (__builtin_find (x₀) == __builtin_ap - 1), __builtin_drop;
			return x₀;
		case 2:
			x₀ = xₙ [0];
			x₁ = xₙ [1];
			if (trace [x₀].reference != 0) -- trace [x₀].reference;
			if (trace [x₁].reference != 0) -- trace [x₁].reference;
			translate² (x₀, x₁, s);
			if (s == STRICT)
			{
				assert (__builtin_find (x₁) == __builtin_ap - 1), __builtin_drop;
				assert (__builtin_find (x₀) == __builtin_ap - 1), __builtin_drop;
				return x₁;
			}
			assert (__builtin_check (xₙ, 2) == 0b11);
			xᵢ = __builtin_stack [__builtin_ap - 1];
			__builtin_drop;
			__builtin_drop;
			return xᵢ;
		case 3:
			x₀ = xₙ [0];
			x₁ = xₙ [1];
			x₂ = xₙ [2];
			if (trace [x₀].reference != 0) -- trace [x₀].reference;
			if (trace [x₁].reference != 0) -- trace [x₁].reference;
			if (trace [x₂].reference != 0) -- trace [x₂].reference;
			translate³ (x₀, x₁, x₂, s);
			if (s == STRICT)
			{
				assert (__builtin_find (x₂) == __builtin_ap - 1), __builtin_drop;
				assert (__builtin_find (x₁) == __builtin_ap - 1), __builtin_drop;
				assert (__builtin_find (x₀) == __builtin_ap - 1), __builtin_drop;
				return x₂;
			}
			assert (__builtin_check (xₙ, 3) == 0b111);
			xᵢ = __builtin_stack [__builtin_ap - 1];
			__builtin_drop;
			__builtin_drop;
			__builtin_drop;
			return xᵢ;
		default: // WARNING
			assert (s == LEEWAY);
			for (uint8_t i = 0; i < n; ++ i) assert (__builtin_find (xₙ [i]) != 0x80000000);
			xᵢ = __builtin_drop;
			for (uint8_t i = 1; i < n; ++ i) __builtin_drop;
			return xᵢ;
	}
}
// Discard expression
void serialize⁻ (uint16_t x)
{
	uint32_t apₓ = __builtin_find (x);
	if (apₓ == 0x80000000) switch (trace [x].code)
	{
		case OP_0:
			return;
		case 1:
		case 2:
		case 3:
		case 4:
			return;
		// ⋯
		// OP_PUSHDATA1
		// OP_PUSHDATA2
		// OP_PUSHDATA4
		case OP_1NEGATE:
			return;
		case OP_RESERVED:
			return;
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
			return;
		case OP_NOP:
			return;
		// OP_VER
		case OP_IF:
		case OP_NOTIF:
			serialize⁻ (trace [x].x₀);
			serialize⁻ (trace [x].x₁);
			serialize⁻ (trace [x].x₂);
			return;
		// OP_VERIF
		// OP_VERNOTIF
		// OP_ELSE
		// OP_ENDIF
		// OP_VERIFY
		// OP_RETURN
		// ⋯
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
		case OP_1ADD:
		case OP_1SUB:
		case OP_2MUL:
		case OP_2DIV:
		case OP_NEGATE:
		case OP_ABS:
		case OP_NOT:
		case OP_0NOTEQUAL:
			serialize⁻ (trace [x].x₀);
			return;
		case OP_ADD:
		case OP_SUB:
		case OP_MUL:
		case OP_DIV:
		case OP_MOD:
		case OP_LSHIFT:
		case OP_RSHIFT:
		case OP_BOOLAND:
		case OP_BOOLOR:
		case OP_NUMEQUAL:
		case OP_NUMEQUALVERIFY:
		case OP_NUMNOTEQUAL:
		case OP_LESSTHAN:
		case OP_GREATERTHAN:
		case OP_LESSTHANOREQUAL:
		case OP_GREATERTHANOREQUAL:
		case OP_MIN:
		case OP_MAX:
			serialize⁻ (trace [x].x₀);
			serialize⁻ (trace [x].x₁);
			return;
		case OP_WITHIN:
			serialize⁻ (trace [x].x₀);
			serialize⁻ (trace [x].x₁);
			serialize⁻ (trace [x].x₂);
			return;
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
			return; // WARNING
	}
	uint16_t Δap = __builtin_ap - apₓ - 1;
	if (trace [x].reference < count⁺ (x, reference⁻¹, 1) && __builtin_count (x) == 1) switch (Δap)
	{
		case 0:
			__builtin_drop;
			__builtin_stdout¹ (OP_DROP);
			return;
		case 1:
			__builtin_swap;
			__builtin_drop;
			__builtin_stdout¹ (OP_NIP);
			return;
		case 2:
			__builtin_roll (2);
			__builtin_stdout¹ (OP_ROT);
			__builtin_drop;
			__builtin_stdout¹ (OP_DROP);
			return;
		default:
			__builtin_stdout (Δap);
			__builtin_roll (Δap);
			__builtin_stdout¹ (OP_ROLL);
			__builtin_drop;
			__builtin_stdout¹ (OP_DROP);
			return;
	}
}
// Compute expression
void serialize⁺ (uint16_t x)
{
	int64_t num;
	uint16_t ap, ap⁻¹;
	uint32_t stack [1000];	
	uint32_t x₀, x₁, x₂;
	uint32_t * xₙ = trace [x].xₙ;
	uint32_t apₓ = __builtin_find (x);
	uint32_t ap₀, ap₁, ap₂;
	// Compute x
	switch (trace [x].code)
	{
		case OP_0:
			assert (trace [x].reference == 0);
			__builtin_push (x);
			__builtin_stdout¹ (OP_0);
			break;
		case 1:
		case 2:
		case 3:
		case 4:
			assert (trace [x].reference != 0);
			if (apₓ != 0x80000000) break;
			num = trace [x].num;
			assert (num > 16 || num <= -1);
			assert (num < +2147483648); // x < +2³¹
			assert (num > -2147483648); // x > -2³¹
			__builtin_stdout (num);
			__builtin_push (x);
			break;
		// ⋯
		// OP_PUSHDATA1
		// OP_PUSHDATA2
		// OP_PUSHDATA4
		// OP_1NEGATE
		case OP_RESERVED:
			assert (trace [x].reference != 0);
			assert (apₓ != 0x80000000);
			break;
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
			assert (trace [x].reference == 0);
			__builtin_stdout¹ (trace [x].code);
			__builtin_push (x);
			break;
		case OP_NOP:
			__builtin_stdout¹ (OP_NOP);
			break;
		// OP_VER
		case OP_IF:
		case OP_NOTIF:
			if (apₓ != 0x80000000) break;
			x₀ = trace [x].x₀, ap₀ = __builtin_find (x₀);  assert (ap₀ != 0x80000000);
			x₁ = trace [x].x₁, ap₁ = __builtin_find (x₁);
			x₂ = trace [x].x₂, ap₂ = __builtin_find (x₂);
			if (ap₁ == 0x80000000 && trace [x₁].reference >= 2) serialize⁺ (x₁), ap₁ = __builtin_find (x₁);
			if (ap₂ == 0x80000000 && trace [x₂].reference >= 2) serialize⁺ (x₂), ap₂ = __builtin_find (x₂);
			translate (& x₀, 1, STRICT);
			__builtin_stdout¹ (trace [x].code);
			memmove (stack, __builtin_stack, sizeof stack);
			memmove (& ap, & __builtin_ap, sizeof ap);
			memmove (& ap⁻¹, & __builtin_ap⁻¹, sizeof ap⁻¹);
			reference⁻¹ = x₂;
			if (ap₁ == 0x80000000) serialize⁺ (x₁);
			uint8_t reference₁ = trace [x₁].reference;
			translate (& x₁, 1, STRICT);
			serialize⁻ (x₂);
			if (reference₁ != 0) ++ trace [x₁].reference;
			__builtin_push (x);
			__builtin_stdout¹ (OP_ELSE);
			memswap (stack, __builtin_stack, sizeof stack);
			memswap (& ap, & __builtin_ap, sizeof ap);
			memswap (& ap⁻¹, & __builtin_ap⁻¹, sizeof ap⁻¹);
			reference⁻¹ = x₁;
			if (ap₂ == 0x80000000) serialize⁺ (x₂);
			uint8_t reference₂ = trace [x₂].reference;
			serialize⁻ (x₁);
			translate (& x₂, 1, STRICT);
			if (reference₂ != 0) ++ trace [x₂].reference;
			__builtin_push (x);
			__builtin_stdout¹ (OP_ENDIF);
			reference⁻¹ = 0x80000000;
			assert (__builtin_ap == ap);
			assert (__builtin_ap⁻¹ == ap⁻¹);
			break;
		// OP_VERIF
		// OP_VERNOTIF
		// OP_ELSE
		// OP_ENDIF
		// OP_VERIFY
		// OP_RETURN
		// ⋯
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
		case OP_1ADD:
		case OP_1SUB:
			if (apₓ != 0x80000000) break;
			x₀ = trace [x].x₀;
			ap₀ = __builtin_find (x₀);
			if (ap₀ == 0x80000000) serialize⁺ (x₀);
			assert (trace [x].reference != 0);
			translate (& x₀, 1, STRICT);
			__builtin_push (x);
			__builtin_stdout¹ (trace [x].code);
			break;
		case OP_2MUL:
			if (apₓ != 0x80000000) break;
			x₀ = trace [x].x₀, ap₀ = __builtin_find (x₀);
			if (ap₀ == 0x80000000) serialize⁺ (x₀);
			assert (trace [x].reference != 0);
			translate (& x₀, 1, STRICT);
			__builtin_stdout¹ (OP_DUP);
			__builtin_stdout¹ (OP_ADD);
			__builtin_push (x);
			break;
		case OP_2DIV:
		case OP_NEGATE:
		case OP_ABS:
		case OP_NOT:
		case OP_0NOTEQUAL:
			if (apₓ != 0x80000000) break;
			x₀ = trace [x].x₀, ap₀ = __builtin_find (x₀);
			if (ap₀ == 0x80000000) serialize⁺ (x₀);
			assert (trace [x].reference != 0);
			translate (& x₀, 1, STRICT);
			__builtin_stdout¹ (trace [x].code);
			__builtin_push (x);
			break;
		case OP_ADD:
			if (apₓ != 0x80000000) break;
			x₀ = trace [x].x₀, ap₀ = __builtin_find (x₀);
			x₁ = trace [x].x₁, ap₁ = __builtin_find (x₁);
			if (ap₀ == 0x80000000) serialize⁺ (trace [x].x₀);
			if (ap₁ == 0x80000000) serialize⁺ (trace [x].x₁);
			assert (trace [x].reference != 0);
			translate (xₙ, 2, LEEWAY);
			__builtin_push (x);
			__builtin_stdout¹ (OP_ADD);
			break;
		case OP_SUB:
			if (apₓ != 0x80000000) break;
			x₀ = trace [x].x₀, ap₀ = __builtin_find (x₀);
			x₁ = trace [x].x₁, ap₁ = __builtin_find (x₁);
			if (ap₀ == 0x80000000) serialize⁺ (x₀);
			if (ap₁ == 0x80000000) serialize⁺ (x₁);
			assert (trace [x].reference != 0);
			translate (xₙ, 2, STRICT);
			__builtin_push (x);
			__builtin_stdout¹ (OP_SUB);
			break;
		// OP_MUL
		// OP_DIV
		// OP_MOD
		// OP_LSHIFT
		// OP_RSHIFT
		case OP_BOOLAND:
		case OP_BOOLOR:
		case OP_NUMEQUAL:
		case OP_NUMEQUALVERIFY:
		case OP_NUMNOTEQUAL:
			if (apₓ != 0x80000000) break;
			x₀ = trace [x].x₀, ap₀ = __builtin_find (x₀);
			x₁ = trace [x].x₁, ap₁ = __builtin_find (x₁);
			if (ap₀ == 0x80000000) serialize⁺ (x₀);
			if (ap₁ == 0x80000000) serialize⁺ (x₁);
			ap₀ = __builtin_find (x₀);  assert (ap₀ != 0x80000000);
			ap₁ = __builtin_find (x₁);  assert (ap₁ != 0x80000000);
			assert (trace [x].reference != 0);
			translate (xₙ, 2, LEEWAY);
			__builtin_push (x);
			__builtin_stdout¹ (trace [x].code);
			break;
		case OP_LESSTHAN:
		case OP_GREATERTHAN:
		case OP_LESSTHANOREQUAL:
		case OP_GREATERTHANOREQUAL:
			if (apₓ != 0x80000000) break;
			x₀ = trace [x].x₀, ap₀ = __builtin_find (x₀);
			x₁ = trace [x].x₁, ap₁ = __builtin_find (x₁);
			if (ap₀ == 0x80000000) serialize⁺ (x₀);
			if (ap₁ == 0x80000000) serialize⁺ (x₁);
			ap₀ = __builtin_find (x₀);  assert (ap₀ != 0x80000000);
			ap₁ = __builtin_find (x₁);  assert (ap₁ != 0x80000000);
			assert (trace [x].reference != 0);
			if (translate (xₙ, 2, LEEWAY) == x₁) __builtin_stdout¹ (trace [x].code);
			else switch (trace [x].code)
			{
				case OP_LESSTHAN: __builtin_stdout¹ (OP_GREATERTHANOREQUAL); break;
				case OP_GREATERTHAN: __builtin_stdout¹ (OP_LESSTHANOREQUAL); break;
				case OP_LESSTHANOREQUAL: __builtin_stdout¹ (OP_GREATERTHAN); break;
				case OP_GREATERTHANOREQUAL: __builtin_stdout¹ (OP_LESSTHAN); break;
				default: break; // WARNING
			}
			__builtin_push (x);
			break;
		case OP_MIN:
		case OP_MAX:
			if (apₓ != 0x80000000) break;
			x₀ = trace [x].x₀, ap₀ = __builtin_find (x₀);
			x₁ = trace [x].x₁, ap₁ = __builtin_find (x₁);
			if (ap₀ == 0x80000000) serialize⁺ (x₀);
			if (ap₁ == 0x80000000) serialize⁺ (x₁);
			ap₀ = __builtin_find (x₀);  assert (ap₀ != 0x80000000);
			ap₁ = __builtin_find (x₁);  assert (ap₁ != 0x80000000);
			assert (trace [x].reference != 0);
			translate (xₙ, 2, LEEWAY);
			__builtin_push (x);
			__builtin_stdout¹ (trace [x].code);
			break;
		case OP_WITHIN:
			if (apₓ != 0x80000000) break;
			x₀ = trace [x].x₀, ap₀ = __builtin_find (x₀);
			x₁ = trace [x].x₁, ap₁ = __builtin_find (x₁);
			x₂ = trace [x].x₂, ap₂ = __builtin_find (x₂);
			if (ap₀ == 0x80000000) serialize⁺ (x₀);
			if (ap₁ == 0x80000000) serialize⁺ (x₁);
			if (ap₂ == 0x80000000) serialize⁺ (x₂);
			ap₀ = __builtin_find (x₀);  assert (ap₀ != 0x80000000);
			ap₁ = __builtin_find (x₁);  assert (ap₁ != 0x80000000);
			ap₂ = __builtin_find (x₂);  assert (ap₂ != 0x80000000);
			assert (trace [x].reference != 0);
			translate (xₙ, 3, STRICT);
			__builtin_push (x);
			__builtin_stdout¹ (trace [x].code);
			break;
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
			break; // WARNING
	}
}
// Dissolve expression (recursively)
void serialize⁰ (uint16_t x)
{
	if (__builtin_find (x) != 0x80000000) return;
	uint8_t op;
	switch (op = trace [x].code)
	{
		case OP_0:
			assert (trace [x].reference == 0);
			return;
		case 1:
		case 2:
		case 3:
		case 4:
			assert (trace [x].reference >= 1);
			if (trace [x].reference >= 2) serialize⁺ (x);
			return;
		// ⋯
		// OP_PUSHDATA1
		// OP_PUSHDATA2
		// OP_PUSHDATA4
		case OP_1NEGATE:
			assert (trace [x].reference == 0);
			return;
		case OP_RESERVED:
			assert (trace [x].reference >= 1);
			return; // WARNING
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
			assert (trace [x].reference == 0);
			return;
		// OP_NOP
		// OP_VER
		case OP_IF:
		case OP_NOTIF:
			assert (trace [x].reference >= 1);
			serialize⁰ (trace [x].x₀);
			serialize⁰ (trace [x].x₁);
			serialize⁰ (trace [x].x₂), serialize⁺ (trace [x].x₀);
			if (trace [x].reference >= 2) serialize⁺ (x);
			return;
		// OP_VERIF
		// OP_VERNOTIF
		// OP_ELSE
		// OP_ENDIF
		// OP_VERIFY
		// OP_RETURN
		// ⋯
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
		case OP_1ADD:
		case OP_1SUB:
		case OP_2MUL:
		case OP_2DIV:
		case OP_NEGATE:
		case OP_ABS:
		case OP_NOT:
		case OP_0NOTEQUAL:
			assert (trace [x].reference >= 1);
			serialize⁰ (trace [x].x₀), serialize⁺ (trace [x].x₀);
			if (trace [x].reference >= 2) serialize⁺ (x);
			return;
		case OP_ADD:
		case OP_SUB:
		case OP_MUL:
		case OP_DIV:
		case OP_MOD:
		case OP_LSHIFT:
		case OP_RSHIFT:
		case OP_BOOLAND:
		case OP_BOOLOR:
		case OP_NUMEQUAL:
		case OP_NUMEQUALVERIFY:
		case OP_NUMNOTEQUAL:
		case OP_LESSTHAN:
		case OP_GREATERTHAN:
		case OP_LESSTHANOREQUAL:
		case OP_GREATERTHANOREQUAL:
		case OP_MIN:
		case OP_MAX:
			assert (trace [x].reference >= 1);
			serialize⁰ (trace [x].x₀), serialize⁺ (trace [x].x₀);
			serialize⁰ (trace [x].x₁), serialize⁺ (trace [x].x₁);
			if (trace [x].reference >= 2) serialize⁺ (x);
			return;
		case OP_WITHIN:
			assert (trace [x].reference >= 1);
			serialize⁰ (trace [x].x₀), serialize⁺ (trace [x].x₀);
			serialize⁰ (trace [x].x₁), serialize⁺ (trace [x].x₁);
			serialize⁰ (trace [x].x₂), serialize⁺ (trace [x].x₂);
			if (trace [x].reference >= 2) serialize⁺ (x);
			return;
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
			return; // WARNING
	}
}
// Flush Bitcoin script
void serialize (const uint32_t xₙ [ ], uint8_t n, workflow s)
{
	// Compute x₀ ⋯ xₙ₋₁
	for (uint8_t i = 0; i < n; ++ i)
	{
		serialize⁰ (xₙ [i]);
		serialize⁺ (xₙ [i]);
	}
	if (__builtin_ap != n) fprintf (stderr, "Assertion failed: ap %s %hu\n", __builtin_ap < n ? "≥" : "≤", n);
	for (uint8_t i = 0; i < n; ++ i) assert (__builtin_find (xₙ [i]) != 0x80000000);
	// Permute stack elements
	translate (xₙ, n, s);
	return;
}
// $ clang sherlock.c -o sherlock
// > clang sherlock.c -o sherlock.exe
int main (void)
{
	freopen (NULL, "rb", stdin); // _setmode (_fileno (stdin), _O_BINARY)
	freopen (NULL, "wb", stdout); // _setmode (_fileno (stdout), _O_BINARY)
	freopen (NULL, "wb", stderr); // _setmode (_fileno (stderr), _O_BINARY)
	// Trace script
	uint8_t op = preprocess ( );
	assert (op == OP_NOP);
	// Mark result(s)
	uint32_t xₙ [0x45] = { [0 ... 0x44] = 0x80000000 };	
	uint8_t n = 0;
	while (__builtin_ap > 0) attach (xₙ [n ++] = __builtin_drop);
	if (__builtin_ap⁻¹ < 999) fputs ("Assertion failed: OP_FROMALTSTACK\n", stderr);
	while (++ __builtin_ap⁻¹ <= 999) __builtin_stack [__builtin_ap⁻¹] = 0x80000000;
	// Push variable(s)
	for (uint32_t x = ÖP_MIN; trace [x].code == OP_RESERVED; ++ x) __builtin_push (x);
	// Flush Bitcoin script
	if (n >= 1) serialize (xₙ, n, LEEWAY); else fputs ("Assertion failed: n ≥ 1\n", stderr);
	return 0;
}
