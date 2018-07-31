#include "projection_creator.hpp"
#include "range.hpp"

Projection_creator::Projection_creator(
        unsigned int roi_width, unsigned int roi_depth,
        double min_height, double max_height, unsigned int levels_count,
        double how_much_pixels_in_meter , double theta_x, double theta_y, double theta_z )
    :
      roi_width( roi_width ),
      roi_depth( roi_depth ),
      min_height( min_height ),
      max_height( max_height ),
      levels_count( levels_count ),
      how_much_pixels_in_meter( how_much_pixels_in_meter ),
      kernel_size( 3 ),
      theta_x( theta_x ),
      theta_y( theta_y ),
      theta_z( theta_z )
{
}

void Projection_creator::update_parameters(
        unsigned int new_roi_width, unsigned int new_roi_depth,
        double new_min_height, double new_max_height,
        unsigned int new_levels_count, double new_how_much_pixels_in_meter, int new_kernel_size,
        double new_theta_x, double new_theta_y, double new_theta_z )
{
    roi_width = new_roi_width;
    roi_depth = new_roi_depth;
    min_height = new_min_height;
    max_height = new_max_height;
    levels_count = new_levels_count;
    kernel_size = new_kernel_size;
    how_much_pixels_in_meter = new_how_much_pixels_in_meter;
    theta_x = new_theta_x;
    theta_y = new_theta_y;
    theta_z = new_theta_z;
    vdeb << "Projection creator: all parameters are updated";
}

void Projection_creator::calculate_projections( Disparity_calculator::Disparity disparity )
{
    projection_received( operator<<( disparity ) );
}

Projection_creator::Projection Projection_creator::operator<<( Disparity_calculator::Disparity disparity )
{
    int tmp_levels_count = levels_count;
    unsigned int cx = roi_width / 2;
    unsigned int cy = 0;

    cv::Mat height_on_frame_map = cv::Mat::zeros( disparity.left_remapped.size(), disparity.left_remapped.type() );
    cv::Mat top_down_projection = cv::Mat::zeros( roi_depth+1, roi_width+1, CV_8U );

    std::vector< Range< double > > height_ranges;
    std::vector< cv::Mat > height_masks;

    double step = ( max_height - min_height ) / levels_count;
    for ( unsigned int i = 0; i < levels_count; i++ )
    {
        height_ranges.push_back( { step * i, step * ( i + 1 ) } );
        height_masks.push_back( cv::Mat::zeros( top_down_projection.size(), top_down_projection.type() ) );
    }

    // Создаём проекции вида сверху
    for ( unsigned int i = 0; i < disparity.points.rows; i++ )
    {
        for ( unsigned int j = 0; j < disparity.points.cols; j++ )
        {
            auto x = disparity.points.at< cv::Vec3f >( i, j )[0];
            auto z = disparity.points.at< cv::Vec3f >( i, j )[2];
            auto h = disparity.points.at< cv::Vec3f >( i, j )[1];

            auto thetaX = theta_x;
            auto thetaY = theta_y;
            auto thetaZ = theta_z;

            x = x*cos( thetaZ ) - h*sin( thetaZ );
            h = x*sin( thetaZ ) + h*cos( thetaZ );

            x = x*cos( thetaY ) - z*sin( thetaY );
            z = x*sin( thetaY ) + z*cos( thetaY );

            h = h*cos( thetaX ) - z*sin( thetaX );
            z = h*sin( thetaX ) + z*cos( thetaX );

            if ( z * how_much_pixels_in_meter + cy < roi_depth &&
                 z * how_much_pixels_in_meter + cy > 0 &&
                 x * how_much_pixels_in_meter + cx < roi_width &&
                 x * how_much_pixels_in_meter + cx > 0 )
            {
                double x_double = ( x * how_much_pixels_in_meter + cx );
                double y_double = h;
                double z_double = ( z * how_much_pixels_in_meter + cy );

                int x = x_double;
                int z = z_double;

                if ( h >= min_height )
                {
                    if ( h <= max_height )
                    {
                        int current_height = ( uchar )( ( y_double - min_height ) / ( max_height - min_height ) * 255.0 );
                        height_on_frame_map.at< uchar >( i, j ) = current_height;

                        for ( unsigned int i = 0; i < tmp_levels_count; i ++ )
                        {
                            if ( height_ranges[i].in_range( y_double ) )
                            {
                                height_masks[i].at< uchar >( roi_depth - z, x ) = 255;
                            }
                        }
                    }
                }
            }
        }
    }

    if ( kernel_size > 0 )
    {
        cv::Mat rect = cv::getStructuringElement( cv::MORPH_RECT, cv::Size( kernel_size + 1 - kernel_size % 2, kernel_size + 1 - kernel_size % 2 ) );
        vdeb << "Kernel: " << kernel_size;
        for ( unsigned int i = 0; i < tmp_levels_count; i ++ )
        {
            cv::dilate( height_masks[i], height_masks[i], rect );
        }
    }

    Projection_creator::Projection projection = {
        disparity,
        height_masks,
        height_on_frame_map,
        min_height, max_height,
        cx, cy, 0, how_much_pixels_in_meter
    };

    return projection;
}
