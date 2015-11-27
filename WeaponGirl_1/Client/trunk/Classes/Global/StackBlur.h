// The Stack Blur Algorithm was invented by Mario Klingemann, 
// mario@quasimondo.com and described here:
// http://incubator.quasimondo.com/processing/fast_blur_deluxe.php

// This is C++ RGBA (32 bit color) multi-threaded version 
// by Victor Laskin (victor.laskin@gmail.com)
// More details: http://vitiy.info/stackblur-algorithm-multi-threaded-blur-for-cpp

// This code is using MVThread class from my cross-platform framework 
// You can exchange it with any thread implementation you like

#ifndef _STACK_BLUR_HEADER_
#define _STACK_BLUR_HEADER_
void stackblur(unsigned char* src, unsigned int w, unsigned int h, unsigned int radius = 16);
#endif // end of _STACK_BLUR_HEADER_