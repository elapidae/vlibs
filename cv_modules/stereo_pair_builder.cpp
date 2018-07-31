#include "stereo_pair_builder.hpp"

#include "vimage_opencv.h"
#include "vlog_pretty.h"

Stereo_pair_builder::Stereo_pair_builder()
{

}

void Stereo_pair_builder::make_pair( const Full_frame frame)
{
    if ( !frame.freerun_synced )
    {
        vdeb << "Cameras are not synchronized";
        return;
    }
    // Конвертируем пришедший кадр в матрицу OpenCV с типом CV8_UC1( чёрно-белое 8-битное )
//    auto basler_frame = frame.frame.convert_mono8();
//    VImage_Basler basler_img( basler_frame );

//    auto cv_frame = VImage_OpenCV::convert( basler_img );

    // В зависимости от местоположения кадра обновляем последний полученный кадр с левой или правой камер
    if ( frame.location == CAM_LOCATION::LEFT  ) last_left  = { frame.img.clone(), VTimePoint( frame.timestamp ) };
    if ( frame.location == CAM_LOCATION::RIGHT ) last_right = { frame.img.clone(), VTimePoint( frame.timestamp ) };

    // Вычисляем задержку между кадрами самостоятельно, условием синхронизации является зажержка не большеыы 10 миллисекунд
    auto delay = abs( ( last_left.timestamp - last_right.timestamp ).milliseconds().count() );
    if ( delay >= 20 )
    {
        vdeb << "Delay is too big: " << delay << " (ms))";
        vdeb << "Left  timestamp: " << last_left.timestamp.nanoseconds()  << "(ns)";
        vdeb << "Right timestamp: " << last_right.timestamp.nanoseconds() << "(ns)\n";
        return;
    }
    if ( !( last_left.img.size()     == last_right.img.size() &&
            last_left.img.channels() == last_right.img.channels()))
    {
        vdeb << "Bad pictures in stereo pair builder";
        return;
    }
    vdeb << "Stereo Pair created";
    vdeb << "Delay is" << delay << "\n";

    // Вызываем дальнейший обрабочик полученной синхронизированной стереопары
    pair_received( { last_left, last_right } );
}
