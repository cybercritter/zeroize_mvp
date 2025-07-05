#ifndef ZEROIZE_H
#define ZEROIZE_H

/**
 * @file zeroize.h
 * @brief Provides functions and constants for securely zeroizing memory buffers.
 *
 * This header defines constants and functions for securely overwriting memory
 * regions with specific patterns, which is useful for removing sensitive data
 * from memory. It includes buffer size, alignment, and patterns for zeroization.
 *
 * Constants:
 *   ZEROIZE_ALIGNMENT       - Alignment requirement for zeroization (in bytes).
 *   ZEROIZE_PATTERN         - Pattern (0xA5) used to overwrite memory.
 *   ZEROIZE_PATTERN_REVERSE - Alternate pattern (0x5A) for overwriting memory.
 *
 * Functions:
 *   int zeroize(void *ptr, size_t size);
 *     Overwrites the memory region pointed to by ptr with a secure pattern.
 *     @param ptr  Pointer to the memory region to zeroize.
 *     @param size Size of the memory region in bytes.
 *     @return 0 on success, non-zero on failure.
 *
 *   bool is_zeroized(const void *ptr, size_t size);
 *     Checks if the memory region is zeroized (matches the zeroization pattern).
 *     @param ptr  Pointer to the memory region to check.
 *     @param size Size of the memory region in bytes.
 *     @return true if the region is zeroized, false otherwise.
 */

#include <stddef.h>                       // For size_t
#include <stdbool.h>                      // For bool type
#include <stdint.h> // For uint8_t type

const int ZEROIZE_PATTERN = 0xA5; // Pattern used to overwrite memory
const int ZEROIZE_PATTERN_REVERSE = 0x5A; // Alternate pattern for overwriting memory
const int ZEROIZE_ALIGNMENT = 4;          // Verify alignment is on a 4-byte boundary

#ifdef __cplusplus
extern "C"
{
#endif

  int8_t zeroize(void *ptr, size_t size);
  bool is_zeroized(const void *ptr, size_t size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif