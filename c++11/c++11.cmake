#========================================================================================
if ( NOT  CPP_11_STANDARD_INCLUDED )
    set ( CPP_11_STANDARD_INCLUDED TRUE )

    message( "add_definitions -std=c++11" )

    add_definitions( -std=c++11 )

endif() #CPP_11_STANDARD_INCLUDED
#========================================================================================


