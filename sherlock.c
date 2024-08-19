# define _CRT_SECURE_NO_WARNINGS
# include "stdio.h"
# include "stdlib.h"
# include "assert.h"
# include "string.h"
# include "bitcoin.h"
# ifndef min
# define min(x₀, x₁) ((x₀) < (x₁) ? (x₀) : (x₁))
# endif
# ifndef max
# define max(x₀, x₁) ((x₀) > (x₁) ? (x₀) : (x₁))
# endif
// move（$ ¥）:｛$ ¥｝→｛$ $｝
void move (const uint16_t * lhs, uint16_t * rhs)
{
	* rhs = * lhs; // --->
}
// swap（$ ¥）💱｛$ ¥｝→｛¥ $｝
void swap (uint16_t * lhs, uint16_t * rhs)
{
	uint16_t tmp = * lhs;
	* lhs = * rhs; // <----
	* rhs = tmp;  // ---->
}
// lzcnt（0x00000000）→ undefined
# define lzcnt(uint32_t) (uint8_t)__builtin_clz(uint32_t)
// tzcnt（0x00000000）→ undefined
# define tzcnt(uint32_t) (uint8_t)__builtin_ctz(uint32_t)
// popcnt（0xFFFFFFFF）→ 32
# define popcnt(uint32_t) (uint8_t)__builtin_popcount(uint32_t)
# define blsi(uint32_t) (uint32_t) ? 1 << tzcnt (uint32_t) : 0
# define blsmsk(uint32_t) (uint32_t) ^ (uint32_t) - 1
# define blsr(uint32_t) (uint32_t) & (uint32_t) - 1
// find（xᵢ｛x₀⋯xₙ₋₁｝n）→ i
uint16_t find (const uint16_t x, const uint16_t * xₙ, uint8_t n)
{
	for (uint16_t i = 0; n --> 0; ++ i)
	{
		// NOTE: First index provided
		if (x == * xₙ ++) return i;
	}
	// NOTE: 2³²⁷⁶⁸ <=>  1 << 2¹⁵  <=>  0
	return 0x8000; // 2¹⁵  <=>  32768
}
uint16_t find⁻¹ (const uint16_t x, const uint16_t * xₙ, uint8_t n)
{
	uint16_t idx = 0x8000; // 2¹⁵  <=>  32768
	// NOTE: 2³²⁷⁶⁸ <=>  1 << 2¹⁵  <=>  0
	for (uint16_t i = 0; n --> 0; ++ i)
	{
		if (x == * xₙ ++) idx = i;
	}
	// NOTE: Last index provided
	return idx;
}
// NOTE: check（xₙ n xₘ m）⩵（1 << n）- 1  <=>  popcnt（check（xₙ n xₘ m））⩵ n
uint32_t check (const uint16_t * xₙ, uint8_t n, const uint16_t * xₘ, uint8_t m)
{
	uint32_t flag = 0x00000000;
	while (m --> 0) // assert n ≤ 32
	{
		uint16_t _ = find (* xₘ ++, xₙ, n);
		// flag |= 1 << min (16, _);
		if (_ != 0x8000) flag |= 1 << _;
	}
	// NOTE: find（x₀ xₙ n）→ 2¹⁵ ❓
	return flag;
}
uint32_t check⁻¹ (const uint16_t * xₙ, uint8_t n, const uint16_t * xₘ, uint8_t m)
{
	uint32_t flag = 0x00000000;
	while (m --> 0) // assert n ≤ 32
	{
		uint16_t _ = find⁻¹ (* xₘ ++, xₙ, n);
		// flag |= 1 << min (16, _);
		if (_ != 0x8000) flag |= 1 << _;
	}
	// NOTE: find（x₀ xₙ n）→ 2¹⁵ ❓
	return flag;
}
// NOTE: count（x₀ xₙ n）≠ 0  <=>  popcnt（check（x₀ 1 xₙ n））≠ 0
uint8_t count (const uint16_t x, const uint16_t * xₙ, uint8_t n)
{
	uint8_t cnt = 0;
	while (n --> 0)
	{
		if (x == * xₙ ++) ++ cnt;
	}
	return cnt;
}
// ⋯
const uint16_t nop = OP_NOP; // NOTE: nop-terminated script
const uint16_t x₀ = OP_CHECKSIGADD + 1; // Unlocking variable
// const uint8_t f₀ = OP_CHECKSIGADD + 42; // Function definition
// char function [24] [48] = { "f₀", "f₁", "f₂", "f₃", "f₄", "f₅", "f₆", "f₇", "f₈", "f₉", "f₁₀",
// 	"f₁₁", "f₁₂", "f₁₃", "f₁₄", "f₁₅", "f₁₆", "f₁₇", "f₁₈", "f₁₉", "f₂₀", "f₂₁", "f₂₂", "f₂₃" };
char variable [24] [48] = { "x₀", "x₁", "x₂", "x₃", "x₄", "x₅", "x₆", "x₇", "x₈", "x₉", "x₁₀",
	"x₁₁", "x₁₂", "x₁₃", "x₁₄", "x₁₅", "x₁₆", "x₁₇", "x₁₈", "x₁₉", "x₂₀", "x₂₁", "x₂₂", "x₂₃" };
struct {
	uint8_t code; // Sherlock script opcode
	uint8_t reference; // Reference counter
	union
	{
		int64_t num; // Constant
		uint16_t xₙ [4]; // Operands
		struct
		{
			uint16_t x₀, x₁, x₂, x₃;
		};
	};
} trace [0x4000] = {
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
	[OP_NOP].code = nop,
	[x₀ ... 0x3FFF].code = nop,
};
uint16_t öp = x₀, öp⁻¹ = 0x3FFF; // Trace allocation pointer
uint16_t stack [1000] = { [0 ... 999] = nop };
uint16_t ap = 0, ap⁻¹ = 999; // Stack allocation pointer
// Read nop-terminated script
uint8_t preprocess (void)
{
	uint16_t op = nop;
	while (fread (& op, 1, 1, stdin) > 0) switch (op)
	{
		case OP_0:
			assert (ap <= ap⁻¹);
			move (& op, & stack [ap ++]);
			continue;
		case 1:
		case 2:
		case 3:
		case 4:
			assert (ap <= ap⁻¹);
			assert (öp <= öp⁻¹);
			// Read multibyte integer
			fread (& trace [öp⁻¹].xₙ, 1, op, stdin);
			assert (trace [öp⁻¹].num > 16 || trace [öp⁻¹].num <= -1);
			assert (trace [öp⁻¹].num < +2147483648); // x < +2³¹
			assert (trace [öp⁻¹].num > -2147483648); // x > -2³¹
			for (uint16_t öp = 0x3FFF; öp >= öp⁻¹; -- öp)
			{
				// öp⁻¹ + 0
				if (öp == öp⁻¹)
				{
					// Allocate constant
					move (& öp⁻¹, & stack [ap ++]), trace [öp⁻¹ --].code = op;
					break;
				}
				// öp⁻¹ + 1 ⋯ 2¹² - 1
				if (trace [öp].code == op && trace [öp].num == trace [öp⁻¹].num)
				{
					// Recycle constant
					move (& öp, & stack [ap ++]), trace [öp⁻¹].num = 0;
					break;
				}
			}
			continue;
		// ⋯
		// OP_PUSHDATA1
		// OP_PUSHDATA2
		// OP_PUSHDATA4
		case OP_1NEGATE:
			assert (ap <= ap⁻¹);
			move (& op, & stack [ap ++]);
			continue;
		case OP_RESERVED: // Function variable
			assert (ap <= ap⁻¹);
			assert (öp <= öp⁻¹);
			// NOTE: OP_RESERVED "x₀"
			trace [öp].code = OP_RESERVED;
			trace [öp].num = öp - x₀;
			move (& öp, & stack [ap ++]), ++ öp;
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
			assert (ap <= ap⁻¹);
			move (& op, & stack [ap ++]);
			continue;
		case OP_NOP: // nop-terminated
			return nop;
		case OP_VER: // Function definition
			// NOTE: OP_VER "f₀"
			continue; // WARNING
		case OP_IF:
		case OP_NOTIF:
		{
			assert (ap >= 1);
			uint16_t __ap, __ap⁻¹;
			uint16_t __stack [1000] = { [0 ... 999] = nop };
			// Save condition
			uint16_t x₀ = stack [ap - 1];
			move (& nop, & stack [-- ap]);
			// Fork stack
			for (uint16_t ap⁺ = 0; ap⁺ < ap; ++ ap⁺) move (& stack [ap⁺], & __stack [ap⁺]);
			for (uint16_t ap = 999; ap > ap⁻¹; -- ap) move (& stack [ap], & __stack [ap]);
			// Recurse scope
			__ap = ap, __ap⁻¹ = ap⁻¹;
			uint8_t __op = preprocess ( );
			if (__op == OP_ELSE)
			{
				// Swap stack
				swap (& __ap, & ap);
				swap (& __ap⁻¹, & ap⁻¹);
				for (uint16_t ap⁺ = 0; ap⁺ < max (__ap, ap); ++ ap⁺) swap (& stack [ap⁺], & __stack [ap⁺]);
				for (uint16_t ap = 999; ap > min (__ap⁻¹, ap⁻¹); -- ap) swap (& stack [ap], & __stack [ap]);
				// Recurse scope
				__op = preprocess ( );
				// Swap stack
				swap (& __ap, & ap);
				swap (& __ap⁻¹, & ap⁻¹);
				for (uint16_t ap⁺ = 0; ap⁺ < max (__ap, ap); ++ ap⁺) swap (& stack [ap⁺], & __stack [ap⁺]);
				for (uint16_t ap = 999; ap > min (__ap⁻¹, ap⁻¹); -- ap) swap (& stack [ap], & __stack [ap]);
			}
			assert (__op == OP_ENDIF);
			assert (__ap == ap && __ap⁻¹ == ap⁻¹);
			// Merge stack
			for (uint16_t ap⁺ = 0; ap⁺ < ap; ++ ap⁺)
			{
				uint16_t x₁ = stack [ap⁺];
				uint16_t x₂ = __stack [ap⁺];
				if (x₁ == x₂) continue;
				if (op == OP_NOTIF) swap (& x₁, & x₂);
				trace [öp].code = OP_IF;
				trace [öp].x₀ = x₀;
				trace [öp].x₁ = x₁;
				trace [öp].x₂ = x₂;
				move (& öp, & stack [ap⁺]), ++ öp;
			}
			// Merge altstack
			for (uint16_t ap = 999; ap > ap⁻¹; -- ap)
			{
				uint16_t x₁ = stack [ap];
				uint16_t x₂ = __stack [ap];
				if (x₁ == x₂) continue;
				if (op == OP_NOTIF) swap (& x₁, & x₂);
				trace [öp].code = OP_IF;
				trace [öp].x₀ = x₀;
				trace [öp].x₁ = x₁;
				trace [öp].x₂ = x₂;
				move (& öp, & stack [ap]), ++ öp;
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
			assert (ap >= 1);
			move (& stack [ap - 1], & stack [ap⁻¹ --]);
			move (& nop, & stack [-- ap]);
			continue;
		case OP_FROMALTSTACK:
			assert (ap⁻¹ < 999);
			move (& stack [++ ap⁻¹], & stack [ap ++]);
			move (& nop, & stack [ap⁻¹ + 0]);
			continue;
		case OP_2DROP:
			assert (ap >= 2);
			move (& nop, & stack [-- ap]);
			move (& nop, & stack [-- ap]);
			continue;
		case OP_2DUP:
			assert (ap >= 2 && ap - 2 < ap⁻¹);
			move (& stack [ap - 2], & stack [ap]), ++ ap;
			move (& stack [ap - 2], & stack [ap]), ++ ap;
			continue;
		case OP_3DUP:
			assert (ap >= 3 && ap - 3 < ap⁻¹);
			move (& stack [ap - 3], & stack [ap]), ++ ap;
			move (& stack [ap - 3], & stack [ap]), ++ ap;
			move (& stack [ap - 3], & stack [ap]), ++ ap;
			continue;
		case OP_2OVER:
			assert (ap >= 4 && ap - 2 < ap⁻¹);
			move (& stack [ap - 4], & stack [ap]), ++ ap;
			move (& stack [ap - 4], & stack [ap]), ++ ap;
			continue;
		case OP_2ROT:
			assert (ap >= 6 && ap - 2 < ap⁻¹);
			swap (& stack [ap - 6], & stack [ap - 4]);
			swap (& stack [ap - 5], & stack [ap - 3]);
			swap (& stack [ap - 4], & stack [ap - 2]);
			swap (& stack [ap - 3], & stack [ap - 1]);
			continue;
		case OP_2SWAP:
			assert (ap >= 4 && ap - 2 < ap⁻¹);
			swap (& stack [ap - 4], & stack [ap - 2]);
			swap (& stack [ap - 3], & stack [ap - 1]);
			continue;
		// OP_IFDUP
		case OP_DEPTH:
			assert (öp <= öp⁻¹);
			trace [öp].code = ap ? OP_RESERVED + ap : OP_0;
			trace [öp].num = ap;
			move (& öp, & stack [ap ++]), ++ öp;
			continue;
		case OP_DROP:
			assert (ap >= 1);
			move (& nop, & stack [-- ap]);
			continue;
		case OP_DUP:
			assert (ap >= 1 && ap - 1 < ap⁻¹);
			move (& stack [ap - 1], & stack [ap + 0]), ++ ap;
			continue;
		case OP_NIP:
			assert (ap >= 2);
			move (& stack [ap - 1], & stack [ap - 2]);
			stack [-- ap] = nop;
			continue;
		case OP_OVER:
			assert (ap >= 2 && ap - 1 < ap⁻¹);
			move (& stack [ap - 2], & stack [ap + 0]), ++ ap;
			continue;
		case OP_PICK:
			assert (ap + 1 > trace [stack [ap - 1]].num + 1);
			move (& stack [ap - 1 - trace [stack [ap - 1]].num - 1], & stack [ap - 1]);
			continue;
		case OP_ROLL:
			assert (ap + 1 > trace [stack [ap - 1]].num + 1);
			for (uint16_t Δap = trace [stack [-- ap]].num; Δap != 0; -- Δap) swap (& stack [ap - Δap - 1], & stack [ap - Δap + 0]);			
			continue;
		case OP_ROT:
			assert (ap >= 3);
			swap (& stack [ap - 3], & stack [ap - 2]);
			swap (& stack [ap - 2], & stack [ap - 1]);
			continue;
		case OP_SWAP:
			assert (ap >= 2);
			swap (& stack [ap - 2], & stack [ap - 1]);
			continue;
		case OP_TUCK:
			assert (ap >= 2 && ap - 1 < ap⁻¹);
			swap (& stack [ap - 2], & stack [ap - 1]);
			move (& stack [ap - 2], & stack [ap + 0]), ++ ap;
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
			assert (ap >= 1);
			assert (öp <= öp⁻¹);
			trace [öp].code = op;
			trace [öp].x₀ = stack [ap - 1];
			move (& öp, & stack [ap - 1]), ++ öp;
			continue;
		case OP_ADD:
			assert (ap >= 2);
			assert (öp <= öp⁻¹);
			if (stack [ap - 1] == stack [ap - 2]) // OP_ADD → OP_2MUL
			{
				trace [öp].code = OP_2MUL;
				trace [öp].x₀ = stack [ap - 1];
				move (& nop, & stack [-- ap]);
				move (& öp, & stack [ap - 1]), ++ öp;
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
			assert (ap >= 2);
			assert (öp <= öp⁻¹);
			assert (stack [ap - 1] != stack [ap - 2]);
			trace [öp].code = op;
			trace [öp].x₀ = stack [ap - 2];
			trace [öp].x₁ = stack [ap - 1];
			move (& nop, & stack [-- ap]);
			move (& öp, & stack [ap - 1]), ++ öp;
			continue;
		case OP_WITHIN:
			assert (ap >= 3);
			assert (öp <= öp⁻¹);
			trace [öp].code = OP_WITHIN;
			trace [öp].x₂ = stack [-- ap];
			trace [öp].x₁ = stack [-- ap];
			trace [öp].x₀ = stack [ap - 1];
			assert (trace [öp].x₁ != trace [öp].x₂);
			move (& öp, & stack [ap - 1]), ++ öp;
			move (& nop, & stack [ap + 0]);
			move (& nop, & stack [ap + 1]);
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
	return op;
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
			if (trace [x].reference ++) return;
			attach (trace [x].x₀);
			attach (trace [x].x₁);
			attach (trace [x].x₂);
			return;
		// OP_NOTIF
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
uint16_t reference⁻¹ = nop;
// Count xᵢ in expression tree
uint8_t count⁺ (uint16_t xᵢ, uint16_t x₀)
{
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
			return (x₀ == xᵢ) ? 1 : count⁺ (xᵢ, trace [x₀].x₀) + count⁺ (xᵢ, trace [x₀].x₁) + count⁺ (xᵢ, trace [x₀].x₂);
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
			return (x₀ == xᵢ) ? 1 : count⁺ (xᵢ, trace [x₀].x₀);
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
			return (x₀ == xᵢ) ? 1 : count⁺ (xᵢ, trace [x₀].x₀) + count⁺ (xᵢ, trace [x₀].x₁);
		case OP_WITHIN:
			return (x₀ == xᵢ) ? 1 : count⁺ (xᵢ, trace [x₀].x₀) + count⁺ (xᵢ, trace [x₀].x₁) + count⁺ (xᵢ, trace [x₀].x₂);
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
	assert (ap >= 1);
	uint16_t apₓ = find⁻¹ (x, stack, ap);
	uint16_t Δap = ap - apₓ - 1;
	assert (apₓ < 1000);
	uint8_t op = nop;
	uint8_t dup = trace [x].reference > count⁺ (x, reference⁻¹) && count (x, stack, ap) == 1;
	// case 0b10000000000000000:
	if (Δap == 0 && dup != 0)
	{
		swap (& stack [ap - 2], & stack [ap - 1]);
		move (& stack [ap - 2], & stack [ap + 0]), ++ ap;
		op = OP_TUCK, fwrite (& op, 1, 1, stdout);
		dup = 0;
	}
	// case 0b01000000000000000:
	if (Δap == 1 && dup == 0)
	{
		swap (& stack [ap - 2], & stack [ap - 1]);
		op = OP_SWAP, fwrite (& op, 1, 1, stdout), Δap = 0;
	}
	if (Δap == 1 && dup != 0)
	{
		move (& stack [ap - 2], & stack [ap + 0]), ++ ap;
		op = OP_OVER, fwrite (& op, 1, 1, stdout), Δap = 0;
		dup = 0;
	}
	// case 0b00100000000000000:
	if (! dup && Δap == 2)
	{
		swap (& stack [ap - 3], & stack [ap - 2]);
		swap (& stack [ap - 2], & stack [ap - 1]);
		op = OP_ROT, fwrite (& op, 1, 1, stdout), Δap = 0;
	}
	// default:
	if (Δap == 0) return;
	if (Δap <= 16)
	{
		op = OP_RESERVED + Δap, fwrite (& op, 1, 1, stdout);
	}
	if (Δap > 16)
	{
		uint8_t n = 4 - lzcnt (Δap) / 8;
		fwrite (& n, 1, 1, stdout);
		fwrite (& Δap, 1, n, stdout);
	}
	if (dup == 0)
	{
		for (uint16_t Δ = Δap; Δ != 0; -- Δ)
		{
			swap (& stack [ap - Δ - 1], & stack [ap - Δ + 0]);	
		}		
		op = OP_ROLL, fwrite (& op, 1, 1, stdout), Δap = 0;
	}
	if (dup != 0)
	{
		move (& stack [ap - Δap - 1], & stack [ap + 0]), ++ ap;
		op = OP_PICK, fwrite (& op, 1, 1, stdout), Δap = 0;
		dup = 0;
	}
	assert (stack [ap - 1] == x);
	return;
}
// Permute stack elements
void translate² (uint16_t x₀, uint16_t x₁, workflow s)
{
	assert (ap >= 2);
	uint16_t ap₀ = find⁻¹ (x₀, stack, ap);  assert (ap₀ < 1000);
	uint16_t ap₁ = find⁻¹ (x₁, stack, ap);  assert (ap₁ < 1000);
	uint16_t xˡʰˢ = stack [min (ap₀, ap₁)];
	uint16_t xʳʰˢ = stack [max (ap₀, ap₁)];
	uint16_t xₙ [ ] = {xˡʰˢ, xʳʰˢ};
	uint8_t op = nop;
	uint16_t dupˡʰˢ = trace [xˡʰˢ].reference > count⁺ (xˡʰˢ, reference⁻¹) && count (xˡʰˢ, stack, ap) == 1;
	uint16_t dupʳʰˢ = trace [xʳʰˢ].reference > count⁺ (xʳʰˢ, reference⁻¹) && count (xʳʰˢ, stack, ap) == 1;
	switch (check⁻¹ (& stack [max (ap, 17) - 17], min (ap, 17), xₙ, 2) << (17 - min (ap, 17)))
	{
		case 0b00001100000000000: // 0x01800
			swap (& stack [ap - 6], & stack [ap - 4]);
			swap (& stack [ap - 5], & stack [ap - 3]);
			swap (& stack [ap - 4], & stack [ap - 2]);
			swap (& stack [ap - 3], & stack [ap - 1]);
			op = OP_2ROT, fwrite (& op, 1, 1, stdout);
			return translate² (x₀, x₁, s);
		case 0b00110000000000000: // 0x06000
			if (dupˡʰˢ && dupʳʰˢ)
			{
				move (& stack [ap - 4], & stack [ap]), ++ ap;
				move (& stack [ap - 4], & stack [ap]), ++ ap;
				op = OP_2OVER, fwrite (& op, 1, 1, stdout);
			}
			else
			{
				swap (& stack [ap - 4], & stack [ap - 2]);
				swap (& stack [ap - 3], & stack [ap - 1]);
				op = OP_2SWAP, fwrite (& op, 1, 1, stdout);
			}
			return translate² (x₀, x₁, s);
		case 0b01100000000000000: // 0x0C000
			if (dupˡʰˢ != dupʳʰˢ)
			{
				translate¹ (x₀);
				translate¹ (x₁);
				return;
			}
			if (x₀ == xˡʰˢ)
			{
				swap (& stack [ap - 3], & stack [ap - 2]);
				swap (& stack [ap - 2], & stack [ap - 1]);
				swap (& xˡʰˢ, & xʳʰˢ), swap (& dupˡʰˢ, & dupʳʰˢ);
				op = OP_ROT, fwrite (& op, 1, 1, stdout);
			}
			else // x₀ == xʳʰˢ
			{
				swap (& stack [ap - 2], & stack [ap - 1]);
				op = OP_SWAP, fwrite (& op, 1, 1, stdout);
			}
		case 0b10100000000000000: // 0x14000
			if (dupˡʰˢ != dupʳʰˢ)
			{
				translate¹ (x₀);
				translate¹ (x₁);
				return;
			}
			swap (& stack [ap - 3], & stack [ap - 2]);
			swap (& stack [ap - 2], & stack [ap - 1]);
			swap (& xˡʰˢ, & xʳʰˢ), swap (& dupˡʰˢ, & dupʳʰˢ);
			op = OP_ROT, fwrite (& op, 1, 1, stdout);
		case 0b11000000000000000: // 0x18000
			if (dupˡʰˢ && dupʳʰˢ)
			{
				move (& stack [ap - 2], & stack [ap]), ++ ap;
				move (& stack [ap - 2], & stack [ap]), ++ ap;
				op = OP_2DUP, fwrite (& op, 1, 1, stdout);
			}
			if (dupˡʰˢ != dupʳʰˢ)
			{
				if (dupˡʰˢ != 0)
				{
					move (& stack [ap - 2], & stack [ap + 0]), ++ ap;
					op = OP_OVER, fwrite (& op, 1, 1, stdout);
				}
				if (dupʳʰˢ != 0)
				{
					swap (& stack [ap - 2], & stack [ap - 1]);
					move (& stack [ap - 2], & stack [ap + 0]), ++ ap;
					op = OP_TUCK, fwrite (& op, 1, 1, stdout);
				}
			}
			if (s == STRICT && stack [ap - 1] == x₀)
			{
				swap (& stack [ap - 2], & stack [ap - 1]);
				op = OP_SWAP, fwrite (& op, 1, 1, stdout);
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
	assert (ap >= 3);
	uint16_t ap₀ = find⁻¹ (x₀, stack, ap);  assert (ap₀ < 1000);
	uint16_t ap₁ = find⁻¹ (x₁, stack, ap);  assert (ap₁ < 1000);
	uint16_t ap₂ = find⁻¹ (x₂, stack, ap);  assert (ap₂ < 1000);
	uint16_t xˡʰˢ = stack [min (min (ap₀, ap₁), ap₂)];
	uint16_t xᵐⁱᵈ;
	uint16_t xʳʰˢ = stack [max (max (ap₀, ap₁), ap₂)];
	if (x₀ != xˡʰˢ && x₀ != xʳʰˢ) xᵐⁱᵈ = x₀;
	if (x₁ != xˡʰˢ && x₁ != xʳʰˢ) xᵐⁱᵈ = x₁;
	if (x₂ != xˡʰˢ && x₂ != xʳʰˢ) xᵐⁱᵈ = x₂;
	uint16_t xₙ [ ] = {xˡʰˢ, xᵐⁱᵈ, xʳʰˢ};
	uint8_t op = nop;
	uint16_t dupˡʰˢ = trace [xˡʰˢ].reference > count⁺ (xˡʰˢ, reference⁻¹) && count (xˡʰˢ, stack, ap) == 1;
	uint16_t dupᵐⁱᵈ = trace [xᵐⁱᵈ].reference > count⁺ (xᵐⁱᵈ, reference⁻¹) && count (xᵐⁱᵈ, stack, ap) == 1;
	uint16_t dupʳʰˢ = trace [xʳʰˢ].reference > count⁺ (xʳʰˢ, reference⁻¹) && count (xʳʰˢ, stack, ap) == 1;
	switch (check⁻¹ (& stack [max (ap, 17) - 17], min (ap, 17), xₙ, 3) << (17 - min (ap, 17)) & 0b11100000000000000)
	{
		case 0b11100000000000000: // 0x1C000
			if (dupˡʰˢ && dupᵐⁱᵈ && dupʳʰˢ)
			{
				move (& stack [ap - 3], & stack [ap]), ++ ap;
				move (& stack [ap - 3], & stack [ap]), ++ ap;
				move (& stack [ap - 3], & stack [ap]), ++ ap;
				op = OP_3DUP, fwrite (& op, 1, 1, stdout);
				dupˡʰˢ = dupᵐⁱᵈ = dupʳʰˢ = 0;
			}
			if (dupᵐⁱᵈ && dupʳʰˢ)
			{
				move (& stack [ap - 2], & stack [ap]), ++ ap;
				move (& stack [ap - 2], & stack [ap]), ++ ap;
				op = OP_2DUP, fwrite (& op, 1, 1, stdout);
				swap (& stack [ap - 5], & stack [ap - 4]);
				swap (& stack [ap - 4], & stack [ap - 3]);
				swap (& stack [ap - 3], & stack [ap - 2]);
				swap (& stack [ap - 2], & stack [ap - 1]);
				swap (& xˡʰˢ, & xᵐⁱᵈ), swap (& xᵐⁱᵈ, & xʳʰˢ);
				op = OP_4, fwrite (& op, 1, 1, stdout);
				op = OP_ROLL, fwrite (& op, 1, 1, stdout);
				dupᵐⁱᵈ = dupʳʰˢ = 0;
			}
			if (dupᵐⁱᵈ != 0)
			{
				move (& stack [ap - 2], & stack [ap + 0]), ++ ap;
				swap (& xᵐⁱᵈ, & xʳʰˢ);
				op = OP_OVER, fwrite (& op, 1, 1, stdout);
				dupᵐⁱᵈ = 0;
			}
			if (dupʳʰˢ != 0)
			{
				swap (& stack [ap - 2], & stack [ap - 1]);
				move (& stack [ap - 2], & stack [ap + 0]), ++ ap;
				op = OP_TUCK, fwrite (& op, 1, 1, stdout);
				dupʳʰˢ = 0;
			}
			if (dupᵐⁱᵈ != dupʳʰˢ)
			{
				swap (& stack [ap - 4], & stack [ap - 3]);
				swap (& stack [ap - 3], & stack [ap - 2]);
				swap (& stack [ap - 2], & stack [ap - 1]);
				swap (& xˡʰˢ, & xᵐⁱᵈ), swap (& xᵐⁱᵈ, & xʳʰˢ);
				op = OP_3, fwrite (& op, 1, 1, stdout);
				op = OP_ROLL, fwrite (& op, 1, 1, stdout);
			}
			if (s == LEEWAY) return;
			if (x₂ == xˡʰˢ && x₀ == xʳʰˢ)
			{
				swap (& stack [ap - 2], & stack [ap - 1]);
				swap (& xᵐⁱᵈ, & xʳʰˢ);
				op = OP_SWAP, fwrite (& op, 1, 1, stdout);
			}
			if (x₂ == xˡʰˢ && x₁ == xʳʰˢ)
			{
				swap (& stack [ap - 3], & stack [ap - 2]);
				swap (& stack [ap - 2], & stack [ap - 1]);
				swap (& xˡʰˢ, & xᵐⁱᵈ);
				swap (& xᵐⁱᵈ, & xʳʰˢ);
				op = OP_ROT, fwrite (& op, 1, 1, stdout);
			}
			if (x₂ == xʳʰˢ) return;
			swap (& stack [ap - 2], & stack [ap - 1]);
			op = OP_SWAP, fwrite (& op, 1, 1, stdout);
			return;
		case 0b01100000000000000: // 0x0C000
		case 0b10100000000000000: // 0x14000
		case 0b11000000000000000: // 0x18000
			translate² (xᵐⁱᵈ, xʳʰˢ, LEEWAY);
			translate¹ (xˡʰˢ);
			return translate³ (x₀, x₁, x₂, s);
		default:
			translate¹ (xʳʰˢ);
			translate¹ (xᵐⁱᵈ);
			translate¹ (xˡʰˢ);
			return translate³ (x₀, x₁, x₂, s);
	}
}
// Permute stack elements
uint16_t translate (const uint16_t xₙ [ ], uint8_t n, workflow s)
{
	uint16_t xᵢ;
	uint16_t x₀, x₁, x₂;
	switch (n)
	{
		case 1:
			x₀ = xₙ [0];
			if (trace [x₀].reference != 0) -- trace [x₀].reference;
			translate¹ (x₀);
			assert (ap >= 1);
			assert (stack [ap - 1] == x₀), move (& nop, & stack [-- ap]);
			return x₀;
		case 2:
			x₀ = xₙ [0];
			x₁ = xₙ [1];
			if (trace [x₀].reference != 0) -- trace [x₀].reference;
			if (trace [x₁].reference != 0) -- trace [x₁].reference;
			translate² (x₀, x₁, s);
			assert (ap >= 2);
			if (s == STRICT)
			{
				assert (stack [ap - 1] == x₁), move (& nop, & stack [-- ap]);
				assert (stack [ap - 1] == x₀), move (& nop, & stack [-- ap]);
				return x₁;
			}
			xᵢ = stack [ap - 1];
			assert (stack [ap - 1] == x₀ || stack [ap - 1] == x₁), move (& nop, & stack [-- ap]);
			assert (stack [ap - 1] == x₀ || stack [ap - 1] == x₁), move (& nop, & stack [-- ap]);
			return xᵢ;
		case 3:
			x₀ = xₙ [0];
			x₁ = xₙ [1];
			x₂ = xₙ [2];
			if (trace [x₀].reference != 0) -- trace [x₀].reference;
			if (trace [x₁].reference != 0) -- trace [x₁].reference;
			if (trace [x₂].reference != 0) -- trace [x₂].reference;
			translate³ (x₀, x₁, x₂, s);
			assert (ap >= 3);
			if (s == STRICT)
			{
				assert (stack [ap - 1] == x₂), move (& nop, & stack [-- ap]);
				assert (stack [ap - 1] == x₁), move (& nop, & stack [-- ap]);
					assert (stack [ap - 1] == x₀), move (& nop, & stack [-- ap]);
				return x₂;
			}
			xᵢ = stack [ap - 1];
			assert (stack [ap - 1] == x₀ || stack [ap - 1] == x₁ || stack [ap - 1] == x₂), move (& nop, & stack [-- ap]);
			assert (stack [ap - 1] == x₀ || stack [ap - 1] == x₁ || stack [ap - 1] == x₂), move (& nop, & stack [-- ap]);
			assert (stack [ap - 1] == x₀ || stack [ap - 1] == x₁ || stack [ap - 1] == x₂), move (& nop, & stack [-- ap]);
			return xᵢ;
		default: // WARNING
			return nop;
	}
}
// Serialize unused operation
void serialize⁻ (uint16_t x)
{
	uint8_t op = nop;
	uint16_t apₓ = find⁻¹ (x, stack, ap);
	if (apₓ == 0x8000) switch (trace [x].code)
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
	uint16_t Δap = ap - apₓ - 1;
	if (trace [x].reference < count⁺ (x, reference⁻¹) && count (x, stack, ap) == 1) switch (Δap)
	{
		case 0:
			stack [-- ap] = nop;
			op = OP_DROP; fwrite (& op, 1, 1, stdout);
			return;
		case 1:
			swap (& stack [ap - 2], & stack [ap - 1]);
			move (& nop, & stack [-- ap]);
			op = OP_NIP; fwrite (& op, 1, 1, stdout);
			return;
		case 2:
			swap (& stack [ap - 3], & stack [ap - 2]);
			swap (& stack [ap - 2], & stack [ap - 1]);
			op = OP_ROT; fwrite (& op, 1, 1, stdout);
			move (& nop, & stack [-- ap]);
			op = OP_DROP; fwrite (& op, 1, 1, stdout);
			return;
		default:
			if (Δap <= 16)
			{
				op = OP_RESERVED + Δap, fwrite (& op, 1, 1, stdout);
			}
			if (Δap > 16)
			{
				uint8_t n = 4 - lzcnt (Δap) / 8;
				fwrite (& n, 1, 1, stdout);
				fwrite (& Δap, 1, n, stdout);
			}
			for (uint16_t Δ = Δap; Δ != 0; -- Δ)
			{
				swap (& stack [ap - Δ - 1], & stack [ap - Δ + 0]);	
			}
			op = OP_ROLL; fwrite (& op, 1, 1, stdout);
			move (& nop, & stack [-- ap]);
			op = OP_DROP; fwrite (& op, 1, 1, stdout);
			return;
	}
}
// Flush Bitcoin script
void serialize⁺ (uint16_t x)
{
	uint8_t op = nop;
	// Compute x₀
	switch (op = trace [x].code)
	{
		case OP_0:
			assert (trace [x].reference == 0);
			move (& x, & stack [ap ++]);
			fwrite (& op, 1, 1, stdout);
			break;
		case 1:
		case 2:
		case 3:
		case 4:
			assert (trace [x].reference != 0);
			if (find⁻¹ (x, stack, ap) < 1000) break;
			assert (trace [x].num > 16 || trace [x].num <= -1);
			assert (trace [x].num < +2147483648); // x₀ < +2³¹
			assert (trace [x].num > -2147483648); // x₀ > -2³¹
			assert (stack [ap] == nop);
			if (trace [x].num <= 16)
			{
				if (trace [x].num == 0) op = OP_0;
				else op = OP_RESERVED + trace [x].num;
				fwrite (& op, 1, 1, stdout);
			}
			else
			{
				uint8_t n = 4 - lzcnt (trace [x].num) / 8;
				fwrite (& n, 1, 1, stdout);
				fwrite (& trace [x].num, 1, n, stdout);
			}
			move (& x, & stack [ap ++]);
			break;
		// ⋯
		// OP_PUSHDATA1
		// OP_PUSHDATA2
		// OP_PUSHDATA4
		// OP_1NEGATE
		case OP_RESERVED:
			assert (trace [x].reference != 0);
			assert (find⁻¹ (x, stack, ap) != 0x8000);
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
			if (trace [x].num <= 16)
			{
				if (trace [x].num == 0) op = OP_0;
				else op = OP_RESERVED + trace [x].num;
				fwrite (& op, 1, 1, stdout);
			}
			else
			{
				uint8_t n = 4 - lzcnt (trace [x].num) / 8;
				fwrite (& n, 1, 1, stdout);
				fwrite (& trace [x].num, 1, n, stdout);
			}
			move (& x, & stack [ap ++]);
			break;
		case OP_NOP:
			fwrite (& op, 1, 1, stdout);
			break;
		// OP_VER
		case OP_IF:
			if (find⁻¹ (x, stack, ap) < 1000) break;
			// if (trace [trace [x].x₂].reference >= 2) serialize⁺ (trace [x].x₂);
			// if (trace [trace [x].x₁].reference >= 2) serialize⁺ (trace [x].x₁);
			assert (find⁻¹ (trace [x].x₀, stack, ap) != 0x8000);
			uint16_t ap₁ = find⁻¹ (trace [x].x₁, stack, ap);
			uint16_t ap₂ = find⁻¹ (trace [x].x₂, stack, ap);
			// if (ap₁ != 0x8000 && trace [trace [x].x₁].reference - 1 == count⁺ (trace [x].x₁, reference⁻¹)) translate¹ (trace [x].x₁);
			// if (ap₂ != 0x8000 && trace [trace [x].x₂].reference - 1 == count⁺ (trace [x].x₂, reference⁻¹)) translate¹ (trace [x].x₂);
			translate (& trace [x].x₀, 1, STRICT), op = OP_IF, fwrite (& op, 1, 1, stdout);
			uint16_t __ap, __ap⁻¹;
			uint16_t __stack [1000] = { [0 ... 999] = nop };
			// Fork stack
			for (uint16_t ap⁺ = 0; ap⁺ < ap; ++ ap⁺) move (& stack [ap⁺], & __stack [ap⁺]);
			for (uint16_t ap = 999; ap > ap⁻¹; -- ap) move (& stack [ap], & __stack [ap]);
			__ap = ap, __ap⁻¹ = ap⁻¹;
			reference⁻¹ = trace [x].x₂;
			if (ap₁ == 0x8000) serialize⁺ (trace [x].x₁);
			translate (& trace [x].x₁, 1, STRICT);
			move (& x, & stack [ap ++]);
			serialize⁻ (trace [x].x₂);
			op = OP_ELSE, fwrite (& op, 1, 1, stdout);
			// Swap stack
			swap (& __ap, & ap);
			swap (& __ap⁻¹, & ap⁻¹);
			for (uint16_t ap⁺ = 0; ap⁺ < max (__ap, ap); ++ ap⁺) swap (& stack [ap⁺], & __stack [ap⁺]);
			for (uint16_t ap = 999; ap > min (__ap⁻¹, ap⁻¹); -- ap) swap (& stack [ap], & __stack [ap]);
			reference⁻¹ = trace [x].x₁;
			if (ap₂ == 0x8000) serialize⁺ (trace [x].x₂);
			translate (& trace [x].x₂, 1, STRICT);
			move (& x, & stack [ap ++]);
			serialize⁻ (trace [x].x₁);
			op = OP_ENDIF, fwrite (& op, 1, 1, stdout);
			reference⁻¹ = nop;
			break;
		// OP_NOTIF
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
			if (find⁻¹ (x, stack, ap) < 1000) break;
			if (find⁻¹ (trace [x].x₀, stack, ap) == 0x8000) serialize⁺ (trace [x].x₀);
			assert (trace [x].reference != 0), translate (trace [x].xₙ, 1, STRICT);
			move (& x, & stack [ap ++]), fwrite (& op, 1, 1, stdout);
			break;
		case OP_2MUL:
			if (find⁻¹ (x, stack, ap) < 1000) break;
			if (find⁻¹ (trace [x].x₀, stack, ap) == 0x8000) serialize⁺ (trace [x].x₀);
			assert (trace [x].reference != 0), translate (trace [x].xₙ, 1, STRICT);
			op = OP_DUP, fwrite (& op, 1, 1, stdout);
			op = OP_ADD, fwrite (& op, 1, 1, stdout), move (& x, & stack [ap ++]);
			break;
		case OP_2DIV:
		case OP_NEGATE:
		case OP_ABS:
		case OP_NOT:
		case OP_0NOTEQUAL:
			if (find⁻¹ (x, stack, ap) < 1000) break;
			if (find⁻¹ (trace [x].x₀, stack, ap) == 0x8000) serialize⁺ (trace [x].x₀);
			assert (trace [x].reference != 0), translate (trace [x].xₙ, 1, STRICT);
			fwrite (& op, 1, 1, stdout), move (& x, & stack [ap ++]);
			break;
		case OP_ADD:
			if (find⁻¹ (x, stack, ap) < 1000) break;
			if (find⁻¹ (trace [x].x₀, stack, ap) == 0x8000) serialize⁺ (trace [x].x₀);
			if (find⁻¹ (trace [x].x₁, stack, ap) == 0x8000) serialize⁺ (trace [x].x₁);
			assert (trace [x].reference != 0), translate (trace [x].xₙ, 2, LEEWAY);
			move (& x, & stack [ap ++]), fwrite (& op, 1, 1, stdout);
			break;
		case OP_SUB:
			if (find⁻¹ (x, stack, ap) < 1000) break;
			if (find⁻¹ (trace [x].x₀, stack, ap) == 0x8000) serialize⁺ (trace [x].x₀);
			if (find⁻¹ (trace [x].x₁, stack, ap) == 0x8000) serialize⁺ (trace [x].x₁);
			assert (trace [x].reference != 0), translate (trace [x].xₙ, 2, STRICT);
			move (& x, & stack [ap ++]), fwrite (& op, 1, 1, stdout);
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
			if (find⁻¹ (x, stack, ap) < 1000) break;
			if (find⁻¹ (trace [x].x₀, stack, ap) == 0x8000) serialize⁺ (trace [x].x₀);
			if (find⁻¹ (trace [x].x₁, stack, ap) == 0x8000) serialize⁺ (trace [x].x₁);
			assert (find⁻¹ (trace [x].x₀, stack, ap) != 0x8000);
			assert (find⁻¹ (trace [x].x₁, stack, ap) != 0x8000);
			assert (trace [x].reference != 0), translate (trace [x].xₙ, 2, LEEWAY);
			move (& x, & stack [ap ++]), fwrite (& op, 1, 1, stdout);
			break;
		case OP_LESSTHAN:
		case OP_GREATERTHAN:
		case OP_LESSTHANOREQUAL:
		case OP_GREATERTHANOREQUAL:
			if (find⁻¹ (x, stack, ap) < 1000) break;
			if (find⁻¹ (trace [x].x₀, stack, ap) == 0x8000) serialize⁺ (trace [x].x₀);
			if (find⁻¹ (trace [x].x₁, stack, ap) == 0x8000) serialize⁺ (trace [x].x₁);
			assert (find⁻¹ (trace [x].x₀, stack, ap) != 0x8000);
			assert (find⁻¹ (trace [x].x₁, stack, ap) != 0x8000);
			assert (trace [x].reference != 0);
			if (translate (trace [x].xₙ, 2, LEEWAY) == trace [x].x₀) switch (trace [x].code)
			{
				case OP_LESSTHAN: op = OP_GREATERTHANOREQUAL; break;
				case OP_GREATERTHAN: op = OP_LESSTHANOREQUAL; break;
				case OP_LESSTHANOREQUAL: op = OP_GREATERTHAN; break;
				case OP_GREATERTHANOREQUAL: op = OP_LESSTHAN; break;
				default: break; // WARNING
			}
			move (& x, & stack [ap ++]), fwrite (& op, 1, 1, stdout);
			break;
		case OP_MIN:
		case OP_MAX:
			if (find⁻¹ (x, stack, ap) < 1000) break;
			if (find⁻¹ (trace [x].x₀, stack, ap) == 0x8000) serialize⁺ (trace [x].x₀);
			if (find⁻¹ (trace [x].x₁, stack, ap) == 0x8000) serialize⁺ (trace [x].x₁);
			assert (find⁻¹ (trace [x].x₀, stack, ap) != 0x8000);
			assert (find⁻¹ (trace [x].x₁, stack, ap) != 0x8000);
			assert (trace [x].reference != 0), translate (trace [x].xₙ, 2, LEEWAY);
			move (& x, & stack [ap ++]), fwrite (& op, 1, 1, stdout);
			break;
		case OP_WITHIN:
			if (find⁻¹ (x, stack, ap) < 1000) break;
			if (find⁻¹ (trace [x].x₀, stack, ap) == 0x8000) serialize⁺ (trace [x].x₀);
			if (find⁻¹ (trace [x].x₁, stack, ap) == 0x8000) serialize⁺ (trace [x].x₁);
			if (find⁻¹ (trace [x].x₂, stack, ap) == 0x8000) serialize⁺ (trace [x].x₂);
			assert (find⁻¹ (trace [x].x₀, stack, ap) != 0x8000);
			assert (find⁻¹ (trace [x].x₁, stack, ap) != 0x8000);
			assert (find⁻¹ (trace [x].x₂, stack, ap) != 0x8000);
			assert (trace [x].reference != 0), translate (trace [x].xₙ, 3, STRICT);
			move (& x, & stack [ap ++]), fwrite (& op, 1, 1, stdout);
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
void serialize⁰ (uint16_t x)
{
	if (find⁻¹ (x, stack, ap) != 0x8000) return;
	uint8_t op = nop;
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
			if (trace [x].reference >= 2 && find⁻¹ (x, stack, ap) == 0x8000) serialize⁺ (x);
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
			assert (find⁻¹ (x, stack, ap) != 0x8000);
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
			assert (trace [x].reference == 0);
			return;
		// OP_NOP
		// OP_VER
		case OP_IF:
		case OP_NOTIF:
			assert (trace [x].reference >= 1);
			serialize⁰ (trace [x].x₀);
			serialize⁰ (trace [x].x₁);
			serialize⁰ (trace [x].x₂);
			serialize⁺ (trace [x].x₀);
			if (trace [x].reference >= 2 && find⁻¹ (x, stack, ap) == 0x8000) serialize⁺ (x);
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
			serialize⁰ (trace [x].x₀);
			serialize⁺ (trace [x].x₀);
			if (trace [x].reference >= 2 && find⁻¹ (x, stack, ap) == 0x8000) serialize⁺ (x);
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
			serialize⁰ (trace [x].x₀);
			serialize⁺ (trace [x].x₀);
			serialize⁰ (trace [x].x₁);
			serialize⁺ (trace [x].x₁);
			if (trace [x].reference >= 2 && find⁻¹ (x, stack, ap) == 0x8000) serialize⁺ (x);
			return;
		case OP_WITHIN:
			assert (trace [x].reference >= 1);
			serialize⁰ (trace [x].x₀);
			serialize⁺ (trace [x].x₀);
			serialize⁰ (trace [x].x₁);
			serialize⁺ (trace [x].x₁);
			serialize⁰ (trace [x].x₂);
			serialize⁺ (trace [x].x₂);
			if (trace [x].reference >= 2 && find⁻¹ (x, stack, ap) == 0x8000) serialize⁺ (x);
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
void serialize (const uint16_t xₙ [ ], uint8_t n, workflow s)
{
	// Compute x₀ ⋯ xₙ₋₁
	for (uint8_t i = 0; i < n; ++ i)
	{
		serialize⁰ (xₙ [i]);
		serialize⁺ (xₙ [i]);
	}
	if (ap != n) fprintf (stderr, "Assertion failed: ap %s %hu\n", ap < n ? "≥" : "≤", n);
	for (const uint16_t * xᵢ = xₙ; n --> 0; ) assert (find (* xᵢ ++, stack, ap) != 0x8000);
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
	uint16_t xₙ [0x45] = { [0 ... 0x44] = nop };	
	uint8_t n = 0;
	while (ap > 0) move (& stack [ap - 1], & xₙ [n]), attach (xₙ [n ++]), move (& nop, & stack [-- ap]);
	while (ap⁻¹ < 999) move (& stack [++ ap⁻¹], & xₙ [n]), attach (xₙ [n ++]), move (& nop, & stack [ap⁻¹ + 0]);
	// Push variable(s)
	for (uint16_t x = x₀; trace [x].code == OP_RESERVED; ++ x) move (& x, & stack [ap ++]);
	// Flush Bitcoin script
	if (n >= 1) serialize (xₙ, n, LEEWAY); else fputs ("Assertion failed: n ≥ 1\n", stderr);
	return 0;
}
