#include "StateBase.h"

#include <vcruntime_typeinfo.h>


void StateBase::OnEnterState(EventBase* e)
{
	 typeid(e);
}
