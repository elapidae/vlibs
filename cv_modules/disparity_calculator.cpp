#include "disparity_calculator.hpp"

#include "calibration.hpp"

Disparity_calculator::Disparity_calculator( std::string path_for_calib_matrix, cv::Size size )
    :
      left_matcher( cv::StereoBM::create() )
{
    // Устанавливаем параметры обработчика стереопары. Данные параметры необходимо подбирать эмпирическим путем.
    left_matcher->setBlockSize(39);
    left_matcher->setMinDisparity(12);
    left_matcher->setNumDisparities(192);
    left_matcher->setDisp12MaxDiff(209);
    left_matcher->setSpeckleRange(120);
    left_matcher->setSpeckleWindowSize(1088);
    left_matcher->setUniquenessRatio(1);
    left_matcher->setPreFilterCap(63);
    left_matcher->setPreFilterSize(21);


    // создаём необходимые объекты для фильтрации карты глубины
    right_matcher = cv::ximgproc::createRightMatcher( left_matcher );
    wls_filter = cv::ximgproc::createDisparityWLSFilter( left_matcher );

    // Задаём эмпирически найденные параметры фильтра
    wls_filter->setLambda( 20.1 );
    wls_filter->setSigmaColor( 0.1 );

    // Читаем из файловой системы калибровочные матрицы
    cv_calib::configure_calib_matrix( path_for_calib_matrix, size, Q, leftMatX, leftMatY, rightMatX, rightMatY );
}

void Disparity_calculator::calcualte( Stereo_pair_builder::Stereo_pair pair )
{
    disparity_received( operator<<( pair ) );
}

Disparity_calculator::Disparity Disparity_calculator::operator <<( Stereo_pair_builder::Stereo_pair pair )
{
    auto left_frame = pair.left.img;
    auto right_frame = pair.right.img;

//    vdeb << left_frame.type();
//    cv::cvtColor( left_frame, left_frame, cv::COLOR_BGR2GRAY );
//    vdeb << left_frame.type();
//    cv::cvtColor( right_frame, right_frame, cv::COLOR_BGR2GRAY );

    // Выполняем ремаппинг кадров для дальнейшей обработки алгоритмами стереозрения. Суть ремаппинга заключается в том, чтобы
    // соответствующие точки между кадрами имели максимально наименьшую среднюю разницу по оси ординат.
    cv::Mat remapped_left, remapped_right;

    cv::remap( left_frame, remapped_left, leftMatX, leftMatY, cv::INTER_CUBIC );
    cv::remap( right_frame, remapped_right, rightMatX, rightMatY, cv::INTER_CUBIC );

    // Выравниваем гистограммы левого и правого изображения, необходимо уменьшения различий между кажрами, связанных с
    // выбором выдержки и экспозиции
    if ( remapped_left.channels() == 3 ) cv::cvtColor( remapped_left, remapped_left, cv::COLOR_BGR2GRAY );
    if ( remapped_right.channels() == 3 ) cv::cvtColor( remapped_right, remapped_right, cv::COLOR_BGR2GRAY );
    cv::equalizeHist( remapped_left, remapped_left );
    cv::equalizeHist( remapped_right, remapped_right );
//    cv::blur( remapped_left, remapped_left, cv::Size( 11, 11 ) );
//    cv::blur( remapped_right, remapped_right, cv::Size( 11, 11 ) );

    // Проверяем кадры на соответствие друг другу по формату
    if ( !( left_frame.size()     == right_frame.size() &&
            left_frame.channels() == right_frame.channels() &&
//            left_frame.channels() == 3 ) )
        left_frame.channels() != 1/*3*/ ) )
    {
        vdeb << "Different matrix params.";
        vdeb << "Left: "  << left_frame.size()  << left_frame.channels();
        vdeb << "Right: " << right_frame.size() << right_frame.channels();
    }

    left_frame = remapped_left.clone();
    right_frame = remapped_right.clone();
    cv::imwrite( "remappedL.png", left_frame );
    cv::imwrite( "remappedR.png", right_frame );

    // Вычисляем карту глубины в формате с плавающей точкой.
    // На данном этапе данные должны использоваться для определения расстояния
    // и 3D реконструкции, после нормализации данные пригодны лишь для визуализации

    cv::Mat left_disp, right_disp, filtered_disp;
    left_matcher->compute( left_frame, right_frame, left_disp );

    // Фитльтрация карты глубины

    right_matcher->compute( right_frame, left_frame, right_disp );

    wls_filter->filter( left_disp, left_frame, filtered_disp, right_disp );
    left_disp = filtered_disp;
    left_disp.convertTo( left_disp, CV_32F, 1.0 / 16 );

    // 3D реконструкция карты глубины в точки в мировыъх координатах
    cv::Mat points;
    cv::reprojectImageTo3D( left_disp, points, Q, false );

    // Создание структуры данных, описывающей карту глубины и другие результаты, вызов дальнейшего обработчика данных
    disparity = { pair, remapped_left, remapped_right, left_disp, points };
    return disparity;
}
