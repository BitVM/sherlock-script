# include "stdio.h"
# include "stdlib.h"
# include "assert.h"
# include "string.h"
# include "bitcoin.h"
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
} trace [0x1000] = {
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
	[x₀ ... 0xFFF].code = nop,
};
uint16_t öp = x₀, öp⁻¹ = 0xFFF; // Trace allocation pointer
uint16_t stack [1000] = { [0 ... 999] = nop };
uint16_t ap = 0, ap⁻¹ = 999; // Stack allocation pointer
// Read nop-terminted script
uint8_t preprocess (FILE * script)
{
	uint16_t op = nop;
	while (fread (& op, 1, 1, script) > 0) switch (op)
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
			fread (& trace [öp⁻¹].xₙ, 1, op, script);
			assert (trace [öp⁻¹].num > 16 || trace [öp⁻¹].num <= -1);
			assert (trace [öp⁻¹].num < +2147483648); // x < +2³¹
			assert (trace [öp⁻¹].num > -2147483648); // x > -2³¹
			for (uint16_t öp = 0xFFF; öp >= öp⁻¹; -- öp)
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
		{
			assert (ap >= 1);
			uint16_t __ap, __ap⁻¹;
			uint16_t __stack [1000] = { [0 ... 999] = nop };
			// Save condition
			uint16_t x₂ = stack [ap - 1];
			move (& nop, & stack [-- ap]);
			// Fork stack
			for (uint16_t ap⁺ = 0; ap⁺ < ap; ++ ap⁺) move (& stack [ap⁺], & __stack [ap⁺]);
			for (uint16_t ap = 999; ap > ap⁻¹; -- ap) move (& stack [ap], & __stack [ap]);
			// Recurse scope
			__ap = ap, __ap⁻¹ = ap⁻¹;
			op = preprocess (script);
			if (op == OP_ELSE)
			{
				// Swap stack
				swap (& __ap, & ap);
				swap (& __ap⁻¹, & ap⁻¹);
				for (uint16_t ap⁺ = 0; ap⁺ < max (__ap, ap); ++ ap⁺) swap (& stack [ap⁺], & __stack [ap⁺]);
				for (uint16_t ap = 999; ap > min (__ap⁻¹, ap⁻¹); -- ap) swap (& stack [ap], & __stack [ap]);
				// Recurse scope
				op = preprocess (script);
				// Swap stack
				swap (& __ap, & ap);
				swap (& __ap⁻¹, & ap⁻¹);
				for (uint16_t ap⁺ = 0; ap⁺ < max (__ap, ap); ++ ap⁺) swap (& stack [ap⁺], & __stack [ap⁺]);
				for (uint16_t ap = 999; ap > min (__ap⁻¹, ap⁻¹); -- ap) swap (& stack [ap], & __stack [ap]);
			}
			assert (op == OP_ENDIF);
			assert (__ap == ap && __ap⁻¹ == ap⁻¹);
			// Merge stack
			for (uint16_t ap⁺ = 0; ap⁺ < ap; ++ ap⁺)
			{
				uint16_t x₁ = stack [ap⁺];
				uint16_t x₀ = __stack [ap⁺];
				if (x₀ == x₁) continue;
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
				uint16_t x₀ = __stack [ap];
				if (x₀ == x₁) continue;
				trace [öp].code = OP_IF;
				trace [öp].x₀ = x₀;
				trace [öp].x₁ = x₁;
				trace [öp].x₂ = x₂;
				move (& öp, & stack [ap]), ++ öp;
			}
			continue;
		}
		// OP_NOTIF
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
			move (& stack [ap - 2], & stack [ap - 1]);
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
		// OP_ROLL
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
typedef enum : char { LEEWAY, STRICT } workflow;
// Permute stack elements
uint16_t translate (FILE * script, const uint16_t * xₙ, uint8_t n, workflow s)
{
	if (n == 0) return 0;
	// Decrement reference counter
	for (uint8_t n⁺ = 0; n⁺ < n; ++ n⁺) if (trace [xₙ [n⁺]].reference) -- trace [xₙ [n⁺]].reference;
	assert (n <= 2); // <--
	uint16_t size = 0;
	if (n == 1)
	{
		uint16_t x₀ = xₙ [0];
		uint16_t apₓ = find⁻¹ (x₀, stack, ap);
		assert (apₓ < 1000);
		uint16_t Δap = ap - apₓ - 1;
		if (trace [x₀].reference && count (x₀, stack, ap) == 1) switch (Δap)
		{
			case 0:
				move (& stack [ap - 1], & stack [ap + 0]), ++ ap;
				++ size, fprintf (script, "OP_DUP\n"); // fwrite (& OP_DUP, 1, 1, script)
				break;
			case 1:
				move (& stack [ap - 2], & stack [ap + 0]), ++ ap;
				++ size, fprintf (script, "OP_OVER\n"); // fwrite (& OP_OVER, 1, 1, script)
				break;
			default:
				move (& stack [apₓ], & stack [ap + 0]), ++ ap;
				++ size, fprintf (script, "%s%hu\n", Δap > 16 ? "" : "OP_", Δap); // <--
				++ size, fprintf (script, "OP_PICK\n"); // fwrite (& OP_PICK, 1, 1, script)
				break;
		}
		else switch (Δap)
		{
			case 0:
				break;
			case 1:
				swap (& stack [ap - 2], & stack [ap - 1]);
				++ size, fprintf (script, "OP_SWAP\n"); // fwrite (& OP_SWAP, 1, 1, script)
				break;
			case 2:
				swap (& stack [ap - 3], & stack [ap - 2]);
				swap (& stack [ap - 2], & stack [ap - 1]);
				++ size, fprintf (script, "OP_ROT\n"); // fwrite (& OP_ROT, 1, 1, script)
				break;
			default:
				assert (0); // TODO: OP_ROLL
				break; 
		}
	}
	if (n == 2)
	{
		uint16_t x₀ = xₙ [0];
		uint16_t x₁ = xₙ [1];
		uint8_t dup₀ = trace [x₀].reference && count (x₀, stack, ap) == 1;
		uint8_t dup₁ = trace [x₁].reference && count (x₁, stack, ap) == 1;
		switch (popcnt (check (xₙ, 2, & stack [ap - 2], 2)))
		{
			case 2:
				if (dup₀ && dup₁)
				{
					move (& stack [ap - 2], & stack [ap]), ++ ap;
					move (& stack [ap - 2], & stack [ap]), ++ ap;
					++ size, fprintf (script, "OP_2DUP\n"); // fwrite (& OP_2DUP, 1, 1, script)
				}
				if (dup₀ != dup₁)
				{
					if (stack [ap - 1] == x₀ && dup₀
					 || stack [ap - 1] == x₁ && dup₁)
					{
						swap (& stack [ap - 2], & stack [ap - 1]);
						move (& stack [ap - 2], & stack [ap + 0]), ++ ap;
						++ size, fprintf (script, "OP_TUCK\n"); // fwrite (& OP_TUCK, 1, 1, script)
					}else
					if (stack [ap - 2] == x₀ && dup₀
					 || stack [ap - 2] == x₁ && dup₁)
					{
						move (& stack [ap - 2], & stack [ap + 0]), ++ ap;
						++ size, fprintf (script, "OP_OVER\n"); // fwrite (& OP_OVER, 1, 1, script)
					}
				}
				break;
			case 1:
				if (stack [ap - 2] == x₀ && dup₀
				 || stack [ap - 2] == x₁ && dup₁)
				{
					move (& stack [ap - 2], & stack [ap + 0]), ++ ap;
					++ size, fprintf (script, "OP_OVER\n"); // fwrite (& OP_OVER, 1, 1, script)
				}else
				if (stack [ap - 1] == x₀ && dup₀
				 || stack [ap - 1] == x₁ && dup₁)
				{
					swap (& stack [ap - 2], & stack [ap - 1]);
					move (& stack [ap - 2], & stack [ap + 0]), ++ ap;
					++ size, fprintf (script, "OP_TUCK\n"); // fwrite (& OP_TUCK, 1, 1, script)
				}else
				if (stack [ap - 1] != x₀
				 && stack [ap - 1] != x₁)
				{
					swap (& stack [ap - 2], & stack [ap - 1]);
					++ size, fprintf (script, "OP_SWAP\n"); // fwrite (& OP_SWAP, 1, 1, script)
				}
			default:
				assert (ap >= 3);
				if (stack [ap - 3] == x₀
				 || stack [ap - 3] == x₁)
				{
					swap (& stack [ap - 3], & stack [ap - 2]);
					swap (& stack [ap - 2], & stack [ap - 1]);
					++ size, fprintf (script, "OP_ROT\n"); // fwrite (& OP_ROT, 1, 1, script)
				}
				if (stack [ap - 1] != x₀ && stack [ap - 2] != x₀)
				{
					uint16_t apₓ = find⁻¹ (x₀, stack, ap);
					assert (apₓ < 1000);
					uint16_t Δap = ap - apₓ - 1;
					if (dup₀)
					{
						move (& stack [apₓ], & stack [ap + 0]), ++ ap;
						++ size, fprintf (script, "%s%hu\n", Δap > 16 ? "" : "OP_", Δap); // <--
						++ size, fprintf (script, "OP_PICK\n"); // fwrite (& OP_PICK, 1, 1, script)
					}
					else
					{
						assert (0); // TODO: OP_ROLL
					}
				}
				if (stack [ap - 1] != x₁ && stack [ap - 2] != x₁)
				{
					uint16_t apₓ = find⁻¹ (x₁, stack, ap);
					assert (apₓ < 1000);
					uint16_t Δap = ap - apₓ - 1;
					if (dup₁)
					{
						move (& stack [apₓ], & stack [ap + 0]), ++ ap;
						++ size, fprintf (script, "%s%hu\n", Δap > 16 ? "" : "OP_", Δap); // <--
						++ size, fprintf (script, "OP_PICK\n"); // fwrite (& OP_PICK, 1, 1, script)
					}
					else
					{
						assert (0); // TODO: OP_ROLL
					}
				}
				break;
		}
		if (s == STRICT && stack [ap - 1] == x₀)
		{
			swap (& stack [ap - 2], & stack [ap - 1]);
			++ size, fprintf (script, "OP_SWAP\n"); // fwrite (& OP_SWAP, 1, 1, script)
		}
	}
	return size;
}
// Flush Bitcoin script
uint16_t serialize (FILE * script, uint16_t xₙ [ ], uint8_t n, workflow s)
{
	uint16_t size = 0; // Byte length
	// Compute x₀ ⋯ xₙ₋₁
	for (uint8_t n⁺ = 0; n⁺ < n; ++ n⁺)
	{
		uint16_t x = xₙ [n⁺];
		uint16_t apₓ = find⁻¹ (x, stack, ap);
		// Compute x
		switch (trace [x].code)
		{
			case OP_0:
				assert (OP_0 == x);
				assert (stack [ap] == nop);
				assert (trace [x].reference == 0);
				move (& x, & stack [ap ++]);
				++ size, fprintf (script, "OP_0\n"); // fwrite (& OP_0, 1, 1, script)
				break;
			case 1:
			case 2:
			case 3:
			case 4:
				assert (trace [x].reference != 0);
				if (apₓ < 1000) break;
				assert (trace [x].num > 16 || trace [x].num <= -1);
				assert (trace [x].num < +2147483648); // x < +2³¹
				assert (trace [x].num > -2147483648); // x > -2³¹
				assert (stack [ap] == nop);
				move (& x, & stack [ap ++]);
				++ size, size += trace [x].code, fprintf (script, "%lli\n", trace [x].num);
				break;
			// ⋯
			// OP_PUSHDATA1
			// OP_PUSHDATA2
			// OP_PUSHDATA4
			// OP_1NEGATE
			case OP_RESERVED:
				assert (trace [x].reference != 0);
				if (apₓ < 1000) break;
				move (& x, & stack [ap ++]);
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
				assert (stack [ap] == nop);
				assert (trace [x].code == x);
				assert (trace [x].reference == 0);
				move (& x, & stack [ap ++]);
				++ size, fprintf (script, "%s%lli\n", trace [x].num > 16 ? "" : "OP_", trace [x].num);
				break;
			case OP_NOP:
				++ size, fprintf (script, "OP_NOP\n"); // fwrite (& OP_NOP, 1, 1, script)
				break;
			// OP_VER
			case OP_IF:
				assert (trace [x].reference != 0);
				if (apₓ < 1000) break;
				size += serialize (script, trace [x].xₙ, 3, STRICT);
				assert (ap >= 3);
				assert (stack [ap - 1] == trace [x].x₂);
				assert (stack [ap - 2] == trace [x].x₁);
				assert (stack [ap - 3] == trace [x].x₀);
				move (& nop, & stack [-- ap]);
				move (& nop, & stack [-- ap]);
				move (& x, & stack [ap - 1]);
				++ size, fprintf (script, "OP_IF\n"); // fwrite (& OP_IF, 1, 1, script)
				++ size, fprintf (script, "OP_NIP\n"); // fwrite (& OP_NIP, 1, 1, script)
				++ size, fprintf (script, "OP_ELSE\n"); // fwrite (& OP_ELSE, 1, 1, script)
				++ size, fprintf (script, "OP_DROP\n"); // fwrite (& OP_DROP, 1, 1, script)
				++ size, fprintf (script, "OP_ENDIF\n"); // fwrite (& OP_ENDIF, 1, 1, script)
				break;
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
			// OP_EQUAL
			// OP_EQUALVERIFY
			// OP_RESERVED1
			// OP_RESERVED2
			case OP_1ADD:
			case OP_1SUB:
			case OP_2MUL:
				assert (trace [x].reference != 0);
				if (apₓ < 1000) break;
				assert (ap >= 1);
				assert (stack [ap - 1] == trace [x].x₀);
				size += serialize (script, trace [x].xₙ, 1, LEEWAY);
				move (& x, & stack [ap - 1]);
				++ size, fprintf (script, "OP_DUP\n"); // fwrite (& OP_DUP, 1, 1, script)
				++ size, fprintf (script, "OP_ADD\n"); // fwrite (& OP_ADD, 1, 1, script)
				continue;
			case OP_2DIV:
			case OP_NEGATE:
			case OP_ABS:
			case OP_NOT:
			case OP_0NOTEQUAL:
				assert (trace [x].reference != 0);
				if (apₓ < 1000) break;
				size += serialize (script, trace [x].xₙ, 1, LEEWAY);
				assert (ap >= 1);
				assert (stack [ap - 1] == trace [x].x₀);
				move (& x, & stack [ap - 1]);
				++ size;{const char*OP[]={"1ADD","1SUB","2MUL","2DIV","NEGATE","ABS","NOT","0NOTEQUAL"};fprintf(script,"OP_%s\n",OP[trace[x].code-OP_1ADD]);}
				break;
			case OP_ADD:
				assert (trace [x].reference != 0);
				if (apₓ < 1000) break;
				size += serialize (script, trace [x].xₙ, 2, LEEWAY);
				assert (ap >= 2);
				assert (check (trace [x].xₙ, 2, & stack [ap - 2], 2) == (1 << 2) - 1);
				move (& nop, & stack [-- ap]);
				move (& x, & stack [ap - 1]);
				++ size, fprintf (script, "OP_ADD\n"); // fwrite (& OP_ADD, 1, 1, script)
				break;
			case OP_SUB:
				assert (trace [x].reference != 0);
				if (apₓ < 1000) break;
				size += serialize (script, trace [x].xₙ, 2, STRICT);
				assert (ap >= 2);
				assert (stack [ap - 1] == trace [x].x₁);
				assert (stack [ap - 2] == trace [x].x₀);
				move (& nop, & stack [-- ap]);
				move (& x, & stack [ap - 1]);
				++ size, fprintf (script, "OP_SUB\n"); // fwrite (& OP_SUB, 1, 1, script)
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
				assert (trace [x].reference != 0);
				if (apₓ < 1000) break;
				size += serialize (script, trace [x].xₙ, 2, LEEWAY);
				assert (ap >= 2);
				assert (check (trace [x].xₙ, 2, & stack [ap - 2], 2) == (1 << 2) - 1);
				move (& nop, & stack [-- ap]);
				move (& x, & stack [ap - 1]);
				++ size;{const char*OP[]={"BOOLAND","BOOLOR","NUMEQUAL","NUMEQUALVERIFY","NUMNOTEQUAL"};fprintf(script,"OP_%s\n",OP[trace[x].code-OP_BOOLAND]);}
				break;
			case OP_LESSTHAN:
			case OP_GREATERTHAN:
			case OP_LESSTHANOREQUAL:
			case OP_GREATERTHANOREQUAL:
				assert (trace [x].reference != 0);
				if (apₓ < 1000) break;
				size += serialize (script, trace [x].xₙ, 2, STRICT);
				assert (ap >= 2);
				assert (stack [ap - 1] == trace [x].x₁);
				assert (stack [ap - 2] == trace [x].x₀);
				move (& nop, & stack [-- ap]);
				move (& x, & stack [ap - 1]);
				++ size;{const char*OP[]={"LESSTHAN","GREATERTHAN","LESSTHANOREQUAL","GREATERTHANOREQUAL"};fprintf(script,"OP_%s\n",OP[trace[x].code-OP_LESSTHAN]);}
				break;
			case OP_MIN:
			case OP_MAX:
				assert (trace [x].reference != 0);
				if (apₓ < 1000) break;
				size += serialize (script, trace [x].xₙ, 2, LEEWAY);
				assert (ap >= 2);
				assert (check (trace [x].xₙ, 2, & stack [ap - 2], 2) == (1 << 2) - 1);
				move (& nop, & stack [-- ap]);
				move (& x, & stack [ap - 1]);
				++ size, fprintf (script, "OP_%s\n", trace [x].code == OP_MIN ? "MIN" : "MAX"); // fwrite (& op, 1, 1, script)
				break;
			case OP_WITHIN:
				assert (trace [x].reference != 0);
				if (apₓ < 1000) break;
				size += serialize (script, trace [x].xₙ, 3, STRICT);
				assert (ap >= 3);
				assert (stack [ap - 1] == trace [x].x₂);
				assert (stack [ap - 2] == trace [x].x₁);
				assert (stack [ap - 3] == trace [x].x₀);
				move (& nop, & stack [-- ap]);
				move (& nop, & stack [-- ap]);
				move (& x, & stack [ap - 1]);
				++ size, fprintf (script, "OP_WITHIN\n"); // fwrite (& OP_WITHIN, 1, 1, script)
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
	size += translate (script, xₙ, min (n, 2), s);
	size += translate (script, xₙ+2, max (n, 2) - 2, s); // <--
	return size;
}
# include "fcntl.h"
# include "io.h"
// clang sherlock.c -o sherlock.exe
int main (void)
{
	// Trace script
	_setmode (_fileno (stdin), _O_BINARY);
	uint8_t op = preprocess (stdin);
	assert (op == OP_NOP);
	// Mark result(s)
	uint16_t xₙ [0x45] = { [0 ... 0x44] = nop };	
	uint16_t n = 0;
	while (n < ap) move (& stack [n], & xₙ [n]), attach (xₙ [n ++]);
	// Reset (alt)stack
	while (ap > 0) move (& nop, & stack [-- ap]);
	while (ap⁻¹ < 999) move (& nop, & stack [++ ap⁻¹]);
	// Push variable(s)
	for (uint16_t x = x₀; trace [x].code == OP_RESERVED; ++ x) move (& x, & stack [ap ++]);
	// Flush Bitcoin script
	uint16_t size = serialize (stdout, xₙ, n, LEEWAY);
	assert (ap == n);
	return 0;
}
