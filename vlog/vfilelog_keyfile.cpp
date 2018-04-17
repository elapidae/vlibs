#include "vfilelog_keyfile.h"

#include <assert.h>

//=======================================================================================
static constexpr auto n_common_need  = "need_common_log";
static constexpr auto n_common_fname = "common_log_filename";
static constexpr auto n_common_sizes = "common_log_filesize";
static constexpr auto n_common_files = "common_log_rotate_count";

static constexpr auto n_group_need  = "need_group_log";
static constexpr auto n_group_path = "group_log_path";
static constexpr auto n_group_sizes = "group_log_filesizes";
static constexpr auto n_group_files = "group_log_rotate_count";
//=======================================================================================


//=======================================================================================
vlog::VGroupFileLog_SharedPtr
vlog::VFilelog_KeyFile::read_grouplog( const NKeyFile &kf,
                                       const std::string &group )
{
    auto need = kf.get_bool( group, n_group_need );
    if ( !need ) return {};

    auto path  = kf.get_string ( group, n_group_path );
    auto sizes = kf.get_int    ( group, n_group_sizes );
    auto files = kf.get_int    ( group, n_group_files );

    return std::make_shared<VGroupFileLog>( path, sizes, files );
}
//=======================================================================================
vlog::VCommonFileLog_SharedPtr
vlog::VFilelog_KeyFile::read_commonlog( const NKeyFile &kf,
                                        const std::string &group )
{
    auto need = kf.get_bool( group, n_common_need );
    if ( !need ) return {};

    auto path  = kf.get_string ( group, n_common_fname );
    auto sizes = kf.get_int    ( group, n_common_sizes );
    auto files = kf.get_int    ( group, n_common_files );

    return std::make_shared<VCommonFileLog>( path, sizes, files );
}
//=======================================================================================
vlog::VGroupFileLog_Threaded_SharedPtr
vlog::VFilelog_KeyFile::read_grouplog_threaded( const NKeyFile &kf,
                                                const std::string &group )
{
    auto need = kf.get_bool( group, n_group_need );
    if ( !need ) return {};

    auto path  = kf.get_string ( group, n_group_path );
    auto sizes = kf.get_int    ( group, n_group_sizes );
    auto files = kf.get_int    ( group, n_group_files );

    return std::make_shared<VGroupFileLog_Threaded>( path, sizes, files );
}
//=======================================================================================
vlog::VCommonFileLog_Threaded_SharedPtr
vlog::VFilelog_KeyFile::read_commonlog_threaded( const NKeyFile &kf,
                                                 const std::string &group )
{
    auto need = kf.get_bool( group, n_common_need );
    if ( !need ) return {};

    auto path  = kf.get_string ( group, n_common_fname );
    auto sizes = kf.get_int    ( group, n_common_sizes );
    auto files = kf.get_int    ( group, n_common_files );

    return std::make_shared<VCommonFileLog_Threaded>( path, sizes, files );
}
//=======================================================================================

//=======================================================================================
void vlog::VFilelog_KeyFile::write_grouplog_params( NKeyFile *dst,
                                                    const std::string &group,
                                                    bool need,
                                                    const std::string &path,
                                                    int fsize,
                                                    int fcount )
{
    dst->set_bool   ( group, n_group_need,  need    );
    dst->set_string ( group, n_group_path,  path    );
    dst->set_int    ( group, n_group_sizes, fsize   );
    dst->set_int    ( group, n_group_files, fcount  );
}
//=======================================================================================
void vlog::VFilelog_KeyFile::write_commonlog_params( NKeyFile *dst,
                                                     const std::string &group,
                                                     bool need,
                                                     const std::string &fname,
                                                     int fsize,
                                                     int fcount )
{
    dst->set_bool   ( group, n_common_need,  need   );
    dst->set_string ( group, n_common_fname, fname  );
    dst->set_int    ( group, n_common_sizes, fsize  );
    dst->set_int    ( group, n_common_files, fcount );
}
//=======================================================================================
