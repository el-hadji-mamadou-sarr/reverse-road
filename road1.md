Quelle est la différence entre un désassembleur et un décompilateur ?
- un déassembleur permet de convertir du binaire en assembleur avec des instructiions. le décompilateur permet de convertir un code assembleur en pseudo code du language de base utilisé pour produire ce t assembleur.

Cite deux cas d'usage légitimes du reverse engineering.
- le CTF (capture the flag) pour la compétition et le challenge et la sécurité offensive pour essayer de trouver des vulnérabilités sur un logiciel.

Qu'est-ce qu'un registre dans le contexte du CPU ? À quoi sert rsp spécifiquement ?
- le registre sert à stocker des variables qui vont étre utilisé par le CPU. ces varibales qui se trouve déja dans la RAM sont déplacés dans le registre puisqu'il est plus rapide en terme d'accessibilité.
- le registre stack pointeur permet de stocker les addresses de retour des fonctions, des variables locales etc

Quelle est la différence fondamentale entre analyse statique et analyse dynamique ? Dans quel cas préfères-tu l'une ou l'autre ?
- l'analyse statique permet d'analyser le code assembleur oubien le pseudo code pour connaitre le fonctionnement du programme
- l'analyse dynamique permet d'éxécuter le programmer et d'utiliser un debogger et des breakpoint pour comprendre le fonctionnement du programme. Je préfére l'analyse statique si le programme est malveillant et qui nuire à mon systéme qui je dois l'exécuter et j'utilise l'analyse dynamique si le programme est trés complexe à analyser statiquement. si il se trouve malveillant il faudrait le lancer dans une VM 

Si tu analyses un malware, pourquoi est-il dangereux de commencer directement par l'analyse dynamique sans précautions ?
- comme dit précédemment pour analyser un malware l'analyse dynamique n'est pas une bonne idée, il serait mieux de l'exécuter dans un laboratoire (VM)


## Etape 2
La sortie de file my_binary
prog_bin: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=84c26e81a0c10d02680d7ec67470b2c49f17120a, for GNU/Linux 3.2.0, not stripped

- c'est un fichier ELF donc un éxécutable sur linux

Les strings intéressantes trouvées
- j'ai trouvé printf, distribution de linux, Result: %d donc le résultat est un entier

La sortie désassemblée de main (copie/colle le output de objdump)
elhadji@elhadji:~/workspace/reverse-plan$ objdump -d prog_bin | grep -A 30 "<main>"
    1078:       48 8d 3d e2 00 00 00    lea    0xe2(%rip),%rdi        # 1161 <main>
    107f:       ff 15 53 2f 00 00       call   *0x2f53(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
    1085:       f4                      hlt
    1086:       66 2e 0f 1f 84 00 00    cs nopw 0x0(%rax,%rax,1)
    108d:       00 00 00 

0000000000001090 <deregister_tm_clones>:
    1090:       48 8d 3d 79 2f 00 00    lea    0x2f79(%rip),%rdi        # 4010 <__TMC_END__>
    1097:       48 8d 05 72 2f 00 00    lea    0x2f72(%rip),%rax        # 4010 <__TMC_END__>
    109e:       48 39 f8                cmp    %rdi,%rax
    10a1:       74 15                   je     10b8 <deregister_tm_clones+0x28>
    10a3:       48 8b 05 36 2f 00 00    mov    0x2f36(%rip),%rax        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    10aa:       48 85 c0                test   %rax,%rax
    10ad:       74 09                   je     10b8 <deregister_tm_clones+0x28>
    10af:       ff e0                   jmp    *%rax
    10b1:       0f 1f 80 00 00 00 00    nopl   0x0(%rax)
    10b8:       c3                      ret
    10b9:       0f 1f 80 00 00 00 00    nopl   0x0(%rax)

00000000000010c0 <register_tm_clones>:
    10c0:       48 8d 3d 49 2f 00 00    lea    0x2f49(%rip),%rdi        # 4010 <__TMC_END__>
    10c7:       48 8d 35 42 2f 00 00    lea    0x2f42(%rip),%rsi        # 4010 <__TMC_END__>
    10ce:       48 29 fe                sub    %rdi,%rsi
    10d1:       48 89 f0                mov    %rsi,%rax
    10d4:       48 c1 ee 3f             shr    $0x3f,%rsi
    10d8:       48 c1 f8 03             sar    $0x3,%rax
    10dc:       48 01 c6                add    %rax,%rsi
    10df:       48 d1 fe                sar    $1,%rsi
    10e2:       74 14                   je     10f8 <register_tm_clones+0x38>
    10e4:       48 8b 05 05 2f 00 00    mov    0x2f05(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    10eb:       48 85 c0                test   %rax,%rax
--
0000000000001161 <main>:
    1161:       f3 0f 1e fa             endbr64
    1165:       55                      push   %rbp
    1166:       48 89 e5                mov    %rsp,%rbp
    1169:       48 83 ec 10             sub    $0x10,%rsp
    116d:       be 04 00 00 00          mov    $0x4,%esi
    1172:       bf 03 00 00 00          mov    $0x3,%edi
    1177:       e8 cd ff ff ff          call   1149 <add>
    117c:       89 45 fc                mov    %eax,-0x4(%rbp)
    117f:       8b 45 fc                mov    -0x4(%rbp),%eax
    1182:       89 c6                   mov    %eax,%esi
    1184:       48 8d 05 79 0e 00 00    lea    0xe79(%rip),%rax        # 2004 <_IO_stdin_used+0x4>
    118b:       48 89 c7                mov    %rax,%rdi
    118e:       b8 00 00 00 00          mov    $0x0,%eax
    1193:       e8 b8 fe ff ff          call   1050 <printf@plt>
    1198:       b8 00 00 00 00          mov    $0x0,%eax
    119d:       c9                      leave
    119e:       c3                      ret

Disassembly of section .fini:

00000000000011a0 <_fini>:
    11a0:       f3 0f 1e fa             endbr64
    11a4:       48 83 ec 08             sub    $0x8,%rsp
    11a8:       48 83 c4 08             add    $0x8,%rsp
    11ac:       c3                      ret

Bonus : identifie dans l'assembleur l'instruction qui correspond à l'appel de add() et celle qui correspond à printf()
- pour la fonction add()
    1177:       e8 cd ff ff ff          call   1149 <add>

- pour le printf
    1193:       e8 b8 fe ff ff          call   1050 <printf@plt>