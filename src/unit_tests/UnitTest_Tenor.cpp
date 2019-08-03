#include <toolbox/Date/Tenor.hpp>

using namespace Toolbox;


int main()
{
    /* Since we evaluate to constexpr, all unit tests are performed at compile time */

    static_assert(Tenor(3, 'D').count() == 3 && Tenor(3, 'D').unit() == 'D');
    static_assert(Tenor(6, 'M').count() == 6 && Tenor(6, 'M').unit() == 'M');
    static_assert(Tenor("3D").count() == 3 && Tenor("3D").unit() == 'D');
    static_assert(Tenor("6M").count() == 6 && Tenor("6M").unit() == 'M');
}
