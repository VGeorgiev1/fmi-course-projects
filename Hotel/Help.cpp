#include <iostream>
#include "Help.h"

Help::Help(Hotel& h)
	: FileOperation(h, "help") {};

void Help::execute() {

	std::cout << "open <file>                                    - opens <file>" << std::endl;
	std::cout << "close                                          - closes currently opened file" << std::endl;
	std::cout << "save		                                     - saves the currently open file"  << std::endl;
	std::cout << "saveas <file>                                  - saves the currently open file in <file>" << std::endl;
	std::cout << "checkin <room> <from> <to> <note> [<guests>]   - register room with number <room> from date <from> to <date> with <note> for <guests>" << std::endl;
	std::cout << "availability [<date>]                          - return list of free rooms for <date>" << std::endl;
	std::cout << "report <from> <to>                             - prints busy rooms for period <from> to <to>" << std::endl;
	std::cout << "find <beds> <from> <to>                        - finds a room with <beds> from <from> to <to>" << std::endl;
	std::cout << "find!<beds> <from> <to>                        - finds a room with <beds> from <from> to <to> even if moving guests is required" << std::endl;
	std::cout << "unavailable <room> <from> <to> <note>          - marks room with number <room> unavailable from <from> to <to>" << std::endl;
	
}