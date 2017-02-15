#ifndef BANSHEERUNE_H
#define BANSHEERUNE_H

#include "innerlinker.h"
#include "inneroutlinker.h"
#include "linkerpoint.h"



namespace banshee_rune {

class FrontBottomLinkerPoint:public FrontBBPoint
{
    // LinkerPoint interface
public:
    Param getParam();
};

class FrontUpLinkerPoint:public FrontSeatPoint
{
    // LinkerPoint interface
public:
    Param getParam();
};

class FrontShoxPoint:public FrontBottomPoint
{
    // LinkerPoint interface
public:
    Param getParam();
};

class RearBottomLinkerPoint:public RearBottomPoint
{
 // LinkerPoint interface
public:
    Param getParam();
};

class RearUpLinkerPoint:public RearUpPoint
{
 // LinkerPoint interface
public:
    Param getParam();
};

class RearShoxPoint:public RearTopExtenPoint
{
 // LinkerPoint interface
public:
    Param getParam();
};

}
struct BansheeRune
{
    typedef banshee_rune::FrontBottomLinkerPoint front_point1;
    typedef banshee_rune::FrontUpLinkerPoint front_point2;
    typedef banshee_rune::RearBottomLinkerPoint rear_point1;
    typedef banshee_rune::RearUpLinkerPoint rear_point2;
    typedef InnerLinker linker1;
    typedef InnerOutLinker linker2;
    typedef banshee_rune::FrontShoxPoint front_shox_point;
    typedef banshee_rune::RearShoxPoint rear_shox_point;
};

#endif // BANSHEERUNE_H
