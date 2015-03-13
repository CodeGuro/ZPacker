#include <iostream>
#include <ZPacker.hpp>

int main( int argc, char **argv )
{
	ZPacker packer;

	packer.process_file( "example.bmp.zlib", "example.bmp", packer.pack );
	packer.process_file( "example(unpacked).bmp", "example.bmp.zlib", packer.unpack );

	return 0;
}