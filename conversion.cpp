#include "conversion.h"


double Conversion::kias2angle(double kias)
{
    return ((359-kias) - 181);
}

Conversion::Conversion()
{

}
