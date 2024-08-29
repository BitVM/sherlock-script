# include "stdio.h"
# include "stdint.h"
# include "assert.h"
enum : uint8_t
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
};
uint32_t __builtin_stack [1000] = { [0 ... 999] = 0x80000000 };
uint16_t __builtin_ap = 0, __builtin_ap⁻¹ = 999; // Stack allocation pointer
void __builtin_push (uint32_t x₀)
{
	assert (__builtin_ap <= __builtin_ap⁻¹);
	__builtin_stack [__builtin_ap ++] = x₀;
}
uint32_t __builtin_drop (void) // OP_DROP
# define __builtin_drop __builtin_drop ( )
{
	assert (__builtin_ap >= 1);
	return __builtin_stack [-- __builtin_ap];
}
void __builtin_pick (uint16_t Δap) // Δap OP_PICK
{
	assert (Δap < __builtin_ap);
	uint32_t xᵢ = __builtin_stack [__builtin_ap - Δap - 1];
	__builtin_stack [__builtin_ap ++] = xᵢ;
}
# define __builtin_over __builtin_pick (1) // OP_OVER
void __builtin_roll (uint16_t Δap) // Δap OP_ROLL
{
	assert (Δap < __builtin_ap);
	uint32_t xᵢ = __builtin_stack [__builtin_ap - Δap - 1];
	memmove (__builtin_stack + __builtin_ap - Δap - 1,
	         __builtin_stack + __builtin_ap - Δap, sizeof (uint32_t) * Δap);
	__builtin_stack [__builtin_ap - 1] = xᵢ;
}
# define __builtin_swap __builtin_roll (1) // OP_SWAP
uint32_t __builtin_find (uint32_t xᵢ)
{
	for (uint16_t apₓ = __builtin_ap; apₓ != 0; -- apₓ) if (__builtin_stack [apₓ - 1] == xᵢ) return apₓ - 1;
	return 0x80000000;
}
uint64_t __builtin_check (const uint32_t * xₙ, uint8_t n)
{
	if (n > 64) n = 64; // n = min (n, 64)
	uint64_t flag = 0x0000000000000000;
	for (uint8_t idx = 0; idx < n; ++ idx)
	for (uint16_t ap = 0; ap < __builtin_ap; ++ ap)
	{
		if (__builtin_stack [ap] == xₙ [idx]) flag |= 1 << idx;
	}
	return flag;
}
uint64_t __builtin_check⁻¹ (const uint32_t * xₙ, uint8_t n)   
{
	uint64_t flag = 0x0000000000000000;
	while (n --> 0) // assert ap ≤ 32
	{
		uint32_t apₓ = __builtin_find (* xₙ ++);
		if (apₓ == 0x80000000) continue;
		uint32_t Δap = __builtin_ap - apₓ - 1;
		if (Δap < 64) flag |= (uint64_t) 1 << Δap;
	}
	return flag;
}
uint8_t __builtin_count (uint32_t x₀)
{
	uint8_t cnt = 0;
	for (uint16_t ap = 0; ap < __builtin_ap; ++ ap)
	{
		if (__builtin_stack [ap] == x₀) ++ cnt;
	}
	return cnt;
}
uint8_t __builtin_stdin¹ (void)
# define __builtin_stdin¹ __builtin_stdin¹ ( )
{
	uint8_t op = OP_NOP;
	fread (& op, 1, 1, stdin);
	return op;
}
int32_t __builtin_stdin (uint8_t op)
{
	int32_t num = 0;
	uint8_t imm8 = 0;
	switch (op)
	{
		case 4: num |= __builtin_stdin¹ << imm8, imm8 += 8; // 🡇
		case 3: num |= __builtin_stdin¹ << imm8, imm8 += 8; // 🡇
		case 2: num |= __builtin_stdin¹ << imm8, imm8 += 8; // 🡇
		case 1: num |= __builtin_stdin¹ << imm8;
		default: break;
	}
	return num;
}
uint8_t __builtin_stdout¹ (uint8_t op)
{
	fwrite (& op, 1, 1, stdout);
	return op;
}
int32_t __builtin_stdout (int32_t num)
{
	if (num == 0) return __builtin_stdout¹ (OP_0);
	if (num == -1) return __builtin_stdout¹ (OP_1NEGATE);
	if (num >= 1 && num <= 16) return __builtin_stdout¹ (OP_RESERVED + num);
	int32_t value = num;
	switch (__builtin_stdout¹ (4 - __builtin_clz (num) / 8))
	{
		case 4: __builtin_stdout¹ (num & 0xFF), num >>= 8; // 🡇
		case 3: __builtin_stdout¹ (num & 0xFF), num >>= 8; // 🡇
		case 2: __builtin_stdout¹ (num & 0xFF), num >>= 8; // 🡇
		case 1: __builtin_stdout¹ (num & 0xFF);
		default: return value;
	}
}
