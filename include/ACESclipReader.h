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

#ifndef ACESclipReader_h
#define ACESclipReader_h

#include <tinyxml2.h>

#include "ACESExport.h"
#include "ACESTransform.h"

namespace ACES {
 
using namespace tinyxml2;

/**
 * ACESclip:  class encompasing an ACESclip.xml file
 *
 */
 
class ACES_EXPORT ACESclipReader
{

  protected:
/**
 * Look Modification Transforms is a list
 */
    typedef std::vector< Transform > LMTransforms;

  protected:
    TransformStatus get_status( const std::string& s );


  public:
    ACESclipReader();
    ~ACESclipReader() {};

    XMLError header();
    XMLError info();
    XMLError clip_id();
    XMLError config();
    XMLError ITL();
    XMLError PTL();

    /** 
     * Load the XML file
     * 
     * @param filename  file to load xml from.  Add prefix and .xml suffix.
     * 
     * @return true if success, false if not.
     */
    bool load( const char* filename );

  public:
    std::string application;
    std::string version;
    std::string comment;

    std::string clip_name;
    std::string media_id;
    std::string clip_date;

    std::string timestamp;

  protected:
    XMLDocument doc;
    XMLElement* element;
    XMLNode* root, *root2, *root3;

  public:
    LMTransforms LMT;
    Transform IDT, RRT, ODT;
    std::string link_ITL;
    std::string link_PTL;
};


}  // namespace ACES

#endif  // ACESclipReader_h
