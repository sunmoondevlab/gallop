// Copyright © 2024- Sunmoon development laboratory All Rights Reserved
#ifndef _CHAR_SET_CHAR_CODE_UTF_ASCII_TABLE_
#define _CHAR_SET_CHAR_CODE_UTF_ASCII_TABLE_

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace gallop {
namespace CharSet {
namespace CharCode {

enum class UtfAsciiTable : uint8_t {
  NullChar,
  StartOfHeading,
  StartOfText,
  EndOfText,
  EndOfTransmission,
  Enquiry,
  Acknowledge,
  BellAlert,      // \a
  Backspace,      // \b
  HorizontalTab,  // \t
  LineFeed,       // \n
  VerticalTab,    // \v
  FormFeed,       // \f
  CarriageReturn, // \r
  ShiftOut,
  ShiftIn,
  DataLinkEscape,
  DeviceControlOne,
  DeviceControlTwo,
  DeviceControlThree,
  DeviceControlFour,
  NegativeAcknowledge,
  SynchronousIdle,
  EndOfTransmissionBlock,
  Cancel,
  EndOfMedium,
  Substitute,
  Escape,
  FileSeparator,
  GroupSeparator,
  RecordSeparator,
  UnitSeparator,
  Space,              // space
  Exclamation,        // !
  DoubleQuotation,    // "
  NumberSign,         // #
  Dollar,             // $
  Percent,            // %
  Ampersand,          // &
  SingleQuotation,    // '
  ParenthesesOpen,    // (
  ParenthesesClose,   // )
  Asterisk,           // *
  Plus,               // +
  Comma,              // ,
  Minus,              // -
  Dot,                // .
  Slash,              // /
  Number0,            // 0
  Number1,            // 1
  Number2,            // 2
  Number3,            // 3
  Number4,            // 4
  Number5,            // 5
  Number6,            // 6
  Number7,            // 7
  Number8,            // 8
  Number9,            // 9
  Colon,              // :
  SemiColon,          // ;
  LessThan,           // <
  Equal,              // =
  GreaterThan,        // >
  Question,           // ?
  AtSign,             // @
  UpperA,             // A
  UpperB,             // B
  UpperC,             // C
  UpperD,             // D
  UpperE,             // E
  UpperF,             // F
  UpperG,             // G
  UpperH,             // H
  UpperI,             // I
  UpperJ,             // J
  UpperK,             // K
  UpperL,             // L
  UpperM,             // M
  UpperN,             // N
  UpperO,             // O
  UpperP,             // P
  UpperQ,             // Q
  UpperR,             // R
  UpperS,             // S
  UpperT,             // T
  UpperU,             // U
  UpperV,             // V
  UpperW,             // W
  UpperX,             // X
  UpperY,             // Y
  UpperZ,             // Z
  SquareBracketOpen,  // [
  BackSlash,          // '\\'
  SquareBracketClose, // ]
  Caret,              // ^
  Underline,          // _
  BackQuotation,      // `
  LowerA,             // a
  LowerB,             // b
  LowerC,             // c
  LowerD,             // d
  LowerE,             // e
  LowerF,             // f
  LowerG,             // g
  LowerH,             // h
  LowerI,             // i
  LowerJ,             // j
  LowerK,             // k
  LowerL,             // l
  LowerM,             // m
  LowerN,             // n
  LowerO,             // o
  LowerP,             // p
  LowerQ,             // q
  LowerR,             // r
  LowerS,             // s
  LowerT,             // t
  LowerU,             // u
  LowerV,             // v
  LowerW,             // w
  LowerX,             // x
  LowerY,             // y
  LowerZ,             // z
  CurlyBracketOpen,   // {
  VerticalBar,        // |
  CurlyBracketClose,  // }
  Tilde,              // ~
  Delete,
};

} // namespace CharCode
} // namespace CharSet
} // namespace gallop
#endif