# Работа с библиотекой

## Начало работы

## Функции и типы данных библиотеки LibTomMath

## Теоретическая вставка

## Параметры и алгоритм возведения в степень

## Структуры и функции программы

- ``` struct Point ``` - структура для хранения координат точки.
- ``` struct Parameters ``` - структура для хранения исходных параметров эллиптической кривой в форме искривленной формы Эдвардса.
- ``` void ToText ``` - небольшая вспомогательная функция для вывода на экран числовых значений, хранящихся в mp_int.
- ``` void Transform ``` - функция переводит координаты точки в афинные координаты.
- ``` void AddPoints ``` - функция сложения двух точек P и Q.
- ```void DoublePoint ``` - функция удваивает точку P.
- ```struct Point BinaryMethod``` - функция вычисляет кратную точку; возвращает точку.

Функции тестирования:

- ```void IfOnCurve``` - функция выполняет проверку, лежит ли результирующая точка на кривой; выводит “Yes”, если точка лежит на кривой; иначе выводит “No”.
- ```void IfIdentical``` - Функция проверяет условие: *[q]P  =  (0,1,0);*



## Тестирование программы

## Источники

- Официальная документация библиотеки LibTomMath доступна по ссылке: https://docviewer.yandex.ru/view/158126255/?page=30&*=7xuiznXmFLC1blVp%2BowakWJzq357InVybCI6Imh0dHBzOi8vZ3RvYWwuY29tL3NyYy9tb2JpL2NsaXQxOC9saWJ0b21tYXRoLTAuNDEvYm4ucGRmIiwidGl0bGUiOiJibi5wZGYiLCJub2lmcmFtZSI6dHJ1ZSwidWlkIjoiMTU4MTI2MjU1IiwidHMiOjE2MDM2NTgzMTk5NjcsInl1IjoiNjQ5OTUwODY3MTU3MjI5ODkzOSIsInNlcnBQYXJhbXMiOiJsYW5nPWVuJnRtPTE2MDM0NjcwMDgmdGxkPXJ1Jm5hbWU9Ym4ucGRmJnRleHQ9bGlidG9tbWF0aCtkb2N1bWVudGF0aW9uJnVybD1odHRwcyUzQS8vZ3RvYWwuY29tL3NyYy9tb2JpL2NsaXQxOC9saWJ0b21tYXRoLTAuNDEvYm4ucGRmJmxyPTIxMyZtaW1lPXBkZiZsMTBuPXJ1JnNpZ249OTI2OTRkZGZkMmUyYTMyY2ZlOTkxOGUxNDMyYTAwNTcma2V5bm89MCJ9&lang=en
- Установка пакетов в Gentoo:
https://losst.ru/ustanovka-paketov-v-gentoo
- Р 1323565.1.024—2019:
https://files.stroyinf.ru/Data2/1/4293730/4293730019.pdf
- Twisted Edwards Curves - Daniel J. Bernstein1, Peter Birkner2, Marc Joye3, Tanja Lange2, and Christiane Peters2:
https://eprint.iacr.org/2008/013.pdf
- Лекции
