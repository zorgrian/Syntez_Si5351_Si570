//  Конфиг для TRX Raisin  (Изюминка) http://dspview.com/viewtopic.php?f=8&t=210
//  Одна ПЧ 11.059MHz, фильтр LSB, гетеродины не переключаемые, 
//  Первый гетеродин выше частоты приема при LSB и ниже при USB

#ifndef CONFIG_SW_H
#define CONFIG_SW_H

// необходимо раскоментировать требуемую моду (только одну!)

// режим прямого преобразования. частота формируется на 1ом выводе. установить
// CLK0_MULT в значение 1/2/4 в зависимости от коэффициента деления частоты гетеродина
// второй и третий гетеродины отключены
//#define MODE_DC

// режим прямого преобразования с формированием квадратурн
// частота формируется на выводах CLK0,CLK1 со сдвигом фаз 90град
// CLK2 отключен. Минимальная частота настройки 2MHz (по даташиту 4MHz) может зависеть от экземпляра Si5351
// режим работает только при использовании Si5351
//#define MODE_DC_QUADRATURE

// одна промежуточная частота. требуемая боковая формируется на счет переключения
// первого гетеродина с инверсией боковой либо без инверсии. второй гетеродин формируется на выходе CLK1
// тип КФ зависит от параметров SSBDetectorFreq_LSB/USB. если фильтр симметричный (определены две частоты SSBDetectorFreq_*)
// то частота первого гетеродина всегда сверху (меньше пораженок) а боковая выбирается изменением частоты второго гетеродина
#define MODE_SINGLE_IF

// аналогично MODE_SINGLE_IF но второй гетеродин генерируется на CLK1 при RX и
// на CLK2 в режиме TX
//#define MODE_SINGLE_IF_RXTX

// аналогично MODE_SINGLE_IF но в режиме передачи гетеродины комутируются,
// тоесть первый формируется на CLK1, а второй - на CLK0
// для трактов где необходимо переключение гетеродинов при смене RX/TX (например Аматор)
//#define MODE_SINGLE_IF_SWAP

// две промежуточные частоты. гетеродины формируются 1й - CLK0, 2й - CLK1, 3й - CLK2
// первый гетеродин всегда "сверху". выбор боковой полосы производится сменой частоты
// второго гетеродина (если заданы USB/LSB) или сменой частоты третьего гетеродина MODE_DOUBLE_IF
//#define MODE_DOUBLE_IF

// режим аналогичен MODE_DOUBLE_IF но в режиме передачи 2й и 3й гетеродины комутируются,
// тоесть второй формируется на CLK2, а третий - на CLK1
// для трактов с двумя промежуточными частотами где необходимо переключение
// гетеродинов при смене RX/TX
//#define MODE_DOUBLE_IF_SWAP23

// множители частоты на выходах. в случае необходимости получения на выводе 2/4 кратной
// частоты установить в соответствующее значение
const long CLK0_MULT = 1;
const long CLK1_MULT = 1;
const long CLK2_MULT = 1;

// Частота 2го (3го для двойного преобразования) гетеродина в детекторе SSB. 
// Может быть определена как одна константа для верхнего/нижнего ската
// так и обе. При определении только одной константы изменение боковой полосы производится 
// 1ым (2ым для двойного преобразования) гетеродином
// При определении обеих констант они должны находится на соответствующих скатах фидьтра.
// Если используется два раздельных фильтра для выделения LSB/USB то выбор их осуществляется
// с помощью сигнала BCPN_SB на порту дешифратора диапазонов
#define SSBDetectorFreq_LSB   (11060000L+300L)
#define SSBDetectorFreq_USB   (11056950L-300L)

// Первая промежуточная частота для трактов с двойным преобразованием частоты
// Используется только если выбрана одна из мод MODE_DOUBLE_*
// Если полоса шире чем принимаемый сигнал то надо определить IFreqEx
// Если полоса узкая и сигнал надо выровнять по одному из скатов то определяем IFreqEx_USB/LSB
//#define IFreqEx 45000000
//#define IFreqEx_LSB 45000000
//#define IFreqEx_USB 45000000

#endif
