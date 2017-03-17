;;# ndisasm -b 64 -p intel -e 64 -k 347,5000 test.o
00000000  55                push rbp
00000001  4889E5            mov rbp,rsp
00000004  897DEC            mov [rbp-0x14],edi
00000007  90                nop
00000008  90                nop
00000009  90                nop
0000000A  90                nop
0000000B  90                nop
0000000C  90                nop
0000000D  90                nop
0000000E  8B45EC            mov eax,[rbp-0x14]
00000011  8945F8            mov [rbp-0x8],eax
00000014  C745FC00000000    mov dword [rbp-0x4],0x0
0000001B  90                nop
0000001C  90                nop
0000001D  90                nop
0000001E  90                nop
0000001F  90                nop
00000020  90                nop
00000021  90                nop
00000022  837DFC02          cmp dword [rbp-0x4],byte +0x2
00000026  7F11              jg 0x39
00000028  90                nop
00000029  90                nop
0000002A  90                nop
0000002B  90                nop
0000002C  90                nop
0000002D  90                nop
0000002E  90                nop
0000002F  8345F801          add dword [rbp-0x8],byte +0x1
00000033  8345FC01          add dword [rbp-0x4],byte +0x1
00000037  EBE2              jmp short 0x1b
00000039  90                nop
0000003A  90                nop
0000003B  90                nop
0000003C  90                nop
0000003D  90                nop
0000003E  90                nop
0000003F  90                nop
00000040  837DF805          cmp dword [rbp-0x8],byte +0x5
00000044  7E0C              jng 0x52
00000046  90                nop
00000047  90                nop
00000048  90                nop
00000049  90                nop
0000004A  90                nop
0000004B  90                nop
0000004C  90                nop
0000004D  8B45F8            mov eax,[rbp-0x8]
00000050  EB0D              jmp short 0x5f
00000052  90                nop
00000053  90                nop
00000054  90                nop
00000055  90                nop
00000056  90                nop
00000057  90                nop
00000058  90                nop
00000059  8B45F8            mov eax,[rbp-0x8]
0000005C  83C004            add eax,byte +0x4
0000005F  90                nop
00000060  90                nop
00000061  90                nop
00000062  90                nop
00000063  90                nop
00000064  90                nop
00000065  90                nop
00000066  5D                pop rbp
00000067  C3                ret
00000068  55                push rbp
00000069  4889E5            mov rbp,rsp
0000006C  4883EC20          sub rsp,byte +0x20
00000070  897DEC            mov [rbp-0x14],edi
00000073  488975E0          mov [rbp-0x20],rsi
00000077  90                nop
00000078  90                nop
00000079  90                nop
0000007A  90                nop
0000007B  90                nop
0000007C  90                nop
0000007D  90                nop
0000007E  C745F400000000    mov dword [rbp-0xc],0x0
00000085  C745F800000000    mov dword [rbp-0x8],0x0
0000008C  837DEC01          cmp dword [rbp-0x14],byte +0x1
00000090  7F11              jg 0xa3
00000092  90                nop
00000093  90                nop
00000094  90                nop
00000095  90                nop
00000096  90                nop
00000097  90                nop
00000098  90                nop
00000099  B8FFFFFFFF        mov eax,0xffffffff
0000009E  E9AF000000        jmp qword 0x152
000000A3  90                nop
000000A4  90                nop
000000A5  90                nop
000000A6  90                nop
000000A7  90                nop
000000A8  90                nop
000000A9  90                nop
000000AA  488B45E0          mov rax,[rbp-0x20]
000000AE  4883C008          add rax,byte +0x8
000000B2  488B00            mov rax,[rax]
000000B5  4889C7            mov rdi,rax
000000B8  E800000000        call qword 0xbd
000000BD  8945F4            mov [rbp-0xc],eax
000000C0  C745FC00000000    mov dword [rbp-0x4],0x0
000000C7  90                nop
000000C8  90                nop
000000C9  90                nop
000000CA  90                nop
000000CB  90                nop
000000CC  90                nop
000000CD  90                nop
000000CE  837DFC02          cmp dword [rbp-0x4],byte +0x2
000000D2  7F11              jg 0xe5
000000D4  90                nop
000000D5  90                nop
000000D6  90                nop
000000D7  90                nop
000000D8  90                nop
000000D9  90                nop
000000DA  90                nop
000000DB  8345F401          add dword [rbp-0xc],byte +0x1
000000DF  8345FC01          add dword [rbp-0x4],byte +0x1
000000E3  EBE2              jmp short 0xc7
000000E5  90                nop
000000E6  90                nop
000000E7  90                nop
000000E8  90                nop
000000E9  90                nop
000000EA  90                nop
000000EB  90                nop
000000EC  837DF404          cmp dword [rbp-0xc],byte +0x4
000000F0  7F14              jg 0x106
000000F2  90                nop
000000F3  90                nop
000000F4  90                nop
000000F5  90                nop
000000F6  90                nop
000000F7  90                nop
000000F8  90                nop
000000F9  8B45F4            mov eax,[rbp-0xc]
000000FC  89C7              mov edi,eax
000000FE  E800000000        call qword 0x103
00000103  8945F8            mov [rbp-0x8],eax
00000106  90                nop
00000107  90                nop
00000108  90                nop
00000109  90                nop
0000010A  90                nop
0000010B  90                nop
0000010C  90                nop
0000010D  8B45F4            mov eax,[rbp-0xc]
00000110  83F808            cmp eax,byte +0x8
00000113  7407              jz 0x11c
00000115  83F80C            cmp eax,byte +0xc
00000118  7411              jz 0x12b
0000011A  EB1C              jmp short 0x138
0000011C  90                nop
0000011D  90                nop
0000011E  90                nop
0000011F  90                nop
00000120  90                nop
00000121  90                nop
00000122  90                nop
00000123  8B45F8            mov eax,[rbp-0x8]
00000126  0145F4            add [rbp-0xc],eax
00000129  EB1D              jmp short 0x148
0000012B  90                nop
0000012C  90                nop
0000012D  90                nop
0000012E  90                nop
0000012F  90                nop
00000130  90                nop
00000131  90                nop
00000132  8345F464          add dword [rbp-0xc],byte +0x64
00000136  EB10              jmp short 0x148
00000138  90                nop
00000139  90                nop
0000013A  90                nop
0000013B  90                nop
0000013C  90                nop
0000013D  90                nop
0000013E  90                nop
0000013F  8B45F8            mov eax,[rbp-0x8]
00000142  83C032            add eax,byte +0x32
00000145  0145F4            add [rbp-0xc],eax
00000148  90                nop
00000149  90                nop
0000014A  90                nop
0000014B  90                nop
0000014C  90                nop
0000014D  90                nop
0000014E  90                nop
0000014F  8B45F4            mov eax,[rbp-0xc]
00000152  90                nop
00000153  90                nop
00000154  90                nop
00000155  90                nop
00000156  90                nop
00000157  90                nop
00000158  90                nop
00000159  C9                leave
0000015A  C3                ret
0000015B  skipping 0x1388 bytes
