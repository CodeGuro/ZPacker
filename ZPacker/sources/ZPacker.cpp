#include <zlib.h>
#include <ZPacker.hpp>
#include <string>
#include <stdlib.h>
#include <fstream>

// default constructor
ZPacker::ZPacker()
{
}

void ZPacker::pack_file( std::string filepath )
{
	// initialize
	std::ifstream input = std::ifstream( filepath, std::ios::binary );
	std::ofstream output = std::ofstream( filepath + ".zlib", std::ios::binary );
	if( !input.is_open() )
		return;
	void *buffer = malloc( 1024 * 1024 );
	z_stream_s z_stream_state;
	memset( &z_stream_state, 0, sizeof( z_stream_s ) );
	z_stream_state.zalloc = Z_NULL;
	z_stream_state.zfree = Z_NULL;
	z_stream_state.opaque = Z_NULL;
	if( deflateInit( &z_stream_state, Z_BEST_COMPRESSION ) != Z_OK )
		return;

	// TODO: perform compression

	// destroy
	deflateEnd( &z_stream_state );
	free( buffer );
	output.close();
	input.close();
}

void ZPacker::unpack_file( std::string filepath )
{
	// TODO: write function
}