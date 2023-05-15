
#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(VAR, BIT) (VAR) |=  (1 << (BIT))
#define CLR_BIT(VAR, BIT) (VAR) &= ~(1 << (BIT))
#define TOG_BIT(VAR, BIT) (VAR) ^=  (1 << (BIT))
#define READ_BIT(VAR, BIT) (((VAR) >> (BIT)) & 0x01 )

#endif /* BIT_MATH_H */

/*** end of file ***/