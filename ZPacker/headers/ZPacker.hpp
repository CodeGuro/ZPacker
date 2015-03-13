#ifndef ZPACKER_HPP
#define ZPACKER_HPP

#include <string>

class ZPacker
{
private:
public:
	enum Mode
	{
		pack, unpack
	};
	ZPacker();
	void process_file( std::string destfilepath, std::string filepath, Mode mode );
};

#endif