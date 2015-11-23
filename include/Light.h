//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███                                                  //
//            █ █        █ █        Light.h                                   //
//             ████████████         LightsOff Core                            //
//           █              █       Copyright (c) 2015 AmazingCow             //
//          █     █    █     █      www.AmazingCow.com                        //
//          █     █    █     █                                                //
//           █              █       N2OMatt - n2omatt@amazingcow.com          //
//             ████████████         www.amazingcow.com/n2omatt                //
//                                                                            //
//                                                                            //
//                  This software is licensed as GPLv3                        //
//                 CHECK THE COPYING FILE TO MORE DETAILS                     //
//                                                                            //
//    Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//               freely, subject to the following restrictions:               //
//                                                                            //
//     0. You **CANNOT** change the type of the license.                      //
//     1. The origin of this software must not be misrepresented;             //
//        you must not claim that you wrote the original software.            //
//     2. If you use this software in a product, an acknowledgment in the     //
//        product IS HIGHLY APPRECIATED, both in source and binary forms.     //
//        (See opensource.AmazingCow.com/acknowledgment.html for details).    //
//        If you will not acknowledge, just send us a email. We'll be         //
//        *VERY* happy to see our work being used by other people. :)         //
//        The email is: acknowledgmentopensource@AmazingCow.com               //
//     3. Altered source versions must be plainly marked as such,             //
//        and must notbe misrepresented as being the original software.       //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//

#ifndef __LightsOffCore_include_Light_h__
#define __LightsOffCore_include_Light_h__

//std
#include <vector>
//LightsOffCore.
#include "LightsOffCore_Utils.h"
//CoreCoord.
#include "CoreCoord.h"

NS_LIGHTSOFFCORE_BEGIN

class Light
{
    // Enums/Constants/Typdefs //
public:
    ///@brief Typedef to ease the typing of "a matrix of LightsOffTypes".
    typedef std::vector<std::vector<Light>> Board;


    // CTOR/DTOR //
public:
    ///@brief Constructs a Light.
    ///@param on If the Light state is on at beginning.
    ///@param affectOffsetRange The coords that this light will affect
    ///when its state changes.
    ///@see Light::changeState, Light::isOn, Light::getAffectedOffsetRange.
    Light(bool on, const CoreCoord::Coord::Vec &affectOffsetRange);


    // Public Methods //
public:
    ///@brief Change the state of the light.
    void changeState();

    ///@brief Gets the state of the light.
    ///@returns true if Light is on, false otherwise.
    bool isOn() const;

    ///@brief Get all the coords that this Light affects
    ///when it changes the state.
    ///@returns The affected range.
    const CoreCoord::Coord::Vec& getAffectOffsetRange() const;

    // iVars //
private:
    bool                  m_isOn;
    CoreCoord::Coord::Vec m_affectOffsetRange;
};



NS_LIGHTSOFFCORE_END
#endif // defined(__LightsOffCore_include_Light_h__) //
