#pragma once

static
const char* KeyNames[] = {
  "OFF",
  "LBUTTON",
  "RBUTTON",
  "CANCEL",
  "MBUTTON",
  "XBUTTON1",
  "XBUTTON2",
  "Unknown",
  "BACK",
  "TAB",
  "Unknown",
  "Unknown",
  "CLEAR",
  "RETURN",
  "Unknown",
  "Unknown",
  "SHIFT",
  "CONTROL",
  "MENU",
  "PAUSE",
  "CAPITAL",
  "KANA",
  "Unknown",
  "JUNJA",
  "FINAL",
  "KANJI",
  "Unknown",
  "ESCAPE",
  "CONVERT",
  "NONCONVERT",
  "ACCEPT",
  "MODECHANGE",
  "SPACE",
  "PRIOR",
  "NEXT",
  "END",
  "HOME",
  "LEFT",
  "UP",
  "RIGHT",
  "DOWN",
  "SELECT",
  "PRINT",
  "EXECUTE",
  "SNAPSHOT",
  "INSERT",
  "DELETE",
  "HELP",
  "0",
  "1",
  "2",
  "3",
  "4",
  "5",
  "6",
  "7",
  "8",
  "9",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "A",
  "B",
  "C",
  "D",
  "E",
  "F",
  "G",
  "H",
  "I",
  "J",
  "K",
  "L",
  "M",
  "N",
  "O",
  "P",
  "Q",
  "R",
  "S",
  "T",
  "U",
  "V",
  "W",
  "X",
  "Y",
  "Z",
  "LWIN",
  "RWIN",
  "APPS",
  "Unknown",
  "SLEEP",
  "NUMPAD0",
  "NUMPAD1",
  "NUMPAD2",
  "NUMPAD3",
  "NUMPAD4",
  "NUMPAD5",
  "NUMPAD6",
  "NUMPAD7",
  "NUMPAD8",
  "NUMPAD9",
  "MULTIPLY",
  "ADD",
  "SEPARATOR",
  "SUBTRACT",
  "DECIMAL",
  "DIVIDE",
  "F1",
  "F2",
  "F3",
  "F4",
  "F5",
  "F6",
  "F7",
  "F8",
  "F9",
  "F10",
  "F11",
  "F12",
  "F13",
  "F14",
  "F15",
  "F16",
  "F17",
  "F18",
  "F19",
  "F20",
  "F21",
  "F22",
  "F23",
  "F24",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "NUMLOCK",
  "SCROLL",
  "NEC_EQUAL",
  "FJ_MASSHOU",
  "FJ_TOUROKU",
  "FJ_LOYA",
  "FJ_ROYA",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "LSHIFT",
  "RSHIFT",
  "LCONTROL",
  "RCONTROL",
  "LMENU",
  "RMENU",

  "BROWSER_BACK",
  "BROWSER_FORWARD",
  "BROWSER_REFRESH",
  "BROWSER_STOP",
  "BROWSER_SEARCH",
  "BROWSER_FAVORITES",
  "BROWSER_HOME",
  "VOLUME_MUTE",
  "VOLUME_DOWN",
  "VOLUME_UP",

  "MEDIA_NEXT_TRACK",
  "MEDIA_PREV_TRACK",
  "MEDIA_STOP",
  "MEDIA_PLAY_PAUSE",
  "LAUNCH_MAIL",
  "LAUNCH_MEDIA_SELECT",
  "LAUNCH_APP1",
  "LAUNCH_APP2",

  "Unknown",
  "Unknown",
  ";:",
  "+",
  ",",
  "-",
  ".",
  "/?",
  "`~",
  "ABNT_C1",
  "ABNT_C2",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",

  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "Unknown",
  "[{",
  "\\",
  "]}",
  "'\"",
  "Unknown",

  "Unknown",
  "AX",
  "102",
  "ICO_HELP",
  "ICO_00",
  "PROCESSKEY",
  "ICO_CLEAR",
  "PACKET",
  "Unknown",
  "RESET",
  "JUMP",
  "PA1",
  "PA2",
  "PA3",
  "WSCTRL",
  "CUSEL",

  "ATTN",
  "FINISH",
  "COPY",
  "AUTO",
  "ENLW",
  "BACKTAB",
  "ATTN",
  "CRSEL",
  "EXSEL",
  "EREOF",
  "PLAY",
  "ZOOM",
  "NONAME",
  "PA1",
  "CLEAR"
};

static
const int KeyCodes[] = {
  0x0, //Undefined
  0x01,
  0x02,
  0x03,
  0x04,
  0x05,
  0x06,
  0x07, //Undefined
  0x08,
  0x09,
  0x0A, //Reserved
  0x0B, //Reserved
  0x0C,
  0x0D,
  0x0E, //Undefined
  0x0F, //Undefined
  0x10,
  0x11,
  0x12,
  0x13,
  0x14,
  0x15,
  0x16, //IME On
  0x17,
  0x18,
  0x19,
  0x1A, //IME Off
  0x1B,
  0x1C,
  0x1D,
  0x1E,
  0x1F,
  0x20,
  0x21,
  0x22,
  0x23,
  0x24,
  0x25,
  0x26,
  0x27,
  0x28,
  0x29,
  0x2A,
  0x2B,
  0x2C,
  0x2D,
  0x2E,
  0x2F,
  0x30,
  0x31,
  0x32,
  0x33,
  0x34,
  0x35,
  0x36,
  0x37,
  0x38,
  0x39,
  0x3A, //Undefined
  0x3B, //Undefined
  0x3C, //Undefined
  0x3D, //Undefined
  0x3E, //Undefined
  0x3F, //Undefined
  0x40, //Undefined
  0x41,
  0x42,
  0x43,
  0x44,
  0x45,
  0x46,
  0x47,
  0x48,
  0x49,
  0x4A,
  0x4B,
  0x4C,
  0x4D,
  0x4E,
  0x4F,
  0x50,
  0x51,
  0x52,
  0x53,
  0x54,
  0x55,
  0x56,
  0x57,
  0x58,
  0x59,
  0x5A,
  0x5B,
  0x5C,
  0x5D,
  0x5E, //Rservered
  0x5F,
  0x60, //Numpad1
  0x61, //Numpad2
  0x62, //Numpad3
  0x63, //Numpad4
  0x64, //Numpad5
  0x65, //Numpad6
  0x66, //Numpad7
  0x67, //Numpad8
  0x68, //Numpad8
  0x69, //Numpad9
  0x6A,
  0x6B,
  0x6C,
  0x6D,
  0x6E,
  0x6F,
  0x70, //F1
  0x71, //F2
  0x72, //F3
  0x73, //F4
  0x74, //F5
  0x75, //F6
  0x76, //F7
  0x77, //F8
  0x78, //F9
  0x79, //F10
  0x7A, //F11
  0x7B, //F12
  0x7C, //F13
  0x7D, //F14
  0x7E, //F15
  0x7F, //F16
  0x80, //F17
  0x81, //F18
  0x82, //F19
  0x83, //F20
  0x84, //F21
  0x85, //F22
  0x86, //F23
  0x87, //F24
  0x88, //Unkown
  0x89, //Unkown
  0x8A, //Unkown
  0x8B, //Unkown
  0x8C, //Unkown
  0x8D, //Unkown
  0x8E, //Unkown
  0x8F, //Unkown
  0x90,
  0x91,
  0x92, //OEM Specific
  0x93, //OEM Specific
  0x94, //OEM Specific
  0x95, //OEM Specific
  0x96, //OEM Specific
  0x97, //Unkown
  0x98, //Unkown
  0x99, //Unkown
  0x9A, //Unkown
  0x9B, //Unkown
  0x9C, //Unkown
  0x9D, //Unkown
  0x9E, //Unkown 
  0x9F, //Unkown
  0xA0,
  0xA1,
  0xA2,
  0xA3,
  0xA4,
  0xA5,
  0xa6,
  0xa7,
  0xa8,
  0xa9,
  0xaa,
  0xab,
  0xac,
  0xad,
  0xae,
  0xaf,
  0xb0,
  0xb1,
  0xb2,
  0xb3,
  0xb4,
  0xb5,
  0xb6,
  0xb7,
  0xb8,
  0xb9,
  0xba,
  0xbb,
  0xbc,
  0xbd,
  0xbe,
  0xbf,
  0xc0,
  0xc1,
  0xc2,
  0xc3,
  0xc4,
  0xc5,
  0xc6,
  0xc7,
  0xc8,
  0xc9,
  0xca,
  0xcb,
  0xcc,
  0xcd,
  0xce,
  0xcf,
  0xd0,
  0xd1,
  0xd2,
  0xd3,
  0xd4,
  0xd5,
  0xd6,
  0xd7,
  0xd8,
  0xd9,
  0xda,
  0xdb,
  0xdc,
  0xdd,
  0xde,
  0xdf,
  0xe0,
  0xe1,
  0xe2,
  0xe3,
  0xe4,
  0xe5,
  0xe6,
  0xe7,
  0xe8,
  0xe9,
  0xea,
  0xeb,
  0xec,
  0xed,
  0xee,
  0xef,
  0xf0,
  0xf1,
  0xf2,
  0xf3,
  0xf4,
  0xf5,
  0xf6,
  0xf7,
  0xf8,
  0xf9,
  0xfa,
  0xfb,
  0xfc,
  0xfd,
  0xfe,
};