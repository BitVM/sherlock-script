# define _CRT_SECURE_NO_WARNINGS
# include "sherlock.h"
# include "fcntl.h"
# include "io.h"
// clang -Wno-unicode-homoglyph sherlock.c -o sherlock.exe
int main (void)
{
	// >>>>>>>>>>>>>>>>>>>>>>>>
	_setmode (_fileno (stdin), _O_BINARY);
	// freopen (NULL, "rb", stdin);
	u16 pc = 0;
	u8 script [4096] = { [0 ... 4095] = OP_NOP };
	do
	{
		fread (script + pc, sizeof (OP_NOP), 1, stdin);
	}
	while (script [pc ++] != OP_NOP);
	// <<<<<<<<<<<<<<<<<<<<<<<<
	_setmode (_fileno (stdout), _O_BINARY);
	// freopen (NULL, "wb", stdout);
	preprocess (script, sizeof script);
	// for (u16 xᵢ = x₀; xᵢ < ap⁻; ++ xᵢ)
	// {
	// 	serialize (stack⁻ [fp⁻] [xᵢ]);
	// }
	serialize (x₀);
	return 0;
}
