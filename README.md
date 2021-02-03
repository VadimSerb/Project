# Работа с библиотекой

## Цель работы

Цель работы заключается в программной реализации эллиптических кривых в искривлённой форме Эдвардса и арифметических операций над точкой в поле, с последующим тестированием для проверки корректности выполнения поставленной задачи. Для выполнения работы применяется библиотека LibTomMath.

## Начало работы

Работа с библиотекой происходила на ОС Gentoo (64-bit) в среде разработки QT Creator. 
Инсталляция и линковка библиотеки LibTomMath:
1. Загрузка архива библиотеки (https://www.libtom.net/), распаковка архива.
2. В командной строке в директории расположения файлов библиотеки: ```make -f makefile.shared```
3. В созданном *Non-Qt Project -> C* проекте в среде разработки QT Creator: *Add Library -> System library -> library file*
4. Теперь в main.c можно добавить заголовочный файл tommath.h и начать работу.

## Функции и типы данных библиотеки LibTomMath

- ```mp_int``` – основной тип, применяемый в библиотеке для хранения больших чисел.

- ```int mp_init``` - служит для инициализации одной переменной типа mp_int.
- ```int mp_init_multi``` - служит для множественной инициализации переменных типа mp_int.
- ```void mp_clear_multi``` - служит для очистки памяти.
- ```int mp_toradix(mp_int * a, char *str, int radix)``` - функция записывает числовое значение в переменную символьного типа в выбранной системе счисления. Используется в функции ```void ToText```.
- ```int mp_read_radix(mp_int * a, char *str, int radix)``` - функция “заносит” числовое значение, хранящееся в  строке в виде отдельных числовых символов в ```mp_int``` так, что с ```mp_int```, имеющим значение, можно производить различные операции.
- ```mp_mulmod(const mp_int *a, const mp_int *b, const mp_int *c, mp_int *d)``` - функция выполняет операцию: *d = a * b (mod c)*
- ```mp_addmod(const mp_int *a, const mp_int *b, const mp_int *c, mp_int *d)``` - функция выполняет операцию: *d = a + b (mod c)*
- ```mp_sqrmod(const mp_int *a, const mp_int *b, mp_int *c)``` - функция выполняет операцию: *c = a * a (mod b)*
- ```mp_neg(const mp_int *a, const mp_int *a)``` - функция выполняет операцию: *a = -a*
- ```mp_mod(const mp_int *a, const mp_int *b, const mp_int *a)``` - функция выполняет операцию: *a = a (mod b)*
- ```mp_submod(const mp_int *a, const mp_int *b, const mp_int *c, mp_int *d)``` – функция выполняет операцию: *d = a - b (mod c)*
- ```int mp_cmp_mag(mp_int * a, mp_int * b)``` - функция сравнения: a сравнивается с b. Принимает значение *MP_EQ (a==b), MP_GT (a>b), MP_LT (a<b)*.
- ```mp_count_bits(mp_int * a)```- функция получает количество бит числа a. Применяется в функции ```struct Point BinaryMethod```.
- ```mp_get_bit(mp_int * a, unsigned long i)``` - функция получает значение i-го бита числа a.  Применяется в функции ```struct Point BinaryMethod```.


## Теоретическая вставка

Эллиптическая криптография — раздел криптографии, в котором изучаются асимметричные криптосистемы, основанные на эллиптических кривых над конечными полями, где образующая точка P используется в качестве открытого ключа, а значение степени k, в которую возводится точка, используется в качестве секретного ключа.
Искривленные кривые Эдвардса лежат в основе схемы электронной подписи под названием EdDSA.

Эллиптическая кривая представлена в форме искривленной формы Эдвардса, определенной над конечным простым полем Fp , где р - простое число и р > 3, если она описывается множеством пар чисел (u, v),  u, v принадлежат Fp, удовлетворяющих следующему уравнению:

(eu^2 + v^2) ≡ 1 + du^2 v^2(mod р),

где е, d Fp, ed(e - d) не сравнимо с нулем по модулю р.

Эллиптическая кривая, представленная в форме скрученной кривой Эдвардса имеет также эквивалентное представление в канонической форме, которая задается соответствующими параметрами.


## Параметры и алгоритм возведения в степень

Параметры для эллиптической кривой в искривленной/скрученной форме Эдвардса:  (см. ГОСТ Р 34.10-2012: https://docplayer.ru/46408167-Tehnicheskiy-komitet-026-zadanie-parametrov-skruchennyh-ellipticheskih-krivyh-edvardsa-v-sootvetstvii-s-gost-r.html)

- *p* – характеристика простого поля, над которым определяется эллиптическая кривая.

- *a, d* – коэффициенты эквивалентной скрученной эллиптической кривой в форме Эдвардса.

- *q* – порядок подгруппы простого порядка группы точек эллиптической кривой.

- *u, v* – координаты точки P при эквивалентном представлении в форме скрученной кривой Эдвардса.

При выполнении работы был взят следующий набор параметров (в десятичной системе счисления) id-tc26-gost-3410-2012-256-paramSet A.

Для вычисления кратной точки использовался двоичный алгоритм (лекции, слайд №53):

![Альтернативный текст](https://sun9-55.userapi.com/impg/FP1xfw8FyxH9f4O_lksAeYb0i2BQoGc_YIIAoQ/qYZdzM3iGvE.jpg?size=1044x330&quality=96&proxy=1&sign=55ad5f421327d6a88534916ca54c439b&type=album)

Точка **O** – особая выделенная точка с решением на проектной кривой *(0; 1; 0)*.

Операции удвоения точки и сложения точек были взяты отсюда:
http://hyperelliptic.org/EFD/g1p/auto-twisted-projective.html

Удвоение - mmadd-2008-bbjlp: 
http://hyperelliptic.org/EFD/g1p/data/twisted/projective/addition/mmadd-2008-bbjlp

Сложение - mdbl-2008-bbjlp:
http://hyperelliptic.org/EFD/g1p/data/twisted/projective/doubling/mdbl-2008-bbjlp


## Структуры и функции программы

- ``` struct Point ``` - структура для хранения координат точки.
- ``` struct Parameters ``` - структура для хранения исходных параметров эллиптической кривой в форме искривленной формы Эдвардса.
- ``` void ToText ``` - небольшая вспомогательная функция для вывода на экран числовых значений, хранящихся в mp_int.
- ``` void Transform ``` - функция переводит проективные координаты точки в афинные координаты.
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
