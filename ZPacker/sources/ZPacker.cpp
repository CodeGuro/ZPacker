#include <zlib.h>
#include <ZPacker.hpp>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <assert.h>

// callbacks
int inflateInitCB( z_stream_s *strm )
{
	return inflateInit( strm );
}

int deflateInitCB( z_stream_s *strm )
{
	return deflateInit( strm, Z_BEST_COMPRESSION );
}

int inflateEndCB( z_stream_s *strm )
{
	return inflateEnd( strm );
}

int deflateEndCB( z_stream_s *strm )
{
	return deflateEnd( strm );
}

// default constructor
ZPacker::ZPacker()
{
}

void ZPacker::process_file( std::string destfilepath, std::string filepath, Mode mode )
{
	// initialize
	typedef int (*callback)( z_stream_s* );
	callback initfunc = mode == pack ? deflateInitCB : inflateInitCB;
	callback destroyfunc = mode == pack ? deflateEndCB : inflateEndCB;
	int ZEXPORT (*operationCB)( z_stream_s*, int ) = mode == pack ? deflate : inflate;
	bool finished = false;
	std::ifstream input = std::ifstream( filepath, std::ios::binary );
	std::ofstream output = std::ofstream( destfilepath, std::ios::binary );
	if( !input.is_open() )
		return;
	const unsigned buffer_size = 1 << 20;
	Bytef *input_buffer = (Bytef*)malloc( buffer_size );
	Bytef *output_buffer = (Bytef*)malloc( buffer_size );
	z_stream_s z_stream_state;
	memset( &z_stream_state, 0, sizeof( z_stream_s ) );
	z_stream_state.zalloc = Z_NULL;
	z_stream_state.zfree = Z_NULL;
	z_stream_state.opaque = Z_NULL;
	if( initfunc( &z_stream_state ) != Z_OK )
		return;

	do
	{
		unsigned bytes_read;
		if( z_stream_state.avail_in == 0 )
		{
			input.read( (char*)input_buffer, buffer_size );
			bytes_read = (unsigned)input.gcount();
			z_stream_state.next_in = input_buffer;
			z_stream_state.avail_in = bytes_read;
		}
		do
		{
			z_stream_state.avail_out = buffer_size;
			z_stream_state.next_out = output_buffer;
			int res = operationCB( &z_stream_state, bytes_read > 0 ? Z_NO_FLUSH : Z_FINISH );
			assert( res == Z_OK || res == Z_STREAM_END );

			output.write( (const char*)output_buffer,
				buffer_size - z_stream_state.avail_out );

			if( res == Z_STREAM_END )
			{
				finished = true;
				break;
			}
		} while( z_stream_state.avail_out == 0 );
	} while( !finished );

	// destroy
	destroyfunc( &z_stream_state );
	free( output_buffer );
	free( input_buffer );
	output.close();
	input.close();
}