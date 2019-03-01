#include "four_images.h"




#include <QSplitter>
#include <QVBoxLayout>




//=======================================================================================
Four_Images::Four_Images()
{
    auto s1 = new QSplitter( Qt::Horizontal );
    auto s2 = new QSplitter( Qt::Horizontal );
    auto s  = new QSplitter( Qt::Vertical   );

    s1->addWidget( &i1 );
    s1->addWidget( &i2 );

    s2->addWidget( &i3 );
    s2->addWidget( &i4 );

    s->addWidget( s1 );
    s->addWidget( s2 );

    setLayout( new QVBoxLayout );
    layout()->setMargin( 0 );
    layout()->addWidget( s );
}
//=======================================================================================

