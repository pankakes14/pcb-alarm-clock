#include "main.h"
#include "util.h"



//This generates a random  byte by using a galois LFSR with polynomial 0xA2
//and iterating that 8 times
uint8_t generate_random_byte(uint8_t lfsr)
{

    char lsb;
    
    //add further randomization by xoring with timer0
    //lfsr ^= TMR0;
    
    //run galois lfsr for rand num cycles cycles
    lsb = lfsr & 1;
    lfsr >>= 1;
    if (lsb)
    {
        lfsr ^= 0xB8;
    }
    
    return lfsr;
}

//get a random number in between 2 bounds
uint8_t get_rand_num(uint8_t lower_bound, uint8_t upper_bound, uint8_t seed)
{
    uint8_t rand_byte = seed;
    
    
    if (lower_bound == upper_bound)
    {
        return lower_bound;
    }
    
    if (seed == 0)
    {
        rand_byte = 0xa5;
    }
    
    do
    {
        rand_byte = generate_random_byte(rand_byte);
    } while (rand_byte <= lower_bound || rand_byte >= upper_bound);
    
    return rand_byte;
}
