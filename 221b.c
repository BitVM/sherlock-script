# define _CRT_SECURE_NO_WARNINGS
# include "sherlock.h"
# include "fcntl.h"
# include "io.h"
// clang -Wno-unicode-homoglyph 221b.c -o 221b.exe
int main (void)
{
	_setmode (_fileno (stdout), _O_BINARY);
	// freopen (NULL, "wb", stdout);
	u8 script [ ] =
	{
		OP_1, OP_2, OP_ADD,
		OP_3, OP_SWAP,
		OP_GREATERTHANOREQUAL,
		OP_SWAP, OP_16, OP_SUB
	};
	preprocess (script, sizeof script);
	// for (u16 xᵢ = x₀; xᵢ < ap⁻; ++ xᵢ) serialize (stack⁻ [fp⁻] [xᵢ]);
	serialize (x₀);
	serialize (x₁);
	// fflush (stdout);
	return 0;
}
