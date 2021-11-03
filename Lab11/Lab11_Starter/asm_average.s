.syntax unified
.text
.align 2
.global asm_average

/* C Declaration                                             */
/* extern uint32_t asm_average(uint32_t Q, uint32_t* input); */

asm_average:
    /*
        On entry:
        Q       r0 (1-16) // ln2(count)
        input   r1        // address of array containing count 32-bit unsigned integers
    */
    push    {r4-r7, lr}

    /* TODO - put the result into r0 */

    movs r5, #1 // Assign 1 to r1
    lsls r5, r0 // n value (Left shift 1-bit to the left 7)

    movs r7, #128 // Loading number a values in array to r3
    movs r6, #0 // Array index
    loop:
        subs r7, #1 // Subtracts 1 from number of values in array
        str r1, [r3,r6]  // store the value in the array r1 to register r3
        adds r6, #4 // Add 1 to array index
        add r4, r3 // Add store value to r4 (Sum value)
        cmp r7, #0 // Compares to 0 (Complete iteration through values array)
        bne loop

    // lsrs r4, r0 // divide
    movs r0, r4

    pop {r4-r7, pc}

