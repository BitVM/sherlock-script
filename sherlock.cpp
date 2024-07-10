
typedef signed int LONG;
typedef signed short INT;
typedef unsigned char BYTE;
typedef unsigned short WORD;

const char * __0123456789 [ ] [10]
{
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
    "₀", "₁", "₂", "₃", "₄", "₅", "₆", "₇", "₈", "₉",
};

const char * __2147483648 [ ]
{
    "-2147483648",
    "₋₂₁₄₇₄₈₃₆₄₈",
};

char __stdout [24576] { };
WORD __buffer = 0;

const char * __attribute__((export_name("stdout"))) stdout (void)
{
    return __stdout;
}

WORD print (const char * c_str)
{
    for (WORD size = 0; true; __stdout [__buffer ++] = c_str [size ++])
    {
        if (c_str [size] == '\0') return size;
    }
}

WORD print (LONG num, bool sub = false)
{
    if (num == -2147483648) return print (__2147483648 [!! sub]); // 0x80000000

    WORD size = num < 0 ? num *= -1, print (sub ? "₋" : "-") : 0;

    if (num == 0) return print (__0123456789 [!! sub] [0]);

    for (LONG div = 1000000000; div > 0; div /= 10)
    {
        if (div <= num) size += print (__0123456789 [!! sub] [num / div % 10]);
    }

    return size;
}

WORD WARNING (const char * c_str)
{
    return print (" ERROR\n") + print (c_str) + print ("\n");
}

template <typename T, unsigned N> void memset (T (& mem) [N], T val)
{
    for (auto & ref : mem) ref = val;
}

template <typename T, unsigned N> void memcpy (T (& mem) [N], const T (& src) [N])
{
    for (auto & ref : mem) ref = src [& ref - mem];
}

template <typename T, unsigned N> void memmove (T (& mem) [N], signed Δ, unsigned ap)
{
    if (Δ == 0) return;
    // NOTE: Ｏ﹙n²﹚
    for (; Δ > 0; -- Δ) for (INT _ = ap - 1; _ > 0; -- _) mem [_] = mem [_ - 1];
    for (; Δ < 0; ++ Δ) for (INT _ = ap - 1; _ < N; ++ _) mem [_ - 1] = mem [_];
}

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

// OP_IF <=> conditional expression
// OP_NOTIF <=> conditional expression
// OP_RESERVED <=> unlocking variable

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
    memset (__script_table, static_cast <LONG> (-2147483648));
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
    // Allocate new variable
    auto op_reserved = [&] (WORD op₀⁻¹)
    {
        memmove (stack₁, 1, ++ ap);
        __trace [op⁻¹].opcode = OP_RESERVED;
        __trace [op⁻¹].reference_counter = 0;
        stack₁ [0] = op₀⁻¹ > op⁻¹ ? op₀⁻¹ : op⁻¹ --;
    };

    // Allocate temporary variable
    auto op_nop = [&] (WORD (& stack) [1000], WORD & ap₀)
    {
        memmove (stack, 1, ++ ap₀);
        __trace [op].opcode = OP_NOP;
        __trace [op].reference_counter = 0;
        stack [0] = op ++;
    };

    // Allocate temporary variable on altstack
    auto op_nop⁻¹ = [&] (WORD (& stack) [1000], WORD & ap₀⁻¹)
    {
        memmove (stack, -1, -- ap₀⁻¹);
        __trace [op].opcode = OP_NOP;
        __trace [op].reference_counter = 0;
        stack [999] = op ++;
    };

    // Initialize stack
    memcpy (stack₁, stack₀);

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
                    // Recursive scope execution
                    WORD __0 = stack₁ [-- ap];
                    ++ pc;
                    // Apply OP_IF or OP_NOTIF to stack₂
                    WORD stack₂ [1000];
                    auto op₀⁻¹ = op⁻¹;
                    auto Δ = trace (stack₂, stack₁, ap, ap⁻¹);
                    while (op₀⁻¹ > op⁻¹) op_reserved (op₀⁻¹ --);
                    if (__script [pc] == OP_ELSE)
                    {
                        ++ pc;
                        // Apply optional OP_ELSE to stack₁
                        WORD stack₂ [1000];
                        auto op₀⁻¹ = op⁻¹;
                        auto Δ = trace (stack₂, stack₁, ap, ap⁻¹);
                        while (op₀⁻¹ > op⁻¹) op_reserved (op₀⁻¹ --);
                        ap = Δ.ap;
                        ap⁻¹ = Δ.ap⁻¹;
                        memcpy (stack₁, stack₂);
                    }
                    if (__script [pc] != OP_ENDIF) return WARNING ("OP_ENDIF"), Δap { ap, ap⁻¹ };
                    // NOTE: __script [pc] must be OP_ENDIF here
                    // Adjust stack height
                    while (ap < Δ.ap) op_nop (stack₁, ap);
                    while (ap > Δ.ap) op_nop (stack₂, Δ.ap);
                    // Merge stack elements
                    for (WORD _ = 0; _ < ap; ++ _)
                    {
                        if (stack₁ [_] == stack₂ [_]) continue;
                        WORD __1 = stack₂ [_];
                        WORD __2 = stack₁ [_];
                        decltype (OP_TRUE) opcode⁻¹ = opcode == OP_IF ? OP_NOTIF : OP_IF;
                        // x₀ ? (x₀ ? x₁ : _) : x₂  <=>  x₀ ? x₁ : x₂
                        if (__trace [__1].opcode == opcode && __trace [__1].operand_0 == __0) __1 = __trace [__1].operand_1;
                        if (__trace [__2].opcode == opcode⁻¹ && __trace [__2].operand_0 == __0) __2 = __trace [__2].operand_1;
                        // x₀ ? x₁ : (x₀ ? _ : x₂)  <=>  x₀ ? x₁ : x₂
                        if (__trace [__1].opcode == opcode⁻¹ && __trace [__1].operand_0 == __0) __1 = __trace [__1].operand_2;
                        if (__trace [__2].opcode == opcode && __trace [__2].operand_0 == __0) __2 = __trace [__2].operand_2;
                        __trace [op].opcode = opcode;
                        __trace [op].reference_counter = 0;
                        __trace [op].operand_0 = __0; // condition
                        __trace [op].operand_1 = __1; // then
                        __trace [op].operand_2 = __2; // else
                        stack₁ [_] = op ++;
                    }
                    // Adjust altstack height
                    while (ap⁻¹ > Δ.ap⁻¹) op_nop⁻¹ (stack₁, ap⁻¹);
                    while (ap⁻¹ < Δ.ap⁻¹) op_nop⁻¹ (stack₂, Δ.ap⁻¹);
                    // Merge altstack elements
                    for (WORD _ = 999; _ > ap⁻¹; -- _)
                    {
                        if (stack₁ [_] == stack₂ [_]) continue;
                        WORD __1 = stack₂ [_];
                        WORD __2 = stack₁ [_];
                        decltype (OP_TRUE) opcode⁻¹ = opcode == OP_IF ? OP_NOTIF : OP_IF;
                        // x₀ ? (x₀ ? x₁ : _) : x₂  <=>  x₀ ? x₁ : x₂
                        if (__trace [__1].opcode == opcode && __trace [__1].operand_0 == __0) __1 = __trace [__1].operand_1;
                        if (__trace [__2].opcode == opcode⁻¹ && __trace [__2].operand_0 == __0) __2 = __trace [__2].operand_1;
                        // x₀ ? x₁ : (x₀ ? _ : x₂)  <=>  x₀ ? x₁ : x₂
                        if (__trace [__1].opcode == opcode⁻¹ && __trace [__1].operand_0 == __0) __1 = __trace [__1].operand_2;
                        if (__trace [__2].opcode == opcode && __trace [__2].operand_0 == __0) __2 = __trace [__2].operand_2;
                        __trace [op].opcode = opcode;
                        __trace [op].reference_counter = 0;
                        __trace [op].operand_0 = __0; // condition
                        __trace [op].operand_1 = __1; // then
                        __trace [op].operand_2 = __2; // else
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
                    if (Δ == -2147483648) return WARNING ("OP_PICK"), Δap { ap, ap⁻¹ };
                    while (ap <= Δ) op_reserved (op⁻¹);
                    stack₁ [ap - 1] = stack₁ [ap - Δ - 2];
                }
                continue;

            case OP_ROLL:
                if (ap == 0) op_reserved (op⁻¹);
                // NOTE: This only works for constant indices
                if (auto Δ = eval (stack₁ [-- ap]))
                {
                    if (Δ == -2147483648) return WARNING ("OP_ROLL"), Δap { ap, ap⁻¹ };
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
                if (opcode < 0xC0) return WARNING ("OP_INVALIDOPCODE"), Δap { ap, ap⁻¹ };
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

// Log trace expression
void __print (WORD trace, char z = '\0') // precedence
{
    auto opcode = __trace [trace].opcode;
    WORD operand_0 = __trace [trace].operand_0;
    WORD operand_1 = __trace [trace].operand_1;
    WORD operand_2 = __trace [trace].operand_2;

    switch (opcode)
    {
        case OP_0:
            print (0);
            return;

        // OP_PUSHDATA1 OP_PUSHDATA2 OP_PUSHDATA4

        case OP_1NEGATE:
            print (-1);
            return;

        case OP_RESERVED:
            print ("x");
            print (65535 - trace, true);
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
            print (opcode - OP_1 + 1);
            return;

        case OP_NOP:
            print ("∅");
            return;

        case OP_IF:
        case OP_NOTIF:
            print (z == '+' || z == '=' ? "(" : ""), __print (operand_0);
            print (" ? "), __print (opcode == OP_IF ? operand_1 : operand_2);
            print (" : "), __print (opcode == OP_NOTIF ? operand_1 : operand_2);
            print (z == '+' || z == '=' ? ")" : "");
            return;

        // OP_ELSE OP_ENDIF

        case OP_VERIFY:
            print ("verify ("), __print (operand_0);
            print (")");
            return;

        // OP_RETURN OP_DEPTH OP_SIZE

        case OP_EQUAL:
            print (z == '=' ? "(" : ""), __print (operand_0, '=');
            print ("≟"), __print (operand_1, '=');
            print (z == '=' ? ")" : "");
            return;

        case OP_EQUALVERIFY:
            print ("verify ("), __print (operand_0, '=');
            print ("≟"), __print (operand_1, '=');
            print (")");
            return;

        // OP_RESERVED1 OP_RESERVED2

        case OP_1ADD:
        case OP_1SUB:
            __print (operand_0, '+'), print (opcode == OP_1ADD ? "+1" : "-1");
            return;

        case OP_NEGATE:
            print ("-"), __print (operand_0, '+');
            return;

        case OP_ABS:
            print ("abs ("), __print (operand_0), print (")");
            return;

        case OP_NOT:
            print ("!"), __print (operand_0, '+');
            return;

        case OP_0NOTEQUAL:
            __print (operand_0, '='), print ("≠0");
            return;

        case OP_ADD:
        case OP_SUB:
            print (z == '+' ? "(" : ""),
            __print (operand_0, '+'), print (opcode == OP_ADD ? "+" : "-");
            __print (operand_1, '+');
            print (z == '+' ? ")" : "");
            return;

        case OP_BOOLAND:
        case OP_BOOLOR:
            __print (operand_0, '='), print (opcode == OP_BOOLAND ? "∧" : "∨");
            __print (operand_1, '=');
            return;

        case OP_NUMEQUAL:
            __print (operand_0), print ("≟");
            __print (operand_1);
            return;

        case OP_NUMEQUALVERIFY:
            print ("verify ("),
            __print (operand_0, '='), print ("≟");
            __print (operand_1, '='), print (")");
            return;

        case OP_NUMNOTEQUAL:
            __print (operand_0, '='), print ("≠");
            __print (operand_1, '=');
            return;

        case OP_LESSTHAN:
        case OP_GREATERTHAN:
            __print (operand_0, '+'), print (opcode == OP_LESSTHAN ? "<" : ">");
            __print (operand_1, '+');
            return;

        case OP_LESSTHANOREQUAL:
        case OP_GREATERTHANOREQUAL:
            __print (operand_0, '+'), print (opcode == OP_LESSTHANOREQUAL ? "≤" : "≥");
            __print (operand_1, '+');
            return;

        case OP_MIN:
        case OP_MAX:
            print (opcode == OP_MIN ? "min (" : "max ("), __print (operand_0), print (", "), __print (operand_1), print (")");
            return;

        case OP_WITHIN:
            __print (operand_1, '='), print ("<");
            __print (operand_0, '='), print ("≤");
            __print (operand_2, '=');
            return;

        case OP_RIPEMD160:
            print ("ripemd160 ("), __print (operand_0), print (")");
            return;

        case OP_SHA1:
        case OP_SHA256:
            print (opcode == OP_SHA1 ? "sha1 (" : "sha256 ("), __print (operand_0), print (")");
            return;

        case OP_HASH160:
        case OP_HASH256:
            print (opcode == OP_HASH160 ? "hash160 (" : "hash256 ("), __print (operand_0), print (")");
            return;

        // OP_CODESEPARATOR OP_CHECKSIG OP_CHECKSIGVERIFY OP_CHECKMULTISIG OP_CHECKMULTISIGVERIFY
        // OP_NOP1 OP_NOP2 OP_NOP3 OP_NOP4 OP_NOP5 OP_NOP6 OP_NOP7 OP_NOP8 OP_NOP9 OP_NOP10 OP_CHECKSIGADD

        default:
            if (opcode >= 0xC0) print (__script_table [opcode - 0xC0]);
            // WARNING: else
            return;
    }

}

//
// clang sherlock.cpp -Wno-mathematical-notation-identifier-extension --no-standard-libraries --target=wasm32 -Wl,--no-entry -o sherlock.wasm
//

WORD __attribute__((export_name("compile"))) compile (BYTE * script, WORD size)
{
    // Reset UTF-8 output buffer
    memset (__stdout, '\0');
    __buffer = 0;

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

    // Show resulting stack if there was no warning
    if (__stdout [0] == '\0') for (auto ap₀ = ap; ap₀ > 0; ) __print (stack₁ [-- ap₀]), print ("\n");

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
            script [size ++] = value & 0xFF;
            continue;
        }
        if (value < 65536)
        {
            script [size ++] = 2;
            script [size ++] = value & 0xFF; value >>= 8;
            script [size ++] = value & 0xFF;
            continue;
        }
        if (value < 16777216)
        {
            script [size ++] = 3;
            script [size ++] = value & 0xFF; value >>= 8;
            script [size ++] = value & 0xFF; value >>= 8;
            script [size ++] = value & 0xFF;
            continue;
        }
        script [size ++] = 4;
        script [size ++] = value & 0xFF; value >>= 8;
        script [size ++] = value & 0xFF; value >>= 8;
        script [size ++] = value & 0xFF; value >>= 8;
        script [size ++] = value & 0xFF;
    }
    return size;
}
