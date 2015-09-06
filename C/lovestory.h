#ifndef _LOVESTORY_H_
#define	_LOVESTORY_H_

#define Increasing ++
#define year wYear
#define month wMonth
#define day wDay
#define nextDay love.day++;
#define nextMonth (love.day>(daysPerMonth[love.month]+((love.month==2)&&(love.day==29)&&((love.year%400==0)||((love.year%4==0)&&(love.year%100!=0))))))
#define nextYear (nextMonth && (love.day=1,love.month++,love.month>12 && (love.month=1,love.year++)))
#define dataMatch ((love.year==timeNow.year)&&(love.month==timeNow.month)&&(love.day==timeNow.day))
#define loveStory (dataMatch && (printf("We have met for %d days!\n",Love),printf("We have fell in love for %d days!\n",Love-100)))
#define LoveStory if(loveStory){
#define Endless goto Program;}}
#define Story int
#define Begin main(){
#define ends :
#define lasts =(WORD)INT_MAX;
#define forever system("pause");}
#define LoveExists while(TRUE){
#define Appear =1;
#define We SYSTEMTIME
#define met timeNow;
#define fell love={2013,3,0,25};
#define in WORD
#define March25 WORD daysPerMonth[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
#define July3 GetLocalTime(&timeNow);

#endif  /* _LOVESTORY_H_ */
