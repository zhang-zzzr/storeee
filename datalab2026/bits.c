/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~ x|~ y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x&y)&~(~x&~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    int a;
    if (!x&&!y)
        a=1;
    else if (!x)
        a=0;    
    else if (!y)
        a=0;
    else if(!((x>>31)^(y>>31)))
        a=1;  
    else
        a=0;
        
    return a;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int result=0;
    int n_1=((v>>16)>0)<<4;
    v=v>>n_1;
    result=result|n_1;
    int n_2=((v>>8)>0)<<3;
    v=v>>n_2;
    result=result|n_2;
    int n_3=((v>>4)>0)<<2;
    v=v>>n_3;
    result=result|n_3;
    int n_4=((v>>2)>0)<<1;
    v=v>>n_4;
    result=result|n_4;
    int n_5=(v>>1)>0;
    v=v>>n_5;
    result=result|n_5;
  
    return result;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    n=n<<3;
    m=m<<3;
    int a=(x>>n)&0xFF;
    int b=(x>>m)&0xFF;
    x=x&(~(0xFF<<n));
    x=x&(~(0xFF<<m));
    x=(x|a<<m);
    x=(x|b<<n);
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned i=32;
    unsigned x=0;
    while(i){
        x=(x<<1)|(v&1);
        v=v>>1;
        i=i-1;
    }
    return x;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask;
    mask=~(((1<<31)>>n)<<1);
    x=(x>>n);
    x=x&mask;
    return x;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int res=0;
    int v=~x;
    int bit_16=!(v>>16);
    res=bit_16<<4;
    v=v<<res;
    int bit_8=!(v>>24);
    res=res+(bit_8<<3);
    v=v<<(bit_8<<3);
    int bit_4=!(v>>28);
    res=res+(bit_4<<2);
    v=v<<(bit_4<<2);
    int bit_2=!(v>>30);
    res=res+(bit_2<<1);
    v=v<<(bit_2<<1);
    int bit_1=!(v>>31);
    res=res+bit_1;
    v=v<<bit_1;
    int b0=!(v>>31);
    res=res+b0;


    return res;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned s;
    unsigned e;
    unsigned m;
    unsigned m_64;
    int count=0;
    unsigned v;
    unsigned res;
    if(x==0){
        return 0;
    }
    else if (x<0){ 
        s=1<<31;
        v=-x;
    }
    else{
        s=0;
        v=x;
    }
       while(!(v&(1<<31))){
            v=v<<1;
            count=count+1;    
        }
        count=32-count;
        e=127+count-1;
        m=(v>>8)&0x7FFFFF;
        m_64=v&0xFF;
        if(m_64>128){
            m=m+1;
        }
        else if(m_64==128){
            if(m&1){
                m=m+1;
            }
        }
    if(m>>23){
        m=m&0x7FFFFF;
        e=e+1;
    }
    res=s|(e<<23)|m;
    return res;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned s=(uf&0x80000000);
    unsigned e=(uf>>23)&0xFF;
    unsigned m=uf&0x7FFFFF;

    if (e==0xFF){
        return uf;
    }
    if (e==0){
        return s|(m<<1);
    }
    
    e=e+1;
    if(e==0xFF){
            return s|0x7F800000;
    }
    else return s|(e<<23)|m;
}


/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned s;
    unsigned e;
    int E;
    unsigned res;

    s=uf2>>31;
    e=((uf2>>20)&0x7FF);
    if (!(e>1022)){
        return 0;
    }
    E=e-1023;

    if(E<0){
        return 0;
    }
    else if (E>31){
        return 0x80000000;
    }
    else if(!(E<31)){
        return 0x80000000;
    }
    

    if(E<=20){
        res=(1<<E)|((uf2&0xFFFFF)>>(20-E));
    }
    else{
        res=(1<<E)|(uf2&0xFFFFF)|(uf1>>(52-E));
    }

    if(s){
        res=-res;
    }
    return res;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x>127){
        return 0x7F800000;
    }
    else if (x<-149){
        return 0;
    }
    else if(x>=-149 && x<-126){
        return (1<<(x+149));
    }
    else{
        return (x+127)<<23;
    }
}
