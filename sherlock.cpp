
typedef signed int LONG;
typedef signed short INT;
typedef unsigned char BYTE;
typedef unsigned short WORD;
constexpr auto NULL = nullptr;

char * stdout;
void PRINT (char c) { * stdout ++ = c; }
void PRINT (const char *c_str) { for (const char * p = c_str; * p != '\0'; ++ p) * stdout ++ = * p; }
const char * __OP__ [256]
{
    "OP_FALSE", "8-bit", "16-bit", "24-bit", "32-bit", "40-bit", "48-bit", "56-bit", "64-bit",
    "72-bit", "80-bit", "88-bit", "96-bit", "104-bit", "112-bit", "120-bit", "128-bit", "136-bit",
    "144-bit", "152-bit", "160-bit", "168-bit", "176-bit", "184-bit", "192-bit", "200-bit",
    "208-bit", "216-bit", "224-bit", "232-bit", "240-bit", "248-bit", "256-bit", "264-bit", "272-bit",
    "280-bit", "288-bit", "296-bit", "304-bit", "312-bit", "320-bit", "328-bit", "336-bit", "344-bit",
    "352-bit", "360-bit", "368-bit", "376-bit", "384-bit", "392-bit", "400-bit", "408-bit", "416-bit",
    "424-bit", "432-bit", "440-bit", "448-bit", "456-bit", "464-bit", "472-bit", "480-bit", "488-bit",
    "496-bit", "504-bit", "512-bit", "520-bit", "528-bit", "536-bit", "544-bit", "552-bit", "560-bit",
    "568-bit", "576-bit", "584-bit", "592-bit", "600-bit", "OP_PUSHDATA1", "OP_PUSHDATA2", "OP_PUSHDATA4",
    "OP_1NEGATE", "OP_RESERVED", "OP_TRUE", "OP_2", "OP_3", "OP_4", "OP_5", "OP_6", "OP_7", "OP_8", "OP_9",
    "OP_10", "OP_11", "OP_12", "OP_13", "OP_14", "OP_15", "OP_16", "OP_NOP", "OP_VER", "OP_IF", "OP_NOTIF",
    "OP_VERIF", "OP_VERNOTIF", "OP_ELSE", "OP_ENDIF", "OP_VERIFY", "OP_RETURN", "OP_TOALTSTACK",
    "OP_FROMALTSTACK", "OP_2DROP", "OP_2DUP", "OP_3DUP", "OP_2OVER", "OP_2ROT", "OP_2SWAP", "OP_IFDUP",
    "OP_DEPTH", "OP_DROP", "OP_DUP", "OP_NIP", "OP_OVER", "OP_PICK", "OP_ROLL", "OP_ROT", "OP_SWAP",
    "OP_TUCK", "OP_CAT", "OP_SUBSTR", "OP_LEFT", "OP_RIGHT", "OP_SIZE", "OP_INVERT", "OP_AND", "OP_OR",
    "OP_XOR", "OP_EQUAL", "OP_EQUALVERIFY", "OP_RESERVED1", "OP_RESERVED2", "OP_1ADD", "OP_1SUB", "OP_2MUL",
    "OP_2DIV", "OP_NEGATE", "OP_ABS", "OP_NOT", "OP_0NOTEQUAL", "OP_ADD", "OP_SUB", "OP_MUL", "OP_DIV",
    "OP_MOD", "OP_LSHIFT", "OP_RSHIFT", "OP_BOOLAND", "OP_BOOLOR", "OP_NUMEQUAL", "OP_NUMEQUALVERIFY",
    "OP_NUMNOTEQUAL", "OP_LESSTHAN", "OP_GREATERTHAN", "OP_LESSTHANOREQUAL", "OP_GREATERTHANOREQUAL",
    "OP_MIN", "OP_MAX", "OP_WITHIN", "OP_RIPEMD160", "OP_SHA1", "OP_SHA256", "OP_HASH160", "OP_HASH256",
    "OP_CODESEPARATOR", "OP_CHECKSIG", "OP_CHECKSIGVERIFY", "OP_CHECKMULTISIG", "OP_CHECKMULTISIGVERIFY",
    "OP_NOP1", "OP_NOP2", "OP_NOP3", "OP_NOP4", "OP_NOP5", "OP_NOP6", "OP_NOP7", "OP_NOP8", "OP_NOP9",
    "OP_NOP10", "OP_CHECKSIGADD", "0xBB", "0xBC", "0xBD", "0xBE", "0xBF",
    "0xC0", "0xC1", "0xC2", "0xC3", "0xC4", "0xC5", "0xC6", "0xC7", "0xC8", "0xC9", "0xCA", "0xCB", "0xCC",
    "0xCD", "0xCE", "0xCF", "0xD0", "0xD1", "0xD2", "0xD3", "0xD4", "0xD5", "0xD6", "0xD7", "0xD8", "0xD9",
    "0xDA", "0xDB", "0xDC", "0xDD", "0xDE", "0xDF", "0xE0", "0xE1", "0xE2", "0xE3", "0xE4", "0xE5", "0xE6",
    "0xE7", "0xE8", "0xE9", "0xEA", "0xEB", "0xEC", "0xED", "0xEE", "0xEF", "0xF0", "0xF1", "0xF2", "0xF3",
    "0xF4", "0xF5", "0xF6", "0xF7", "0xF8", "0xF9", "0xFA", "0xFB", "0xFC", "0xFD", "0xFE", "0xFF"
};
template <typename T> T WARNING (T VA_ARGS, const char * C_STR)
{
    for (const char * p = C_STR; * p != '\0'; ++ p)
    {
        * stdout ++ = * p;
    }
    return VA_ARGS;
}
# define WARNING(...) WARNING(__VA_ARGS__, " ERROR\n" #__VA_ARGS__ "\n")

// Bitcoin script

enum : BYTE
{
    OP_0 = 0x00, OP_PUSHDATA1 = 0x4c, OP_PUSHDATA2, OP_PUSHDATA4, OP_1NEGATE, OP_RESERVED, OP_1, OP_2, OP_3, OP_4, OP_5, OP_6, OP_7,
    OP_8, OP_9, OP_10, OP_11, OP_12, OP_13, OP_14, OP_15, OP_16, OP_NOP, OP_VER, OP_IF, OP_NOTIF, OP_VERIF, OP_VERNOTIF, OP_ELSE,
    OP_ENDIF, OP_VERIFY, OP_RETURN, OP_TOALTSTACK, OP_FROMALTSTACK, OP_2DROP, OP_2DUP, OP_3DUP, OP_2OVER, OP_2ROT, OP_2SWAP, OP_IFDUP,
    OP_DEPTH, OP_DROP, OP_DUP, OP_NIP, OP_OVER, OP_PICK, OP_ROLL, OP_ROT, OP_SWAP, OP_TUCK, OP_CAT, OP_SUBSTR, OP_LEFT, OP_RIGHT, OP_SIZE,
    OP_INVERT, OP_AND, OP_OR, OP_XOR, OP_EQUAL, OP_EQUALVERIFY, OP_RESERVED1, OP_RESERVED2, OP_1ADD, OP_1SUB, OP_2MUL, OP_2DIV, OP_NEGATE,
    OP_ABS, OP_NOT, OP_0NOTEQUAL, OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD, OP_LSHIFT, OP_RSHIFT, OP_BOOLAND, OP_BOOLOR, OP_NUMEQUAL,
    OP_NUMEQUALVERIFY, OP_NUMNOTEQUAL, OP_LESSTHAN, OP_GREATERTHAN, OP_LESSTHANOREQUAL, OP_GREATERTHANOREQUAL, OP_MIN, OP_MAX, OP_WITHIN,
    OP_RIPEMD160, OP_SHA1, OP_SHA256, OP_HASH160, OP_HASH256, OP_CODESEPARATOR, OP_CHECKSIG, OP_CHECKSIGVERIFY, OP_CHECKMULTISIG,
    OP_CHECKMULTISIGVERIFY, OP_NOP1, OP_NOP2, OP_NOP3, OP_NOP4, OP_NOP5, OP_NOP6, OP_NOP7, OP_NOP8, OP_NOP9, OP_NOP10, OP_CHECKSIGADD,
};

auto OP_TRUE = OP_1;
auto OP_FALSE = OP_0;
auto OP_CHECKLOCKTIMEVERIFY = OP_NOP2;
auto OP_CHECKSEQUENCEVERIFY = OP_NOP3;

// Sherlock script

// OP_RESERVED <=> unlocking variable
// OP_RESERVED1 <=> function call (scan source code in detail)
// OP_RESERVED2 <=> function call (let source code untouched)

// Execution

// Script representation
decltype (OP_TRUE) __script [65536];
// NOTE: __script_table does not include -1 <= numbers <= 16
LONG __script_table [64]; // Opcodes 0xC0 up to 0xFF
WORD pc = 0;

// Preprocess script
WORD preprocess (const BYTE * script, WORD size)
{
    WORD count = 0;
    // Set constants to undefined
    for (WORD n = 0; n < 64; ++ n) __script_table [n] = -2147483648; // memset
    // Copy script from source address
    for (WORD pc₀ = 0; pc₀ < size; ++ pc₀)
    {
        auto opcode = script [pc₀];
        // Transcode multi-byte opcode
        if (1 <= opcode && opcode <= 4)
        {
            LONG constant = 0;
            // Compose constant
            for (WORD n = 0; n < opcode; ++ n) constant |= script [++ pc₀] << n * 8;
            // Check constant for duplication
            for (WORD n = 0; n < 64; ++ n)
            {
                // Reuse constant
                if (__script_table [n] == constant)
                {
                    __script [count ++] = (decltype (OP_TRUE)) (0xC0 + n);
                    break;
                }
                // Register constant
                if (__script_table [n] == -2147483648)
                {
                    __script_table [n] = constant;
                    __script [count ++] = (decltype (OP_TRUE)) (0xC0 + n);
                    break;
                }
            }
            continue;
        }
        __script [count ++] = (decltype (OP_TRUE) &) script [pc₀];
    }
    // Fill unused memory with OP_NOP
    for (WORD n = 65535; count <= n; -- n) __script [n] = OP_NOP;
    // Return the number of opcodes
    return count;
}

// Program trace
struct
{
    // NOTE: OP_RESERVED new input element
    // NOTE: OP_NOP1 unknown stack element
    // NOTE: 0xC0-0xFF compressed constant
    decltype (OP_TRUE) opcode; // operator, constant or condition
    BYTE reference_counter; // OP_PICK|OP_ROLL OP_OVER|OP_SWAP [OP_DUP]
    WORD operand_0; // OP_* arithmetic expression
    WORD operand_1; // OP_* arithmetic expression
    WORD operand_2; // OP_* arithmetic expression
}
__trace [65536];
// NOTE: OP_RESERVED unlocking variable at index 65535
WORD op = 0;
WORD op⁻¹ = 65535;

// Parse trace index as constant number
LONG eval (WORD addr)
{
    decltype (OP_TRUE) opcode = __trace [addr].opcode;
    if (opcode == OP_0) return 0;
    if (opcode <= OP_16 && opcode >= OP_1) return opcode - OP_1 + 1;
    if (opcode >= 0xC0) return __script_table [opcode - 0xC0];
    return -2147483648;
}

struct Δap
{
    WORD ap = 0;
    WORD ap⁻¹ = 999;
};

// Trace script
Δap trace (WORD (& stack₁) [1000], const WORD (& stack₀) [1000], WORD ap = 0, WORD ap⁻¹ = 999)
{
    // memcpy
    for (WORD _ = 0; _ < ap; ++ _) stack₁ [_] = stack₀ [_];
    // memcpy
    for (WORD _ = 999; _ > ap⁻¹; -- _) stack₁ [_] = stack₀ [_];

    auto op_reserved = [&] (WORD op₀⁻¹)
    {
        // Allocate new variable
        for (INT _ = ap ++; _ > 0; -- _) stack₁ [_] = stack₁ [_ - 1]; // memmove
        __trace [op⁻¹].opcode = OP_RESERVED;
        __trace [op⁻¹].reference_counter = 0;
        stack₁ [0] = op₀⁻¹ > op⁻¹ ? op₀⁻¹ : op⁻¹ --;
    };

    auto op_nop = [&] (WORD (& stack) [1000], WORD & ap₀)
    {
        // Allocate temporary variable
        for (INT _ = ap₀ ++; _ > 0; -- _) stack [_] = stack [_ - 1]; // memmove
        __trace [op].opcode = OP_NOP;
        __trace [op].reference_counter = 0;
        stack [0] = op ++;
    };

    auto op_nop⁻¹ = [&] (WORD (& stack) [1000], WORD & ap₀⁻¹)
    {
        // Allocate temporary variable on altstack
        for (INT _ = -- ap₀⁻¹; _ < 999; ++ _) stack [_] = stack [_ + 1]; // memmove
        __trace [op].opcode = OP_NOP;
        __trace [op].reference_counter = 0;
        stack [999] = op ++;
    };

    for (auto opcode = __script [pc]; opcode != OP_NOP; opcode = __script [++ pc])
    {
        switch (opcode)
        {
            case OP_0: // OP_FALSE
                __trace [op].opcode = OP_FALSE;
                __trace [op].reference_counter = 0;
                stack₁ [ap ++] = op ++;
                continue;

            case OP_1NEGATE:
                __trace [op].opcode = OP_1NEGATE;
                __trace [op].reference_counter = 0;
                stack₁ [ap ++] = op ++;
                continue;

            case OP_1: // OP_TRUE
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
                __trace [op].opcode = opcode;
                __trace [op].reference_counter = 0;
                stack₁ [ap ++] = op ++;
                continue;

            case OP_IF:
            case OP_NOTIF:
                if (ap == 0) op_reserved (op⁻¹);
                // Execute and merge OP_IF and OP_ELSE
                {
                    decltype (OP_TRUE) opcode⁻¹ = opcode == OP_NOTIF ? OP_RESERVED1 : OP_RESERVED2;
                    decltype (OP_TRUE) opcode = opcode == OP_IF ? OP_RESERVED1 : OP_RESERVED2;
                    WORD __0 = stack₁ [-- ap];
                    // OP_IF
                    ++ pc;
                    WORD stack₂ [1000];
                    auto op₀⁻¹ = op⁻¹;
                    auto Δ = trace (stack₂, stack₁, ap, ap⁻¹);
                    while (op₀⁻¹ > op⁻¹) op_reserved (op₀⁻¹ --);
                    if (__script [pc] == OP_ELSE)
                    {
                        ++ pc;
                        WORD stack₂ [1000];
                        auto op₀⁻¹ = op⁻¹;
                        auto Δ = trace (stack₂, stack₁, ap, ap⁻¹);
                        while (op₀⁻¹ > op⁻¹) op_reserved (op₀⁻¹ --);
                        ap = Δ.ap;
                        ap⁻¹ = Δ.ap⁻¹;
                        // memcpy
                        for (WORD _ = 0; _ < ap; ++ _) stack₁ [_] = stack₂ [_];
                        for (WORD _ = 999; _ > ap⁻¹; -- _) stack₁ [_] = stack₂ [_];
                    }
                    if (__script [pc] != OP_ENDIF) return WARNING (OP_ENDIF), Δap { ap, ap⁻¹ };
                    // NOTE: __script [pc] must be OP_ENDIF here
                    while (ap < Δ.ap) op_nop (stack₁, ap);
                    while (ap > Δ.ap) op_nop (stack₂, Δ.ap);
                    for (WORD _ = 0; _ < ap; ++ _)
                    {
                        if (stack₁ [_] == stack₂ [_]) continue;
                        WORD __1 = stack₂ [_];
                        WORD __2 = stack₁ [_];
                        // x₀ ? (x₀ ? x₁ : _) : x₂  <=>  x₀ ? x₁ : x₂
                        if (__trace [__1].opcode == opcode && __trace [__1].operand_0 == __0) __1 = __trace [__1].operand_1;
                        if (__trace [__2].opcode == opcode⁻¹ && __trace [__2].operand_0 == __0) __2 = __trace [__2].operand_1;
                        // x₀ ? x₁ : (x₀ ? _ : x₂)  <=>  x₀ ? x₁ : x₂
                        if (__trace [__1].opcode == opcode⁻¹ && __trace [__1].operand_0 == __0) __1 = __trace [__1].operand_2;
                        if (__trace [__2].opcode == opcode && __trace [__2].operand_0 == __0) __2 = __trace [__2].operand_2;
                        __trace [op].opcode = opcode;
                        __trace [op].reference_counter = 0;
                        __trace [op].operand_0 = __0;
                        __trace [op].operand_1 = __1;
                        __trace [op].operand_2 = __2;
                        stack₁ [_] = op ++;
                    }
                    while (ap⁻¹ > Δ.ap⁻¹) op_nop⁻¹ (stack₁, ap⁻¹);
                    while (ap⁻¹ < Δ.ap⁻¹) op_nop⁻¹ (stack₂, Δ.ap⁻¹);
                    for (WORD _ = 999; _ > ap⁻¹; -- _)
                    {
                        if (stack₁ [_] == stack₂ [_]) continue;
                        WORD __1 = stack₂ [_];
                        WORD __2 = stack₁ [_];
                        // x₀ ? (x₀ ? x₁ : _) : x₂  <=>  x₀ ? x₁ : x₂
                        if (__trace [__1].opcode == opcode && __trace [__1].operand_0 == __0) __1 = __trace [__1].operand_1;
                        if (__trace [__2].opcode == opcode⁻¹ && __trace [__2].operand_0 == __0) __2 = __trace [__2].operand_1;
                        // x₀ ? x₁ : (x₀ ? _ : x₂)  <=>  x₀ ? x₁ : x₂
                        if (__trace [__1].opcode == opcode⁻¹ && __trace [__1].operand_0 == __0) __1 = __trace [__1].operand_2;
                        if (__trace [__2].opcode == opcode && __trace [__2].operand_0 == __0) __2 = __trace [__2].operand_2;
                        __trace [op].opcode = opcode;
                        __trace [op].reference_counter = 0;
                        __trace [op].operand_0 = __0;
                        __trace [op].operand_1 = __1;
                        __trace [op].operand_2 = __2;
                        stack₁ [_] = op ++;
                    }
                }
                continue;

            case OP_ELSE:
            case OP_ENDIF:
                return Δap { ap, ap⁻¹ };

            case OP_TOALTSTACK:
                if (ap == 0) op_reserved (op⁻¹);
                stack₁ [ap⁻¹ --] = stack₁ [-- ap];
                continue;

            case OP_FROMALTSTACK:
                if (ap⁻¹ < 999)
                {
                    stack₁ [ap ++] = stack₁ [++ ap⁻¹];
                }
                continue;

            case OP_2DROP:
                while (ap < 2) op_reserved (op⁻¹);
                // while (ap < 2) op_nop (stack₁, ap);
                -- ap;
                -- ap;
                continue;

            case OP_2DUP:
                while (ap < 2) op_reserved (op⁻¹);
                stack₁ [ap] = stack₁ [ap - 2]; ++ ap;
                stack₁ [ap] = stack₁ [ap - 2]; ++ ap;
                continue;

            case OP_3DUP:
                while (ap < 3) op_reserved (op⁻¹);
                stack₁ [ap] = stack₁ [ap - 3]; ++ ap;
                stack₁ [ap] = stack₁ [ap - 3]; ++ ap;
                stack₁ [ap] = stack₁ [ap - 3]; ++ ap;
                continue;

            case OP_2OVER:
                while (ap < 4) op_reserved (op⁻¹);
                stack₁ [ap] = stack₁ [ap - 4]; ++ ap;
                stack₁ [ap] = stack₁ [ap - 4]; ++ ap;
                continue;

            case OP_2ROT:
                while (ap < 6) op_reserved (op⁻¹);
                stack₁ [ap] = stack₁ [ap - 6];
                stack₁ [ap - 6] = stack₁ [ap - 4];
                stack₁ [ap - 4] = stack₁ [ap - 2];
                stack₁ [ap - 2] = stack₁ [ap];
                stack₁ [ap] = stack₁ [ap - 5];
                stack₁ [ap - 5] = stack₁ [ap - 3];
                stack₁ [ap - 3] = stack₁ [ap - 1];
                stack₁ [ap - 1] = stack₁ [ap];
                continue;

            case OP_2SWAP:
                while (ap < 4) op_reserved (op⁻¹);
                stack₁ [ap] = stack₁ [ap - 4];
                stack₁ [ap - 4] = stack₁ [ap - 2];
                stack₁ [ap - 2] = stack₁ [ap];
                stack₁ [ap] = stack₁ [ap - 3];
                stack₁ [ap - 3] = stack₁ [ap - 1];
                stack₁ [ap - 1] = stack₁ [ap];
                continue;

            case OP_DROP:
                if (ap == 0) op_reserved (op⁻¹);
                // if (ap == 0) op_nop (stack₁, ap);
                -- ap;
                continue;

            case OP_DUP:
                if (ap == 0) op_reserved (op⁻¹);
                stack₁ [ap] = stack₁ [ap - 1]; ++ ap;
                continue;

            case OP_NIP:
                while (ap < 2) op_reserved (op⁻¹);
                stack₁ [ap - 2] = stack₁ [ap - 1];
                -- ap;
                continue;

            case OP_OVER:
                while (ap < 2) op_reserved (op⁻¹);
                stack₁ [ap] = stack₁ [ap - 2]; ++ ap;
                continue;

            case OP_PICK:
                if (ap == 0) op_reserved (op⁻¹);
                {
                    // NOTE: This only works for constant indices
                    auto Δ = eval (stack₁ [ap - 1]);
                    if (Δ == -2147483648) return WARNING (OP_PICK), Δap { ap, ap⁻¹ };
                    while (ap <= Δ) op_reserved (op⁻¹);
                    stack₁ [ap - 1] = stack₁ [ap - Δ - 2];
                }
                continue;

            case OP_ROLL:
                if (ap == 0) op_reserved (op⁻¹);
                // NOTE: This only works for constant indices
                if (auto Δ = eval (stack₁ [-- ap]))
                {
                    if (Δ == -2147483648) return WARNING (OP_ROLL), Δap { ap, ap⁻¹ };
                    while (ap <= Δ) op_reserved (op⁻¹);
                    stack₁ [ap] = stack₁ [ap - Δ - 1];
                    do
                    {
                        stack₁ [ap - Δ - 1] = stack₁ [ap - Δ];
                    }
                    while (0 <-- Δ);
                    stack₁ [ap - 1] = stack₁ [ap];
                }
                continue;

            case OP_ROT:
                while (ap < 3) op_reserved (op⁻¹);
                stack₁ [ap] = stack₁ [ap - 3];
                stack₁ [ap - 3] = stack₁ [ap - 2];
                stack₁ [ap - 2] = stack₁ [ap - 1];
                stack₁ [ap - 1] = stack₁ [ap];
                continue;

            case OP_SWAP:
                while (ap < 2) op_reserved (op⁻¹);
                stack₁ [ap] = stack₁ [ap - 2];
                stack₁ [ap - 2] = stack₁ [ap - 1];
                stack₁ [ap - 1] = stack₁ [ap];
                continue;

            case OP_TUCK:
                while (ap < 2) op_reserved (op⁻¹);
                stack₁ [ap] = stack₁ [ap - 2];
                stack₁ [ap - 2] = stack₁ [ap - 1];
                stack₁ [ap - 1] = stack₁ [ap];
                stack₁ [ap] = stack₁ [ap - 2]; ++ ap;
                continue;

            case OP_EQUAL:
                while (ap < 2) op_reserved (op⁻¹);
                __trace [op].opcode = OP_EQUAL;
                __trace [op].reference_counter = 0;
                __trace [op].operand_0 = stack₁ [-- ap];
                __trace [op].operand_1 = stack₁ [-- ap];
                stack₁ [ap ++] = op ++;
                continue;

            case OP_1ADD:
            case OP_1SUB:
            case OP_NEGATE:
            case OP_NOT:
            case OP_0NOTEQUAL:
                if (ap == 0) op_reserved (op⁻¹);
                __trace [op].opcode = opcode;
                __trace [op].reference_counter = 0;
                __trace [op].operand_0 = stack₁ [ap - 1];
                stack₁ [ap - 1] = op ++;
                continue;

            case OP_ADD:
            case OP_SUB:
            case OP_BOOLAND:
            case OP_BOOLOR:
            case OP_NUMEQUAL:
            case OP_NUMNOTEQUAL:
            case OP_LESSTHAN:
            case OP_GREATERTHAN:
            case OP_LESSTHANOREQUAL:
            case OP_GREATERTHANOREQUAL:
                while (ap < 2) op_reserved (op⁻¹);
                __trace [op].opcode = opcode;
                __trace [op].reference_counter = 0;
                __trace [op].operand_0 = stack₁ [-- ap];
                __trace [op].operand_1 = stack₁ [-- ap];
                stack₁ [ap ++] = op ++;
                continue;

            default:
                if (opcode < 0xC0) return WARNING (OP_RESERVED), Δap { ap, ap⁻¹ };
                // NOTE: 0xC0 is the very first constant
                if (WORD constant = 65535)
                {
                    // Checking entire trace to prevent duplication
                    for (WORD n = 0; n < op; ++ n)
                    {
                        if (__trace [n].opcode == opcode)
                        {
                            constant = n;
                            break;
                        }
                    }
                    if (constant == 65535)
                    {
                        __trace [op].opcode = opcode;
                        __trace [op].reference_counter = 0;
                        constant = op ++;
                    }
                    stack₁ [ap ++] = constant;
                }
                continue;
        }
    }

    return Δap { ap, ap⁻¹ };
}

//
// clang sherlock.cpp -Wno-mathematical-notation-identifier-extension --no-standard-libraries --target=wasm32 -Wl,--no-entry -o sherlock.wasm
//

const char * __indices [ ] {"₀", "₁", "₂", "₃", "₄", "₅", "₆", "₇", "₈", "₉"};

void print (WORD trace, char z = '\0') // precedence
{
    auto opcode = __trace [trace].opcode;
    WORD operand_0 = __trace [trace].operand_0;
    WORD operand_1 = __trace [trace].operand_1;
    WORD operand_2 = __trace [trace].operand_2;

    switch (opcode)
    {
        case OP_0: PRINT ('0'); return;
        case OP_PUSHDATA1: PRINT ("OP_PUSHDATA1"); return;
        case OP_PUSHDATA2: PRINT ("OP_PUSHDATA2"); return;
        case OP_PUSHDATA4: PRINT ("OP_PUSHDATA4"); return;
        case OP_1NEGATE: PRINT ("-1"); return;
        case OP_RESERVED: PRINT ('x'); PRINT (__indices [65535 - trace]); return;
        case OP_1: PRINT ("1"); return;
        case OP_2: PRINT ("2"); return;
        case OP_3: PRINT ("3"); return;
        case OP_4: PRINT ("4"); return;
        case OP_5: PRINT ("5"); return;
        case OP_6: PRINT ("6"); return;
        case OP_7: PRINT ("7"); return;
        case OP_8: PRINT ("8"); return;
        case OP_9: PRINT ("9"); return;
        case OP_10: PRINT ("10"); return;
        case OP_11: PRINT ("11"); return;
        case OP_12: PRINT ("12"); return;
        case OP_13: PRINT ("13"); return;
        case OP_14: PRINT ("14"); return;
        case OP_15: PRINT ("15"); return;
        case OP_16: PRINT ("16"); return;
        case OP_NOP: PRINT ("∅"); return;
        // case OP_VER:
        // case OP_IF:
        // case OP_NOTIF:
        // case OP_VERIF:
        // case OP_VERNOTIF:
        // case OP_ELSE:,
        // case OP_ENDIF:
        case OP_VERIFY: PRINT ("verify ("); print (operand_0); PRINT (")"); return;
        case OP_RETURN: PRINT ("return"); return;
        // case OP_TOALTSTACK:
        // case OP_FROMALTSTACK:
        // case OP_2DROP:
        // case OP_2DUP:
        // case OP_3DUP:
        // case OP_2OVER:
        // case OP_2ROT:
        // case OP_2SWAP:
        // case OP_IFDUP:
        case OP_DEPTH: PRINT ("z"); return;
        // case OP_DROP:
        // case OP_DUP:
        // case OP_NIP:
        // case OP_OVER:
        // case OP_PICK:
        // case OP_ROLL:
        // case OP_ROT:
        // case OP_SWAP:
        // case OP_TUCK:
        // case OP_CAT:
        // case OP_SUBSTR:
        // case OP_LEFT:
        // case OP_RIGHT:
        case OP_SIZE: PRINT ("n"); return;
        // case OP_INVERT:
        // case OP_AND:
        // case OP_OR:
        // case OP_XOR:
        case OP_EQUAL: if (z == '=') PRINT ('('); print (operand_0, '='); PRINT ("≟"); print (operand_1, '='); if (z == '=') PRINT (')'); return;
        case OP_EQUALVERIFY: PRINT ("verify ("); print (operand_0, '='); PRINT ("≟"); print (operand_1, '='); PRINT (")"); return;
        case OP_RESERVED1: if (z == '+' || z == '=') PRINT ('('); print (operand_0); PRINT (" ? "); print (operand_1); PRINT (" : "); print (operand_2); if (z == '+' || z == '=') PRINT (')'); return;
        case OP_RESERVED2: if (z == '+' || z == '=') PRINT ('('); print (operand_0); PRINT (" ? "); print (operand_2); PRINT (" : "); print (operand_1); if (z == '+' || z == '=') PRINT (')'); return;
        case OP_1ADD: print (operand_0, '+'); PRINT ("+1"); return;
        case OP_1SUB: print (operand_0, '+'); PRINT ("-1"); return;
        // case OP_2MUL:
        // case OP_2DIV:
        case OP_NEGATE: PRINT ("-"); print (operand_0, '+'); return;
        case OP_ABS: PRINT ("abs ("); print (operand_0); PRINT (")"); return;
        case OP_NOT: PRINT ("!"); print (operand_0, '+'); return;
        case OP_0NOTEQUAL: print (operand_0, '='); PRINT ("≠0"); return;
        case OP_ADD: print (operand_0, '+'); PRINT ("+"); print (operand_1, '+'); return;
        case OP_SUB: if (z == '+') PRINT ('('); print (operand_0, '+'); PRINT ("-"); print (operand_1, '+'); if (z == '+') PRINT (')'); return;
        // case OP_MUL:
        // case OP_DIV:
        // case OP_MOD:
        // case OP_LSHIFT:
        // case OP_RSHIFT:
        case OP_BOOLAND: print (operand_0, '='); PRINT ("∧"); print (operand_1, '='); return;
        case OP_BOOLOR: print (operand_0, '='); PRINT ("∨"); print (operand_1, '='); return;
        case OP_NUMEQUAL: print (operand_0); PRINT ("≟"); print (operand_1); return;
        case OP_NUMEQUALVERIFY: PRINT ("verify ("); print (operand_0, '='); PRINT ("≟"); print (operand_1, '='); PRINT (")"); return;
        case OP_NUMNOTEQUAL: print (operand_0, '='); PRINT ("≠"); print (operand_1, '='); return;
        case OP_LESSTHAN: print (operand_0, '+'); PRINT ("<"); print (operand_1, '+'); return;
        case OP_GREATERTHAN: print (operand_0, '+'); PRINT (">"); print (operand_1, '+'); return;
        case OP_LESSTHANOREQUAL: print (operand_0, '+'); PRINT ("≤"); print (operand_1, '+'); return;
        case OP_GREATERTHANOREQUAL: print (operand_0, '+'); PRINT ("≥"); print (operand_1, '+'); return;
        case OP_MIN: PRINT ("min ("); print (operand_0); PRINT (", "); print (operand_1); PRINT (')'); return;
        case OP_MAX: PRINT ("max ("); print (operand_0); PRINT (", "); print (operand_1); PRINT (')'); return;
        case OP_WITHIN: print (operand_1, '='); PRINT ("<"); print (operand_0, '='); PRINT ("≤"); print (operand_2, '='); return;
        case OP_RIPEMD160: PRINT ("ripemd160 ("); print (operand_0); PRINT (")"); return;
        case OP_SHA1: PRINT ("sha1 ("); print (operand_0); PRINT (")"); return;
        case OP_SHA256: PRINT ("sha256 ("); print (operand_0); PRINT (")"); return;
        case OP_HASH160: PRINT ("hash160 ("); print (operand_0); PRINT (")"); return;
        case OP_HASH256: PRINT ("hash256 ("); print (operand_0); PRINT (")"); return;
        // case OP_CODESEPARATOR:
        // case OP_CHECKSIG:
        // case OP_CHECKSIGVERIFY:
        // case OP_CHECKMULTISIG:
        // case OP_CHECKMULTISIGVERIFY:
        // case OP_NOP1:
        // case OP_NOP2:
        // case OP_NOP3:
        // case OP_NOP4:
        // case OP_NOP5:
        // case OP_NOP6:
        // case OP_NOP7:
        // case OP_NOP8:
        // case OP_NOP9:
        // case OP_NOP10:
        // case OP_CHECKSIGADD:

        default:
            if (opcode >= 0xC0)
            {
                auto divisor = 1000000000;
                auto number = __script_table [opcode - 0xC0];
                auto lz = true;
                while (divisor > 0)
                {
                    char digit = number / divisor % 10 + '0';
                    if (digit != '0' || lz == false)
                    {
                        PRINT (digit);
                        lz = false;
                    }
                    divisor /= 10;
                }
                if (lz == true) PRINT ('0');
            }
            else
            {
                PRINT (__OP__ [opcode]);
            }
            return;
    }

}

WORD __attribute__((export_name("compile"))) compile (BYTE * script, WORD size, char * stdout)
{
    :: stdout = stdout;

    // Transcode multi-byte opcodes
    preprocess (script, size);

    // Reset internal state
    op⁻¹ = 65535;
    op = 0;
    pc = 0;

    // Roll out program trace and leave the result on the stack
    WORD stack₀ [1000];
    WORD stack₁ [1000];
    auto [ap, ap⁻¹] = trace (stack₁, stack₀);

    if (:: stdout == stdout)
    {
        auto ap₀ = ap;
        while (ap₀ > 0)
        {
            print (stack₁ [-- ap₀]);
            PRINT ('\n');
        }
    }

    // TODO: Serialize to bitcoin script
    size = 0;
    for (auto opcode = __script [pc = 0]; opcode != OP_NOP; opcode = __script [++ pc])
    {
        if (opcode < 0xC0)
        {
            script [size ++] = opcode;
            continue;
        }
        auto value = __script_table [opcode - 0xC0];
        if (value < 256)
        {
            script [size ++] = 1;
            script [size ++] = value;
            continue;
        }
        if (value < 65536)
        {
            script [size ++] = 2;
            script [size ++] = value & 0xFF;
            script [size ++] = value >> 8;
            continue;
        }
        if (value < 16777216)
        {
            script [size ++] = 3;
            script [size ++] = value & 0xFF;
            script [size ++] = value >> 8 & 0xFF;
            script [size ++] = value >> 16;
            continue;
        }
        continue; // WARNING
    }
    return size;
}
