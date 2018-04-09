#ifndef VIMAGE_H
#define VIMAGE_H

#include <memory>

//=======================================================================================
class VImage
{
public:
    using data_t = unsigned char;

    enum class Format
    {
        Invalid,
        Gray8,
        RGB888
    };

    virtual ~VImage() = default;

    virtual bool is_valid()         const = 0;

    virtual Format format()         const = 0;

    virtual int width()             const = 0;
    virtual int height()            const = 0;
    virtual int bytes_per_line()    const = 0;

    virtual const data_t* data()    const = 0;

    virtual const data_t* line(int row) const;

    virtual void detach() = 0;
};
//=======================================================================================



#endif // VIMAGE_H
