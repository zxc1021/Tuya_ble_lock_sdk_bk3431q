/**
 * \file config.h
 *
 * \brief Configuration with all cryptography features and no X.509 or TLS.
 *
 * This configuration is intended to prototype the PSA reference implementation.
 */
/*
 *  Copyright (C) 2006-2018, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of Mbed Crypto (https://tls.mbed.org)
 */

#ifndef MBEDCRYPTO_CONFIG_H
#define MBEDCRYPTO_CONFIG_H

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
#define _CRT_SECURE_NO_DEPRECATE 1
#endif

/**
 * \name SECTION: System support
 *
 * This section sets system specific settings.
 * \{
 */

/**
 * \def MBEDCRYPTO_HAVE_ASM
 *
 * The compiler has support for asm().
 *
 * Requires support for asm() in compiler.
 *
 * Used in:
 *      library/timing.c
 *      library/padlock.c
 *      include/mbedcrypto/bn_mul.h
 *
 * Comment to disable the use of assembly code.
 */
#define MBEDCRYPTO_HAVE_ASM

/**
 * \def MBEDCRYPTO_NO_UDBL_DIVISION
 *
 * The platform lacks support for double-width integer division (64-bit
 * division on a 32-bit platform, 128-bit division on a 64-bit platform).
 *
 * Used in:
 *      include/mbedcrypto/bignum.h
 *      library/bignum.c
 *
 * The bignum code uses double-width division to speed up some operations.
 * Double-width division is often implemented in software that needs to
 * be linked with the program. The presence of a double-width integer
 * type is usually detected automatically through preprocessor macros,
 * but the automatic detection cannot know whether the code needs to
 * and can be linked with an implementation of division for that type.
 * By default division is assumed to be usable if the type is present.
 * Uncomment this option to prevent the use of double-width division.
 *
 * Note that division for the native integer type is always required.
 * Furthermore, a 64-bit type is always required even on a 32-bit
 * platform, but it need not support multiplication or division. In some
 * cases it is also desirable to disable some double-width operations. For
 * example, if double-width division is implemented in software, disabling
 * it can reduce code size in some embedded targets.
 */
//#define MBEDCRYPTO_NO_UDBL_DIVISION

/**
 * \def MBEDCRYPTO_HAVE_SSE2
 *
 * CPU supports SSE2 instruction set.
 *
 * Uncomment if the CPU supports SSE2 (IA-32 specific).
 */
//#define MBEDCRYPTO_HAVE_SSE2

/**
 * \def MBEDCRYPTO_PLATFORM_MEMORY
 *
 * Enable the memory allocation layer.
 *
 * By default Mbed Crypto uses the system-provided calloc() and free().
 * This allows different allocators (self-implemented or provided) to be
 * provided to the platform abstraction layer.
 *
 * Enabling MBEDCRYPTO_PLATFORM_MEMORY without the
 * MBEDCRYPTO_PLATFORM_{FREE,CALLOC}_MACROs will provide
 * "mbedcrypto_platform_set_calloc_free()" allowing you to set an alternative calloc() and
 * free() function pointer at runtime.
 *
 * Enabling MBEDCRYPTO_PLATFORM_MEMORY and specifying
 * MBEDCRYPTO_PLATFORM_{CALLOC,FREE}_MACROs will allow you to specify the
 * alternate function at compile time.
 *
 * Requires: MBEDCRYPTO_PLATFORM_C
 *
 * Enable this layer to allow use of alternative memory allocators.
 */
//#define MBEDCRYPTO_PLATFORM_MEMORY

/**
 * \def MBEDCRYPTO_PLATFORM_NO_STD_FUNCTIONS
 *
 * Do not assign standard functions in the platform layer (e.g. calloc() to
 * MBEDCRYPTO_PLATFORM_STD_CALLOC and printf() to MBEDCRYPTO_PLATFORM_STD_PRINTF)
 *
 * This makes sure there are no linking errors on platforms that do not support
 * these functions. You will HAVE to provide alternatives, either at runtime
 * via the platform_set_xxx() functions or at compile time by setting
 * the MBEDCRYPTO_PLATFORM_STD_XXX defines, or enabling a
 * MBEDCRYPTO_PLATFORM_XXX_MACRO.
 *
 * Requires: MBEDCRYPTO_PLATFORM_C
 *
 * Uncomment to prevent default assignment of standard functions in the
 * platform layer.
 */
//#define MBEDCRYPTO_PLATFORM_NO_STD_FUNCTIONS

/**
 * \def MBEDCRYPTO_PLATFORM_EXIT_ALT
 *
 * MBEDCRYPTO_PLATFORM_XXX_ALT: Uncomment a macro to let Mbed Crypto support the
 * function in the platform abstraction layer.
 *
 * Example: In case you uncomment MBEDCRYPTO_PLATFORM_PRINTF_ALT, Mbed Crypto will
 * provide a function "mbedcrypto_platform_set_printf()" that allows you to set an
 * alternative printf function pointer.
 *
 * All these define require MBEDCRYPTO_PLATFORM_C to be defined!
 *
 * \note MBEDCRYPTO_PLATFORM_SNPRINTF_ALT is required on Windows;
 * it will be enabled automatically by check_config.h
 *
 * \warning MBEDCRYPTO_PLATFORM_XXX_ALT cannot be defined at the same time as
 * MBEDCRYPTO_PLATFORM_XXX_MACRO!
 *
 * Uncomment a macro to enable alternate implementation of specific base
 * platform function
 */
//#define MBEDCRYPTO_PLATFORM_EXIT_ALT
//#define MBEDCRYPTO_PLATFORM_FPRINTF_ALT
//#define MBEDCRYPTO_PLATFORM_PRINTF_ALT
//#define MBEDCRYPTO_PLATFORM_SNPRINTF_ALT
//#define MBEDCRYPTO_PLATFORM_NV_SEED_ALT
//#define MBEDCRYPTO_PLATFORM_SETUP_TEARDOWN_ALT

/**
 * \def MBEDCRYPTO_DEPRECATED_WARNING
 *
 * Mark deprecated functions so that they generate a warning if used.
 * Functions deprecated in one version will usually be removed in the next
 * version. You can enable this to help you prepare the transition to a new
 * major version by making sure your code is not using these functions.
 *
 * This only works with GCC and Clang. With other compilers, you may want to
 * use MBEDCRYPTO_DEPRECATED_REMOVED
 *
 * Uncomment to get warnings on using deprecated functions.
 */
//#define MBEDCRYPTO_DEPRECATED_WARNING

/**
 * \def MBEDCRYPTO_DEPRECATED_REMOVED
 *
 * Remove deprecated functions so that they generate an error if used.
 * Functions deprecated in one version will usually be removed in the next
 * version. You can enable this to help you prepare the transition to a new
 * major version by making sure your code is not using these functions.
 *
 * Uncomment to get errors on using deprecated functions.
 */
//#define MBEDCRYPTO_DEPRECATED_REMOVED

/* \} name SECTION: System support */

/**
 * \name SECTION: Mbed Crypto feature support
 *
 * This section sets support for features that are or are not needed
 * within the modules that are enabled.
 * \{
 */

/**
 * \def MBEDCRYPTO_AES_ALT
 *
 * MBEDCRYPTO__MODULE_NAME__ALT: Uncomment a macro to let Mbed Crypto use your
 * alternate core implementation of a symmetric crypto, an arithmetic or hash
 * module (e.g. platform specific assembly optimized implementations). Keep
 * in mind that the function prototypes should remain the same.
 *
 * This replaces the whole module. If you only want to replace one of the
 * functions, use one of the MBEDCRYPTO__FUNCTION_NAME__ALT flags.
 *
 * Example: In case you uncomment MBEDCRYPTO_AES_ALT, Mbed Crypto will no longer
 * provide the "struct mbedcrypto_aes_context" definition and omit the base
 * function declarations and implementations. "aes_alt.h" will be included from
 * "aes.h" to include the new function definitions.
 *
 * Uncomment a macro to enable alternate implementation of the corresponding
 * module.
 *
 * \warning   MD2, MD4, MD5, ARC4, DES and SHA-1 are considered weak and their
 *            use constitutes a security risk. If possible, we recommend
 *            avoiding dependencies on them, and considering stronger message
 *            digests and ciphers instead.
 *
 */
//#define MBEDCRYPTO_AES_ALT
//#define MBEDCRYPTO_ARC4_ALT
//#define MBEDCRYPTO_BLOWFISH_ALT
//#define MBEDCRYPTO_CAMELLIA_ALT
//#define MBEDCRYPTO_CCM_ALT
//#define MBEDCRYPTO_CMAC_ALT
//#define MBEDCRYPTO_DES_ALT
//#define MBEDCRYPTO_DHM_ALT
//#define MBEDCRYPTO_ECJPAKE_ALT
//#define MBEDCRYPTO_GCM_ALT
//#define MBEDCRYPTO_MD2_ALT
//#define MBEDCRYPTO_MD4_ALT
//#define MBEDCRYPTO_MD5_ALT
//#define MBEDCRYPTO_RIPEMD160_ALT
//#define MBEDCRYPTO_RSA_ALT
//#define MBEDCRYPTO_SHA1_ALT
//#define MBEDCRYPTO_SHA256_ALT
//#define MBEDCRYPTO_SHA512_ALT
//#define MBEDCRYPTO_XTEA_ALT
/*
 * When replacing the elliptic curve module, pleace consider, that it is
 * implemented with two .c files:
 *      - ecp.c
 *      - ecp_curves.c
 * You can replace them very much like all the other MBEDCRYPTO__MODULE_NAME__ALT
 * macros as described above. The only difference is that you have to make sure
 * that you provide functionality for both .c files.
 */
//#define MBEDCRYPTO_ECP_ALT

/**
 * \def MBEDCRYPTO_MD2_PROCESS_ALT
 *
 * MBEDCRYPTO__FUNCTION_NAME__ALT: Uncomment a macro to let Mbed Crypto use you
 * alternate core implementation of symmetric crypto or hash function. Keep in
 * mind that function prototypes should remain the same.
 *
 * This replaces only one function. The header file from Mbed Crypto is still
 * used, in contrast to the MBEDCRYPTO__MODULE_NAME__ALT flags.
 *
 * Example: In case you uncomment MBEDCRYPTO_SHA256_PROCESS_ALT, Mbed Crypto will
 * no longer provide the mbedcrypto_sha1_process() function, but it will still provide
 * the other function (using your mbedcrypto_sha1_process() function) and the definition
 * of mbedcrypto_sha1_context, so your implementation of mbedcrypto_sha1_process must be compatible
 * with this definition.
 *
 * \note Because of a signature change, the core AES encryption and decryption routines are
 *       currently named mbedcrypto_aes_internal_encrypt and mbedcrypto_aes_internal_decrypt,
 *       respectively. When setting up alternative implementations, these functions should
 *       be overriden, but the wrapper functions mbedcrypto_aes_decrypt and mbedcrypto_aes_encrypt
 *       must stay untouched.
 *
 * \note If you use the AES_xxx_ALT macros, then is is recommended to also set
 *       MBEDCRYPTO_AES_ROM_TABLES in order to help the linker garbage-collect the AES
 *       tables.
 *
 * Uncomment a macro to enable alternate implementation of the corresponding
 * function.
 *
 * \warning   MD2, MD4, MD5, DES and SHA-1 are considered weak and their use
 *            constitutes a security risk. If possible, we recommend avoiding
 *            dependencies on them, and considering stronger message digests
 *            and ciphers instead.
 *
 */
//#define MBEDCRYPTO_MD2_PROCESS_ALT
//#define MBEDCRYPTO_MD4_PROCESS_ALT
//#define MBEDCRYPTO_MD5_PROCESS_ALT
//#define MBEDCRYPTO_RIPEMD160_PROCESS_ALT
//#define MBEDCRYPTO_SHA1_PROCESS_ALT
//#define MBEDCRYPTO_SHA256_PROCESS_ALT
//#define MBEDCRYPTO_SHA512_PROCESS_ALT
//#define MBEDCRYPTO_DES_SETKEY_ALT
//#define MBEDCRYPTO_DES_CRYPT_ECB_ALT
//#define MBEDCRYPTO_DES3_CRYPT_ECB_ALT
//#define MBEDCRYPTO_AES_SETKEY_ENC_ALT
//#define MBEDCRYPTO_AES_SETKEY_DEC_ALT
//#define MBEDCRYPTO_AES_ENCRYPT_ALT
//#define MBEDCRYPTO_AES_DECRYPT_ALT
//#define MBEDCRYPTO_ECDH_GEN_PUBLIC_ALT
//#define MBEDCRYPTO_ECDH_COMPUTE_SHARED_ALT
//#define MBEDCRYPTO_ECDSA_VERIFY_ALT
//#define MBEDCRYPTO_ECDSA_SIGN_ALT
//#define MBEDCRYPTO_ECDSA_GENKEY_ALT

/**
 * \def MBEDCRYPTO_ECP_INTERNAL_ALT
 *
 * Expose a part of the internal interface of the Elliptic Curve Point module.
 *
 * MBEDCRYPTO_ECP__FUNCTION_NAME__ALT: Uncomment a macro to let Mbed Crypto use your
 * alternative core implementation of elliptic curve arithmetic. Keep in mind
 * that function prototypes should remain the same.
 *
 * This partially replaces one function. The header file from Mbed Crypto is still
 * used, in contrast to the MBEDCRYPTO_ECP_ALT flag. The original implementation
 * is still present and it is used for group structures not supported by the
 * alternative.
 *
 * Any of these options become available by defining MBEDCRYPTO_ECP_INTERNAL_ALT
 * and implementing the following functions:
 *      unsigned char mbedcrypto_internal_ecp_grp_capable(
 *          const mbedcrypto_ecp_group *grp )
 *      int  mbedcrypto_internal_ecp_init( const mbedcrypto_ecp_group *grp )
 *      void mbedcrypto_internal_ecp_deinit( const mbedcrypto_ecp_group *grp )
 * The mbedcrypto_internal_ecp_grp_capable function should return 1 if the
 * replacement functions implement arithmetic for the given group and 0
 * otherwise.
 * The functions mbedcrypto_internal_ecp_init and mbedcrypto_internal_ecp_deinit are
 * called before and after each point operation and provide an opportunity to
 * implement optimized set up and tear down instructions.
 *
 * Example: In case you uncomment MBEDCRYPTO_ECP_INTERNAL_ALT and
 * MBEDCRYPTO_ECP_DOUBLE_JAC_ALT, Mbed Crypto will still provide the ecp_double_jac
 * function, but will use your mbedcrypto_internal_ecp_double_jac if the group is
 * supported (your mbedcrypto_internal_ecp_grp_capable function returns 1 when
 * receives it as an argument). If the group is not supported then the original
 * implementation is used. The other functions and the definition of
 * mbedcrypto_ecp_group and mbedcrypto_ecp_point will not change, so your
 * implementation of mbedcrypto_internal_ecp_double_jac and
 * mbedcrypto_internal_ecp_grp_capable must be compatible with this definition.
 *
 * Uncomment a macro to enable alternate implementation of the corresponding
 * function.
 */
/* Required for all the functions in this section */
//#define MBEDCRYPTO_ECP_INTERNAL_ALT
/* Support for Weierstrass curves with Jacobi representation */
//#define MBEDCRYPTO_ECP_RANDOMIZE_JAC_ALT
//#define MBEDCRYPTO_ECP_ADD_MIXED_ALT
//#define MBEDCRYPTO_ECP_DOUBLE_JAC_ALT
//#define MBEDCRYPTO_ECP_NORMALIZE_JAC_MANY_ALT
//#define MBEDCRYPTO_ECP_NORMALIZE_JAC_ALT
/* Support for curves with Montgomery arithmetic */
//#define MBEDCRYPTO_ECP_DOUBLE_ADD_MXZ_ALT
//#define MBEDCRYPTO_ECP_RANDOMIZE_MXZ_ALT
//#define MBEDCRYPTO_ECP_NORMALIZE_MXZ_ALT

/**
 * \def MBEDCRYPTO_TEST_NULL_ENTROPY
 *
 * Enables testing and use of Mbed Crypto without any configured entropy sources.
 * This permits use of the library on platforms before an entropy source has
 * been integrated (see for example the MBEDCRYPTO_ENTROPY_HARDWARE_ALT or the
 * MBEDCRYPTO_ENTROPY_NV_SEED switches).
 *
 * WARNING! This switch MUST be disabled in production builds, and is suitable
 * only for development.
 * Enabling the switch negates any security provided by the library.
 *
 * Requires MBEDCRYPTO_ENTROPY_C, MBEDCRYPTO_NO_DEFAULT_ENTROPY_SOURCES
 *
 */
//#define MBEDCRYPTO_TEST_NULL_ENTROPY

/**
 * \def MBEDCRYPTO_ENTROPY_HARDWARE_ALT
 *
 * Uncomment this macro to let Mbed Crypto use your own implementation of a
 * hardware entropy collector.
 *
 * Your function must be called \c mbedcrypto_hardware_poll(), have the same
 * prototype as declared in entropy_poll.h, and accept NULL as first argument.
 *
 * Uncomment to use your own hardware entropy collector.
 */
//#define MBEDCRYPTO_ENTROPY_HARDWARE_ALT

/**
 * \def MBEDCRYPTO_AES_ROM_TABLES
 *
 * Use precomputed AES tables stored in ROM.
 *
 * Uncomment this macro to use precomputed AES tables stored in ROM.
 * Comment this macro to generate AES tables in RAM at runtime.
 *
 * Tradeoff: Using precomputed ROM tables reduces RAM usage by ~8kb
 * (or ~2kb if \c MBEDCRYPTO_AES_FEWER_TABLES is used) and reduces the
 * initialization time before the first AES operation can be performed.
 * It comes at the cost of additional ~8kb ROM use (resp. ~2kb if \c
 * MBEDCRYPTO_AES_FEWER_TABLES below is used), and potentially degraded
 * performance if ROM access is slower than RAM access.
 *
 * This option is independent of \c MBEDCRYPTO_AES_FEWER_TABLES.
 *
 */
//#define MBEDCRYPTO_AES_ROM_TABLES

/**
 * \def MBEDCRYPTO_AES_FEWER_TABLES
 *
 * Use less ROM/RAM for AES tables.
 *
 * Uncommenting this macro omits 75% of the AES tables from
 * ROM / RAM (depending on the value of \c MBEDCRYPTO_AES_ROM_TABLES)
 * by computing their values on the fly during operations
 * (the tables are entry-wise rotations of one another).
 *
 * Tradeoff: Uncommenting this reduces the RAM / ROM footprint
 * by ~6kb but at the cost of more arithmetic operations during
 * runtime. Specifically, one has to compare 4 accesses within
 * different tables to 4 accesses with additional arithmetic
 * operations within the same table. The performance gain/loss
 * depends on the system and memory details.
 *
 * This option is independent of \c MBEDCRYPTO_AES_ROM_TABLES.
 *
 */
//#define MBEDCRYPTO_AES_FEWER_TABLES

/**
 * \def MBEDCRYPTO_CAMELLIA_SMALL_MEMORY
 *
 * Use less ROM for the Camellia implementation (saves about 768 bytes).
 *
 * Uncomment this macro to use less memory for Camellia.
 */
//#define MBEDCRYPTO_CAMELLIA_SMALL_MEMORY

/**
 * \def MBEDCRYPTO_CIPHER_MODE_CBC
 *
 * Enable Cipher Block Chaining mode (CBC) for symmetric ciphers.
 */
#define MBEDCRYPTO_CIPHER_MODE_CBC

/**
 * \def MBEDCRYPTO_CIPHER_MODE_CFB
 *
 * Enable Cipher Feedback mode (CFB) for symmetric ciphers.
 */
#define MBEDCRYPTO_CIPHER_MODE_CFB

/**
 * \def MBEDCRYPTO_CIPHER_MODE_CTR
 *
 * Enable Counter Block Cipher mode (CTR) for symmetric ciphers.
 */
#define MBEDCRYPTO_CIPHER_MODE_CTR

/**
 * \def MBEDCRYPTO_CIPHER_PADDING_PKCS7
 *
 * MBEDCRYPTO_CIPHER_PADDING_XXX: Uncomment or comment macros to add support for
 * specific padding modes in the cipher layer with cipher modes that support
 * padding (e.g. CBC)
 *
 * If you disable all padding modes, only full blocks can be used with CBC.
 *
 * Enable padding modes in the cipher layer.
 */
#define MBEDCRYPTO_CIPHER_PADDING_PKCS7
#define MBEDCRYPTO_CIPHER_PADDING_ONE_AND_ZEROS
#define MBEDCRYPTO_CIPHER_PADDING_ZEROS_AND_LEN
#define MBEDCRYPTO_CIPHER_PADDING_ZEROS

/**
 * \def MBEDCRYPTO_ECP_DP_SECP192R1_ENABLED
 *
 * MBEDCRYPTO_ECP_XXXX_ENABLED: Enables specific curves within the Elliptic Curve
 * module.  By default all supported curves are enabled.
 *
 * Comment macros to disable the curve and functions for it
 */
#define MBEDCRYPTO_ECP_DP_SECP192R1_ENABLED
#define MBEDCRYPTO_ECP_DP_SECP224R1_ENABLED
#define MBEDCRYPTO_ECP_DP_SECP256R1_ENABLED
#define MBEDCRYPTO_ECP_DP_SECP384R1_ENABLED
#define MBEDCRYPTO_ECP_DP_SECP521R1_ENABLED
#define MBEDCRYPTO_ECP_DP_SECP192K1_ENABLED
#define MBEDCRYPTO_ECP_DP_SECP224K1_ENABLED
#define MBEDCRYPTO_ECP_DP_SECP256K1_ENABLED
#define MBEDCRYPTO_ECP_DP_BP256R1_ENABLED
#define MBEDCRYPTO_ECP_DP_BP384R1_ENABLED
#define MBEDCRYPTO_ECP_DP_BP512R1_ENABLED
#define MBEDCRYPTO_ECP_DP_CURVE25519_ENABLED
#define MBEDCRYPTO_ECP_DP_CURVE448_ENABLED

/**
 * \def MBEDCRYPTO_ECP_NIST_OPTIM
 *
 * Enable specific 'modulo p' routines for each NIST prime.
 * Depending on the prime and architecture, makes operations 4 to 8 times
 * faster on the corresponding curve.
 *
 * Comment this macro to disable NIST curves optimisation.
 */
#define MBEDCRYPTO_ECP_NIST_OPTIM

/**
 * \def MBEDCRYPTO_ECDSA_DETERMINISTIC
 *
 * Enable deterministic ECDSA (RFC 6979).
 * Standard ECDSA is "fragile" in the sense that lack of entropy when signing
 * may result in a compromise of the long-term signing key. This is avoided by
 * the deterministic variant.
 *
 * Requires: MBEDCRYPTO_HMAC_DRBG_C
 *
 * Comment this macro to disable deterministic ECDSA.
 */
#define MBEDCRYPTO_ECDSA_DETERMINISTIC

/**
 * \def MBEDCRYPTO_PK_PARSE_EC_EXTENDED
 *
 * Enhance support for reading EC keys using variants of SEC1 not allowed by
 * RFC 5915 and RFC 5480.
 *
 * Currently this means parsing the SpecifiedECDomain choice of EC
 * parameters (only known groups are supported, not arbitrary domains, to
 * avoid validation issues).
 *
 * Disable if you only need to support RFC 5915 + 5480 key formats.
 */
#define MBEDCRYPTO_PK_PARSE_EC_EXTENDED

/**
 * \def MBEDCRYPTO_ERROR_STRERROR_DUMMY
 *
 * Enable a dummy error function to make use of mbedcrypto_strerror() in
 * third party libraries easier when MBEDCRYPTO_ERROR_C is disabled
 * (no effect when MBEDCRYPTO_ERROR_C is enabled).
 *
 * You can safely disable this if MBEDCRYPTO_ERROR_C is enabled, or if you're
 * not using mbedcrypto_strerror() or error_strerror() in your application.
 *
 * Disable if you run into name conflicts and want to really remove the
 * mbedcrypto_strerror()
 */
#define MBEDCRYPTO_ERROR_STRERROR_DUMMY

/**
 * \def MBEDCRYPTO_GENPRIME
 *
 * Enable the prime-number generation code.
 *
 * Requires: MBEDCRYPTO_BIGNUM_C
 */
#define MBEDCRYPTO_GENPRIME

/**
 * \def MBEDCRYPTO_FS_IO
 *
 * Enable functions that use the filesystem.
 */
#define MBEDCRYPTO_FS_IO

/**
 * \def MBEDCRYPTO_NO_DEFAULT_ENTROPY_SOURCES
 *
 * Do not add default entropy sources. These are the platform specific,
 * mbedcrypto_timing_hardclock and HAVEGE based poll functions.
 *
 * This is useful to have more control over the added entropy sources in an
 * application.
 *
 * Uncomment this macro to prevent loading of default entropy functions.
 */
//#define MBEDCRYPTO_NO_DEFAULT_ENTROPY_SOURCES

/**
 * \def MBEDCRYPTO_NO_PLATFORM_ENTROPY
 *
 * Do not use built-in platform entropy functions.
 * This is useful if your platform does not support
 * standards like the /dev/urandom or Windows CryptoAPI.
 *
 * Uncomment this macro to disable the built-in platform entropy functions.
 */
//#define MBEDCRYPTO_NO_PLATFORM_ENTROPY

/**
 * \def MBEDCRYPTO_ENTROPY_FORCE_SHA256
 *
 * Force the entropy accumulator to use a SHA-256 accumulator instead of the
 * default SHA-512 based one (if both are available).
 *
 * Requires: MBEDCRYPTO_SHA256_C
 *
 * On 32-bit systems SHA-256 can be much faster than SHA-512. Use this option
 * if you have performance concerns.
 *
 * This option is only useful if both MBEDCRYPTO_SHA256_C and
 * MBEDCRYPTO_SHA512_C are defined. Otherwise the available hash module is used.
 */
//#define MBEDCRYPTO_ENTROPY_FORCE_SHA256

/**
 * \def MBEDCRYPTO_ENTROPY_NV_SEED
 *
 * Enable the non-volatile (NV) seed file-based entropy source.
 * (Also enables the NV seed read/write functions in the platform layer)
 *
 * This is crucial (if not required) on systems that do not have a
 * cryptographic entropy source (in hardware or kernel) available.
 *
 * Requires: MBEDCRYPTO_ENTROPY_C, MBEDCRYPTO_PLATFORM_C
 *
 * \note The read/write functions that are used by the entropy source are
 *       determined in the platform layer, and can be modified at runtime and/or
 *       compile-time depending on the flags (MBEDCRYPTO_PLATFORM_NV_SEED_*) used.
 *
 * \note If you use the default implementation functions that read a seedfile
 *       with regular fopen(), please make sure you make a seedfile with the
 *       proper name (defined in MBEDCRYPTO_PLATFORM_STD_NV_SEED_FILE) and at
 *       least MBEDCRYPTO_ENTROPY_BLOCK_SIZE bytes in size that can be read from
 *       and written to or you will get an entropy source error! The default
 *       implementation will only use the first MBEDCRYPTO_ENTROPY_BLOCK_SIZE
 *       bytes from the file.
 *
 * \note The entropy collector will write to the seed file before entropy is
 *       given to an external source, to update it.
 */
//#define MBEDCRYPTO_ENTROPY_NV_SEED

/**
 * \def MBEDCRYPTO_MEMORY_DEBUG
 *
 * Enable debugging of buffer allocator memory issues. Automatically prints
 * (to stderr) all (fatal) messages on memory allocation issues. Enables
 * function for 'debug output' of allocated memory.
 *
 * Requires: MBEDCRYPTO_MEMORY_BUFFER_ALLOC_C
 *
 * Uncomment this macro to let the buffer allocator print out error messages.
 */
//#define MBEDCRYPTO_MEMORY_DEBUG

/**
 * \def MBEDCRYPTO_MEMORY_BACKTRACE
 *
 * Include backtrace information with each allocated block.
 *
 * Requires: MBEDCRYPTO_MEMORY_BUFFER_ALLOC_C
 *           GLIBC-compatible backtrace() an backtrace_symbols() support
 *
 * Uncomment this macro to include backtrace information
 */
//#define MBEDCRYPTO_MEMORY_BACKTRACE

/**
 * \def MBEDCRYPTO_PK_RSA_ALT_SUPPORT
 *
 * Support external private RSA keys (eg from a HSM) in the PK layer.
 *
 * Comment this macro to disable support for external private RSA keys.
 */
#define MBEDCRYPTO_PK_RSA_ALT_SUPPORT

/**
 * \def MBEDCRYPTO_PKCS1_V15
 *
 * Enable support for PKCS#1 v1.5 encoding.
 *
 * Requires: MBEDCRYPTO_RSA_C
 *
 * This enables support for PKCS#1 v1.5 operations.
 */
#define MBEDCRYPTO_PKCS1_V15

/**
 * \def MBEDCRYPTO_PKCS1_V21
 *
 * Enable support for PKCS#1 v2.1 encoding.
 *
 * Requires: MBEDCRYPTO_MD_C, MBEDCRYPTO_RSA_C
 *
 * This enables support for RSAES-OAEP and RSASSA-PSS operations.
 */
#define MBEDCRYPTO_PKCS1_V21

/**
 * \def MBEDCRYPTO_PSA_CRYPTO_SPM
 *
 * When MBEDCRYPTO_PSA_CRYPTO_SPM is defined, the code is built for SPM (Secure
 * Partition Manager) integration which separates the code into two parts: a
 * NSPE (Non-Secure Process Environment) and an SPE (Secure Process
 * Environment).
 *
 * Module:  library/psa_crypto.c
 * Requires: MBEDCRYPTO_PSA_CRYPTO_C
 *
 */
//#define MBEDCRYPTO_PSA_CRYPTO_SPM

/**
 * \def MBEDCRYPTO_RSA_NO_CRT
 *
 * Do not use the Chinese Remainder Theorem for the RSA private operation.
 *
 * Uncomment this macro to disable the use of CRT in RSA.
 *
 */
//#define MBEDCRYPTO_RSA_NO_CRT

/**
 * \def MBEDCRYPTO_SELF_TEST
 *
 * Enable the checkup functions (*_self_test).
 */
#define MBEDCRYPTO_SELF_TEST

/**
 * \def MBEDCRYPTO_SHA256_SMALLER
 *
 * Enable an implementation of SHA-256 that has lower ROM footprint but also
 * lower performance.
 *
 * The default implementation is meant to be a reasonnable compromise between
 * performance and size. This version optimizes more aggressively for size at
 * the expense of performance. Eg on Cortex-M4 it reduces the size of
 * mbedcrypto_sha256_process() from ~2KB to ~0.5KB for a performance hit of about
 * 30%.
 *
 * Uncomment to enable the smaller implementation of SHA256.
 */
//#define MBEDCRYPTO_SHA256_SMALLER

/**
 * \def MBEDCRYPTO_THREADING_ALT
 *
 * Provide your own alternate threading implementation.
 *
 * Requires: MBEDCRYPTO_THREADING_C
 *
 * Uncomment this to allow your own alternate threading implementation.
 */
//#define MBEDCRYPTO_THREADING_ALT

/**
 * \def MBEDCRYPTO_THREADING_PTHREAD
 *
 * Enable the pthread wrapper layer for the threading layer.
 *
 * Requires: MBEDCRYPTO_THREADING_C
 *
 * Uncomment this to enable pthread mutexes.
 */
//#define MBEDCRYPTO_THREADING_PTHREAD

/**
 * \def MBEDCRYPTO_VERSION_FEATURES
 *
 * Allow run-time checking of compile-time enabled features. Thus allowing users
 * to check at run-time if the library is for instance compiled with threading
 * support via mbedcrypto_version_check_feature().
 *
 * Requires: MBEDCRYPTO_VERSION_C
 *
 * Comment this to disable run-time checking and save ROM space
 */
#define MBEDCRYPTO_VERSION_FEATURES

/* \} name SECTION: Mbed Crypto feature support */

/**
 * \name SECTION: Mbed Crypto modules
 *
 * This section enables or disables entire modules in Mbed Crypto
 * \{
 */

/**
 * \def MBEDCRYPTO_AESNI_C
 *
 * Enable AES-NI support on x86-64.
 *
 * Module:  library/aesni.c
 * Caller:  library/aes.c
 *
 * Requires: MBEDCRYPTO_HAVE_ASM
 *
 * This modules adds support for the AES-NI instructions on x86-64
 */
#define MBEDCRYPTO_AESNI_C

/**
 * \def MBEDCRYPTO_AES_C
 *
 * Enable the AES block cipher.
 *
 * Module:  library/aes.c
 * Caller:  library/ssl_tls.c
 *          library/pem.c
 *          library/ctr_drbg.c
 *
 * This module enables the following ciphersuites (if other requisites are
 * enabled as well):
 *      MBEDCRYPTO_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA
 *      MBEDCRYPTO_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA
 *      MBEDCRYPTO_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA
 *      MBEDCRYPTO_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA
 *      MBEDCRYPTO_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256
 *      MBEDCRYPTO_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384
 *      MBEDCRYPTO_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256
 *      MBEDCRYPTO_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384
 *      MBEDCRYPTO_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256
 *      MBEDCRYPTO_TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384
 *      MBEDCRYPTO_TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256
 *      MBEDCRYPTO_TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384
 *      MBEDCRYPTO_TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384
 *      MBEDCRYPTO_TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
 *      MBEDCRYPTO_TLS_DHE_RSA_WITH_AES_256_GCM_SHA384
 *      MBEDCRYPTO_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384
 *      MBEDCRYPTO_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384
 *      MBEDCRYPTO_TLS_DHE_RSA_WITH_AES_256_CBC_SHA256
 *      MBEDCRYPTO_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA
 *      MBEDCRYPTO_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA
 *      MBEDCRYPTO_TLS_DHE_RSA_WITH_AES_256_CBC_SHA
 *      MBEDCRYPTO_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256
 *      MBEDCRYPTO_TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256
 *      MBEDCRYPTO_TLS_DHE_RSA_WITH_AES_128_GCM_SHA256
 *      MBEDCRYPTO_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
 *      MBEDCRYPTO_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256
 *      MBEDCRYPTO_TLS_DHE_RSA_WITH_AES_128_CBC_SHA256
 *      MBEDCRYPTO_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA
 *      MBEDCRYPTO_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA
 *      MBEDCRYPTO_TLS_DHE_RSA_WITH_AES_128_CBC_SHA
 *      MBEDCRYPTO_TLS_DHE_PSK_WITH_AES_256_GCM_SHA384
 *      MBEDCRYPTO_TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA384
 *      MBEDCRYPTO_TLS_DHE_PSK_WITH_AES_256_CBC_SHA384
 *      MBEDCRYPTO_TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA
 *      MBEDCRYPTO_TLS_DHE_PSK_WITH_AES_256_CBC_SHA
 *      MBEDCRYPTO_TLS_DHE_PSK_WITH_AES_128_GCM_SHA256
 *      MBEDCRYPTO_TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA256
 *      MBEDCRYPTO_TLS_DHE_PSK_WITH_AES_128_CBC_SHA256
 *      MBEDCRYPTO_TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA
 *      MBEDCRYPTO_TLS_DHE_PSK_WITH_AES_128_CBC_SHA
 *      MBEDCRYPTO_TLS_RSA_WITH_AES_256_GCM_SHA384
 *      MBEDCRYPTO_TLS_RSA_WITH_AES_256_CBC_SHA256
 *      MBEDCRYPTO_TLS_RSA_WITH_AES_256_CBC_SHA
 *      MBEDCRYPTO_TLS_RSA_WITH_AES_128_GCM_SHA256
 *      MBEDCRYPTO_TLS_RSA_WITH_AES_128_CBC_SHA256
 *      MBEDCRYPTO_TLS_RSA_WITH_AES_128_CBC_SHA
 *      MBEDCRYPTO_TLS_RSA_PSK_WITH_AES_256_GCM_SHA384
 *      MBEDCRYPTO_TLS_RSA_PSK_WITH_AES_256_CBC_SHA384
 *      MBEDCRYPTO_TLS_RSA_PSK_WITH_AES_256_CBC_SHA
 *      MBEDCRYPTO_TLS_RSA_PSK_WITH_AES_128_GCM_SHA256
 *      MBEDCRYPTO_TLS_RSA_PSK_WITH_AES_128_CBC_SHA256
 *      MBEDCRYPTO_TLS_RSA_PSK_WITH_AES_128_CBC_SHA
 *      MBEDCRYPTO_TLS_PSK_WITH_AES_256_GCM_SHA384
 *      MBEDCRYPTO_TLS_PSK_WITH_AES_256_CBC_SHA384
 *      MBEDCRYPTO_TLS_PSK_WITH_AES_256_CBC_SHA
 *      MBEDCRYPTO_TLS_PSK_WITH_AES_128_GCM_SHA256
 *      MBEDCRYPTO_TLS_PSK_WITH_AES_128_CBC_SHA256
 *      MBEDCRYPTO_TLS_PSK_WITH_AES_128_CBC_SHA
 *
 * PEM_PARSE uses AES for decrypting encrypted keys.
 */
#define MBEDCRYPTO_AES_C

/**
 * \def MBEDCRYPTO_ARC4_C
 *
 * Enable the ARCFOUR stream cipher.
 *
 * Module:  library/arc4.c
 * Caller:  library/ssl_tls.c
 *
 * This module enables the following ciphersuites (if other requisites are
 * enabled as well):
 *      MBEDCRYPTO_TLS_ECDH_ECDSA_WITH_RC4_128_SHA
 *      MBEDCRYPTO_TLS_ECDH_RSA_WITH_RC4_128_SHA
 *      MBEDCRYPTO_TLS_ECDHE_ECDSA_WITH_RC4_128_SHA
 *      MBEDCRYPTO_TLS_ECDHE_RSA_WITH_RC4_128_SHA
 *      MBEDCRYPTO_TLS_ECDHE_PSK_WITH_RC4_128_SHA
 *      MBEDCRYPTO_TLS_DHE_PSK_WITH_RC4_128_SHA
 *      MBEDCRYPTO_TLS_RSA_WITH_RC4_128_SHA
 *      MBEDCRYPTO_TLS_RSA_WITH_RC4_128_MD5
 *      MBEDCRYPTO_TLS_RSA_PSK_WITH_RC4_128_SHA
 *      MBEDCRYPTO_TLS_PSK_WITH_RC4_128_SHA
 *
 * \warning   ARC4 is considered a weak cipher and its use constitutes a
 *            security risk. If possible, we recommend avoidng dependencies on
 *            it, and considering stronger ciphers instead.
 *
 */
#define MBEDCRYPTO_ARC4_C

/**
 * \def MBEDCRYPTO_ASN1_PARSE_C
 *
 * Enable the generic ASN1 parser.
 *
 * Module:  library/asn1.c
 * Caller:  library/x509.c
 *          library/dhm.c
 *          library/pkcs12.c
 *          library/pkcs5.c
 *          library/pkparse.c
 */
#define MBEDCRYPTO_ASN1_PARSE_C

/**
 * \def MBEDCRYPTO_ASN1_WRITE_C
 *
 * Enable the generic ASN1 writer.
 *
 * Module:  library/asn1write.c
 * Caller:  library/ecdsa.c
 *          library/pkwrite.c
 *          library/x509_create.c
 *          library/x509write_crt.c
 *          library/x509write_csr.c
 */
#define MBEDCRYPTO_ASN1_WRITE_C

/**
 * \def MBEDCRYPTO_BASE64_C
 *
 * Enable the Base64 module.
 *
 * Module:  library/base64.c
 * Caller:  library/pem.c
 *
 * This module is required for PEM support (required by X.509).
 */
#define MBEDCRYPTO_BASE64_C

/**
 * \def MBEDCRYPTO_BIGNUM_C
 *
 * Enable the multi-precision integer library.
 *
 * Module:  library/bignum.c
 * Caller:  library/dhm.c
 *          library/ecp.c
 *          library/ecdsa.c
 *          library/rsa.c
 *          library/rsa_internal.c
 *          library/ssl_tls.c
 *
 * This module is required for RSA, DHM and ECC (ECDH, ECDSA) support.
 */
#define MBEDCRYPTO_BIGNUM_C

/**
 * \def MBEDCRYPTO_BLOWFISH_C
 *
 * Enable the Blowfish block cipher.
 *
 * Module:  library/blowfish.c
 */
#define MBEDCRYPTO_BLOWFISH_C

/**
 * \def MBEDCRYPTO_CAMELLIA_C
 *
 * Enable the Camellia block cipher.
 *
 * Module:  library/camellia.c
 * Caller:  library/ssl_tls.c
 *
 * This module enables the following ciphersuites (if other requisites are
 * enabled as well):
 *      MBEDCRYPTO_TLS_ECDH_ECDSA_WITH_CAMELLIA_128_CBC_SHA256
 *      MBEDCRYPTO_TLS_ECDH_ECDSA_WITH_CAMELLIA_256_CBC_SHA384
 *      MBEDCRYPTO_TLS_ECDH_RSA_WITH_CAMELLIA_128_CBC_SHA256
 *      MBEDCRYPTO_TLS_ECDH_RSA_WITH_CAMELLIA_256_CBC_SHA384
 *      MBEDCRYPTO_TLS_ECDH_ECDSA_WITH_CAMELLIA_128_GCM_SHA256
 *      MBEDCRYPTO_TLS_ECDH_ECDSA_WITH_CAMELLIA_256_GCM_SHA384
 *      MBEDCRYPTO_TLS_ECDH_RSA_WITH_CAMELLIA_128_GCM_SHA256
 *      MBEDCRYPTO_TLS_ECDH_RSA_WITH_CAMELLIA_256_GCM_SHA384
 *      MBEDCRYPTO_TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_GCM_SHA384
 *      MBEDCRYPTO_TLS_ECDHE_RSA_WITH_CAMELLIA_256_GCM_SHA384
 *      MBEDCRYPTO_TLS_DHE_RSA_WITH_CAMELLIA_256_GCM_SHA384
 *      MBEDCRYPTO_TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_CBC_SHA384
 *      MBEDCRYPTO_TLS_ECDHE_RSA_WITH_CAMELLIA_256_CBC_SHA384
 *      MBEDCRYPTO_TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA256
 *      MBEDCRYPTO_TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA
 *      MBEDCRYPTO_TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_GCM_SHA256
 *      MBEDCRYPTO_TLS_ECDHE_RSA_WITH_CAMELLIA_128_GCM_SHA256
 *      MBEDCRYPTO_TLS_DHE_RSA_WITH_CAMELLIA_128_GCM_SHA256
 *      MBEDCRYPTO_TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_CBC_SHA256
 *      MBEDCRYPTO_TLS_ECDHE_RSA_WITH_CAMELLIA_128_CBC_SHA256
 *      MBEDCRYPTO_TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA256
 *      MBEDCRYPTO_TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA
 *      MBEDCRYPTO_TLS_DHE_PSK_WITH_CAMELLIA_256_GCM_SHA384
 *      MBEDCRYPTO_TLS_ECDHE_PSK_WITH_CAMELLIA_256_CBC_SHA384
 *      MBEDCRYPTO_TLS_DHE_PSK_WITH_CAMELLIA_256_CBC_SHA384
 *      MBEDCRYPTO_TLS_DHE_PSK_WITH_CAMELLIA_128_GCM_SHA256
 *      MBEDCRYPTO_TLS_DHE_PSK_WITH_CAMELLIA_128_CBC_SHA256
 *      MBEDCRYPTO_TLS_ECDHE_PSK_WITH_CAMELLIA_128_CBC_SHA256
 *      MBEDCRYPTO_TLS_RSA_WITH_CAMELLIA_256_GCM_SHA384
 *      MBEDCRYPTO_TLS_RSA_WITH_CAMELLIA_256_CBC_SHA256
 *      MBEDCRYPTO_TLS_RSA_WITH_CAMELLIA_256_CBC_SHA
 *      MBEDCRYPTO_TLS_RSA_WITH_CAMELLIA_128_GCM_SHA256
 *      MBEDCRYPTO_TLS_RSA_WITH_CAMELLIA_128_CBC_SHA256
 *      MBEDCRYPTO_TLS_RSA_WITH_CAMELLIA_128_CBC_SHA
 *      MBEDCRYPTO_TLS_RSA_PSK_WITH_CAMELLIA_256_GCM_SHA384
 *      MBEDCRYPTO_TLS_RSA_PSK_WITH_CAMELLIA_256_CBC_SHA384
 *      MBEDCRYPTO_TLS_RSA_PSK_WITH_CAMELLIA_128_GCM_SHA256
 *      MBEDCRYPTO_TLS_RSA_PSK_WITH_CAMELLIA_128_CBC_SHA256
 *      MBEDCRYPTO_TLS_PSK_WITH_CAMELLIA_256_GCM_SHA384
 *      MBEDCRYPTO_TLS_PSK_WITH_CAMELLIA_256_CBC_SHA384
 *      MBEDCRYPTO_TLS_PSK_WITH_CAMELLIA_128_GCM_SHA256
 *      MBEDCRYPTO_TLS_PSK_WITH_CAMELLIA_128_CBC_SHA256
 */
#define MBEDCRYPTO_CAMELLIA_C

/**
 * \def MBEDCRYPTO_CCM_C
 *
 * Enable the Counter with CBC-MAC (CCM) mode for 128-bit block cipher.
 *
 * Module:  library/ccm.c
 *
 * Requires: MBEDCRYPTO_AES_C or MBEDCRYPTO_CAMELLIA_C
 *
 * This module enables the AES-CCM ciphersuites, if other requisites are
 * enabled as well.
 */
#define MBEDCRYPTO_CCM_C

/**
 * \def MBEDCRYPTO_CIPHER_C
 *
 * Enable the generic cipher layer.
 *
 * Module:  library/cipher.c
 * Caller:  library/ssl_tls.c
 *
 * Uncomment to enable generic cipher wrappers.
 */
#define MBEDCRYPTO_CIPHER_C

/**
 * \def MBEDCRYPTO_CMAC_C
 *
 * Enable the CMAC (Cipher-based Message Authentication Code) mode for block
 * ciphers.
 *
 * Module:  library/cmac.c
 *
 * Requires: MBEDCRYPTO_AES_C or MBEDCRYPTO_DES_C
 *
 */
#define MBEDCRYPTO_CMAC_C

/**
 * \def MBEDCRYPTO_CTR_DRBG_C
 *
 * Enable the CTR_DRBG AES-256-based random generator.
 *
 * Module:  library/ctr_drbg.c
 * Caller:
 *
 * Requires: MBEDCRYPTO_AES_C
 *
 * This module provides the CTR_DRBG AES-256 random number generator.
 */
#define MBEDCRYPTO_CTR_DRBG_C

/**
 * \def MBEDCRYPTO_DES_C
 *
 * Enable the DES block cipher.
 *
 * Module:  library/des.c
 * Caller:  library/pem.c
 *          library/ssl_tls.c
 *
 * This module enables the following ciphersuites (if other requisites are
 * enabled as well):
 *      MBEDCRYPTO_TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA
 *      MBEDCRYPTO_TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA
 *      MBEDCRYPTO_TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA
 *      MBEDCRYPTO_TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA
 *      MBEDCRYPTO_TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA
 *      MBEDCRYPTO_TLS_ECDHE_PSK_WITH_3DES_EDE_CBC_SHA
 *      MBEDCRYPTO_TLS_DHE_PSK_WITH_3DES_EDE_CBC_SHA
 *      MBEDCRYPTO_TLS_RSA_WITH_3DES_EDE_CBC_SHA
 *      MBEDCRYPTO_TLS_RSA_PSK_WITH_3DES_EDE_CBC_SHA
 *      MBEDCRYPTO_TLS_PSK_WITH_3DES_EDE_CBC_SHA
 *
 * PEM_PARSE uses DES/3DES for decrypting encrypted keys.
 *
 * \warning   DES is considered a weak cipher and its use constitutes a
 *            security risk. We recommend considering stronger ciphers instead.
 */
#define MBEDCRYPTO_DES_C

/**
 * \def MBEDCRYPTO_DHM_C
 *
 * Enable the Diffie-Hellman-Merkle module.
 *
 * Module:  library/dhm.c
 * Caller:  library/ssl_cli.c
 *          library/ssl_srv.c
 *
 * This module is used by the following key exchanges:
 *      DHE-RSA, DHE-PSK
 *
 * \warning    Using DHE constitutes a security risk as it
 *             is not possible to validate custom DH parameters.
 *             If possible, it is recommended users should consider
 *             preferring other methods of key exchange.
 *             See dhm.h for more details.
 *
 */
#define MBEDCRYPTO_DHM_C

/**
 * \def MBEDCRYPTO_ECDH_C
 *
 * Enable the elliptic curve Diffie-Hellman library.
 *
 * Module:  library/ecdh.c
 * Caller:  library/ssl_cli.c
 *          library/ssl_srv.c
 *
 * This module is used by the following key exchanges:
 *      ECDHE-ECDSA, ECDHE-RSA, DHE-PSK
 *
 * Requires: MBEDCRYPTO_ECP_C
 */
#define MBEDCRYPTO_ECDH_C

/**
 * \def MBEDCRYPTO_ECDSA_C
 *
 * Enable the elliptic curve DSA library.
 *
 * Module:  library/ecdsa.c
 * Caller:
 *
 * This module is used by the following key exchanges:
 *      ECDHE-ECDSA
 *
 * Requires: MBEDCRYPTO_ECP_C, MBEDCRYPTO_ASN1_WRITE_C, MBEDCRYPTO_ASN1_PARSE_C
 */
#define MBEDCRYPTO_ECDSA_C

/**
 * \def MBEDCRYPTO_ECJPAKE_C
 *
 * Enable the elliptic curve J-PAKE library.
 *
 * \warning This is currently experimental. EC J-PAKE support is based on the
 * Thread v1.0.0 specification; incompatible changes to the specification
 * might still happen. For this reason, this is disabled by default.
 *
 * Module:  library/ecjpake.c
 * Caller:
 *
 * This module is used by the following key exchanges:
 *      ECJPAKE
 *
 * Requires: MBEDCRYPTO_ECP_C, MBEDCRYPTO_MD_C
 */
#define MBEDCRYPTO_ECJPAKE_C

/**
 * \def MBEDCRYPTO_ECP_C
 *
 * Enable the elliptic curve over GF(p) library.
 *
 * Module:  library/ecp.c
 * Caller:  library/ecdh.c
 *          library/ecdsa.c
 *          library/ecjpake.c
 *
 * Requires: MBEDCRYPTO_BIGNUM_C and at least one MBEDCRYPTO_ECP_DP_XXX_ENABLED
 */
#define MBEDCRYPTO_ECP_C

/**
 * \def MBEDCRYPTO_ENTROPY_C
 *
 * Enable the platform-specific entropy code.
 *
 * Module:  library/entropy.c
 * Caller:
 *
 * Requires: MBEDCRYPTO_SHA512_C or MBEDCRYPTO_SHA256_C
 *
 * This module provides a generic entropy pool
 */
#define MBEDCRYPTO_ENTROPY_C

/**
 * \def MBEDCRYPTO_ERROR_C
 *
 * Enable error code to error string conversion.
 *
 * Module:  library/error.c
 * Caller:
 *
 * This module enables mbedcrypto_strerror().
 */
#define MBEDCRYPTO_ERROR_C

/**
 * \def MBEDCRYPTO_GCM_C
 *
 * Enable the Galois/Counter Mode (GCM) for AES.
 *
 * Module:  library/gcm.c
 *
 * Requires: MBEDCRYPTO_AES_C or MBEDCRYPTO_CAMELLIA_C
 *
 * This module enables the AES-GCM and CAMELLIA-GCM ciphersuites, if other
 * requisites are enabled as well.
 */
#define MBEDCRYPTO_GCM_C

/**
 * \def MBEDCRYPTO_HMAC_DRBG_C
 *
 * Enable the HMAC_DRBG random generator.
 *
 * Module:  library/hmac_drbg.c
 * Caller:
 *
 * Requires: MBEDCRYPTO_MD_C
 *
 * Uncomment to enable the HMAC_DRBG random number geerator.
 */
#define MBEDCRYPTO_HMAC_DRBG_C

/**
 * \def MBEDCRYPTO_MD_C
 *
 * Enable the generic message digest layer.
 *
 * Module:  library/md.c
 * Caller:
 *
 * Uncomment to enable generic message digest wrappers.
 */
#define MBEDCRYPTO_MD_C

/**
 * \def MBEDCRYPTO_MD2_C
 *
 * Enable the MD2 hash algorithm.
 *
 * Module:  library/md2.c
 * Caller:
 *
 * Uncomment to enable support for (rare) MD2-signed X.509 certs.
 *
 * \warning   MD2 is considered a weak message digest and its use constitutes a
 *            security risk. If possible, we recommend avoiding dependencies on
 *            it, and considering stronger message digests instead.
 *
 */
#define MBEDCRYPTO_MD2_C

/**
 * \def MBEDCRYPTO_MD4_C
 *
 * Enable the MD4 hash algorithm.
 *
 * Module:  library/md4.c
 * Caller:
 *
 * Uncomment to enable support for (rare) MD4-signed X.509 certs.
 *
 * \warning   MD4 is considered a weak message digest and its use constitutes a
 *            security risk. If possible, we recommend avoiding dependencies on
 *            it, and considering stronger message digests instead.
 *
 */
#define MBEDCRYPTO_MD4_C

/**
 * \def MBEDCRYPTO_MD5_C
 *
 * Enable the MD5 hash algorithm.
 *
 * Module:  library/md5.c
 * Caller:  library/md.c
 *          library/pem.c
 *          library/ssl_tls.c
 *
 * This module is required for SSL/TLS up to version 1.1, and for TLS 1.2
 * depending on the handshake parameters. Further, it is used for checking
 * MD5-signed certificates, and for PBKDF1 when decrypting PEM-encoded
 * encrypted keys.
 *
 * \warning   MD5 is considered a weak message digest and its use constitutes a
 *            security risk. If possible, we recommend avoiding dependencies on
 *            it, and considering stronger message digests instead.
 *
 */
#define MBEDCRYPTO_MD5_C

/**
 * \def MBEDCRYPTO_MEMORY_BUFFER_ALLOC_C
 *
 * Enable the buffer allocator implementation that makes use of a (stack)
 * based buffer to 'allocate' dynamic memory. (replaces calloc() and free()
 * calls)
 *
 * Module:  library/memory_buffer_alloc.c
 *
 * Requires: MBEDCRYPTO_PLATFORM_C
 *           MBEDCRYPTO_PLATFORM_MEMORY (to use it within Mbed Crypto)
 *
 * Enable this module to enable the buffer memory allocator.
 */
//#define MBEDCRYPTO_MEMORY_BUFFER_ALLOC_C

/**
 * \def MBEDCRYPTO_OID_C
 *
 * Enable the OID database.
 *
 * Module:  library/oid.c
 * Caller:  library/asn1write.c
 *          library/pkcs5.c
 *          library/pkparse.c
 *          library/pkwrite.c
 *          library/rsa.c
 *          library/x509.c
 *          library/x509_create.c
 *          library/x509_crl.c
 *          library/x509_crt.c
 *          library/x509_csr.c
 *          library/x509write_crt.c
 *          library/x509write_csr.c
 *
 * This modules translates between OIDs and internal values.
 */
#define MBEDCRYPTO_OID_C

/**
 * \def MBEDCRYPTO_PADLOCK_C
 *
 * Enable VIA Padlock support on x86.
 *
 * Module:  library/padlock.c
 * Caller:  library/aes.c
 *
 * Requires: MBEDCRYPTO_HAVE_ASM
 *
 * This modules adds support for the VIA PadLock on x86.
 */
//#define MBEDCRYPTO_PADLOCK_C

/**
 * \def MBEDCRYPTO_PEM_PARSE_C
 *
 * Enable PEM decoding / parsing.
 *
 * Module:  library/pem.c
 * Caller:  library/dhm.c
 *          library/pkparse.c
 *          library/x509_crl.c
 *          library/x509_crt.c
 *          library/x509_csr.c
 *
 * Requires: MBEDCRYPTO_BASE64_C
 *
 * This modules adds support for decoding / parsing PEM files.
 */
#define MBEDCRYPTO_PEM_PARSE_C

/**
 * \def MBEDCRYPTO_PEM_WRITE_C
 *
 * Enable PEM encoding / writing.
 *
 * Module:  library/pem.c
 * Caller:  library/pkwrite.c
 *          library/x509write_crt.c
 *          library/x509write_csr.c
 *
 * Requires: MBEDCRYPTO_BASE64_C
 *
 * This modules adds support for encoding / writing PEM files.
 */
#define MBEDCRYPTO_PEM_WRITE_C

/**
 * \def MBEDCRYPTO_PK_C
 *
 * Enable the generic public (asymetric) key layer.
 *
 * Module:  library/pk.c
 * Caller:  library/ssl_tls.c
 *          library/ssl_cli.c
 *          library/ssl_srv.c
 *
 * Requires: MBEDCRYPTO_RSA_C or MBEDCRYPTO_ECP_C
 *
 * Uncomment to enable generic public key wrappers.
 */
#define MBEDCRYPTO_PK_C

/**
 * \def MBEDCRYPTO_PK_PARSE_C
 *
 * Enable the generic public (asymetric) key parser.
 *
 * Module:  library/pkparse.c
 * Caller:  library/x509_crt.c
 *          library/x509_csr.c
 *
 * Requires: MBEDCRYPTO_PK_C
 *
 * Uncomment to enable generic public key parse functions.
 */
#define MBEDCRYPTO_PK_PARSE_C

/**
 * \def MBEDCRYPTO_PK_WRITE_C
 *
 * Enable the generic public (asymetric) key writer.
 *
 * Module:  library/pkwrite.c
 * Caller:  library/x509write.c
 *
 * Requires: MBEDCRYPTO_PK_C
 *
 * Uncomment to enable generic public key write functions.
 */
#define MBEDCRYPTO_PK_WRITE_C

/**
 * \def MBEDCRYPTO_PKCS5_C
 *
 * Enable PKCS#5 functions.
 *
 * Module:  library/pkcs5.c
 *
 * Requires: MBEDCRYPTO_MD_C
 *
 * This module adds support for the PKCS#5 functions.
 */
#define MBEDCRYPTO_PKCS5_C

/**
 * \def MBEDCRYPTO_PKCS11_C
 *
 * Enable wrapper for PKCS#11 smartcard support.
 *
 * Module:  library/pkcs11.c
 * Caller:  library/pk.c
 *
 * Requires: MBEDCRYPTO_PK_C
 *
 * This module enables SSL/TLS PKCS #11 smartcard support.
 * Requires the presence of the PKCS#11 helper library (libpkcs11-helper)
 */
//#define MBEDCRYPTO_PKCS11_C

/**
 * \def MBEDCRYPTO_PKCS12_C
 *
 * Enable PKCS#12 PBE functions.
 * Adds algorithms for parsing PKCS#8 encrypted private keys
 *
 * Module:  library/pkcs12.c
 * Caller:  library/pkparse.c
 *
 * Requires: MBEDCRYPTO_ASN1_PARSE_C, MBEDCRYPTO_CIPHER_C, MBEDCRYPTO_MD_C
 * Can use:  MBEDCRYPTO_ARC4_C
 *
 * This module enables PKCS#12 functions.
 */
#define MBEDCRYPTO_PKCS12_C

/**
 * \def MBEDCRYPTO_PLATFORM_C
 *
 * Enable the platform abstraction layer that allows you to re-assign
 * functions like calloc(), free(), snprintf(), printf(), fprintf(), exit().
 *
 * Enabling MBEDCRYPTO_PLATFORM_C enables to use of MBEDCRYPTO_PLATFORM_XXX_ALT
 * or MBEDCRYPTO_PLATFORM_XXX_MACRO directives, allowing the functions mentioned
 * above to be specified at runtime or compile time respectively.
 *
 * \note This abstraction layer must be enabled on Windows (including MSYS2)
 * as other module rely on it for a fixed snprintf implementation.
 *
 * Module:  library/platform.c
 * Caller:  Most other .c files
 *
 * This module enables abstraction of common (libc) functions.
 */
#define MBEDCRYPTO_PLATFORM_C

/**
 * \def MBEDCRYPTO_PSA_CRYPTO_C
 *
 * Enable the Platform Security Architecture cryptography API.
 *
 * Module:  library/psa_crypto.c
 *
 * Requires: MBEDCRYPTO_CTR_DRBG_C, MBEDCRYPTO_ENTROPY_C
 *
 */
#define MBEDCRYPTO_PSA_CRYPTO_C

/**
 * \def MBEDCRYPTO_RIPEMD160_C
 *
 * Enable the RIPEMD-160 hash algorithm.
 *
 * Module:  library/ripemd160.c
 * Caller:  library/md.c
 *
 */
#define MBEDCRYPTO_RIPEMD160_C

/**
 * \def MBEDCRYPTO_RSA_C
 *
 * Enable the RSA public-key cryptosystem.
 *
 * Module:  library/rsa.c
 *          library/rsa_internal.c
 * Caller:  library/ssl_cli.c
 *          library/ssl_srv.c
 *          library/ssl_tls.c
 *          library/x509.c
 *
 * This module is used by the following key exchanges:
 *      RSA, DHE-RSA, ECDHE-RSA, RSA-PSK
 *
 * Requires: MBEDCRYPTO_BIGNUM_C, MBEDCRYPTO_OID_C
 */
#define MBEDCRYPTO_RSA_C

/**
 * \def MBEDCRYPTO_SHA1_C
 *
 * Enable the SHA1 cryptographic hash algorithm.
 *
 * Module:  library/sha1.c
 * Caller:  library/md.c
 *          library/ssl_cli.c
 *          library/ssl_srv.c
 *          library/ssl_tls.c
 *          library/x509write_crt.c
 *
 * This module is required for SSL/TLS up to version 1.1, for TLS 1.2
 * depending on the handshake parameters, and for SHA1-signed certificates.
 *
 * \warning   SHA-1 is considered a weak message digest and its use constitutes
 *            a security risk. If possible, we recommend avoiding dependencies
 *            on it, and considering stronger message digests instead.
 *
 */
#define MBEDCRYPTO_SHA1_C

/**
 * \def MBEDCRYPTO_SHA256_C
 *
 * Enable the SHA-224 and SHA-256 cryptographic hash algorithms.
 *
 * Module:  library/sha256.c
 * Caller:  library/entropy.c
 *          library/md.c
 *          library/ssl_cli.c
 *          library/ssl_srv.c
 *          library/ssl_tls.c
 *
 * This module adds support for SHA-224 and SHA-256.
 * This module is required for the SSL/TLS 1.2 PRF function.
 */
#define MBEDCRYPTO_SHA256_C

/**
 * \def MBEDCRYPTO_SHA512_C
 *
 * Enable the SHA-384 and SHA-512 cryptographic hash algorithms.
 *
 * Module:  library/sha512.c
 * Caller:  library/entropy.c
 *          library/md.c
 *          library/ssl_cli.c
 *          library/ssl_srv.c
 *
 * This module adds support for SHA-384 and SHA-512.
 */
#define MBEDCRYPTO_SHA512_C

/**
 * \def MBEDCRYPTO_THREADING_C
 *
 * Enable the threading abstraction layer.
 * By default Mbed Crypto assumes it is used in a non-threaded environment or that
 * contexts are not shared between threads. If you do intend to use contexts
 * between threads, you will need to enable this layer to prevent race
 * conditions. See also our Knowledge Base article about threading:
 * https://tls.mbed.org/kb/development/thread-safety-and-multi-threading
 *
 * Module:  library/threading.c
 *
 * This allows different threading implementations (self-implemented or
 * provided).
 *
 * You will have to enable either MBEDCRYPTO_THREADING_ALT or
 * MBEDCRYPTO_THREADING_PTHREAD.
 *
 * Enable this layer to allow use of mutexes within Mbed Crypto
 */
//#define MBEDCRYPTO_THREADING_C

/**
 * \def MBEDCRYPTO_VERSION_C
 *
 * Enable run-time version information.
 *
 * Module:  library/version.c
 *
 * This module provides run-time version information.
 */
#define MBEDCRYPTO_VERSION_C

/**
 * \def MBEDCRYPTO_XTEA_C
 *
 * Enable the XTEA block cipher.
 *
 * Module:  library/xtea.c
 * Caller:
 */
#define MBEDCRYPTO_XTEA_C

/* \} name SECTION: Mbed Crypto modules */

/**
 * \name SECTION: Module configuration options
 *
 * This section allows for the setting of module specific sizes and
 * configuration options. The default values are already present in the
 * relevant header files and should suffice for the regular use cases.
 *
 * Our advice is to enable options and change their values here
 * only if you have a good reason and know the consequences.
 *
 * Please check the respective header file for documentation on these
 * parameters (to prevent duplicate documentation).
 * \{
 */

/* MPI / BIGNUM options */
//#define MBEDCRYPTO_MPI_WINDOW_SIZE            6 /**< Maximum windows size used. */
//#define MBEDCRYPTO_MPI_MAX_SIZE            1024 /**< Maximum number of bytes for usable MPIs. */

/* CTR_DRBG options */
//#define MBEDCRYPTO_CTR_DRBG_ENTROPY_LEN               48 /**< Amount of entropy used per seed by default (48 with SHA-512, 32 with SHA-256) */
//#define MBEDCRYPTO_CTR_DRBG_RESEED_INTERVAL        10000 /**< Interval before reseed is performed by default */
//#define MBEDCRYPTO_CTR_DRBG_MAX_INPUT                256 /**< Maximum number of additional input bytes */
//#define MBEDCRYPTO_CTR_DRBG_MAX_REQUEST             1024 /**< Maximum number of requested bytes per call */
//#define MBEDCRYPTO_CTR_DRBG_MAX_SEED_INPUT           384 /**< Maximum size of (re)seed buffer */

/* HMAC_DRBG options */
//#define MBEDCRYPTO_HMAC_DRBG_RESEED_INTERVAL   10000 /**< Interval before reseed is performed by default */
//#define MBEDCRYPTO_HMAC_DRBG_MAX_INPUT           256 /**< Maximum number of additional input bytes */
//#define MBEDCRYPTO_HMAC_DRBG_MAX_REQUEST        1024 /**< Maximum number of requested bytes per call */
//#define MBEDCRYPTO_HMAC_DRBG_MAX_SEED_INPUT      384 /**< Maximum size of (re)seed buffer */

/* ECP options */
//#define MBEDCRYPTO_ECP_MAX_BITS             521 /**< Maximum bit size of groups */
//#define MBEDCRYPTO_ECP_WINDOW_SIZE            6 /**< Maximum window size used */
//#define MBEDCRYPTO_ECP_FIXED_POINT_OPTIM      1 /**< Enable fixed-point speed-up */

/* Entropy options */
//#define MBEDCRYPTO_ENTROPY_MAX_SOURCES                20 /**< Maximum number of sources supported */
//#define MBEDCRYPTO_ENTROPY_MAX_GATHER                128 /**< Maximum amount requested from entropy sources */
//#define MBEDCRYPTO_ENTROPY_MIN_HARDWARE               32 /**< Default minimum number of bytes required for the hardware entropy source mbedcrypto_hardware_poll() before entropy is released */

/* Memory buffer allocator options */
//#define MBEDCRYPTO_MEMORY_ALIGN_MULTIPLE      4 /**< Align on multiples of this value */

/* Platform options */
//#define MBEDCRYPTO_PLATFORM_STD_MEM_HDR   <stdlib.h> /**< Header to include if MBEDCRYPTO_PLATFORM_NO_STD_FUNCTIONS is defined. Don't define if no header is needed. */
//#define MBEDCRYPTO_PLATFORM_STD_CALLOC        calloc /**< Default allocator to use, can be undefined */
//#define MBEDCRYPTO_PLATFORM_STD_FREE            free /**< Default free to use, can be undefined */
//#define MBEDCRYPTO_PLATFORM_STD_EXIT            exit /**< Default exit to use, can be undefined */
//#define MBEDCRYPTO_PLATFORM_STD_TIME            time /**< Default time to use, can be undefined. MBEDCRYPTO_HAVE_TIME must be enabled */
//#define MBEDCRYPTO_PLATFORM_STD_FPRINTF      fprintf /**< Default fprintf to use, can be undefined */
//#define MBEDCRYPTO_PLATFORM_STD_PRINTF        printf /**< Default printf to use, can be undefined */
/* Note: your snprintf must correclty zero-terminate the buffer! */
//#define MBEDCRYPTO_PLATFORM_STD_SNPRINTF    snprintf /**< Default snprintf to use, can be undefined */
//#define MBEDCRYPTO_PLATFORM_STD_EXIT_SUCCESS       0 /**< Default exit value to use, can be undefined */
//#define MBEDCRYPTO_PLATFORM_STD_EXIT_FAILURE       1 /**< Default exit value to use, can be undefined */
//#define MBEDCRYPTO_PLATFORM_STD_NV_SEED_READ   mbedcrypto_platform_std_nv_seed_read /**< Default nv_seed_read function to use, can be undefined */
//#define MBEDCRYPTO_PLATFORM_STD_NV_SEED_WRITE  mbedcrypto_platform_std_nv_seed_write /**< Default nv_seed_write function to use, can be undefined */
//#define MBEDCRYPTO_PLATFORM_STD_NV_SEED_FILE  "seedfile" /**< Seed file to read/write with default implementation */

/* To Use Function Macros MBEDCRYPTO_PLATFORM_C must be enabled */
/* MBEDCRYPTO_PLATFORM_XXX_MACRO and MBEDCRYPTO_PLATFORM_XXX_ALT cannot both be defined */
//#define MBEDCRYPTO_PLATFORM_CALLOC_MACRO        calloc /**< Default allocator macro to use, can be undefined */
//#define MBEDCRYPTO_PLATFORM_FREE_MACRO            free /**< Default free macro to use, can be undefined */
//#define MBEDCRYPTO_PLATFORM_EXIT_MACRO            exit /**< Default exit macro to use, can be undefined */
//#define MBEDCRYPTO_PLATFORM_TIME_MACRO            time /**< Default time macro to use, can be undefined. MBEDCRYPTO_HAVE_TIME must be enabled */
//#define MBEDCRYPTO_PLATFORM_TIME_TYPE_MACRO       time_t /**< Default time macro to use, can be undefined. MBEDCRYPTO_HAVE_TIME must be enabled */
//#define MBEDCRYPTO_PLATFORM_FPRINTF_MACRO      fprintf /**< Default fprintf macro to use, can be undefined */
//#define MBEDCRYPTO_PLATFORM_PRINTF_MACRO        printf /**< Default printf macro to use, can be undefined */
/* Note: your snprintf must correclty zero-terminate the buffer! */
//#define MBEDCRYPTO_PLATFORM_SNPRINTF_MACRO    snprintf /**< Default snprintf macro to use, can be undefined */
//#define MBEDCRYPTO_PLATFORM_NV_SEED_READ_MACRO   mbedcrypto_platform_std_nv_seed_read /**< Default nv_seed_read function to use, can be undefined */
//#define MBEDCRYPTO_PLATFORM_NV_SEED_WRITE_MACRO  mbedcrypto_platform_std_nv_seed_write /**< Default nv_seed_write function to use, can be undefined */

/**
 * Uncomment the macro to let Mbed Crypto use your alternate implementation of
 * mbedcrypto_platform_zeroize(). This replaces the default implementation in
 * platform_util.c.
 *
 * mbedcrypto_platform_zeroize() is a widely used function across the library to
 * zero a block of memory. The implementation is expected to be secure in the
 * sense that it has been written to prevent the compiler from removing calls
 * to mbedcrypto_platform_zeroize() as part of redundant code elimination
 * optimizations. However, it is difficult to guarantee that calls to
 * mbedcrypto_platform_zeroize() will not be optimized by the compiler as older
 * versions of the C language standards do not provide a secure implementation
 * of memset(). Therefore, MBEDCRYPTO_PLATFORM_ZEROIZE_ALT enables users to
 * configure their own implementation of mbedcrypto_platform_zeroize(), for
 * example by using directives specific to their compiler, features from newer
 * C standards (e.g using memset_s() in C11) or calling a secure memset() from
 * their system (e.g explicit_bzero() in BSD).
 */
//#define MBEDCRYPTO_PLATFORM_ZEROIZE_ALT

/* \} name SECTION: Customisation configuration options */

#include "mbedcrypto/check_config.h"

#endif /* MBEDCRYPTO_CONFIG_H */
