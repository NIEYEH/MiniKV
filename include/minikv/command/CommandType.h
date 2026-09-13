#pragma once

// 不用字符串的原因是字符串比较慢，而且容易写错
enum class CommandType
{
    SET,
    GET,
    DEL,
    UNKNOWN
};