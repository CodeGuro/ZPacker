#include <iostream>
#include <ZPacker.hpp>

int main( int argc, char **argv )
{
	ZPacker packer;

	packer.pack_file( "example.bmp" );

	return 0;
}