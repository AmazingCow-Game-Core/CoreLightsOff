//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        GameCore.h                                //
//            █ █        █ █        CoreLightsOff                             //
//             ████████████                                                   //
//           █              █       Copyright (c) 2015, 2016                  //
//          █     █    █     █      AmazingCow - www.AmazingCow.com           //
//          █     █    █     █                                                //
//           █              █       N2OMatt - n2omatt@amazingcow.com          //
//             ████████████         www.amazingcow.com/n2omatt                //
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
//        The email is: acknowledgment_opensource@AmazingCow.com              //
//     3. Altered source versions must be plainly marked as such,             //
//        and must not be misrepresented as being the original software.      //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//

#ifndef __CoreLightsOff_include_GameCore_h__
#define __CoreLightsOff_include_GameCore_h__

//std
#include <string>
//CoreLightsOff.
#include "CoreLightsOff_Utils.h"
#include "ILevelLoader.h"
#include "Light.h"
#include "Status.h"
//CoreCoord.
#include "CoreCoord.h"


NS_CORELIGHTSOFF_BEGIN

class GameCore
{
    // Constants //
public:
    ///@brief A meta value meaning that player can play indefinitely.
    ///@see GameCore::GameCore
    static const int kUnlimitedMoves;


    // CTOR/DTOR //
public:
    ///@brief Constructs the GameCore.
    ///@param loader
    ///     A ILevelLoader subclass that loads the board.
    ///@param maxMoves
    //      How many tries player has to win the game -
    ///     Default GameCore::kUnlimitedMoves
    ///@note
    ///     If the loader throws an exception, it will NOT be
    ///     by the GameCore - So is users reponsability to handle them.
    ///@see GameCore::kUnlimitedMoves, ILevelLoader, FileLevelLoader.
    GameCore(const ILevelLoader &loader, int maxMoves = kUnlimitedMoves);


    // Public Methods //
public:
    ///@brief Gets the current state of Board.
    ///@returns The current Board.
    const Light::Board& getBoard() const;


    ///@brief Change the state of Light at coord.
    ///@param coord
    ///     A valid coord, otherwise nothing will be done.
    ///@returns
    ///     A vector of affected coords, i.e. the coords lights that
    ///     changed the state.
    ///@see GameCore::isValidCoord.
    CoreCoord::Coord::Vec changeLightStateAt(const CoreCoord::Coord &coord);


    ///@brief Gets the light at the given coord.
    ///@param coord
    ///     A valid coord, otherwise an exception will be thrown.
    ///@returns
    ///     The light reference.
    ///@see GameCore::isValidCoord.
    const Light& getLightAt(const CoreCoord::Coord &coord) const;

    ///@brief Gets the number of Lights on.
    ///@returns The number of Lights on.
    ///@see GameCore::getLightsOffCount.
    int getLightsOnCount() const;

    ///@brief Gets the number of Lights off.
    ///@returns The number of Lights off.
    ///@see GameCore::getLightsOnCount.
    int getLightsOffCount() const;


    ///@brief Get the current status of game.
    ///@returns the current status of game.
    ///@see
    ///     Status, GameCore::getMovesCount,
    ///     GameCore::getMaxMovesCount, GameCore::kUnlimitedMoves.
    Status getStatus() const;


    ///@brief Get how many moves the player did so far.
    ///@returns The number of player's moves.
    ///@see
    ///     Status, GameCore::getMaxMovesCount,
    ///     GameCore::kUnlimitedMoves.
    int getMovesCount() const;

    ///@brief Get how many moves the player can do.
    ///@returns
    ///     The number of moves or GameCore::kUnlimitedMoves
    ///     if there is no restriction..
    ///@see
    ///     Status, GameCore::getMovesCount,
    ///     GameCore::kUnlimitedMoves
    int getMaxMovesCount() const;


    ///@brief Check if a given coord is inside of Board bounds.
    ///@returns true if coord is valid, false otherwise.
    bool isValidCoord(const CoreCoord::Coord &coord) const;


    ///@brief Return a nice string representation.
    std::string ascii() const;


    // Private Methods //
private:
    void changeLightStateHelper(Light &light);
    void checkStatus();


    // iVars //
private:
    Light::Board m_board;

    int m_lightsOnCount;
    int m_lightOffCount;

    Status m_status;

    int m_movesCount;
    int m_maxMovesCount;
};


NS_CORELIGHTSOFF_END
#endif // defined(__CoreLightsOff_include_GameCore_h__) //
