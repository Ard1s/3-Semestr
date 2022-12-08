#include "Call_states.h"

Call_states::Call_states()
{
    stateUp = 0;
    stateDown = 0;
}

unsigned short int Call_states::getStateUp()
{
    return stateUp;
}

unsigned short int Call_states::getStateDown()
{
    return stateDown;
}

void Call_states::setStateUp(unsigned short int s)
{
    stateUp = s;
}

void Call_states::setStateDown(unsigned short s)
{
    stateDown = s;
}

bool Call_states::isMine()
{
    if (stateDown==9 || stateDown==10)
        return true;
    else
        return false;
}

bool Call_states::isFlag()
{
    if (stateUp==2)
        return true;
    else
        return false;
}

bool Call_states::isClicked()
{
    if (stateUp==1 or stateUp==3)
        return true;
    else
        return false;
}

void Call_states::setMine()
{
    stateDown = 9;
}
