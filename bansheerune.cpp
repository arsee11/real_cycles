#include "bansheerune.h"

namespace banshee_rune {

FrontBottomLinkerPoint::Param FrontBottomLinkerPoint::getParam()
{
    return Param(0.f, 3.f, 4.f);
}

FrontUpLinkerPoint::Param FrontUpLinkerPoint::getParam()
{
    return Param(-2.f, 28.f, 4.f, false);
}

RearBottomLinkerPoint::Param RearBottomLinkerPoint::getParam()
{
    return Param(-1.f, 0.f, 4.f);
}

RearUpLinkerPoint::Param RearUpLinkerPoint::getParam()
{
    return Param(-1.f, 5.f, 4.f);
}

FrontShoxPoint::Param FrontShoxPoint::getParam()
{
    return Param(34.f, 5.f, 4.f);
}

RearShoxPoint::Param RearShoxPoint::getParam()
{
    return Param(8.f, 0.f, 4.f);
}

}
