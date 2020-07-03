

#include "main.h"
#include "timer.h"


bool timer_has_time_elapsed(uint32_t time, uint32_t num_ms)
{
    //Check for overflow condition
    if (timer_get_ticks() >=  time)
    {
        if ((timer_get_ticks() - time) >= num_ms)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    //overflow has occurred just return true as something happening too quickly once
    //isn't a really big deal in this application. Maybe I'll put in more sophisticated handling later...
    else 
    {
        return true;
    }
}




uint32_t timer_get_ticks()
{
    return SYSTEM_TICKS;
}
