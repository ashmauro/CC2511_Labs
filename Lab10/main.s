/** 
 * CC2511 Lab 10
 */

/* Assembler directives */

.syntax unified /* Use modern syntax                                                    */
.text           /* The "text" section of the executable is where code is placed.        */
.thumb_func     /* Specifies that main is a thumb mode function and will be offset by 1 */ 
.global main    /* Declare "main" as a global symbol (callable from other files).       */
.align 4        /* Make sure the starting address is a multiple of 4.                   */

/* Definitions */
/* These are equivalent to C macros. However, note that they use a comma. */

.EQU LED_PIN,                 25
.EQU WAIT_LOOPS_ON,           10000000
.EQU WAIT_LOOPS_OFF,          10000000
.EQU REG_GPIO_OE_SET,         (0xd0000024)
.EQU GPIO_OUT_SET,            (0xd0000014)
.EQU GPIO_OUT_CLR,            (0xd0000018)
.EQU GPIO_PAD,                (0x4001c068)
.EQU GPIO_CTRL,               (0x400140cc)

/* TODO - Add definitions of register addresses used in the program */  

/* Main function */
main:
  push {lr}

    /* Function 5 */
    ldr r0, =GPIO_CTRL
    movs r1, #5
    str r1, [r0]

    /* Data direction */
    ldr r0, =REG_GPIO_OE_SET
    movs r1, #1
    movs r2, #25
    lsls r1, r2
    str r1, [r0]

    /* Turn off output and turn on input */
    ldr r0, = GPIO_PAD
    movs r1, #1
    lsls r2, r1, #6 /* Shift bit 1 left 6 bits */
    lsls r3, r1, #7 /* Shift bit 1 left 7 bits */
    mvns r3, r3     /* Inverse of ~(1<<7) */
    orrs r2, r3, r2 /* ~(1<<7) | (1<<6) */
    ands r0, r0, r2 /* CONTENT_OF(GPIO_PAD) & ~(1<<7) | (1<<6) */

   
   /* 'While loop' */
    ldr r0, =#100000000    /* ro = 10 */
   myloop:
        subs r0, #1  /* ro -= 1 */

             /* Turn LED on */
            ldr r1, =GPIO_OUT_SET
            movs r2, #1
            lsls r3, r2, #25
            str r3, [r1]

            /* Wait in an inner loop */
            ldr r4, =#10000000
            myloop2:
                subs r4, #1
            bne myloop2

            /* Turn LED off */
            ldr r1, =GPIO_OUT_CLR
            movs r2, #1
            lsls r3, r2, #25
            str r3, [r1]

             /* Wait in an inner loop */
            ldr r5, =#10000000
            myloop3:
                subs r5, #1
            bne myloop3
            
    cmp r0, #0
    b myloop

	pop {pc}  /* Return from this function, by popping the return address into the program counter (pc) */
