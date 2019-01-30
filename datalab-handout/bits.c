/* 
 * CS:APP Data Lab 
 * 
 * <OSMAN ALI OZA5@PSU.EDU>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  // Using Demorgans law
  return ~(~x|~y);
}
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
   // Since nothing bigget than 0x55 allowed used shifting and OR to add upto 0x55555555
   int mask = 0x55 << 8;
   mask = mask | 0x55;
   mask = mask << 8;
   mask = mask | 0x55;
   mask = mask << 8;
   mask = mask | 0x55;
   // Masking should return either 0 or any other number. "!" of 0 gives 1, and "!" of any other gives 0
  return !((x&mask)^(mask));

}
/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
  int high_pos,low_pos,mid_pos;
  // Since nothing bigget than 0xFF allowed used shifting and OR to add upto 0xFFFFFFFF
  int msk = 0xFF << 8;
   msk= msk | 0xFF;
   msk = msk << 8;
   msk = msk | 0xFF;
   msk = msk << 8;
   msk = msk | 0xFF;
  // Creates seperate masks for highbits,lowbits and middle 1's
  high_pos = msk << highbit;
  low_pos = ~(msk << lowbit);
  mid_pos = (1 << highbit);
  high_pos = high_pos & ~mid_pos;
  //Or's the masks and returns the answer
  return ~(high_pos | low_pos);
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
 int mask_1 = 0x000000FF;
 //Shifts FF into position using 8*n
 int mask = mask_1 << ((n<<3));
 int ans_mask = ~mask;
 int mask_4 = x & ans_mask;
 //O's out the numbers on position and Or's repalce bits to the number,
 // replacing the bits.
 int mask_3 = c << ((n<<3));
 return mask_4 | mask_3;
}

/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  // divides and adds result to x using xor operator
  // Xor operator decides parity
  x = (x >> 16) ^ x;
  x = (x >> 8 ) ^ x;
  x = (x >> 4 ) ^ x;
  x = (x >> 2 ) ^ x;
  x = (x >> 1 ) ^ x;
  // At this stage division returns either 1 or 0
  // We and it with 1 and return result
  return (x&1);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  //Using formula for lowest 2's complement (-2^bits-1)
  //Gives (-2^31)
  //in hex that is 0x80000000
  return (1<<31);
}
/* 
 * isNegative - return 1 if x < 0, return 0 otherwise 
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
  int get_sign = 0x1;
  // Sign of integer returned
  x = x>>31;
  x = x&get_sign;
  return x;
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  //Returns sign of x number
  int sx = x >> 31;
  //Returns sign of y number
  int sy = y >> 31;
  //Sign of sum
  int sum = x+y;
  //Get sign of Sum
  int sum_s = sum>> 31;
  // An overflow occurs when the sign of x and y are the same, but the sign of the sum of x and y is different
  return !(~(sx ^ sy) & (sx ^ sum_s));


}
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */

int absVal(int x) {
  int mask = 1<<31;
  int a = x & mask;
  int b = a >> 31;
  int c = (b ^ x);
  int d = b & (0x1);
  return c+d;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
 // Mask for EXP bits
 int mask_8 = 0x7F800000;
 // Mask for frac bits
 int mask_23 = 0x007FFFFF;
 int temp = (uf >> 31);
 temp = ~temp;
 // Definition of NAN
 if (((uf & mask_8) ==  mask_8) && (uf & mask_23) != 0x0)return uf;
 
 return (uf & 0x7FFFFFFF) | (temp << 31);
}
/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
  int chk, Sign, Exp, mask_3, mask_2, mask_1,mask_f, mask_h,cond,cond2, tmp;
  cond = ( (uf&3) ^ 3);
  mask_1 = 0x80000000;
  mask_3 = 0x7F800000;

  Exp = uf&mask_3;
  Sign = uf&mask_1;
  mask_2 = 0x007FFFFF;
  mask_f= 0x7FFFFFFF;
  mask_h= 0x807FFFFF;
  cond = ((uf&3)^3);
  chk = !(cond);

  //Nan Case
  if (Exp==0x7F800000) return uf;
  // outlier
  if (Exp==0x00800000){
    cond2 = (chk + ((uf & mask_f)>>1));
    return Sign | cond2 ;
  }
  //E=ddenormalized
  if (Exp==0) {
    tmp = (uf&mask_2)>>1;
    return Sign | (tmp + chk);
  }
  //normal
  return (((Exp>>23)-1)<<23) | (uf & mask_h);
}


