/* Copyright 2022, Laboratorio de Microprocesadores
 * Facultad de Ciencias Exactas y Tecnología
 * Universidad Nacional de Tucuman
 * http://www.microprocesadores.unt.edu.ar/
 * Copyright 2023, Rosales Facundo Ezequiel <facundoerosales@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** \brief Implementacion de HAL y BSP
 **
 ** \addtogroup main MAIN
 ** \brief Gestion de entradas y salidas digitales
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "bspciaa.h"
#include "chip.h"
#include "reloj.h"
#include <digital.h>
#include <stdbool.h>
#include <stddef.h>

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */
typedef enum {
    SIN_CONFIGURAR,
    MOSTRANDO_HORA,
    AJUSTANDO_MINUTOS_ACTUAL,
    AJUSTANDO_HORAS_ACTUAL,
    AJUSTANDO_MINUTOS_ALARMA,
    AJUSTANDO_HORAS_ALARMA,
} modo_t;

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

void ActivarAlarma(bool reloj);

/* === Public variable definitions ============================================================= */

static board_t board;
static clock_t reloj;

static modo_t modo;

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */
void ActivarAlarma(bool reloj) {
}

/* === Public function implementation ========================================================= */

int main(void) {

    reloj = ClockCreate(1000, ActivarAlarma);

    board = BoardCreate();

    modo = SIN_CONFIGURAR;

    SisTick_Init(1000);
    DisplayFlashDigits(board->display, 0, 3, 200);

    // DisplayWriteBCD(board->display, (uint8_t[]){1, 2, 3, 4}, 4);
    // DisplayToggleDot(board->display, 1);

    while (true) {
        if (DigitalInputHasActivated(board->accept)) {
            // DisplayFlashDigits(board->display, 0, 1, 0);
        }

        if (DigitalInputHasActivated(board->cancel)) {
            // DisplayFlashDigits(board->display, 0, 1, 100);
        }

        if (DigitalInputHasActivated(board->set_time)) {
        }

        if (DigitalInputHasActivated(board->set_alarm)) {
        }

        if (DigitalInputHasActivated(board->decrement)) {
        }

        if (DigitalInputHasActivated(board->increment)) {
        }

        // DisplayRefresh(board->display);

        for (int index = 0; index < 100; index++) {
            for (int delay = 0; delay < 200; delay++) {
                __asm("NOP");
            }
        }

        /*ClockGetTime(reloj, hora, sizeof(hora));
        __asm volatile("cpsid i");
        DisplayWriteBCD(board->display, hora, sizeof(hora));
        __asm volatile("cpsie i");*/
    }
}

void SysTick_Handler(void) {
    static bool last_value = false;
    bool current_value;
    uint8_t hora[6];

    DisplayRefresh(board->display);
    current_value = ClockUpdate(reloj);

    if (current_value != last_value) {
        last_value = current_value;

        if (modo <= MOSTRANDO_HORA) {
            ClockGetTime(reloj, hora, sizeof(hora));
            DisplayWriteBCD(board->display, hora, sizeof(hora));
            DisplayToggleDot(board->display, 1);
        }
    };
}
/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
