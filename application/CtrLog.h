//------------------------------------------------------------------------------------//
//                                                                                    //
//               _________        .__  __    __                                       //
//               \_   ___ \_______|__|/  |__/  |_  ___________                        //
//               /    \  \/\_  __ \  \   __\   __\/ __ \_  __ \                       //
//               \     \____|  | \/  ||  |  |  | \  ___/|  | \/                       //
//                \______  /|__|  |__||__|  |__|  \___  >__|                          //
//                       \/                           \/                              //
//                                                                                    //
//    Critter is provided under the MIT License(MIT)                                  //
//    Critter uses portions of other open source software.                            //
//    Please review the LICENSE file for further details.                             //
//                                                                                    //
//    Copyright(c) 2015 Matt Davidson                                                 //
//                                                                                    //
//    Permission is hereby granted, free of charge, to any person obtaining a copy    //
//    of this software and associated documentation files(the "Software"), to deal    //
//    in the Software without restriction, including without limitation the rights    //
//    to use, copy, modify, merge, publish, distribute, sublicense, and / or sell     //
//    copies of the Software, and to permit persons to whom the Software is           //
//    furnished to do so, subject to the following conditions :                       //
//                                                                                    //
//    1. Redistributions of source code must retain the above copyright notice,       //
//    this list of conditions and the following disclaimer.                           //
//    2. Redistributions in binary form must reproduce the above copyright notice,    //
//    this list of conditions and the following disclaimer in the                     //
//    documentation and / or other materials provided with the distribution.          //
//    3. Neither the name of the copyright holder nor the names of its                //
//    contributors may be used to endorse or promote products derived                 //
//    from this software without specific prior written permission.                   //
//                                                                                    //
//    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      //
//    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        //
//    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE      //
//    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          //
//    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   //
//    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN       //
//    THE SOFTWARE.                                                                   //
//                                                                                    //
//------------------------------------------------------------------------------------//
#ifndef BB_LOG
#define BB_LOG

#include <CtrPlatform.h>

namespace Ctr
{

	//-----------------------------------------------------------
	// class Log
	// Very, very simple and dumb logging to file wrapper.
	// Not threadsafe. Prints to std out along with file io.
	//-----------------------------------------------------------
	enum LogLevel
	{
		InfoEntry = 0,
		WarningEntry = 1,
		CriticalEntry = 2
	};

	class Log
	{
	public:
		/** Pass an empty filename to disable logging*/
		static void                initialize(const std::string& logFilePathName, const LogLevel loggingLevel);

		static void                write(const std::string& s, Ctr::LogLevel level = Ctr::InfoEntry);

	private:
		static bool                _initialized;
		static std::string         _filePathName;
		static LogLevel        _logLevel;
	};

#define LOG(text)                                     \
{                                                     \
    std::ostringstream s;                             \
    s << text << "\0";                                \
    Ctr::Log::write (std::string(s.str().c_str()),Ctr::InfoEntry);   \
}

#define LOG_WARNING(text)                                  \
{                                                          \
    std::ostringstream s;                                  \
    s << text << "\0";                                     \
    Ctr::Log::write (std::string(s.str().c_str()), Ctr::WarningEntry); \
}

#define LOG_CRITICAL(text)                                \
{                                                          \
    std::ostringstream s;                                  \
    s << text << "\0";                                     \
    Ctr::Log::write (std::string(s.str().c_str()), Ctr::CriticalEntry); \
}

#define IBLASSERT(expression, text) \
{                                   \
    if (!expression)                \
        LOG_CRITICAL(text)          \
    assert(expression);             \
} 

}

#endif