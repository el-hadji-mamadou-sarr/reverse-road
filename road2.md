Compréhension :

Dans quelle section ELF trouves-tu la string "Result: %d\n" de ton programme ? Pourquoi ?
- On le trouve dans la section .rodata

Explique en tes propres mots ce qui se passe exactement sur la pile lors d'un call — avant même que la première instruction de la fonction appelée s'exécute.
- lors d'un call, push l'adresse de retour sur la pile et saute à l'adresse suivante

Si une fonction prend 8 arguments, comment sont passés les 2 derniers selon la convention x86-64 ?
- push arg8 et push arg7

Tu vois dans un binaire inconnu que la PLT contient des entrées pour CreateFile, WriteFile, RegOpenKey. Qu'est-ce que cela t'indique sur le comportement probable du programme ?
- ce programme va surement manipuler le registre de windows et d'écrire sur un fichier oubien de créer un fichier.

La pile grandit vers les basses adresses. Si un attaquant peut écrire plus de données qu'un buffer local ne peut en contenir, que se passe-t-il sur la pile ? (c'est une intro au concept de buffer overflow — réfléchis sans chercher)
- on écrase l'adresse de retour. et l'attanquant pourra mettre son propres adresse.

Questions sur le code désassemblé :
a) Dans le désassemblage de greet, combien d'octets sont réservés sur la pile (sub $X, %rsp) ? Est-ce cohérent avec char buffer[32] ?
- l'assembleur réserve 48 bytes (sub  $0x30,%rsp) alors que dans le code, on a un buffer de 32 bytes de charactéres. c'est normal puiqu'on réserve pas exactement ce que l'on veux, on ajoute une marge pour les overheads afin d'éviter le buffer overflow.

b) Identifie les instructions qui correspondent au passage des arguments à snprintf. Combien d'arguments a snprintf ? Comment sont-ils passés ?
- il prend 5 arguments. 
    1175:       48 89 7d d8             mov    %rdi,-0x28(%rbp) -> rdi
    1179:       89 75 d4                mov    %esi,-0x2c(%rbp) -> rsi
    117c:       8b 4d d4                mov    -0x2c(%rbp),%ecx -> rdx
    117f:       48 8b 55 d8             mov    -0x28(%rbp),%rdx -> rcx
    1183:       48 8d 45 e0             lea    -0x20(%rbp),%rax 
    1187:       41 89 c8                mov    %ecx,%r8d -> r8

c) Repère le prologue et l'épilogue de greet et explique ce que fait chaque instruction.
- prologue
    116d:       55                      push   %rbp  #mettre rbp dans la pile
    116e:       48 89 e5                mov    %rsp,%rbp #pointer rbp sur rsp
    1171:       48 83 ec 30             sub    $0x30,%rsp # réserver 48 bytes dans la pile

- épilogue
    11b3:       c9                      leave #enlever rbp de la pile et dépiler rsp
    11b4:       c3                      ret #dépiler l'adresse de retour

Bonus : Lance readelf -S cours2 sans grep et identifie la section .rodata. Utilise objdump -s -j .rodata cours2 pour voir son contenu — tu devrais voir la format string. Explique ce que tu vois.