/*cortex-m3 
AUTHOR : hady abdelhady
*/
.section .vectors
.word 0x20001000
.word _reset
.word vector_handler /*nmi*/
.word vector_handler /*hw fault*/
.word vector_handler /*memory management fault*/
.word vector_handler /*bus fault*/
.word vector_handler /*usage fault*/
.word vector_handler /*reserved*/
.word vector_handler /*sv_call*/
.word vector_handler /*debug monitor*/
.word vector_handler /*reserved*/
.word vector_handler /*pendsv*/
.word vector_handler /*systick*/
.word vector_handler /*wwdg*/
.word vector_handler /*pvd*/
.word vector_handler /*tamper*/
.word vector_handler /*RTC*/
.word vector_handler /*flash*/
.word vector_handler /*RCC*/
.word vector_handler /*EXTI0*/
.word vector_handler /*EXTI1*/
.word vector_handler /*EXTI2*/

.section .text
_reset:
	bl main 
	b .
	
.thumb_func	
vector_handler:
	b _reset	