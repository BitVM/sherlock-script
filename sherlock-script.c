# include "stdio.h"
# include "bitcoin.h"
const uint8_t script [ ] =
{
	OP_RESERVED, OP_RESERVED, 4, 0, 0, 0, 32, // 2²⁹
	OP_ROT, OP_ROT, OP_ADD, // 2²⁹ x₀+x₁
	OP_2DUP, OP_LESSTHANOREQUAL, // 2²⁹ x₀+x₁ [2²⁹ ≤ x₀+x₁]
	OP_TUCK, OP_IF, // 2²⁹ [2²⁹ ≤ x₀+x₁] x₀+x₁
		OP_2, OP_PICK, OP_SUB, // 2²⁹ [2²⁹≤x₀+x₁] x₀+x₁-2²⁹
	OP_ENDIF, // 2²⁹ [2²⁹≤x₀+x₁] x₀+x₁-2²⁹[2²⁹≤x₀+x₁]
	OP_NOP
};
// clang sherlock-script.c -o sherlock-script.exe
int main (void)
{
	FILE * sherlock = _popen ("sherlock", "wb");
	fwrite (script, 1, sizeof script, sherlock);
	_pclose (sherlock);
	return 0;
}
