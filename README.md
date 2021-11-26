# SoftIBus


##
Библиотека Arduino для чтения значений протокола RC FlySky Ibus через библиотеку SoftwareSerial
Рабочая версия

Проект все еще находится в разработке, но стремится иметь возможность получать значения IBus без «отключения» аппаратного порта на небольших платах, которые не имеют нескольких выводов Tx и Rx. К примеру Pro Mini и Nano, оба из которых имеют по одному последовательному порту. Так как Nano, например, подключает USB (определенным образом) к этим контактам, использование библиотек IBus, которым нужны настоящие контакты Tx и Rx, делает USB бесполезным. Если, с другой стороны, использовался виртуальный порт, USB все равно мог бы работать для отладки. В случае Pro Mini мой адаптер FTDI предназначен для подключения непосредственно к 6-контактному разъему на передней панели, что означает, что я не смогу использовать его для отладки, если я не использую для этого виртуальный порт (который бы быть беспорядком, учитывая все лишние кабели и ненужные сложности, которые могут возникнуть).

Кроме того можно использовать Arduino для получения значений Ibus, а также для записи значений датчиков. Поскольку для порта датчика требуется не один вывод (вывод «сервопривода» приемников IBus подключается непосредственно к Arduino Rx, в данном случае виртуальный), а одновременно выводы Tx и Rx (с использованием диода, подключенного между ними, как я покажу вам в приложениях), Arduino может принимать (виртуальный Rx) и передавать значения (аппаратный Tx + Rx, на данный момент. Все еще в процессе!). Я наткнулся на библиотеку, в которой для последнего использовался только 1 контакт (очевидно, с использованием SoftwareSerial), но в результате отправленные значения отображались на передатчике FlySky только как целые числа, а не до двух десятичных знаков, разрешенных на экране. С другой стороны, установка Tx + Rx с диодом дала разрешение 0,01. Как можно скорее я постараюсь не только заставить датчик IBus использовать только 1 виртуальный вывод и иметь лучшую точность, но и интегрировать его с этой библиотекой.

Любые комментарии приветствуются, особенно идеи по улучшению и тому подобное. 

#
Arduino library for reading Ibus values through SoftwareSerial pins

The project is still in development, but seeks to be able to receive IBus values without "disabling" the hardware port on small boards which do not have multiple Tx and Rx pins. My case is with the Pro Mini and Nano, both of which have one one serial port. As the Nano, for example, has the USB connected (in a certain way) to these pins, using IBus libraries that needed real Tx and Rx pins left the USB useless. If, on the other hand, a virtual port were used, the USB could still function for debugging. In the case of the Pro Mini, my FTDI adapter is designed to atach directly to the 6-pin header in the front, meaning I wouldn´t be able to use it for debugging, unless I used a virtual port for that (which would be a mess, considering all the extra cables and the unecessary complications that might arise).

Furthermore, I wished to use the Arduino to receive Ibus values but also write sensor ones. Since the sensor port requires not one pin (the "servo" pin of IBus receivers connects directly to the Arduino Rx, in this case a virtual one) but both the Tx and Rx pins at the same time (using a diode connected between them, as I´ll show you in the attachments), it would be possible for the Arduino to receive (virtual Rx) and transmit values (hardware Tx+Rx, for now. Still in process!). I stumbled on a library for using only 1 pin to do the latter (using SoftwareSerial, obviously), but the result was that values sent apeared on the FlySky transmitter as integers only and not up to the two decimal places allowed on the screen. On the other hand, the Tx+Rx setup with the diode gave a resolution of 0.01. As soon as possible I´ll try not only to make the IBus sensor use only 1 virtual pin and have the best precision, but also integrate it with this library.

Any comments are welcome, especially ideas for improvements and such.
