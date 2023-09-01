
/*
 * Coded by Mayur Patel
 * Copyright (c) 2023
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of this project.
 */
 
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>

#include "sobolowen.h"

#define SAMPLES (uint32_t(32))

// =======================================================================
// dumping samples into an array, then processing the array later
// makes sure that steps of each generator don't get optimized out of the loop!
float  gf_samples[SAMPLES][2];


// =======================================================================
void stateless_generate(void){
  for(uint32_t u=0; u<SAMPLES; ++u){
    gf_samples[u][0] = sobolowen::get_sample(u, 0);
    gf_samples[u][1] = sobolowen::get_sample(u, 1);
  }
  return;
}

// =======================================================================
inline void stateful_generate(void){
  sobolowen::StatefulGenerator32f ss(2); // 2D generator
    
  for(uint32_t u=0; u<SAMPLES; ++u){
    ss.get_sample(gf_samples[u]);
  }
  return;
}

// =======================================================================
void output(void){
  for( unsigned i=0; i<SAMPLES; ++i)
    std::cout << gf_samples[i][0] << ' ' << gf_samples[i][1] << std::endl;
  return;
}

// =======================================================================
int main(int argc, char*argv[]) {
  const char* cpName = argv[1];

  if( 0 == strcmp( cpName, "stateful" )) {
    stateful_generate();
    output();
  }
  
  if( 0 == strcmp( cpName, "stateless" )) {
    stateless_generate();
    output();
  }
  
  return 0;
}


