Сербаев Вадим, СКБ 172. Отчет по курсовой работе по дисциплине «Программирование алгоритмов защиты информации».

# Работа с библиотекой

## Цель работы

Цель работы заключается в программной реализации эллиптических кривых в ***искривлённой форме Эдвардса*** и арифметических операций над точкой в поле, с последующим тестированием для проверки корректности выполнения поставленной задачи. Для выполнения работы применяется ***библиотека LibTomMath***.

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

Эллиптическая кривая представлена в форме искривленной формы Эдвардса, определенной над конечным простым полем Fp , где р - простое число и р > 3, если она описывается множеством пар чисел / точек *(x, y)*,  *x*, *y* принадлежат *Fp*, удовлетворяющих следующему уравнению:
![Альтернативный текст](https://sun9-2.userapi.com/impg/XcSHrkfI0SeWlLM2THQ_ZLxANIrePxIS2HsAJw/42ZVp0gdINU.jpg?size=239x22&quality=96&proxy=1&sign=849d7911873dced54168a83a78ac00b0&type=album)

В данной реализации предусмотрен переход в проективное пространство, позволяющий избежать операции деления и повысить эффективность вычислений.
Пусть задано проективное пространство:

![Альтернативный текст](https://sun9-15.userapi.com/impg/sxAAANcRSo4nOb5Ky2oCtebqd2SOxa7alrJ_Uw/UFfBU1OJAvU.jpg?size=326x33&quality=96&proxy=1&sign=6ffe5281b033338768a560e61821746a&type=album)

с условием эквивалентности
![Альтернативный текст](https://sun9-69.userapi.com/impg/BqXIpDcWeipn5NziiOQRU9nzfUr7DJvLqLmfLA/5pbX63590_g.jpg?size=367x21&quality=96&proxy=1&sign=7af2f16a17c320aeeb8cccda84579c28&type=album)

причем точка *(0; 0; 0)* не принадлежит 
![Альтернативный текст](https://sun9-14.userapi.com/impg/bBkCNRNbqSgf679Nou5ti2qAAwrBZJ8TPMIrZg/VSk1UWxx3QY.jpg?size=56x22&quality=96&proxy=1&sign=95c58721e6ba3fb4870d5f8278f98f3f&type=album)

В проективных координатах точка P с координатами *(x : y)* переходит в точку с координатами *(X : Y : Z)*
![Альтернативный текст](https://sun9-19.userapi.com/impg/kfcOrjCPiLdzmyNfzylZ2w8tb24iD1OA49oPUw/t2RO2PEKhp4.jpg?size=71x22&quality=96&proxy=1&sign=4bd03d754b484c1cbff69d0485d46bc6&type=album)

Переход осуществляется по формулам:
![Альтернативный текст](https://sun9-35.userapi.com/impg/k_Nh1Hdq9AYIUGdDp1wYm8Jc93gUljV0EUk9YA/kOPTA0q4ROM.jpg?size=233x43&quality=96&proxy=1&sign=3073c188348c05ffb72324da91fb448c&type=album)

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

1. Тест: проверка принадлежности результирующей точки кривой:
![Альтернативный текст](https://sun9-68.userapi.com/impg/CrH2cMiq8JAHrEqBhKCXqND6Zq_8JVf84GMIRw/BP80daV-RWk.jpg?size=2346x1194&quality=96&proxy=1&sign=3cc5413cc42cb7b2108c4c48fc83be40&type=album)

2. Тест: проверка того, что *[q]P = O*, где q – порядок группы точек.
![Альтернативный текст](https://sun9-55.userapi.com/impg/vVrIL23sJuw15GhTudhem3HhPGR1uE_dLpFkdA/ymRGHJXJX60.jpg?size=2526x1302&quality=96&proxy=1&sign=37b52634c6483563d8437fb829e55548&type=album)

3.1. Тест: проверка того, что *[q + 1]P = P*.
![Альтернативный текст](https://sun9-30.userapi.com/impg/f0rciaPTqnMHad2GoHz8ynguEO2xcmI73Xdvdg/jjC_Vwoxsfo.jpg?size=2548x1352&quality=96&proxy=1&sign=dfffc9b648452ee375ca88dc180a3bee&type=album)

3.2. Тест: проверка того, что *[q − 1]P = −P*.
![Альтернативный текст](https://sun9-70.userapi.com/impg/07uAOvan_OCTjSBO4XOOGVPMmtr0ahCQba46fA/9XKjKLcqfx0.jpg?size=2508x1056&quality=96&proxy=1&sign=bbee1b2948f31189e04e3356a10aba56&type=album)

4. Тест: проверка того, что для двух случайных *k1* и *k2* выполняется: *[k1]P + [k2]P = [k1 + k2]P* 
Пояснения: первые три координаты - результат *[k1]P + [k2]P*, три последующие - *[k1 + k2]P*
![Альтернативный текст](https://sun9-49.userapi.com/impg/IsMAcy79I53OF8bN0U6Agpg3bfYHM1cf6e7muQ/imnIdugpECc.jpg?size=2524x1226&quality=96&proxy=1&sign=1508ad241856197885303fc193c376f2&type=album)

## Источники

- Официальная документация библиотеки LibTomMath доступна по ссылке: https://docviewer.yandex.ru/view/158126255/?page=30&*=7xuiznXmFLC1blVp%2BowakWJzq357InVybCI6Imh0dHBzOi8vZ3RvYWwuY29tL3NyYy9tb2JpL2NsaXQxOC9saWJ0b21tYXRoLTAuNDEvYm4ucGRmIiwidGl0bGUiOiJibi5wZGYiLCJub2lmcmFtZSI6dHJ1ZSwidWlkIjoiMTU4MTI2MjU1IiwidHMiOjE2MDM2NTgzMTk5NjcsInl1IjoiNjQ5OTUwODY3MTU3MjI5ODkzOSIsInNlcnBQYXJhbXMiOiJsYW5nPWVuJnRtPTE2MDM0NjcwMDgmdGxkPXJ1Jm5hbWU9Ym4ucGRmJnRleHQ9bGlidG9tbWF0aCtkb2N1bWVudGF0aW9uJnVybD1odHRwcyUzQS8vZ3RvYWwuY29tL3NyYy9tb2JpL2NsaXQxOC9saWJ0b21tYXRoLTAuNDEvYm4ucGRmJmxyPTIxMyZtaW1lPXBkZiZsMTBuPXJ1JnNpZ249OTI2OTRkZGZkMmUyYTMyY2ZlOTkxOGUxNDMyYTAwNTcma2V5bm89MCJ9&lang=en
- Установка пакетов в Gentoo:
https://losst.ru/ustanovka-paketov-v-gentoo
- Р 1323565.1.024—2019:
https://files.stroyinf.ru/Data2/1/4293730/4293730019.pdf
- Twisted Edwards Curves - Daniel J. Bernstein1, Peter Birkner2, Marc Joye3, Tanja Lange2, and Christiane Peters2:
https://eprint.iacr.org/2008/013.pdf
- Лекции
