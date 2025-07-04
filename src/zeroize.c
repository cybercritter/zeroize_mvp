/**
 * @file zeroize.c
 * @brief Implementation of memory zeroization and verification functions.
 *
 * This file provides functions to securely overwrite memory with a specific pattern
 * and to verify if a memory region has been zeroized.
 */

#include <zeroize.h>

/**
 * @brief Overwrites a memory region with a predefined zeroization pattern.
 *
 * This function securely sets each byte of the specified memory region to the
 * value defined by ZEROIZE_PATTERN. The use of a volatile pointer prevents the
 * compiler from optimizing out the memory write, which is important for security.
 *
 * @param ptr Pointer to the memory region to zeroize.
 * @param size Number of bytes to overwrite.
 * @return 0 on success, -1 if ptr is NULL or size is 0.
 */
int8_t zeroize(void *ptr, size_t size)
{
    int8_t error_code = 0; // Initialize error code

    if (ptr == NULL || size == 0)
    {
        error_code = -1; // Error: Invalid pointer or size
    }
    else
    {

        if (size % ZEROIZE_ALIGNMENT != 0)
        {
            error_code = -2; // Error: Size is not aligned
        }
    }

    if (error_code == 0)
    {

        // Use a volatile pointer to prevent compiler optimizations
        // that might skip the memory write operation.
        volatile unsigned char *p = (volatile unsigned char *)ptr;
        for (size_t i = 0; i < size; i++)
        {
            p[i] = ZEROIZE_PATTERN;
        }
    }

    return error_code;
}

/**
 * @brief Checks if a memory region is fully zeroized.
 *
 * This function verifies that every byte in the specified memory region matches
 * the ZEROIZE_PATTERN value.
 *
 * @param ptr Pointer to the memory region to check.
 * @param size Number of bytes to check.
 * @return true if all bytes are equal to ZEROIZE_PATTERN, false otherwise or if
 *         ptr is NULL or size is 0.
 */
bool is_zeroized(const void *ptr, size_t size)
{
    bool is_zeroized_flag = true; // Initialize to true

    if (ptr == NULL || size == 0)
    {
        is_zeroized_flag = false; // Error: Invalid pointer or size
    }

    if (size % ZEROIZE_ALIGNMENT != 0)
    {
        is_zeroized_flag = false; // Error: Size is not aligned
    }

    if (is_zeroized_flag != false)
    {
        const unsigned char *p = (const unsigned char *)ptr;
        for (size_t i = 0; i < size; i++)
        {
            if (p[i] != ZEROIZE_PATTERN)
            {
                is_zeroized_flag = false; // Memory is not zeroized
                break;                    // Exit loop early if a non-zeroized byte is found
            }
        }
    }
    return is_zeroized_flag; // Memory is zeroized
}