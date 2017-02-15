#include "bansheerune.h"

namespace banshee_rune {

RearBottomLinkerPoint::Param FrontBottomLinkerPoint::getParam()
{
    return Param(4.f, 3.f, 4.f);
}

FrontUpLinkerPoint::Param FrontUpLinkerPoint::getParam()
{
    return Param(-2.f, 28.f, 4.f, false);
}

RearBottomLinkerPoint::Param RearBottomLinkerPoint::getParam()
{
    return Param(0.f, 4.f, 0.f);
}

RearUpLinkerPoint::Param RearUpLinkerPoint::getParam()
{
    return Param(0.f, 5.f, 0.f);
}

FrontShoxPoint::Param FrontShoxPoint::getParam()
{
    return Param(34.f, 5.f, 4.f);
}

RearShoxPoint::Param RearShoxPoint::getParam()
{
    return Param(13.f, 0.f, 4.f);
}

}
