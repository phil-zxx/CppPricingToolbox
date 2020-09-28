#pragma once


namespace TB
{
    /* ========== dummy false type ========== */
    template<class... Args>
    struct false_template : std::false_type { };
}
