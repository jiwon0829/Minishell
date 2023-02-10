!?after dup2 fd[ret]: 1 ,dup2 fd[0]: 13 
redirec dup2 while 1
str :w
fd> : 14
!?after dup2 fd[ret]: -1 ,dup2 fd[0]: 14 
----finish redir_dup----
-----cur redir_list----
(0	13)
(0	14)
----------
--------
>>>>>last set redir fd<<<<<
0 13
------------------------------
---in runprogram---
----in redir_dup----
-----cur redir_list----
----------
--------redir NULL
-----cur redir_list----
----------
--------
>>>>>last set redir fd<<<<<
------------------------------
---in runprogram---
Makefile
a
a.out
b
bb
c
d
f
g
include
libft
minishell
o
p
ppo.c
q
qq
src
w
!?after_append dup2 fd[ret]: 1 ,dup2 fd[0]: 5 
redirec dup2 while 1
str :w
fd>> : 6
!?after_append dup2 fd[ret]: -1 ,dup2 fd[0]: 6 
----finish redir_dup----
-----cur redir_list----
(0	5)
(0	6)
----------
--------
>>>>>last set redir fd<<<<<
0 5
------------------------------
---in runprogram---
----in redir_dup----
-----cur redir_list----
----------
--------redir NULL
-----cur redir_list----
----------
--------
>>>>>last set redir fd<<<<<
------------------------------
---in runprogram---
Makefile
a
a.out
b
bb
c
d
f
g
include
libft
minishell
o
p
ppo.c
q
qq
src
w
!?after_append dup2 fd[ret]: 1 ,dup2 fd[0]: 9 
redirec dup2 while 1
str :w
fd>> : 10
!?after_append dup2 fd[ret]: -1 ,dup2 fd[0]: 10 
----finish redir_dup----
-----cur redir_list----
(0	9)
(0	10)
----------
--------
>>>>>last set redir fd<<<<<
0 9
------------------------------
---in runprogram---
----in redir_dup----
-----cur redir_list----
----------
--------redir NULL
-----cur redir_list----
----------
--------
>>>>>last set redir fd<<<<<
------------------------------
---in runprogram---
Makefile
a
a.out
b
bb
c
d
f
g
include
libft
minishell
o
p
ppo.c
q
qq
src
w
!?after_append dup2 fd[ret]: 1 ,dup2 fd[0]: 13 
redirec dup2 while 1
str :w
fd>> : 14
!?after_append dup2 fd[ret]: -1 ,dup2 fd[0]: 14 
----finish redir_dup----
-----cur redir_list----
(0	13)
(0	14)
----------
--------
>>>>>last set redir fd<<<<<
0 13
------------------------------
---in runprogram---
----in redir_dup----
-----cur redir_list----
----------
--------redir NULL
-----cur redir_list----
----------
--------
>>>>>last set redir fd<<<<<
------------------------------
---in runprogram---
Makefile
a
a.out
b
bb
c
d
f
g
include
libft
minishell
o
p
ppo.c
q
qq
src
w
