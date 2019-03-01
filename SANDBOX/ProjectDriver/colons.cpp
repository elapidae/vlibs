#include "colons.h"

#include <QString>
#include <QStringList>
#include <iostream>

static auto cols = R"delimiter(
                   [sourceanalizer.cpp:157]	>> TRC: usleep(Microsec::fromSec(Constants::Settings::Timing::SrvChannel::T_CHANNEL_STATISTICS_RECALCULATION_SEC));
                   [sourceanalizer.cpp:157]	>> TRC: if (primary_channel_min < Constants::Settings::Timing::SrvChannel::T_CHANNEL_SWITCH_NO_ANSWER_SEC) {
                   [sourceanalizer.cpp:157]	>> TRC: else if (secondary_channel_min < Constants::Settings::Timing::SrvChannel::T_CHANNEL_SWITCH_NO_ANSWER_SEC) {
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::FileLoad::FILE_LOAD_IN_PROGRESS);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::FileLoad::FILE_LOAD_STOPPING);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, "FileLoader::startScheduleSpeedProfileFile: File found loaded", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, "FileLoader::startScheduleSpeedProfileFile: Starting loading file from ftp server", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::FileLoad::ERROR_CREATING_THREAD, ret_code);
                   [sourceanalizer.cpp:157]	>> TRC: //ss << "FileLoader::onTimer, file_load_thread_arg.status" << StringEnum<FtpStatus::LoadState>::toFullString(file_load_result.state) << std::endl;
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, "FileLoader::fileLoadThreadFunction - start", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, "FileLoader::fileLoadThreadFunction - connection successfully opened", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::FileLoad::THREAD_STOPPING, StringEnum<FileLoadThreadStopCode>::toFullString(code).c_str());
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::FileLoad::FILE_LOAD_CHECK_LOCAL, check_file_status);
                   [sourceanalizer.cpp:157]	>> TRC: const char* LogSrvMessages::DataUnitHandling::InvalidData::SpeedRestriction::INVALID_TIMESTAMPS = "SPEED_RESTRICTION: Invalid start/end timestamp: %d (%s UTC), %d (%s UTC)";
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, ILogger::LEVEL::LEVEL_ERROR, LogKernelMessages::Errors::INITIALIZATION_KLUB_OPEN);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, ILogger::LEVEL::LEVEL_ERROR, LogKernelMessages::Errors::INITIALIZATION_KLUB_INIT);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_WARN, LogKernelMessages::AutopilotLoad::LOAD_FAILURE, version, timestamp_file);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::AutopilotLoad::LOAD_SUCCESS, version, file_timestamp);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::AutopilotLoad::LOAD_STARTING, file.timestamp_msg, file_full_name.c_str(), file.version);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::FileLoad::FILE_FOUND_LOCAL_LOADED, file.file_data.file_timestamp, local_file.c_str());
                   [sourceanalizer.cpp:157]	>> TRC: //	logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::FileLoad::FILE_LOAD_STARTING, file.file_data.file_timestamp, remote_filename.c_str());
                   [sourceanalizer.cpp:157]	>> TRC: //		logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::FileLoad::FILE_LOAD_STARTING, file.file_data.file_timestamp, remote_filename.c_str());
                   [sourceanalizer.cpp:157]	>> TRC: std::bind(&Kernel::onFileLoadFound, this, std::placeholders::_1));
                   [sourceanalizer.cpp:157]	>> TRC: std::bind(&Kernel::onFileLoadSuccess, this, std::placeholders::_1, std::placeholders::_2));
                   [sourceanalizer.cpp:157]	>> TRC: std::bind(&Kernel::onFileLoadFailure, this, std::placeholders::_1, std::placeholders::_2));
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::ChannelModule::ACTIVE_CHANNEL_CHANGED, StringEnum<ProcessorModuleCode>::toString(active_channel).c_str());
                   [sourceanalizer.cpp:157]	>> TRC: //std::bind(&Kernel::onFileLoadCommandReceived, this, std::placeholders::_1, std::placeholders::_2));
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::Schedule::SCHEDULE_RECEIVED,
                   [sourceanalizer.cpp:157]	>> TRC: std::bind(&ScheduleController::onFileLoadFailure, &controllers.schedule, std::placeholders::_1, std::placeholders::_2));
                   [sourceanalizer.cpp:157]	>> TRC: std::bind(&ScheduleController::onFileLoadSuccess, &controllers.schedule, std::placeholders::_1, std::placeholders::_2));
                   [sourceanalizer.cpp:157]	>> TRC: std::bind(&ScheduleController::onFileLoadSuccess, &controllers.schedule, std::placeholders::_1, std::placeholders::_2));
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::Session::SRV_REGISTRATION_ATTEMPT,
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::Session::SRV_REGISTRATION_FAILURE_CONNECT);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::Session::SRV_REGISTRATION_SUCCESS);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::Session::SRV_UNREGISTRATION, StringEnum<SessionStateReason>::toFullString(reason).c_str());
                   [sourceanalizer.cpp:157]	>> TRC: // 			logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::TrainParameters::TRAIN_PARAMETER_UPDATED,
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::TrainParameters::TRAIN_PARAMETERS_INITIALIZING );
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_ERROR, LogKernelMessages::TrainParameters::TRAIN_PARAMETERS_INIT_FAILURE, StringEnum<SysDataCode>::toFullString(code).c_str() );
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_ERROR, LogKernelMessages::TrainParameters::KLUB_MODULE_VERSION_INIT_FAILURE, StringEnum<KlubModuleCode>::toFullString(module_code).c_str());
                   [sourceanalizer.cpp:157]	>> TRC: usleep(Microsec::fromMillisec(Constants::Settings::Timing::T_MAIN_CYCLE_MSEC));
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::TrainParameters::TRAIN_PARAMETERS_INITIALIZED,
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::TrainParameters::TRAIN_PARAMETERS_INITIALIZED,
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_ERROR, LogKernelMessages::TrainParameters::DATE_TIME_INIT_FAILURE);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::TrainParameters::DATE_TIME_INITIALIZED,
                   [sourceanalizer.cpp:157]	>> TRC: //				logger->log(ILogger::LEVEL::LEVEL_ERROR, LogKlubMessages::Channel::ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: if (srv_processor->getSession().getState() == SrvSessionState::SessionState::CONNECTED_REGISTERING || srv_processor->getSession().getState() == SrvSessionState::SessionState::REGISTERED) {
                   [sourceanalizer.cpp:157]	>> TRC: usleep(Microsec::fromMillisec(Constants::Settings::Timing::T_MAIN_CYCLE_MSEC - cyrcle_time));
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logging_manager->getKernelLogger(), ILogger::LEVEL::LEVEL_INFO, "AP file status changed to AutopilotFileStateCode::WAIT_AP_FILE_ELAPSED: Constants::Settings::Timing::T_WAIT_AP_FILE_SEC timer elapsed");
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_WARN, LogSrvMessages::Channel::ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_WARN, LogKernelMessages::FileLoad::FILE_LOAD_FAILURE, file_load_result.toString().c_str(), file_load_result.ncftp_code);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::FileLoad::FILE_LOAD_SUCCESS, file.file_data.file_timestamp);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::FileLoad::FILE_LOAD_FOUND, file.file_data.file_timestamp);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_ERROR, LogSrvMessages::Channel::ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_ERROR, LogSrvMessages::Channel::MEMORY_MANAGEMENT_ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_ERROR, LogKernelMessages::FileLoad::DIR_NOT_FOUND, app_settings.load_files_dir.c_str());
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_ERROR, LogKernelMessages::AutopilotLoad::STUB_STATUS_FILE_NOT_FOUND,
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_ERROR, LogKernelMessages::Errors::POSITION_LOGGING_CAN_NOT_OPEN_FILE,
                   [sourceanalizer.cpp:157]	>> TRC: //	logger->log(ILogger::LEVEL::LEVEL_ERROR, LogKernelMessages::Settings::CHANNEL_CONTROL_STUB_STATUS_FILE_NOT_FOUND,
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::AutopilotLoad::SETTINGS_STUB_STATUS_FILE,
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::AutopilotLoad::SETTINGS,
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::Settings::CHANNEL_CONTROL_STUB_STATUS_FILE,
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, ss.str(), (result == RESULT::SUCCESS ? ILogger::LEVEL::LEVEL_DEBUG : ILogger::LEVEL::LEVEL_ERROR));
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, LogKernelMessages::Errors::CHC_CHANNEL_ERROR, ILogger::LEVEL::LEVEL_ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::AutopilotLoad::ERROR_CREATING_THREAD, ret_code);
                   [sourceanalizer.cpp:157]	>> TRC: && std::abs(static_cast<int32_t>(application_timer->getTimestamp() - file_state.load_start_timestamp)) > static_cast<int32_t>(Constants::Settings::Autopilot::STATE_TO_LOADING_AFTER_LOAD_STARTED_SEC)
                   [sourceanalizer.cpp:157]	>> TRC: is_attempt_start_ok ? LogKernelMessages::AutopilotLoad::LOAD_ATTEMPT : LogKernelMessages::AutopilotLoad::LOAD_ATTEMPT_START_FAILED,
                   [sourceanalizer.cpp:157]	>> TRC: //	logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::AutopilotLoad::THREAD_STOPPING);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::FileLoad::FILE_LOAD_CHECK_LOCAL, check_file_status);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::Schedule::HANDLED_SCHEDULE_RECEIVED, schedule.file.file_timestamp);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::Schedule::HANDLING_SCHEDULE_RECEIVED, schedule.file.file_timestamp);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::Schedule::WAITING_SCHEDULE_RECEIVED, schedule.file.file_timestamp);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::Schedule::SCHEDULE_PUT_TO_QUEUE, schedule.file.file_timestamp);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::Schedule::SCHEDULE_GET_FROM_QUEUE,
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::Schedule::SpeedProfileProcessing::SCHEDULE_APPROVED, status.processing_schedule.timestamp_msg, speed_profile.speed_profile_id);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::Schedule::SpeedProfileProcessing::SCHEDULE_PAGE_APPROVED,
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::Schedule::SpeedProfileProcessing::DRIVER_CANCELLED_ALL_RESTRICTIONS);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::Schedule::SpeedProfileProcessing::SCHEDULE_REJECTED,
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, "ScheduleController::onFileLoadFailure: calling cancelProcessingSpeedProfile", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, "ScheduleController::onAutopilotLoadFailure: calling cancelProcessingSpeedProfile", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: //		logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::Schedule::SpeedProfileProcessing::SCHEDULE_CANCELLED, speed_profile_processing.speed_profile_id);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::Schedule::SpeedProfileProcessing::SCHEDULE_SENT_TO_DRIVER,
                   [sourceanalizer.cpp:157]	>> TRC: //		logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::Schedule::SpeedProfileProcessing::SCHEDULE_CANCELLED,
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, "SpeedRestrictionController::onSpeedProfileChecksumError: calling cancelProcessingSpeedProfile", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::Schedule::SpeedProfileProcessing::SCHEDULE_APPROVE_TIMER_EXPIRED,
                   [sourceanalizer.cpp:157]	>> TRC: //	logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::Schedule::SpeedProfileProcessing::SCHEDULE_CANCELLED, speed_profile.speed_profile_id);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::Synchronization::SYNCHRONIZATION_CHECK, synchro_cyrcle_number, cyrcle_number_received,
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logging_manager->getKernelLogger(), ILogger::LEVEL::LEVEL_WARN, LogKernelMessages::Synchronization::MODULES_NOT_SYNCHRONIZED_CLIENT,
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logging_manager->getKernelLogger(), ILogger::LEVEL::LEVEL_WARN, LogKernelMessages::Synchronization::MODULES_NOT_SYNCHRONIZED_SERVER,
                   [sourceanalizer.cpp:157]	>> TRC: (kill_result != -1 ? ILogger::LEVEL::LEVEL_DEBUG : ILogger::LEVEL::LEVEL_ERROR),
                   [sourceanalizer.cpp:157]	>> TRC: usleep(asuspn_obu::Microsec::fromMillisec(asuspn_obu::Constants::Settings::Timing::T_MAIN_CYCLE_MSEC));
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logging_manager->getKlubLogger(), ILogger::LEVEL::LEVEL_WARN, LogKernelMessages::Warnings::NO_KLUB_MSG_RECEIVED, can_cyrcle_number);
                   [sourceanalizer.cpp:157]	>> TRC: usleep(asuspn_obu::Microsec::fromMillisec(asuspn_obu::Constants::Settings::Timing::T_MAIN_CYCLE_MSEC));
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, LogKernelSyncronizatorMessages::Errors::NO_SYNCHRO_FROM_SERVER, ILogger::LEVEL::LEVEL_WARN);
                   [sourceanalizer.cpp:157]	>> TRC: usleep(Microsec::fromMillisec(Constants::Settings::Timing::T_MAIN_CYCLE_MSEC - static_cast<uint32_t>(circle_len_msec)));
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, ILogger::LEVEL::LEVEL_WARN, LogKernelSyncronizatorMessages::Warning::TOO_LONG_MAIN_CYRCLE, static_cast<uint32_t>(circle_len_msec));
                   [sourceanalizer.cpp:157]	>> TRC: Constants::Settings::Timing::Can::NO_MESSAGE_FAILURE_PERIOD_MSEC) &&
                   [sourceanalizer.cpp:157]	>> TRC: (now - can_exchange.can_initialization_timestamp >= Constants::Settings::Timing::Can::REINITIALIZATION_PERIOD_SEC)) {
                   [sourceanalizer.cpp:157]	>> TRC: //	if (static_cast<RetcodeFileLoad>(static_cast<std::uint8_t>(retcode)& static_cast<std::uint8_t>(RetcodeFileLoad::LOAD_LOADING_STARTED)) != RetcodeFileLoad::NONE) {
                   [sourceanalizer.cpp:157]	>> TRC: //	if (static_cast<RetcodeFileLoad>(static_cast<std::uint8_t>(retcode)& static_cast<std::uint8_t>(RetcodeFileLoad::LOAD_FAILURE_CHECKSUM)) != RetcodeFileLoad::NONE) {
                   [sourceanalizer.cpp:157]	>> TRC: //	else if (static_cast<RetcodeFileLoad>(static_cast<std::uint8_t>(retcode)& static_cast<std::uint8_t>(RetcodeFileLoad::LOAD_FAILURE_FILE_NOT_FOUND)) != RetcodeFileLoad::NONE) {
                   [sourceanalizer.cpp:157]	>> TRC: //	else if (static_cast<RetcodeFileLoad>(static_cast<std::uint8_t>(retcode)& static_cast<std::uint8_t>(RetcodeFileLoad::LOAD_FAILURE_UNKNOWN_ERROR)) != RetcodeFileLoad::NONE) {
                   [sourceanalizer.cpp:157]	>> TRC: //	else if (static_cast<RetcodeFileLoad>(static_cast<std::uint8_t>(retcode)& static_cast<std::uint8_t>(RetcodeFileLoad::LOAD_SUCCESS)) != RetcodeFileLoad::NONE) {
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, "SynchronizatorFileClient::start - waiting for data... ", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, "SynchronizatorFileClient::start - getting chc msg... ", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: //usleep(Microsec::fromMillisec(Constants::Settings::Timing::T_FILE_SYNC_DATA_SLEEP_MSEC));
                   [sourceanalizer.cpp:157]	>> TRC: std::ofstream filestream(filename, std::ios::out | std::ios::binary);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, "SynchronizatorFileClient::start, waitForData returned 0", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, "File load failure: timer FileLoadResultCode::FILELOADRESULT_FAILURE_TOO_LONG", ILogger::LEVEL::LEVEL_ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: std::ifstream filestream(filename, std::ios::in | std::ios::binary);
                   [sourceanalizer.cpp:157]	>> TRC: logging_manager->getKernelLogger()->log(ILogger::LEVEL::LEVEL_INFO, LogKernelMessages::FileLoad::FTP_FILE_LOAD_STARTING,
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logging_manager->getKernelLogger(), LogKernelMessages::Synchronization::RESTART_TIME_UPDATED, ILogger::LEVEL::LEVEL_ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, LogKernelSyncronizatorMessages::Warning::INVALID_SYNCHRO_ACK_FROM_CLIENT, ILogger::LEVEL::LEVEL_WARN);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, ILogger::LEVEL::LEVEL_WARN, LogKernelMessages::UpdateTimeByKlub::REQUIRED,
                   [sourceanalizer.cpp:157]	>> TRC: (set_time_result == UpdateSystemTimeResult::Success ? ILogger::LEVEL::LEVEL_INFO : ILogger::LEVEL::LEVEL_WARN),
                   [sourceanalizer.cpp:157]	>> TRC: if (!asuspn_obu::AppData::isDualMode() || asuspn_obu::AppData::getSettings().mode == asuspn_obu::ProcessorModuleCode::SECONDARY) {
                   [sourceanalizer.cpp:157]	>> TRC: //					if (asuspn_obu::AppData::getSettings().srv_mode == asuspn_obu::SrvModeCode::PRIMARY) {
                   [sourceanalizer.cpp:157]	>> TRC: if (asuspn_obu::AppData::isDualMode() && asuspn_obu::AppData::getSettings().mode == asuspn_obu::ProcessorModuleCode::SECONDARY) {
                   [sourceanalizer.cpp:157]	>> TRC: usleep(Microsec::fromMillisec(Constants::Settings::Timing::T_MAIN_CYCLE_MSEC));
                   [sourceanalizer.cpp:157]	>> TRC: settings.app_settings.mode = instance_number == 1 ? asuspn_obu::ProcessorModuleCode::PRIMARY : asuspn_obu::ProcessorModuleCode::SECONDARY;
                   [sourceanalizer.cpp:157]	>> TRC: asuspn_obu::SocketProtocol::TCP : asuspn_obu::SocketProtocol::UDP;
                   [sourceanalizer.cpp:157]	>> TRC: asuspn_obu::ILogger::tryLog(s_logging_manager->getKernelLogger(), asuspn_obu::ILogger::LEVEL::LEVEL_DEBUG, "asuspn: segmentation fault occured");
                   [sourceanalizer.cpp:157]	>> TRC: asuspn_obu::ILogger::tryLog(s_logging_manager->getKernelLogger(), asuspn_obu::ILogger::LEVEL::LEVEL_DEBUG, ss.str().c_str());
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::AutopilotLoad::STATE,
                   [sourceanalizer.cpp:157]	>> TRC: asuspn_obu::ILogger::tryLog(s_logging_manager->getChannelModuleLogger(), asuspn_obu::ILogger::LEVEL::LEVEL_DEBUG, "asuspn: segmentation fault occured");
                   [sourceanalizer.cpp:157]	>> TRC: asuspn_obu::ILogger::tryLog(s_logging_manager->getChannelModuleLogger(), asuspn_obu::ILogger::LEVEL::LEVEL_DEBUG, ss.str().c_str());
                   [sourceanalizer.cpp:157]	>> TRC: std::string filename = apps::channel_module::ChmApplication::getConfigFilename(argc, argv, module_code);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, "KlubProcessor::handleInputData", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log (ILogger::LEVEL::LEVEL_INFO, LogKlubMessages::Settings::FILTERING, input_str.c_str(), output_str.c_str());
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_ERROR, LogKlubMessages::Channel::ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_ERROR, LogKlubMessages::Channel::ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: return Millisec::fromSec(statistics.channel_1.sec_since_last_receive) <= Constants::Settings::Timing::T_CONNECTION_ALIVE_DEFAULT_MSEC;
                   [sourceanalizer.cpp:157]	>> TRC: return Millisec::fromSec(statistics.channel_2.sec_since_last_receive) <= Constants::Settings::Timing::T_CONNECTION_ALIVE_DEFAULT_MSEC;
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_ERROR, LogSrvMessages::Channel::MEMORY_MANAGEMENT_ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogSrvMessages::DataUnitHandling::InvalidData::SpeedRestriction::INVALID_TIMESTAMPS,
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogSrvMessages::DataUnitHandling::MSG_INFO_NOT_HANDLED, msg->getId(), msg->getName().c_str(), msg_info->getTime(), msg_info->getCounter(), reason);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogSrvMessages::DataUnitHandling::MSG_CHANNEL_STATE_NOT_HANDLED, msg->getId(), msg->getName().c_str(), msg_channel->getCounter(), reason);
                   [sourceanalizer.cpp:157]	>> TRC: } else if (getState() == SrvSessionState::SessionState::CONNECTED_REGISTERING || getState() == SrvSessionState::SessionState::REGISTERED) {
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, ILogger::LEVEL::LEVEL_WARN, LogSrvMessages::DataUnitHandling::MSG_INFO_UNEXPECTED_COUNTER,
                   [sourceanalizer.cpp:157]	>> TRC: if ((getState() == SrvSessionState::SessionState::CONNECTED_REGISTERING || getState() == SrvSessionState::SessionState::REGISTERED)) {
                   [sourceanalizer.cpp:157]	>> TRC: IMPLEMENT_ENUM_NAMES (SrvSessionState::SessionState, (std::map <SrvSessionState::SessionState, std::string>({
                   [sourceanalizer.cpp:157]	>> TRC: if (now - it->send_timestamp >= static_cast<time_t>(Constants::Settings::Timing::SrvChannel::T_STATISTICS_TIMEOUT_SEC)) {
                   [sourceanalizer.cpp:157]	>> TRC: if (sec_since_last_receive >= 0 && sec_since_last_receive < Constants::Settings::Timing::SrvChannel::T_STATISTICS_TIMEOUT_SEC) {
                   [sourceanalizer.cpp:157]	>> TRC: usleep(Microsec::fromSec(Constants::Settings::Timing::SrvChannel::T_CHANNEL_STATE_TIMEOUT_SEC));
                   [sourceanalizer.cpp:157]	>> TRC: (std::abs(now - state.obj.last_receive_timestamp) < Constants::Settings::Timing::SrvChannel::T_CHANNEL_SWITCH_NO_ANSWER_SEC)
                   [sourceanalizer.cpp:157]	>> TRC: //			logger->log(LogSrvMessages::Channel::ERROR, ILogger::LEVEL::LEVEL_ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: //			logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogSrvMessages::MemoryManagement::INVALID_BUFFER_LENGTH);
                   [sourceanalizer.cpp:157]	>> TRC: //		logger->log(LogSrvMessages::Channel::ERROR, ILogger::LEVEL::LEVEL_ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(LogSrvMessages::Channel::ERROR, ILogger::LEVEL::LEVEL_ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, ILogger::LEVEL::LEVEL_DEBUG, LogSrvMessages::Channel::PARSING_ERROR, StringEnum<ParseResultCode>::toString(result.code).c_str());
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(LogSrvMessages::Channel::ERROR, ILogger::LEVEL::LEVEL_ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: if (min_delay >= Constants::Settings::Timing::SrvChannel::T_STATISTICS_TIMEOUT_SEC) {
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, "ModemStub::connect()", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, "ModemStub::dicconnect()", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, "ModemStub::getStatus()", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: && schedule_timers.registration_timer.getMillisecSinceStart() >= Millisec::fromSec(Constants::Settings::Timing::T_WAIT_SCHEDULE_AFTER_REGISTRATION_SEC))
                   [sourceanalizer.cpp:157]	>> TRC: && schedule_timers.first_schedule_timer.getMillisecSinceStart() >= Millisec::fromSec(Constants::Settings::Timing::T_WAIT_AUTOPILOT_SUCCESS_AFTER_SCHEDULE_RECEIVED_SEC));
                   [sourceanalizer.cpp:157]	>> TRC: pages_to_approve = static_cast<std::uint8_t>(std::ceil(static_cast<double>(profile.speed_restrictions.size()) / Constants::Settings::Klub::SPEED_RESTRICTIONS_PAGE_COUNT));
                   [sourceanalizer.cpp:157]	>> TRC: return asuspn_obu::AppData::getSettings().mode == asuspn_obu::ProcessorModuleCode::PRIMARY ?
                   [sourceanalizer.cpp:157]	>> TRC: asuspn_obu::SocketMessageChannel<asuspn_obu::Constants::Settings::Klub::CAN_BUFFER> socket_channel;
                   [sourceanalizer.cpp:157]	>> TRC: asuspn_obu::CanMessageChannel<asuspn_obu::Constants::Settings::Klub::CAN_BUFFER> can_channel;
                   [sourceanalizer.cpp:157]	>> TRC: managed_processor(asuspn_obu::AppData::getSettings().mode == asuspn_obu::ProcessorModuleCode::PRIMARY ?
                   [sourceanalizer.cpp:157]	>> TRC: asuspn_obu::IMessageChannel<asuspn_obu::Constants::Settings::Klub::CAN_BUFFER>* getChannel () {
                   [sourceanalizer.cpp:157]	>> TRC: static_cast <asuspn_obu::IMessageChannel<asuspn_obu::Constants::Settings::Klub::CAN_BUFFER>* > (&can_channel) :
                   [sourceanalizer.cpp:157]	>> TRC: static_cast <asuspn_obu::IMessageChannel<asuspn_obu::Constants::Settings::Klub::CAN_BUFFER>* > (&socket_channel);
                   [sourceanalizer.cpp:157]	>> TRC: channel(asuspn_obu::AppData::getSettings().mode == asuspn_obu::ProcessorModuleCode::SECONDARY ?
                   [sourceanalizer.cpp:157]	>> TRC: return asuspn_obu::AppData::getSettings().mode == asuspn_obu::ProcessorModuleCode::SECONDARY ?
                   [sourceanalizer.cpp:157]	>> TRC: managed_processor(asuspn_obu::AppData::getSettings().mode == asuspn_obu::ProcessorModuleCode::PRIMARY ?
                   [sourceanalizer.cpp:157]	>> TRC: std::uint16_t sec_since_last_receive = Constants::Codes::Srv::CHANNEL_INFINITE_DELAY;
                   [sourceanalizer.cpp:157]	>> TRC: std::string logger_section, std::string default_filename, asuspn_obu::ILogger::LEVEL default_level);
                   [sourceanalizer.cpp:157]	>> TRC: #define IMPLEMENT_ENUM_NAMES(type,names_map) const std::map <type, std::string> EnumNames<type>::names = std::map<type, std::string>(names_map);
                   [sourceanalizer.cpp:157]	>> TRC: static std::ostream& toStream(const char* name, std::string data, std::ostream &stream, std::string after = "") {
                   [sourceanalizer.cpp:157]	>> TRC: MessageFilter (std::initializer_list<std::uint16_t> _input_msg_enabled, std::initializer_list<std::uint16_t> _output_msg_enabled);
                   [sourceanalizer.cpp:157]	>> TRC: void getFilters (std::set<std::uint16_t>& input, std::set<std::uint16_t>& output) const;
                   [sourceanalizer.cpp:157]	>> TRC: //ILogger::tryLog(logger, "SocketClient::close()", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: //ILogger::tryLog(logger, "socket_client::close shutting down...", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: //endpoint(boost::asio::ip::address::from_string(settings.ip), settings.port),
                   [sourceanalizer.cpp:157]	>> TRC: // sock.open(boost::asio::ip::udp::v4());
                   [sourceanalizer.cpp:157]	>> TRC: //boost::asio::ip::udp::endpoint remote_ep;
                   [sourceanalizer.cpp:157]	>> TRC: end_point(boost::asio::ip::address::from_string(settings.ip), settings.port),
                   [sourceanalizer.cpp:157]	>> TRC: boost::asio::ip::tcp::endpoint end_point;
                   [sourceanalizer.cpp:157]	>> TRC: boost::asio::ip::tcp::socket sock;
                   [sourceanalizer.cpp:157]	>> TRC: boost::asio::ip::tcp::acceptor acceptor;
                   [sourceanalizer.cpp:157]	>> TRC: boost::asio::ip::basic_endpoint<boost::asio::ip::udp> endpoint;
                   [sourceanalizer.cpp:157]	>> TRC: //boost::asio::ip::udp::endpoint endpoint;
                   [sourceanalizer.cpp:157]	>> TRC: boost::asio::ip::udp::endpoint remote_endpoint;
                   [sourceanalizer.cpp:157]	>> TRC: boost::asio::ip::udp::socket sock;
                   [sourceanalizer.cpp:157]	>> TRC: ret.free_count = std::count_if(std::begin(units), std::end(units), [](std::pair<TDataUnit, bool> unit) {
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::MemoryManagement::STORAGE_ERROR,
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::MemoryManagement::STORAGE_CREATE_RESULT,
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::MemoryManagement::STORAGE_RELEASE_RESULT,
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, "Parser::parse() - error parsing msg: not created", ILogger::LEVEL::LEVEL_ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: static std::string replaceAll(std::string src, std::string old_str, std::string new_str);
                   [sourceanalizer.cpp:157]	>> TRC: ip::udp::endpoint ep( ip::address::from_string("192.168.0.203"), 9998);
                   [sourceanalizer.cpp:157]	>> TRC: ip::udp::socket sock(service, ip::udp::endpoint(ip::udp::v4(), 0) );
                   [sourceanalizer.cpp:157]	>> TRC: std::this_thread::sleep_for(std::chrono::seconds(10));
                   [sourceanalizer.cpp:157]	>> TRC: std::bind(&FileLoadControllerTest::onLoadSuccess, this, std::placeholders::_1, std::placeholders::_2));
                   [sourceanalizer.cpp:157]	>> TRC: std::bind(&FileLoadControllerTest::onLoadStarted, this, std::placeholders::_1));
                   [sourceanalizer.cpp:157]	>> TRC: std::bind(&FileLoadControllerTest::onLoadFailureInvalidCrc, this, std::placeholders::_1, std::placeholders::_2));
                   [sourceanalizer.cpp:157]	>> TRC: std::bind(&FileLoadControllerTest::onLoadFailureInvalidTimestamp, this, std::placeholders::_1));
                   [sourceanalizer.cpp:157]	>> TRC: std::bind(&FileLoadControllerTest::onLoadFailure, this, std::placeholders::_1));
                   [sourceanalizer.cpp:157]	>> TRC: std::placeholders::_1, std::placeholders::_2));
                   [sourceanalizer.cpp:157]	>> TRC: std::placeholders::_1, std::placeholders::_2));
                   [sourceanalizer.cpp:157]	>> TRC: onInvalidSpeedProfileFileId(::testing::_, ::testing::_));
                   [sourceanalizer.cpp:157]	>> TRC: std::string res = StringHelper::replaceAll(std::string("{0} string to {0} class methods {0}"), std::string("{0}"), std::string("test"));
                   [sourceanalizer.cpp:157]	>> TRC: //std::string res = StringHelper::replaceAll(std::string("{0} string to {0} class methods {0}"), std::string("{0}"), std::string("test"));
                   [sourceanalizer.cpp:157]	>> TRC: msg = asuspn_obu::KlubFactory::createMsgFromId(asuspn_obu::KlubMsg::ITR_TARGET_EK);
                   [sourceanalizer.cpp:157]	>> TRC: asuspn_obu::KlubMsg msg = asuspn_obu::KlubFactory::createMsgFromId(asuspn_obu::KlubMsg::MM_COORD);
                   [sourceanalizer.cpp:157]	>> TRC: filestream.open(filename, std::ios_base::in | std::ios_base::binary);
                   [sourceanalizer.cpp:157]	>> TRC: coord_file.open(settings.coord_file_path, std::ios_base::out | std::ios_base::trunc);
                   [sourceanalizer.cpp:157]	>> TRC: asuspn_obu::tool_parser::MsgType msg_type = asuspn_obu::tool_parser::MsgType::Srv;
                   [sourceanalizer.cpp:157]	>> TRC: p_log_->add_log("", utils::log::FMT_ALL, utils::log::LVL_ALL);
                   [sourceanalizer.cpp:157]	>> TRC: utils::log::CLog log_; utils::log::CLog *p_log_ = &log_;
                   [sourceanalizer.cpp:157]	>> TRC: p_log_->add_log("", utils::log::FMT_ALL, utils::log::LVL_ALL);
                   [sourceanalizer.cpp:157]	>> TRC: utils::log::CLogObu log_; utils::log::CLogObu *p_log_ = &log_;
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(autopilot_logger, "PrimaryAutopilotProcessor::init starting...", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(autopilot_logger, "PrimaryAutopilotProcessor::init - unhandled exception", ILogger::LEVEL::LEVEL_ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(autopilot_logger, "PrimaryAutopilotProcessor::init ended", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(autopilot_logger, "PrimaryAutopilotProcessor::sendFile calling autopilot module sendFile...", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(autopilot_logger, "PrimaryAutopilotProcessor::sendFile - unhandled exception", ILogger::LEVEL::LEVEL_ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(autopilot_logger, "PrimaryAutopilotProcessor::getState - unhandled exception", ILogger::LEVEL::LEVEL_ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: logger->log(ILogger::LEVEL::LEVEL_DEBUG, LogKernelMessages::AutopilotLoad::STATE,
                   [sourceanalizer.cpp:157]	>> TRC: std::string logger_section, std::string default_filename, asuspn_obu::ILogger::LEVEL default_level) {
                   [sourceanalizer.cpp:157]	>> TRC: std::string FileSystem::makeFileName (std::string directory, std::string filename) {
                   [sourceanalizer.cpp:157]	>> TRC: bool Utils::replaceString(std::string& str, const std::string& from, const std::string& to) {
                   [sourceanalizer.cpp:157]	>> TRC: MessageFilter::MessageFilter (std::initializer_list<std::uint16_t> _input_msg_enabled, std::initializer_list<std::uint16_t> _output_msg_enabled) :
                   [sourceanalizer.cpp:157]	>> TRC: void MessageFilter::getFilters (std::set<std::uint16_t>& input, std::set<std::uint16_t>& output) const {
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(logger, "CanInitializer::init() error", ILogger::LEVEL::LEVEL_ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: //ILogger::tryLog(logger, "TcpSocketClient::doSend(): waitForData calling...", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: //ILogger::tryLog(logger, "TcpSocketClient::doSend(): waitForData returned", ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: sock.open(boost::asio::ip::tcp::v4());
                   [sourceanalizer.cpp:157]	>> TRC: sock.set_option(boost::asio::ip::tcp::socket::reuse_address(true));
                   [sourceanalizer.cpp:157]	>> TRC: //endpoint(boost::asio::ip::address::from_string(settings.ip), settings.port),
                   [sourceanalizer.cpp:157]	>> TRC: endpoint(boost::asio::ip::udp::v4(), settings.port),
                   [sourceanalizer.cpp:157]	>> TRC: sock.open(boost::asio::ip::udp::v4());
                   [sourceanalizer.cpp:157]	>> TRC: sock.set_option(boost::asio::ip::udp::socket::reuse_address(true));
                   [sourceanalizer.cpp:157]	>> TRC: //boost::asio::ip::udp::endpoint remote_ep;
                   [sourceanalizer.cpp:157]	>> TRC: sock.async_receive_from(boost::asio::buffer(inner_buffer, BUFFER_LENGTH), remote_endpoint, [this/*, remote_ep*/](boost::system::error_code ec, std::size_t len) {
                   [sourceanalizer.cpp:157]	>> TRC: stream.open(filename, std::ios_base::out | std::ios_base::trunc);
                   [sourceanalizer.cpp:157]	>> TRC: const std::map <LoggerLevel, std::string> EnumNames<LoggerLevel>::names = std::map<LoggerLevel, std::string>({
                   [sourceanalizer.cpp:157]	>> TRC: ILogger::tryLog(&logger_pair.file, ILogger::LEVEL::LEVEL_OFF, "%s (%s)", logger_settings.file.c_str(), StringEnum<ILogger::LEVEL>::toFullString(logger_settings.max_level).c_str());
                   [sourceanalizer.cpp:157]	>> TRC: std::string StringHelper::replaceAll(std::string src, std::string old_str, std::string new_str)
                   [sourceanalizer.cpp:157]	>> TRC: CLog::p_log->log_print(CLog::p_log->s_file.c_str(), CLog::p_log->line, CLog::p_log->s_fun.c_str(), LVL_NONE, "", ap_msg, va);
                   [sourceanalizer.cpp:157]	>> TRC: CLog::p_log->log_print(CLog::p_log->s_file.c_str(), CLog::p_log->line, CLog::p_log->s_fun.c_str(), a_lvl, "", ap_msg, va);
                   [sourceanalizer.cpp:157]	>> TRC: CLog::p_log->log_print(CLog::p_log->s_file.c_str(), CLog::p_log->line, CLog::p_log->s_fun.c_str(), LVL_NONE, ap_tag, ap_msg, va);
                   [sourceanalizer.cpp:157]	>> TRC: CLog::p_log->log_print(CLog::p_log->s_file.c_str(), CLog::p_log->line, CLog::p_log->s_fun.c_str(), a_lvl, ap_tag, ap_msg, va);
                   [sourceanalizer.cpp:157]	>> TRC: CLog::p_log->log_print_out(CLog::p_log->s_file.c_str(), CLog::p_log->line, CLog::p_log->s_fun.c_str(), LVL_NONE, "", ap_msg, va);
                   [sourceanalizer.cpp:157]	>> TRC: CLog::p_log->log_print_out(CLog::p_log->s_file.c_str(), CLog::p_log->line, CLog::p_log->s_fun.c_str(), a_lvl, "", ap_msg, va);
                   [sourceanalizer.cpp:157]	>> TRC: CLog::p_log->log_print_out(CLog::p_log->s_file.c_str(), CLog::p_log->line, CLog::p_log->s_fun.c_str(), LVL_NONE, ap_tag, ap_msg, va);
                   [sourceanalizer.cpp:157]	>> TRC: CLog::p_log->log_print_out(CLog::p_log->s_file.c_str(), CLog::p_log->line, CLog::p_log->s_fun.c_str(), a_lvl, ap_tag, ap_msg, va);
                   [sourceanalizer.cpp:157]	>> TRC: CLog::p_log->log_print_raw(CLog::p_log->s_file.c_str(), CLog::p_log->line, CLog::p_log->s_fun.c_str(), LVL_NONE, "", ap_msg, va);
                   [sourceanalizer.cpp:157]	>> TRC: CLog::p_log->log_print_raw(CLog::p_log->s_file.c_str(), CLog::p_log->line, CLog::p_log->s_fun.c_str(), a_lvl, "", ap_msg, va);
                   [sourceanalizer.cpp:157]	>> TRC: CLog::p_log->log_print_raw(CLog::p_log->s_file.c_str(), CLog::p_log->line, CLog::p_log->s_fun.c_str(), LVL_NONE, ap_tag, ap_msg, va);
                   [sourceanalizer.cpp:157]	>> TRC: CLog::p_log->log_print_raw(CLog::p_log->s_file.c_str(), CLog::p_log->line, CLog::p_log->s_fun.c_str(), a_lvl, ap_tag, ap_msg, va);
                   [sourceanalizer.cpp:157]	>> TRC: CLog::p_log->log_print_raw_out(CLog::p_log->s_file.c_str(), CLog::p_log->line, CLog::p_log->s_fun.c_str(), LVL_NONE, "", ap_msg, va);
                   [sourceanalizer.cpp:157]	>> TRC: CLog::p_log->log_print_raw_out(CLog::p_log->s_file.c_str(), CLog::p_log->line, CLog::p_log->s_fun.c_str(), a_lvl, "", ap_msg, va);
                   [sourceanalizer.cpp:157]	>> TRC: CLog::p_log->log_print_raw_out(CLog::p_log->s_file.c_str(), CLog::p_log->line, CLog::p_log->s_fun.c_str(), LVL_NONE, ap_tag, ap_msg, va);
                   [sourceanalizer.cpp:157]	>> TRC: CLog::p_log->log_print_raw_out(CLog::p_log->s_file.c_str(), CLog::p_log->line, CLog::p_log->s_fun.c_str(), a_lvl, ap_tag, ap_msg, va);
                   [sourceanalizer.cpp:157]	>> TRC: asuspn_obu::ILogger::tryLog(p_logger_, ac_msg, asuspn_obu::ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: asuspn_obu::ILogger::tryLog(p_logger_, ac_msg, asuspn_obu::ILogger::LEVEL::LEVEL_DEBUG);
                   [sourceanalizer.cpp:157]	>> TRC: asuspn_obu::ILogger::tryLog(p_logger_, ac_msg, asuspn_obu::ILogger::LEVEL::LEVEL_INFO);
                   [sourceanalizer.cpp:157]	>> TRC: asuspn_obu::ILogger::tryLog(p_logger_, ac_msg, asuspn_obu::ILogger::LEVEL::LEVEL_WARN);
                   [sourceanalizer.cpp:157]	>> TRC: asuspn_obu::ILogger::tryLog(p_logger_, ac_msg, asuspn_obu::ILogger::LEVEL::LEVEL_ERROR);
                   [sourceanalizer.cpp:157]	>> TRC: const uint32_t LoggerFactory::LEVEL_NONE, LoggerFactory::LEVEL_INFO, LoggerFactory::LEVEL_WARN, LoggerFactory::LEVEL_DEBUG, LoggerFactory::LEVEL_ERROR, LoggerFactory::LEVEL_ALL;
                   [sourceanalizer.cpp:157]	>> TRC: //utils::log::CLog &l = utils::log::CLog::getInst();
                   [sourceanalizer.cpp:157]	>> TRC: //utils::log::CLog l = utils::log::CLog();
                   [sourceanalizer.cpp:157]	>> TRC: //l.setLevel(utils::log::LVL_ALL, utils::log::LVL_DBG);
                   [sourceanalizer.cpp:157]	>> TRC: //l.setFormat(utils::log::FMT_ALL, utils::log::FMT_ALL);
                   [sourceanalizer.cpp:157]	>> TRC: //l.setRotate(utils::log::ROT_YY, utils::log::ROT_YYMM);
                   [sourceanalizer.cpp:157]	>> TRC: //utils::log::CLog log_modem = utils::log::CLog();
                   [sourceanalizer.cpp:157]	>> TRC: //log_modem.setFormat(utils::log::FMT_ALL, utils::log::FMT_ALL);
                   [sourceanalizer.cpp:157]	>> TRC: //log_modem.setRotate(utils::log::ROT_NONE, utils::log::ROT_YYMMDD);
                   [sourceanalizer.cpp:157]	>> TRC: //l.addLog("", utils::log::FMT_ALL, utils::log::LVL_ALL);
                   [sourceanalizer.cpp:157]	>> TRC: const uint32_t LoggerFactory::LEVEL_NONE, LoggerFactory::LEVEL_INFO, LoggerFactory::LEVEL_WARN, LoggerFactory::LEVEL_ERROR, LoggerFactory::LEVEL_ALL;                                                                                                                                                                                                                            )delimiter";



colons::colons()
{
    auto lines = QString(cols).split('\n');
    for (auto &l:lines)
                                                                                                                                                                                                                        {
auto tab = std::find(l.begin(), l.end(), '\t')                                                                                                                                                                                                                           ;
                                                                                                                                                                                                                            l.remove(0, 9+tab - l.begin());
std::cout << l.toStdString() << std::endl;
                                                                                                                                                                                                                        }
}
