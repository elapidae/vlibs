/****************************************************************************************
**
**  VLIBS codebase, NIIAS
**
**  Authors:
**  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
**  Nadezhda Churikova aka claorisel    claorisel@gmail.com
**  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
**  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
**
**  GNU Lesser General Public License Usage
**  This file may be used under the terms of the GNU Lesser General Public License
**  version 3 as published by the Free Software Foundation and appearing in the file
**  LICENSE.LGPL3 included in the packaging of this file. Please review the following
**  information to ensure the GNU Lesser General Public License version 3 requirements
**  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************************/


#include "vjpeg.h"

#include <assert.h>
#include <string.h>
#include "voutfile.h"
#include "vlog.h"
#include "verror.h"

#include <setjmp.h>
extern "C"
{
    #include <jpeglib.h>
}

//=======================================================================================
/*  02-04-2018
 *  Код нагло взят из Qt. Самому управлялку к этому трешу написать сложновато будет.
 *  Только код подкорректировал, чтобы не использовать new|delete.
 *  Авторы jpeg используют setjmp/longjmp для сообщений об ошибках. Соответственно,
 *  грозят утечки памяти, инварианта и т.д. Мне не удалось вызвать ошибки кодирования,
 *  чтобы проверить на утечки, если будет оказия, делитесь способом.
*/
//=======================================================================================



//=======================================================================================
static constexpr auto max_buf = 4096;
struct my_jpeg_destination_mgr : public jpeg_destination_mgr
{
    // Nothing dynamic - cannot rely on destruction over longjump
    std::string *std_buf;
    JOCTET buffer[max_buf];

public:
    my_jpeg_destination_mgr( std::string * );
};
//=======================================================================================
extern "C"
{
    //-----------------------------------------------------------------------------------
    static void qt_init_destination(j_compress_ptr)
    {}
    //-----------------------------------------------------------------------------------
    static boolean qt_empty_output_buffer( j_compress_ptr cinfo )
    {
        auto * dest = static_cast<my_jpeg_destination_mgr*>(cinfo->dest);

        auto * ch = static_cast<const char*>( static_cast<const void*>(dest->buffer) );
        dest->std_buf->append( ch, max_buf );

        dest->next_output_byte = dest->buffer;
        dest->free_in_buffer = max_buf;

        return TRUE;
    }
    //-----------------------------------------------------------------------------------
    static void qt_term_destination( j_compress_ptr cinfo )
    {
        auto * dest = static_cast<my_jpeg_destination_mgr*>(cinfo->dest);
        auto n = max_buf - dest->free_in_buffer;

        auto * ch = static_cast<const char*>( static_cast<const void*>(dest->buffer) );
        dest->std_buf->append( ch, n );
    }
    //-----------------------------------------------------------------------------------
}
//=======================================================================================
my_jpeg_destination_mgr::my_jpeg_destination_mgr( std::string *buf )
{
    jpeg_destination_mgr::init_destination    = qt_init_destination;
    jpeg_destination_mgr::empty_output_buffer = qt_empty_output_buffer;
    jpeg_destination_mgr::term_destination    = qt_term_destination;
    std_buf = buf;
    next_output_byte = buffer;
    free_in_buffer   = max_buf;
}
//=======================================================================================
struct my_error_mgr : public jpeg_error_mgr
{
    jmp_buf setjmp_buffer;
};
//=======================================================================================
extern "C"
{
    [[noreturn]]
    static void my_error_exit( j_common_ptr cinfo )
    {
        my_error_mgr* myerr = static_cast<my_error_mgr*>( cinfo->err );
        char buffer[JMSG_LENGTH_MAX];
        (*cinfo->err->format_message)(cinfo, buffer);
        vfatal << buffer;
        longjmp( myerr->setjmp_buffer, 1 );
    }

    static void my_output_message( j_common_ptr cinfo )
    {
        char buffer[JMSG_LENGTH_MAX];
        (*cinfo->err->format_message)(cinfo, buffer);
        vfatal << buffer;
    }
} // extern C
//=======================================================================================


//=======================================================================================
bool VJpeg::save_to_buffer( const VImage &img,
                            std::string *out,
                            int sourceQuality,
                            VJpeg::_optimize optimize,
                            VJpeg::_progressive progressive )
{
    if ( img.format() == VImage::Format::Invalid ) return false;

    jpeg_compress_struct cinfo;

    struct my_error_mgr jerr;

    cinfo.err = jpeg_std_error( &jerr );
    jerr.error_exit = my_error_exit;
    jerr.output_message = my_output_message;


    // Условие проверяет наличие ошибки, был ли контекст вызван longjmp.
    // Если да,  контекст был создан и были к-л неприятности.
    if ( setjmp(jerr.setjmp_buffer) )
    {
        jpeg_destroy_compress ( &cinfo );
        return false;
    }

    ///////////////////////////
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wold-style-cast"
    // WARNING:
    // this if loop is inside a setjmp/longjmp branch
    // do not create C++ temporaries here because the destructor may never be called
    // if you allocate memory, make sure that you can free it (row_pointer[0])
    jpeg_create_compress( &cinfo );

    #pragma GCC diagnostic pop
    ///////////////////////////

    my_jpeg_destination_mgr iod_dest( out );
    cinfo.dest = &iod_dest;

    cinfo.image_width  = uint( img.width()  );
    cinfo.image_height = uint( img.height() );

    cinfo.density_unit = 0; // dots/inch == unknown
    cinfo.X_density = 0;
    cinfo.Y_density = 0;

    switch ( img.format() )
    {
    case VImage::Format::Gray_8:
        cinfo.input_components = 1;
        cinfo.in_color_space = JCS_GRAYSCALE;
        break;
    case VImage::Format::RGB_888:
        cinfo.input_components = 3;
        cinfo.in_color_space = JCS_RGB;
        break;
    default:
        vfatal("Cannot define jpeg color type");
        exit(1);
    }

    jpeg_set_defaults( &cinfo );

    cinfo.optimize_coding = optimize == Optimize ? true : false;

    if ( progressive == Progressive )
        jpeg_simple_progression( &cinfo );

    //jpeg_set_linear_quality( &cinfo, 100, TRUE );
    //cinfo.dct_method = J_DCT_METHOD::JDCT_FLOAT;
    //throw VLogError(vfatal << );

    int quality = sourceQuality >= 0 ? std::min(sourceQuality,100) : 75;
    jpeg_set_quality( &cinfo, quality, TRUE );
    jpeg_start_compress( &cinfo, TRUE );

    uint line_size = cinfo.image_width * uint(cinfo.input_components);

    ///////////////////////////
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wvla"
    //#pragma GCC diagnostic ignored "-Wvla-extension"
    JSAMPROW row_pointer[1] = {nullptr};
    //unsigned char buf[ line_size ];
    //row_pointer[0] = new unsigned char[ line_size ];
    //row_pointer[0] = buf;
    (void)(line_size);
    #pragma GCC diagnostic pop
    ///////////////////////////

    auto row_bytes = size_t(cinfo.input_components) * cinfo.image_width;
    while ( cinfo.next_scanline < cinfo.image_height )
    {
        // Проверка показывает, что scanlines не изменяет буфера, сделан const_cast хак.
        // В результате, накинулось процентов пять-семь по производительности.
        auto src = img.line( int(cinfo.next_scanline) );
        row_pointer[0] = const_cast<unsigned char*>( src );
        //std::copy( src, src + row_bytes, row_pointer[0] );

        ////////////////////////////
        //std::string before( src, src + row_bytes );
        ////////////////////////////

        jpeg_write_scanlines( &cinfo, row_pointer, 1 );

        ////////////////////////////
        //std::string after( (char*)row_pointer[0], row_bytes );
        //assert( before == after );
        ////////////////////////////
    } // for all scanlines.

    jpeg_finish_compress  ( &cinfo );
    jpeg_destroy_compress ( &cinfo );

//    if ( row_pointer[0] )
//        delete [] row_pointer[0];

    (void)(row_bytes); // unused method;
    return true;
}
//=======================================================================================
std::string VJpeg::save_to_buffer( const VImage &img,
                                   int quality,
                                   VJpeg::_optimize optimize,
                                   VJpeg::_progressive progressive )
{
    std::string res;
    auto ok = save_to_buffer( img, &res, quality, optimize, progressive );
    if (!ok) throw verror << "Error during jpeg coding.";
    return res;
}
//=======================================================================================
bool VJpeg::save_to_file( const VImage &img,
                          const std::string &fname,
                          int quality,
                          VJpeg::_optimize optimize,
                          VJpeg::_progressive progressive )
{
    std::string res;
    auto ok = save_to_buffer( img, &res, quality, optimize, progressive );
    if (!ok) return false;

    VOutFile f( fname );
    f.write( res );

    return f.is_good();
}
//=======================================================================================
