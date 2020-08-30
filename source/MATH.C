/*////////////////////////////////////////////////////////////////////////////*/

/* We need abs(). */
#include <stdlib.h>

#define FIXED_POINT_SHIFT_AMOUNT 0x08 /* Must be a power of 2. */
#define FIXED_POINT_SHIFT_MASK ((1<<FIXED_POINT_SHIFT_AMOUNT)-1)

typedef union _SFIXED_
{
    struct { S8 lo, hi; } part;
    S16                   full;

} SFIXED;

typedef union _UFIXED_
{
    struct { U8 lo, hi; } part;
    U16                   full;

} UFIXED;

#define GET_INTEGRAL(  a)      (a.part.hi      )
#define GET_FRACTIONAL(a) abs(((a.part.lo * 100) / (1 << FIXED_POINT_SHIFT_AMOUNT)))

/* Builds a fixed-point value out of two integral values. A value passed in   */
/* to represent the fractional must be in 10s in order for this call to work: */
/*                                                                            */
/*   MAKE_FIDED_POINT(a,  3,14); // 3.14                                      */
/*   MAKE_FIDED_POINT(a,  5,50); // 5.50                                      */
/*                                                                            */
/* Passing in a single digit value for the fractional WILL NOT work ever.     */
#define MAKE_FIXED_POINT(a,i,f) a.full = ((i << FIXED_POINT_SHIFT_AMOUNT) | ((f * (1 << FIXED_POINT_SHIFT_AMOUNT)) / 100))

/* Operations for integers on fixed-point values.    */
#define F_ADD_I(a,b) (a.part.hi += b     )
#define F_SUB_I(a,b) (a.part.hi -= b     )
#define F_MUL_I(a,b) (a.full    *= b     )
#define F_DIV_I(a,b) (a.full    /= b     )

/* Operations for fixed-point on fixed-point values. */
#define F_ADD_F(a,b) (a.full    += b.full)
#define F_SUB_F(a,b) (a.full    -= b.full)
#define F_MUL_F(a,b) (a.full    *= b.full)
#define F_DIV_F(a,b) (a.full    /= b.full)

/*////////////////////////////////////////////////////////////////////////////*/
