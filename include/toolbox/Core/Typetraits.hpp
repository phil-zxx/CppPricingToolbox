#pragma once


namespace Toolbox
{
    /* ========== dummy false type ========== */
    template<class... Args>
    struct false_template : std::false_type { };
}
