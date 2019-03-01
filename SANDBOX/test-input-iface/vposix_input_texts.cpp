#include "vposix_input_texts.h"



//#include <stdint.h>

#include <linux/input.h>

//#include <string.h>
//#include <fcntl.h>
//#include <unistd.h>
//#include <stdio.h>

//=======================================================================================
static void vec_resize( std::vector<std::string> *v, int sz )
{
    v->resize( sz );
    for (auto & s: *v) s = "?";
}
//=======================================================================================

//=======================================================================================
std::vector<std::string> &events()
{
    static auto res = []()
    {
        std::vector<std::string> res;
        vec_resize( &res, EV_MAX + 1);
        res[EV_SYN] = "Sync";			res[EV_KEY] = "Key";
        res[EV_REL] = "Relative";		res[EV_ABS] = "Absolute";
        res[EV_MSC] = "Misc";			res[EV_LED] = "LED";
        res[EV_SND] = "Sound";			res[EV_REP] = "Repeat";
        res[EV_FF] = "ForceFeedback";   res[EV_PWR] = "Power";
        res[EV_FF_STATUS] = "ForceFeedbackStatus";
        return res;
    }();
    return res;
}
//=======================================================================================
std::vector<std::string>& keys()
{
    static auto res = []()
    {
        std::vector<std::string> res;
        vec_resize( &res, KEY_MAX + 1);
        res[KEY_RESERVED] = "Reserved";		res[KEY_ESC] = "Esc";
        res[KEY_1] = "1";				res[KEY_2] = "2";
        res[KEY_3] = "3";				res[KEY_4] = "4";
        res[KEY_5] = "5";				res[KEY_6] = "6";
        res[KEY_7] = "7";				res[KEY_8] = "8";
        res[KEY_9] = "9";				res[KEY_0] = "0";
        res[KEY_MINUS] = "Minus";			res[KEY_EQUAL] = "Equal";
        res[KEY_BACKSPACE] = "Backspace";		res[KEY_TAB] = "Tab";
        res[KEY_Q] = "Q";				res[KEY_W] = "W";
        res[KEY_E] = "E";				res[KEY_R] = "R";
        res[KEY_T] = "T";				res[KEY_Y] = "Y";
        res[KEY_U] = "U";				res[KEY_I] = "I";
        res[KEY_O] = "O";				res[KEY_P] = "P";
        res[KEY_LEFTBRACE] = "LeftBrace";		res[KEY_RIGHTBRACE] = "RightBrace";
        res[KEY_ENTER] = "Enter";			res[KEY_LEFTCTRL] = "LeftControl";
        res[KEY_A] = "A";				res[KEY_S] = "S";
        res[KEY_D] = "D";				res[KEY_F] = "F";
        res[KEY_G] = "G";				res[KEY_H] = "H";
        res[KEY_J] = "J";				res[KEY_K] = "K";
        res[KEY_L] = "L";				res[KEY_SEMICOLON] = "Semicolon";
        res[KEY_APOSTROPHE] = "Apostrophe";	res[KEY_GRAVE] = "Grave";
        res[KEY_LEFTSHIFT] = "LeftShift";		res[KEY_BACKSLASH] = "BackSlash";
        res[KEY_Z] = "Z";				res[KEY_X] = "X";
        res[KEY_C] = "C";				res[KEY_V] = "V";
        res[KEY_B] = "B";				res[KEY_N] = "N";
        res[KEY_M] = "M";				res[KEY_COMMA] = "Comma";
        res[KEY_DOT] = "Dot";			res[KEY_SLASH] = "Slash";
        res[KEY_RIGHTSHIFT] = "RightShift";	res[KEY_KPASTERISK] = "KPAsterisk";
        res[KEY_LEFTALT] = "LeftAlt";		res[KEY_SPACE] = "Space";
        res[KEY_CAPSLOCK] = "CapsLock";		res[KEY_F1] = "F1";
        res[KEY_F2] = "F2";			res[KEY_F3] = "F3";
        res[KEY_F4] = "F4";			res[KEY_F5] = "F5";
        res[KEY_F6] = "F6";			res[KEY_F7] = "F7";
        res[KEY_F8] = "F8";			res[KEY_F9] = "F9";
        res[KEY_F10] = "F10";			res[KEY_NUMLOCK] = "NumLock";
        res[KEY_SCROLLLOCK] = "ScrollLock";	res[KEY_KP7] = "KP7";
        res[KEY_KP8] = "KP8";			res[KEY_KP9] = "KP9";
        res[KEY_KPMINUS] = "KPMinus";		res[KEY_KP4] = "KP4";
        res[KEY_KP5] = "KP5";			res[KEY_KP6] = "KP6";
        res[KEY_KPPLUS] = "KPPlus";		res[KEY_KP1] = "KP1";
        res[KEY_KP2] = "KP2";			res[KEY_KP3] = "KP3";
        res[KEY_KP0] = "KP0";			res[KEY_KPDOT] = "KPDot";
        res[KEY_ZENKAKUHANKAKU] = "Zenkaku/Hankaku"; res[KEY_102ND] = "102nd";
        res[KEY_F11] = "F11";			res[KEY_F12] = "F12";
        res[KEY_RO] = "RO";			res[KEY_KATAKANA] = "Katakana";
        res[KEY_HIRAGANA] = "HIRAGANA";		res[KEY_HENKAN] = "Henkan";
        res[KEY_KATAKANAHIRAGANA] = "Katakana/Hiragana"; res[KEY_MUHENKAN] = "Muhenkan";
        res[KEY_KPJPCOMMA] = "KPJpComma";		res[KEY_KPENTER] = "KPEnter";
        res[KEY_RIGHTCTRL] = "RightCtrl";		res[KEY_KPSLASH] = "KPSlash";
        res[KEY_SYSRQ] = "SysRq";			res[KEY_RIGHTALT] = "RightAlt";
        res[KEY_LINEFEED] = "LineFeed";		res[KEY_HOME] = "Home";
        res[KEY_UP] = "Up";			res[KEY_PAGEUP] = "PageUp";
        res[KEY_LEFT] = "Left";			res[KEY_RIGHT] = "Right";
        res[KEY_END] = "End";			res[KEY_DOWN] = "Down";
        res[KEY_PAGEDOWN] = "PageDown";		res[KEY_INSERT] = "Insert";
        res[KEY_DELETE] = "Delete";		res[KEY_MACRO] = "Macro";
        res[KEY_MUTE] = "Mute";			res[KEY_VOLUMEDOWN] = "VolumeDown";
        res[KEY_VOLUMEUP] = "VolumeUp";		res[KEY_POWER] = "Power";
        res[KEY_KPEQUAL] = "KPEqual";		res[KEY_KPPLUSMINUS] = "KPPlusMinus";
        res[KEY_PAUSE] = "Pause";			res[KEY_KPCOMMA] = "KPComma";
        res[KEY_HANGUEL] = "Hanguel";		res[KEY_HANJA] = "Hanja";
        res[KEY_YEN] = "Yen";			res[KEY_LEFTMETA] = "LeftMeta";
        res[KEY_RIGHTMETA] = "RightMeta";		res[KEY_COMPOSE] = "Compose";
        res[KEY_STOP] = "Stop";			res[KEY_AGAIN] = "Again";
        res[KEY_PROPS] = "Props";			res[KEY_UNDO] = "Undo";
        res[KEY_FRONT] = "Front";			res[KEY_COPY] = "Copy";
        res[KEY_OPEN] = "Open";			res[KEY_PASTE] = "Paste";
        res[KEY_FIND] = "Find";			res[KEY_CUT] = "Cut";
        res[KEY_HELP] = "Help";			res[KEY_MENU] = "Menu";
        res[KEY_CALC] = "Calc";			res[KEY_SETUP] = "Setup";
        res[KEY_SLEEP] = "Sleep";			res[KEY_WAKEUP] = "WakeUp";
        res[KEY_FILE] = "File";			res[KEY_SENDFILE] = "SendFile";
        res[KEY_DELETEFILE] = "DeleteFile";	res[KEY_XFER] = "X-fer";
        res[KEY_PROG1] = "Prog1";			res[KEY_PROG2] = "Prog2";
        res[KEY_WWW] = "WWW";			res[KEY_MSDOS] = "MSDOS";
        res[KEY_COFFEE] = "Coffee";		res[KEY_DIRECTION] = "Direction";
        res[KEY_CYCLEWINDOWS] = "CycleWindows";	res[KEY_MAIL] = "Mail";
        res[KEY_BOOKMARKS] = "Bookmarks";		res[KEY_COMPUTER] = "Computer";
        res[KEY_BACK] = "Back";			res[KEY_FORWARD] = "Forward";
        res[KEY_CLOSECD] = "CloseCD";		res[KEY_EJECTCD] = "EjectCD";
        res[KEY_EJECTCLOSECD] = "EjectCloseCD";	res[KEY_NEXTSONG] = "NextSong";
        res[KEY_PLAYPAUSE] = "PlayPause";		res[KEY_PREVIOUSSONG] = "PreviousSong";
        res[KEY_STOPCD] = "StopCD";		res[KEY_RECORD] = "Record";
        res[KEY_REWIND] = "Rewind";		res[KEY_PHONE] = "Phone";
        res[KEY_ISO] = "ISOKey";			res[KEY_CONFIG] = "Config";
        res[KEY_HOMEPAGE] = "HomePage";		res[KEY_REFRESH] = "Refresh";
        res[KEY_EXIT] = "Exit";			res[KEY_MOVE] = "Move";
        res[KEY_EDIT] = "Edit";			res[KEY_SCROLLUP] = "ScrollUp";
        res[KEY_SCROLLDOWN] = "ScrollDown";	res[KEY_KPLEFTPAREN] = "KPLeftParenthesis";
        res[KEY_KPRIGHTPAREN] = "KPRightParenthesis"; res[KEY_F13] = "F13";
        res[KEY_F14] = "F14";			res[KEY_F15] = "F15";
        res[KEY_F16] = "F16";			res[KEY_F17] = "F17";
        res[KEY_F18] = "F18";			res[KEY_F19] = "F19";
        res[KEY_F20] = "F20";			res[KEY_F21] = "F21";
        res[KEY_F22] = "F22";			res[KEY_F23] = "F23";
        res[KEY_F24] = "F24";			res[KEY_PLAYCD] = "PlayCD";
        res[KEY_PAUSECD] = "PauseCD";		res[KEY_PROG3] = "Prog3";
        res[KEY_PROG4] = "Prog4";			res[KEY_SUSPEND] = "Suspend";
        res[KEY_CLOSE] = "Close";			res[KEY_PLAY] = "Play";
        res[KEY_FASTFORWARD] = "Fast Forward";	res[KEY_BASSBOOST] = "Bass Boost";
        res[KEY_PRINT] = "Print";			res[KEY_HP] = "HP";
        res[KEY_CAMERA] = "Camera";		res[KEY_SOUND] = "Sound";
        res[KEY_QUESTION] = "Question";		res[KEY_EMAIL] = "Email";
        res[KEY_CHAT] = "Chat";			res[KEY_SEARCH] = "Search";
        res[KEY_CONNECT] = "Connect";		res[KEY_FINANCE] = "Finance";
        res[KEY_SPORT] = "Sport";			res[KEY_SHOP] = "Shop";
        res[KEY_ALTERASE] = "Alternate Erase";	res[KEY_CANCEL] = "Cancel";
        res[KEY_BRIGHTNESSDOWN] = "Brightness down"; res[KEY_BRIGHTNESSUP] = "Brightness up";
        res[KEY_MEDIA] = "Media";			res[KEY_UNKNOWN] = "Unknown";
        res[BTN_0] = "Btn0";			res[BTN_1] = "Btn1";
        res[BTN_2] = "Btn2";			res[BTN_3] = "Btn3";
        res[BTN_4] = "Btn4";			res[BTN_5] = "Btn5";
        res[BTN_6] = "Btn6";			res[BTN_7] = "Btn7";
        res[BTN_8] = "Btn8";			res[BTN_9] = "Btn9";
        res[BTN_LEFT] = "LeftBtn";			res[BTN_RIGHT] = "RightBtn";
        res[BTN_MIDDLE] = "MiddleBtn";		res[BTN_SIDE] = "SideBtn";
        res[BTN_EXTRA] = "ExtraBtn";		res[BTN_FORWARD] = "ForwardBtn";
        res[BTN_BACK] = "BackBtn";			res[BTN_TASK] = "TaskBtn";
        res[BTN_TRIGGER] = "Trigger";		res[BTN_THUMB] = "ThumbBtn";
        res[BTN_THUMB2] = "ThumbBtn2";		res[BTN_TOP] = "TopBtn";
        res[BTN_TOP2] = "TopBtn2";			res[BTN_PINKIE] = "PinkieBtn";
        res[BTN_BASE] = "BaseBtn";			res[BTN_BASE2] = "BaseBtn2";
        res[BTN_BASE3] = "BaseBtn3";		res[BTN_BASE4] = "BaseBtn4";
        res[BTN_BASE5] = "BaseBtn5";		res[BTN_BASE6] = "BaseBtn6";
        res[BTN_DEAD] = "BtnDead";			res[BTN_A] = "BtnA";
        res[BTN_B] = "BtnB";			res[BTN_C] = "BtnC";
        res[BTN_X] = "BtnX";			res[BTN_Y] = "BtnY";
        res[BTN_Z] = "BtnZ";			res[BTN_TL] = "BtnTL";
        res[BTN_TR] = "BtnTR";			res[BTN_TL2] = "BtnTL2";
        res[BTN_TR2] = "BtnTR2";			res[BTN_SELECT] = "BtnSelect";
        res[BTN_START] = "BtnStart";		res[BTN_MODE] = "BtnMode";
        res[BTN_THUMBL] = "BtnThumbL";		res[BTN_THUMBR] = "BtnThumbR";
        res[BTN_TOOL_PEN] = "ToolPen";		res[BTN_TOOL_RUBBER] = "ToolRubber";
        res[BTN_TOOL_BRUSH] = "ToolBrush";		res[BTN_TOOL_PENCIL] = "ToolPencil";
        res[BTN_TOOL_AIRBRUSH] = "ToolAirbrush";	res[BTN_TOOL_FINGER] = "ToolFinger";
        res[BTN_TOOL_MOUSE] = "ToolMouse";		res[BTN_TOOL_LENS] = "ToolLens";
        res[BTN_TOUCH] = "Touch";			res[BTN_STYLUS] = "Stylus";
        res[BTN_STYLUS2] = "Stylus2";		res[BTN_TOOL_DOUBLETAP] = "Tool Doubletap";
        res[BTN_TOOL_TRIPLETAP] = "Tool Tripletap"; res[BTN_GEAR_DOWN] = "WheelBtn";
        res[BTN_GEAR_UP] = "Gear up";		res[KEY_OK] = "Ok";
        res[KEY_SELECT] = "Select";		res[KEY_GOTO] = "Goto";
        res[KEY_CLEAR] = "Clear";			res[KEY_POWER2] = "Power2";
        res[KEY_OPTION] = "Option";		res[KEY_INFO] = "Info";
        res[KEY_TIME] = "Time";			res[KEY_VENDOR] = "Vendor";
        res[KEY_ARCHIVE] = "Archive";		res[KEY_PROGRAM] = "Program";
        res[KEY_CHANNEL] = "Channel";		res[KEY_FAVORITES] = "Favorites";
        res[KEY_EPG] = "EPG";			res[KEY_PVR] = "PVR";
        res[KEY_MHP] = "MHP";			res[KEY_LANGUAGE] = "Language";
        res[KEY_TITLE] = "Title";			res[KEY_SUBTITLE] = "Subtitle";
        res[KEY_ANGLE] = "Angle";			res[KEY_ZOOM] = "Zoom";
        res[KEY_MODE] = "Mode";			res[KEY_KEYBOARD] = "Keyboard";
        res[KEY_SCREEN] = "Screen";		res[KEY_PC] = "PC";
        res[KEY_TV] = "TV";			res[KEY_TV2] = "TV2";
        res[KEY_VCR] = "VCR";			res[KEY_VCR2] = "VCR2";
        res[KEY_SAT] = "Sat";			res[KEY_SAT2] = "Sat2";
        res[KEY_CD] = "CD";			res[KEY_TAPE] = "Tape";
        res[KEY_RADIO] = "Radio";			res[KEY_TUNER] = "Tuner";
        res[KEY_PLAYER] = "Player";		res[KEY_TEXT] = "Text";
        res[KEY_DVD] = "DVD";			res[KEY_AUX] = "Aux";
        res[KEY_MP3] = "MP3";			res[KEY_AUDIO] = "Audio";
        res[KEY_VIDEO] = "Video";			res[KEY_DIRECTORY] = "Directory";
        res[KEY_LIST] = "List";			res[KEY_MEMO] = "Memo";
        res[KEY_CALENDAR] = "Calendar";		res[KEY_RED] = "Red";
        res[KEY_GREEN] = "Green";			res[KEY_YELLOW] = "Yellow";
        res[KEY_BLUE] = "Blue";			res[KEY_CHANNELUP] = "ChannelUp";
        res[KEY_CHANNELDOWN] = "ChannelDown";	res[KEY_FIRST] = "First";
        res[KEY_LAST] = "Last";			res[KEY_AB] = "AB";
        res[KEY_NEXT] = "Next";			res[KEY_RESTART] = "Restart";
        res[KEY_SLOW] = "Slow";			res[KEY_SHUFFLE] = "Shuffle";
        res[KEY_BREAK] = "Break";			res[KEY_PREVIOUS] = "Previous";
        res[KEY_DIGITS] = "Digits";		res[KEY_TEEN] = "TEEN";
        res[KEY_TWEN] = "TWEN";			res[KEY_DEL_EOL] = "Delete EOL";
        res[KEY_DEL_EOS] = "Delete EOS";		res[KEY_INS_LINE] = "Insert line";
        res[KEY_DEL_LINE] = "Delete line";
        return res;
    }(); // lambda
    return res;
}
//=======================================================================================
std::vector<std::string>& absval()
{
    static auto res = []()
    {
        return std::vector<std::string>{ "Value", "Min  ", "Max  ", "Fuzz ", "Flat " };
    }(); // lambda
    return res;
}
//=======================================================================================
std::vector<std::string> &relatives()
{
    static auto res = []()
    {
        std::vector<std::string> res;
        vec_resize( &res, REL_MAX + 1);

        res[REL_X] = "X";			res[REL_Y] = "Y";
        res[REL_Z] = "Z";			res[REL_HWHEEL] = "HWheel";
        res[REL_DIAL] = "Dial";		res[REL_WHEEL] = "Wheel";
        res[REL_MISC] = "Misc";

        return res;
    }(); // lambda
    return res;
}
//=======================================================================================

std::vector<std::string> &absolutes()
{
    static auto res = []()
    {
        std::vector<std::string> res;
        vec_resize( &res, ABS_MAX + 1);

        res[ABS_X] = "X";               res[ABS_Y] = "Y";
        res[ABS_Z] = "Z";               res[ABS_RX] = "Rx";
        res[ABS_RY] = "Ry";             res[ABS_RZ] = "Rz";
        res[ABS_THROTTLE] = "Throttle";	res[ABS_RUDDER] = "Rudder";
        res[ABS_WHEEL] = "Wheel";		res[ABS_GAS] = "Gas";
        res[ABS_BRAKE] = "Brake";		res[ABS_HAT0X] = "Hat0X";
        res[ABS_HAT0Y] = "Hat0Y";		res[ABS_HAT1X] = "Hat1X";
        res[ABS_HAT1Y] = "Hat1Y";		res[ABS_HAT2X] = "Hat2X";
        res[ABS_HAT2Y] = "Hat2Y";		res[ABS_HAT3X] = "Hat3X";
        res[ABS_HAT3Y] = "Hat 3Y";		res[ABS_PRESSURE] = "Pressure";
        res[ABS_DISTANCE] = "Distance";	res[ABS_TILT_X] = "XTilt";
        res[ABS_TILT_Y] = "YTilt";		res[ABS_TOOL_WIDTH] = "Tool Width";
        res[ABS_VOLUME] = "Volume";     res[ABS_MISC] = "Misc";

        return res;
    }(); // lambda
    return res;
}
//=======================================================================================
std::vector<std::string> &misc()
{
    static auto res = []()
    {
        std::vector<std::string> res;
        vec_resize( &res, MSC_MAX + 1);

        res[MSC_SERIAL] = "Serial";     res[MSC_PULSELED] = "Pulseled";
        res[MSC_GESTURE] = "Gesture";	res[MSC_RAW] = "RawData";
        res[MSC_SCAN] = "ScanCode";

        return res;
    }(); // lambda
    return res;
}

//=======================================================================================

std::vector<std::string> &leds()
{
    static auto res = []()
    {
        std::vector<std::string> res;
        vec_resize( &res, LED_MAX + 1 );

        res.at(LED_NUML) = "NumLock";		res.at(LED_CAPSL) = "CapsLock";
        res.at(LED_SCROLLL) = "ScrollLock";	res.at(LED_COMPOSE) = "Compose";
        res.at(LED_KANA) = "Kana";		res.at(LED_SLEEP) = "Sleep";
        res.at(LED_SUSPEND) = "Suspend";	res.at(LED_MUTE) = "Mute";
        res.at(LED_MISC) = "Misc";

        return res;
    }(); // lambda
    return res;
}

//=======================================================================================

std::vector<std::string> &repeats()
{
    static auto res = []()
    {
        std::vector<std::string> res;
        vec_resize( &res, REP_MAX + 1 );

        res[REP_DELAY] = "Delay";
        res[REP_PERIOD] = "Period";

        return res;
    }(); // lambda
    return res;
}
//=======================================================================================
std::vector<std::string> &sounds()
{
    static auto res = []()
    {
        std::vector<std::string> res;
        vec_resize( &res, SND_MAX + 1 );

        res[SND_CLICK] = "Click";		res[SND_BELL] = "Bell";
        res[SND_TONE] = "Tone";

        return res;
    }(); // lambda
    return res;
}
//=======================================================================================
std::vector<std::vector<std::string>> &names()
{
    static auto res = []()
    {
        std::vector<std::vector<std::string>> res;
        res.resize( EV_MAX + 1 );

        res[EV_SYN] = events();			res[EV_KEY] = keys();
        res[EV_REL] = relatives();		res[EV_ABS] = absolutes();
        res[EV_MSC] = misc();           res[EV_LED] = leds();
        res[EV_SND] = sounds();			res[EV_REP] = repeats();

        return res;
    }(); // lambda
    return res;
}
//=======================================================================================
