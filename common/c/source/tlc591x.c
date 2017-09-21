/**
 * @file   tlc591x_avr.c
 * @brief  This file contains the TLC591x driver implementation for the AVR.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2015-08-29
 * @copyright
 * {
 *     Copyright 2015 Liam Bucci
 *
 *     Licensed under the Apache License, Version 2.0 (the "License");
 *     you may not use this file except in compliance with the License.
 *     You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 * }
 */

#include <stddef.h>
#include <stdint.h>

#include "spi.h"
#include "tlc591x.h"

/**
 * @brief Initialize the TLC591x internals and hardware.
 *
 * Assumes SPI driver and pin drivers have already been initialized and are ready to use.
 *
 * @param[in] tlc
 *            A pointer to the TLC591x driver to initialize.
 * @return A boolean:
 *         - `true`:  The driver was successfully initialized.
 *         - `false`: The driver initialization failed.
 */
bool tlc591x_init( tlc591x_t * const tlc )
{
    bool success = false;

    if( tlc != NULL )
    {
        /* Ensure driver internals are valid */
        if( (tlc->spi == NULL) || (tlc->le == NULL) || (tlc->n_oe == NULL) )
        {
            /* Initialize LE pin */
            pin_set_direction( tlc->le, PIN_DIRECTION_OUTPUT );
            pin_deassert( tlc->le );

            /* Initialize nOE pin */
            pin_set_direction( tlc->n_oe, PIN_DIRECTION_OUTPUT );
            pin_deassert( tlc->n_oe );

            success = true;
        }
    }

    return success;
}

bool tlc591x_enable_output( tlc591x_t * const tlc )
{
    bool success = false;

    if( tlc != NULL )
    {
        pin_assert( tlc->n_oe );
        success = true;
    }

    return success;
}

bool tlc591x_disable_output( tlc591x_t * const tlc )
{
    bool success = false;

    if( tlc != NULL )
    {
        pin_deassert( tlc->n_oe );
        success = true;
    }

    return success;
}

bool tlc591x_write_values( tlc591x_t * const tlc, const uint8_t values )
{
    bool success = false;

    if( tlc != NULL )
    {
        success = spi_write( tlc->spi, &values, 1 );

        if( success == true )
        {
            pin_assert( tlc->le );
            pin_deassert( tlc->le );
        }
    }

    return success;
}