//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███                                                  //
//            █ █        █ █        GameCore.h                                //
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

#ifndef __LightsOffCore_include_GameCore_h__
#define __LightsOffCore_include_GameCore_h__

//std
#include <string>
//LightsOffCore.
#include "LightsOffCore_Utils.h"
#include "Status.h"
#include "Light.h"
#include "Coord.h"
#include "ILevelLoader.h"

NS_LIGHTSOFFCORE_BEGIN

class GameCore
{
    // Constants //
public:
    ///@brief
    ///@returns
    ///@see
    static const int kUnlimitedMoves;


    // CTOR/DTOR //
public:
    ///@brief
    ///@returns
    ///@see
    GameCore(const ILevelLoader &loader, int maxMoves = kUnlimitedMoves);


    // Public Methods //
public:
    ///@brief
    ///@returns
    ///@see
    const Board& getBoard() const;
     

    ///@brief
    ///@returns
    ///@see
    CoordVec changeLightStateAt(const Coord &coord);


    ///@brief
    ///@returns
    ///@see
    const Light& getLightAt(const Coord &coord) const;

    ///@brief
    ///@returns
    ///@see
    int getLightsOnCount() const;

    ///@brief
    ///@returns
    ///@see
    int getLightsOffCount() const;


    ///@brief
    ///@returns
    ///@see
    Status getStatus() const;


    ///@brief
    ///@returns
    ///@see
    int getMovesCount() const;

    ///@brief
    ///@returns
    ///@see
    int getMaxMovesCount() const;


    ///@brief
    ///@returns
    ///@see
    bool isValidCoord(const Coord &coord) const;


    ///@brief
    ///@returns
    ///@see
    std::string ascii() const;
    
    // Private Methods //
private:
    void changeLightStateHelper(Light &light);
    void checkStatus();

    // iVars //
private:
    Board m_board;
    
    int m_lightsOnCount;
    int m_lightOffCount;
    
    Status m_status;

    int m_movesCount;
    int m_maxMovesCount;
};

NS_LIGHTSOFFCORE_END
#endif // defined(__LightsOffCore_include_GameCore_h__) //
