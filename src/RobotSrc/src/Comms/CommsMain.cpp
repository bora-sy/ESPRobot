#include "Comms/CommsMain.h"

bool CommsMain::Initialize()
{
    return true;
}


void CommsMain::Loop()
{
    Comm_Espnow::Loop();
}