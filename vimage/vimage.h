#ifndef VIMAGE_H
#define VIMAGE_H

#include <memory>

//=======================================================================================
class VImage
{
public:
    class Impl;
    using Impl_Ptr = std::shared_ptr<Impl>;
    using data_t = unsigned char;

    enum class Format
    {
        Invalid,
        Gray8,
        RGB888
    };

    explicit VImage();
    explicit VImage( Impl_Ptr && ptr );
    explicit VImage( const Impl_Ptr& ptr );
    virtual ~VImage();

    bool is_valid()             const;

    Format format()             const;

    int width()                 const;
    int height()                const;
    int bytes_per_line()        const;

    const data_t* data()        const;

    const data_t* line(int row) const;

    void detach();

private:
     Impl_Ptr p;
};
//=======================================================================================
class VImage::Impl
{
public:
    virtual ~Impl();
    virtual Format format()         const = 0;

    virtual int width()             const = 0;
    virtual int height()            const = 0;
    virtual int bytes_per_line()    const = 0;

    virtual const data_t* data()    const = 0;

    virtual const data_t* line(int row) const;

    virtual Impl_Ptr copy()               = 0;
};
//=======================================================================================


#endif // VIMAGE_H
