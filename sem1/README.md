# Компиляция

`gcc -m32 prog.S -o prog`

Для компиляции в некоторых 64битных системах необходимо поставить `gcc-multilib`, например:

`sudo apt-get install gcc-multilib`

Если несколько исходных файлов, в том числе может быть и simpleio - просто перечисляем все файлы

`gcc -m32 prog.S simpleio_i686.S -o prog`
