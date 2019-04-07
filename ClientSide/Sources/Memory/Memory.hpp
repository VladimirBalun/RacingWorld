/*
 * Copyright 2018 Vladimir Balun
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

// Bytes
#define BYTE_SIZE       1u
#define BYTES_2_SIZE    (BYTE_SIZE * 2u)
#define BYTES_4_SIZE    (BYTE_SIZE * 4u)
#define BYTES_8_SIZE    (BYTE_SIZE * 8u)
#define BYTES_16_SIZE   (BYTE_SIZE * 16u)
#define BYTES_32_SIZE   (BYTE_SIZE * 32u)
#define BYTES_64_SIZE   (BYTE_SIZE * 64u)
#define BYTES_128_SIZE  (BYTE_SIZE * 128u)
#define BYTES_256_SIZE  (BYTE_SIZE * 256u)
#define BYTES_512_SIZE  (BYTE_SIZE * 512u)
#define BYTES_1024_SIZE (BYTE_SIZE * 1024u)

// Killobytes
#define KILLOBYTE_SIZE       BYTES_1024_SIZE
#define KILLOBYTES_2_SIZE    (KILLOBYTE_SIZE * 2u)
#define KILLOBYTES_4_SIZE    (KILLOBYTE_SIZE * 4u)
#define KILLOBYTES_8_SIZE    (KILLOBYTE_SIZE * 8u)
#define KILLOBYTES_16_SIZE   (KILLOBYTE_SIZE * 16u)
#define KILLOBYTES_32_SIZE   (KILLOBYTE_SIZE * 32u)
#define KILLOBYTES_64_SIZE   (KILLOBYTE_SIZE * 64u)
#define KILLOBYTES_128_SIZE  (KILLOBYTE_SIZE * 128u)
#define KILLOBYTES_256_SIZE  (KILLOBYTE_SIZE * 256u)
#define KILLOBYTES_512_SIZE  (KILLOBYTE_SIZE * 512u)
#define KILLOBYTES_1024_SIZE (KILLOBYTE_SIZE * 1024u)

// Megabytes
#define MEGABYTE_SIZE       KILLOBYTES_1024_SIZE
#define MEGABYTES_2_SIZE    (MEGABYTE_SIZE * 2u)
#define MEGABYTES_4_SIZE    (MEGABYTE_SIZE * 4u)
#define MEGABYTES_8_SIZE    (MEGABYTE_SIZE * 8u)
#define MEGABYTES_16_SIZE   (MEGABYTE_SIZE * 16u)
#define MEGABYTES_32_SIZE   (MEGABYTE_SIZE * 32u)
#define MEGABYTES_64_SIZE   (MEGABYTE_SIZE * 64u)
#define MEGABYTES_128_SIZE  (MEGABYTE_SIZE * 128u)
#define MEGABYTES_256_SIZE  (MEGABYTE_SIZE * 256u)
#define MEGABYTES_512_SIZE  (MEGABYTE_SIZE * 512u)
#define MEGABYTES_1024_SIZE (MEGABYTE_SIZE * 1024u)

// Gigabytes
#define GIGABYTE_SIZE       MEGABYTES_1024_SIZE
#define GIGABYTES_2_SIZE    (GIGABYTE_SIZE * 2u)
#define GIGABYTES_4_SIZE    (GIGABYTE_SIZE * 4u)
#define GIGABYTES_8_SIZE    (GIGABYTE_SIZE * 8u)
#define GIGABYTES_16_SIZE   (GIGABYTE_SIZE * 16u)
#define GIGABYTES_32_SIZE   (GIGABYTE_SIZE * 32u)
#define GIGABYTES_64_SIZE   (GIGABYTE_SIZE * 64u)
#define GIGABYTES_128_SIZE  (GIGABYTE_SIZE * 128u)
#define GIGABYTES_256_SIZE  (GIGABYTE_SIZE * 256u)
#define GIGABYTES_512_SIZE  (GIGABYTE_SIZE * 512u)
#define GIGABYTES_1024_SIZE (GIGABYTE_SIZE * 1024u)

// Average cache parameters
#define CACHE_L1_SIZE   KILLOBYTES_32_SIZE
#define CACHE_L2_SIZE   KILLOBYTES_512_SIZE
#define CACHE_L3_SIZE   MEGABYTES_64_SIZE
#define CACHE_LINE_SIZE BYTES_64_SIZE
