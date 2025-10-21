// Ahmet Can Karayoluk 231ADB260
// https://github.com/AHO1212/RTU_Programming_Languages_C_Lab_Fall_2025_Ahmet-Can-Karayoluk
// Build: gcc -O2 -Wall -Wextra -std=c17 -o calc calc.c
// Usage: ./calc input.txt
// Output: task1_Ahmet_Can_Karayoluk_231ADB260.txt 

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* src;
int pos = 1;  // 1-based position
int error_pos = 0;

static inline char peek(void) { return *src; }

static inline char getc_advance(void) {
  if (*src == '\0') return '\0';
  pos++;
  return *src++;
}

void skip_spaces(void) {
  while (isspace((unsigned char)peek())) getc_advance();
}

double parse_expr(void);  // forward

double error_here(void) {
  if (!error_pos) error_pos = pos;
  return 0;
}

double parse_number(void) {
  skip_spaces();
  char* end;
  double v = strtod(src, &end);
  if (end == src) return error_here();
  pos += (int)(end - src);
  src = end;
  return v;
}

double parse_factor(void) {
  skip_spaces();
  if (peek() == '(') {
    getc_advance();
    double v = parse_expr();
    skip_spaces();
    if (peek() == ')')
      getc_advance();
    else
      error_here();
    return v;
  }
  return parse_number();
}

double parse_term(void) {
  double left = parse_factor();
  for (;;) {
    skip_spaces();
    if (peek() == '*') {
      getc_advance();
      double right = parse_factor();
      left *= right;
    } else if (peek() == '/') {
      getc_advance();
      double right = parse_factor();
      if (right == 0) {
        error_here();
        return 0;
      }
      left /= right;
    } else
      break;
  }
  return left;
}

double parse_expr(void) {
  double left = parse_term();
  for (;;) {
    skip_spaces();
    if (peek() == '+') {
      getc_advance();
      double right = parse_term();
      left += right;
    } else if (peek() == '-') {
      getc_advance();
      double right = parse_term();
      left -= right;
    } else
      break;
  }
  return left;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("Usage: ./calc input.txt\n");
    return 1;
  }

  FILE* f = fopen(argv[1], "r");
  if (!f) {
    printf("Cannot open input file.\n");
    return 1;
  }

  fseek(f, 0, SEEK_END);
  long size = ftell(f);
  fseek(f, 0, SEEK_SET);

  char* buffer = (char*)malloc(size + 1);
  if (!buffer) {
    fclose(f);
    return 1;
  }
  fread(buffer, 1, size, f);
  buffer[size] = '\0';
  fclose(f);

  src = buffer;
  pos = 1;
  error_pos = 0;

  double result = parse_expr();
  skip_spaces();
  if (*src != '\0') error_here();

  char outfile[256];
  snprintf(outfile, sizeof(outfile), "task1_Ahmet_Can_Karayoluk_231ADB260.txt");

  FILE* out = fopen(outfile, "w");
  if (!out) {
    free(buffer);
    printf("Cannot write output file.\n");
    return 1;
  }

  if (error_pos)
    fprintf(out, "ERROR:%d\n", error_pos);
  else
    fprintf(out, "%.15g\n", result);

  fclose(out);
  free(buffer);
  return 0;
}
