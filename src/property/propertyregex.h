#pragma once

#include "def_regex.h"


// some string, some spaces, equals, some spaces, some string, maybe a comment
static regexns::regex line_regex() { return regexns::regex(R"(^([\w\.]*) *= *(.+?)( *#.*)?$)"); }
static regexns::regex title_regex() { return regexns::regex(R"(^\[(\w+)\])"); }

static regexns::regex float_regex() { return regexns::regex(R"(^[-+]?\d*\.?\d*$)"); }
static regexns::regex int_regex() { return regexns::regex(R"(^([-+]?\d+)$)"); }
static regexns::regex uint32_regex() { return regexns::regex(R"(^(\d+)|(0x([0-9a-fA-F]){1,8})$)"); } // stoi can also parse hex values
static regexns::regex bool_regex() { return regexns::regex(R"(^(true|false)$)"); }
static regexns::regex char_regex() { return regexns::regex(R"(^\w$)"); }
static regexns::regex string_regex() { return regexns::regex(R"(^.*$)"); }
static regexns::regex vec2_regex() { return regexns::regex(R"(^([-+]?\d*\.?\d*), *([-+]?\d*\.?\d*)$)"); }
static regexns::regex vec3_regex() { return regexns::regex(R"(^([-+]?\d*\.?\d*), *([-+]?\d*\.?\d*), *([-+]?\d*\.?\d*)$)"); }
static regexns::regex vec4_regex() { return regexns::regex(R"(^([-+]?\d*\.?\d*), *([-+]?\d*\.?\d*), *([-+]?\d*\.?\d*), *([-+]?\d*\.?\d*)$)"); }
static regexns::regex input_mapping_regex() { return regexns::regex(R"(^InputMapping\((\d+), *(\d+), *([-+]?\d*\.?\d*), *([-+]?\d*\.?\d*)\)$)"); }
static regexns::regex list_regex() { return regexns::regex(R"(^([a-zA-Z1-9]+)(, *([a-zA-Z1-9]+))*$)"); }
