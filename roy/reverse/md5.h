#ifndef MD5_H
#define MD5_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void md5(uint8_t *initial_msg, uint8_t *output_str, size_t output_siz);

#endif