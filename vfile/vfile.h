#ifndef VFILE_H
#define VFILE_H

//=======================================================================================
//  TODO: утащить все сырые посиксовые неприятности в vposix_files.
//
//=======================================================================================


#include <string>


//=======================================================================================
namespace tr1
{
    //===================================================================================
    class VFile
    {
    public:
        using cstr = const std::string&;

        enum class Mode_ReadWrite { ReadOnly, WriteOnly, ReadWrite };
        //enum class Mode_Exclusive { Yes, No };

        //VFile( cstr fname, Mode_ReadWrite rw, Mode_Exclusive exclusive );
        VFile( cstr fname, Mode_ReadWrite rw = Mode_ReadWrite::ReadWrite );

        void write( cstr buffer );

    private:
        int _fd = 0;

        struct helpers
        {
            static int mode_readwrite( Mode_ReadWrite mode );
            //static int mode_exclusive( Mode_Exclusive mode );
        };
    };
    //===================================================================================
    //class VFileExclusive : public VFile
    //{
    //public:
    //    VFileExclusive( cstr fname, Mode_ReadWrite rw = Mode_ReadWrite::ReadWrite );
    //};
    //===================================================================================

} // namespace tr1
//=======================================================================================


#endif // VFILE_H
