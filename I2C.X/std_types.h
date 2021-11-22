/* 
 * File:   std_types.h
 * Author: Dell
 *
 * Created on November 22, 2021, 8:19 PM
 */

#ifndef STD_TYPES_H
#define	STD_TYPES_H

/************************************************************************/
/*                   typedefs for standard types                        */
/************************************************************************/


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;
typedef signed char sint8_t;
typedef signed int sint16_t;
typedef signed long int sint32_t;
typedef signed long long sint64_t;
typedef volatile uint8_t* const reg_type8_t;
typedef volatile uint16_t* const reg_type16_t;


/************************************************************************/
/*				 		defining boolean values                         */
/************************************************************************/
#define FALSE 	0	// defines boolean false
#define TRUE 	1	// defines boolean true


/************************************************************************/
/*						 LOW/HIGH defines                               */
/************************************************************************/
#define LOW  0		// defines LOW value for a bit
#define HIGH 0xFF	// defines HIGH value for a bit



#define SET_BIT(REG,BIT) (REG |=(1<<BIT))
#define CLEAR_BIT(REG,BIT) (REG &=(~(1<<BIT)))

#define READBIT(REG,BIT)  ( (REG >> BIT) & 1 )

#endif	/* STD_TYPES_H */

