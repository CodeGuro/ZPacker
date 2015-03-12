#ifndef ZPACKER_HPP
#define ZPACKER_HPP

#include <string>

class ZPacker
{
private:
public:
	ZPacker();
	void pack_file( std::string filepath );
	void unpack_file( std::string filepath );
};

#endif