;;# ndisasm -b 64 -p intel -e 64 -k 482,12288 test.o
00000000  55                push rbp
00000001  4889E5            mov rbp,rsp
00000004  4883EC20          sub rsp,byte +0x20
00000008  897DEC            mov [rbp-0x14],edi
0000000B  90                nop
0000000C  90                nop
0000000D  90                nop
0000000E  90                nop
0000000F  90                nop
00000010  8B45EC            mov eax,[rbp-0x14]
00000013  8945FC            mov [rbp-0x4],eax
00000016  C745F800000000    mov dword [rbp-0x8],0x0
0000001D  90                nop
0000001E  90                nop
0000001F  90                nop
00000020  90                nop
00000021  90                nop
00000022  837DF802          cmp dword [rbp-0x8],byte +0x2
00000026  7F0F              jg 0x37
00000028  90                nop
00000029  90                nop
0000002A  90                nop
0000002B  90                nop
0000002C  90                nop
0000002D  8345FC01          add dword [rbp-0x4],byte +0x1
00000031  8345F801          add dword [rbp-0x8],byte +0x1
00000035  EBE6              jmp short 0x1d
00000037  90                nop
00000038  90                nop
00000039  90                nop
0000003A  90                nop
0000003B  90                nop
0000003C  837DFC05          cmp dword [rbp-0x4],byte +0x5
00000040  7E0A              jng 0x4c
00000042  90                nop
00000043  90                nop
00000044  90                nop
00000045  90                nop
00000046  90                nop
00000047  8B45FC            mov eax,[rbp-0x4]
0000004A  EB13              jmp short 0x5f
0000004C  90                nop
0000004D  90                nop
0000004E  90                nop
0000004F  90                nop
00000050  90                nop
00000051  E800000000        call qword 0x56
00000056  8945FC            mov [rbp-0x4],eax
00000059  8B45FC            mov eax,[rbp-0x4]
0000005C  83C004            add eax,byte +0x4
0000005F  90                nop
00000060  90                nop
00000061  90                nop
00000062  90                nop
00000063  90                nop
00000064  C9                leave
00000065  C3                ret
00000066  55                push rbp
00000067  4889E5            mov rbp,rsp
0000006A  897DFC            mov [rbp-0x4],edi
0000006D  90                nop
0000006E  90                nop
0000006F  90                nop
00000070  90                nop
00000071  90                nop
00000072  90                nop
00000073  8B45FC            mov eax,[rbp-0x4]
00000076  83C001            add eax,byte +0x1
00000079  90                nop
0000007A  90                nop
0000007B  90                nop
0000007C  90                nop
0000007D  90                nop
0000007E  5D                pop rbp
0000007F  C3                ret
00000080  55                push rbp
00000081  4889E5            mov rbp,rsp
00000084  4883EC20          sub rsp,byte +0x20
00000088  897DEC            mov [rbp-0x14],edi
0000008B  90                nop
0000008C  90                nop
0000008D  90                nop
0000008E  90                nop
0000008F  90                nop
00000090  C745FC00000000    mov dword [rbp-0x4],0x0
00000097  90                nop
00000098  90                nop
00000099  90                nop
0000009A  90                nop
0000009B  90                nop
0000009C  8B45FC            mov eax,[rbp-0x4]
0000009F  3B45EC            cmp eax,[rbp-0x14]
000000A2  7D1F              jnl 0xc3
000000A4  90                nop
000000A5  90                nop
000000A6  90                nop
000000A7  90                nop
000000A8  90                nop
000000A9  8B45FC            mov eax,[rbp-0x4]
000000AC  89C6              mov esi,eax
000000AE  BF00000000        mov edi,0x0
000000B3  B800000000        mov eax,0x0
000000B8  E800000000        call qword 0xbd
000000BD  8345FC01          add dword [rbp-0x4],byte +0x1
000000C1  EBD4              jmp short 0x97
000000C3  90                nop
000000C4  90                nop
000000C5  90                nop
000000C6  90                nop
000000C7  90                nop
000000C8  90                nop
000000C9  C9                leave
000000CA  C3                ret
000000CB  55                push rbp
000000CC  4889E5            mov rbp,rsp
000000CF  4883EC10          sub rsp,byte +0x10
000000D3  897DFC            mov [rbp-0x4],edi
000000D6  90                nop
000000D7  90                nop
000000D8  90                nop
000000D9  90                nop
000000DA  90                nop
000000DB  837DFC00          cmp dword [rbp-0x4],byte +0x0
000000DF  7411              jz 0xf2
000000E1  90                nop
000000E2  90                nop
000000E3  90                nop
000000E4  90                nop
000000E5  90                nop
000000E6  8B45FC            mov eax,[rbp-0x4]
000000E9  89C7              mov edi,eax
000000EB  E800000000        call qword 0xf0
000000F0  EB0F              jmp short 0x101
000000F2  90                nop
000000F3  90                nop
000000F4  90                nop
000000F5  90                nop
000000F6  90                nop
000000F7  8B45FC            mov eax,[rbp-0x4]
000000FA  89C7              mov edi,eax
000000FC  E800000000        call qword 0x101
00000101  90                nop
00000102  90                nop
00000103  90                nop
00000104  90                nop
00000105  90                nop
00000106  90                nop
00000107  C9                leave
00000108  C3                ret
00000109  55                push rbp
0000010A  4889E5            mov rbp,rsp
0000010D  4883EC20          sub rsp,byte +0x20
00000111  897DEC            mov [rbp-0x14],edi
00000114  488975E0          mov [rbp-0x20],rsi
00000118  90                nop
00000119  90                nop
0000011A  90                nop
0000011B  90                nop
0000011C  90                nop
0000011D  C745FC00000000    mov dword [rbp-0x4],0x0
00000124  C745F800000000    mov dword [rbp-0x8],0x0
0000012B  837DEC01          cmp dword [rbp-0x14],byte +0x1
0000012F  7F0F              jg 0x140
00000131  90                nop
00000132  90                nop
00000133  90                nop
00000134  90                nop
00000135  90                nop
00000136  B8FFFFFFFF        mov eax,0xffffffff
0000013B  E99B000000        jmp qword 0x1db
00000140  90                nop
00000141  90                nop
00000142  90                nop
00000143  90                nop
00000144  90                nop
00000145  488B45E0          mov rax,[rbp-0x20]
00000149  4883C008          add rax,byte +0x8
0000014D  488B00            mov rax,[rax]
00000150  4889C7            mov rdi,rax
00000153  E800000000        call qword 0x158
00000158  8945FC            mov [rbp-0x4],eax
0000015B  C745F400000000    mov dword [rbp-0xc],0x0
00000162  90                nop
00000163  90                nop
00000164  90                nop
00000165  90                nop
00000166  90                nop
00000167  837DF402          cmp dword [rbp-0xc],byte +0x2
0000016B  7F0F              jg 0x17c
0000016D  90                nop
0000016E  90                nop
0000016F  90                nop
00000170  90                nop
00000171  90                nop
00000172  8345FC01          add dword [rbp-0x4],byte +0x1
00000176  8345F401          add dword [rbp-0xc],byte +0x1
0000017A  EBE6              jmp short 0x162
0000017C  90                nop
0000017D  90                nop
0000017E  90                nop
0000017F  90                nop
00000180  90                nop
00000181  837DFC04          cmp dword [rbp-0x4],byte +0x4
00000185  7F12              jg 0x199
00000187  90                nop
00000188  90                nop
00000189  90                nop
0000018A  90                nop
0000018B  90                nop
0000018C  8B45FC            mov eax,[rbp-0x4]
0000018F  89C7              mov edi,eax
00000191  E800000000        call qword 0x196
00000196  8945F8            mov [rbp-0x8],eax
00000199  90                nop
0000019A  90                nop
0000019B  90                nop
0000019C  90                nop
0000019D  90                nop
0000019E  8B45FC            mov eax,[rbp-0x4]
000001A1  83F808            cmp eax,byte +0x8
000001A4  7407              jz 0x1ad
000001A6  83F80C            cmp eax,byte +0xc
000001A9  740F              jz 0x1ba
000001AB  EB18              jmp short 0x1c5
000001AD  90                nop
000001AE  90                nop
000001AF  90                nop
000001B0  90                nop
000001B1  90                nop
000001B2  8B45F8            mov eax,[rbp-0x8]
000001B5  0145FC            add [rbp-0x4],eax
000001B8  EB19              jmp short 0x1d3
000001BA  90                nop
000001BB  90                nop
000001BC  90                nop
000001BD  90                nop
000001BE  90                nop
000001BF  8345FC64          add dword [rbp-0x4],byte +0x64
000001C3  EB0E              jmp short 0x1d3
000001C5  90                nop
000001C6  90                nop
000001C7  90                nop
000001C8  90                nop
000001C9  90                nop
000001CA  8B45F8            mov eax,[rbp-0x8]
000001CD  83C032            add eax,byte +0x32
000001D0  0145FC            add [rbp-0x4],eax
000001D3  90                nop
000001D4  90                nop
000001D5  90                nop
000001D6  90                nop
000001D7  90                nop
000001D8  8B45FC            mov eax,[rbp-0x4]
000001DB  90                nop
000001DC  90                nop
000001DD  90                nop
000001DE  90                nop
000001DF  90                nop
000001E0  C9                leave
000001E1  C3                ret
000001E2  skipping 0x3000 bytes
