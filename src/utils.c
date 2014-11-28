#include <pebble.h>

uint get_prime(uint iPrime) {
    int flag = 1;
    int j, i;
    
    for(i=iPrime+1; flag==1; ++i)
    {
        flag=0;
        for(j=2; j<=i/2; ++j)
        {
          if(i%j==0)
          {
            flag=1;
            break;
          }
        }
    }

    return i-1;
  
}


int itoa(int value, char *sp, int radix)
{
    char tmp[16];// be careful with the length of the buffer
    char *tp = tmp;
    uint i;
    unsigned v;

    int sign = (radix == 10 && value < 0);    
    if (sign)
        v = -value;
    else
        v = (unsigned)value;

    while (v || tp == tmp)
    {
        i = v % radix;
        v /= radix; // v/=radix uses less CPU clocks than v=v/radix does
        if (i < 10)
          *tp++ = i+'0';
        else
          *tp++ = i + 'a' - 10;
    }

    int len = tp - tmp;

    if (sign) 
    {
        *sp++ = '-';
        len++;
    }

    while (tp > tmp)
        *sp++ = *--tp;

    return len;
}