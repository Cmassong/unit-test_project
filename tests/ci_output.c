// ci_output.c
// This file provides a custom output character function for Unity test framework,
// used when running in environments (like CI or some embedded targets)
// where the default `_putchar` may not be available or linked correctly.

#include <stdio.h>

/*
 * Unity uses a function called `_putchar` by default for outputting test results.
 * This often causes linker errors in environments like CI, Linux, or non-embedded systems,
 * because `_putchar` is not a standard C function (it's usually used in embedded platforms).
 *
 * To avoid changing Unity's internals, we override the output character function
 * by defining the macro `UNITY_OUTPUT_CHAR` to point to this function.
 * That macro is passed via Makefile: `-DUNITY_OUTPUT_CHAR=ci_putchar`
 *
 * This way, Unity will call `ci_putchar()` instead of `_putchar()`,
 * and we forward it to the standard `putchar()` in `stdio.h`.
 */

int ci_putchar(int c) {
    return putchar(c);  // Just forward the character to standard output.
}
