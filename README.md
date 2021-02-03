# Работа с библиотекой

## Начало работы

## Функции и типы данных библиотеки LibTomMath

## Теоретическая вставка

## Параметры и алгоритм возведения в степень

Параметры для эллиптической кривой в искривленной/скрученной форме Эдвардса:  (см. ГОСТ Р 34.10-2012: https://docplayer.ru/46408167-Tehnicheskiy-komitet-026-zadanie-parametrov-skruchennyh-ellipticheskih-krivyh-edvardsa-v-sootvetstvii-s-gost-r.html)

- *p* – характеристика простого поля, над которым определяется эллиптическая кривая.

- *a, d* – коэффициенты эквивалентной скрученной эллиптической кривой в форме Эдвардса.

- *q* – порядок подгруппы простого порядка группы точек эллиптической кривой.

- *u, v* – координаты точки P при эквивалентном представлении в форме скрученной кривой Эдвардса.

При выполнении работы был взят следующий набор параметров (в десятичной системе счисления) id-tc26-gost-3410-2012-256-paramSet A.

Для вычисления кратной точки использовался двоичный алгоритм (лекции, слайд №53):

![Альтернативный текст](https://sun9-55.userapi.com/impg/FP1xfw8FyxH9f4O_lksAeYb0i2BQoGc_YIIAoQ/qYZdzM3iGvE.jpg?size=1044x330&quality=96&proxy=1&sign=55ad5f421327d6a88534916ca54c439b&type=album)

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
- ```void IfIdentical``` - Функция проверяет условие: *[q]P  =  (0,1,0)*. При выполнении условия выводит “Yes”, иначе – “No”. 
- ```void IfNeighbors``` - Функция проверяет условия: *[q + 1]P = P*   и   *[q − 1]P = −P*. При выполнении первого выводит “Yes”, иначе – “No”. Аналогично для второго. Для корректной работы функции требуется предварительная подготовка, равно как и для проведения четвертого теста.

Четвертый тест реализован "вручную" (условия теста успешно выполняется: *[q + 1]P = P   и   [q − 1]P = −P* ) из-за возникающих проблем с сегментацией при многократном вызове функции BinaryMethod с одними параметрами. Результаты тестирования приведены далее.



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
