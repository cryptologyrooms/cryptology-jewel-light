#include "raat.hpp"

#include "raat-oneshot-timer.hpp"

static bool game_complete = false;

static RAATOneShotTimer s_timers[3] = {
    RAATOneShotTimer(0),
    RAATOneShotTimer(0),
    RAATOneShotTimer(0)
};

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
}

void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
{
    bool states[3] = {false, false, false};

    if (!game_complete)
    {
        for (uint8_t i = 0; i<3; i++)
        {
            if (devices.pInputs[i]->check_low_and_clear())
            {
                raat_logln(LOG_APP, "Input %d trigger", i);
            }

            if (devices.pInputs[i]->check_high_and_clear())
            {
                raat_logln(LOG_APP, "Input %d cleared", i);
            }

            if (devices.pInputs[i]->state() == true)
            {
                s_timers[i].start(params.pTriggerHold->get());
            }
            states[i] = s_timers[i].is_running() && !s_timers[i].check();
            devices.pLEDOutputs[i]->set(states[i]);
        }

        if (states[0] && states[1] && states[2])
        {
            game_complete = true;
            raat_logln(LOG_APP, "Game complete!");
        }
    }
    else
    {
        devices.pRelayOutput->set(true);
        devices.pLEDOutputs[0]->set(true);
        devices.pLEDOutputs[1]->set(true);
        devices.pLEDOutputs[2]->set(true);
    }
}
