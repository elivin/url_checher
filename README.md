# url_checher - Пример расширения для php

Попробую описать небольшой пример расширения для php на языке C. В данном примере будут рассмотрены:
- базовая обёртка;
- добавление функции;
- обработка параметров;
- подключение сторонних библиотек.

## Для чего написан данный пример

Документации по расширениям php на русском не так много, да и на английском большинство ссылок, которые мне попадались, вели на 404 страницу. Значительная часть тех, что открывались, описывали разработку расширений через различные инструменты.
В данном примере мы будем определять статусы страниц. Параллельно. С использованием сторонних библиотек.

## Что понадобится

Я работаю исключительно с Linux (у меня Debian jessie), так что другие ОС, увы, не рассматриваю. Если Вы собрались писать расширение для php, полагаю, сам php уже устанослен. Я проверял пример только на php5.6, но думаю, он без проблем должен завестись на всей ветке php5 (с 5.3 то точно). Кроме интерпретатора потребуются библиотеки для разработки. В Debian для их установки достаточно установить пакет php-dev.
Маловероятно, но может потребуется установить gcc. Скорее всего он потянеятся в качестве зависимости при установке php-dev.
Собственно, минимальный набор готов. Текстовый редактор/IDE на свой вкус.

## Стадии сборки

Проект может располагаться налюбом месте на диске. 
>phpize

>./configure

>make

>sudo make install
