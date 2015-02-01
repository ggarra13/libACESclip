/* 
Copyright (c) 2015, Gonzalo Garramuño
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies, 
either expressed or implied, of the FreeBSD Project.
*/

#include <iostream>

#include "ACESclipReader.h"


int main( int argc, char** argv )
{
    if ( argc != 2 )
    {
        std::cerr << argv[0] << " v0.2" << std::endl
                  << std::endl
                  << argv[0] << " <file>"
                  << std::endl
                  << std::endl
                  << "Example: "
                  << std::endl
                  << std::endl
                  << argv[0] << " ACESclip.output.xml"
                  << std::endl;
        exit(-1);
    }

    ACES::ACESclipReader c;
    c.load( argv[1] );

    std::cout << "Application: " << c.application << " " << c.version
              << std::endl;
    std::cout << "Clip Name: " << c.clip_name << std::endl
              << "Media Id:  " << c.media_id << std::endl
              << "Clip Date: " << c.clip_date << std::endl;
    if ( !c.IDT.name.empty() )
        std::cout << "IDT: " << c.IDT << std::endl;
    if ( !c.link_ITL.empty() )
        std::cout << "Link ITL: " << c.link_ITL << std::endl;
    for ( size_t i = 0; i < c.LMT.size(); ++i )
        std::cout << "LMT " << i+1 << ": " << c.LMT[i] << std::endl;
    if ( !c.RRT.name.empty() )
        std::cout << "RRT: " << c.RRT << std::endl;
    if ( !c.ODT.name.empty() )
        std::cout << "ODT: " << c.ODT << std::endl;
    if ( !c.link_PTL.empty() )
        std::cout << "Link LPT: " << c.link_PTL << std::endl;



    return 0;
}
