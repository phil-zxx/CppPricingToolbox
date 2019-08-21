#pragma once

#include <cassert>


namespace Toolbox
{
    bool TB_ASSERT_MESSAGE(const char* /* msg */)
    {
        return false;
    }

    # define TB_ASSERT(expr, msg) assert((expr) || TB_ASSERT_MESSAGE(msg))
}