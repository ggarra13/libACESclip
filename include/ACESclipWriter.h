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

#ifndef ACESclipWriter_h
#define ACESclipWriter_h

#include <string>
#include <vector>

#include <tinyxml2.h>

#include "ACESexport.h"

namespace ACES {

static const char* kLibVersion = "0.1";


enum TransformStatus
{
kPreview,
kApplied,
kLastStatus
};

/** 
 * Transform:  A class to store the name of a transform and its status
 * 
 */
class ACES_EXPORT Transform
{
  public:
    Transform() : name(""), status( kLastStatus ) {}

    Transform( std::string n, TransformStatus t) :
    name( n ),
    status( t )
    {}

    ~Transform() {}

    Transform( const Transform& b ) :
    name( b.name ),
    status( b.status )
    {
    }

  public:
    std::string     name;
    TransformStatus status;
};


using namespace tinyxml2;

/**
 * ACESclip:  class encompasing an ACESclip.xml file
 *
 */
 
class ACES_EXPORT ACESclipWriter
{

  protected:
/**
 * Look Modification Transforms is a list
 */
    typedef std::vector< Transform > LMTransforms;

  protected:
    std::string date_time( const time_t& t ) const;
    void set_id();
    void set_status( TransformStatus s );

  public:
    ACESclipWriter();
    ~ACESclipWriter() {};

    /** 
     * aces:Info section
     * 
     * @param application application used to save xml file. 
     * @param version     version of application used.
     * @param comment     some comment of usefulness
     */
    void info( std::string application = "ACESclipLib",
               std::string version = kLibVersion,
               std::string comment = "" );

    /** 
     * aces:clipID section
     * 
     * @param clip_name name of the clip (image name, for example)
     * @param media_id  media id ( show,shot,take, for example )
     * @param clip_date date of clip as return by stat
     */
    void clip_id( std::string clip_name,
                  std::string media_id,
                  time_t clip_date = time(0) );

    /** 
     * aces:Config section
     * 
     * @param xml_date date of xml creation
     */
    void config( time_t xml_date = time(0) );

    /** 
     * Input Transform List beginnings.
     * 
     */
    void ITL_start();

    /** 
     * Add Input Device Transform (IDT) to ITL.
     * 
     * @param name    name of the transform (without .ctl extension)
     * @param status  status of transform (preview or applied)
     */
    void add_IDT( const std::string name, 
                  TransformStatus status = kPreview );

    /** 
     * Input Transform List ending
     * 
     * @param it pointer to combined process list
     */
    void ITL_end( const std::string it = "inputTransformID" );


    /** 
     * Preview Transform List beginning.
     * 
     */
    void PTL_start();

    /** 
     * Append one Look Modification Transform to PTL.  Multiple
     * calls on this function are allowed.
     * 
     * @param name     name of the transform (without .ctl extension)
     * @param status   status of transform (preview or applied)
     */
    void add_LMT( const std::string name, 
                  TransformStatus status = kPreview );

    /** 
     * Add a Reference Rendering Transform to PTL.  Only a single
     * call to it is accepted.
     * 
     * @param name    name of the transform (without .ctl extension)
     * @param status  status of transform (preview or applied)
     */
    void add_RRT( const std::string name, 
                  TransformStatus status = kPreview );

    /** 
     * Add an Output Device Transform to PTL.  Only a single call
     * to it is accepted.
     * 
     * @param name    name of the transform (without .ctl extension)
     * @param status  status of transform (preview or applied)
     */

    void add_ODT( const std::string name, 
                  TransformStatus status = kPreview );

    /** 
     * Preview Transform List ending.
     * 
     * @param t Combined LMTs + RRT + ODT (optional)
     */
    void PTL_end( const std::string t = "CombinedLMT_RRT_ODT" );


    /** 
     * Save the XML file to a certain filename
     * 
     * @param filename  file to save xml into.  Add prefix and .xml suffix.
     * 
     * @return true if success, false if not.
     */
    bool save( const char* filename );

  protected:
    XMLDocument doc;
    XMLElement* element;
    XMLNode* root, *root2, *root3;
    LMTransforms LMT;
    Transform IDT, RRT, ODT;
    unsigned id;
};


}  // namespace ACES

#endif  // ACESclipWriter_h
