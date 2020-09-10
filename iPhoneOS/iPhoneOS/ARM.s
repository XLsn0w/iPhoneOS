
.text
.global _test

_test:

; mov指令  注释用;
mov x0, #0x8

ret


__asm关键字启动内联汇编并且能写在任何C++合法语句之处。它不能单独出现，必须接汇编指令、一组被大括号包含的指令或一对空括号。

术语“__asm 块”在这里是任意一个指令或一组指令无论是否在括号内。

以下代码片段是在括号内的一个简单的__asm块。
__asm　{　mov al, 2 　mov dx, 0xD007　out al, dx　}
另一种方法是，你可以在每个汇编指令前放置__asm
__asm mov al, 2
__asm mov dx, 0xD007
__asm out al, dx
因为__asm关键字是一个语句分隔符，你也可以将汇编指令放在同一行：
__asm mov al, 2 __asm mov dx, 0xD007 __asm out al, dx
