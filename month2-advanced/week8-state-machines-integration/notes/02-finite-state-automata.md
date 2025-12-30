# 02: Finite State Automata

## Finite State Automata (FSA)
A finite state automaton is a mathematical model of computation with a finite number of states and transitions between them.

## Deterministic Finite Automaton (DFA)
```c
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// DFA for recognizing strings ending with "ab"
typedef enum {
    STATE_S0,  // Initial state
    STATE_S1,  // Read 'a'
    STATE_S2   // Read "ab"
} DfaState;

typedef struct {
    DfaState current_state;
} DFA;

// Transition function: δ(state, input) -> next_state
DfaState dfa_transition(DfaState state, char input) {
    switch (state) {
        case STATE_S0:
            return (input == 'a') ? STATE_S1 : STATE_S0;
        case STATE_S1:
            return (input == 'b') ? STATE_S2 : STATE_S1;
        case STATE_S2:
            return (input == 'a') ? STATE_S1 : STATE_S0;
        default:
            return STATE_S0;
    }
}

// Check if current state is accepting
bool dfa_is_accepting(DfaState state) {
    return state == STATE_S2;
}

bool dfa_process_string(const char* str) {
    DfaState state = STATE_S0;

    printf("Processing string: \"%s\"\n", str);
    printf("State transitions: S0");

    for (size_t i = 0; i < strlen(str); i++) {
        state = dfa_transition(state, str[i]);
        printf(" -> S%d", state);
    }

    printf("\nResult: %s\n\n", dfa_is_accepting(state) ? "ACCEPTED" : "REJECTED");
    return dfa_is_accepting(state);
}

int main() {
    // Test strings
    dfa_process_string("ab");        // Should accept
    dfa_process_string("aab");       // Should accept
    dfa_process_string("abab");      // Should accept
    dfa_process_string("a");         // Should reject
    dfa_process_string("b");         // Should reject
    dfa_process_string("ba");        // Should reject
    dfa_process_string("abc");       // Should reject

    return 0;
}
```

## Non-Deterministic Finite Automaton (NFA)
```c
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// NFA for recognizing strings containing "ab" or "ba"
#define MAX_STATES 4

typedef struct {
    int states[MAX_STATES];  // Current set of states (bitset)
    int num_states;
} NFA;

// Initialize NFA to start state
void nfa_init(NFA* nfa) {
    nfa->states[0] = 0;  // Start state
    nfa->num_states = 1;
}

// Add state to current set
void nfa_add_state(NFA* nfa, int state) {
    for (int i = 0; i < nfa->num_states; i++) {
        if (nfa->states[i] == state) return;  // Already in set
    }
    nfa->states[nfa->num_states++] = state;
}

// Transition function for NFA (returns multiple possible states)
void nfa_transition(NFA* current, char input, NFA* next) {
    next->num_states = 0;

    for (int i = 0; i < current->num_states; i++) {
        int state = current->states[i];

        switch (state) {
            case 0:  // Start state
                if (input == 'a') nfa_add_state(next, 1);
                if (input == 'b') nfa_add_state(next, 2);
                break;
            case 1:  // Read 'a'
                if (input == 'b') nfa_add_state(next, 3);
                break;
            case 2:  // Read 'b'
                if (input == 'a') nfa_add_state(next, 3);
                break;
            case 3:  // Accepting state
                // Epsilon transitions or stay in accepting state
                nfa_add_state(next, 3);
                break;
        }
    }
}

// Check if any current state is accepting
bool nfa_is_accepting(const NFA* nfa) {
    for (int i = 0; i < nfa->num_states; i++) {
        if (nfa->states[i] == 3) return true;
    }
    return false;
}

bool nfa_process_string(const char* str) {
    NFA current, next;

    nfa_init(&current);
    printf("Processing: \"%s\"\n", str);
    printf("States: {0}");

    for (size_t i = 0; i < strlen(str); i++) {
        nfa_transition(&current, str[i], &next);
        current = next;

        printf(" -> {");
        for (int j = 0; j < current.num_states; j++) {
            printf("%d", current.states[j]);
            if (j < current.num_states - 1) printf(",");
        }
        printf("}");
    }

    bool accepted = nfa_is_accepting(&current);
    printf("\nResult: %s\n\n", accepted ? "ACCEPTED" : "REJECTED");
    return accepted;
}

int main() {
    nfa_process_string("ab");     // Should accept
    nfa_process_string("ba");     // Should accept
    nfa_process_string("abab");   // Should accept
    nfa_process_string("baba");   // Should accept
    nfa_process_string("a");      // Should reject
    nfa_process_string("b");      // Should reject
    nfa_process_string("aa");     // Should reject

    return 0;
}
```

## Regular Expression to NFA Conversion
```c
// Simple regex engine using NFA
// Supports: literals, concatenation, alternation (|), Kleene star (*)

typedef struct NFA_State NFA_State;

struct NFA_State {
    int id;
    NFA_State* transitions[256];  // One for each possible character
    bool is_accepting;
};

typedef struct {
    NFA_State* start;
    NFA_State* accept;
} NFA_Machine;

NFA_State* nfa_create_state() {
    NFA_State* state = calloc(1, sizeof(NFA_State));
    static int next_id = 0;
    state->id = next_id++;
    return state;
}

void nfa_add_transition(NFA_State* from, char symbol, NFA_State* to) {
    from->transitions[(unsigned char)symbol] = to;
}

// Create NFA for single character
NFA_Machine nfa_literal(char c) {
    NFA_State* start = nfa_create_state();
    NFA_State* accept = nfa_create_state();
    accept->is_accepting = true;

    nfa_add_transition(start, c, accept);

    return (NFA_Machine){start, accept};
}

// Create NFA for concatenation
NFA_Machine nfa_concat(NFA_Machine first, NFA_Machine second) {
    // Add epsilon transition from first.accept to second.start
    first.accept->transitions[0] = second.start;  // 0 represents epsilon
    first.accept->is_accepting = false;

    return (NFA_Machine){first.start, second.accept};
}

// Create NFA for alternation
NFA_Machine nfa_alternate(NFA_Machine first, NFA_Machine second) {
    NFA_State* new_start = nfa_create_state();
    NFA_State* new_accept = nfa_create_state();
    new_accept->is_accepting = true;

    // Epsilon transitions from new start
    new_start->transitions[0] = first.start;
    new_start->transitions[0] = second.start;  // Overwrites - need better implementation

    // This is simplified - real implementation needs proper epsilon handling
    first.accept->is_accepting = false;
    second.accept->is_accepting = false;

    return (NFA_Machine){new_start, new_accept};
}

bool nfa_matches(NFA_Machine nfa, const char* str) {
    NFA_State* current = nfa.start;

    for (size_t i = 0; str[i] && current; i++) {
        current = current->transitions[(unsigned char)str[i]];
    }

    return current && current->is_accepting;
}

int main() {
    // Create NFA for "ab"
    NFA_Machine nfa_a = nfa_literal('a');
    NFA_Machine nfa_b = nfa_literal('b');
    NFA_Machine nfa_ab = nfa_concat(nfa_a, nfa_b);

    printf("Testing regex \"ab\":\n");
    printf("\"ab\" matches: %s\n", nfa_matches(nfa_ab, "ab") ? "yes" : "no");
    printf("\"abc\" matches: %s\n", nfa_matches(nfa_ab, "abc") ? "yes" : "no");
    printf("\"a\" matches: %s\n", nfa_matches(nfa_ab, "a") ? "yes" : "no");

    return 0;
}
```

## Lexical Analysis with DFA
```c
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Token types for simple language
typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    char* lexeme;
    int line;
} Token;

// DFA states for lexical analysis
typedef enum {
    STATE_START,
    STATE_IN_IDENTIFIER,
    STATE_IN_NUMBER,
    STATE_DONE
} LexerState;

// Simple lexer DFA
Token get_next_token(const char** input) {
    LexerState state = STATE_START;
    const char* start = *input;
    Token token = {TOKEN_ERROR, NULL, 1};

    while (state != STATE_DONE) {
        char c = **input;

        switch (state) {
            case STATE_START:
                if (isalpha(c)) {
                    state = STATE_IN_IDENTIFIER;
                } else if (isdigit(c)) {
                    state = STATE_IN_NUMBER;
                } else {
                    switch (c) {
                        case '+': token.type = TOKEN_PLUS; state = STATE_DONE; break;
                        case '-': token.type = TOKEN_MINUS; state = STATE_DONE; break;
                        case '*': token.type = TOKEN_MULTIPLY; state = STATE_DONE; break;
                        case '/': token.type = TOKEN_DIVIDE; state = STATE_DONE; break;
                        case '(': token.type = TOKEN_LPAREN; state = STATE_DONE; break;
                        case ')': token.type = TOKEN_RPAREN; state = STATE_DONE; break;
                        case '\0': token.type = TOKEN_EOF; state = STATE_DONE; break;
                        case ' ': case '\t': case '\n':
                            (*input)++;  // Skip whitespace
                            start = *input;
                            break;
                        default:
                            token.type = TOKEN_ERROR;
                            state = STATE_DONE;
                            break;
                    }
                }
                break;

            case STATE_IN_IDENTIFIER:
                if (!isalnum(c)) {
                    state = STATE_DONE;
                    token.type = TOKEN_IDENTIFIER;
                }
                break;

            case STATE_IN_NUMBER:
                if (!isdigit(c)) {
                    state = STATE_DONE;
                    token.type = TOKEN_NUMBER;
                }
                break;

            case STATE_DONE:
                break;
        }

        if (state != STATE_DONE) {
            (*input)++;
        }
    }

    // Create lexeme
    size_t length = *input - start;
    if (length > 0) {
        token.lexeme = malloc(length + 1);
        strncpy(token.lexeme, start, length);
        token.lexeme[length] = '\0';
    }

    return token;
}

void tokenize_expression(const char* expression) {
    const char* input = expression;
    Token token;

    printf("Tokenizing: %s\n", expression);

    do {
        token = get_next_token(&input);
        printf("Token: %d, Lexeme: '%s'\n", token.type, token.lexeme ? token.lexeme : "NULL");
        free(token.lexeme);
    } while (token.type != TOKEN_EOF && token.type != TOKEN_ERROR);
}

int main() {
    tokenize_expression("x + 42 * (y - 1)");
    tokenize_expression("var1 = value2 + 123");
    return 0;
}
```

## Pushdown Automaton (PDA)
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Simple stack for PDA
typedef struct {
    char* data;
    size_t top;
    size_t capacity;
} Stack;

void stack_init(Stack* stack, size_t capacity) {
    stack->data = malloc(capacity);
    stack->top = 0;
    stack->capacity = capacity;
}

void stack_push(Stack* stack, char c) {
    if (stack->top < stack->capacity) {
        stack->data[stack->top++] = c;
    }
}

char stack_pop(Stack* stack) {
    return stack->top > 0 ? stack->data[--stack->top] : '\0';
}

char stack_peek(const Stack* stack) {
    return stack->top > 0 ? stack->data[stack->top - 1] : '\0';
}

// PDA for balanced parentheses
typedef enum {
    PDA_STATE_START,
    PDA_STATE_ACCEPT
} PDAState;

bool pda_process(const char* str) {
    Stack stack;
    stack_init(&stack, strlen(str) + 1);

    PDAState state = PDA_STATE_START;
    bool accepted = false;

    printf("Processing: \"%s\"\n", str);

    for (size_t i = 0; str[i]; i++) {
        char c = str[i];

        switch (state) {
            case PDA_STATE_START:
                if (c == '(') {
                    stack_push(&stack, c);
                    printf("Pushed '('\n");
                } else if (c == ')') {
                    if (stack_pop(&stack) != '(') {
                        printf("Unmatched ')'\n");
                        goto cleanup;
                    }
                    printf("Popped '('\n");
                }
                break;
        }
    }

    // Check if stack is empty (balanced)
    if (stack.top == 0) {
        accepted = true;
        printf("String is balanced\n");
    } else {
        printf("Unmatched '(' remaining\n");
    }

cleanup:
    free(stack.data);
    return accepted;
}

int main() {
    pda_process("()");           // Should accept
    pda_process("(())");         // Should accept
    pda_process("(()())");       // Should accept
    pda_process("(");            // Should reject
    pda_process(")");            // Should reject
    pda_process("(()");          // Should reject
    pda_process("())");          // Should reject

    return 0;
}
```

## Finite State Transducer (FST)
```c
#include <stdio.h>
#include <string.h>

// FST for case conversion (uppercase to lowercase)
typedef enum {
    FST_STATE_START,
    FST_STATE_PROCESSING
} FSTState;

typedef struct {
    FSTState state;
    char output[256];
    size_t output_len;
} FST;

// Transition function that also produces output
char fst_transition(FST* fst, char input) {
    char output = input;

    switch (fst->state) {
        case FST_STATE_START:
            if (input >= 'A' && input <= 'Z') {
                output = input + 32;  // Convert to lowercase
                fst->state = FST_STATE_PROCESSING;
            } else if (input != '\0') {
                fst->state = FST_STATE_PROCESSING;
            }
            break;

        case FST_STATE_PROCESSING:
            if (input >= 'A' && input <= 'Z') {
                output = input + 32;  // Convert to lowercase
            }
            break;
    }

    if (input != '\0') {
        fst->output[fst->output_len++] = output;
    }

    return output;
}

void fst_process_string(const char* input) {
    FST fst = {FST_STATE_START, {0}, 0};

    printf("Input:  \"%s\"\n", input);
    printf("Output: \"");

    for (size_t i = 0; input[i]; i++) {
        char output = fst_transition(&fst, input[i]);
        printf("%c", output);
    }

    fst_transition(&fst, '\0');  // Null terminate
    printf("\"\n\n");
}

int main() {
    fst_process_string("HELLO WORLD");
    fst_process_string("Hello World");
    fst_process_string("hello world");
    fst_process_string("MIXED case STRING");

    return 0;
}
```

## Applications of Finite Automata
### Text Processing
- Pattern matching (grep, regex engines)
- Lexical analysis (compilers)
- Text editors (syntax highlighting)
- Search engines (query processing)

### Network Protocols
- TCP state machine
- HTTP request/response parsing
- Packet classification
- Firewall rule matching

### Embedded Systems
- Sensor data validation
- Command parsing
- Device state management
- Communication protocol handling

### Game Development
- AI behavior trees
- Animation state machines
- Input handling
- Game state management

## Best Practices
- Keep automata simple and well-documented
- Test all possible transitions
- Use meaningful state and transition names
- Consider non-deterministic automata for complex patterns
- Implement proper error handling
- Document the language recognized/accepted
- Test edge cases thoroughly

## Performance Considerations
- DFA is faster than NFA for processing
- Minimize number of states when possible
- Use table-driven implementations for speed
- Consider memory usage for large automata
- Profile and optimize critical paths

## Common Pitfalls
- Missing transitions (undefined behavior)
- Incorrect accepting states
- Infinite loops in NFA processing
- Memory leaks in dynamic state allocation
- Not handling all possible inputs
- Race conditions in concurrent processing