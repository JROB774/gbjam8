/*////////////////////////////////////////////////////////////////////////////*/

/* 12.4 Fixed-point type imeplementation with basic mathematical operations.  */
/* We are using this represenation as we do not need high-precision with our  */
/* real numbers and would still like to represent large integral values.      */

#define FP_SHIFT (4            )
#define FP_SCALE (1 << FP_SHIFT)
#define FP_MASK  (FP_SCALE -  1)
#define FP_ONE   (FP_SCALE     )
#define FP_HALF  (FP_SCALE >> 1)

#define M_FP_2PI  ITOF(0xFF            )
#define M_FP_PI   ITOF(0x7F            )
#define M_FP_PI4  FDIV(M_FP_PI,ITOF(4) )
#define M_FP_3PI4 FMUL(ITOF(3),M_FP_PI4)

typedef S16 FIXED;

#define FADD(a,b) ( (a)             + (b) )       /* Add two fixed-points.    */
#define FSUB(a,b) ( (a)             - (b) )       /* Sub two fixed-points.    */
#define FMUL(a,b) (((a) * (b)) >> FP_SHIFT)       /* Mul two fixed-points.    */
#define FDIV(a,b) (((a) * FP_SCALE) / (b) )       /* Div two fixed-points.    */

#define UTOF(x) ((x) << FP_SHIFT)                 /* UINT  to FIXED.          */
#define ITOF(x) ((x) << FP_SHIFT)                 /* SINT  to FIXED.          */
#define FTOU(x) ((x) /  FP_SCALE)                 /* FIXED to UINT (truncate).*/
#define FTOI(x) ((x) >> FP_SHIFT)                 /* FIXED to SINT (truncate).*/

#define FROUNDU(x) FTOU(x + FP_HALF)              /* Round FIXED to UINT.     */
#define FROUNDI(x) FTOI(x + FP_HALF)              /* Round FIXED to SINT.     */

#define SIN(x) SIN_TABLE[(((x))       ) & 0xFF]   /* Sine.                    */
#define COS(x) SIN_TABLE[(((x)) + 0x40) & 0xFF]   /* Cosine.                  */

INTERNAL FIXED ATAN2 (FIXED y, FIXED x);          /* Arc tangent.             */
INTERNAL FIXED SQRT  (FIXED n         );          /* Square root.             */

/* Extract the integral and fractional parts of a fixed-point value and then  */
/* convert them into integers; useful for printing out fixed-points, like so: */
/*                                                                            */
/*   printf("%d.%d", FINT(fixed), FFRAC(fixed,10));                           */
/*                                                                            */
/* The argument p to FFRAC is the level of precision to print with. Passing a */
/* value of 1 will result in one digit, 10 for two, 100 for three, and so on. */
#define FINT(  x)     ((x) >> FP_SHIFT)
#define FFRAC( x,p) ((((x) &  FP_MASK ) * p) / FP_SCALE)

#define FPRINT(x,p) FINT(x), FFRAC(x,p)

/* Table of fixed-point sin values for implementing sin() and cos() functions.*/
/* The table goes from the range [0x00 - 0xFF] with 0xFF representing 2pi.    */

GLOBAL const U16 SIN_TABLE[] =
{
0x0000,0x0006,0x000C,0x0012,0x0019,0x001F,0x0025,0x002B,
0x0031,0x0038,0x003E,0x0044,0x004A,0x0050,0x0056,0x005C,
0x0061,0x0067,0x006D,0x0073,0x0078,0x007E,0x0083,0x0088,
0x008E,0x0093,0x0098,0x009D,0x00A2,0x00A7,0x00AB,0x00B0,
0x00B5,0x00B9,0x00BD,0x00C1,0x00C5,0x00C9,0x00CD,0x00D1,
0x00D4,0x00D8,0x00DB,0x00DE,0x00E1,0x00E4,0x00E7,0x00EA,
0x00EC,0x00EE,0x00F1,0x00F3,0x00F4,0x00F6,0x00F8,0x00F9,
0x00FB,0x00FC,0x00FD,0x00FE,0x00FE,0x00FF,0x00FF,0x00FF,
0x00FF,0x00FF,0x00FF,0x00FF,0x00FE,0x00FE,0x00FD,0x00FC,
0x00FB,0x00F9,0x00F8,0x00F6,0x00F4,0x00F3,0x00F1,0x00EE,
0x00EC,0x00EA,0x00E7,0x00E4,0x00E1,0x00DE,0x00DB,0x00D8,
0x00D4,0x00D1,0x00CD,0x00C9,0x00C5,0x00C1,0x00BD,0x00B9,
0x00B5,0x00B0,0x00AB,0x00A7,0x00A2,0x009D,0x0098,0x0093,
0x008E,0x0088,0x0083,0x007E,0x0078,0x0073,0x006D,0x0067,
0x0061,0x005C,0x0056,0x0050,0x004A,0x0044,0x003E,0x0038,
0x0031,0x002B,0x0025,0x001F,0x0019,0x0012,0x000C,0x0006,
0x0000,0xFFFA,0xFFF4,0xFFEE,0xFFE7,0xFFE1,0xFFDB,0xFFD5,
0xFFCF,0xFFC8,0xFFC2,0xFFBC,0xFFB6,0xFFB0,0xFFAA,0xFFA4,
0xFF9F,0xFF99,0xFF93,0xFF8D,0xFF88,0xFF82,0xFF7D,0xFF78,
0xFF72,0xFF6D,0xFF68,0xFF63,0xFF5E,0xFF59,0xFF55,0xFF50,
0xFF4B,0xFF47,0xFF43,0xFF3F,0xFF3B,0xFF37,0xFF33,0xFF2F,
0xFF2C,0xFF28,0xFF25,0xFF22,0xFF1F,0xFF1C,0xFF19,0xFF16,
0xFF14,0xFF12,0xFF0F,0xFF0D,0xFF0C,0xFF0A,0xFF08,0xFF07,
0xFF05,0xFF04,0xFF03,0xFF02,0xFF02,0xFF01,0xFF01,0xFF01,
0xFF01,0xFF01,0xFF01,0xFF01,0xFF02,0xFF02,0xFF03,0xFF04,
0xFF05,0xFF07,0xFF08,0xFF0A,0xFF0C,0xFF0D,0xFF0F,0xFF12,
0xFF14,0xFF16,0xFF19,0xFF1C,0xFF1F,0xFF22,0xFF25,0xFF28,
0xFF2C,0xFF2F,0xFF33,0xFF37,0xFF3B,0xFF3F,0xFF43,0xFF47,
0xFF4B,0xFF50,0xFF55,0xFF59,0xFF5E,0xFF63,0xFF68,0xFF6D,
0xFF72,0xFF78,0xFF7D,0xFF82,0xFF88,0xFF8D,0xFF93,0xFF99,
0xFF9F,0xFFA4,0xFFAA,0xFFB0,0xFFB6,0xFFBC,0xFFC2,0xFFC8,
0xFFCF,0xFFD5,0xFFDB,0xFFE1,0xFFE7,0xFFEE,0xFFF4,0xFFFA
};

/* The implementations for a number of different fixed-point math operations. */

INTERNAL FIXED ATAN2 (FIXED y, FIXED x)
{
    FIXED coeff_1,coeff_2, abs_y, r, angle;

    coeff_1 = M_FP_PI4;
    coeff_2 = M_FP_3PI4;

    abs_y = y;

         if (abs_y <  0) { abs_y = -abs_y; }
    else if (abs_y == 0) { abs_y = 1;      }

    if (x >= 0) {
        r = FDIV(x-abs_y, x+abs_y);
        angle = coeff_1 - FMUL(coeff_1,r);
    } else {
        r = FDIV(x+abs_y, abs_y-x);
        angle = coeff_2 - FMUL(coeff_1,r);
    }

    return ((y < 0) ? (-angle) : (angle));
}

INTERNAL FIXED SQRT (FIXED n)
{
    FIXED s;
    U8 i;
    s = (n + 0xFF) >> 1;
    for (i=0; i<8; ++i) {
        s = (s + FDIV(n,s)) >> 1;
    }
    return s;
}

/*////////////////////////////////////////////////////////////////////////////*/
