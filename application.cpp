#include "raat.hpp"

static bool bRelaySet = false;

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;
}

void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
{
    bool states[3];

    for (uint8_t i = 0; i<3; i++)
    {
        states[i] = devices.pInputs[i]->state();
        devices.pLEDOutputs[i]->set(states[i]);
    }

    if (states[0] && states[1] && states[2])
    {
        bRelaySet = true;
    }

    devices.pRelayOutput->set(bRelaySet);
}
