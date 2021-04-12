	.arch msp430g2553
	.p2align 1,0
	.text

	.global buzzer_setter_assembly

	buzzer_init_assembly
	:
	call #buzzer_init
