//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        FileLevelLoader.cpp                       //
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

//Header
#include "../include/FileLevelLoader.h"
//CoreCoord.
#include "CoreCoord.h"
//std
#include <fstream>
#include <system_error>

//Usings.
USING_NS_CORELIGHTSOFF;
USING_NS_CORECOORD;


// Constants //
const char FileLevelLoader::kLightOnChar  = 'o';
const char FileLevelLoader::kLightOffChar = '.';


// CTOR/DTOR //
FileLevelLoader::FileLevelLoader(const std::string &filename) :
    m_lightsOnCount (0),
    m_lightsOffCount(0)
{
    std::ifstream infile(filename.c_str());

    //Check file existence.
    if(!infile)
    {
        auto errcode = std::make_error_code(std::errc::no_such_file_or_directory);
        throw std::system_error(errcode, filename);
    }

    auto orthogonalCoords = Coord().getOrthogonal();

    for(std::string line; std::getline(infile, line); /*None*/ )
    {
        //Create a row of lights...
        m_board.push_back(std::vector<Light>());

        for(auto &ch : line)
        {
            auto isOn = ch == FileLevelLoader::kLightOnChar;

            auto light = Light(isOn, orthogonalCoords);
            m_board[m_board.size()-1].push_back(light);

            m_lightsOnCount  += (isOn) ? 1 : 0;
            m_lightsOffCount += (isOn) ? 0 : 1;
        }
    }
}

FileLevelLoader::~FileLevelLoader()
{
    //Empty...
}


// Overriden Methods //
const Light::Board& FileLevelLoader::getBoard() const
{
    return m_board;
}
int FileLevelLoader::getLightsOnCount() const
{
    return m_lightsOnCount;
}
int FileLevelLoader::getLightsOffCount() const
{
    return m_lightsOffCount;
}
