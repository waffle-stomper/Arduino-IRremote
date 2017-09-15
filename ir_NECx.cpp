#include "IRremote.h"
#include "IRremoteInt.h"

//==============================================================================
//
//
//                              NECx
//
//
//==============================================================================

#define NECX_BITS    32     // The number of bits in the command

#define HDR_MARK     4512   // The length of the Header:Mark
#define HDR_SPACE    4512   // The lenght of the Header:Space

#define BIT_MARK     564    // The length of a Bit:Mark
#define ONE_SPACE    1692   // The length of a Bit:Space for 1's
#define ZERO_SPACE   564    // The length of a Bit:Space for 0's

#define REPEAT_SPACE 412    // Used with REPEAT_DELAY
#define REPEAT_DELAY 98     // ms


//+=============================================================================
//
#if SEND_NECX
void  IRsend::sendNECX (unsigned long data,  int nbits, boolean repeat)
{
	// Set IR carrier frequency
	enableIROut(38);

	// Header
	mark (HDR_MARK);
	space(HDR_SPACE);

  if (repeat == false){
    // Data
    for (unsigned long  mask = 1UL << (nbits - 1);  mask;  mask >>= 1) {
      if (data & mask) {
        mark (BIT_MARK);
        space(ONE_SPACE);
      } else {
        mark (BIT_MARK);
        space(ZERO_SPACE);
      }
    }
    // Footer
    mark(BIT_MARK);
    space(0);
  }
  else{
    mark(BIT_MARK); space(ZERO_SPACE);
    mark(BIT_MARK); space(REPEAT_SPACE); delay(REPEAT_DELAY);
  }
}
#endif

