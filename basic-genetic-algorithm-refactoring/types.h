/*
 * types.h
 * Copyright (C) 2018 guiufo <guiufo@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */
#define __STDC_FORMAT_MACROS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>
#include <random>
#include <iostream>
#include <unistd.h>

#define ROWSIZE 149
#define RULESIZE2 32
#define RULESIZE3 128
#define NGENERATIONS 100
#define NROWS 100

#define MUTATIONRATE 0.016
#define ELITISMRATE 0.1

#ifndef TYPES_H
#define TYPES_H

typedef struct{
  int cromossome[RULESIZE2];
  int fitness = 0;
}Individual2;

typedef struct{
  int cromossome[RULESIZE3];
  int fitness = 0;
}Individual3;

#endif /* !TYPES_H */