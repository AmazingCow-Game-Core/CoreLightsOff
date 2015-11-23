//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███                                                  //
//            █ █        █ █        GameCore.cpp                              //
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

//Header
#include "../include/GameCore.h"

//std
#include <sstream>

//Usings.
USING_NS_LIGHTSOFFCORE;
USING_NS_CORECOORD;

// Constants //
const int GameCore::kUnlimitedMoves = -1;

// CTOR/DTOR //
GameCore::GameCore(const ILevelLoader &loader,
                   int maxMoves /* = kUnlimitedMoves */) :

    m_board        (loader.getBoard()),
    m_lightsOnCount(loader.getLightsOnCount()),
    m_lightOffCount(loader.getLightsOffCount()),
    m_status       (Status::Continue),
    m_movesCount   (0),
    m_maxMovesCount(maxMoves)
{
    //Empty...
}

// Public Methods //
const Light::Board& GameCore::getBoard() const
{
    return m_board;
}

Coord::Vec GameCore::changeLightStateAt(const Coord &coord)
{
    //All coords for lights that changed the state.
    Coord::Vec affectedCoords;

    //No valid coord, no affected coords.
    //Game is over, no affected coords.
    if(!isValidCoord(coord) || m_status != Status::Continue)
        return affectedCoords;

    //Get the light at coord and all the coords that
    //this light will affect if change the state.
    auto light = getLightAt(coord);

    //Remove the coords that is not valid in this board.
    for(auto &offsetCoord : light.getAffectOffsetRange())
    {
        auto rangeCoord = (coord + offsetCoord);
        if(isValidCoord(rangeCoord))
            affectedCoords.push_back(rangeCoord);
    }

    //Change the state of the affected ligths.
    affectedCoords.push_back(coord); //Add the original coord to affected list.
    for(auto affectCoord : affectedCoords)
    {
        auto &affectedLight = getLightAt(affectCoord);
        changeLightStateHelper(const_cast<Light &>(affectedLight));
    }

    //Move was performed.
    ++m_movesCount;

    //Check the current game status.
    checkStatus();

    return affectedCoords;
}

const Light& GameCore::getLightAt(const Coord &coord) const
{
    return m_board.at(coord.y).at(coord.x);
}

int GameCore::getLightsOnCount() const
{
    return m_lightsOnCount;
}
int GameCore::getLightsOffCount() const
{
    return m_lightOffCount;
}

Status GameCore::getStatus() const
{
    return m_status;
}

int GameCore::getMovesCount() const
{
    return m_movesCount;
}
int GameCore::getMaxMovesCount() const
{
    return m_maxMovesCount;
}

bool GameCore::isValidCoord(const Coord &coord) const
{
    //Must be inside of bounds of board.
    return (coord.y >= 0 && coord.y < static_cast<int>(m_board.size()))
        && (coord.x >= 0 && coord.x < static_cast<int>(m_board[coord.y].size()));
}

std::string GameCore::ascii() const
{
    std::stringstream ss;

    for(auto &line : m_board)
    {
        for(auto &light : line)
        {
            ss << (light.isOn() ? "o "  : ". ");
        }
        ss << std::endl;
    }

    return ss.str();
}

// Private Methods //
void GameCore::changeLightStateHelper(Light &light)
{
    //Light as 2 possible states and transitions.
    // On  -> Off. Decrement the On value and Increment the Off.
    // Off -> On.  Decrement the Off value and Increment the On.
    if(light.isOn())
    {
        --m_lightsOnCount;
        ++m_lightOffCount;
    }
    else
    {
        ++m_lightsOnCount;
        --m_lightOffCount;
    }

    light.changeState();
}

void GameCore::checkStatus()
{
    //No lights on - Game is over - Player Won.
    if(m_lightsOnCount == 0)
    {
        m_status = Status::Victory;
        return;
    }

    //Has lights on - Player exceeds the max moves - Player Lose
    if(m_maxMovesCount != kUnlimitedMoves && m_movesCount >= m_maxMovesCount)
    {
        m_status = Status::Defeat;
        return;
    }

    //Has lights on but unlimited moves... Keep playing....
}
