//  Конфиг для DragonFly Pro http://dspview.com/viewtopic.php?f=8&t=196
//  Одна ПЧ 8MHz, фильтр USB, гетеродины не переключаемые

#ifndef CONFIG_H
#define CONFIG_H

// раскоментировать используемый дисплей (только один!)
//#define DISPLAY_1602
#define DISPLAY_ILI9341

// раскоментировать используемую клавиатуру (только одну!)
//#define KEYPAD_7
#define KEYPAD_12

// раскоментировать установленные чипы
#define VFO_SI5351
#define VFO_SI570

// выбрать в меню калибровку и прописать измеренные частоты на выходах синтезаторов
#define SI5351_CALIBRATION       25003181
#define SI570_CALIBRATION        56319832

// уровень сигнала на выходе Si5351. 0=2mA, 1=4mA, 2=6mA, 3=8mA
#define SI5351_CLK0_DRIVE   0
#define SI5351_CLK1_DRIVE   0
#define SI5351_CLK2_DRIVE   0

/*
  I2C address mapping
  0x25  ! PCF8574/LCD board (alt band control)
  0x26  ! PCF8574/LCD board (3x4 keypad)
  0x27  ! LCD 1602 [optional]
  0x3B  ! PCF8574 (band control)
  0x3E  ! PCF8574 (7 btn keypad)
  0x50  ! 24C04 at TinyRTC board [optional]
  0x55  ! Si570 [optional]
  0x60  ! Si5351 [optional]
  0x68  ! DS1307 at TinyRTC board [optional]
*/

// I2C адреса устройств
#define I2C_ADR_KEYPAD_7      0x3E
#define I2C_ADR_KEYPAD_12     0x26
#define I2C_ADR_DISPLAY_1602  0x27
#define I2C_ADR_EE24C32       0x50
#define I2C_ADR_BAND_CTRL     0x3B

// Pin mapping
#define PIN_IN_TX       4
#define PIN_IN_TUNE     5
#define PIN_OUT_TX      6
#define PIN_OUT_QRP     7
#define PIN_OUT_TONE    8
#define PIN_IN_SMETER   A6
#define PIN_IN_RIT      A7

// распиновка I2C расширителя band control
// двоичный дешифратор диапазона - пины 0-3
#define BCPN_BAND_0     0
#define BCPN_BAND_1     1
#define BCPN_BAND_2     2
#define BCPN_BAND_3     3
// 4й пин - ATT, 5й пин - Preamp, 6й - SSB/CW (можно использовать для переключения фильтров/режимов)
#define BCPN_ATT        4
#define BCPN_PRE        5
#define BCPN_CW         6

// количество импульсов на оборот примененного энкодера
#define ENCODER_PULSE_PER_TURN    360
// изменение частоты в Гц на один оборот в обычном режиме
#define ENCODER_FREQ_LO_STEP      3000
// изменение частоты в Гц на один оборот в ускоренном режиме
#define ENCODER_FREQ_HI_STEP      12000
// порог переключения в ускоренный режим. если частота изменится более
// чем на ENCODER_FREQ_HI_LO_TRASH Гц за секунду то переходим в ускоренный режим
#define ENCODER_FREQ_HI_LO_TRASH  8000                   
// кратность перестройки частоты при нажатой кнопке Fn
#define ENCODER_FN_MULT           10

#define CAT_ENABLE
#define COM_BAUND_RATE  9600      // скорость обмена COM-порта

#define RIT_MAX_VALUE   1200      // максимальная расстройка

#define LSB 0
#define USB 1

// число диапазонов
#define BAND_COUNT  9

extern const struct _Bands {
  uint8_t   mc;
  long  start, startSSB, end;
  uint8_t sideband;
} Bands[];

#define DEFINED_BANDS \
  {160,  1810000L,  1840000L,  2000000L, LSB}, \
  {80,   3500000L,  3600000L,  3800000L, LSB}, \
  {40,   7000000L,  7045000L,  7200000L, LSB}, \
  {30,  10100000L,        0,  10150000L, USB}, \
  {20,  14000000L, 14100000L, 14350000L, USB}, \
  {17,  18068000L, 18110000L, 18168000L, USB}, \
  {15,  21000000L, 21150000L, 21450000L, USB}, \
  {12,  24890000L, 24930000L, 25140000L, USB}, \
  {10,  28000000L, 28200000L, 29700000L, USB}

// для режима general coverage
#define FREQ_MIN  1000000L
#define FREQ_MAX 30000000L

// список комманд трансивера. порядок соответствует обходу физического расположения клавиш слева направо, снизу вверх (7-btn keypad)
enum {
  cmdNone = 0,
  
  // без нажатия Fn  
  cmdBandUp,   // переключение диапазонов или частоты
  cmdBandDown,
  cmdLock,     // Lock freq
  cmdVFOSel,   // VFO A/B
  cmdAttPre,   // переключает по кругу аттенюатор/увч
  cmdVFOEQ,    // VFO A=B

  // с нажатой Fn  
  cmdRIT,      // RIT
  cmdZero,     // устанавливает частоту точно по еденицам кГц. 3623145->3623000
  cmdUSBLSB,   // выбор боковой USB/LSB
  cmdSplit,    // Split on/off
  cmdQRP,      // режим уменьшенной выходной мощности
  cmdHam,      // режим Ham band/General coverage. в режиме Ham кнопки cmdBandUp/Down переключают диапазоны
               // в режиме General coverage - изменяют частоту на +/-1MHz
  
  cmdMenu
};

// необходимо раскоментировать требуемую моду (только одну!)

//*****************************************************************************************//

// режим прямого преобразования. частота формируется на 1ом выводе. установить
// CLK0_MULT в значение 1/2/4 в зависимости от коэффициента деления частоты гетеродина
// второй и третий гетеродины отключены
//#define MODE_DC

// режим прямого преобразования с формированием квадратурн
// частота формируется на выводах CLK0,CLK1 со сдвигом фаз 90град
// CLK2 отключен. Минимальная частота настройки 2MHz (по даташиту 4MHz) может зависеть от экземпляра Si5351
//#define MODE_DC_QUADRATURE

//*****************************************************************************************//

// одна промежуточная частота. требуемая боковая формируется на счет переключения
// первого гетеродина с инверсией боковой либо без инверсии. второй гетеродин формируется на выходе CLK1
// тип КФ зависит от параметров IFreq_LSB/IFreq_USB. если фильтр симметричный (определены две частоты IFreq)
// то частота первого гетеродина всегда сверху (меньше пораженок) а боковая выбирается изменением частоты второго гетеродина
#define MODE_SINGLE_IF

// аналогично MODE_SINGLE_IF но второй гетеродин генерируется на CLK1 при RX и
// на CLK2 в режиме TX
//#define MODE_SINGLE_IF_RXTX

// аналогично MODE_SINGLE_IF но в режиме передачи гетеродины комутируются,
// тоесть первый формируется на CLK1, а второй - на CLK0
// для трактов где необходимо переключение гетеродинов при смене RX/TX
//#define MODE_SINGLE_IF_SWAP

//*****************************************************************************************//

// две промежуточные частоты. гетеродины формируются 1й - CLK0, 2й - CLK1, 3й - CLK2
// первый гетеродин всегда "сверху". выбор боковой полосы производится сменой частоты
// второго гетеродина для режимов MODE_DOUBLE_IF_USB/LSB, или сменой частоты третьего гетеродина MODE_DOUBLE_IF
// в режиме MODE_DOUBLE_IF второй гетеродин выше первой ПЧ
//#define MODE_DOUBLE_IF
//#define MODE_DOUBLE_IF_USB
//#define MODE_DOUBLE_IF_LSB

// режим аналогичен MODE_DOUBLE_IF но в режиме передачи 2й и 3й гетеродины комутируются,
// тоесть второй формируется на CLK2, а третий - на CLK1
// для трактов с двумя промежуточными частотами где необходимо переключение
// гетеродинов при смене RX/TX
//#define MODE_DOUBLE_IF_SWAP23
//#define MODE_DOUBLE_IF_USB_SWAP23
//#define MODE_DOUBLE_IF_LSB_SWAP23

// множители частоты на выходах. в случае необходимости получения на выводе 2/4 кратной
// частоты установить в соответствующее значение
const long CLK0_MULT = 1;
const long CLK1_MULT = 1;
const long CLK2_MULT = 1;

// следующие дефайны определяют какой у нас фильтр - нижняя либо верхняя боковая
// они задают частоту второго (или третьего) гетеродина
// если фильтр имеет симметричные скаты (например мостовой) либо высокое подавление 
// по обеим скатам то раскоментарить и определить оба дефайна
//#define IFreq_LSB   0L
#define IFreq_USB   7998350L

// первая промежуточная частота для трактов с двойным преобразованием частоты
const long IFreqEx = 45000000;

#endif
