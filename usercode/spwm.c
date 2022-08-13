#include "spwm.h"
#include "user_type_define.h"

float MODULAT = 0.8;   //调制度
float T_sine = 100;    //正弦波周期(ms)

/*
半正弦表生成提示：
spwm中值 = 0；
spwm幅值 = Timer_A CCR0
数组个数为n表示：正弦波半周期(n=100 => T_semi_sine=100ms)包含的定时器溢出中断周期(T_time_IT=1ms)数目
*/
// int const semi_sine_tabel[100] = {
//     0,31,62,94,125,156,187,218,248,278,309,338,368,397,425,453,
// 481,509,535,562,587,612,637,661,684,707,728,750,770,790,809,827,
// 844,860,876,891,904,917,929,940,951,960,968,975,982,987,992,995,
// 998,999,1000,999,998,995,992,987,982,975,968,960,951,940,929,917,
// 904,891,876,860,844,827,809,790,770,750,728,707,684,661,637,612,
// 587,562,535,509,481,453,425,397,368,338,309,278,248,218,187,156,
// 125,94,62,31
// };

/*
正弦表生成提示：
spwm中值 = Timer_A CCR0/2
spwm幅值 = Timer_A CCR0/2
数组个数为n表示：正弦波周期(n=100 => T_sine=100ms)包含的定时器溢出中断周期(T_time_IT=1ms)数目
*/
int const sine_tabel[250] = {
500,512,525,537,550,562,575,587,599,612,624,636,648,660,672,684,
695,707,718,729,740,751,762,773,783,793,803,813,823,833,842,851,
860,868,877,885,893,900,908,915,922,928,935,941,946,952,957,962,
967,971,975,979,982,985,988,991,993,995,996,998,999,999,999,999,
999,999,998,996,995,993,991,988,985,982,979,975,971,967,962,957,
952,946,941,935,928,922,915,908,900,893,885,877,868,860,851,842,
833,823,813,803,793,783,773,762,751,740,729,718,707,695,684,672,
660,648,636,624,612,599,587,575,562,550,537,525,512,500,487,474,
462,449,437,424,412,400,387,375,363,351,339,327,315,304,292,281,
270,259,248,237,226,216,206,196,186,176,166,157,148,139,131,122,
114,106,99,91,84,77,71,64,58,53,47,42,37,32,28,24,
20,17,14,11,8,6,4,3,1,0,0,0,0,0,0,1,
3,4,6,8,11,14,17,20,24,28,32,37,42,47,53,58,
64,71,77,84,91,99,106,114,122,131,139,148,157,166,176,186,
196,206,216,226,237,248,259,270,281,292,304,315,327,339,351,363,
375,387,400,412,424,437,449,462,474,487
};